
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

#ifndef EOSIMIAS_UTIL_H
#define EOSIMIAS_UTIL_H

#define ES_OK_REASON                    "No Error"
#define ES_FAIL_REASON                  "Unknown Error"
#define ES_NOMEM_REASON                 "Out of Memory"
#define ES_BUFOVER_REASON               "Buffer Overflow"
#define ES_BADPARAM_REASON              "Bad input parameter"
#define ES_CANT_DLINIT_REASON           "Unable to initialize dl library"
#define ES_CANT_DLSETSEARCHPATH_REASON  "Unable to set dl search patch"
#define ES_CANT_DLOPENEXT_REASON        "Call to dlopenext failed"
#define ES_CANT_DLSYM                   "Unable to find symbol"
#define ES_CANT_DLCLOSE_REASON          "Unable to close dl"
#define ES_CANT_DLEXIT_REASON           "Call to dlexit failed"

char* eosimias_error_string(int error);

#endif // EOSIMIAS_UTIL_H
