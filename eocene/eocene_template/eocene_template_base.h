
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

#ifndef EOCENE_TEMPLATE_BASE_H
#define EOCENE_TEMPLATE_BASE_H

/* Return types. But only use these internally! */
/* Use, for example, EC_OK, when returning from public
 * functions. */
#define EC_TP_OK               0 /* successful result */
#define EC_TP_FAIL            -1 /* generic failure */
#define EC_TP_NOMEM           -2 /* memory shortage failure */
#define EC_TP_BUFOVER         -3 /* overflowed buffer */
#define EC_TP_BADPARAM        -4 /* invalid parameter supplied */
#define EC_TP_BAD_DATA        -5 /* Invalid Packet */

int init(config_setting_t *config,
        ec_use_table_cb _use_table,
        ec_store_cb _store,
        ec_retrieve_cb _retrieve,
        ec_rem_cb rem,
        ec_unuse_table_cb _unuse_table);

#endif // EOCENE_TEMPLATE_BASE_H
