#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <ev.h>
#include <eonessa.h>
#include <eocene.h>
#include "eocene_libev.h"

#define init eocene_libev_LTX_init
#define parse eocene_libev_LTX_parse

struct ev_loop *loop = NULL;

struct ec_timer_list *timer_list_head;
struct ec_timer_list *timer_list_tail;

int init(config_setting_t *config, struct ec_state *_state) {
    loop = ev_default_loop (0);
    return EC_OK;
}

static void ec_io_read_cb (EV_P_ ev_io *w, int revents) {
    struct ec_io_data *io_data = w->data;
    io_data->callback(io_data->data, EC_READ);
}

static void ec_io_write_cb (EV_P_ ev_io *w, int revents) {
    struct ec_io_data *io_data = w->data;
    io_data->callback(io_data->data, EC_WRITE);
}

static void ec_io_read_or_write_cb (EV_P_ ev_io *w, int revents) {
    int mask = 0;
    struct ec_io_data *io_data = w->data;

    mask |= (revents|EV_READ) ? EC_READ : 0;
    mask |= (revents|EV_WRITE) ? EC_WRITE : 0;
    io_data->callback(io_data->data, mask);
}

int ec_watch_fd_for_reads(int fd, void *associated_data, ec_io_cb io_cb) {
    struct ev_io *fd_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));
    ev_init (fd_watcher, ec_io_read_cb);
    struct ec_io_data *io_data = (struct ec_io_data*)malloc(sizeof(struct ec_io_data));
    io_data->data = associated_data;
    io_data->callback = io_cb;
    fd_watcher->data = io_data;
    ev_io_set (fd_watcher, fd, EV_READ);
    ev_io_start (loop, fd_watcher);
    return EC_OK;
}

int ec_watch_fd_for_writes(int fd, void *associated_data, ec_io_cb io_cb) {
    struct ev_io *fd_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));
    ev_init (fd_watcher, ec_io_read_cb);
    struct ec_io_data *io_data = (struct ec_io_data*)malloc(sizeof(struct ec_io_data));
    io_data->data = associated_data;
    io_data->callback = io_cb;
    fd_watcher->data = io_data;
    ev_io_set (fd_watcher, fd, EV_WRITE);
    ev_io_start (loop, fd_watcher);
    return EC_OK;
}

int ec_watch_fd_for_reads_and_writes(int fd, void *associated_data, ec_io_cb io_cb) {
    struct ev_io *fd_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));
    ev_init (fd_watcher, ec_io_read_cb);
    struct ec_io_data *io_data = (struct ec_io_data*)malloc(sizeof(struct ec_io_data));
    io_data->data = associated_data;
    io_data->callback = io_cb;
    fd_watcher->data = io_data;
    ev_io_set (fd_watcher, fd, EV_READ|EV_WRITE);
    ev_io_start (loop, fd_watcher);
    return EC_OK;
}

int ec_run() {
    ev_run (loop, 0);
    return EC_OK;
}

int ec_process_timer (struct ev_loop *loop, ev_timer *ev_timer, int revents) {
    struct ec_timer_list *timer_list_ptr = ev_timer->data;
    struct ec_timer *current_timer = NULL;
    ev_tstamp now = ev_now (loop);
    while (current_timer = timer_list_ptr->head) {
        if (current_timer->when <= now) {
            ((ec_timer_cb)(current_timer->callback)) (current_timer->data, current_timer);
            if (timer_list_ptr->head->next == NULL) {
                /*ev_timer_stop (loop, ev_timer);*/
            }
            timer_list_ptr->head = timer_list_ptr->head->next;
            current_timer->next = NULL;
            current_timer->prev = NULL;
        } else {
            break;
        }
    }
    if (timer_list_ptr->head != NULL) {
        /* Rearm the timeout */
        ev_timer->repeat = timer_list_ptr->head->when - now;
        ev_timer_again (loop, ev_timer);
    }
}

int ec_new_timer (void **timer_ref, void **associated_data, double timeout, ec_timer_cb timer_cb) {
    struct ec_timer_list *timer_list_ptr = NULL;
    struct ec_timer *timer = (struct ec_timer*)malloc(sizeof(struct ec_timer));
    memset(timer, 0, sizeof (struct ec_timer));
    if (loop == NULL) {
        timer->when = (double) (ev_time() + timeout);
    } else {
        timer->when = ev_now(loop) + timeout;
    }
    timer->callback = timer_cb;

    *timer_ref = timer;
    if (associated_data != NULL)
        timer->data = *associated_data;

    timer_list_ptr = timer_list_head;

    while (timer_list_ptr != NULL) {
        if (timer_list_ptr->timeout == timeout)
            break;
        timer_list_ptr = timer_list_ptr->next;
    }

    if (timer_list_ptr == NULL) {
        timer_list_ptr = (struct ec_timer_list *)malloc(sizeof(struct ec_timer_list));
        memset(timer_list_ptr, 0, sizeof (struct ec_timer_list));
        timer_list_ptr->timeout = timeout;
        ev_timer *libev_timer = (ev_timer*)malloc(sizeof(ev_timer));
        libev_timer->data = timer_list_ptr;
        ev_timer_init (libev_timer, ec_process_timer, timeout, timeout);
        ev_timer_start (loop, libev_timer);
    }

    if (timer_list_head == NULL) {
        timer_list_head = timer_list_tail = timer_list_ptr;
    } else {
        timer_list_tail->next = timer_list_ptr;
        timer_list_ptr->prev = timer_list_tail;
        timer_list_tail = timer_list_ptr;
    }

    if (timer_list_ptr->head == NULL) {
        timer_list_ptr->head = timer_list_ptr->tail = timer;
    } else {
        timer_list_ptr->tail->next = timer;
        timer->prev = timer_list_ptr->tail;
        timer_list_ptr->tail = timer;
    }
}

int ec_update_timeout (void **timer_ref, double timeout) {
    struct ec_timer *timer = *timer_ref;
}

int ec_update_associated_data (void **timer_ref, void **associated_data) {
    struct ec_timer *timer = *timer_ref;
}

int ec_get_associated_data (void **timer_ref, void **associated_data) {
    struct ec_timer *timer = *timer_ref;
    *associated_data = timer->data;
}

int ec_delete_timer (void **timer_ref) {
    free (*timer_ref);
}

