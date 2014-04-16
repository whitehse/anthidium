#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eocene.h>
#include "eocene_ethernet.h"

#define init eocene_ethernet_LTX_init
#define parse eocene_ethernet_LTX_parse

eocene_ethernet_listener *ethernet_listeners[EC_ETH_MAX_LISTENERS];
int number_of_ethernet_listeners = 0;

int init(config_setting_t *config, struct es_state *_state) {
    return ES_OK;
}

int register_listener(void *callback) {
    ethernet_listeners[number_of_ethernet_listeners] = callback;
    number_of_ethernet_listeners += 1;
}

int parse(const char* buf, unsigned n, int capture_type) {
//    if (n < EC_ETH_MIN_SNAPLEN || n > EC_ETH_MAX_SNAPLEN) {
//        return EC_ETH_BAD_FRAME;
//    }

    if (buf == NULL) {
        return EC_ETH_BAD_FRAME;
    }

    struct ec_ethernet *frame;
    frame = (struct ec_ethernet*)malloc(sizeof(struct ec_ethernet));
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

    frame->frame_size = n;
    frame->capture_type = capture_type;
    memcpy (frame->destination_mac, buf, 6);
    memcpy (frame->source_mac, buf+6, 6);

    offset = 12;

    possible_ethertype = ntohs(*(uint16_t *) (buf+offset));

    for (i=0; i<32 && !frame->done; i++) {
        switch (possible_ethertype) {
            case EC_ETH_ETHER_IPV4:
                frame->payload_ethertype = EC_ETH_ETHER_IPV4;
                frame->payload_pointer = buf+offset+2;
                frame->payload_length = (n-(offset+2));
                frame->done = 1;
                break;
            case EC_ETH_ETHER_ARP:
                frame->payload_ethertype = EC_ETH_ETHER_ARP;
                frame->payload_pointer = buf+offset+2;
                frame->payload_length = (n-(offset+2));
                frame->done = 1;
                break;
            case EC_ETH_ETHER_IS_IS:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_REVERSE_ARP:
                frame->payload_ethertype = EC_ETH_ETHER_REVERSE_ARP;
                frame->payload_pointer = buf+offset+2;
                frame->payload_length = (n-(offset+2));
                frame->done = 1;
                break;
            case EC_ETH_ETHER_VLAN_TAG_8100:
                if (offset+4 > n) return EC_ETH_BAD_FRAME;
                frame->contents = frame->contents | EC_ETH_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                frame->vlan_tags[frame->number_of_vlan_tags].priority = priority;
                frame->vlan_tags[frame->number_of_vlan_tags].canonical_format = canonical_format;
                frame->vlan_tags[frame->number_of_vlan_tags].vlan = vlan;
                frame->vlan_tags[frame->number_of_vlan_tags].tag_type = EC_ETH_ETHER_VLAN_TAG_8100;
                frame->number_of_vlan_tags += 1;
                if (frame->number_of_vlan_tags > EC_ETH_MAX_VLAN_TAGS) {
                    return EC_ETH_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EC_ETH_ETHER_IPV6:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_TCP_IP_COMPRESSION:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_IP_AUTONOMOUS_SYSTEMS:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_SECURE_DATA:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_LACP:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_PPP:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_VLAN_TAG_88A8:
                if (offset+4 > n) return EC_ETH_BAD_FRAME;
                frame->contents = frame->contents | EC_ETH_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                frame->vlan_tags[frame->number_of_vlan_tags].priority = priority;
                frame->vlan_tags[frame->number_of_vlan_tags].canonical_format = canonical_format;
                frame->vlan_tags[frame->number_of_vlan_tags].vlan = vlan;
                frame->vlan_tags[frame->number_of_vlan_tags].tag_type = EC_ETH_ETHER_VLAN_TAG_88A8;
                frame->number_of_vlan_tags += 1;
                if (frame->number_of_vlan_tags > EC_ETH_MAX_VLAN_TAGS) {
                    return EC_ETH_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EC_ETH_ETHER_MPLS:
                if (offset+6 > n) return EC_ETH_BAD_FRAME;
                frame->contents = frame->contents | EC_ETH_CONTAINS_MPLS_TAGS;
                offset += 2;
                do {
                    if (offset+4 > n) return EC_ETH_BAD_FRAME;
                    label = (ntohs(*(uint16_t *)(buf+offset)) << 4) +
                        (((*(uint8_t*)(buf+offset+2)) & 0xf0) >> 4);
                    cos = ((*(uint8_t*)(buf+offset+2)) & 0x0e) >> 1;
                    stack_bit = (*(uint8_t*)(buf+offset+2)) & 0x01;
                    ttl = (*(uint8_t*)(buf+offset+3));
                    frame->mpls_tags[frame->number_of_mpls_tags].label = label;
                    frame->mpls_tags[frame->number_of_mpls_tags].cos = cos;
                    frame->mpls_tags[frame->number_of_mpls_tags].stack_bit = stack_bit;
                    frame->mpls_tags[frame->number_of_mpls_tags].ttl = ttl;
                    frame->number_of_mpls_tags += 1;
                    if (frame->number_of_mpls_tags > EC_ETH_MAX_MPLS_TAGS) {
                        return EC_ETH_BAD_FRAME;
                    }
                    offset += 4;
                } while (stack_bit == 0);
                frame->payload_pointer = buf+offset;
                frame->payload_length = n-offset;
                frame->payload_ethertype = EC_ETH_ETHER_UNKNOWN;
                frame->done = 1;
                break;
            case EC_ETH_ETHER_MPLS_UPSTREAM_LABEL:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_PPPOE_DISCOVERY:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_PPPOE_SESSION:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_802_DOT_1X:
                return EC_ETH_BAD_FRAME;
                break;
            case EC_ETH_ETHER_VLAN_TAG_9100:
                if (offset+4 > n) return EC_ETH_BAD_FRAME;
                frame->contents = frame->contents | EC_ETH_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                frame->vlan_tags[frame->number_of_vlan_tags].priority = priority;
                frame->vlan_tags[frame->number_of_vlan_tags].canonical_format = canonical_format;
                frame->vlan_tags[frame->number_of_vlan_tags].vlan = vlan;
                frame->vlan_tags[frame->number_of_vlan_tags].tag_type = EC_ETH_ETHER_VLAN_TAG_9100;
                frame->number_of_vlan_tags += 1;
                if (frame->number_of_vlan_tags > EC_ETH_MAX_VLAN_TAGS) {
                    return EC_ETH_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EC_ETH_ETHER_VLAN_TAG_9200:
                if (offset+4 > n) return EC_ETH_BAD_FRAME;
                frame->contents = frame->contents | EC_ETH_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                frame->vlan_tags[frame->number_of_vlan_tags].priority = priority;
                frame->vlan_tags[frame->number_of_vlan_tags].canonical_format = canonical_format;
                frame->vlan_tags[frame->number_of_vlan_tags].vlan = vlan;
                frame->vlan_tags[frame->number_of_vlan_tags].tag_type = EC_ETH_ETHER_VLAN_TAG_9200;
                frame->number_of_vlan_tags += 1;
                if (frame->number_of_vlan_tags > EC_ETH_MAX_VLAN_TAGS) {
                    return EC_ETH_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EC_ETH_ETHER_VLAN_TAG_9300:
                if (offset+4 > n) return EC_ETH_BAD_FRAME;
                frame->contents = frame->contents | EC_ETH_CONTAINS_VLAN_TAGS;
                priority = *(uint8_t *)(buf + offset+2) >> 5;
                canonical_format = *(uint8_t *)(buf + offset+2) & 0x10 >> 4;
                vlan = ntohs(*(uint16_t *)(buf + offset+2)) & 0x0fff;
                frame->vlan_tags[frame->number_of_vlan_tags].priority = priority;
                frame->vlan_tags[frame->number_of_vlan_tags].canonical_format = canonical_format;
                frame->vlan_tags[frame->number_of_vlan_tags].vlan = vlan;
                frame->vlan_tags[frame->number_of_vlan_tags].tag_type = EC_ETH_ETHER_VLAN_TAG_9300;
                frame->number_of_vlan_tags += 1;
                if (frame->number_of_vlan_tags > EC_ETH_MAX_VLAN_TAGS) {
                    return EC_ETH_BAD_FRAME;
                }
                offset += 4;
                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                break;
            case EC_ETH_ETHER_RESERVED:
                return EC_ETH_BAD_FRAME;
                break;
            default:
                /* Other ethertype, or unrecognized format */
                if (possible_ethertype > 1500) {
                    fprintf (stderr, "possible_ethernet > 1500. bad frame or unregnized ethertype.\n");
                    return EC_ETH_BAD_FRAME;
                }

                /* This is an 802.3 frame */
                frame->contents = frame->contents | EC_ETH_CONTAINS_802_DOT_3_LENGTH;
                frame->dot_3_length = possible_ethertype;
                offset += 2;

                if (offset+4 > n) return EC_ETH_BAD_FRAME;

                possible_ethertype = ntohs(*(uint16_t *) (buf+offset));

                /* Check for LLC */
                uint8_t llc_destination_sap = possible_ethertype;
                uint8_t llc_source_sap      = ntohs(*(uint8_t *) (buf+offset+1));

                /* IPX Raw 802.3 frame? */
                if (llc_destination_sap == EC_ETH_SAP_GLOBAL_LSAP 
                    && llc_source_sap == EC_ETH_SAP_GLOBAL_LSAP) {
                    frame->contents = frame->contents | EC_ETH_CONTAINS_IPX_RAW_802_DOT_3;
                    frame->payload_ethertype = EC_ETH_ETHER_RESERVED;
                    frame->payload_pointer = offset;
                    frame->payload_length = (n-offset);
                    frame->done = 1;
                    goto out;
                }

                /* Does have LLC */
                frame->contents = frame->contents | EC_ETH_CONTAINS_LLC_HEADER;
                frame->llc_destination_sap = llc_destination_sap;
                frame->llc_source_sap      = llc_source_sap;

                /* Is this an unnumbered (U-Format/1 byte) PDU? */
                if ( (*(uint8_t *)(buf+offset+2)) & 3) {
                    frame->llc_control = *(uint8_t *)(buf + offset+2);
                    offset += 3;
                } else {
                    frame->contents = frame->contents | EC_ETH_CONTAINS_2_BYTE_LLC_CONTROL;
                    frame->llc_control = ntohs(*(uint16_t *)(buf+offset+2));
                    offset += 4;
                }

                if (offset+5 > n) return EC_ETH_BAD_FRAME;
                /* Is SNAP service requested? */
                if ((llc_destination_sap == EC_ETH_SAP_SNAP_AA
                     || llc_destination_sap == EC_ETH_SAP_SNAP_AB)
                   && (llc_source_sap == EC_ETH_SAP_SNAP_AA
                     || llc_source_sap == EC_ETH_SAP_SNAP_AB)) {

                    return EC_ETH_BAD_FRAME;
/* Need to debug this
                    frame->contents = frame->contents | EC_ETH_CONTAINS_SNAP_HEADER;
                    memcpy (frame->snap_oui, buf+offset, 3);
                    frame->snap_sub_protocol = ntohs(*(uint16_t *)(buf+offset+3));
                    offset += 3;
*/
                } else {
                    switch (llc_destination_sap) {
                        case EC_ETH_SAP_IEEE_802_DOT_1_STP:
                            frame->payload_ethertype = EC_ETH_ETHER_802_DOT_1_STP;
                            frame->payload_pointer = buf+offset;
                            frame->payload_length = (n-(offset));
                            frame->done = 1;
                            goto out;
                            break;
                        default: /* unregocnized SAP */
                            return EC_ETH_BAD_FRAME;
                            break;
                    }
                } /* No recognizable Ethertype */

                /* RFC 1042 ethertype SNAP? */
                if (frame->llc_control == 3 && frame->snap_oui[0] == 0 &&
                   frame->snap_oui[1] == 0 && frame->snap_oui[2]) {
                    possible_ethertype = ntohs(*(uint16_t *) (buf+offset));
                } else {
                    return EC_ETH_BAD_FRAME;
                }
            /* End of Default Case */
        }
    }

out:

    // Further processing
    for (i=0; i<number_of_ethernet_listeners; i++) {
        eocene_ethernet_listener listener_cb = ethernet_listeners[i];
        listener_cb (frame);
    }

    return ES_OK;
}
