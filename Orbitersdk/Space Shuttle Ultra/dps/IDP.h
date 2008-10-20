#pragma once

#include <vector>
#include "../vc/vc_defs.h"
#include "dps_defs.h"
#include "../Keyboard.h"
#include "../discsignals/DiscInPort.h"
#include <map>

namespace dps {
	class IDP;
};

namespace dps {	
	using class ::Keyboard;
	using class discsignals::DiscInPort;

	using namespace std;

	const char DEUATT_NORMAL = 0;
	const char DEUATT_OVERBRIGHT = 1;
	const char DEUATT_FLASHING = 2;
	const char DEUATT_UNDERLINED = 4;

	/**
	 * Generic class for IDP display. 
	 * Each display should implement it's own functions for drawing and input. 
 	 */
	class IDPSoftware {
		IDP* pIDP;
	public:
		IDPSoftware(IDP* hardware);
		virtual ~IDPSoftware();
		virtual void Run(double fSimT, double fDeltaT);
	};

	/**
	 * Implementation of the Integrated display processor. Each can deal with a infinite number of 
	 * MDUs. 
 	 */
	class IDP : public AtlantisSubsystem {
		unsigned short usIDPID;
		vc::PMDU mdu_list[7];
		MAJORFUNCTION majfunc;
		unsigned short usOPS;
		unsigned short usSPEC;
		unsigned short usDISP;
		Keyboard* pKeyboardA;
		Keyboard* pKeyboardB;
		bool bUseKeyboardA;
		char cScratchPadLine[120];
		short sScratchPadLength;
		unsigned short usGPCDriver;
		unsigned short usSelectedFC;
		DiscInPort KeybSelectA;
		DiscInPort KeybSelectB;
		DiscInPort MajorFuncGNC;
		DiscInPort MajorFuncPL;

		map<unsigned short, IDPSoftware*> ipl_software;

		map<unsigned short, IDPSoftware*> gnc_ops;
		map<unsigned short, IDPSoftware*> gnc_specdisp;

		map<unsigned short, IDPSoftware*> sm_ops;
		map<unsigned short, IDPSoftware*> sm_specdisp;

		map<unsigned short, IDPSoftware*> pl_ops;
		map<unsigned short, IDPSoftware*> pl_specdisp;

		map<unsigned short, IDPSoftware*> bfs_ops;
		map<unsigned short, IDPSoftware*> bfs_specdisp;
		
	public:
		IDP(SubsystemDirector* pDirect, const string& _ident, unsigned short _usIDPID);
		virtual ~IDP();
		/**
		 * Perform a initial software load.
		 * Basically just reset software configuration to basic and 
		 * request critical format data from assigned GPC.
		 */
		void IPL();
		void ConnectToMDU(vc::PMDU pMDU, bool bPrimary = true);
		void ConnectToKeyboard(Keyboard* pKeyboardA, Keyboard* pKeyboardB);
		unsigned short GetIDPID() const;
		unsigned short GetOps() const;
		unsigned short GetSpec() const;
		unsigned short GetDisp() const;
		MAJORFUNCTION GetMajfunc() const;
		void SetSpec(unsigned short spec);
		void SetDisp(unsigned short disp);
		void SetMajFunc(MAJORFUNCTION func);
		virtual void OnSaveState(FILEHANDLE scn) const;
		virtual bool OnParseLine(const char* line);
	};
};
