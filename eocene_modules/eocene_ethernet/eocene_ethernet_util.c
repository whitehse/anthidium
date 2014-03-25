#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "eocene_ethernet.h"

/*void print_line(const char *line, unsigned n) {
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
}*/

char* destination_mac_in_dash_format (struct ec_ethernet* frame) {
    snprintf(frame->destination_mac_dash_format, 18,
        "%02x-%02x-%02x-%02x-%02x-%02x",
        (unsigned char)frame->destination_mac[0],
        (unsigned char)frame->destination_mac[1],
        (unsigned char)frame->destination_mac[2],
        (unsigned char)frame->destination_mac[3],
        (unsigned char)frame->destination_mac[4],
        (unsigned char)frame->destination_mac[5]);
    return frame->destination_mac_dash_format;
}

char* destination_mac_in_colon_format (struct ec_ethernet* frame) {
    snprintf(frame->destination_mac_colon_format, 18,
        "%02x:%02x:%02x:%02x:%02x:%02x",
        (unsigned char)frame->destination_mac[0],
        (unsigned char)frame->destination_mac[1],
        (unsigned char)frame->destination_mac[2],
        (unsigned char)frame->destination_mac[3],
        (unsigned char)frame->destination_mac[4],
        (unsigned char)frame->destination_mac[5]);
    return frame->destination_mac_colon_format;
}

char* destination_mac_in_cisco_format (struct ec_ethernet* frame) {
    snprintf(frame->destination_mac_cisco_format, 18,
        "%02x%02x.%02x%02x.%02x%02x",
        (unsigned char)frame->destination_mac[0],
        (unsigned char)frame->destination_mac[1],
        (unsigned char)frame->destination_mac[2],
        (unsigned char)frame->destination_mac[3],
        (unsigned char)frame->destination_mac[4],
        (unsigned char)frame->destination_mac[5]);
    return frame->destination_mac_cisco_format;
}

char* source_mac_in_dash_format (struct ec_ethernet* frame) {
    snprintf(frame->source_mac_dash_format, 18,
        "%02x-%02x-%02x-%02x-%02x-%02x",
        (unsigned char)frame->source_mac[0],
        (unsigned char)frame->source_mac[1],
        (unsigned char)frame->source_mac[2],
        (unsigned char)frame->source_mac[3],
        (unsigned char)frame->source_mac[4],
        (unsigned char)frame->source_mac[5]);
    return frame->source_mac_dash_format;
}

char* source_mac_in_colon_format (struct ec_ethernet* frame) {
    snprintf(frame->source_mac_colon_format, 18,
        "%02x:%02x:%02x:%02x:%02x:%02x",
        (unsigned char)frame->source_mac[0],
        (unsigned char)frame->source_mac[1],
        (unsigned char)frame->source_mac[2],
        (unsigned char)frame->source_mac[3],
        (unsigned char)frame->source_mac[4],
        (unsigned char)frame->source_mac[5]);
    return frame->source_mac_colon_format;
}

char* source_mac_in_cisco_format (struct ec_ethernet* frame) {
    snprintf(frame->source_mac_cisco_format, 18,
        "%02x%02x.%02x%02x.%02x%02x",
        (unsigned char)frame->source_mac[0],
        (unsigned char)frame->source_mac[1],
        (unsigned char)frame->source_mac[2],
        (unsigned char)frame->source_mac[3],
        (unsigned char)frame->source_mac[4],
        (unsigned char)frame->source_mac[5]);
    return frame->source_mac_cisco_format;
}

char* source_oui_in_dash_format (struct ec_ethernet* frame) {
    snprintf(frame->source_oui_dash_format, 18,
        "%02x-%02x-%02x",
        (unsigned char)frame->source_mac[0],
        (unsigned char)frame->source_mac[1],
        (unsigned char)frame->source_mac[2]);
    return frame->source_oui_dash_format;
}

char* source_oui_in_colon_format (struct ec_ethernet* frame) {
    snprintf(frame->source_oui_colon_format, 18,
        "%02x:%02x:%02x",
        (unsigned char)frame->source_mac[0],
        (unsigned char)frame->source_mac[1],
        (unsigned char)frame->source_mac[2]);
    return frame->source_oui_colon_format;
}

char* destination_oui_in_dash_format (struct ec_ethernet* frame) {
    snprintf(frame->destination_oui_dash_format, 18,
        "%02x-%02x-%02x",
        (unsigned char)frame->destination_mac[0],
        (unsigned char)frame->destination_mac[1],
        (unsigned char)frame->destination_mac[2]);
    return frame->destination_oui_dash_format;
}

char* destination_oui_in_colon_format (struct ec_ethernet* frame) {
    snprintf(frame->destination_oui_colon_format, 18,
        "%02x:%02x:%02x",
        (unsigned char)frame->destination_mac[0],
        (unsigned char)frame->destination_mac[1],
        (unsigned char)frame->destination_mac[2]);
    return frame->destination_oui_colon_format;
}

char* snap_oui_in_dash_format (struct ec_ethernet* frame) {
    snprintf(frame->snap_oui_dash_format, 18,
        "%02x-%02x-%02x",
        (unsigned char)frame->snap_oui[0],
        (unsigned char)frame->snap_oui[1],
        (unsigned char)frame->snap_oui[2]);
    return frame->snap_oui_dash_format;
}

char* snap_oui_in_colon_format (struct ec_ethernet* frame) {
    snprintf(frame->snap_oui_colon_format, 18,
        "%02x:%02x:%02x",
        (unsigned char)frame->snap_oui[0],
        (unsigned char)frame->snap_oui[1],
        (unsigned char)frame->snap_oui[2]);
    return frame->snap_oui_colon_format;
}
