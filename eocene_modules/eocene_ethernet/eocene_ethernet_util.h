
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

#ifndef EOCENE_ETHERNET_UTIL_H
#define EOCENE_ETHERNET_UTIL_H

/*void print_line(const char *buf, unsigned n);
void dump_buffer(const char* buf, unsigned n);*/
char* destination_mac_in_dash_format (struct ec_ethernet* frame);
char* destination_mac_in_colon_format (struct ec_ethernet* frame);
char* destination_mac_in_cisco_format (struct ec_ethernet* frame);
char* source_mac_in_dash_format (struct ec_ethernet* frame);
char* source_mac_in_colon_format (struct ec_ethernet* frame);
char* source_mac_in_cisco_format (struct ec_ethernet* frame);
char* source_oui_in_dash_format (struct ec_ethernet* frame);
char* source_oui_in_colon_format (struct ec_ethernet* frame);
char* destination_oui_in_dash_format (struct ec_ethernet* frame);
char* destination_oui_in_colon_format (struct ec_ethernet* frame);
char* snap_oui_in_dash_format (struct ec_ethernet* frame);
char* snap_oui_in_colon_format (struct ec_ethernet* frame);

#endif // EOCENE_ETHERNET_UTIL_H
