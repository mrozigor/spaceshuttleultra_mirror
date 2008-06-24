#include "EIU.h"


namespace mps
{
	EIU::EIU( SubsystemDirector* _director, const string& _ident, int nID, SSME* ptr ):AtlantisSubsystem( _director, _ident )
	{
		ID = nID;
		engine = ptr;
		BUFFER_SSME_DATA_TABLE = new DATA_TABLE;
		RequestDATA( BUFFER_SSME_DATA_TABLE );
		return;
	}

	EIU::~EIU( void )
	{
		delete BUFFER_SSME_DATA_TABLE;
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
				break;
			case 8:
				break;
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
				break;
			case 13:
				if (engine->cmdOxidizerDump() == true) return 1;
				return 2;
			case 14:
				break;
			case 15:
				break;
			case 16:
				break;
			case 17:
				if (engine->cmdThrottle( data ) == true) return 1;
				return 2;
			case 18:
				break;
		}

		return 0;
	}

	int EIU::RequestDATA( DATA_TABLE* ptrDataTable )
	{
		memcpy( ptrDataTable, BUFFER_SSME_DATA_TABLE, sizeof(DATA_TABLE) );
		return 0;
	}


	void EIU::OnPostStep( double fSimT, double fDeltaT, double fMJD )
	{
		engine->dataDataTable( BUFFER_SSME_DATA_TABLE );
		return;
	}
}