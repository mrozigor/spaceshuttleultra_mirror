#pragma once

#include <vector>
#include "../vc/vc_defs.h"
#include "dps_defs.h"
#include "BIU.h"
#include "../Keyboard.h"
#include "../discsignals/DiscInPort.h"
#include <map>

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
		virtual void Run(double fSimT, double fDeltaT) = 0;
		virtual void PaintMDU(vc::MDU* pmdu) = 0;
	};

	/**
	 * Implementation of the Integrated display processor. Each can deal with a infinite number of 
	 * MDUs. 
 	 */
	class IDP : public AtlantisSubsystem {
	public:
		typedef enum __memory_state {
			MS_EMPTY = 0,
			MS_IPL,
			MS_OPERATIONAL
		} MEMORY_STATE;

		BIU dk_channel;
		BIU fc_channel[4];
	private:
		unsigned short usIDPID;
		vc::PMDU mdu_list[7];
		MAJORFUNCTION majfunc;
		MEMORY_STATE memstate;

		unsigned short usGPCDay;
		unsigned short usGPCHour;
		unsigned short usGPCMinute;
		unsigned short usGPCSecond;

		bool bGPCTimerActive;

		unsigned short usTimerDay;
		unsigned short usTimerHour;
		unsigned short usTimerMinute;
		unsigned short usTimerSecond;

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

		vector<IDPSoftware*> software_storage;

		IDPSoftware* pOTP;

		map<unsigned short, IDPSoftware*> ipl_software;

		map<unsigned short, IDPSoftware*> gnc_ops;
		map<unsigned short, IDPSoftware*> gnc_specdisp;

		map<unsigned short, IDPSoftware*> sm_ops;
		map<unsigned short, IDPSoftware*> sm_specdisp;

		map<unsigned short, IDPSoftware*> pl_ops;
		map<unsigned short, IDPSoftware*> pl_specdisp;

		map<unsigned short, IDPSoftware*> bfs_ops;
		map<unsigned short, IDPSoftware*> bfs_specdisp;

		void CreateSoftware();

		void AppendScratchPadLine(char cKey);
		void ClearScratchPadLine();
		void DelFromScratchPadLine();
	protected:
		virtual void OnMMChange(unsigned short usNewMM);
		virtual void OnSysSummary();
		virtual void OnFaultSummary();
		virtual void OnMsgReset();
		virtual void OnAck();
		virtual void OnClear();
		virtual void OnExec();

		void PrintTime(vc::MDU* mdu);
		
	public:
		IDP(SubsystemDirector* pDirect, const string& _ident, unsigned short _usIDPID);
		virtual ~IDP();
		
		void ConnectToMDU(vc::PMDU pMDU, bool bPrimary = true);
		void ConnectToKeyboard(Keyboard* pKeyboardA, Keyboard* pKeyboardB);
		unsigned short GetIDPID() const;
		unsigned short GetOps() const;
		unsigned short GetSpec() const;
		unsigned short GetDisp() const;
		unsigned short GetKeyboardSelection() const;
		virtual MAJORFUNCTION GetMajfunc() const;
		virtual const char* GetScratchPadLineString() const;
		virtual const char* GetScratchPadLineScan() const;
		/**
		 * Perform a initial program load.
		 * Basically just reset software configuration to basic and 
		 * request critical format data from assigned GPC.
		 */
		
		virtual void IPL();
		bool IsBFS() const;
		virtual bool PutKey(unsigned short usKeyboardID, char cKey);
		void SetSpec(unsigned short spec);
		void SetDisp(unsigned short disp);
		void SetMajFunc(MAJORFUNCTION func);
		virtual void OnSaveState(FILEHANDLE scn) const;
		virtual bool OnParseLine(const char* line);
		//
		inline bool IsOPSLine() const {return (cScratchPadLine[0] == SSU_KEY_OPS);};
		inline bool IsSPECLine() const {return (cScratchPadLine[0] == SSU_KEY_SPEC);};
		inline bool IsITEMLine() const {return (cScratchPadLine[0] == SSU_KEY_ITEM);};
		inline bool IsGPCIDPLine() const {return (cScratchPadLine[0] == SSU_KEY_GPCIDP);};
		inline bool IsNoLine() const {return (cScratchPadLine[0] == '\0');};
		bool IsCompleteLine() const;

		virtual bool OnPaint(vc::MDU* pMDU);
		
	};
};
