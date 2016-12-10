// ======================================================
// Created by ssumeshc 0.2
// Date of conversion : Sat Dec 10 14:36:21 2016

// Input file: Orbiter.msh
// ======================================================

#pragma once

const unsigned int NUMGRP = 148;

const unsigned int GRP_LEFT_MLG_DOOR	=	0;	//LEFT_MLG_DOOR
const unsigned int GRP_RIGHT_MLG_DOOR	=	1;	//RIGHT_MLG_DOOR
const unsigned int GRP_LEFT_PLBD_EXT	=	2;	//LEFT_PLBD_EXT
const unsigned int GRP_RIGHT_OMSPOD	=	3;	//RIGHT_OMSpod
const unsigned int GRP_LEFT_OMSPOD	=	4;	//LEFT_OMSpod
const unsigned int GRP_XO576_BULKHEAD_	=	5;	//Xo576_BULKHEAD 
const unsigned int GRP_STBDOMS_BASE_TILES	=	6;	//STBDOMS_base_tiles
const unsigned int GRP_XO576_BULKHEAD_DOCKING_LIGHT	=	7;	//Xo576_BULKHEAD_DOCKING_LIGHT
const unsigned int GRP_XO576_BULKHEAD_LIGHT	=	8;	//Xo576_BULKHEAD_LIGHT
const unsigned int GRP_TAIL_CHUTE	=	9;	//TAIL_CHUTE
const unsigned int GRP_TAIL_NO_CHUTE	=	10;	//TAIL_NO_CHUTE
const unsigned int GRP_XSTARTRACKER_IMAGE	=	11;	//Xstartracker_image
const unsigned int GRP_ZSTARTRACKER_IMAGE	=	12;	//Zstartracker_image
const unsigned int GRP_STARTRACKER_INDENT	=	13;	//startracker_indent
const unsigned int GRP_ZSTARTRACKER_DOOR	=	14;	//Zstartracker_door
const unsigned int GRP_XSTARTRACKER_DOOR	=	15;	//Xstartracker_door
const unsigned int GRP_RIGHT_ARCS_JETS	=	16;	//RIGHT_ARCS_JETS
const unsigned int GRP_LEFT_ARCS_JETS	=	17;	//LEFT_ARCS_JETS
const unsigned int GRP_MIDBODYT0_UMBILICAL_CAVITIES	=	18;	//MIDBODYT0_UMBILICAL_CAVITIES
const unsigned int GRP_BAY13_TRANSPARENCY	=	19;	//BAY13_TRANSPARENCY
const unsigned int GRP_WINDOWS	=	20;	//WINDOWS
const unsigned int GRP_PLB_VENTS	=	21;	//PLB_VENTS
const unsigned int GRP_STBD_FWD_RADIATOR_COOLANT_LINES	=	22;	//STBD_FWD_RADIATOR_COOLANT_LINES
const unsigned int GRP_CENTER_SSME	=	23;	//CENTER_SSME
const unsigned int GRP_PLB_TCS	=	24;	//PLB_TCS
const unsigned int GRP_STBDDOOR_PULL	=	25;	//STBDdoor_pull
const unsigned int GRP_STBD_CLAMP	=	26;	//STBD_clamp
const unsigned int GRP_STBDPUSH_ROD	=	27;	//STBDpush_rod
const unsigned int GRP_PORTPUSH_ROD	=	28;	//PORTpush_rod
const unsigned int GRP_PORT_CLAMP	=	29;	//PORT_clamp
const unsigned int GRP_PORTDOOR_PULL	=	30;	//PORTdoor_pull
const unsigned int GRP_AFT_EVA_WINCH_HOOK	=	31;	//AFT_EVA_WINCH_HOOK
const unsigned int GRP_PLB_LIGHTS	=	32;	//PLB_LIGHTS
const unsigned int GRP_PLB_SILL_LONGERONS	=	33;	//PLB_SILL_LONGERONS
const unsigned int GRP_PLB_RING_FRAMES	=	34;	//PLB_RING_FRAMES
const unsigned int GRP_PORT_FWD_RADIATOR_COOLANT_LINES	=	35;	//PORT_FWD_RADIATOR_COOLANT_LINES
const unsigned int GRP_PANTILT_CAM_A	=	36;	//PANTILT_CAM_A
const unsigned int GRP_CAM_B	=	37;	//CAM_B
const unsigned int GRP_PANTILT_CAM_B	=	38;	//PANTILT_CAM_B
const unsigned int GRP_CAM_C	=	39;	//CAM_C
const unsigned int GRP_PANTILT_CAM_C	=	40;	//PANTILT_CAM_C
const unsigned int GRP_CAM_D	=	41;	//CAM_D
const unsigned int GRP_PANTILT_CAM_D	=	42;	//PANTILT_CAM_D
const unsigned int GRP_AFT_EVA_WINCH_HANDLE	=	43;	//AFT_EVA_WINCH_HANDLE
const unsigned int GRP_FWD_EVA_WINCH_HOOK	=	44;	//FWD_EVA_WINCH_HOOK
const unsigned int GRP_FWD_EVA_WINCH_HANDLE	=	45;	//FWD_EVA_WINCH_HANDLE
const unsigned int GRP_EVA_THERMAL_COVER	=	46;	//EVA_THERMAL_COVER
const unsigned int GRP_NLG_UPPER_TORQUE_ARM	=	47;	//NLG_UPPER_TORQUE_ARM
const unsigned int GRP_NLG_LOWER_TORQUE_ARM	=	48;	//NLG_LOWER_TORQUE_ARM
const unsigned int GRP_NLG_STRUT	=	49;	//NLG_STRUT
const unsigned int GRP_NLG_SHOCK_STRUT	=	50;	//NLG_SHOCK_STRUT
const unsigned int GRP_NOSE_WHEELS	=	51;	//NOSE_WHEELS
const unsigned int GRP_LEFT_MN_WHEELS	=	52;	//LEFT_MN_WHEELS
const unsigned int GRP_LEFT_MLG_STRUT	=	53;	//LEFT_MLG_STRUT
const unsigned int GRP_LEFT_MLG_SHOCK_STRUT	=	54;	//LEFT_MLG_SHOCK_STRUT
const unsigned int GRP_RIGHT_MN_WHEELS	=	55;	//RIGHT_MN_WHEELS
const unsigned int GRP_RIGHT_MLG_STRUT	=	56;	//RIGHT_MLG_STRUT
const unsigned int GRP_RIGHT_MLG_SHOCK_STRUT	=	57;	//RIGHT_MLG_SHOCK_STRUT
const unsigned int GRP_PROBEL	=	58;	//PROBEL
const unsigned int GRP_PROBER	=	59;	//PROBER
const unsigned int GRP_SSME_HEATSHIELDS	=	60;	//SSME_HEATSHIELDS
const unsigned int GRP_ET_DOOR_LEFT	=	61;	//ET_DOOR_LEFT
const unsigned int GRP_ET_DOOR_LEFT_DDM_ARM_AFT	=	62;	//ET_DOOR_LEFT_DDM_ARM_AFT
const unsigned int GRP_ET_DOOR_LEFT_DDM_ARM_FWD	=	63;	//ET_DOOR_LEFT_DDM_ARM_FWD
const unsigned int GRP_ET_DOOR_LEFT_DDM_LINK_ROD_AFT	=	64;	//ET_DOOR_LEFT_DDM_LINK_ROD_AFT
const unsigned int GRP_ET_DOOR_LEFT_DDM_LINK_ROD_FWD	=	65;	//ET_DOOR_LEFT_DDM_LINK_ROD_FWD
const unsigned int GRP_ET_DOOR_RIGHT_DDM_LINK_ROD_FWD	=	66;	//ET_DOOR_RIGHT_DDM_LINK_ROD_FWD
const unsigned int GRP_ET_DOOR_RIGHT_DDM_LINK_ROD_AFT	=	67;	//ET_DOOR_RIGHT_DDM_LINK_ROD_AFT
const unsigned int GRP_ET_DOOR_RIGHT_DDM_ARM_FWD	=	68;	//ET_DOOR_RIGHT_DDM_ARM_FWD
const unsigned int GRP_ET_DOOR_RIGHT_DDM_ARM_AFT	=	69;	//ET_DOOR_RIGHT_DDM_ARM_AFT
const unsigned int GRP_ET_DOOR_RIGHT	=	70;	//ET_DOOR_RIGHT
const unsigned int GRP_BAYPFR	=	71;	//BayPFR
const unsigned int GRP_BAY1_LONGERON	=	72;	//Bay1_longeron
const unsigned int GRP_BAY2_LONGERON	=	73;	//Bay2_longeron
const unsigned int GRP_BAY3_LONGERON	=	74;	//Bay3_longeron
const unsigned int GRP_BAY4_LONGERON	=	75;	//Bay4_longeron
const unsigned int GRP_BAY5_LONGERON	=	76;	//Bay5_longeron
const unsigned int GRP_BAY6_LONGERON	=	77;	//Bay6_longeron
const unsigned int GRP_BAY7_LONGERON	=	78;	//Bay7_longeron
const unsigned int GRP_BAY8_LONGERON	=	79;	//Bay8_longeron
const unsigned int GRP_BAY9_LONGERON	=	80;	//Bay9_longeron
const unsigned int GRP_BAY10_LONGERON	=	81;	//Bay10_longeron
const unsigned int GRP_BAY11_LONGERON	=	82;	//Bay11_longeron
const unsigned int GRP_BAY12_LONGERON	=	83;	//Bay12_longeron
const unsigned int GRP_BAY13_LONGERON	=	84;	//Bay13_longeron
const unsigned int GRP_CAM_A	=	85;	//CAM_A
const unsigned int GRP_PLB_WIRE_TRAY	=	86;	//PLB_WIRE_TRAY
const unsigned int GRP_XO1307_BULKHEAD	=	87;	//Xo1307_BULKHEAD
const unsigned int GRP_LOME	=	88;	//LOME
const unsigned int GRP_RIGHT_SSME	=	89;	//RIGHT_SSME
const unsigned int GRP_LEFT_SSME	=	90;	//LEFT_SSME
const unsigned int GRP_ROME	=	91;	//ROME
const unsigned int GRP_PLB_BAY13_COVERS	=	92;	//PLB_BAY13_COVERS
const unsigned int GRP_AFT_HOOKS	=	93;	//AFT_HOOKS
const unsigned int GRP_MID_AFT_HOOKS	=	94;	//MID_AFT_HOOKS
const unsigned int GRP_MID_FWD_HOOKS	=	95;	//MID_FWD_HOOKS
const unsigned int GRP_FWD_HOOKS	=	96;	//FWD_HOOKS
const unsigned int GRP_PORT_PLB_RADIATOR_3	=	97;	//PORT_PLB_RADIATOR_3
const unsigned int GRP_PORT_PLB_RADIATOR_2	=	98;	//PORT_PLB_RADIATOR_2
const unsigned int GRP_PORT_PLB_RADIATOR_1	=	99;	//PORT_PLB_RADIATOR_1
const unsigned int GRP_PORT_PLB_RADIATOR_4	=	100;	//PORT_PLB_RADIATOR_4
const unsigned int GRP_STBD_PLB_RADIATOR_4	=	101;	//STBD_PLB_RADIATOR_4
const unsigned int GRP_STBD_PLB_RADIATOR_3	=	102;	//STBD_PLB_RADIATOR_3
const unsigned int GRP_STBD_PLB_RADIATOR_2	=	103;	//STBD_PLB_RADIATOR_2
const unsigned int GRP_STBD_PLB_RADIATOR_1	=	104;	//STBD_PLB_RADIATOR_1
const unsigned int GRP_PORT_PLBD_INTERIOR	=	105;	//PORT_PLBD_INTERIOR
const unsigned int GRP_STBD_PLBD_INTERIOR	=	106;	//STBD_PLBD_INTERIOR
const unsigned int GRP_FRCS_MODULE	=	107;	//FRCS_MODULE
const unsigned int GRP_WING_RCC	=	108;	//Wing_RCC
const unsigned int GRP_HATCH	=	109;	//hatch
const unsigned int GRP_LEFT_NLG_DOOR	=	110;	//LEFT_NLG_DOOR
const unsigned int GRP_RIGHT_NLG_DOOR	=	111;	//RIGHT_NLG_DOOR
const unsigned int GRP_WINGTOPS	=	112;	//Wingtops
const unsigned int GRP_T0_UMBILICAL_PANELS	=	113;	//T0_UMBILICAL_PANELS
const unsigned int GRP_BODYFLAP	=	114;	//BODYFLAP
const unsigned int GRP_RIGHT_PLBD_EXT	=	115;	//RIGHT_PLBD_EXT
const unsigned int GRP_RIGHT_RSB_PANEL	=	116;	//RIGHT_RSB_PANEL
const unsigned int GRP_LEFT_RSB_PANEL	=	117;	//LEFT_RSB_PANEL
const unsigned int GRP_LEFT_INBOARD_ELEVON_SEAL_PANEL	=	118;	//LEFT_INBOARD_ELEVON_SEAL_PANEL
const unsigned int GRP_LEFT_OUTBOARD_ELEVON_SEAL_PANEL	=	119;	//LEFT_OUTBOARD_ELEVON_SEAL_PANEL
const unsigned int GRP_RIGHT_OUTBOARD_ELEVON_SEAL_PANEL	=	120;	//RIGHT_OUTBOARD_ELEVON_SEAL_PANEL
const unsigned int GRP_RIGHT_INBOARD_ELEVON_SEAL_PANEL	=	121;	//RIGHT_INBOARD_ELEVON_SEAL_PANEL
const unsigned int GRP_LEFT_OUTBOARD_ELEVON	=	122;	//LEFT_OUTBOARD_ELEVON
const unsigned int GRP_LEFT_INBOARD_ELEVON	=	123;	//LEFT_INBOARD_ELEVON
const unsigned int GRP_RIGHT_OUTBOARD_ELEVON	=	124;	//RIGHT_OUTBOARD_ELEVON
const unsigned int GRP_ELEVON_HINGE_BLOCKS	=	125;	//ELEVON_HINGE_BLOCKS
const unsigned int GRP_RIGHT_INBOARD_ELEVON	=	126;	//RIGHT_INBOARD_ELEVON
const unsigned int GRP_STARBOARD_AFT_AVS_DOOR_9	=	127;	//STARBOARD_AFT_AVS_DOOR_9
const unsigned int GRP_STARBOARD_AFT_AVS_DOOR_8	=	128;	//STARBOARD_AFT_AVS_DOOR_8
const unsigned int GRP_PORT_AFT_AVS_DOOR_8	=	129;	//PORT_AFT_AVS_DOOR_8
const unsigned int GRP_PORT_AFT_AVS_DOOR_9	=	130;	//PORT_AFT_AVS_DOOR_9
const unsigned int GRP_PORT_MIDBODY_AVS_DOOR_6	=	131;	//PORT_MIDBODY_AVS_DOOR_6
const unsigned int GRP_PORT_MIDBODY_AVS_DOOR_3	=	132;	//PORT_MIDBODY_AVS_DOOR_3
const unsigned int GRP_PORT_MIDBODY_AVS_DOOR_7	=	133;	//PORT_MIDBODY_AVS_DOOR_7
const unsigned int GRP_PORT_MIDBODY_AVS_DOOR_4	=	134;	//PORT_MIDBODY_AVS_DOOR_4
const unsigned int GRP_PORT_MIDBODY_AVS_DOOR_5	=	135;	//PORT_MIDBODY_AVS_DOOR_5
const unsigned int GRP_STARBOARD_MIDBODY_AVS_DOOR_5	=	136;	//STARBOARD_MIDBODY_AVS_DOOR_5
const unsigned int GRP_STARBOARD_MIDBODY_AVS_DOOR_4	=	137;	//STARBOARD_MIDBODY_AVS_DOOR_4
const unsigned int GRP_STARBOARD_MIDBODY_AVS_DOOR_7	=	138;	//STARBOARD_MIDBODY_AVS_DOOR_7
const unsigned int GRP_STARBOARD_MIDBODY_AVS_DOOR_3	=	139;	//STARBOARD_MIDBODY_AVS_DOOR_3
const unsigned int GRP_STARBOARD_MIDBODY_AVS_DOOR_6	=	140;	//STARBOARD_MIDBODY_AVS_DOOR_6
const unsigned int GRP_PLB_SILL_EQUIPMENT	=	141;	//PLB_SILL_EQUIPMENT
const unsigned int GRP_XO576_BULKHEAD_EQUIPMENT	=	142;	//Xo576_BULKHEAD_EQUIPMENT
const unsigned int GRP_TRANSPARENT	=	143;	//transparent
const unsigned int GRP_FUSELAGE	=	144;	//FUSELAGE
const unsigned int GRP_PORTOMS_BASE_TILES	=	145;	//PORTOMS_base_tiles
const unsigned int GRP_RIGHT_ARCS_POD	=	146;	//RIGHT_ARCS_POD
const unsigned int GRP_LEFT_ARCS_POD	=	147;	//LEFT_ARCS_POD

