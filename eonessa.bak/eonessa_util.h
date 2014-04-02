
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

#ifndef EONESSA_UTIL_H
#define EONESSA_UTIL_H

void print_line(const char *buf, unsigned n);
void dump_buffer(const char* buf, unsigned n);
char* destination_mac_in_dash_format (struct eonessa* en);
char* destination_mac_in_colon_format (struct eonessa* en);
char* destination_mac_in_cisco_format (struct eonessa* en);
char* source_mac_in_dash_format (struct eonessa* en);
char* source_mac_in_colon_format (struct eonessa* en);
char* source_mac_in_cisco_format (struct eonessa* en);
char* source_oui_in_dash_format (struct eonessa* en);
char* source_oui_in_colon_format (struct eonessa* en);
char* destination_oui_in_dash_format (struct eonessa* en);
char* destination_oui_in_colon_format (struct eonessa* en);
char* snap_oui_in_dash_format (struct eonessa* en);
char* snap_oui_in_colon_format (struct eonessa* en);

char* ipv4_source_ip_in_decimal (struct eonessa_ipv4* en);
char* ipv4_destination_ip_in_decimal (struct eonessa_ipv4* en);

#endif // EONESSA_UTIL_H
