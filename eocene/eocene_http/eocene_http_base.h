
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

#ifndef EOCENE_HTTP_BASE_H
#define EOCENE_HTTP_BASE_H

/* Return types. But only use these internally! */
/* Use, for example, EC_OK, when returning from public
 * functions. */
#define EC_HT_OK               0 /* successful result */
#define EC_HT_FAIL            -1 /* generic failure */
#define EC_HT_NOMEM           -2 /* memory shortage failure */
#define EC_HT_BUFOVER         -3 /* overflowed buffer */
#define EC_HT_BADPARAM        -4 /* invalid parameter supplied */
#define EC_HT_BAD_DATA        -5 /* Invalid Packet */

#define EC_HT_FRESH                0 /* No data as of yet */
#define EC_HT_REQUEST_HEADER_DATA  1 /* Received some header data */
#define EC_HT_REQUEST_BODY         2 /* Expecting more body data */
#define EC_HT_REQUEST_COMPLETE     3 /* Waiting for server response */
#define EC_HT_RESPONSE_HEADER_DATA 4 /* Received some header data (from server) */
#define EC_HT_RESPONSE_BODY        5 /* Expecting more body data */

int init(config_setting_t *config);

#endif // EOCENE_HTTP_BASE_H
