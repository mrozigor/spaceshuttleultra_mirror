#include "PanelA7A8ODS.h"
#include "../Atlantis.h"
#include "../meshres_odsvc.h"

namespace vc {

	PanelA7A8ODS::PanelA7A8ODS(Atlantis* _sts)
		: BasicPanel(_sts, "A7A3/A8A3")
	{
		Add(pSystemPowerMNA		= new StdSwitch3(_sts, "SYSTEM POWER MNA"));
		Add(pSystemPowerMNB		= new StdSwitch3(_sts, "SYSTEM POWER MNB"));
		Add(pPyroPowerMNA		= new StdSwitch2(_sts, "PYRO POWER MNA"));
		Add(pPyroPowerMNC		= new StdSwitch2(_sts, "PYRO POWER MNC"));
		Add(pSys1VentIsol		= new StdSwitch3(_sts, "SYS1 VENT ISOL"));
		Add(pSys1Vent			= new StdSwitch3(_sts, "SYS1 VENT"));
		Add(pSys2VentIsol		= new StdSwitch3(_sts, "SYS2 VENT ISOL"));
		Add(pSys2Vent			= new StdSwitch3(_sts, "SYS2 VENT"));
		Add(pPSUPowerMNA		= new StdSwitch2(_sts, "PSU POWER MNA"));
		Add(pPSUPowerMNB		= new StdSwitch2(_sts, "PSU POWER MNB"));
		Add(pLightsAirlock14	= new StdSwitch2(_sts, "LIGHTS AIRLOCK 1-4"));
		Add(pLightsAirlock23	= new StdSwitch2(_sts, "LIGHTS AIRLOCK 2-3"));
		Add(pLightsDockingFWD	= new StdSwitch2(_sts, "LIGHTS DOCKING TRUSS FWD"));
		Add(pLightsDockingAFT	= new StdSwitch2(_sts, "LIGHTS DOCKING TRUSS AFT"));
		Add(pARLKTNLFanA		= new StdSwitch2(_sts, "ARLK/TNL FAN A"));
		Add(pARLKTNLFanB		= new StdSwitch2(_sts, "ARLK/TNL FAN B"));
		Add(pLightsCLVestPORT	= new StdSwitch2(_sts, "LIGHTS C/L VESTIBULE PORT"));
		Add(pLightsCLVestSTBD	= new StdSwitch2(_sts, "LIGHTS C/L VESTIBULE STBD"));


		Add(pControlPanelPowerA = new StdSwitch2(_sts, "CNTL PNL PWR A"));
		Add(pControlPanelPowerB = new StdSwitch2(_sts, "CNTL PNL PWR B"));
		Add(pControlPanelPowerC = new StdSwitch2(_sts, "CNTL PNL PWR C"));
		Add(pHeatersDCUPowerH1 = new StdSwitch2(_sts, "HTRS/DCU PWR H1"));
		Add(pHeatersDCUPowerH2 = new StdSwitch2(_sts, "HTRS/DCU PWR H2/DCU"));
		Add(pHeatersDCUPowerH3 = new StdSwitch2(_sts, "HTRS/DCU PWR H3/DCU"));
		Add(pAPDSPowerA = new StdSwitch2(_sts, "APDS PWR A"));
		Add(pAPDSPowerB = new StdSwitch2(_sts, "APDS PWR B"));
		Add(pAPDSPowerC = new StdSwitch2(_sts, "APDS PWR C"));
		
		
		Add(pPyrosAp			= new StdSwitch2(_sts, "PYROS Ap"));
		Add(pPyrosBp			= new StdSwitch2(_sts, "PYROS Bp"));
		Add(pPyrosCp			= new StdSwitch2(_sts, "PYROS Cp"));

		pControlPanelPowerA->SetLabel(0, "OFF");
		pControlPanelPowerA->SetLabel(1, "ON");
		
		pControlPanelPowerB->SetLabel(0, "OFF");
		pControlPanelPowerB->SetLabel(1, "ON");

		pControlPanelPowerC->SetLabel(0, "OFF");
		pControlPanelPowerC->SetLabel(1, "ON");


		pHeatersDCUPowerH1->SetLabel(0, "OFF");
		pHeatersDCUPowerH1->SetLabel(1, "ON");
		pHeatersDCUPowerH2->SetLabel(0, "OFF");
		pHeatersDCUPowerH2->SetLabel(1, "ON");
		pHeatersDCUPowerH3->SetLabel(0, "OFF");
		pHeatersDCUPowerH3->SetLabel(1, "ON");

		pAPDSPowerA->SetLabel(0, "OFF");
		pAPDSPowerA->SetLabel(1, "ON");
		pAPDSPowerB->SetLabel(0, "OFF");
		pAPDSPowerB->SetLabel(1, "ON");
		pAPDSPowerC->SetLabel(0, "OFF");
		pAPDSPowerC->SetLabel(1, "ON");
	}

	PanelA7A8ODS::~PanelA7A8ODS()
	{
	}

	void PanelA7A8ODS::AddMeshes(const VECTOR3& ofs)
	{
		SetHasOwnVCMesh();
		midx_odspanel = STS()->AddMesh(ODSPANEL_MESHNAME, &ofs);
		STS()->SetMeshVisibilityMode(midx_odspanel, MESHVIS_VC);
	}

	UINT PanelA7A8ODS::GetVCMeshIndex() const
	{
		return midx_odspanel;
	}

	void PanelA7A8ODS::Realize()
	{	
		//Define switch connections
		BasicPanel::Realize();
	}

	void PanelA7A8ODS::DefineVC()
	{
		oapiWriteLog("Panel A7/A8:\tDefine VC");
		//Define VC regions
		AddAIDToMouseEventList(AID_A7A3);
		AddAIDToMouseEventList(AID_A8A3);
		//first is A7A3, second region A8A3. 

		//Panel A8A3
		//-0.265916, 2.5048, 12.399
		//0.254716, 2.12746, 12.5175
		//register mouse event regions in BasicPanel

		//0.262413  2.443722  12.41595

		pControlPanelPowerA->SetMouseRegion(0.081f, 0.124f, 0.094f, 0.197f);
		pControlPanelPowerA->SetReference(_V(0.0, 2.443722, 12.41595),
			_V(-1.0, 0.0, 0.0));
		pControlPanelPowerA->DefineSwitchGroup(GRP_A8A3S1_ODSVC);

		pControlPanelPowerB->SetMouseRegion(0.177f, 0.124f, 0.194f, 0.197f);
		pControlPanelPowerB->SetReference(_V(0.0, 2.443722, 12.41595), 
			_V(-1.0, 0.0, 0.0));
		pControlPanelPowerB->DefineSwitchGroup(GRP_A8A3S2_ODSVC);

		pControlPanelPowerC->SetMouseRegion(0.274f, 0.124f, 0.286f, 0.197f);
		pControlPanelPowerC->SetReference(_V(0.0, 2.443722, 12.41595), 
			_V(-1.0, 0.0, 0.0));
		pControlPanelPowerC->DefineSwitchGroup(GRP_A8A3S3_ODSVC);

		pHeatersDCUPowerH1->SetMouseRegion(0.076f, 0.337f, 0.095f, 0.379f);
		pHeatersDCUPowerH1->SetReference(_V(0.0, 2.370605, 12.43914), 
			_V(-1.0, 0.0, 0.0));
		pHeatersDCUPowerH1->DefineSwitchGroup(GRP_A8A3S4_ODSVC);

		pHeatersDCUPowerH2->SetMouseRegion(0.176f, 0.337f, 0.195f, 0.379f);
		pHeatersDCUPowerH2->SetReference(_V(0.0, 2.370605, 12.43914),
			_V(-1.0, 0.0, 0.0));
		pHeatersDCUPowerH2->DefineSwitchGroup(GRP_A8A3S5_ODSVC);

		pHeatersDCUPowerH3->SetMouseRegion(0.273f, 0.337f, 0.290f, 0.379f);
		pHeatersDCUPowerH3->SetReference(_V(0.0, 2.370605, 12.43914), 
			_V(-1.0, 0.0, 0.0));
		pHeatersDCUPowerH3->DefineSwitchGroup(GRP_A8A3S6_ODSVC);

		pAPDSPowerA->SetMouseRegion(0.076f, 0.519f, 0.095f, 0.590f);
		pAPDSPowerA->SetReference(_V(0.0,  2.297854, 12.46215), _V(-1.0, 0.0, 0.0));
		pAPDSPowerA->DefineSwitchGroup(GRP_A8A3S7_ODSVC);

		pAPDSPowerB->SetMouseRegion(0.176f, 0.519f, 0.195f, 0.590f);
		pAPDSPowerB->SetReference(_V(0.0,  2.297854, 12.46215), _V(-1.0, 0.0, 0.0));
		pAPDSPowerB->DefineSwitchGroup(GRP_A8A3S8_ODSVC);

		pAPDSPowerC->SetMouseRegion(0.273f, 0.519f, 0.290f, 0.590f);
		pAPDSPowerC->SetReference(_V(0.0,  2.297854, 12.46215), _V(-1.0, 0.0, 0.0));
		pAPDSPowerC->DefineSwitchGroup(GRP_A8A3S9_ODSVC);
		
		
		pPyrosAp->SetMouseRegion(0.709f, 0.124f, 0.725f, 0.197f);
		pPyrosAp->SetReference(_V(0.0, 2.443722, 12.41595),
			_V(-1.0, 0.0, 0.0));
		pPyrosAp->DefineSwitchGroup(GRP_A8A3S10_ODSVC);

		pPyrosBp->SetMouseRegion(0.803f, 0.124f, 0.825f, 0.197f);
		pPyrosBp->SetReference(_V(0.0, 2.443722, 12.41595), 
			_V(-1.0, 0.0, 0.0));
		pPyrosBp->DefineSwitchGroup(GRP_A8A3S11_ODSVC);

		pPyrosCp->SetMouseRegion(0.902f, 0.124f, 0.920f, 0.197f);
		pPyrosCp->SetReference(_V(0.0, 2.443722, 12.41595),
			_V(-1.0, 0.0, 0.0));
		pPyrosCp->DefineSwitchGroup(GRP_A8A3S12_ODSVC);

	}

	void PanelA7A8ODS::RegisterVC()
	{
		BasicPanel::RegisterVC();

		VECTOR3 ofs = STS()->orbiter_ofs;
		oapiVCRegisterArea(AID_A8A3, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP);
		oapiVCSetAreaClickmode_Quadrilateral (AID_A8A3, 
			_V(0.254716, 2.5048, 12.399)+ofs, _V(-0.265916, 2.5048, 12.399)+ofs,
			_V(0.254716, 2.12746, 12.5175)+ofs, _V(-0.265916, 2.12746, 12.5175) + ofs);
	}

	void PanelA7A8ODS::DefineVCAnimations(UINT vc_idx)
	{
		oapiWriteLog("PANEL A7/A8:\tDefine VC Animations");
		BasicPanel::DefineVCAnimations(midx_odspanel);
	}
		
};