/****************************************************************************
  This file is part of Space Shuttle Ultra

  MPMSystem definition



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
#ifndef __MPMSUBSYSTEMS_H
#define __MPMSUBSYSTEMS_H
#pragma once

#include "Latch.h"
#include "discsignals.h"
#include "Atlantis.h"

const double MPM_DEPLOY_SPEED = 0.0294117647;
const double MRL_LATCH_SPEED = 0.11765;
// speed of MPM latches (8.5 seconds)
const double MRL_MAX_ANGLE_ERROR = 0.1;
// max angular misalignment (in degrees) between MPM and OBSS/RMS to allow latching

using namespace discsignals;

class MPMSystem : public LatchSystem
{
public:
	MPMSystem(AtlantisSubsystemDirector* _director, const string& _ident, const char* _meshname, const VECTOR3& _meshOffset, const string& _attachID);
	virtual ~MPMSystem();

	virtual void Realize();
	virtual void OnPreStep(double SimT, double DeltaT, double MJD);
	//virtual void OnPostStep(double SimT, double DeltaT, double MJD);
	virtual bool OnParseLine(const char* line);
	virtual void OnSaveState(FILEHANDLE scn) const;

	void CheckDoubleAttach(VESSEL* vessel, bool attached) { 
		if((attachedPayload && attachedPayload==vessel) || (hAttach && vessel->GetHandle()==STS()->GetAttachmentStatus(hAttach))) doubleAttached=attached; 
	};

	/*bool Deployed() const {return MPMRollout.Open();};
	bool Stowed() const {return MPMRollout.Closed();};
	bool Released() const {return MRLLatches.Open();};
	bool Latched() const {return MRLLatches.Closed();};*/
protected:
	virtual void OnMRLLatched();
	virtual void OnMRLReleased();

	virtual void OnAttach();
	virtual void OnDetach();

	UINT mesh_index;
	// all animations should be added by derived classes
	UINT anim_mpm;

	//true if MPM was moved this timestep
	bool mpm_moved;
	// true if MPM is attached to object that is attached to something else
	bool doubleAttached;

	AnimState MPMRollout, MRLLatches;
	DiscOutPort MRL_Rel_Microswitches[3], MRL_Lat_Microswitches[3], MRL_RTL_Microswitches[3];
	DiscOutPort MRL_Latched, MRL_Released;
	DiscOutPort MPM_Stowed, MPM_Deployed;
private:
	void AddMesh();
	
	MESHHANDLE hMesh;
	VECTOR3 mesh_offset;

	DiscInPort Release, Latch;
	DiscInPort Deploy, Stow;

	DiscInPort PLBayMECHPWRSYS_ON[2];
};

#endif //__MPMSUBSYSTEMS_H