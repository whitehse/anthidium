#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "eonessa.h"

int eonessa_parse_ipv4(const char* buf, unsigned n, struct eonessa_ipv4* en4, int flags) {
    if (n < EN_MIN_IPV4_PACKET_SIZE || n > EN_MAX_IPV4_PACKET_SIZE) {
        return EN_BAD_PACKET;
    }

    int i;
    int offset=0;

    en4->packet_size = n;

    en4->version = *(uint8_t *)(buf+offset) >> 4;
    if (en4->version != 4) {
        return EN_BAD_PACKET;
    }

    if (offset+20 > n) return EN_BAD_PACKET;

    en4->header_length = *(uint8_t *)(buf+offset) & 0x0f;
    if (en4->header_length < 5 ||
        en4->header_length * 4 > n) {
        return EN_BAD_PACKET;
    }
    en4->payload_length = n - en4->header_length*4;
    if (en4->payload_length > 0) {
        en4->payload_pointer = buf + (en4->header_length * 4);
    } else {
        en4->payload_pointer = NULL;
    }
    en4->dscp = (*(uint8_t *)(buf+offset+1) & 0xfc) >> 2;
    en4->ecn = *(uint8_t *)(buf+offset+1) & 0x03;
    en4->total_length = ntohs(*(uint16_t *)(buf+offset+2));
    if (n != en4->total_length && (flags & EN_IPV4_PARSE_FAIL_ON_INVALID_LENGTH)) {
        return EN_BAD_PACKET;
    }
    en4->identification = ntohs(*(uint16_t *)(buf+offset+4));
    en4->flags = *(uint8_t *)(buf+offset+6) & 0x07;
    en4->fragment_offset = (ntohs(*(uint16_t *)(buf+offset+6)) & 0xf8) >> 3;
    en4->ttl = *(uint8_t *)(buf+offset+8);
    en4->protocol = *(uint8_t *)(buf+offset+9);
    en4->checksum = ntohs(*(uint16_t *)(buf+offset+10));
    en4->source_ip = ntohl(*(uint32_t *)(buf+offset+12));
    en4->destination_ip = ntohl(*(uint32_t *)(buf+offset+16));
    offset += 20;

    if (offset+1 > n) return EN_BAD_PACKET;

    for (i=0; en4->header_length>5 && i < EN_MAX_IPV4_HEADERS; i++) {
        en4->number_of_options += 1;
        en4->header_options[i].copy_flag = *(uint8_t *)(buf+offset) & 0x01;
        en4->header_options[i].class_type = (*(uint8_t *)(buf+offset) & 0x06) >> 1;
        en4->header_options[i].number = (*(uint8_t *)(buf+offset) & 0xf8) >> 3;

        switch (en4->header_options[i].number) {
            case EN_OPT_END_OF_LIST:
                en4->header_options[i].length = 0;
                en4->header_options[i].data_pointer = NULL;
                goto out;
            /* simple options */
            case EN_OPT_NOP:
            case EN_OPT_COMMERCIAL_SECURITY:
            case EN_OPT_EXPERIMENTAL_MEASURE:
            case EN_OPT_EXP_FLOW_CONTROL:
            case EN_OPT_EXP_ACCESS_CONTROL:
            case EN_OPT_ENCODE:
            case EN_OPT_IMI_TRAFFIC_DESCRIPTOR:
            case EN_OPT_UNKNOWN_SIMPLE_1:
            case EN_OPT_DYNAMIC_PACKET_STATE:
            case EN_OPT_UPSTREAM_MULTICAST:
            case EN_OPT_QUICK_START:
            case EN_OPT_RFC3692_EXPERIMENTAL_1:
            case EN_OPT_RFC3692_EXPERIMENTAL_2:
            case EN_OPT_RFC3692_EXPERIMENTAL_3:
            case EN_OPT_RFC3692_EXPERIMENTAL_4:
                en4->header_options[i].data_pointer = NULL;
                en4->header_options[i].length = 0;
                offset += 1;
                break;
            default: /* It's assumed all other options include their own length */
                if (offset+1 > n) return EN_BAD_PACKET;
                en4->header_options[i].length = *(uint8_t *)(buf+offset+1);
                offset += 1;
                if (offset+1+(en4->header_options[i].length-2) > n) return EN_BAD_PACKET;
                en4->header_options[i].data_pointer = buf+offset+1;
                offset += 1 + (en4->header_options[i].length-2);
                break;
            /* end of default */
        }
        if (offset > en4->header_length*4) {
            return EN_BAD_PACKET;
        }
        if (offset == en4->header_length*4) {
            goto out;
        }
    }

out:
    return EN_OK;
}

int eonessa_parse_udp(const char* buf, unsigned n, struct eonessa_udp* enu, int flags) {
    if (n < EN_MIN_UDP_SIZE || n > EN_MAX_UDP_SIZE) {
        return EN_BAD_UDP_MESSAGE;
    }

    int i;

    enu->message_size = n;

    if (8 > n) return EN_BAD_UDP_MESSAGE;

    enu->source_port = ntohs(*(uint16_t *)(buf));
    enu->destination_port = ntohs(*(uint16_t *)(buf+2));
    enu->length = ntohs(*(uint16_t *)(buf+4));
    enu->checksum = ntohs(*(uint16_t *)(buf+6));

    if (enu->length != n) return EN_BAD_UDP_MESSAGE;

    enu->payload_length = enu->length - 8;

    if (enu->payload_length > 0) {
        enu->payload_pointer = buf + 8;
    } else {
        enu->payload_pointer = NULL;
    }
    return EN_OK;
}

int eonessa_parse_tcp(const char* buf, unsigned n, struct eonessa_tcp* ent, int flags) {
    if (n < EN_MIN_TCP_SIZE || n > EN_MAX_TCP_SIZE) {
        return EN_BAD_TCP_MESSAGE;
    }

    int i;
    int offset = 0;

    ent->message_size = n;

    if (offset+20 > n) return EN_BAD_TCP_MESSAGE;

    ent->source_port = ntohs(*(uint16_t *)(buf));
    ent->destination_port = ntohs(*(uint16_t *)(buf+2));
    ent->sequence_number = ntohl(*(uint32_t *)(buf+4));
    ent->acknowledgement_number = ntohl(*(uint32_t *)(buf+8));
    ent->data_offset = (*(uint8_t *)(buf+offset+12) & 0xf0) >> 4;
    if (ent->data_offset < 5 ||
        ent->data_offset * 4 > n) {
        return EN_BAD_TCP_MESSAGE;
    }
    ent->payload_length = n - ent->data_offset*4;
    if (ent->payload_length > 0) {
        ent->payload_pointer = buf + (ent->data_offset * 4);
    } else {
        ent->payload_pointer = NULL;
    }
    ent->flags = ntohs(*(uint16_t *)(buf+offset+12)) & 0x0fff;
    ent->window_size = ntohl(*(uint32_t *)(buf+14));
    ent->checksum = ntohl(*(uint32_t *)(buf+16));
    ent->urgent_pointer = ntohl(*(uint32_t *)(buf+18));
    offset += 20;

    if (offset+1 > n) return EN_BAD_TCP_MESSAGE;

    for (i=0; ent->data_offset>5 && i < EN_MAX_TCP_HEADERS; i++) {
        ent->number_of_options += 1;
        ent->header_options[i].number = *(uint8_t *)(buf+offset);

        switch (ent->header_options[i].number) {
            case EN_TCP_OPT_END_OF_LIST:
                ent->header_options[i].length = 0;
                ent->header_options[i].data_pointer = NULL;
                goto out;
            /* simple options */
            case EN_TCP_OPT_NOP:
                ent->header_options[i].data_pointer = NULL;
                ent->header_options[i].length = 0;
                offset += 1;
                break;
            default: /* It's assumed all other options include their own length */
                if (offset+1 > n) return EN_BAD_TCP_MESSAGE;
                ent->header_options[i].length = *(uint8_t *)(buf+offset+1);
                offset += 1;
                if (offset+1+(ent->header_options[i].length-2) > n) return EN_BAD_TCP_MESSAGE;
                ent->header_options[i].data_pointer = buf+offset+1;
                offset += 1 + (ent->header_options[i].length-2);
                break;
            /* end of default */
        }
        if (offset > ent->data_offset*4) {
            return EN_BAD_TCP_MESSAGE;
        }
        if (offset == ent->data_offset*4) {
            goto out;
        }
     }
out:
    return EN_OK;
}
