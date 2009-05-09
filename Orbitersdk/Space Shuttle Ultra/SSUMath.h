 /****************************************************************************
  This file is part of Space Shuttle Ultra

  SSU mathematical functions



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See http://spaceshuttleultra.sourceforge.net/license/ for more details.

  **************************************************************************/
#pragma once

#include "OrbiterAPI.h"
#include <cmath>
#include "SSUEngConst.h"

const MATRIX3 IdentityMatrix = _M(1, 0, 0,
								  0, 1, 0,
								  0, 0, 1);

//Math
VECTOR3 GetPYR(VECTOR3 Pitch, VECTOR3 YawRoll);
VECTOR3 GetPYR2(VECTOR3 Pitch, VECTOR3 YawRoll);
//returns rotation axis and angle of rotation (in radians)
double CalcEulerAngle(const MATRIX3 &RefAngles, const MATRIX3 &TargetAngles, VECTOR3 &Axis);
double CalcEulerAngle(const VECTOR3 &RefAngles, const VECTOR3 &TargetAngles, VECTOR3 &Axis);
void RotateVector(const VECTOR3 &Initial, const VECTOR3 &Angles, VECTOR3 &Result);
void RotateVectorPYR(const VECTOR3 &Initial, const VECTOR3 &Angles, VECTOR3 &Result);
void RotateVectorPYR2(const VECTOR3 &Initial, const VECTOR3 &Angles, VECTOR3 &Result);
VECTOR3 GetAnglesFromMatrix(const MATRIX3 &RotMatrix); //returns angles in radians
VECTOR3 GetPYRAnglesFromMatrix(const MATRIX3 &RotMatrix); //returns angles in radians
void GetRotMatrixX(double Angle, MATRIX3 &RotMatrixX);
void GetRotMatrixY(double Angle, MATRIX3 &RotMatrixY);
void GetRotMatrixZ(double Angle, MATRIX3 &RotMatrixZ);
	
static inline VECTOR3 Normalize(const VECTOR3 &a)
{
	return (a/length(a));
}
	
	
static inline VECTOR3 Projection(const VECTOR3 &u, const VECTOR3 &v) //Proj u onto v
{
	return v*(dotp(u, v)/dotp(v, v));
}

static inline VECTOR3 ToRad(const VECTOR3 &Input)
{
		VECTOR3 Output;
		for(int i=0;i<3;i++) {
			Output.data[i]=Input.data[i]*RAD;
		}
		return Output;
	}
	
static inline VECTOR3 ToDeg(const VECTOR3 &Input)
{
	VECTOR3 Output;
	for(int i=0;i<3;i++) {
		Output.data[i]=Input.data[i]*DEG;
	}
	return Output;
}
	
static inline VECTOR3 NormZ(VECTOR3 &v)
{
	// error checking
	/*if((pow(v.x,2)-pow(v.y,2))>0.1) {
		sprintf_s(oapiDebugString(), 255, "NormZ ERROR: Vector %f %f %f passed at T: %f",
			v.x, v.y, v.z, met);
		oapiWriteLog(oapiDebugString());
		return _V(0, 0, 1);
	}*/
	VECTOR3 o=v;
	o.z=sqrt(1.0-pow(v.x,2)-pow(v.y,2));
	return o;
}

static inline bool Eq(const double d1, const double d2, double dDiff=0.00001)
{
	if(fabs(d1-d2)>dDiff) return false;
	return true;
}

static inline bool Eq(const VECTOR3 v1, const VECTOR3 v2, double dDiff=0.00001)
{
	for(int i=0;i<3;i++) {
		if(fabs(v1.data[i]-v2.data[i])>dDiff) return false;
	}
	return true;
}

static inline double range(double min, double value, double max)
{
	if(value<min) return min;
	if(value>max) return max;
	return value;
}

static inline VECTOR3 RotateVectorX(const VECTOR3 &v, double angle) //rotates about angle (in degrees) in X-axis
{
	VECTOR3 Output;
	Output.x=v.x;
	Output.z=v.z*cos(angle*RAD)-v.y*sin(angle*RAD);
	Output.y=v.y*cos(angle*RAD)+v.z*sin(angle*RAD);
	return Output;
}
static inline VECTOR3 RotateVectorY(const VECTOR3 &v, double angle) //rotates about angle (in degrees) in Y-axis
{
	VECTOR3 Output;
	Output.y=v.y;
	Output.x=v.x*cos(angle*RAD)-v.z*sin(angle*RAD);
	Output.z=v.z*cos(angle*RAD)+v.x*sin(angle*RAD);
	return Output;
}
static inline VECTOR3 RotateVectorZ(const VECTOR3 &v, double angle) //rotates about angle (in degrees) in Z-axis
{
	VECTOR3 Output;
	Output.x=v.x*cos(angle*RAD)-v.y*sin(angle*RAD);
	Output.y=v.x*sin(angle*RAD)+v.y*cos(angle*RAD);
	Output.z=v.z;
	return Output;
}