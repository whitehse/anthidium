
/*
 * Copyright (C) 2014 Dan White
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef EONESSA_BASE_H
#define EONESSA_BASE_H

/* Return types */
#define EN_OK                    0 /* successful result */
#define EN_FAIL                 -1 /* generic failure */
#define EN_NOMEM                -2 /* memory shortage failure */
#define EN_BUFOVER              -3 /* overflowed buffer */
#define EN_BADPARAM             -4 /* invalid parameter supplied */
#define EN_CANT_DLINIT          -5
#define EN_CANT_DLSETSEARCHPATH -6
#define EN_CANT_DLOPENEXT       -7
#define EN_CANT_DLSYM           -8
#define EN_CANT_DLCLOSE         -9
#define EN_CANT_DLEXIT          -10

#ifndef MODULE_PATH_ENV
#  define EONESSA_PLUGIN_PATH    "EONESSA_PLUGIN_PATH"
#endif

#define EN_LIB_DIR         PACKAGE_PKG_LIB_DIR

#define EN_MAX_NUM_OF_SUBMODULES   128

#endif // EONESSA_BASE_H
