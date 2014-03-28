
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

#ifndef EOCENE_STP_BASE_H
#define EOCENE_STP_BASE_H

/* Return types. But only use these internally! */
/* Use, for example, EC_OK, when returning from public
 * functions. */
#define EC_STP_OK               0 /* successful result */
#define EC_STP_FAIL            -1 /* generic failure */
#define EC_STP_NOMEM           -2 /* memory shortage failure */
#define EC_STP_BUFOVER         -3 /* overflowed buffer */
#define EC_STP_BADPARAM        -4 /* invalid parameter supplied */
#define EC_STP_BAD_DATA        -5 /* Invalid Packet */

#define EC_STP_TOPOLOGY_CHANGE  1
#define EC_STP_PROPOSAL         2
#define EC_STP_ROLE_ALTERNATE   4
#define EC_STP_ROLE_ROOT        8
#define EC_STP_ROLE_DESIGNATED  12
#define EC_STP_STATE_LEARNING   32
#define EC_STP_STATE_FORWARDING 64
#define EC_STP_STATE_AGREEMENT  128
#define EC_STP_ROLE_BITMAP      12

struct ec_stp {
    int protocol_id;
    int version_id;
    int bpdu_type;
    uint8_t flags;
    int root_bridge_priority;
    int root_bridge_system_id_extension;
    char root_bridge_mac[7];
    int root_path_cost;
    int bridge_priority;
    int bridge_system_id_extension;
    char bridge_mac[7];
    int port_id;
    int message_age;
    int max_age;
    int hello_time;
    int forward_delay;
};


#endif // EOCENE_STP_BASE_H
