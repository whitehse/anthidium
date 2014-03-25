
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

#ifndef EONESSA_IP_H
#define EONESSA_IP_H

/* Return types */
/*#define EN_OK               0
#define EN_FAIL            -1
#define EN_NOMEM           -2
#define EN_BUFOVER         -3
#define EN_BADPARAM        -4
#define EN_BAD_FRAME       -5*/
#define EN_BAD_PACKET      -6 /* Invalid Packet */
#define EN_BAD_UDP_MESSAGE -7 /* Invalid UDP Message */
#define EN_BAD_TCP_MESSAGE -8 /* Invalid TCP Message */

#define EN_MIN_IPV4_PACKET_SIZE 20
#define EN_MAX_IPV4_PACKET_SIZE 65535

/* Packet types */
#define EN_IPV4 1
#define EN_ARP  2
#define EN_RARP 4
#define EN_IPV6 8

/* ARP Hardward Type */
#define EN_ARP_HW_RESERVED_0      0
#define EN_ARP_HW_ETHERNET        1
#define EN_ARP_HW_EXP_ETH         2
#define EN_ARP_HW_AXDOT25         3
#define EN_ARP_HW_PRONET          4
#define EN_ARP_HW_CHAOS           5
#define EN_ARP_HW_IEEE802         6
#define EN_ARP_HW_ARCNET          7
#define EN_ARP_HW_HYPERCHANNEL    8
#define EN_ARP_HW_LANSTAR         9
#define EN_ARP_HW_AUTONET         10
#define EN_ARP_HW_LOCALTALK       11
#define EN_ARP_HW_LOCALNET        12
#define EN_ARP_HW_ULTRALINK       13
#define EN_ARP_HW_SMDS            14
#define EN_ARP_HW_FRAME_RELAY     15
#define EN_ARP_HW_ATM_16          16
#define EN_ARP_HW_HDLC            17
#define EN_ARP_HW_FIBRE_CHANNEL   18
#define EN_ARP_HW_ATM_19          19
#define EN_ARP_HW_SERIAL_LINE     20
#define EN_ARP_HW_ATM_21          21
#define EN_ARP_HW_MIL_STD         22
#define EN_ARP_HW_METRICOM        23
#define EN_ARP_HW_IEEE_1394       24
#define EN_ARP_HW_MAPOS           25
#define EN_ARP_HW_TWINAXIAL       26
#define EN_ARP_HW_EUI_64          27
#define EN_ARP_HW_HIPARP          28
#define EN_ARP_HW_IPARP_OVER_ISO  29
#define EN_ARP_HW_ARPSEC          30
#define EN_ARP_HW_IPSEC_TUNNEL    31
#define EN_ARP_HW_INFINIBAND      32
#define EN_ARP_HW_CAI_TAI         33
#define EN_ARP_HW_WIEGAND         34
#define EN_ARP_HW_PUR_IP          35
#define EN_ARP_HW_HW_EXP1         36
#define EN_ARP_HW_HW_EXP2         256
#define EN_ARP_HW_RESERVERD_65534 65534

#define EN_ARP_PROT_IP            0x0800

#define EN_ARP_OP_RESERVED_0         0
#define EN_ARP_OP_REQUEST            1
#define EN_ARP_OP_REPLY              2
#define EN_ARP_OP_REQUEST_REVERSE    3
#define EN_ARP_OP_REPLY_REVERSE      4
#define EN_ARP_OP_DRARP_REQUEST      5
#define EN_ARP_OP_DRARP_REPLY        6
#define EN_ARP_OP_DRARP_ERROR        7
#define EN_ARP_OP_INARP_REQUEST      8
#define EN_ARP_OP_INARP_REPLY        9
#define EN_ARP_OP_ARP_NAK            10
#define EN_ARP_OP_MARS_REQUEST       11
#define EN_ARP_OP_MARK_MULTI         12
#define EN_ARP_OP_MARS_MSERV         13
#define EN_ARP_OP_MARS_JOIN          14
#define EN_ARP_OP_MARS_LEAVE         15
#define EN_ARP_OP_MARS_NAK           16
#define EN_ARP_OP_MARS_UNSERV        17
#define EN_ARP_OP_MARS_SJOIN         18
#define EN_ARP_OP_MARS_SLEAVE        19
#define EN_ARP_OP_MARS_GROUPLIST_REQ 20
#define EN_ARP_OP_MARS_GROUPLIST_REP 21
#define EN_ARP_OP_MARS_REDIRECT_MAP  22
#define EN_ARP_OP_MAPOS              23
#define EN_ARP_OP_OP_EXP1            24
#define EN_ARP_OP_OP_EXP2            25

/* IP Protocol Field */
#define EN_PROT_HOPOPT          0x00
#define EN_PROT_ICMP            0x01
#define EN_PROT_IGMP            0x02
#define EN_PROT_GGP             0x03
#define EN_PROT_IP              0x04
#define EN_PROT_ST              0x05
#define EN_PROT_TCP             0x06
#define EN_PROT_CBT             0x07
#define EN_PROT_EGP             0x08
#define EN_PROT_IGP             0x09
#define EN_PROT_BBN_RCC_MON     0x0a
#define EN_PROT_NVP_II          0x0b
#define EN_PROT_PUP             0x0c
#define EN_PROT_ARGUS           0x0d
#define EN_PROT_EMCON           0x0e
#define EN_PROT_XNET            0x0f
#define EN_PROT_CHAOS           0x10
#define EN_PROT_UDP             0x11
#define EN_PROT_MUX             0x12
#define EN_PROT_DCN_MEAS        0x13
#define EN_PROT_HMP             0x14
#define EN_PROT_PRM             0x15
#define EN_PROT_XNS_IDP         0x16
#define EN_PROT_TRUNK_1         0x17
#define EN_PROT_TRUNK_2         0x18
#define EN_PROT_LEAF_1          0x19
#define EN_PROT_LEAF_2          0x1a
#define EN_PROT_RDP             0x1b
#define EN_PROT_IRTP            0x1c
#define EN_PROT_ISO_TP4         0x1d
#define EN_PROT_NETBLT          0x1e
#define EN_PROT_MFE_NSP         0x1f
#define EN_PROT_MERIT_INP       0x20
#define EN_PROT_DCCP            0x21
#define EN_PROT_3PC             0x22
#define EN_PROT_IDPR            0x23
#define EN_PROT_XTP             0x24
#define EN_PROT_DDP             0x25
#define EN_PROT_IDPR_CMTP       0x26
#define EN_PROT_TPPLUSPLUS      0x27
#define EN_PROT_IL              0x28
#define EN_PROT_IPV6            0x29
#define EN_PROT_SDRP            0x2a
#define EN_PROT_IPV6_ROUTE      0x2b
#define EN_PROT_IPV6_FRAG       0x2c
#define EN_PROT_IDRP            0x2d
#define EN_PROT_RSVP            0x2e
#define EN_PROT_GRE             0x2f
#define EN_PROT_MHRP            0x30
#define EN_PROT_BNA             0x31
#define EN_PROT_ESP             0x32
#define EN_PROT_AH              0x33
#define EN_PROT_I_NLSP          0x34
#define EN_PROT_SWIPE           0x35
#define EN_PROT_NARP            0x36
#define EN_PROT_MOBILE          0x37
#define EN_PROT_TLSP            0x38
#define EN_PROT_SKIP            0x39
#define EN_PROT_IPV6_ICMP       0x3a
#define EN_PROT_IPV6_NONXT      0x3b
#define EN_PROT_IPV6_OPTS       0x3c
#define EN_PROT_INTERNAL        0x3d
#define EN_PROT_CFTP            0x3e
#define EN_PROT_LOCAL           0x3f
#define EN_PROT_SAT_EXPAK       0x40
#define EN_PROT_KRYPTOLAN       0x41
#define EN_PROT_RVD             0x42
#define EN_PROT_IPPC            0x43
#define EN_PROT_DIST_FILE_SYS   0x44
#define EN_PROT_SAT_MON         0x45
#define EN_PROT_VISA            0x46
#define EN_PROT_IPCV            0x47
#define EN_PROT_CPNX            0x48
#define EN_PROT_CPHB            0x49
#define EN_PROT_WSN             0x4a
#define EN_PROT_PVP             0x4b
#define EN_PROT_BR_SAT_MON      0x4c
#define EN_PROT_SUN_ND          0x4d
#define EN_PROT_WB_MON          0x4e
#define EN_PROT_WB_EXPAK        0x4f
#define EN_PROT_ISO_IP          0x50
#define EN_PROT_VMTP            0x51
#define EN_PROT_SECURE_VMTP     0x52
#define EN_PROT_VINES           0x53
#define EN_PROT_TTP             0x54
#define EN_PROT_IPTM            0x54 /* Same as TTP */
#define EN_PROT_NSFNET_IGP      0x55
#define EN_PROT_DGP             0x56
#define EN_PROT_TCF             0x57
#define EN_PROT_EIGRP           0x58
#define EN_PROT_OSPF            0x59
#define EN_PROT_SPRITE_RPC      0x5a
#define EN_PROT_LARP            0x5b
#define EN_PROT_MTP             0x5c
#define EN_PROT_AX_DOT_25       0x5d
#define EN_PROT_IPIP            0x5e
#define EN_PROT_MICP            0x5f
#define EN_PROT_SCC_SP          0x60
#define EN_PROT_ETHERIP         0x61
#define EN_PROT_ENCAP           0x62
#define EN_PROT_PRIV_ENCRYPT    0x63
#define EN_PROT_GMTP            0x64
#define EN_PROT_IFMP            0x65
#define EN_PROT_PNNI            0x66
#define EN_PROT_PIM             0x67
#define EN_PROT_ARIS            0x68
#define EN_PROT_SCPS            0x69
#define EN_PROT_QNX             0x6a
#define EN_PROT_A_SLASH_N       0x6b
#define EN_PROT_IPCOMP          0x6c
#define EN_PROT_SNP             0x6d
#define EN_PROT_COMPAQ_PEER     0x6e
#define EN_PROT_IPX_IN_IP       0x6f
#define EN_PROT_VRRP            0x70
#define EN_PROT_PGM             0x71
#define EN_PROT_ZERO_HOP_PROT   0x72
#define EN_PROT_L2TP            0x73
#define EN_PROT_DDX             0x74
#define EN_PROT_IATP            0x75
#define EN_PROT_STP             0x76
#define EN_PROT_SRP             0x77
#define EN_PROT_UTI             0x78
#define EN_PROT_SMP             0x79
#define EN_PROT_SM              0x7a
#define EN_PROT_PTP             0x7b
#define EN_PROT_IS_IS_OVER_IPV4 0x7c
#define EN_PROT_FIRE            0x7d
#define EN_PROT_CRTP            0x7e
#define EN_PROT_CRUDP           0x7f
#define EN_PROT_SSCOPMCE        0x80
#define EN_PROT_IPLT            0x81
#define EN_PROT_SPS             0x82
#define EN_PROT_PIPE            0x83
#define EN_PROT_SCTP            0x84
#define EN_PROT_FC              0x85
#define EN_PROT_RSVP_E2E_IGNORE 0x86
#define EN_PROT_MOBILITY_HEADER 0x87
#define EN_PROT_UDP_LITE        0x88
#define EN_PROT_MPLS_IN_IP      0x89
#define EN_PROT_MANET           0x8a
#define EN_PROT_HIP             0x8b
#define EN_PROT_SHIM6           0x8c
#define EN_PROT_RESERVED        0xff

#define EN_OPT_COPY        0x00
#define EN_OPT_DO_NOT_COPY 0x01

#define EN_OPT_CLASS_CONTROL  0x00
#define EN_OPT_CLASS_DEBUG    0x02

#define EN_MAX_IPV4_HEADERS 40
#define EN_MAX_TCP_HEADERS  40

#define EN_OPT_END_OF_LIST             0 /* Documentation uses decimal */
#define EN_OPT_NOP                     1
#define EN_OPT_RECORD_ROUTE            7
#define EN_OPT_EXPERIMENTAL_MEASURE    10
#define EN_OPT_MTU_PROBE               11
#define EN_OPT_MTU_REPLY               12
#define EN_OPT_ENCODE                  15
#define EN_OPT_QUICK_START             25
#define EN_OPT_RFC3692_EXPERIMENTAL_1  30
#define EN_OPT_TIME_STAMP              68
#define EN_OPT_TRACEROUTE              82
#define EN_OPT_RFC3692_EXPERIMENTAL_2  94
#define EN_OPT_SECURITY                130
#define EN_OPT_LOOSE_SOURCE_ROUTE      131
#define EN_OPT_EXTENDED_SECURITY       133
#define EN_OPT_COMMERCIAL_SECURITY     134
#define EN_OPT_STREAM_IDENTIFIER       136
#define EN_OPT_STRICT_SOURCE_ROUTE     137
#define EN_OPT_EXP_ACCESS_CONTROL      142
#define EN_OPT_IMI_TRAFFIC_DESCRIPTOR  144
#define EN_OPT_EXTENDED_IP             145
#define EN_OPT_ADDRESS_EXTENTION       147
#define EN_OPT_ROUTER_ALERT            148
#define EN_OPT_SELECTIVE_DIRECTED_BC   149
#define EN_OPT_UNKNOWN_SIMPLE_1        150
#define EN_OPT_DYNAMIC_PACKET_STATE    151
#define EN_OPT_UPSTREAM_MULTICAST      152
#define EN_OPT_RFC3692_EXPERIMENTAL_3  158
#define EN_OPT_EXP_FLOW_CONTROL        205
#define EN_OPT_RFC3692_EXPERIMENTAL_4  222

#define EN_TCP_OPT_END_OF_LIST           0 /* Documentation uses decimal */
#define EN_TCP_OPT_NOP                   1
#define EN_TCP_OPT_MAX_SEGMENT_SIZE      2
#define EN_TCP_OPT_WSOPT                 3
#define EN_TCP_OPT_SACK_PERMITTED        4
#define EN_TCP_OPT_SACK                  5
#define EN_TCP_OPT_ECHO                  6
#define EN_TCP_OPT_ECHO_REPLY            7
#define EN_TCP_OPT_TSOPT                 8
#define EN_TCP_OPT_PARTIAL_ORDER_CONNECT 9
#define EN_TCP_OPT_PARTIAL_ORDER_SERVICE 10
#define EN_TCP_OPT_CC                    11
#define EN_TCP_OPT_CC_NEW                12
#define EN_TCP_OPT_CC_ECHO               13
#define EN_TCP_OPT_TCP_ALT_CHECKSUM_REQ  14
#define EN_TCP_OPT_TCP_ALT_CHECKSUM_DATA 15
#define EN_TCP_OPT_SKEETER               16
#define EN_TCP_OPT_BUBBA                 17
#define EN_TCP_OPT_TRAILER_CHECKSUM_OPT  18
#define EN_TCP_OPT_MD5_SIGNATURE_OPT     19
#define EN_TCP_OPT_SCPS                  20
#define EN_TCP_OPT_SELECT_NEGATIVE_ACKS  21
#define EN_TCP_OPT_RECORD_BOUNDARIES     22
#define EN_TCP_OPT_CORRUPTED_EXPERIENCED 23
#define EN_TCP_OPT_SNAP                  24
#define EN_TCP_OPT_UNASSIGNED_25         25
#define EN_TCP_OPT_COMPRESSION_FILTER    26
#define EN_TCP_OPT_QUICK_START_RESPONSE  27
#define EN_TCP_OPT_USER_TIMEOUT_OPT      28
#define EN_TCP_OPT_AUTHENTICATION_OPT    29
#define EN_TCP_OPT_RFC3692_EXP_1         253
#define EN_TCP_OPT_RFC3692_EXP_2         254

#define EN_IPV4_PARSE_FAIL_ON_INVALID_LENGTH 1

struct eonessa_arp {
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t hardware_address_length;
    uint8_t protocol_address_length;
    uint16_t opcode;
    
};

struct eonessa_ipv4_header_option {
    int copy_flag;
    int class_type;
    int number;
    char data_pointer;
    int length;
};

struct eonessa_ipv4 {
    int packet_size;
    int version;
    int header_length;
    int dscp;
    int ecn;
    int total_length;
    int identification;
    int flags;
    int fragment_offset;
    int ttl;
    int protocol;
    int checksum;       /* Host byte order */
    uint32_t source_ip;      /* Host byte order */
    uint32_t destination_ip; /* Host byte order */
    char source_ip_decimal[16];
    char destination_ip_decimal[16];
    int number_of_options;
    struct eonessa_ipv4_header_option header_options[EN_MAX_IPV4_HEADERS];
    int payload_length;
    char* payload_pointer;
    int fail_codes;
};

#define EN_MIN_UDP_SIZE 8
#define EN_MAX_UDP_SIZE 65507

struct eonessa_udp {
    int message_size;      /* All are in host byte order */
    uint16_t source_port;
    uint16_t destination_port;
    uint16_t length;
    uint16_t checksum;
    int payload_length;
    char* payload_pointer;
};

#define EN_MIN_TCP_SIZE 20
#define EN_MAX_TCP_SIZE 65495

#define EN_TCP_FLAG_FIN 1
#define EN_TCP_FLAG_SYN 2
#define EN_TCP_FLAG_RST 4
#define EN_TCP_FLAG_PSH 8
#define EN_TCP_FLAG_ACK 16
#define EN_TCP_FLAG_URG 32
#define EN_TCP_FLAG_ECE 64
#define EN_TCP_FLAG_CWR 128

struct eonessa_tcp_header_option {
    int number;
    char data_pointer;
    int length;         /* length includes the above two bytes */
};

struct eonessa_tcp {
    int message_size;      /* All are in host byte order */
    uint16_t source_port;
    uint16_t destination_port;
    uint32_t sequence_number;
    uint32_t acknowledgement_number;
    int data_offset;
    int flags;
    uint16_t window_size;
    uint16_t checksum;
    uint16_t urgent_pointer;
    int number_of_options;
    struct eonessa_tcp_header_option header_options[EN_MAX_TCP_HEADERS];
    int payload_length;
    char* payload_pointer;
};

#define EN_TCP_STATE_CLOSED       0
#define EN_TCP_STATE_SYN_SENT     1
#define EN_TCP_STATE_SYN_RECEIVED 2
#define EN_TCP_STATE_ESTABLISHED  3
#define EN_TCP_STATE_FIN_WAIT_1   4
#define EN_TCP_STATE_FIN_WAIT_2   5
#define EN_TCP_STATE_CLOSE_WAIT   6
#define EN_TCP_STATE_CLOSING      7
#define EN_TCP_STATE_LAST_ACK     8
#define EN_TCP_STATE_TIME_WAIT    9

#define EN_MAX_ETHER_HEADERS 8

struct eonessa_clump {
    int number_of_ether_headers;
    struct eonessa *eonessa[EN_MAX_ETHER_HEADERS];
    struct eonessa_arp *arp;
    struct eonessa_ipv4 *ipv4;
    struct eonessa_udp *udp;
    struct eonessa_tcp *tcp;
};

int eonessa_parse_ipv4(const char* buf, unsigned n, struct eonessa_ipv4*, int flags);
int eonessa_parse_udp(const char* buf, unsigned n, struct eonessa_udp*, int flags);
int eonessa_parse_tcp(const char* buf, unsigned n, struct eonessa_tcp*, int flags);

typedef int (*sub_eonessa_parse)(struct eonessa_clump *clump);

#endif // EONESSA_IP_H
