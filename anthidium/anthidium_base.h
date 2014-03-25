
/* anthidium_base.h
 *
 * Copyright (C) Dan White
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

#ifndef ANTHIDIUM_BASE_H
#define ANTHIDIUM_BASE_H

/*This is a main header - it inludes everything else.*/

#define CONFIG_FILENAME (PACKAGE_SYSCONF_DIR "/anthidium.conf")

static void usage (int status);
//static void pcap_ev_cb (EV_P_ ev_io *w, int revents);
void got_frame(u_char *args, const struct pcap_pkthdr *header, const u_char *frame);

/*int use_table (void **db, char *table);
int store (void **db, void *key, int key_len, void **value, int *value_len);
int retrieve (void **db, void *key, int key_len, void **value, int *value_len);
int rem (void **db, void *key, int key_len);
int unuse_table (void **db);*/

/*int new_timer (void **timer_ref, void **associated_data, double timeout);
int update_timeout (void **timer_ref, double timeout );
int update_associated_data (void **timer_ref, void **associated_data);
int delete_timer (void **timer_ref);*/

#endif // ANTHIDIUM_BASE_H

