
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
#define EN_OK          0   /* successful result */
#define EN_FAIL       -1   /* generic failure */
#define EN_NOMEM      -2   /* memory shortage failure */
#define EN_BUFOVER    -3   /* overflowed buffer */
#define EN_BADPARAM   -4   /* invalid parameter supplied */
#define EN_BAD_FRAME  -5   /* Invalid Frame */

/*#define EN_MAX_COMPONENTS 128*/  /* Maximum number of headers and components that
                                  the library will parse */

#define EN_MIN_SNAPLEN 60
#define EN_MAX_SNAPLEN 32764

/* Capture types */
#define EN_CAP_TYPE_MAC  0  /* Frame begins with destination MAC */
#define EN_CAP_TYPE_PCAP 1  /* Ditto. PCAP doesn't include framing bits */

/* Frame types */
#define EN_FRAME_ETHERNET_II 1  /* Ethertype */
#define EN_FRAME_802_DOT_3   2  /* Length + 802.2 LLC */
/* 802.3 requires an LLC (802.2) header, which in turn optionally supports a
 * SNAP header */

#define EN_MAX_VLAN_TAGS 8
#define EN_MAX_MPLS_TAGS 8

/* Contents */
#define EN_CONTAINS_802_DOT_3_LENGTH   1
#define EN_CONTAINS_IPX_RAW_802_DOT_3  2
#define EN_CONTAINS_LLC_HEADER         4
#define EN_CONTAINS_2_BYTE_LLC_CONTROL 8
#define EN_CONTAINS_SNAP_HEADER        16
#define EN_CONTAINS_VLAN_TAGS          32
#define EN_CONTAINS_MPLS_TAGS          64

struct en_vlan_tag {
    int tag_type;
    int priority;
    int canonical_format;
    int vlan;
};

struct en_mpls_tag {
    uint32_t label;
    int cos;
    int stack_bit;
    int ttl;
};

struct eonessa {
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
    struct en_vlan_tag vlan_tags[EN_MAX_VLAN_TAGS];
    int number_of_mpls_tags;
    struct en_mpls_tag mpls_tags[EN_MAX_MPLS_TAGS];
    uint16_t payload_ethertype;
    char* payload_pointer;
    int payload_length;
    int done;
};

int eonessa_parse(const char* buf, unsigned n, int capture_type, struct eonessa*);

#endif // EONESSA_BASE_H
