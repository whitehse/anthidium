
/*
 * Copyright (C) 2011 Dan White
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

#ifndef EOCENE_ETHERNET_SAP
#define EOCENE_ETHERNET_SAP

#define EC_ETH_SAP_NULL                                 0x00
#define EC_ETH_SAP_INDIVIDUAL_LLC_SUBLAYER              0x02
#define EC_ETH_SAP_GROUP_LLC_SUBLAYER                   0x03
#define EC_ETH_SAP_IBM_SNA_INDIVIDUAL_PATH_CONTROL      0x04
#define EC_ETH_SAP_IBM_SNA_GROUP_PATH_CONTROL           0x05
#define EC_ETH_SAP_ARPANET_INTERNET_PROTOCOL            0x06
#define EC_ETH_SAP_SNA                                  0x08
#define EC_ETH_SAP_SNA2                                 0x0c
#define EC_ETH_SAP_PROWAY_NETWORK_MANAGEMENT            0x0e
#define EC_ETH_SAP_TEXAS_INSTRUMENTS                    0x18
#define EC_ETH_SAP_IEEE_802_DOT_1_STP                   0x42
#define EC_ETH_SAP_EIA_RS_511_MESSAGE                   0x4e
#define EC_ETH_SAP_ISO_8208                             0x7e
#define EC_ETH_SAP_XEROX_NETWORK_SYSTEMS                0x80
#define EC_ETH_SAP_NESTAR                               0x86
#define EC_ETH_SAP_PROWAY_ACTIVE_STATION                0x8e
#define EC_ETH_SAP_ARPANET_ARP                          0x98
#define EC_ETH_SAP_BANYAN_VINES                         0xbc
#define EC_ETH_SAP_SNAP_AA                              0xaa
#define EC_ETH_SAP_SNAP_AB                              0xab
#define EC_ETH_SAP_NOVELL_NETWARE                       0xe0
#define EC_ETH_SAP_IBM_NETBIOS                          0xf0
#define EC_ETH_SAP_IBM_INDIVIDUAL_LAN_MANAGEMENT        0xf4
#define EC_ETH_SAP_IBM_GROUP_LAN_MANAGEMENT             0xf5
#define EC_ETH_SAP_IBM_REMOTE_PROGRAM_LOAD              0xf8
#define EC_ETH_SAP_UNGERMANN_BASS                       0xfa
#define EC_ETH_SAP_ISO_NETWORK_LAYER_PROTOCOL           0xfe
#define EC_ETH_SAP_GLOBAL_LSAP                          0xff

#endif // EOCENE_ETHERNET_SAP
