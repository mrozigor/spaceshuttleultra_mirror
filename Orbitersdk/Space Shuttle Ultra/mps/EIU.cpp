#include "EIU.h"


namespace mps
{
	EIU::EIU( SubsystemDirector* _director, const string& _ident, int nID, SSME* ptr ):AtlantisSubsystem( _director, _ident )
	{
		ID = nID;
		engine = ptr;

		PrimaryData = new VDT_32;
		SecondaryData = new VDT_6;

		engine->dataGetPrimaryData( PrimaryData );
		engine->dataGetSecondaryData( SecondaryData );
		return;
	}

	EIU::~EIU( void )
	{
		delete PrimaryData;
		delete SecondaryData;
		// the end
	}

	int EIU::RequestCMD( int cmd, double data )
	{
		switch (cmd)
		{
			case 1:
				if (engine->cmdPurgeSequence1() == true) return 1;
				return 2;
			case 2:
				if (engine->cmdPurgeSequence2() == true) return 1;
				return 2;
			case 3:
				if (engine->cmdPurgeSequence3() == true) return 1;
				return 2;
			case 4:
				if (engine->cmdPurgeSequence4() == true) return 1;
				return 2;
			case 5:
				if (engine->cmdStartEnable() == true) return 1;
				return 2;
			case 6:
				if (engine->cmdStart() == true) return 1;
				return 2;
			case 7:
				if (engine->cmdControllerReset() == true) return 1;
				return 2;
			case 8:
				if (engine->cmdCheckoutStandby() == true) return 1;
				return 2;
			case 9:
				if (engine->cmdTerminateSequence() == true) return 1;
				return 2;
			case 10:
				if (engine->cmdShutdownEnable() == true) return 1;
				return 2;
			case 11:
				if (engine->cmdShutdown() == true) return 1;
				return 2;
			case 12:
				if (engine->cmdFRT1() == true) return 1;
				return 2;
			case 13:
				if (engine->cmdOxidizerDump() == true) return 1;
				return 2;
			case 14:
				if (engine->cmdExitPROM() == true) return 1;
				return 2;
			case 15:
				if (engine->cmdPowerOn() == true) return 1;
				return 2;
			case 16:
				if (engine->cmdChannelReset() == true) return 1;
				return 2;
			case 17:
				if (engine->cmdThrottle( data ) == true) return 1;
				return 2;
			case 18:
				if (engine->cmdPowerOff() == true) return 1;
				return 2;
			case 19:
				break;
		}

		return 0;
	}

	int EIU::RequestPrimaryData( VDT_32* ptrPrimaryData )
	{
		memcpy( ptrPrimaryData, PrimaryData, sizeof(VDT_32) );
		return 0;
	}

	int EIU::RequestSecondaryData( VDT_6* ptrSecondaryData )
	{
		memcpy( ptrSecondaryData, SecondaryData, sizeof(VDT_6) );
		return 0;
	}


	void EIU::OnPostStep( double fSimT, double fDeltaT, double fMJD )
	{
		engine->dataGetPrimaryData( PrimaryData );
		engine->dataGetSecondaryData( SecondaryData );
		return;
	}
}