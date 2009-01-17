#include "PanelF4.h"
#include "../meshres_vc_additions.h"

extern GDIParams g_Param;

namespace vc
{
	PanelF4::PanelF4(Atlantis* _sts)
		: BasicPanel(_sts, "F4")
	{
		Add(pSbdbkThrot = new PushButtonIndicator(_sts, "F4_SBDTHROT_AUTO"));
		Add(pSbdbkThrotMan = new StandardLight(_sts, "F4_SBDKTHROT_MAN"));
		Add(pBodyFlap = new PushButtonIndicator(_sts, "F4_BODYFLAP_AUTO"));
		Add(pBodyFlapMan = new StandardLight(_sts, "F4_BODYFLAP_MAN"));
	}

	PanelF4::~PanelF4()
	{
	}

	void PanelF4::Realize()
	{
		BasicPanel::Realize();

		DiscreteBundle* pBundle=STS()->BundleManager()->CreateBundle("SBDBKTHROT_CONTROLS", 16);
		pSbdbkThrot->ConnectAll(pBundle, 0); //AUTO light; common to F2 and F4 PBIs
		pSbdbkThrotMan->input.Connect(pBundle, 2); //MAN light; F4 PBI only
		pSbdbkThrotMan->test.Connect(pBundle, 2); //MAN light; F4 PBI only

		pBundle=STS()->BundleManager()->CreateBundle("BODYFLAP_CONTROLS", 16);
		pBodyFlap->ConnectAll(pBundle, 0); //AUTO light; common to F2 and F4 PBIs
		pBodyFlapMan->input.Connect(pBundle, 1); //MAN light; common to F2 and F4 PBIs
		pBodyFlapMan->test.Connect(pBundle, 1); //MAN light; common to F2 and F4 PBIs
	}

	void PanelF4::DefineVC()
	{
		AddAIDToMouseEventList(AID_F4);

		pSbdbkThrot->AddAIDToRedrawEventList(AID_F4_ST_AUTO);
		pSbdbkThrot->SetSourceImage(g_Param.pbi_lights);
		pSbdbkThrot->SetBase(0, 0);
		pSbdbkThrot->SetSourceCoords(true, 0, 0);
		pSbdbkThrot->SetSourceCoords(false, 0, 14);
		pSbdbkThrot->SetDimensions(42, 14);
		pSbdbkThrot->SetMouseRegion(0.823518f, 0.583791f, 0.867013f, 0.697191f);
		pSbdbkThrot->AllowReset(true);

		pSbdbkThrotMan->AddAIDToRedrawEventList(AID_F4_ST_MAN);
		pSbdbkThrotMan->SetSourceImage(g_Param.pbi_lights);
		pSbdbkThrotMan->SetBase(0, 0);
		pSbdbkThrotMan->SetSourceCoords(true, 0, 0);
		pSbdbkThrotMan->SetSourceCoords(false, 0, 14);
		pSbdbkThrotMan->SetDimensions(42, 14);

		pBodyFlap->AddAIDToRedrawEventList(AID_F4_BF_AUTO);
		pBodyFlap->SetSourceImage(g_Param.pbi_lights);
		pBodyFlap->SetBase(0, 0);
		pBodyFlap->SetSourceCoords(true, 0, 0);
		pBodyFlap->SetSourceCoords(false, 0, 14);
		pBodyFlap->SetDimensions(42, 14);
		pBodyFlap->SetMouseRegion(0.872915f, 0.660717f, 0.916913f, 0.770096f);
		pBodyFlap->AllowReset(true);

		pBodyFlapMan->AddAIDToRedrawEventList(AID_F4_BF_MAN);
		pBodyFlapMan->SetSourceImage(g_Param.pbi_lights);
		pBodyFlapMan->SetBase(0, 0);
		pBodyFlapMan->SetSourceCoords(true, 0, 0);
		pBodyFlapMan->SetSourceCoords(false, 0, 14);
		pBodyFlapMan->SetDimensions(42, 14);
	}

	void PanelF4::RegisterVC()
	{
		BasicPanel::RegisterVC();

		SURFHANDLE tex=oapiGetTextureHandle(STS()->hOrbiterVCMesh, TEX_FPANELS_VC);

		VECTOR3 ofs=STS()->orbiter_ofs;

		oapiVCRegisterArea(AID_F4, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP);
		oapiVCSetAreaClickmode_Quadrilateral(AID_F4,
			_V(0.38, 2.535, 14.612)+ofs, _V(1.147, 2.535, 14.612)+ofs,
			_V(0.38, 2.25, 14.533)+ofs, _V(1.147, 2.25, 14.533)+ofs);

		oapiVCRegisterArea(AID_F4_ST_AUTO, _R(1296, 548, 1338, 562), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, tex);
		oapiVCRegisterArea(AID_F4_ST_MAN, _R(1296, 585, 1338, 599), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, tex);
		oapiVCRegisterArea(AID_F4_BF_AUTO, _R(1436, 542, 1478, 556), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, tex);
		oapiVCRegisterArea(AID_F4_BF_MAN, _R(1437, 583, 1479, 597), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, tex);
	}
};