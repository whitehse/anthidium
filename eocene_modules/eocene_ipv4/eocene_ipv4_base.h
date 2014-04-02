
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

#ifndef EOCENE_IPV4_BASE_H
#define EOCENE_IPV4_BASE_H

/* Return types. But only use these internally! */
/* Use, for example, EC_OK, when returning from public
 * functions. */
#define EC_IPV4_OK               0 /* successful result */
#define EC_IPV4_FAIL            -1 /* generic failure */
#define EC_IPV4_NOMEM           -2 /* memory shortage failure */
#define EC_IPV4_BUFOVER         -3 /* overflowed buffer */
#define EC_IPV4_BADPARAM        -4 /* invalid parameter supplied */
#define EC_IPV4_BAD_DATA        -5 /* Invalid Packet */

#define EC_IPV4_BAD_PACKET      -6 /* Invalid Packet */
#define EC_IPV4_BAD_UDP_MESSAGE -7 /* Invalid UDP Message */
#define EC_IPV4_BAD_TCP_MESSAGE -8 /* Invalid TCP Message */

#define EC_IPV4_MIN_PACKET_SIZE 20
#define EC_IPV4_MAX_PACKET_SIZE 65535

/* IP Protocol Field */
#define EC_IPV4_PROT_HOPOPT          0x00
#define EC_IPV4_PROT_ICMP            0x01
#define EC_IPV4_PROT_IGMP            0x02
#define EC_IPV4_PROT_GGP             0x03
#define EC_IPV4_PROT_IP              0x04
#define EC_IPV4_PROT_ST              0x05
#define EC_IPV4_PROT_TCP             0x06
#define EC_IPV4_PROT_CBT             0x07
#define EC_IPV4_PROT_EGP             0x08
#define EC_IPV4_PROT_IGP             0x09
#define EC_IPV4_PROT_BBN_RCC_MON     0x0a
#define EC_IPV4_PROT_NVP_II          0x0b
#define EC_IPV4_PROT_PUP             0x0c
#define EC_IPV4_PROT_ARGUS           0x0d
#define EC_IPV4_PROT_EMCON           0x0e
#define EC_IPV4_PROT_XNET            0x0f
#define EC_IPV4_PROT_CHAOS           0x10
#define EC_IPV4_PROT_UDP             0x11
#define EC_IPV4_PROT_MUX             0x12
#define EC_IPV4_PROT_DCN_MEAS        0x13
#define EC_IPV4_PROT_HMP             0x14
#define EC_IPV4_PROT_PRM             0x15
#define EC_IPV4_PROT_XNS_IDP         0x16
#define EC_IPV4_PROT_TRUNK_1         0x17
#define EC_IPV4_PROT_TRUNK_2         0x18
#define EC_IPV4_PROT_LEAF_1          0x19
#define EC_IPV4_PROT_LEAF_2          0x1a
#define EC_IPV4_PROT_RDP             0x1b
#define EC_IPV4_PROT_IRTP            0x1c
#define EC_IPV4_PROT_ISO_TP4         0x1d
#define EC_IPV4_PROT_NETBLT          0x1e
#define EC_IPV4_PROT_MFE_NSP         0x1f
#define EC_IPV4_PROT_MERIT_INP       0x20
#define EC_IPV4_PROT_DCCP            0x21
#define EC_IPV4_PROT_3PC             0x22
#define EC_IPV4_PROT_IDPR            0x23
#define EC_IPV4_PROT_XTP             0x24
#define EC_IPV4_PROT_DDP             0x25
#define EC_IPV4_PROT_IDPR_CMTP       0x26
#define EC_IPV4_PROT_TPPLUSPLUS      0x27
#define EC_IPV4_PROT_IL              0x28
#define EC_IPV4_PROT_IPV6            0x29
#define EC_IPV4_PROT_SDRP            0x2a
#define EC_IPV4_PROT_IPV6_ROUTE      0x2b
#define EC_IPV4_PROT_IPV6_FRAG       0x2c
#define EC_IPV4_PROT_IDRP            0x2d
#define EC_IPV4_PROT_RSVP            0x2e
#define EC_IPV4_PROT_GRE             0x2f
#define EC_IPV4_PROT_MHRP            0x30
#define EC_IPV4_PROT_BNA             0x31
#define EC_IPV4_PROT_ESP             0x32
#define EC_IPV4_PROT_AH              0x33
#define EC_IPV4_PROT_I_NLSP          0x34
#define EC_IPV4_PROT_SWIPE           0x35
#define EC_IPV4_PROT_NARP            0x36
#define EC_IPV4_PROT_MOBILE          0x37
#define EC_IPV4_PROT_TLSP            0x38
#define EC_IPV4_PROT_SKIP            0x39
#define EC_IPV4_PROT_IPV6_ICMP       0x3a
#define EC_IPV4_PROT_IPV6_NONXT      0x3b
#define EC_IPV4_PROT_IPV6_OPTS       0x3c
#define EC_IPV4_PROT_INTERNAL        0x3d
#define EC_IPV4_PROT_CFTP            0x3e
#define EC_IPV4_PROT_LOCAL           0x3f
#define EC_IPV4_PROT_SAT_EXPAK       0x40
#define EC_IPV4_PROT_KRYPTOLAN       0x41
#define EC_IPV4_PROT_RVD             0x42
#define EC_IPV4_PROT_IPPC            0x43
#define EC_IPV4_PROT_DIST_FILE_SYS   0x44
#define EC_IPV4_PROT_SAT_MON         0x45
#define EC_IPV4_PROT_VISA            0x46
#define EC_IPV4_PROT_IPCV            0x47
#define EC_IPV4_PROT_CPNX            0x48
#define EC_IPV4_PROT_CPHB            0x49
#define EC_IPV4_PROT_WSN             0x4a
#define EC_IPV4_PROT_PVP             0x4b
#define EC_IPV4_PROT_BR_SAT_MON      0x4c
#define EC_IPV4_PROT_SUN_ND          0x4d
#define EC_IPV4_PROT_WB_MON          0x4e
#define EC_IPV4_PROT_WB_EXPAK        0x4f
#define EC_IPV4_PROT_ISO_IP          0x50
#define EC_IPV4_PROT_VMTP            0x51
#define EC_IPV4_PROT_SECURE_VMTP     0x52
#define EC_IPV4_PROT_VINES           0x53
#define EC_IPV4_PROT_TTP             0x54
#define EC_IPV4_PROT_IPTM            0x54 /* Same as TTP */
#define EC_IPV4_PROT_NSFNET_IGP      0x55
#define EC_IPV4_PROT_DGP             0x56
#define EC_IPV4_PROT_TCF             0x57
#define EC_IPV4_PROT_EIGRP           0x58
#define EC_IPV4_PROT_OSPF            0x59
#define EC_IPV4_PROT_SPRITE_RPC      0x5a
#define EC_IPV4_PROT_LARP            0x5b
#define EC_IPV4_PROT_MTP             0x5c
#define EC_IPV4_PROT_AX_DOT_25       0x5d
#define EC_IPV4_PROT_IPIP            0x5e
#define EC_IPV4_PROT_MICP            0x5f
#define EC_IPV4_PROT_SCC_SP          0x60
#define EC_IPV4_PROT_ETHERIP         0x61
#define EC_IPV4_PROT_ENCAP           0x62
#define EC_IPV4_PROT_PRIV_ENCRYPT    0x63
#define EC_IPV4_PROT_GMTP            0x64
#define EC_IPV4_PROT_IFMP            0x65
#define EC_IPV4_PROT_PNNI            0x66
#define EC_IPV4_PROT_PIM             0x67
#define EC_IPV4_PROT_ARIS            0x68
#define EC_IPV4_PROT_SCPS            0x69
#define EC_IPV4_PROT_QNX             0x6a
#define EC_IPV4_PROT_A_SLASH_N       0x6b
#define EC_IPV4_PROT_IPCOMP          0x6c
#define EC_IPV4_PROT_SNP             0x6d
#define EC_IPV4_PROT_COMPAQ_PEER     0x6e
#define EC_IPV4_PROT_IPX_IN_IP       0x6f
#define EC_IPV4_PROT_VRRP            0x70
#define EC_IPV4_PROT_PGM             0x71
#define EC_IPV4_PROT_ZERO_HOP_PROT   0x72
#define EC_IPV4_PROT_L2TP            0x73
#define EC_IPV4_PROT_DDX             0x74
#define EC_IPV4_PROT_IATP            0x75
#define EC_IPV4_PROT_STP             0x76
#define EC_IPV4_PROT_SRP             0x77
#define EC_IPV4_PROT_UTI             0x78
#define EC_IPV4_PROT_SMP             0x79
#define EC_IPV4_PROT_SM              0x7a
#define EC_IPV4_PROT_PTP             0x7b
#define EC_IPV4_PROT_IS_IS_OVER_IPV4 0x7c
#define EC_IPV4_PROT_FIRE            0x7d
#define EC_IPV4_PROT_CRTP            0x7e
#define EC_IPV4_PROT_CRUDP           0x7f
#define EC_IPV4_PROT_SSCOPMCE        0x80
#define EC_IPV4_PROT_IPLT            0x81
#define EC_IPV4_PROT_SPS             0x82
#define EC_IPV4_PROT_PIPE            0x83
#define EC_IPV4_PROT_SCTP            0x84
#define EC_IPV4_PROT_FC              0x85
#define EC_IPV4_PROT_RSVP_E2E_IGNORE 0x86
#define EC_IPV4_PROT_MOBILITY_HEADER 0x87
#define EC_IPV4_PROT_UDP_LITE        0x88
#define EC_IPV4_PROT_MPLS_IN_IP      0x89
#define EC_IPV4_PROT_MANET           0x8a
#define EC_IPV4_PROT_HIP             0x8b
#define EC_IPV4_PROT_SHIM6           0x8c
#define EC_IPV4_PROT_RESERVED        0xff

#define EC_IPV4_OPT_COPY        0x00
#define EC_IPV4_OPT_DO_NOT_COPY 0x01

#define EC_IPV4_OPT_CLASS_CONTROL  0x00
#define EC_IPV4_OPT_CLASS_DEBUG    0x02

#define EC_IPV4_MAX_HEADERS 40

#define EC_IPV4_OPT_END_OF_LIST             0 /* Documentation uses decimal */
#define EC_IPV4_OPT_NOP                     1
#define EC_IPV4_OPT_RECORD_ROUTE            7
#define EC_IPV4_OPT_EXPERIMENTAL_MEASURE    10
#define EC_IPV4_OPT_MTU_PROBE               11
#define EC_IPV4_OPT_MTU_REPLY               12
#define EC_IPV4_OPT_ENCODE                  15
#define EC_IPV4_OPT_QUICK_START             25
#define EC_IPV4_OPT_RFC3692_EXPERIMENTAL_1  30
#define EC_IPV4_OPT_TIME_STAMP              68
#define EC_IPV4_OPT_TRACEROUTE              82
#define EC_IPV4_OPT_RFC3692_EXPERIMENTAL_2  94
#define EC_IPV4_OPT_SECURITY                130
#define EC_IPV4_OPT_LOOSE_SOURCE_ROUTE      131
#define EC_IPV4_OPT_EXTENDED_SECURITY       133
#define EC_IPV4_OPT_COMMERCIAL_SECURITY     134
#define EC_IPV4_OPT_STREAM_IDENTIFIER       136
#define EC_IPV4_OPT_STRICT_SOURCE_ROUTE     137
#define EC_IPV4_OPT_EXP_ACCESS_CONTROL      142
#define EC_IPV4_OPT_IMI_TRAFFIC_DESCRIPTOR  144
#define EC_IPV4_OPT_EXTENDED_IP             145
#define EC_IPV4_OPT_ADDRESS_EXTENTION       147
#define EC_IPV4_OPT_ROUTER_ALERT            148
#define EC_IPV4_OPT_SELECTIVE_DIRECTED_BC   149
#define EC_IPV4_OPT_UNKNOWN_SIMPLE_1        150
#define EC_IPV4_OPT_DYNAMIC_PACKET_STATE    151
#define EC_IPV4_OPT_UPSTREAM_MULTICAST      152
#define EC_IPV4_OPT_RFC3692_EXPERIMENTAL_3  158
#define EC_IPV4_OPT_EXP_FLOW_CONTROL        205
#define EC_IPV4_OPT_RFC3692_EXPERIMENTAL_4  222

#define EC_IPV4_PARSE_FAIL_ON_INVALID_LENGTH 1

struct ec_ipv4_header_option {
    int copy_flag;
    int class_type;
    int number;
    char data_pointer;
    int length;
};

struct ec_ipv4 {
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
    struct ec_ipv4_header_option header_options[EC_IPV4_MAX_HEADERS];
    int payload_length;
    char* payload_pointer;
    int fail_codes;
};

char* ipv4_source_ip_in_decimal (struct ec_ipv4* ipv4);
char* ipv4_destination_ip_in_decimal (struct ec_ipv4* ipv4);


#endif // EOCENE_IPV4_BASE_H
