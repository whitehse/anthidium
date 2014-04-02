#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "eonessa.h"

int eonessa_parse(const char* buf, unsigned n, int capture_type, struct eonessa* en) {
    if (n < EN_MIN_SNAPLEN || n > EN_MAX_SNAPLEN) {
        return EN_BAD_FRAME;
    }

    if (buf == NULL) {
        return EN_BAD_FRAME;
    }

    int i;
    uint16_t possible_ethertype = 0;
    int offset=0;
    int priority;
    int canonical_format;
    int vlan;
    uint32_t label;
    int cos;
    int stack_bit;
    int ttl;

    en->frame_size = n;
    en->capture_type = capture_type;
    memcpy (en->destination_mac, buf, 6);
    memcpy (en->source_mac, buf+6, 6);

    offset = 12;

    possible_ethertype = ntohs(*(uint16_t *) (buf+offset));

    for (i=0; i<32 && !en->done; i++) {
        switch (possible_ethertype) {
            case EN_ETHER_IPV4:
                en->payload_ethertype = EN_ETHER_IPV4;
                en->payload_pointer = buf+offset+2;
                en->payload_length = (n-(offset+2));
                en->done = 1;
                break;
            case EN_ETHER_ARP:
                en->payload_ethertype = EN_ETHER_ARP;
                en->payload_pointer = buf+offset+2;
                en->payload_length = (n-(offset+2));
                en->done = 1;
                break;
            case EN_ETHER_IS_IS:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_REVERSE_ARP:
                en->payload_ethertype = EN_ETHER_REVERSE_ARP;
                en->payload_pointer = buf+offset+2;
                en->payload_length = (n-(offset+2));
                en->done = 1;
                break;
            case EN_ETHER_VLAN_TAG_8100:
                if (offset+4 > n) return EN_BAD_FRAME;
                en->contents = en->contents | EN_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                en->vlan_tags[en->number_of_vlan_tags].priority = priority;
                en->vlan_tags[en->number_of_vlan_tags].canonical_format = canonical_format;
                en->vlan_tags[en->number_of_vlan_tags].vlan = vlan;
                en->vlan_tags[en->number_of_vlan_tags].tag_type = EN_ETHER_VLAN_TAG_8100;
                en->number_of_vlan_tags += 1;
                if (en->number_of_vlan_tags > EN_MAX_VLAN_TAGS) {
                    return EN_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EN_ETHER_IPV6:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_TCP_IP_COMPRESSION:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_IP_AUTONOMOUS_SYSTEMS:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_SECURE_DATA:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_LACP:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_PPP:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_VLAN_TAG_88A8:
                if (offset+4 > n) return EN_BAD_FRAME;
                en->contents = en->contents | EN_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                en->vlan_tags[en->number_of_vlan_tags].priority = priority;
                en->vlan_tags[en->number_of_vlan_tags].canonical_format = canonical_format;
                en->vlan_tags[en->number_of_vlan_tags].vlan = vlan;
                en->vlan_tags[en->number_of_vlan_tags].tag_type = EN_ETHER_VLAN_TAG_88A8;
                en->number_of_vlan_tags += 1;
                if (en->number_of_vlan_tags > EN_MAX_VLAN_TAGS) {
                    return EN_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EN_ETHER_MPLS:
                if (offset+6 > n) return EN_BAD_FRAME;
                en->contents = en->contents | EN_CONTAINS_MPLS_TAGS;
                offset += 2;
                do {
                    if (offset+4 > n) return EN_BAD_FRAME;
                    label = (ntohs(*(uint16_t *)(buf+offset)) << 4) +
                        (((*(uint8_t*)(buf+offset+2)) & 0xf0) >> 4);
                    cos = ((*(uint8_t*)(buf+offset+2)) & 0x0e) >> 1;
                    stack_bit = (*(uint8_t*)(buf+offset+2)) & 0x01;
                    ttl = (*(uint8_t*)(buf+offset+3));
                    en->mpls_tags[en->number_of_mpls_tags].label = label;
                    en->mpls_tags[en->number_of_mpls_tags].cos = cos;
                    en->mpls_tags[en->number_of_mpls_tags].stack_bit = stack_bit;
                    en->mpls_tags[en->number_of_mpls_tags].ttl = ttl;
                    en->number_of_mpls_tags += 1;
                    if (en->number_of_mpls_tags > EN_MAX_MPLS_TAGS) {
                        return EN_BAD_FRAME;
                    }
                    offset += 4;
                } while (stack_bit == 0);
                en->payload_pointer = buf+offset;
                en->payload_length = n-offset;
                en->payload_ethertype = EN_ETHER_UNKNOWN;
                en->done = 1;
                break;
            case EN_ETHER_MPLS_UPSTREAM_LABEL:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_PPPOE_DISCOVERY:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_PPPOE_SESSION:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_802_DOT_1X:
                return EN_BAD_FRAME;
                break;
            case EN_ETHER_VLAN_TAG_9100:
                if (offset+4 > n) return EN_BAD_FRAME;
                en->contents = en->contents | EN_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                en->vlan_tags[en->number_of_vlan_tags].priority = priority;
                en->vlan_tags[en->number_of_vlan_tags].canonical_format = canonical_format;
                en->vlan_tags[en->number_of_vlan_tags].vlan = vlan;
                en->vlan_tags[en->number_of_vlan_tags].tag_type = EN_ETHER_VLAN_TAG_9100;
                en->number_of_vlan_tags += 1;
                if (en->number_of_vlan_tags > EN_MAX_VLAN_TAGS) {
                    return EN_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EN_ETHER_VLAN_TAG_9200:
                if (offset+4 > n) return EN_BAD_FRAME;
                en->contents = en->contents | EN_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                en->vlan_tags[en->number_of_vlan_tags].priority = priority;
                en->vlan_tags[en->number_of_vlan_tags].canonical_format = canonical_format;
                en->vlan_tags[en->number_of_vlan_tags].vlan = vlan;
                en->vlan_tags[en->number_of_vlan_tags].tag_type = EN_ETHER_VLAN_TAG_9200;
                en->number_of_vlan_tags += 1;
                if (en->number_of_vlan_tags > EN_MAX_VLAN_TAGS) {
                    return EN_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EN_ETHER_VLAN_TAG_9300:
                if (offset+4 > n) return EN_BAD_FRAME;
                en->contents = en->contents | EN_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                en->vlan_tags[en->number_of_vlan_tags].priority = priority;
                en->vlan_tags[en->number_of_vlan_tags].canonical_format = canonical_format;
                en->vlan_tags[en->number_of_vlan_tags].vlan = vlan;
                en->vlan_tags[en->number_of_vlan_tags].tag_type = EN_ETHER_VLAN_TAG_9300;
                en->number_of_vlan_tags += 1;
                if (en->number_of_vlan_tags > EN_MAX_VLAN_TAGS) {
                    return EN_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EN_ETHER_RESERVED:
                return EN_BAD_FRAME;
                break;
            default:
                /* Other ethertype, or unrecognized format */
                if (possible_ethertype > 1500) {
                    return EN_BAD_FRAME;
                }

                /* This is an 802.3 frame */
                en->contents = en->contents | EN_CONTAINS_802_DOT_3_LENGTH;
                en->dot_3_length = possible_ethertype;
                offset += 2;

                if (offset+4 > n) return EN_BAD_FRAME;
                /* Check for LLC */
                uint16_t llc_destination_sap = ntohs(*(uint16_t *) (buf+offset));
                uint16_t llc_source_sap      = ntohs(*(uint16_t *) (buf+offset+2));

                /* IPX Raw 802.3 frame? */
                if (llc_destination_sap == 0xff && llc_source_sap == 0xff) {
                    en->contents = en->contents | EN_CONTAINS_IPX_RAW_802_DOT_3;
                    en->payload_ethertype = EN_ETHER_RESERVED;
                    en->payload_pointer = offset;
                    en->payload_length = (n-offset);
                    en->done = 1;
                    goto out;
                }

                /* Does have LLC */
                en->contents = en->contents | EN_CONTAINS_LLC_HEADER;
                en->llc_destination_sap = llc_destination_sap;
                en->llc_source_sap      = llc_source_sap;

                /* Is this an unnumbered (U-Format/1 byte) PDU? */
                if ( (*(uint8_t *)(buf+offset+3)) & 3) {
                    en->llc_control = *(uint8_t *)(buf + offset+3);
                    offset += 3;
                } else {
                    en->contents = en->contents | EN_CONTAINS_2_BYTE_LLC_CONTROL;
                    en->llc_control = ntohs(*(uint16_t *)(buf+offset+3));
                    offset += 4;
                }

                if (offset+5 > n) return EN_BAD_FRAME;
                /* Is SNAP service requested? */
                if ((llc_destination_sap == 0xaa || llc_destination_sap == 0xab) &&
                   (llc_source_sap == 0xaa || llc_source_sap == 0xab)) {

                    en->contents = en->contents | EN_CONTAINS_SNAP_HEADER;
                    memcpy (en->snap_oui, buf+offset, 3);
                    en->snap_sub_protocol = ntohs(*(uint16_t *)(buf+offset+3));
                    offset += 3;
                } else {   /* aw snap!, there's no SNAP. Don't know what to do */
                   return EN_BAD_FRAME; 
                }

                /* RFC 1042 ethertype SNAP? */
                if (en->llc_control == 3 && en->snap_oui[0] == 0 &&
                   en->snap_oui[1] == 0 && en->snap_oui[2]) {
                    possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                } else {
                    return EN_BAD_FRAME;
                }
            /* End of Default Case */
        }
    }

out:
    return EN_OK;
}
