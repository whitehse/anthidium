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

#ifndef EOCENE_ETHERNET_BASE_H
#define EOCENE_ETHERNET_BASE_H

/* Return types. But only use these internally! */
/* Use, for example, EC_OK, when returning from public
 * functions. */
#define EC_ETH_OK               0 /* successful result */
#define EC_ETH_FAIL            -1 /* generic failure */
#define EC_ETH_NOMEM           -2 /* memory shortage failure */
#define EC_ETH_BUFOVER         -3 /* overflowed buffer */
#define EC_ETH_BADPARAM        -4 /* invalid parameter supplied */
#define EC_ETH_BAD_FRAME       -5 /* Invalid Packet */

#define init eocene_ethernet_LTX_init
#define parse eocene_ethernet_LTX_parse

/*#define EC_ETH_MAX_COMPONENTS 128*/  /* Maximum number of headers and components that
                                  the library will parse */

#define EC_ETH_MIN_SNAPLEN 60
#define EC_ETH_MAX_SNAPLEN 32764

/* Capture types */
#define EC_ETH_CAP_TYPE_MAC  0  /* Frame begins with destination MAC */
#define EC_ETH_CAP_TYPE_PCAP 1  /* Ditto. PCAP doesn't include framing bits */

/* Frame types */
#define EC_ETH_FRAME_ETHERNET_II 1  /* Ethertype */
#define EC_ETH_FRAME_802_DOT_3   2  /* Length + 802.2 LLC */
/* 802.3 requires an LLC (802.2) header, which in turn optionally supports a
 * SNAP header */

#define EC_ETH_MAX_VLAN_TAGS 8
#define EC_ETH_MAX_MPLS_TAGS 8

/* Contents */
#define EC_ETH_CONTAINS_802_DOT_3_LENGTH   1
#define EC_ETH_CONTAINS_IPX_RAW_802_DOT_3  2
#define EC_ETH_CONTAINS_LLC_HEADER         4
#define EC_ETH_CONTAINS_2_BYTE_LLC_CONTROL 8
#define EC_ETH_CONTAINS_SNAP_HEADER        16
#define EC_ETH_CONTAINS_VLAN_TAGS          32
#define EC_ETH_CONTAINS_MPLS_TAGS          64

struct ec_eth_vlan_tag {
    int tag_type;
    int priority;
    int canonical_format;
    int vlan;
};

struct ec_eth_mpls_tag {
    uint32_t label;
    int cos;
    int stack_bit;
    int ttl;
};

struct ec_ethernet {
    int frame_size;
    int capture_type;
    char source_mac[7];     /* All MACs/OUIs are in network byte order */
    char source_mac_dash_format[18];
    char source_mac_colon_format[18];
    char source_mac_cisco_format[18];
    char destination_mac[7];
    char destination_mac_dash_format[18];
    char destination_mac_colon_format[18];
    char destination_mac_cisco_format[18];
    char source_oui_dash_format[9];
    char source_oui_colon_format[9];
    char destination_oui_dash_format[9];
    char destination_oui_colon_format[9];
    int contents;
    int dot_3_length;
    uint16_t llc_destination_sap; /* Host byte order */
    uint16_t llc_source_sap;      /* Host byte order */
    uint16_t llc_control;         /* Host byte order. >=0, <=65535 */
    char snap_oui[3];             /* Network byte order */
    char snap_oui_dash_format[9];
    char snap_oui_colon_format[9];
    uint16_t snap_sub_protocol;   /* Host byte order */
    int number_of_vlan_tags;
    struct ec_eth_vlan_tag vlan_tags[EC_ETH_MAX_VLAN_TAGS];
    int number_of_mpls_tags;
    struct ec_eth_mpls_tag mpls_tags[EC_ETH_MAX_MPLS_TAGS];
    uint16_t payload_ethertype;
    char* payload_pointer;
    int payload_length;
    int done;
};

//int ec_eth_parse(const char* buf, unsigned n, int capture_type, struct eonessa*);
typedef int (*eocene_ethernet_listener)(struct ec_ethernet *frame, const char* buf, unsigned buf_len);
typedef int (*eocene_ethernet_register_listener)(void *callback);


#endif // EOCENE_ETHERNET_BASE_H
