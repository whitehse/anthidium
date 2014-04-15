#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <libconfig.h>
#include <ev.h>
#include <eosimias.h>
#include "eosimias_libev.h"

#define init eosimias_libev_LTX_init

struct ev_loop *loop = NULL;

struct es_timer_list *timer_list_head;
struct es_timer_list *timer_list_tail;

int init(config_setting_t *config, struct es_state *_state) {
    loop = ev_default_loop (0);
    return ES_OK;
}

static void es_io_read_cb (EV_P_ ev_io *w, int revents) {
    struct es_io_data *io_data = w->data;
    io_data->callback(io_data->data, ES_READ);
}

static void es_io_write_cb (EV_P_ ev_io *w, int revents) {
    struct es_io_data *io_data = w->data;
    io_data->callback(io_data->data, ES_WRITE);
}

static void es_io_read_or_write_cb (EV_P_ ev_io *w, int revents) {
    int mask = 0;
    struct es_io_data *io_data = w->data;

    mask |= (revents|ES_READ) ? ES_READ : 0;
    mask |= (revents|ES_WRITE) ? ES_WRITE : 0;
    io_data->callback(io_data->data, mask);
}

int es_watch_fd_for_reads(int fd, void *associated_data, es_io_cb io_cb) {
    struct ev_io *fd_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));
    ev_init (fd_watcher, es_io_read_cb);
    struct es_io_data *io_data = (struct es_io_data*)malloc(sizeof(struct es_io_data));
    io_data->data = associated_data;
    io_data->callback = io_cb;
    fd_watcher->data = io_data;
    ev_io_set (fd_watcher, fd, EV_READ);
    ev_io_start (loop, fd_watcher);
    return ES_OK;
}

int es_watch_fd_for_writes(int fd, void *associated_data, es_io_cb io_cb) {
    struct ev_io *fd_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));
    ev_init (fd_watcher, es_io_read_cb);
    struct es_io_data *io_data = (struct es_io_data*)malloc(sizeof(struct es_io_data));
    io_data->data = associated_data;
    io_data->callback = io_cb;
    fd_watcher->data = io_data;
    ev_io_set (fd_watcher, fd, EV_WRITE);
    ev_io_start (loop, fd_watcher);
    return ES_OK;
}

int es_watch_fd_for_reads_and_writes(int fd, void *associated_data, es_io_cb io_cb) {
    struct ev_io *fd_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));
    ev_init (fd_watcher, es_io_read_cb);
    struct es_io_data *io_data = (struct es_io_data*)malloc(sizeof(struct es_io_data));
    io_data->data = associated_data;
    io_data->callback = io_cb;
    fd_watcher->data = io_data;
    ev_io_set (fd_watcher, fd, EV_READ|EV_WRITE);
    ev_io_start (loop, fd_watcher);
    return ES_OK;
}

int es_run() {
    es_run (loop, 0);
    return ES_OK;
}

int es_process_timer (struct ev_loop *loop, ev_timer *ev_timer, int revents) {
    struct es_timer_list *timer_list_ptr = ev_timer->data;
    struct es_timer *current_timer = NULL;
    ev_tstamp now = ev_now (loop);
    while (current_timer = timer_list_ptr->head) {
        if (current_timer->when <= now) {
            ((es_timer_cb)(current_timer->callback)) (current_timer->data, current_timer);
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

int es_new_timer (void **timer_ref, void **associated_data, double timeout, es_timer_cb timer_cb) {
    struct es_timer_list *timer_list_ptr = NULL;
    struct es_timer *timer = (struct es_timer*)malloc(sizeof(struct es_timer));
    memset(timer, 0, sizeof (struct es_timer));
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
        timer_list_ptr = (struct es_timer_list *)malloc(sizeof(struct es_timer_list));
        memset(timer_list_ptr, 0, sizeof (struct es_timer_list));
        timer_list_ptr->timeout = timeout;
        ev_timer *libev_timer = (ev_timer*)malloc(sizeof(ev_timer));
        libev_timer->data = timer_list_ptr;
        ev_timer_init (libev_timer, es_process_timer, timeout, timeout);
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

int es_update_timeout (void **timer_ref, double timeout) {
    struct es_timer *timer = *timer_ref;
}

int es_update_associated_data (void **timer_ref, void **associated_data) {
    struct es_timer *timer = *timer_ref;
}

int es_get_associated_data (void **timer_ref, void **associated_data) {
    struct es_timer *timer = *timer_ref;
    *associated_data = timer->data;
}

int es_delete_timer (void **timer_ref) {
    free (*timer_ref);
}

