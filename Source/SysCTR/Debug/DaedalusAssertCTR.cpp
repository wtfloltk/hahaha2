/*

  Copyright (C) 2001 StrmnNrmn

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/



#include <stdio.h>
#include "Base/Assert.h"

#ifdef DAEDALUS_ENABLE_ASSERTS

EAssertResult DaedalusAssert(const char * expression, const char * file, unsigned int line, const char * msg, ...);

DaedalusAssertHook gAssertHook = &DaedalusAssert;
//
//	Return -1 to ignore once, 0 to ignore permenantly, 1 to break
//
EAssertResult DaedalusAssert(const char * expression, const char * file, unsigned int line, const char * msg, ...)
{
	return AR_BREAK;
}

#endif //DAEDALUS_ENABLE_ASSERTS
