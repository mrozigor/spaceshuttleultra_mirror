#pragma once

#include "AtlantisSubsystem.h"
#include "discsignals/DiscInPort.h"
#include "discsignals/DiscOutPort.h"
#include "eps/eps_defs.h"



class MechActuator: public AtlantisSubsystem
{
	double fOutPos; //Output position 0 ... 1
	double fSpeed;  // 1/s

	double fLimit0Max;
	double fLimit1Min;
	double fHardStopMin;
	double fHardStopMax;

	double fMaxSpeed;
	double fAccConstant;
	double fMechMI;
	
	UINT object_anim;
	bool fSingleMotorFlag;
	
public:
	MechActuator(SubsystemDirector* _pDirect, const string& _ident, double fStandardTime = 0.0);
	virtual ~MechActuator();
	virtual void OnPreStep(double fSimT, double fDeltaT, double fMJD);
	virtual void OnPostStep(double fSimT, double fDeltaT, double fMJD);
	virtual void OnPropagate(double fSimT, double fDeltaT, double fMJD);
	/*
	void SetMotorParams(double fNormTorque, double fNormAmps, double fNormSpeed, 
		double fNormVoltage);
	void SetObjectParams(double fMinTorque, double fFrictionCoeff, 
		double fMOICoeff);
	*/
	void SetSingleMotorTime(double fTimeSingle);
	/**
	 * @param fLimit0 maximum position to set Limit 0 discrete
	 * @param fLimit1 minimum position to set Limit 1 discrete
	 */
	void SetMicroSwitchPositions(double fLimit0, double fLimit1);
	void SetState(double fState0);
	void SetObjectAnim(UINT anim);

	discsignals::DiscOutPort PosLimit0;
	discsignals::DiscOutPort PosLimit1;
	
	discsignals::DiscInPort LogicPwrOn;

	eps::ACMotor system[2];
};