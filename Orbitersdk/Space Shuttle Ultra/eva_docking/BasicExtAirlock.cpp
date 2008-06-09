#include "BasicExtAirlock.h"

namespace eva_docking {

	BasicExternalAirlock::BasicExternalAirlock(SubsystemDirector* pdirect, const string& _ident)
		: AtlantisSubsystem(pdirect, _ident)
	{
	}

	BasicExternalAirlock::~BasicExternalAirlock() {
	}

	void BasicExternalAirlock::AddMeshes(const VECTOR3& ofs) {
	}

	void BasicExternalAirlock::Realize() {
	}

	double BasicExternalAirlock::GetSubsystemEmptyMass() const {
		return 0.0;
	}
	void BasicExternalAirlock::OnPreStep(double fSimT, double fDeltaT, double fMJD) {
	}
	
	void BasicExternalAirlock::OnPostStep(double fSimT, double fDeltaT, double fMJD) {
	}
	
	void BasicExternalAirlock::OnPropagate(double fSimT, double fDeltaT, double fMJD) {
	}
	
	void BasicExternalAirlock::OnPlaybackEvent(double fSimT, double fEventT, const char* event_t, const char* event) {
	}
	
	bool BasicExternalAirlock::OnParseLine(const char* line) {
		return false;
	}

	void BasicExternalAirlock::OnSaveState(FILEHANDLE scn) const {
	}

	void BasicExternalAirlock::OnDumpToLog() const {

	}

};