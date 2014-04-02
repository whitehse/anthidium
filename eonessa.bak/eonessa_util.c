#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "eonessa.h"

void print_line(const char *line, unsigned n) {
    int i;
    int display_width=16;

    for(i=0;i<n;i++)
        fprintf(stderr, "%02x ", (unsigned char)line[i]);
    for(i=n;i<display_width;i++)
        fprintf(stderr, "   ");
    fprintf(stderr, " ");
    for(i=0;i<n;i++)
        if(isgraph((unsigned) line[i]))
            fprintf(stderr, "%c", line[i]);
        else
            fprintf(stderr, ".");
        fprintf(stderr, "\n");
}

void dump_buffer(const char* dump, unsigned n) {
    int i;

    if (dump == NULL) { return; }

    for (i=0;i<n;i+=16) {
        if(i + 16 <= n)
            print_line(dump+i, 16);
        else
            print_line(dump+i, n - i);
    }
}

char* destination_mac_in_dash_format (struct eonessa* en) {
    snprintf(en->destination_mac_dash_format, 18,
        "%02x-%02x-%02x-%02x-%02x-%02x",
        (unsigned char)en->destination_mac[0],
        (unsigned char)en->destination_mac[1],
        (unsigned char)en->destination_mac[2],
        (unsigned char)en->destination_mac[3],
        (unsigned char)en->destination_mac[4],
        (unsigned char)en->destination_mac[5]);
    return en->destination_mac_dash_format;
}

char* destination_mac_in_colon_format (struct eonessa* en) {
    snprintf(en->destination_mac_colon_format, 18,
        "%02x:%02x:%02x:%02x:%02x:%02x",
        (unsigned char)en->destination_mac[0],
        (unsigned char)en->destination_mac[1],
        (unsigned char)en->destination_mac[2],
        (unsigned char)en->destination_mac[3],
        (unsigned char)en->destination_mac[4],
        (unsigned char)en->destination_mac[5]);
    return en->destination_mac_colon_format;
}

char* destination_mac_in_cisco_format (struct eonessa* en) {
    snprintf(en->destination_mac_cisco_format, 18,
        "%02x%02x.%02x%02x.%02x%02x",
        (unsigned char)en->destination_mac[0],
        (unsigned char)en->destination_mac[1],
        (unsigned char)en->destination_mac[2],
        (unsigned char)en->destination_mac[3],
        (unsigned char)en->destination_mac[4],
        (unsigned char)en->destination_mac[5]);
    return en->destination_mac_cisco_format;
}

char* source_mac_in_dash_format (struct eonessa* en) {
    snprintf(en->source_mac_dash_format, 18,
        "%02x-%02x-%02x-%02x-%02x-%02x",
        (unsigned char)en->source_mac[0],
        (unsigned char)en->source_mac[1],
        (unsigned char)en->source_mac[2],
        (unsigned char)en->source_mac[3],
        (unsigned char)en->source_mac[4],
        (unsigned char)en->source_mac[5]);
    return en->source_mac_dash_format;
}

char* source_mac_in_colon_format (struct eonessa* en) {
    snprintf(en->source_mac_colon_format, 18,
        "%02x:%02x:%02x:%02x:%02x:%02x",
        (unsigned char)en->source_mac[0],
        (unsigned char)en->source_mac[1],
        (unsigned char)en->source_mac[2],
        (unsigned char)en->source_mac[3],
        (unsigned char)en->source_mac[4],
        (unsigned char)en->source_mac[5]);
    return en->source_mac_colon_format;
}

char* source_mac_in_cisco_format (struct eonessa* en) {
    snprintf(en->source_mac_cisco_format, 18,
        "%02x%02x.%02x%02x.%02x%02x",
        (unsigned char)en->source_mac[0],
        (unsigned char)en->source_mac[1],
        (unsigned char)en->source_mac[2],
        (unsigned char)en->source_mac[3],
        (unsigned char)en->source_mac[4],
        (unsigned char)en->source_mac[5]);
    return en->source_mac_cisco_format;
}

char* source_oui_in_dash_format (struct eonessa* en) {
    snprintf(en->source_oui_dash_format, 18,
        "%02x-%02x-%02x",
        (unsigned char)en->source_mac[0],
        (unsigned char)en->source_mac[1],
        (unsigned char)en->source_mac[2]);
    return en->source_oui_dash_format;
}

char* source_oui_in_colon_format (struct eonessa* en) {
    snprintf(en->source_oui_colon_format, 18,
        "%02x:%02x:%02x",
        (unsigned char)en->source_mac[0],
        (unsigned char)en->source_mac[1],
        (unsigned char)en->source_mac[2]);
    return en->source_oui_colon_format;
}

char* destination_oui_in_dash_format (struct eonessa* en) {
    snprintf(en->destination_oui_dash_format, 18,
        "%02x-%02x-%02x",
        (unsigned char)en->destination_mac[0],
        (unsigned char)en->destination_mac[1],
        (unsigned char)en->destination_mac[2]);
    return en->destination_oui_dash_format;
}

char* destination_oui_in_colon_format (struct eonessa* en) {
    snprintf(en->destination_oui_colon_format, 18,
        "%02x:%02x:%02x",
        (unsigned char)en->destination_mac[0],
        (unsigned char)en->destination_mac[1],
        (unsigned char)en->destination_mac[2]);
    return en->destination_oui_colon_format;
}

char* snap_oui_in_dash_format (struct eonessa* en) {
    snprintf(en->snap_oui_dash_format, 18,
        "%02x-%02x-%02x",
        (unsigned char)en->snap_oui[0],
        (unsigned char)en->snap_oui[1],
        (unsigned char)en->snap_oui[2]);
    return en->snap_oui_dash_format;
}

char* snap_oui_in_colon_format (struct eonessa* en) {
    snprintf(en->snap_oui_colon_format, 18,
        "%02x:%02x:%02x",
        (unsigned char)en->snap_oui[0],
        (unsigned char)en->snap_oui[1],
        (unsigned char)en->snap_oui[2]);
    return en->snap_oui_colon_format;
}

char* ipv4_source_ip_in_decimal (struct eonessa_ipv4* en4) {
    snprintf(en4->source_ip_decimal, 16,
        "%d.%d.%d.%d",
        (unsigned char)((en4->source_ip & 0xff000000) >> 24),
        (unsigned char)((en4->source_ip & 0x00ff0000) >> 16),
        (unsigned char)((en4->source_ip & 0x0000ff00) >> 8),
        (unsigned char)(en4->source_ip & 0x000000ff));
    return en4->source_ip_decimal;
}

char* ipv4_destination_ip_in_decimal (struct eonessa_ipv4* en4) {
    snprintf(en4->destination_ip_decimal, 16,
        "%d.%d.%d.%d",
        (unsigned char)((en4->destination_ip & 0xff000000) >> 24),
        (unsigned char)((en4->destination_ip & 0x00ff0000) >> 16),
        (unsigned char)((en4->destination_ip & 0x0000ff00) >> 8),
        (unsigned char)(en4->destination_ip & 0x000000ff));
    return en4->destination_ip_decimal;
}

