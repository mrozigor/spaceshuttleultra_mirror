#include "PanelA8.h"
#include "PlBayOp.h"
#include "resource.h"
//#include "meshres.h"
#include "meshres_vc.h"
#include "meshres_vc_additions.h"
#include "DlgCtrl.h"
#include <stdio.h>
//#include "MasterTimingUnit.h"

extern GDIParams g_Param;
extern HELPCONTEXT g_hc;
extern char *ActionString[5];

// ==============================================================

PanelA8::PanelA8(Atlantis *_sts): sts(_sts)
{
	int i;
	for(i=0;i<20;i++) {
		anim_VC_A8[i]=NULL;
		switch_state[i]=1;
		tkbk_state[i]=0;
	}
}

void PanelA8::RegisterVC()
{
	//sprintf_s(oapiDebugString(), 255, "Registering panelA8");
	VECTOR3 ofs=sts->orbiter_ofs;
	SURFHANDLE panela8t_tex = oapiGetTextureHandle (sts->hOrbiterVCMesh, TEX_A8TOP_VC);
	SURFHANDLE panela8b_tex = oapiGetTextureHandle (sts->hOrbiterVCMesh, TEX_A8BOTTOM_VC);

	oapiVCRegisterArea(AID_A8, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN | PANEL_MOUSE_LBUP);
	//oapiVCSetAreaClickmode_Quadrilateral (AID_A8, _V(-0.274, 2.848, 12.567)+ofs, _V(-0.813, 2.848, 12.567)+ofs, _V(-0.277, 2.055, 12.816)+ofs, _V(-0.819, 2.055, 12.816)+ofs);
	//oapiVCSetAreaClickmode_Quadrilateral (AID_A8, _V(-0.813, 2.848, 12.567)+ofs, _V(-0.274, 2.848, 12.567)+ofs, _V(-0.813, 2.3, 12.74)+ofs, _V(-0.274, 2.3, 12.74)+ofs);
	oapiVCSetAreaClickmode_Quadrilateral (AID_A8, _V(-0.797, 2.892, 12.279)+ofs, _V(-0.266, 2.892, 12.279)+ofs, _V(-0.797, 2.119, 12.522)+ofs, _V(-0.266, 2.119, 12.522)+ofs);
	
	oapiVCRegisterArea(AID_A8_TKBK1, _R(895, 900, 927, 918), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8b_tex);
	oapiVCRegisterArea(AID_A8_TKBK3, _R(895, 774, 927, 792), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8b_tex);
	oapiVCRegisterArea(AID_A8_TKBK5, _R(895, 647, 927, 665), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8b_tex);
	oapiVCRegisterArea(AID_A8_TKBK6, _R(806, 650, 838, 668), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8b_tex);
	oapiVCRegisterArea(AID_A8_TKBK7, _R(717, 648, 749, 666), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8b_tex);
	oapiVCRegisterArea(AID_A8_TKBK9, _R(914, 334, 946, 352), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8t_tex);
	oapiVCRegisterArea(AID_A8_TKBK10, _R(914, 400, 946, 418), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8t_tex);
	oapiVCRegisterArea(AID_A8_TKBK11, _R(901, 931, 933, 949), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8t_tex);
	oapiVCRegisterArea(AID_A8_TKBK14, _R(868, 334, 900, 352), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8t_tex);
	oapiVCRegisterArea(AID_A8_TKBK15, _R(868, 400, 900, 418), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8t_tex);
	oapiVCRegisterArea(AID_A8_TKBK16, _R(819, 334, 851, 352), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8t_tex);
	oapiVCRegisterArea(AID_A8_TKBK17, _R(819, 400, 851, 418), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8t_tex);
	//oapiVCRegisterArea(AID_A8_TKBK7, _R(614, 617, 646, 635), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, panela8b_tex);
}

bool PanelA8::VCRedrawEvent (int id, int event, SURFHANDLE surf)
{
	switch(id) {
		case AID_A8_TKBK1:
			/*if(sts->Eq(sts->arm_sy, 0.5) && sts->Eq(sts->arm_sp, sts->shoulder_neutral))
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);*/
			if(sts->MRL_FwdMicroswitches[0][2]==1)
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			//sprintf(oapiDebugString(), "AID_A8_TKBK1: %d", tkbk_state[id-AID_A8_TKBK1]);
			break;
		case AID_A8_TKBK3:
			/*if(sts->Eq(sts->arm_sy, 0.5) && sts->Eq(sts->arm_sp, sts->shoulder_neutral) && sts->Eq(sts->arm_ep, sts->elbow_neutral))
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);*/
			if(sts->MRL_MidMicroswitches[0][2]==1)
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK5:
			/*if(sts->ArmCradled()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);*/
			if(sts->MRL_AftMicroswitches[0][2]==1)
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK6:
			if(sts->MRL[0]==0.0) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 10);
			else if(sts->MRL[0]==1.0) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 2);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK7:
			/*if(sts->RMSRollout.action==AnimState::OPEN)
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 9);
			else if(sts->RMSRollout.Moving()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			else if(sts->RMSRollout.action==AnimState::CLOSED)
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 1);*/
			if(sts->MPM_Microswitches[0][0]==1) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 1);
			else if(sts->MPM_Microswitches[0][1]==1) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 9);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK9:
			//if(sts->Extend.Closed()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			//else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 9);
			if(sts->GetAttachmentStatus(sts->rms_attach)) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK10:
			if(sts->Extend.Open()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK11:
			if(sts->shoulder_brace==0.0 && switch_state[SWITCH12]==0)
				return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK14:
			if(sts->Grapple.Closed()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK15:
			if(sts->Grapple.Open()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK16:
			if(sts->Rigidize.Closed()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
		case AID_A8_TKBK17:
			if(sts->Rigidize.Open()) return VCDrawTalkback(surf, id-AID_A8_TKBK1, 8);
			else return VCDrawTalkback(surf, id-AID_A8_TKBK1, 0);
			break;
	}
	return false;
}

bool PanelA8::VCDrawTalkback(SURFHANDLE surf, int idx, int label)
{
	if (tkbk_state[idx] == label) return false; // nothing to do
	//sprintf(oapiDebugString(), "Panel A8 Talkback: %d %d %d", idx, label, tkbk_state[idx]);
	tkbk_state[idx] = label;
	//if(label<=1) oapiBlt (surf, g_Param.tkbk_label, 0, 0, 0, label*18, 32, 18);
	//else oapiBlt (surf, g_Param.tkbk_label, 0, 0, (label-1)*32, 0, 32, 18);
	//oapiBlt(surf, g_Param.tkbk_label, 0, 0, 0, 0, 32, 18);
	if(label<8) oapiBlt (surf, g_Param.tkbk_label, 0, 0, label*32, 0, 32, 18);
	else oapiBlt (surf, g_Param.tkbk_label, 0, 0, (label-8)*32, 18, 32, 18);
	return true;
}

void PanelA8::DefineVCAnimations(UINT vcidx)
{
	static VECTOR3 switch_rot_vert=_V(1.0, 0.0, 0.0);
	static VECTOR3 switch_rot_horz=_V(0.0, 0.793, -0.249);

	static UINT VC_A8b5_GRP = GRP_A8b5_VC;
	static MGROUP_ROTATE VC_A8b5 (vcidx, &VC_A8b5_GRP, 1,
		_V(-0.693, 2.233, 12.486), switch_rot_vert, (float)(90.0*RAD));
	anim_VC_A8[SWITCH5]=sts->CreateAnimation(0.5);
	sts->AddAnimationComponent(anim_VC_A8[SWITCH5], 0, 1, &VC_A8b5);
	
	static UINT VC_A8b6_GRP = GRP_A8b6_VC;
	static MGROUP_ROTATE VC_A8b6 (vcidx, &VC_A8b6_GRP, 1,
		_V(-0.647, 2.238, 12.486), switch_rot_vert, (float)(90.0*RAD));
	anim_VC_A8[SWITCH6]=sts->CreateAnimation(0.5);
	sts->AddAnimationComponent(anim_VC_A8[SWITCH6], 0, 1, &VC_A8b6);

	static UINT VC_A8b9_GRP = GRP_A8b9_VC;
	static MGROUP_ROTATE VC_A8b9 (vcidx, &VC_A8b9_GRP, 1,
		_V(-0.693, 2.233, 12.486), switch_rot_vert, (float)(90.0*RAD));
	anim_VC_A8[SWITCH9]=sts->CreateAnimation(0.5);
	sts->AddAnimationComponent(anim_VC_A8[SWITCH9], 0, 1, &VC_A8b9);

	static UINT VC_A8b10_GRP = GRP_A8b10_VC;
	static MGROUP_ROTATE VC_A8b10 (vcidx, &VC_A8b10_GRP, 1,
		_V(-0.687, 2.402, 12.434), switch_rot_horz, (float)(90.0*RAD));
	anim_VC_A8[SWITCH10]=sts->CreateAnimation(0.5);
	sts->AddAnimationComponent(anim_VC_A8[SWITCH10], 0, 1, &VC_A8b10);

	static UINT VC_A8b12_GRP = GRP_A8b12_VC;
	static MGROUP_ROTATE VC_A8b12 (vcidx, &VC_A8b12_GRP, 1,
		_V(-0.537, 2.294, 12.467), switch_rot_horz, (float)(90.0*RAD));
	anim_VC_A8[SWITCH12]=sts->CreateAnimation(0.5);
	sts->AddAnimationComponent(anim_VC_A8[SWITCH12], 0, 1, &VC_A8b12);

	//MAN CONTR
	static UINT VC_A8b16_GRP = GRP_A8b16_VC;
	static MGROUP_ROTATE VC_A8b16 (vcidx, &VC_A8b16_GRP, 1,
		_V(-0.654, 2.709, 12.337), switch_rot_vert, (float)(90.0*RAD));
	anim_VC_A8[SWITCH16]=sts->CreateAnimation(0.5);
	sts->AddAnimationComponent(anim_VC_A8[SWITCH16], 0, 1, &VC_A8b16);

	//MODE
	static UINT VC_A8b17_GRP = GRP_A8b17_VC;
	static MGROUP_ROTATE VC_A8b17 (vcidx, &VC_A8b17_GRP, 1,
		_V(-0.625, 2.709, 12.337), switch_rot_vert, (float)(90.0*RAD));
	anim_VC_A8[SWITCH17]=sts->CreateAnimation(0.5);
	sts->AddAnimationComponent(anim_VC_A8[SWITCH17], 0, 1, &VC_A8b17);
}

void PanelA8::UpdateVC()
{
	//if(!sts->RMS) return;
	sts->SetAnimation(anim_VC_A8[SWITCH5], switch_state[SWITCH5]/2.0);
	sts->SetAnimation(anim_VC_A8[SWITCH6], switch_state[SWITCH6]/2.0);
	sts->SetAnimation(anim_VC_A8[SWITCH9], switch_state[SWITCH9]/2.0);
	sts->SetAnimation(anim_VC_A8[SWITCH10], switch_state[SWITCH10]/2.0);
	sts->SetAnimation(anim_VC_A8[SWITCH12], switch_state[SWITCH12]/2.0);
	sts->SetAnimation(anim_VC_A8[SWITCH16], switch_state[SWITCH16]/2.0);
	sts->SetAnimation(anim_VC_A8[SWITCH17], switch_state[SWITCH17]/2.0);
	
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK1);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK3);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK5);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK6);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK7);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK9);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK10);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK11);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK14);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK15);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK16);
	oapiVCTriggerRedrawArea(-1, AID_A8_TKBK17);
}

bool PanelA8::VCMouseEvent(int id, int event, VECTOR3 &p)
{
	bool action = false;
	sprintf_s(oapiDebugString(), 255, "Panel A8 event: %f %f %f %f", p.x, p.y, p.z);
	/*if(event & PANEL_MOUSE_LBPRESSED) sprintf(oapiDebugString(), "LBPressed");
	else if(event == PANEL_MOUSE_LBUP) sprintf(oapiDebugString(), "LBUp");
	else if(event & PANEL_MOUSE_LBDOWN) sprintf(oapiDebugString(), "LBDown");*/

	if(event == PANEL_MOUSE_LBDOWN) {
		if(p.x>=0.167373 && p.x<=0.217567) {
			if(p.y>=0.841234 && p.y<=0.867132) {
				if(p.y<0.854145) {
					if(switch_state[SWITCH5]>0) switch_state[SWITCH5]--;
				}
				else {
					if(switch_state[SWITCH5]<2) switch_state[SWITCH5]++;
				}
				action=true;
			}
		}

		if(p.x>=0.252639 && p.x<=0.305916) {
			if(p.y>=0.828852 && p.y<=0.863428) {
				if(p.y<0.848199) {
					//sprintf(oapiDebugString(), "Deploying PORT MPMs");
					if(switch_state[SWITCH6]>0) switch_state[SWITCH6]--;
				}
				else {
					//sprintf(oapiDebugString(), "Stowing PORT MPMs");
					if(switch_state[SWITCH6]<2) switch_state[SWITCH6]++;
				}
				if(switch_state[SWITCH6]==0) {
					if(sts->RMSRollout.action!=AnimState::OPEN) {
						sts->RMSRollout.action=AnimState::OPENING;
					}
				}
				else if(switch_state[SWITCH6]==1) {
					if(sts->RMSRollout.Moving()) sts->RMSRollout.action=AnimState::STOPPED;
				}
				else {
					if(sts->RMSRollout.action!=AnimState::CLOSED) {
						sts->RMSRollout.action=AnimState::CLOSING;
					}
				}
				/*if(RMSRollout.action==AnimState::CLOSED) {
					RMSRollout.action=AnimState::OPENING;
				}
				else {
					RMSRollout.action=AnimState::CLOSING;
				}*/
				action=true;
			}
		}

		if(p.x>=0.841143 && p.x<=0.886384) {
			if(p.y>=0.829965 && p.y<=0.867186) {
				if(p.y<0.848995) {
					//sprintf(oapiDebugString(), "Deploying STBD MPMs");
					if(switch_state[SWITCH9]>0) switch_state[SWITCH9]--;
				}
				else {
					//sprintf(oapiDebugString(), "Stowing STBD MPMs");
					if(switch_state[SWITCH9]<2) switch_state[SWITCH9]++;
				}
				action=true;
			}
		}

		if(p.x>=0.170449 && p.x<=0.226497) {
			if(p.y>=0.618925 && p.y<=0.651137) {
				if(p.x<0.200508) {
					if(switch_state[SWITCH10]>0) switch_state[SWITCH10]--;
				}
				else {
					if(switch_state[SWITCH10]<2) switch_state[SWITCH10]++;
				}
				sprintf_s(oapiDebugString(), 255, "%d", switch_state[SWITCH10]);
				action=true;
			}
		}

		if(p.x>=0.466754 && p.x<=0.510409) {
			if(p.y>=0.757090 && p.y<=0.788049) {
				if(p.x<0.486494) {
					if(switch_state[SWITCH12]>0) switch_state[SWITCH12]--;
				}
				else {
					if(switch_state[SWITCH12]<2) switch_state[SWITCH12]++;
				}
				action=true;
			}
		}

		if(p.x>=0.243867 && p.x<=0.288102) {
			if(p.y>=0.22259 && p.y<=0.252219) {
				if(p.y<0.2374045) {
					if(switch_state[SWITCH16]>0) switch_state[SWITCH16]--;
					//sprintf_s(oapiDebugString(), 255, "SWITCH16");
				}
				else {
					if(switch_state[SWITCH16]<2) switch_state[SWITCH16]++;
				}
				action=true;
			}
		}

		if(p.x>=0.298233 && p.x<=0.346051) {
			if(p.y>=0.2227635 && p.y<=0.250502) {
				if(p.y<0.23663275) {
					if(switch_state[SWITCH17]>0) switch_state[SWITCH17]--;
					//sprintf_s(oapiDebugString(), 255, "SWITCH16");
				}
				else {
					if(switch_state[SWITCH17]<2) switch_state[SWITCH17]++;
				}
				if(switch_state[SWITCH17]==1) {
					sts->EEGrappleMode=0;
					//stop grapple/release sequences
					if(sts->bGrappleInProgress) sts->AutoGrappleSequence();
					else if(sts->bReleaseInProgress) sts->AutoReleaseSequence();
				}
				else if(switch_state[SWITCH17]==2) sts->EEGrappleMode=1;
				else sts->EEGrappleMode=2;
				action=true;
			}
		}
	}

	else { //reset spring-loaded switches
		if(p.x>=0.170449 && p.x<=0.226497) {
			if(p.y>=0.618925 && p.y<=0.651137) {
				switch_state[SWITCH10]=1;
				action=true;
			}
		}

		if(p.x>=0.243867 && p.x<=0.288102) {
			if(p.y>=0.22259 && p.y<=0.252219) {
				switch_state[SWITCH16]=1;
				action=true;
			}
		}
	}

	if(action) {
		UpdateVC();
		return true;
	}
	return false;
}

void PanelA8::Step(double t, double dt)
{
	//if(!sts->RMS) return;
	if(switch_state[SWITCH5]==0 && sts->ArmCradled() && sts->plop->MechPwr[1]==PayloadBayOp::MP_ON) {
		double da = dt*SHOULDER_BRACE_SPEED;
		sts->MRL[0]=max(0.0, sts->MRL[0]-da);
		sts->UpdateMRLMicroswitches();
		UpdateVC();
	}
	else if(switch_state[SWITCH5]==2 && sts->ArmCradled() && sts->plop->MechPwr[1]==PayloadBayOp::MP_ON) {
		double da = dt*SHOULDER_BRACE_SPEED;
		sts->MRL[0]=min(1.0, sts->MRL[0]+da);
		sts->UpdateMRLMicroswitches();
		UpdateVC();
	}

	if(switch_state[SWITCH10]==0) {
		double da = dt*SHOULDER_BRACE_SPEED;
		sts->shoulder_brace=max(0.0, sts->shoulder_brace-da);
		UpdateVC();
	}
	return;
}

bool PanelA8::ParseScenarioLine(char *line)
{
	if(!_strnicmp(line, "STBD_RMS", 8)) {
		sscanf_s(line+8, "%d", &switch_state[SWITCH6]);
		/*if(switch_state[SWITCH6]==0 && sts->RMSRollout.action!=AnimState::OPEN) {
			sts->RMSRollout.action=AnimState::OPENING;
		}
		else if(switch_state[SWITCH6]==1 && sts->RMSRollout.Moving()) {
			sts->RMSRollout.action=AnimState::STOPPED;
		}
		else if(sts->RMSRollout.action!=AnimState::CLOSED) {
			sts->RMSRollout.action=AnimState::CLOSING;
		}*/
	}
	else if(!_strnicmp(line, "EE MODE", 7)) {
		sscanf_s(line+7, "%d", &switch_state[SWITCH17]);
		if(switch_state[SWITCH17]==1) sts->EEGrappleMode=0;
		else if(switch_state[SWITCH17]==2) sts->EEGrappleMode=1;
		else sts->EEGrappleMode=2;
	}
	/*else if(!strnicmp(line, "SHOULDER_BRACE_RELEASE", 22)) {
		sscanf(line+22, "%d", &switch_state[SWITCH10]);
	}*/
	return false;
}

void PanelA8::SaveState(FILEHANDLE scn)
{
	oapiWriteScenario_int(scn, "STBD_RMS", switch_state[SWITCH6]);
	oapiWriteScenario_int(scn, "EE MODE", switch_state[SWITCH17]);
	//oapiWriteScenario_int(scn, "SHOULDER_BRACE_RELEASE", switch_state[SWITCH10]);
	return;
}
