#include "CrawlerCenterPanel.h"
#include "Crawler.h"
#include "meshres_crawler_vc.h"

namespace vc
{

CrawlerCenterPanel::CrawlerCenterPanel(Crawler* _v, const std::string& _ident, CRAWLER_CAB _cab)
: CrawlerPanel(_v, _ident, _cab)
{
	Add(pSpeedGauge = new CrawlerBarGauge(_v, "SpeedGauge", false));
	Add(pSpeedDisplay = new CrawlerDigitalDisplay(_v, "SpeedDisplay"));
}

CrawlerCenterPanel::~CrawlerCenterPanel()
{
	for(vector<MGROUP_TRANSFORM*>::const_iterator i=vpAnimations.begin(); i!=vpAnimations.end();++i)
		delete (*i);
}

void CrawlerCenterPanel::RegisterVC()
{
	CrawlerPanel::RegisterVC();
	
	int aid_ofs;
	if(cabID==FWD) aid_ofs = 0;
	else  aid_ofs = AID_REAR_OFFSET;
	
	SURFHANDLE gauges_tex = oapiGetTextureHandle(V()->GetVCMesh(cabID), 2);
	oapiVCRegisterArea(AID_SPEED_BAR+aid_ofs, _R(50, 769, 532, 797), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
	oapiVCRegisterArea(AID_SPEED_VALUE+aid_ofs, _R(52, 707, 200, 749), PANEL_REDRAW_USER, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, gauges_tex);
}

void CrawlerCenterPanel::DefineVC()
{	
	int aid_ofs;
	if(cabID==FWD) aid_ofs = 0;
	else  aid_ofs = AID_REAR_OFFSET;

	pSpeedGauge->AddAIDToRedrawEventList(AID_SPEED_BAR+aid_ofs);
	pSpeedGauge->SetRange(-2.0, 2.0);
	pSpeedGauge->SetBaseCoords(0, 0);
	pSpeedGauge->SetDimensions(482, 28, 37);
	if(cabID==REAR) pSpeedGauge->SetScaleValue(-1.0);

	pSpeedDisplay->AddAIDToRedrawEventList(AID_SPEED_VALUE+aid_ofs);
	pSpeedDisplay->SetBaseCoords(0, 0);
	pSpeedDisplay->SetDimensions(148, 42, 4);
	if(cabID==REAR) pSpeedDisplay->SetScaleValue(-1.0);
}

void CrawlerCenterPanel::DefineVCAnimations(UINT vcidx)
{	
	static UINT SteeringWheel[2] = {GRP_GROUP_31_VC, GRP_GROUP_8_VC};
	MGROUP_ROTATE *pSteeringWheel = new MGROUP_ROTATE(vcidx, SteeringWheel, 2, TransformVector(_V(0.0, 0.043, -0.158)),
		TransformVector(_V(0, -0.50104, -0.86543)), (float)(180.0*RAD));
	anim_steering = V()->CreateAnimation(0.5);
	V()->AddAnimationComponent(anim_steering, 0.0, 1.0, pSteeringWheel);
	vpAnimations.push_back(pSteeringWheel);
}

void CrawlerCenterPanel::Realize()
{
	// connect disc ports
	DiscreteBundle* pBundle = V()->BundleManager()->CreateBundle("CRAWLER_STEERING", 7);
	steering.Connect(pBundle, cabID);

	pBundle = V()->BundleManager()->CreateBundle("CRAWLER_ENGINE", 16);
	pSpeedGauge->ConnectPort(pBundle, 0);
	pSpeedDisplay->ConnectPort(pBundle, 0);

	CrawlerPanel::Realize();
}

void CrawlerCenterPanel::OnPreStep(double SimT, double SimDT, double MJD)
{
	CrawlerPanel::OnPreStep(SimT, SimDT, MJD);

	double steeringAnim = steering.GetVoltage()/2.0 + 0.5;
	V()->SetAnimation(anim_steering, steeringAnim);
}

};