#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <eonessa.h>
#include <eocene.h>
#include "eocene_dhcpv4.h"

int eocene_parse_dhcpv4(const char* buf, unsigned n, struct eocene_dhcpv4* spdh4, int flags) {
/*    if (n < EC_MIN_IPV4_PACKET_SIZE || n > EC_MAX_IPV4_PACKET_SIZE) {
        return EC_D4_BAD_DATA;
    }*/

    int i;
    int offset=0;

    memset(spdh4, 0, sizeof (struct eocene_dhcpv4));
    spdh4->data_size = n;
}

/*
struct eocene_dhcpv4 {
    uint8_t op;
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
    char chaddr[17];
    char sname[65];
    char file[129];
    int number_of_options;
    struct eocene_dhcpv4_option options[EC_D4_MAX_DHCPV4_OPTIONS];
};
*/

