
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

#ifndef EOSIMIAS_LIBEV_BASE_H
#define EOSIMIAS_LIBEV_BASE_H

//int _es_init();
int es_watch_fd_for_reads(int fd, void *associated_data, es_io_cb io_cb);
int es_watch_fd_for_writes(int fd, void *associated_data, es_io_cb io_cb);
int es_watch_fd_for_reads_and_writes(int fd, void *associated_data, es_io_cb io_cb);
int es_run();

//int init(config_setting_t *config, struct es_state *_state);

#endif // EOSIMIAS_LIBEV_BASE_H
