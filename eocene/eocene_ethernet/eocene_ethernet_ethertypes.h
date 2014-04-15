
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

#ifndef EOCENE_ETHERNET_ETHERTYPE
#define EOCENE_ETHERNET_ETHERTYPE

#define EC_ETH_ETHER_UNKNOWN               0x0000
#define EC_ETH_ETHER_IPV4                  0x0800
#define EC_ETH_ETHER_ARP                   0x0806
#define EC_ETH_ETHER_802_DOT_1_STP         0x4242
#define EC_ETH_ETHER_IS_IS                 0x8000
#define EC_ETH_ETHER_REVERSE_ARP           0x8035
#define EC_ETH_ETHER_VLAN_TAG_8100         0x8100
#define EC_ETH_ETHER_IPV6                  0x86dd
#define EC_ETH_ETHER_TCP_IP_COMPRESSION    0x876b
#define EC_ETH_ETHER_IP_AUTONOMOUS_SYSTEMS 0x876c
#define EC_ETH_ETHER_SECURE_DATA           0x876d
#define EC_ETH_ETHER_LACP                  0x8809
#define EC_ETH_ETHER_PPP                   0x880b
#define EC_ETH_ETHER_VLAN_TAG_88A8         0x88a8
#define EC_ETH_ETHER_MPLS                  0x8847
#define EC_ETH_ETHER_MPLS_UPSTREAM_LABEL   0x8848
#define EC_ETH_ETHER_PPPOE_DISCOVERY       0x8863
#define EC_ETH_ETHER_PPPOE_SESSION         0x8864
#define EC_ETH_ETHER_802_DOT_1X            0x888e
#define EC_ETH_ETHER_VLAN_TAG_9100         0x9100
#define EC_ETH_ETHER_VLAN_TAG_9200         0x9200
#define EC_ETH_ETHER_VLAN_TAG_9300         0x9300
#define EC_ETH_ETHER_RESERVED              0xffff

#endif // EOCENE_ETHERNET_ETHERTYPE
