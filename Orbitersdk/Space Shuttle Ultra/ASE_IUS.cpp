#include "ASE_IUS.h"


ASE_IUS::ASE_IUS( AtlantisSubsystemDirector* _director, bool AftLocation ):AtlantisSubsystem( _director, "ASE_IUS" )
{
	PyroBusPri = false;
	PyroBusAlt = false;
	IUSDeploymentEnaPri = false;
	IUSDeploymentEnaAlt = false;
	TiltTableActuatorMotionPri1Lower = false;
	TiltTableActuatorMotionPri1Raise = false;
	TiltTableActuatorMotionAlt2Lower = false;
	TiltTableActuatorMotionAlt2Raise = false;

	hIUSattach = NULL;

	asTiltTable.Set( AnimState::STOPPED, ASE_IUS_TILT_TABLE_POS_0 );// 0� position
	oldposition = ASE_IUS_TILT_TABLE_POS_0;

	firststep = true;

	// TODO "use" attachment 7 (aft active keel)

	if (AftLocation == true)
	{
		ASEoffset = ASE_IUS_OFFSET_AFT_LOCATION;
		IUSattachoffset = IUS_ATTACHMENT_OFFSET_AFT_LOCATION;
		// uses bridge rails: 10/12/13
	}
	else
	{
		ASEoffset = ASE_IUS_OFFSET_FORWARD_LOCATION;
		IUSattachoffset = IUS_ATTACHMENT_OFFSET_FORWARD_LOCATION;
		// uses bridge rails: 9/11/12
	}

	hMesh = oapiLoadMeshGlobal( ASE_IUS_MESHNAME );
	return;
}

ASE_IUS::~ASE_IUS()
{
	return;
}

void ASE_IUS::Realize()
{
	DiscreteBundle* pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_G", 16 );
	pTiltTableActuatorDriveEnablePri1Intermediate.Connect( pBundle, 12 );
	pTiltTableActuatorDriveEnablePri1Maximum.Connect( pBundle, 13 );
	pTiltTableActuatorDriveEnableAlt2Intermediate.Connect( pBundle, 14 );
	pTiltTableActuatorDriveEnableAlt2Maximum.Connect( pBundle, 15 );

	pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_H", 16 );
	pTiltTableActuatorMotionPri1Lower.Connect( pBundle, 0 );
	pTiltTableActuatorMotionPri1Raise.Connect( pBundle, 1 );
	pTiltTableActuatorMotionAlt2Lower.Connect( pBundle, 2 );
	pTiltTableActuatorMotionAlt2Raise.Connect( pBundle, 3 );
	pTiltTableActuatorMotionPri1TB.Connect( pBundle, 4 );
	pTiltTableActuatorMotionAlt2TB.Connect( pBundle, 5 );
	pTiltTableActuatorPositionPri1TB.Connect( pBundle, 6 );
	pTiltTableActuatorPositionAlt2TB.Connect( pBundle, 7 );
	// tb
	// tb
	//pTiltTableActuatorAltDrAct1->ConnectPort( 1, pBundle, 10 );

	pPyroBusPriOff.Connect( pBundle, 13 );
	pPyroBusPriOn.Connect( pBundle, 14 );
	pPyroBusPriTB.Connect( pBundle, 15 );

	pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_I", 16 );
	pPyroBusAltOff.Connect( pBundle, 0 );
	pPyroBusAltOn.Connect( pBundle, 1 );
	pPyroBusAltTB.Connect( pBundle, 2 );

	pIUSDeploymentEnaPriOff.Connect( pBundle, 13 );
	pIUSDeploymentEnaPriEnable.Connect( pBundle, 14 );
	pIUSDeploymentEnaPriTB.Connect( pBundle, 15 );

	pBundle = STS()->BundleManager()->CreateBundle( "L10toASE_J", 16 );
	pIUSDeploymentEnaAltOff.Connect( pBundle, 0 );
	pIUSDeploymentEnaAltEnable.Connect( pBundle, 1 );
	pIUSDeploymentEnaAltTB.Connect( pBundle, 2 );
	pIUSDeploymentDpyPriDeploy.Connect( pBundle, 3 );
	pIUSDeploymentDpyAltDeploy.Connect( pBundle, 4 );

	DefineAnimations();
	return;
}

void ASE_IUS::OnPreStep( double SimT, double DeltaT, double MJD )
{
	if (firststep)// set initial animation/attachment (part 1)
	{
		if ((IsIUSAttached()) && (asTiltTable.pos < ASE_IUS_TILT_TABLE_POS_0))
		{
			asTiltTable.pos = ASE_IUS_TILT_TABLE_POS_0;
			oldposition = asTiltTable.pos;
		}
		STS()->SetAnimation( animTiltTable, asTiltTable.pos );
	}

	// panel inputs
	PyroBusPri = pPyroBusPriOn.IsSet() | (PyroBusPri & !pPyroBusPriOff.IsSet());
	PyroBusAlt = pPyroBusAltOn.IsSet() | (PyroBusAlt & !pPyroBusAltOff.IsSet());
	IUSDeploymentEnaPri = (pIUSDeploymentEnaPriEnable.IsSet() | (IUSDeploymentEnaPri & !pIUSDeploymentEnaPriOff.IsSet())) & PyroBusPri;
	IUSDeploymentEnaAlt = (pIUSDeploymentEnaAltEnable.IsSet() | (IUSDeploymentEnaAlt & !pIUSDeploymentEnaAltOff.IsSet())) & PyroBusAlt;

	TiltTableActuatorMotionPri1Lower = (pTiltTableActuatorMotionPri1Lower.IsSet() | TiltTableActuatorMotionPri1Lower) & (pTiltTableActuatorDriveEnablePri1Maximum.IsSet() | pTiltTableActuatorDriveEnablePri1Intermediate.IsSet());
	TiltTableActuatorMotionPri1Raise = (pTiltTableActuatorMotionPri1Raise.IsSet() | TiltTableActuatorMotionPri1Raise) & (pTiltTableActuatorDriveEnablePri1Maximum.IsSet() | pTiltTableActuatorDriveEnablePri1Intermediate.IsSet());
	TiltTableActuatorMotionAlt2Lower = (pTiltTableActuatorMotionAlt2Lower.IsSet() | TiltTableActuatorMotionAlt2Lower) & (pTiltTableActuatorDriveEnableAlt2Maximum.IsSet() | pTiltTableActuatorDriveEnableAlt2Intermediate.IsSet());
	TiltTableActuatorMotionAlt2Raise = (pTiltTableActuatorMotionAlt2Raise.IsSet() | TiltTableActuatorMotionAlt2Raise) & (pTiltTableActuatorDriveEnableAlt2Maximum.IsSet() | pTiltTableActuatorDriveEnableAlt2Intermediate.IsSet());


	// move tilt table
	double da = DeltaT * ASE_IUS_TILT_TABLE_SPEED * (
		(int)(TiltTableActuatorMotionPri1Raise | TiltTableActuatorMotionAlt2Raise) - 
		(int)(TiltTableActuatorMotionPri1Lower | TiltTableActuatorMotionAlt2Lower));

	if (da > 0) // raise
	{
		asTiltTable.action = AnimState::OPENING;
		asTiltTable.Move( da );
		RunAnimation();
	}
	else if (da < 0)// lower
	{
		da = -da;
		asTiltTable.action = AnimState::CLOSING;
		if ((IsIUSAttached() == true) && ((asTiltTable.pos - da) < ASE_IUS_TILT_TABLE_POS_0)) da = asTiltTable.pos - ASE_IUS_TILT_TABLE_POS_0;// limit motion if IUS still attached
		asTiltTable.Move( da );
		RunAnimation();
	}
	else asTiltTable.action = AnimState::STOPPED;// stop
	
	// release umbilicals
	// TODO

	// deploy IUS
	if ((pIUSDeploymentDpyPriDeploy.IsSet() & IUSDeploymentEnaPri) | (pIUSDeploymentDpyAltDeploy.IsSet() & IUSDeploymentEnaAlt))
	{
		// deploy ius
		STS()->DetachChild( hIUSattach, IUS_JETTISON_VELOCITY );
	}


	// check for actuator stop
	if (pTiltTableActuatorDriveEnablePri1Intermediate.IsSet())
	{
		if ((((asTiltTable.pos >= ASE_IUS_TILT_TABLE_POS_28) && (oldposition < ASE_IUS_TILT_TABLE_POS_28)) || 
			((asTiltTable.pos >= ASE_IUS_TILT_TABLE_POS_58) && (oldposition < ASE_IUS_TILT_TABLE_POS_58))) && 
			(TiltTableActuatorMotionPri1Raise)) TiltTableActuatorMotionPri1Raise = false;
		if ((oldposition >= ASE_IUS_TILT_TABLE_POS_28) && (asTiltTable.pos < ASE_IUS_TILT_TABLE_POS_28) && (TiltTableActuatorMotionPri1Lower))
			TiltTableActuatorMotionPri1Lower = false;
	}
	if (pTiltTableActuatorDriveEnableAlt2Intermediate.IsSet())
	{
		if ((asTiltTable.pos >= ASE_IUS_TILT_TABLE_POS_30) && (oldposition < ASE_IUS_TILT_TABLE_POS_30) && (TiltTableActuatorMotionAlt2Raise))
			TiltTableActuatorMotionAlt2Raise = false;
		if ((oldposition >= ASE_IUS_TILT_TABLE_POS_30) && (asTiltTable.pos < ASE_IUS_TILT_TABLE_POS_30) && (TiltTableActuatorMotionAlt2Lower))
			TiltTableActuatorMotionAlt2Lower = false;
	}
	if ((asTiltTable.pos == ASE_IUS_TILT_TABLE_POS_06) || (asTiltTable.pos == ASE_IUS_TILT_TABLE_POS_61))
	{
		TiltTableActuatorMotionPri1Lower = false;
		TiltTableActuatorMotionPri1Raise = false;
		TiltTableActuatorMotionAlt2Lower = false;
		TiltTableActuatorMotionAlt2Raise = false;
	}
	oldposition = asTiltTable.pos;


	// panel outputs
	pPyroBusPriTB.SetLine( (int)PyroBusPri * 5.0f );
	pPyroBusAltTB.SetLine( (int)PyroBusAlt * 5.0f );

	pIUSDeploymentEnaPriTB.SetLine( (int)IUSDeploymentEnaPri * 5.0f );
	pIUSDeploymentEnaAltTB.SetLine( (int)IUSDeploymentEnaAlt * 5.0f );

	pTiltTableActuatorMotionPri1TB.SetLine( (int)(TiltTableActuatorMotionPri1Lower | TiltTableActuatorMotionPri1Raise) * 5.0f );
	pTiltTableActuatorMotionAlt2TB.SetLine( (int)(TiltTableActuatorMotionAlt2Lower | TiltTableActuatorMotionAlt2Raise) * 5.0f );

	pTiltTableActuatorPositionPri1TB.SetLine( (int)(Eq( asTiltTable.pos, ASE_IUS_TILT_TABLE_POS_0, 0.001 ) | Eq( asTiltTable.pos, ASE_IUS_TILT_TABLE_POS_265, ASE_IUS_TILT_TABLE_DP ) | Eq( asTiltTable.pos, ASE_IUS_TILT_TABLE_POS_57, ASE_IUS_TILT_TABLE_DP )) * 5.0f );
	pTiltTableActuatorPositionAlt2TB.SetLine( (int)(Eq( asTiltTable.pos, ASE_IUS_TILT_TABLE_POS_0, 0.001 ) | Eq( asTiltTable.pos, ASE_IUS_TILT_TABLE_POS_295, ASE_IUS_TILT_TABLE_DP ) | Eq( asTiltTable.pos, ASE_IUS_TILT_TABLE_POS_595, ASE_IUS_TILT_TABLE_DP )) * 5.0f );
	return;
}

void ASE_IUS::OnPostStep( double SimT, double DeltaT, double MJD )
{
	if (firststep)// set initial animation/attachment (part 2)
	{
		STS()->SetAttachmentParams( hIUSattach, IUSattachpoints[0] + STS()->GetOrbiterCoGOffset(), IUSattachpoints[1] - IUSattachpoints[0], IUSattachpoints[2] - IUSattachpoints[0] );
		firststep = false;
	}
	return;
}

bool ASE_IUS::OnParseLine( const char* line )
{
	if (!_strnicmp( line, "TILT_TABLE", 10 ))
	{
		sscan_state( (char*)(line + 10), asTiltTable );
		oldposition = asTiltTable.pos;
		return true;
	}
	else return false;
}

void ASE_IUS::OnSaveState( FILEHANDLE scn ) const
{
	WriteScenario_state( scn, "TILT_TABLE", asTiltTable );
	return;
}

double ASE_IUS::GetSubsystemEmptyMass() const
{
	return ASE_IUS_MASS;
}

void ASE_IUS::AddMesh()
{
	VECTOR3 ofs = STS()->GetOrbiterCoGOffset() + ASEoffset;
	mesh_index = STS()->AddMesh( hMesh, &ofs );
	STS()->SetMeshVisibilityMode( mesh_index, MESHVIS_EXTERNAL | MESHVIS_VC | MESHVIS_EXTPASS );
	return;
}

void ASE_IUS::DefineAnimations()
{
	static UINT TiltTable[11] = {
		GRP_AFT_ASE_TILT_FRAME_ASE, 
		GRP_IUS_FRAME_TUBE_ASE, 
		GRP_POWER_CONTROL_UNIT_ASE, 
		GRP_BATTERY_1_ASE, 
		GRP_BATTERY_2_ASE, 
		GRP_BATTERY_3_ASE, 
		GRP_SPACECRAFT_CONVERTER_REGULATOR_UNIT_ASE, 
		GRP_IUS_CONVERTER_REGULATOR_UNIT_ASE, 
		GRP_ASE_CONVERTER_REGULATOR_UNIT_ASE, 
		GRP_ASE_ACTUATOR_CONTROLLER_A_ASE, 
		GRP_ASE_ACTUATOR_CONTROLLER_B_ASE
	};
	static MGROUP_ROTATE TiltTable_Rotate = MGROUP_ROTATE( mesh_index, TiltTable, 11, _V( 0, 0.3985, -1.3304 ), _V( -1, 0, 0 ), (float)(67.0 * RAD) );
	animTiltTable = STS()->CreateAnimation( ASE_IUS_TILT_TABLE_POS_0 );// 0� position
	STS()->AddAnimationComponent( animTiltTable, 0, 1, &TiltTable_Rotate );

	static MGROUP_ROTATE IUSattachment_Rotate( LOCALVERTEXLIST, MAKEGROUPARRAY( IUSattachpoints ), 3, _V( 0, 0.3985, -1.3304 ) + ASEoffset, _V( -1, 0, 0 ), (float)(67.0 * RAD) );
	STS()->AddAnimationComponent( animTiltTable, 0, 1, &IUSattachment_Rotate );
	return;
}

void ASE_IUS::CreateAttachment()
{
	if (hIUSattach == NULL)
	{
		IUSattachpoints[0] = STS()->GetOrbiterCoGOffset() + IUSattachoffset;
		IUSattachpoints[1] = IUSattachpoints[0] + _V( 0, 0, 1 );
		IUSattachpoints[2] = IUSattachpoints[0] + _V( 0, 1, 0 );
		hIUSattach = STS()->CreateAttachment( false, IUSattachpoints[0], _V( 0, 0, 1 ), _V( 0, 1, 0 ), "SSU_ASE" );
	}
	return;
}

bool ASE_IUS::IsIUSAttached()
{
	return (STS()->GetAttachmentStatus( hIUSattach ) != NULL);
}

void ASE_IUS::RunAnimation()
{
	STS()->SetAnimation( animTiltTable, asTiltTable.pos );
	STS()->SetAttachmentParams( hIUSattach, IUSattachpoints[0] + STS()->GetOrbiterCoGOffset(), IUSattachpoints[1] - IUSattachpoints[0], IUSattachpoints[2] - IUSattachpoints[0] );
	return;
}