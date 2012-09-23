/****************************************************************************
  This file is part of Space Shuttle Ultra

  Computer Interface Electronics Block II definition



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
#ifndef _mps_CIE_BLOCK_II_H_
#define _mps_CIE_BLOCK_II_H_


#include "ComputerInterfaceElectronics.h"
#include "SSMEController.h"


namespace mps
{
	class ComputerInterfaceElectronics_BLOCK_II:public ComputerInterfaceElectronics
	{
		public:
			ComputerInterfaceElectronics_BLOCK_II( int ch, SSMEController* Controller );
			~ComputerInterfaceElectronics_BLOCK_II( void );

			void __OnSaveState( FILEHANDLE scn ) const;
			bool __OnParseLine( const char* line );
	};

}


#endif// _mps_CIE_BLOCK_II_H_
