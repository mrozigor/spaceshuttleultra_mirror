#include "PEG4Targeting.h"
#include "UltraMath.h"

//static const double PROPAGATOR_STEP_LENGTH = 0.2;
static const double PROPAGATOR_STEP_LENGTH = 0.05;
static const int PROPAGATOR_STEP_COUNT = 800;
static const double MAX_RANGE_ERROR = 1000.0/MPS2FPS;
//static const double MAX_RANGE_ERROR = 2000.0;
static const int MAX_ITERATIONS = 20;

VECTOR3 CalculatePEG7Targets(double C1, double C2, double transferAngle, const VECTOR3& initialPos, const VECTOR3& targetPos, double mu, double& transferTime)
{
	// algorithm from LTVCON function described in NASA document (dated 1976)
	// http://ntrs.nasa.gov/search.jsp?R=19760024151
	
	double S = (length(targetPos) + length(initialPos) + length(targetPos-initialPos))/2.0;
	double r_circ = S/2.0;
	double v_circ = sqrt(mu/r_circ);
	
	double A = ((length(targetPos)/length(initialPos)) - cos(transferAngle)) - C2*sin(transferAngle);
	double B = -(C1/v_circ)*sin(transferAngle);
	double C = -(r_circ/length(targetPos))*(1-cos(transferAngle));
	double D = B*B - 4*A*C;

	if(D < 0.0) return _V(0, 0, 0); // no solution
	double final_horizontal_vel = -2.0*C/(B + sqrt(D)); // normalized horizontal velocity (inertial frame) at target pos
	//double final_horizontal_vel = (sqrt(D)-B)/(2.0*A); // normalized horizontal velocity (inertial frame) at target pos
	double initial_horizontal_vel = (length(targetPos)/length(initialPos))*final_horizontal_vel;
	double final_radial_vel = (C1/v_circ) + C2*final_horizontal_vel;
	double initial_radial_vel = final_radial_vel*cos(transferAngle) - (final_horizontal_vel-(r_circ/length(targetPos))/final_horizontal_vel)*sin(transferAngle);

	//VECTOR3 orbit_plane = crossp(targetPos, initialPos);
	VECTOR3 orbit_plane = crossp(initialPos, targetPos);
	orbit_plane /= length(orbit_plane);
	VECTOR3 initialPos_unit = initialPos/length(initialPos);
	VECTOR3 initial_vel = (initialPos_unit*initial_radial_vel + crossp(orbit_plane, initialPos_unit)*initial_horizontal_vel)*v_circ;
	//VECTOR3 final_vel = v_circ*(final_radial_vel*targetPos/length(targetPos) + final_horizontal_vel*crossp(orbit_plane, targetPos));

	// calculate transfer time
	kostStateVector postBurnState;
	postBurnState.pos = ConvertBetweenLHAndRHFrames(initialPos);
	postBurnState.vel = ConvertBetweenLHAndRHFrames(initial_vel);
	kostElements postBurnElements;
	kostOrbitParam postBurnParams;
	kostStateVector2Elements(mu, &postBurnState, &postBurnElements, &postBurnParams);
	double trueAnomaly;
	kostGetTrueAnomaly(mu, &postBurnElements, &trueAnomaly, 0.01*RAD, 50);
	trueAnomaly += transferAngle; // true anomaly at target point
	if(trueAnomaly > 2*PI) trueAnomaly -= 2*PI;
	else if(trueAnomaly < 0.0) trueAnomaly += 2*PI;
	// convert true anomaly to mean anomaly
	double eccAnomaly = atan2(sqrt(1 - postBurnElements.e*postBurnElements.e)*sin(trueAnomaly), postBurnElements.e+cos(trueAnomaly));
	if(eccAnomaly < 0.0) eccAnomaly += 2*PI;
	double finalMeanAnomaly = eccAnomaly - postBurnElements.e*sin(eccAnomaly);
	// calculate time between initial and target positions
	double meanMotion = (2*PI)/postBurnParams.T;
	double deltaM = finalMeanAnomaly-postBurnParams.MnA;
	if(deltaM <= 0.0) deltaM += 2*PI;
	transferTime = deltaM/meanMotion;
	//double lambda = sign(sin(transferAngle))*sqrt(1 - length(targetPos-initialPos)/S);
	//double U = lambda*sqrt(S - length(initialPos)/(S-length(targetPos))) + initial_horizontal_vel-initial_radial_vel; 
	//if(U <= -1) return _V(0, 0, 0); // hyperbolic solution
	//double E = sqrt(1 - lambda*lambda*(1-U*U)) - lambda*U;
	//double W = sqrt(1 + lambda + 
	return initial_vel;
}

PEG4Propagator::PEG4Propagator()
: burnInProgress(false), burnCompleted(false)
{
}

PEG4Propagator::~PEG4Propagator()
{
}

void PEG4Propagator::SetBurnData(double TIG, const VECTOR3 &equDeltaV, double acceleration)
{
	burnInProgress = false;
	burnCompleted = false;
	this->TIG = TIG;
	lastMET = TIG;
	VGO = length(equDeltaV);
	equBurnDirection = equDeltaV/VGO; // normalise DV vector
	acc = acceleration;
}

void PEG4Propagator::GetCutoffStateVector(VECTOR3& pos, VECTOR3& vel) const
{
	pos = cutoffPos;
	vel = cutoffVel;
}

VECTOR3 PEG4Propagator::GetAcceleration(double MET, const VECTOR3& equPos, const VECTOR3& equVel)
{
	//char cbuf[255];
	if(!burnInProgress && !burnCompleted && MET>=TIG) burnInProgress = true;

	if(burnInProgress) {
		VGO -= acc*(MET-lastMET);
		if(VGO <= 0.0) {
			burnCompleted = true;
			burnInProgress = false;
			cutoffPos = equPos;
			cutoffVel = equVel;
			//sprintf_s(cbuf, 255, "MET: %f burn completeted", MET);
			//oapiWriteLog(cbuf);
		}
		//sprintf_s(cbuf, 255, "MET: %f VGO: %f burn in progress", MET, VGO);
		//oapiWriteLog(cbuf);
		lastMET = MET;
		return equBurnDirection*acc;
	}
	
	return _V(0, 0, 0);
}

PEG4Targeting::PEG4Targeting()
: propagator(PROPAGATOR_STEP_LENGTH, PROPAGATOR_STEP_COUNT, 7200), currentState(ERR)
{
}

PEG4Targeting::~PEG4Targeting()
{
}

void PEG4Targeting::SetPlanetParameters(double _planetMass, double _planetRadius, double J2Coeff)
{
	planetMass = _planetMass;
	planetRadius = _planetRadius;
	mu = GGRAV*planetMass;
	propagator.SetParameters(1.0, _planetMass, _planetRadius, J2Coeff);
}

void PEG4Targeting::SetPEG4Targets(double C1, double C2, double HT, double transferAngle, const VECTOR3& _initialPos, const VECTOR3& _initialVel, double vesselAcceleration)
{
	initialPos = _initialPos;
	initialVel = _initialVel;
	this->C1 = C1;
	this->C2 = C2;
	this->transferAngle = transferAngle;
	acceleration = vesselAcceleration;
	// calculate target position
	orbitPlane = crossp(initialPos/length(initialPos), initialVel/length(initialVel));
	targetPos = RotateVector(orbitPlane, transferAngle, initialPos/length(initialPos));
	targetPos = targetPos*(planetRadius + HT);

	totalMissOffset = _V(0.0, 0.0, 0.0);
	PerformTargetingIteration();
	cutoffPos = initialPos; // for first iteration, assume instantaneous burn
	cutoffVel = initialVel;

	iterationCount = 0;
	currentState = BURN_PROP;

	totalMissOffset = _V(0.0, 0.0, 0.0);
	equDeltaV = _V(0.0, 0.0, 0.0);
	PerformTargetingIteration();
}

bool PEG4Targeting::Step()
{
	if(propagatorStepsRemaining > 0) {
		propagator.Step(0.0, 0.01);
		propagatorStepsRemaining--;
	}
	else { // finished propagating
		if(currentState == BURN_PROP) {
			//VECTOR3 cutoffVel;
			//propagator.GetStateVectors(burnTime, cutoffPos, cutoffVel);
			omsPropagator.GetCutoffStateVector(cutoffPos, cutoffVel);
			orbitPlane = crossp(cutoffPos/length(cutoffPos), cutoffVel/length(cutoffVel));
			if(iterationCount%2 == 1) { // only propagate every other iteration to target point - this helps convergence when acceleration is low by correcting errors due to burn duration
				PerformTargetingIteration();
			}
			else {
				//propagatorStepsRemaining = static_cast<int>(1.25*coastTime/(PROPAGATOR_STEP_LENGTH*PROPAGATOR_STEP_COUNT))+1; // number of steps required before propagator reaches transfer time
				propagatorStepsRemaining = static_cast<int>(coastTime/(PROPAGATOR_STEP_LENGTH*PROPAGATOR_STEP_COUNT))+1; // number of steps required before propagator reaches transfer time
				currentState = COAST_PROP;
			}
		}
		else if(currentState == COAST_PROP) {
			VECTOR3 propPos, propVel;
			propagator.GetStateVectors(coastTime+burnTime, propPos, propVel);
			//propagator.GetStateVectors(transferTime-1.0, propPos, propVel);
			VECTOR3 missOffset = targetPos - propPos;
			// ignore any out-of-plane error
			missOffset -= orbitPlane*dotp(missOffset, orbitPlane);
			//missOffset = orbitPlane*dotp(missOffset, orbitPlane);
			totalMissOffset += missOffset;
			char cbuf[255];
			sprintf_s(cbuf, 255, "Miss offset: %f %f %f Time: %f", missOffset.x, missOffset.y, missOffset.z, coastTime+burnTime);
			//sprintf_s(cbuf, 255, "Total Miss offset: %f %f %f Time: %f", totalMissOffset.x, totalMissOffset.y, totalMissOffset.z, transferTime);
			oapiWriteLog(cbuf);
			if(length(missOffset) < MAX_RANGE_ERROR) currentState = COMPLETE;
			else {
				PerformTargetingIteration();
				if(iterationCount > MAX_ITERATIONS) {
					currentState = ERR;
					equDeltaV = _V(0.0, 0.0, 0.0);
				}
			}
		}
	}

	//return (currentState != RUNNING);
	return (currentState >= COMPLETE);
}

VECTOR3 PEG4Targeting::GetDeltaV() const
{
	return equDeltaV;
}

double PEG4Targeting::GetTransferTime() const
{
	return coastTime+burnTime;
}

bool PEG4Targeting::Converged() const
{
	return currentState == COMPLETE;
}

void PEG4Targeting::PerformTargetingIteration()
{
	VECTOR3 correctedTargetPos = targetPos+totalMissOffset;
	// calculate coast phase transfer angle to account for miss offset
	double correctedTransferAngle = acos(dotp(cutoffPos/length(cutoffPos), correctedTargetPos/length(correctedTargetPos)));
	// acos is limited to [0, pi]; transfer angle is within [0, 3*pi]
	if(transferAngle >= 2*PI) correctedTransferAngle += 2*PI;
	if(transferAngle >= PI) correctedTransferAngle = 2*PI - correctedTransferAngle;
	
	VECTOR3 reqdVel = CalculatePEG7Targets(C1, C2, correctedTransferAngle, cutoffPos, correctedTargetPos, mu, coastTime);
	equDeltaV += reqdVel - cutoffVel; // in first iteration, this will be reqd-initial; further iterations will refine value
	equDeltaV -= orbitPlane*dotp(equDeltaV, orbitPlane); // remove any out-of-plane component
	burnTime = length(equDeltaV)/acceleration;

	char cbuf[255];
	sprintf_s(cbuf, 255, "DV: %f %f %f", equDeltaV.x, equDeltaV.y, equDeltaV.z);
	oapiWriteLog(cbuf);

	omsPropagator.SetBurnData(0.0, equDeltaV, acceleration);
	
	propagator.UpdateStateVector(initialPos, initialVel, 0.0, true);
	propagator.DefinePerturbations(&omsPropagator);
	propagatorStepsRemaining = static_cast<int>(burnTime/(PROPAGATOR_STEP_LENGTH*PROPAGATOR_STEP_COUNT))+1; // number of steps required before propagator reaches transfer time
	currentState = BURN_PROP;
	iterationCount++;
}