/****************************************************************************
  This file is part of Space Shuttle Ultra

  Multi-Function Display Unit  definition



  Space Shuttle Ultra is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Ultra is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Ultra; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See http://spaceshuttleultra.sourceforge.net/license/ for more details.

  **************************************************************************/
#pragma once

#include <vector>
#include "../dps/dps_defs.h"
#include "vc_defs.h"
#include "AtlantisVCComponent.h"
#include <UltraMath.h>
#include "gcAPI.h"
#include "Sketchpad2.h"


#define CR_BLACK RGB( 0, 0, 0 )//RGB( 0, 0, 25 )
#define CR_DARK_GRAY RGB( 60, 60, 80 )
#define CR_LIGHT_GRAY RGB( 180, 180, 200 )
#define CR_WHITE RGB( 255, 255, 255 )
//#define CR_ORANGE RGB( 255, 128, 0 )
#define CR_RED RGB( 255, 0, 0 )
#define CR_YELLOW RGB( 255, 255, 0 )
#define CR_CYAN RGB( 0, 255, 255 )
#define CR_MAGENTA RGB( 255, 0, 255 )
#define CR_LIGHT_GREEN RGB( 0, 255, 0 )
#define CR_DARK_GREEN RGB( 0, 160, 0 )
#define CR_BLUE RGB( 0, 0, 255 )
//#define CR_PINK RGB( 220, 150, 220 )
//#define CR_BROWN RGB( 190, 50, 30 )

#define CR_DPS_NORMAL RGB( 128, 255, 0 )
#define CR_DPS_OVERBRIGHT RGB( 255, 255, 0 )


namespace vc {


	class MDU: public AtlantisVCComponent
	{	
		double t0;
		bool counting;

		// MEDS pens and brushes
		HBRUSH gdiBlackBrush;
		HBRUSH gdiDarkGrayBrush;
		HBRUSH gdiLightGrayBrush;
		HBRUSH gdiWhiteBrush;
		HBRUSH gdiRedBrush;
		HBRUSH gdiYellowBrush;
		HBRUSH gdiMagentaBrush;
		HBRUSH gdiLightGreenBrush;

		oapi::Brush* skpBlackBrush;
		oapi::Brush* skpDarkGrayBrush;
		oapi::Brush* skpLightGrayBrush;
		oapi::Brush* skpWhiteBrush;
		oapi::Brush* skpRedBrush;
		oapi::Brush* skpYellowBrush;
		oapi::Brush* skpCyanBrush;
		oapi::Brush* skpMagentaBrush;
		oapi::Brush* skpLightGreenBrush;
		oapi::Brush* skpBlueBrush;
		
		HPEN gdiBlackPen;
		HPEN gdiDarkGrayPen;
		HPEN gdiDarkGrayThickPen;
		HPEN gdiLightGrayPen;
		HPEN gdiWhitePen;
		HPEN gdiRedPen;
		HPEN gdiYellowPen;
		HPEN gdiCyanPen;
		HPEN gdiMagentaPen;
		HPEN gdiLightGreenPen;
		HPEN gdiLightGreenThickPen;

		oapi::Pen* skpBlackPen;
		oapi::Pen* skpDarkGrayPen;
		oapi::Pen* skpDarkGrayThickPen;
		oapi::Pen* skpLightGrayPen;
		oapi::Pen* skpWhitePen;
		oapi::Pen* skpRedPen;
		oapi::Pen* skpYellowPen;
		oapi::Pen* skpCyanPen;
		oapi::Pen* skpMagentaPen;
		oapi::Pen* skpLightGreenPen;
		oapi::Pen* skpDarkGreenPen;
		oapi::Pen* skpLightGreenThickPen;

		// DPS pens
		HPEN gdiOverbrightPen;
		HPEN gdiNormalPen;
		HPEN gdiDashedNormalPen;

		oapi::Pen* skpOverbrightPen;
		oapi::Pen* skpNormalPen;
		oapi::Pen* skpDashedNormalPen;

		// fonts
		HFONT gdiTahomaFont_h10w4;
		HFONT gdiTahomaFont_h7w3;
		HFONT gdiTahomaFont_h17w6;

		oapi::Font* skpTahomaFont_h10w4;
		oapi::Font* skpTahomaFont_h7w3;
		oapi::Font* skpTahomaFont_h17w6;
		oapi::Font* skpArialFont_h15w5;
		oapi::Font* skpArialFont_h13w6;

		void CreateGDIObjects();
		void DestroyGDIObjects();
		void CreateSketchpadObjects();
		void DestroySketchpadObjects();

		HDC hDC_Tapes;
		HDC hDC_ADI;
		HDC hDC_ADI_ORBIT;
		HDC hDC_ADIMASK;
		HDC hDC_ADIMASK_ORBIT;

		SKETCHMESH hADIball;

		void Tape_Create( void );
		void ADI_Create( void );

		/** 
		 * Paints the DPS display.
		 */
		void DPS( HDC hDC );
		void DPS( oapi::Sketchpad* skp );

		/**
		 * MEDS Display functions
		 */
		void SystemStatusDisplay_CSTMenu( oapi::Sketchpad* skp );
		void SystemStatusDisplay_IDPInteractiveCST( oapi::Sketchpad* skp );
		void AEPFD( HDC hDC );
		void AEPFD( oapi::Sketchpad2* skp );
		void ORBITPFD( HDC hDC );
		void ORBITPFD( oapi::Sketchpad2* skp );
		void OMSMPS( oapi::Sketchpad* skp );
		void APUHYD( oapi::Sketchpad* skp );
		void SPI( oapi::Sketchpad* skp );

		// TODO correct position and size of tapes
		void Tape_Alpha( HDC hDC, double MachNumber );
		void Tape_KEAS_MVR( HDC hDC, double MachNumber );
		void Tape_MVR_KEAS( HDC hDC, double MachNumber );
		void Tape_MVI_KEAS( HDC hDC, double MachNumber );
		void Tape_H_Hdot( HDC hDC, double Altitude_ft, double Hdot );
		void Tapes_Invalid( HDC hDC );
		void Tapes_Invalid( oapi::Sketchpad2* skp );

		void ADI_STATIC( HDC hDC );
		void ADI_STATIC( oapi::Sketchpad2* skp );
		void ADI_STATIC_ORBIT( HDC hDC );
		void ADI_STATIC_ORBIT( oapi::Sketchpad2* skp );
		void ADI( HDC hDC, double pitch, double roll, double yaw );
		void ADI( oapi::Sketchpad2* skp, double pitch, double roll, double yaw );
		void ADI_ORBIT( HDC hDC, double pitch, double roll, double yaw );
		void ADI_ORBIT( oapi::Sketchpad2* skp, double pitch, double roll, double yaw );
		void ADI_RATE_A( HDC hDC, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_RATE_A( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_RATE_B( HDC hDC, double pitch, double roll, double yaw, int adirate, double Altitude_ft );// 5/(5/etc)/5
		void ADI_RATE_B( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adirate, double Altitude_ft );// 5/(5/etc)/5
		void ADI_RATE_ORBIT( HDC hDC, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_RATE_ORBIT( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adirate );// 10/5/1
		void ADI_ERROR_A( HDC hDC, double pitch, double roll, double yaw, int adierr );// 10/5/1
		void ADI_ERROR_A( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr );// 10/5/1
		void ADI_ERROR_B( HDC hDC, double pitch, double roll, double yaw, int adierr );// 25/25/10 5/2/1 2.5/2.5/2.5
		void ADI_ERROR_B( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr );// 25/25/10 5/2/1 2.5/2.5/2.5
		void ADI_ERROR_C( HDC hDC, double pitch, double roll, double yaw, int adierr );// 25/25/10 1.25/1.25/0.5 2.5/2.5/2.5
		void ADI_ERROR_C( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr );// 25/25/10 1.25/1.25/0.5 2.5/2.5/2.5
		void ADI_ERROR_D( HDC hDC, double pitch, double roll, double yaw, int adierr );// 20/5/1 10/5/1 2.5/2.5/2.5
		void ADI_ERROR_D( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr );// 20/5/1 10/5/1 2.5/2.5/2.5
		void ADI_ERROR_ORBIT( HDC hDC, double pitch, double roll, double yaw, int adierr );// 10/5/1
		void ADI_ERROR_ORBIT( oapi::Sketchpad2* skp, double pitch, double roll, double yaw, int adierr );// 10/5/1

		void HSI_A( HDC hDC, double heading, double roll, bool arrowon, double arrowheading );
		void HSI_A( oapi::Sketchpad2* skp, double heading, double roll, bool arrowon, double arrowheading );
		void HSI_E( HDC hDC, double heading, bool arrowon, double arrowheading );
		void HSI_E( oapi::Sketchpad2* skp, double heading, bool arrowon, double arrowheading );
		void HSI_Arrow( HDC hDC, double heading );
		void HSI_Arrow( oapi::Sketchpad2* skp, double heading );

		void AEPFD_Header_AscentDAP( HDC hDC, int MM, int adiatt );
		void AEPFD_Header_AscentDAP( oapi::Sketchpad2* skp, int MM, int adiatt );
		void AEPFD_Header_TransDAP( HDC hDC, int MM, int adiatt );
		void AEPFD_Header_TransDAP( oapi::Sketchpad2* skp, int MM, int adiatt );
		void AEPFD_Header_AerojetDAP( HDC hDC, int MM, double MachNumber );
		void AEPFD_Header_AerojetDAP( oapi::Sketchpad2* skp, int MM, double MachNumber );
		void AEPFD_BETA( HDC hDC );
		void AEPFD_BETA( oapi::Sketchpad2* skp );
		void AEPFD_GMETER_STATIC( HDC hDC );
		void AEPFD_GMETER_STATIC( oapi::Sketchpad2* skp );
		void AEPFD_GMETER_ACCEL( HDC hDC );
		void AEPFD_GMETER_ACCEL( oapi::Sketchpad2* skp );
		void AEPFD_GMETER_NZ( HDC hDC );
		void AEPFD_GMETER_NZ( oapi::Sketchpad2* skp );
		void AEPFD_HACCEL( HDC hDC );
		void AEPFD_HACCEL( oapi::Sketchpad2* skp );
		void AEPFD_RANGERW( HDC hDC );
		void AEPFD_RANGERW( oapi::Sketchpad2* skp );
		void AEPFD_RANGEHACC( HDC hDC );
		void AEPFD_RANGEHACC( oapi::Sketchpad2* skp );
		void AEPFD_dAZ_HTA( HDC hDC, double MachNumber );
		void AEPFD_dAZ_HTA( oapi::Sketchpad2* skp, double MachNumber );
		void AEPFD_dXTRK( HDC hDC );
		void AEPFD_dXTRK( oapi::Sketchpad2* skp );
		void AEPFD_XTRK( HDC hDC );
		void AEPFD_XTRK( oapi::Sketchpad2* skp );
		void AEPFD_dINC( HDC hDC );
		void AEPFD_dINC( oapi::Sketchpad2* skp );
		void AEPFD_TGTINC( HDC hDC );
		void AEPFD_TGTINC( oapi::Sketchpad2* skp );
		void AEPFD_GSI( HDC hDC, double Altitude_ft );
		void AEPFD_GSI( oapi::Sketchpad2* skp, double Altitude_ft );

		inline bool GetFlash( void ) const
		{
			int SimT=(int)(oapiGetSimTime() * 2);
			return (SimT%2)==1;
		}

	protected:
		unsigned short usMDUID;
		SURFHANDLE shLabelTex;
		dps::DEUCHAR textBuffer[51][26];
		dps::IDP* prim_idp;
		dps::IDP* sec_idp;
		bool bInverseX;
		bool bUseSecondaryPort;
		EXTMFDSPEC mfdspec;
		double fBrightness;
		bool bPower;

		int display;
		int menu;
		
		std::vector<dps::DEU_LINE> lines;
		std::vector<dps::DEU_ELLIPSE> ellipses;
		
		float btnPwrXmin, btnPwrXmax, btnPwrYmin, btnPwrYmax;
		float btnBrtXmin, btnBrtXmax, btnBrtYmin, btnBrtYmax;
		float edgekeyXmin, edgekeyXmax, edgekeyYmin, edgekeyYmax;

		//Use a paint buffer for storing primitives?
		virtual void RegisterMFDContext(int id);
		//void DrawCommonHeader(const char* cDispTitle);
		virtual void PrintToBuffer(const char* string, int length, int col, int row, char attributes);

		void DrawMenuButton( oapi::Sketchpad* skp, int x );

	public:
		MDU(Atlantis* _sts, const string& _ident, unsigned short usMDUID, bool _bUseCRTMFD = true);
		virtual ~MDU();

		virtual bool OnReadState( FILEHANDLE scn );
		virtual void OnSaveState( FILEHANDLE scn ) const;
		virtual bool IsMultiLineSaveState() const { return true; };

		//bool PrintChar(unsigned short x, unsigned short y, DEUCHAR c);
		//bool PrintString(unsigned short x, unsigned short y, char* pText, short sLength, char cAttr = DEUATT_NORMAL);
		//DEUCHAR GetTextBuffer(unsigned short x, unsigned short y) const;
		bool SetPrimaryIDP(dps::IDP* idp);
		bool SetSecondaryIDP(dps::IDP* idp);
		inline dps::IDP* GetIDP() const {
			if(bUseSecondaryPort)
				return sec_idp;
			else
				return prim_idp;
		}
		/**
		 * Does nothing as it currently has no animations.
		 * @sa BasicVCComponent::DefineVCAnimations
		 */
		virtual void DefineVCAnimations(UINT vc_idx);
		/**
		 * handle mouse events
		 * @sa BasicVCComponent::OnMouseEvent
		 */
		virtual bool OnMouseEvent(int _event, float x, float y);

		/** 
		 * Paint the edge menu area on this Sketchpad.
		 */
		virtual bool PaintEdgeMenu( oapi::Sketchpad* skp );
		/**
		 * Register the MFD area for Orbiter. Does nothing when MFD rendering 
		 * is bypassed.
		 */
		virtual bool RealizeMFD(int id);

		virtual bool OnVCRedrawEvent(int id, int _event, SURFHANDLE surf);

		virtual void RegisterVC();
		/**
		 * define the Area ID of the MDU screen inside the VC. when in 
		 * CRTMFD mode, it paints only the edge key menu area. 
		 */
		virtual bool DefineRegionAID(UINT aid);
		virtual bool DefineVCGroup(UINT mgrp);
		/**
		 * Links to label texture, when used in conjunction with CRTMFD, expects texture 
		 * for drawing full MDU when not.
		 * @return false, if failed.
		 */
		virtual bool DefineVCTexture(SURFHANDLE tex);
		virtual bool IsCRTBufferEnabled() const;

		/**
		 * Sets location of power button.
		 * If this function is not called, power button location will be set to default values
		 */
		void SetPowerButtonArea(float xmin, float ymin, float xmax, float ymax);
		/**
		 * Sets location of brightness button.
		 * If this function is not called, brightness button location will be set to default values
		 */
		void SetBrightnessButtonArea(float xmin, float ymin, float xmax, float ymax);
		/**
		 * Sets location of edgekeys.
		 * Parameters specify row containing all 6 edgekeys.
		 * If this function is not called, edgekey location will be set to default values
		 */
		void SetEdgekeyArea(float xmin, float ymin, float xmax, float ymax);

		virtual void UpdateTextBuffer();
		

		//IDP interface functions
		/** 
		 * Act like the curses function
		 */
		inline void mvprint(int x, int y, const char* pszLine, char attributes = 0) 
		{
			//
			PrintToBuffer(pszLine, strlen(pszLine), x, y, attributes);
		}

		/**
		 * Draw line on DEU.
		 * Coordinates should be between 0 and 255
		 */
		inline void Line(int x1, int y1, int x2, int y2, char attributes = 0) 
		{
			dps::DEU_LINE line;
			line.x0 = x1;
			line.y0 = y1;
			line.x1 = x2;
			line.y1 = y2;
			line.cAttr = attributes;
			lines.push_back(line);
		}

		/**
		 * Draw ellipse on DEU.
		 * Coordinates should be between 0 and 255
		 */
		inline void Ellipse(int xLeft, int yTop, int xRight, int yBottom, char attributes = 0)
		{
			dps::DEU_ELLIPSE ellipse;
			ellipse.xLeft = xLeft;
			ellipse.yTop = yTop;
			ellipse.xRight = xRight;
			ellipse.yBottom = yBottom;
			ellipse.cAttr = attributes;
			ellipses.push_back(ellipse);
		}

		/**
		 * Draw circle on DEU.
		 * Coordinates should be between 0 and 255
		 */
		inline void Circle(int xCenter, int yCenter, int radius, char attributes = 0)
		{
			Ellipse(xCenter-radius, yCenter-radius, xCenter+radius, yCenter+radius, attributes);
		}

		/**
		 * Draws delta character at specified location on MDU.
		 */
		inline void Delta(int x, int y, char attributes = 0)
		{
			// each DEU character is 5 pixels wide and 9 pixels high
			Line(5*x, 9*y + 6, 5*x+4, 9*y + 6, attributes);
			Line(5*x, 9*y + 6, 5*x + 2, 9*y, attributes);
			Line(5*x+4, 9*y + 6, 5*x + 2, 9*y, attributes);
		}

		/**
		 * Draws theta character at specified location on MDU.
		 */
		inline void Theta(int x, int y, char attributes = 0)
		{
			Ellipse(5*x, 9*y+1, 5*x+4, 9*y+8, attributes);
			Line(5*x, 9*y+4, 5*x+4, 9*y+4, attributes);
		}

		/**
		 * Adds dot above specified character on MDU.
		 * This is usually used to signify rates (i.e. rdot or hdot).
		 */
		inline void DotCharacter(int x, int y, char attributes = 0)
		{
			Circle(5*x+3, 9*y, 1, attributes);
		}

		/**
		 * Draws alpha character at specified location on MDU.
		 */
		inline void Alpha(int x, int y, char attributes = 0)
		{
			Circle(5*x+2, 9*y+5, 2, attributes);
			Line(5*x+4, 9*y+3, 5*x+3, 9*y+3, attributes);
			Line(5*x+4, 9*y+6, 5*x+3, 9*y+6, attributes);
		}

		/**
		 * Draws sigma character at specified location on MDU.
		 */
		inline void Sigma(int x, int y, char attributes = 0)
		{
			Line(5*x+4, 9*y+3, 5*x+2, 9*y+3, attributes);
			Circle(5*x+2, 9*y+5, 2, attributes);
		}

		/**
		 * Draws up arrow character at specified location on MDU.
		 */
		inline void UpArrow(int x, int y, char attributes = 0)
		{
			Line(5*x+2, 9*y+7, 5*x+2, 9*y, attributes);
			Line(5*x, 9*y+3, 5*x+2, 9*y+1, attributes);
			Line(5*x+4, 9*y+3, 5*x+2, 9*y+1, attributes);
		}

		/**
		 * Draws down arrow character at specified location on MDU.
		 */
		inline void DownArrow(int x, int y, char attributes = 0)
		{
			Line(5*x+2, 9*y+1, 5*x+2, 9*y+8, attributes);
			Line(5*x, 9*y+5, 5*x+2, 9*y+7, attributes);
			Line(5*x+4, 9*y+5, 5*x+2, 9*y+7, attributes);
		}

		/**
		 * Draws left arrow character at specified location on MDU.
		 */
		inline void LeftArrow( int x, int y, char attributes = 0 )
		{
			Line( (5 * x) + 4, (9 * y) + 4, (5 * x) - 1, (9 * y) + 4, attributes );
			Line( (5 * x) + 2, (9 * y) + 2, 5 * x, (9 * y) + 4, attributes );
			Line( (5 * x) + 2, (9 * y) + 6, 5 * x, (9 * y) + 4, attributes );
		}

		/**
		 * Draws right arrow character at specified location on MDU.
		 */
		inline void RightArrow( int x, int y, char attributes = 0 )
		{
			Line( 5 * x, (9 * y) + 4, (5 * x) + 5, (9 * y) + 4, attributes );
			Line( (5 * x) + 2, (9 * y) + 2, (5 * x) + 4, (9 * y) + 4, attributes );
			Line( (5 * x) + 2, (9 * y) + 6, (5 * x) + 4, (9 * y) + 4, attributes );
		}

		/**
		 * Draws the orbiter symbol, as viewed from the top at specified location on MDU.
		 */
		inline void OrbiterSymbolTop( int x, int y, char attributes = 0 )
		{
			Line( x, y, x, y + 2, attributes );
			Line( x + 1, y + 2, x + 1, y + 5, attributes );
			Line( x - 1, y + 2, x - 1, y + 5, attributes );
			Line( x + 1, y + 4, x + 4, y + 7, attributes );
			Line( x - 1, y + 4, x - 4, y + 7, attributes );
			Line( x + 3, y + 7, x, y + 7, attributes );
			Line( x - 3, y + 7, x, y + 7, attributes );
			Line( x, y + 8,  x - 1, y + 7, attributes );
		}

		inline void OrbiterSymbolSide( int x, int y, double rotation, char attributes = 0 )
		{
			double sinrot = sin( rotation );
			double cosrot = cos( rotation );

			Line( x, y, x + Round( 2 * (cosrot + sinrot) ), y + Round( 2 * (sinrot - cosrot) ), attributes );
			Line( x + Round( 2 * (cosrot + sinrot) ), y + Round( 2 * (sinrot - cosrot) ), x + Round( 5 * cosrot + 2 * sinrot ), y + Round( 5 * sinrot - 2 * cosrot ), attributes );
			Line( x + Round( 5 * cosrot + 2 * sinrot ), y + Round( 5 * sinrot - 2 * cosrot ), x + Round( 7 * cosrot + 5 * sinrot ), y + Round( 7 * sinrot - 5 * cosrot ), attributes );
			Line( x + Round( 7 * cosrot + 5 * sinrot ), y + Round( 7 * sinrot - 5 * cosrot ), x + Round( 8 * cosrot + 5 * sinrot ), y + Round( 8 * sinrot - 5 * cosrot ), attributes );
			Line( x + Round( 8 * cosrot + 5 * sinrot ), y + Round( 8 * sinrot - 5 * cosrot ), x + Round( 7 * cosrot + 2 * sinrot ), y + Round( 7 * sinrot - 2 * cosrot ), attributes );
			Line( x + Round( 7 * cosrot + 2 * sinrot ), y + Round( 7 * sinrot - 2 * cosrot ), x + Round( 8 * cosrot + sinrot ), y + Round( 8 * sinrot - cosrot ), attributes );
			Line( x + Round( 8 * cosrot + sinrot ), y + Round( 8 * sinrot - cosrot ), x + Round( 8 * cosrot ), y + Round( 8 * sinrot ), attributes );
			Line( x + Round( 8 * cosrot ), y + Round( 8 * sinrot ), x + Round( 7 * cosrot - sinrot ), y + Round( 7 * sinrot + cosrot ), attributes );
			Line( x + Round( 7 * cosrot - sinrot ), y + Round( 7 * sinrot + cosrot ), x + Round( cosrot - sinrot ), y + Round( sinrot + cosrot ), attributes );
			Line( x + Round( cosrot - sinrot ), y + Round( sinrot + cosrot ), x, y, attributes );
			// no rotation normal
			/*Line( x, y, x + 2, y - 2, attributes );
			Line( x + 2, y - 2, x + 5, y - 2, attributes );
			Line( x + 5, y - 2, x + 7, y - 5, attributes );
			Line( x + 7, y - 5, x + 8, y - 5, attributes );
			Line( x + 8, y - 5, x + 7, y - 2, attributes );
			Line( x + 7, y - 2, x + 8, y - 1, attributes );
			Line( x + 8, y - 1, x + 8, y, attributes );
			Line( x + 8, y, x + 7, y + 1, attributes );
			Line( x + 7, y + 1, x + 1, y + 1, attributes );
			Line( x + 1, y + 1, x, y, attributes );*/
			// no rotation minimal
			/*Line( x, y, x + 2, y - 2, attributes );
			Line( x + 2, y - 2, x + 5, y - 2, attributes );
			Line( x + 5, y - 2, x + 7, y - 5, attributes );
			Line( x + 7, y - 5, x + 9, y - 5, attributes );
			Line( x + 8, y - 4, x + 6, y - 1, attributes );
			Line( x + 7, y + 1, x + 9, y - 2, attributes );
			Line( x + 7, y + 1, x, y + 1, attributes );*/
		}

		/**
		 * Draws sign of number at specified location on MDU.
		 */
		inline void NumberSign( int x, int y, double number, char attributes = 0 )
		{
			if (number > 0) mvprint( x, y, "+", attributes );
			else if (number < 0) mvprint( x, y, "-", attributes );
			else mvprint( x, y, " ", attributes );
		}

		/**
		 * Draws sign of number with brackets at specified location on MDU.
		 */
		inline void NumberSignBracket( int x, int y, double number, char attributes = 0 )
		{
			if (number > 0) mvprint( x, y, "+", attributes );
			else if (number < 0) mvprint( x, y, "-", attributes );
			else mvprint( x, y, " ", attributes );

			Line( x * 5, (y * 9) + 1, (x * 5) + 2, (y * 9) + 1, attributes );
			Line( x * 5, (y * 9) + 7, (x * 5) + 2, (y * 9) + 7, attributes );

			Line( (x * 5) + 4, (y * 9) + 1, (x * 5) + 2, (y * 9) + 1, attributes );
			Line( (x * 5) + 4, (y * 9) + 7, (x * 5) + 2, (y * 9) + 7, attributes );

			Line( x * 5, (y * 9) + 1, x * 5, (y * 9) + 7, attributes );
			Line( (x * 5) + 4, (y * 9) + 1, (x * 5) + 4, (y * 9) + 7, attributes );
		}

		/**
		 * Draws underline the character at the specified location on MDU.
		 */
		inline void Underline( int x, int y, char attributes = 0 )
		{
			Line( (x * 5) + 1, (y * 9) + 7, (x * 5) + 4, (y * 9) + 7, attributes );
		}

		virtual bool GetViewAngle() const;
		virtual short GetPortConfig() const;
		virtual bool GetSelectedPort() const;

		/**
		 * Return the identification of the IDP driving this
		 * display. 
		 * @return 0 if not connected to IDP or IDP failed
		 */
		virtual unsigned short GetDrivingIDP() const;

		virtual void PaintDisplay( oapi::Sketchpad* skp );
		virtual int NavigateMenu( DWORD key );
		virtual char* ButtonLabel( int bt );
		virtual int ButtonMenu( const MFDBUTTONMENU **menu ) const;
	};
};
