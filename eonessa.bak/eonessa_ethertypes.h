
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

#ifndef EONESSA_ETHERTYPE
#define EONESSA_ETHERTYPE

#define EN_ETHER_UNKNOWN               0x0000
#define EN_ETHER_IPV4                  0x0800
#define EN_ETHER_ARP                   0x0806
#define EN_ETHER_IS_IS                 0x8000
#define EN_ETHER_REVERSE_ARP           0x8035
#define EN_ETHER_VLAN_TAG_8100         0x8100
#define EN_ETHER_IPV6                  0x86dd
#define EN_ETHER_TCP_IP_COMPRESSION    0x876b
#define EN_ETHER_IP_AUTONOMOUS_SYSTEMS 0x876c
#define EN_ETHER_SECURE_DATA           0x876d
#define EN_ETHER_LACP                  0x8809
#define EN_ETHER_PPP                   0x880b
#define EN_ETHER_VLAN_TAG_88A8         0x88a8
#define EN_ETHER_MPLS                  0x8847
#define EN_ETHER_MPLS_UPSTREAM_LABEL   0x8848
#define EN_ETHER_PPPOE_DISCOVERY       0x8863
#define EN_ETHER_PPPOE_SESSION         0x8864
#define EN_ETHER_802_DOT_1X            0x888e
#define EN_ETHER_VLAN_TAG_9100         0x9100
#define EN_ETHER_VLAN_TAG_9200         0x9200
#define EN_ETHER_VLAN_TAG_9300         0x9300
#define EN_ETHER_RESERVED              0xffff

#endif // EONESSA_ETHERTYPE
