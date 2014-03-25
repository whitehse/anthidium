
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

#ifndef EOCENE_DHCPV4_BASE_H
#define EOCENE_DHCPV4_BASE_H

/* Return types. But only use these internally! */
/* Use, for example, EC_OK, when returning from public
 * functions. */
#define EC_D4_OK               0 /* successful result */
#define EC_D4_FAIL            -1 /* generic failure */
#define EC_D4_NOMEM           -2 /* memory shortage failure */
#define EC_D4_BUFOVER         -3 /* overflowed buffer */
#define EC_D4_BADPARAM        -4 /* invalid parameter supplied */
#define EC_D4_BAD_DATA        -5 /* Invalid Packet */

#define EC_D4_MAX_DHCPV4_OPTIONS 64

#define EC_D4_BROADCAST_FLAG 1

/* Hardware Types (http://www.iana.org/assignments/arp-parameters/arp-parameters.xml) */
#define EC_D4_HW_RESERVED_0         0
#define EC_D4_HW_ETHERNET_10_MB     1
#define EC_D4_HW_EXP_ETHERNET_3_MB  2
#define EC_D4_HW_AX_DOT_25          3
#define EC_D4_HW_TOKEN_RING         4
#define EC_D4_HW_CHAOS              5
#define EC_D4_HW_IEEE_802           6
#define EC_D4_HW_ARCNET             7
#define EC_D4_HW_HYPERCHANNEL       8
#define EC_D4_HW_LANSTAR            9
#define EC_D4_HW_AUTONET            10
#define EC_D4_HW_LOCALTALK          11
#define EC_D4_HW_LOCALNET           12
#define EC_D4_HW_ULTRA_LINK         13
#define EC_D4_HW_SMDS               14
#define EC_D4_HW_FRAME_RELAY        15
#define EC_D4_HW_ATM_JBX2           16
#define EC_D4_HW_HDLC               17
#define EC_D4_HW_FIBRE_CHANNEL      18
#define EC_D4_HW_ATM_RFC2255        19
#define EC_D4_HW_SERIAL_LINE        20
#define EC_D4_HW_ATM_MIKE_BURROWS   21
#define EC_D4_HW_MLD_STD_188_220    22
#define EC_D4_HW_METRICOM           23
#define EC_D4_HW_IEEE_1394          24
#define EC_D4_HW_MAPOS              25
#define EC_D4_HW_TWINAXIAL          26
#define EC_D4_HW_EUI_64             27
#define EC_D4_HW_HIPARP             28
#define EC_D4_HW_IP_OVER_ISO_7816_3 29
#define EC_D4_HW_ARPSEC             30
#define EC_D4_HW_IPSEC_TUNNEL       31
#define EC_D4_HW_INFINIBAND         32
#define EC_D4_HW_CAI                33
#define EC_D4_HW_WIEGAND            34
#define EC_D4_HW_PURE_IP            35
#define EC_D4_HW_HW_EXP1            36
#define EC_D4_HW_HFI                37
#define EC_D4_HW_HW_EXP2            256
#define EC_D4_HW_RESERVED_65535     65535

#define EC_D4_OPT_OVERLOAD_FILE     1
#define EC_D4_OPT_OVERLOAD_SNAME    2
#define EC_D4_OPT_OVERLOAD_BOTH     3

#define EC_D4_MESSAGE_TYPE_DHCPDISCOVER 1
#define EC_D4_MESSAGE_TYPE_DHCPOFFER    2
#define EC_D4_MESSAGE_TYPE_DHCPREQUEST  3
#define EC_D4_MESSAGE_TYPE_DHCPDECLINE  4
#define EC_D4_MESSAGE_TYPE_DHCPACK      5
#define EC_D4_MESSAGE_TYPE_DHCPNAK      6
#define EC_D4_MESSAGE_TYPE_DHCPRELEASE  7
#define EC_D4_MESSAGE_TYPE_DHCPINFORM   8

#define EC_D4_OPT_PAD                      0
#define EC_D4_OPT_SUBNET_MASK              1
#define EC_D4_OPT_TIME_OFFSET              2
#define EC_D4_OPT_ROUTER                   3
#define EC_D4_OPT_TIME_SERVER              4
#define EC_D4_OPT_IEN_116_NAMESERVER       5   /* Must be a multiple of 4 */
#define EC_D4_OPT_DOMAIN_NAMESERVER        6
#define EC_D4_OPT_LOG_SERVER               7
#define EC_D4_OPT_COOKIE_SERVER            8
#define EC_D4_OPT_LPR                      9
#define EC_D4_OPT_IMPRESS                  10
#define EC_D4_OPT_RESOURCE_LOCATION        11
#define EC_D4_OPT_HOSTNAME                 12
#define EC_D4_OPT_BOOT_FILE_SIZE           13
#define EC_D4_OPT_MERIT_DUMP_FILE          14
#define EC_D4_OPT_DOMAINNAME               15
#define EC_D4_OPT_SWAP_SERVER              16
#define EC_D4_OPT_ROOT_PATH                17
#define EC_D4_OPT_EXTENTIONS_PATH          18
#define EC_D4_OPT_IP_FORWARDING            19
#define EC_D4_OPT_NON_LOCAL_ROUTING        20
#define EC_D4_OPT_POLICY_FILTER            21
#define EC_D4_OPT_MAX_DATAGRAM_SIZE        22
#define EC_D4_OPT_TTL                      23
#define EC_D4_OPT_MTU_AGING_TIMEOUT        24
#define EC_D4_OPT_MTU_PLATEAU              25
#define EC_D4_OPT_INTERFACE_MTU            26
#define EC_D4_OPT_ALL_SUBNETS_LOCAL        27
#define EC_D4_OPT_BROADCAST_ADDR           28
#define EC_D4_OPT_PERFORM_MASK_DISC        29
#define EC_D4_OPT_MASK_SUPPLIER            30
#define EC_D4_OPT_PERFORM_ROUTER_DISC      31
#define EC_D4_OPT_ROUTER_SOLICITATION      32
#define EC_D4_OPT_STATIC_ROUTE             33
#define EC_D4_OPT_TRAILER_ENCAP            34
#define EC_D4_OPT_ARP_CACHE_TIMEOUT        35
#define EC_D4_OPT_ETHERNET_ENCAP           36
#define EC_D4_OPT_TCP_DEFAULT_TTL          37
#define EC_D4_OPT_TCP_KEEPALIVE_INT        38
#define EC_D4_OPT_TCP_KEEPALIVE_GARB       39
#define EC_D4_OPT_NIS_DOMAIN               40
#define EC_D4_OPT_NIS_SERVERS              41
#define EC_D4_OPT_NTP_SERVERS              42
#define EC_D4_OPT_VENDOR_SPECIFIC          43
#define EC_D4_OPT_NETBIOS_NAMESERVER       44
#define EC_D4_OPT_NETBIOS_DIST_SERVER      45
#define EC_D4_OPT_NETBIOS_NODE_TYPE        46
#define EC_D4_OPT_NETBIOS_SCOPE            47
#define EC_D4_OPT_X_FONT_SERVER            48
#define EC_D4_OPT_X_DISPLAY_MANAGER        49
#define EC_D4_OPT_REQUESTED_IP             50
#define EC_D4_OPT_LEASE_TIME               51
#define EC_D4_OPT_OVERLOAD                 52
#define EC_D4_OPT_MESSAGE_TYPE             53
#define EC_D4_OPT_SERVER_IDENTIFIER        54
#define EC_D4_OPT_PARAMETER_REQ_LIST       55
#define EC_D4_OPT_ERROR_MESSAGE            56
#define EC_D4_OPT_MAX_DHCP_SIZE            57
#define EC_D4_OPT_T1_RENEWAL_TIME          58
#define EC_D4_OPT_T2_REBINDING_TIME        59
#define EC_D4_OPT_VENDOR_CLASS_IDENTIFIER  60
#define EC_D4_OPT_CLIENT_IDENTIFIER        61
#define EC_D4_OPT_NIS_PLUS_DOMAIN          64
#define EC_D4_OPT_NIS_PLUS_SERVERS         65
#define EC_D4_OPT_TFTP_SERVER              66
#define EC_D4_OPT_BOOTFILE                 67
#define EC_D4_OPT_MOBILE_HOME_AGENT        68
#define EC_D4_OPT_SMTP_SERVER              69
#define EC_D4_OPT_POP3_SERVER              70
#define EC_D4_OPT_NNTP_SERVER              71
#define EC_D4_OPT_WWW_SERVER               72
#define EC_D4_OPT_FINGER_SERVER            73
#define EC_D4_OPT_IRC_SERVER               74
#define EC_D4_OPT_STREETTALK_SERVER        75
#define EC_D4_OPT_STDA_SERVER              76
#define EC_D4_OPT_SITE_SPECIFIC_128        128
#define EC_D4_OPT_SITE_SPECIFIC_254        254
#define EC_D4_OPT_END                      255

struct eocene_dhcpv4_option {
    uint8_t tag;
    uint8_t length;
    char data_pointer;
};

struct eocene_dhcpv4 {
    int data_size;
    uint8_t op;         /* Host byte order */
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    uint32_t ciaddr;
    uint32_t yiaddr;
    uint32_t siaddr;
    uint32_t giaddr;
    char chaddr[17];    /* These are stored in network byte order */
    char sname[65];     /* */
    char file[129];     /* */
    int number_of_options;
    struct eocene_dhcpv4_option options[EC_D4_MAX_DHCPV4_OPTIONS];
};

#define init eocene_dhcpv4_LTX_init
#define parse eocene_dhcpv4_LTX_parse

int init(config_setting_t *config);
int parse(const char* buf, unsigned n, struct eocene_dhcpv4*, int flags);

#endif // EOCENE_DHCPV4_BASE_H
