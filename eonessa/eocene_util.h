
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

#ifndef EOCENE_UTIL_H
#define EOCENE_UTIL_H

#define EC_OK_REASON                    "No Error"
#define EC_FAIL_REASON                  "Unknown Error"
#define EC_NOMEM_REASON                 "Out of Memory"
#define EC_BUFOVER_REASON               "Buffer Overflow"
#define EC_BADPARAM_REASON              "Bad input parameter"
#define EC_CANT_DLINIT_REASON           "Unable to initialize dl library"
#define EC_CANT_DLSETSEARCHPATH_REASON  "Unable to set dl search patch"
#define EC_CANT_DLOPENEXT_REASON        "Call to dlopenext failed"
#define EC_CANT_DLCLOSE_REASON          "Unable to close dl"
#define EC_CANT_DLEXIT_REASON           "Call to dlexit failed"

char* eocene_error_string(int error);

#endif // EOCENE_UTIL_H
