#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <pcap.h>
#include <libconfig.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <eocene/eocene.h>
#include <eocene/eocene_util.h>
#include "anthidium.h"

struct ec_state *state;
eocene_wireline_parse *wireline_callbacks;
int number_of_wireline_modules = 0;
lua_State* master_lua_state;

int j=0;

static struct option const long_options[] =
{
    {"help", no_argument, 0, 'h'},
    {"config", required_argument, 0, 'c'},
    {NULL, 0, NULL, 0}
};

int local_timer_cb (void* data, struct ec_timer *timer) {
    fprintf (stderr, "local_timer_cb was called.\n");
}

int pcap_cb (pcap_t *handle, int mask) {

    struct pcap_pkthdr header;
    u_char         *frame;
    int count=0;

    frame = (u_char *) pcap_next(handle, &header);

    int i, r;

    j++;
    
    if (j < 100) {
        void *test = NULL;
        void **test2 = NULL;
        test2 = &test;

        state->new_timer (test2, NULL, 10, local_timer_cb);
    }

    dump_buffer(frame, header.len);

    // Further processing
    for (i=0; i<number_of_wireline_modules; i++) {
        (*wireline_callbacks[i]) (frame, header.len, EC_CAP_TYPE_PCAP);
    }

    fprintf(stderr, "======================================\n");
}

int main (int argc, char **argv) {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    struct pcap_pkthdr header;  /* The header that pcap gives us */
    const u_char *frame;        /* The actual frame */
    int error = 0;
    char *config_file = NULL;
    struct config_t cfg;
    char *eocene_module_path = NULL;
    char *eonessa_module_path = NULL;
    config_setting_t *modules;
    config_setting_t *eocene_sources;
    config_setting_t *eocene_wireline_modules;
    char *data_store_module = NULL;
    char *event_module = NULL;
    char *output_module = NULL;
    int number_of_eocene_modules = 0;
    int number_of_eocene_sources = 0;
    int result;
    int i;

    state = (struct ec_state*)malloc(sizeof(struct ec_state));
    memset(state, 0, sizeof (struct ec_state));

    master_lua_state = luaL_newstate();
    luaL_openlibs (master_lua_state);

    state->master_lua_state = master_lua_state;

    /*luaopen_base (master_lua_state); 
    luaopen_package (master_lua_state);
    luaopen_string (master_lua_state);
    luaopen_table (master_lua_state);
    luaopen_math (master_lua_state);
    luaopen_io (master_lua_state);
    luaopen_os (master_lua_state);*/

/*    int status;
    double sum;
    status = luaL_loadfile(master_lua_state, "script.lua");
    if (status) {
        fprintf(stderr, "Couldn't load file: %s\n", lua_tostring(master_lua_state, -1));
        exit(1);
    }
    lua_newtable(master_lua_state);
    for (i = 1; i <= 5; i++) {
        lua_pushnumber(master_lua_state, i);
        lua_pushnumber(master_lua_state, i*2);
        lua_rawset(master_lua_state, -3);
    }
    lua_setglobal(master_lua_state, "foo");
    status = lua_pcall(master_lua_state, 0, LUA_MULTRET, 0);
    if (status) {
        fprintf(stderr, "Failed to run script: %s\n", lua_tostring(master_lua_state, -1));
        exit(1);
    }
    sum = lua_tonumber(master_lua_state, -1);
    printf("Script returned: %.0f\n", sum);
    lua_pop(master_lua_state, 1);*/
    /*lua_close(master_lua_state);*/
/*
    clump.arp = &ena;
    clump.ipv4 = &en4;
    clump.udp = &enu;
    clump.tcp = &ent;
*/
    int c;

    while ((c = getopt_long (argc, argv,
                    "h" /* help */
                    "c:", /* config file */
                    long_options, (int *) 0)) != EOF) {
        switch (c) {
            case 'h':
                usage (0);

            case 'c':
                config_file = optarg;
                break;

        }
    }

    config_init(&cfg);
    if (config_file == NULL) {
        config_file = CONFIG_FILENAME;
    }
    if (config_read_file(&cfg, config_file) != CONFIG_TRUE) {
        fprintf(stderr, "config parse error in %s:%d - %s\n",
            config_file,
            config_error_line(&cfg),
            config_error_text(&cfg));
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }

    state->cfg = &cfg;

    config_lookup_string(&cfg, "eocene_module_path", &eocene_module_path);
    if (eocene_module_path) {
        error = set_eocene_module_search_path (eocene_module_path);
        if (error) {
            fprintf(stderr, "Unable to set module search path.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        /* If not specified, it should default to the correct location */
    }

    modules = config_lookup(&cfg, "load_eocene_modules");
    if (!modules) {
        fprintf(stderr, "configuration item 'load_eocene_modules' could not be found.\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }
    if (config_setting_is_array(modules) != CONFIG_TRUE) {
        fprintf(stderr, "configuration item 'load_eocene_modules' is not an array.\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }
    number_of_eocene_modules = config_setting_length(modules);

    for (i=0; i<number_of_eocene_modules; i++) {
        const char *module = config_setting_get_string_elem(modules, i);
        error = load_eocene_module(module);
        if (error) {
            fprintf(stderr, "Unable to load module %s: %s\n", module, eocene_error_string(error));
            config_destroy(&cfg);
            exit(EXIT_FAILURE);
        } else {
            fprintf(stderr, "Sucessfully loaded module %s.\n", module);
        }
        eocene_init eocene_init_ref;
        config_setting_t *module_config;
        //module_config = config_setting_get_string_elem(modules, i);
        fprintf (stderr, "Getting ready to find the init function for module %s\n", module);
        result = find_eocene_symbol (module, "init", &eocene_init_ref);
        result = (*eocene_init_ref) (&module_config, state);
    }

    config_lookup_string(&cfg, "data_store_module", &data_store_module);
    if (!data_store_module) {
        fprintf(stderr, "configuration item 'data_store_module' could not be found.\n");
        exit(EXIT_FAILURE);
    }
    
    result = find_eocene_symbol (data_store_module, "open_table", &(state->open_table));
    result = find_eocene_symbol (data_store_module, "get", &(state->get));
    result = find_eocene_symbol (data_store_module, "put", &(state->put));
    result = find_eocene_symbol (data_store_module, "del", &(state->del));
    result = find_eocene_symbol (data_store_module, "close_table", &(state->close_table));

    config_lookup_string(&cfg, "event_module", &event_module);
    if (!event_module) {
        fprintf(stderr, "configuration item 'event_module' could not be found.\n");
        exit(EXIT_FAILURE);
    }
    
    result = find_eocene_symbol (event_module, "ec_new_timer", &(state->new_timer));
    result = find_eocene_symbol (event_module, "ec_update_timeout", &(state->update_timeout));
    result = find_eocene_symbol (event_module, "ec_update_associated_data", &(state->update_associated_data));
    result = find_eocene_symbol (event_module, "ec_delete_timer", &(state->delete_timer));
    result = find_eocene_symbol (event_module, "ec_watch_fd_for_reads", &(state->watch_fd_for_reads));
    result = find_eocene_symbol (event_module, "ec_watch_fd_for_writes", &(state->watch_fd_for_writes));
    result = find_eocene_symbol (event_module, "ec_watch_fd_for_reads_and_writes", &(state->watch_fd_for_reads_and_writes));
    result = find_eocene_symbol (event_module, "ec_run", &(state->run));

    eocene_wireline_modules = config_lookup(&cfg, "eocene_wireline_modules");
    if (!eocene_wireline_modules) {
        fprintf(stderr, "configuration item 'eocene_wireline_modules' could not be found.\n");
        exit(EXIT_FAILURE);
    }
    if (config_setting_is_array(eocene_wireline_modules) != CONFIG_TRUE) {
        fprintf(stderr, "configuration item 'eocene_wireline_modules' is not an array.\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }
    number_of_wireline_modules = config_setting_length(eocene_wireline_modules);

    wireline_callbacks = malloc((number_of_wireline_modules) * sizeof(eocene_wireline_parse));
    for (i=0; i<number_of_wireline_modules; i++) {
        eocene_init eocene_init_ref;
        eocene_wireline_parse eocene_wireline_parse_ref;
        config_setting_t *module_config;
        const char *module = config_setting_get_string_elem(eocene_wireline_modules, i);
//        result = find_eocene_symbol (module, "init", &eocene_init_ref);
        result = find_eocene_symbol (module, "parse", &eocene_wireline_parse_ref);
        if (result) {
            fprintf (stderr, "Danger Will Robinson!\n");
        }
//        result = (*eocene_init_ref) (&module_config, state);
        wireline_callbacks[i] = eocene_wireline_parse_ref;
    }
    //wireline_callbacks[i+1] = NULL;

    config_lookup_string(&cfg, "output_module", &output_module);
    if (!event_module) {
        fprintf(stderr, "configuration item 'output_module' could not be found.\n");
        exit(EXIT_FAILURE);
    }
    
    result = find_eocene_symbol (output_module, "print", &(state->printer));

    eocene_sources = config_lookup(&cfg, "eocene_sources");
    if (!eocene_sources) {
        fprintf(stderr, "configuration item 'eocene_sources' could not be found.\n");
        exit(EXIT_FAILURE);
    }
    if (config_setting_is_list(eocene_sources) != CONFIG_TRUE) {
        fprintf(stderr, "configuration item 'eocene_sources' is not a list.\n");
        exit(EXIT_FAILURE);
    }
    number_of_eocene_sources = config_setting_length(eocene_sources);

    for (i=0; i<number_of_eocene_sources; i++) {
        const char *dev = NULL;
        const char *type = NULL;
        const char *filter_exp = NULL;
        const char *filename = NULL;
        int promiscuous = 0;
        bpf_u_int32 mask;
        bpf_u_int32 net;
        config_setting_t *source;
        char *source_string;

        source = config_setting_get_elem(eocene_sources, i);

        if (! config_setting_lookup_string(source, "type", &type)) {
            fprintf(stderr, "Capture source did not specify a required type.\n");
            exit(EXIT_FAILURE);
        }
        if (! config_setting_lookup_string(source, "source", &dev)) {
            fprintf(stderr, "Could not find a valid source definition.\n");
            exit(EXIT_FAILURE);
        }
        if (! strncmp(type, "pcap-live", 9)) {
            if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
                fprintf(stderr, "Can't get netmask for device %s\n", dev);
                net = 0;
                mask = 0;
            }
            if (config_setting_lookup_bool(source, "promiscuous", &promiscuous)) {
                /* default promiscuous to off. There could be a syntax error, so warn the user. */
                fprintf(stderr, "Could not find valid promiscuous definition. Defaulting to off.\n");
                promiscuous = 0;
            }
            handle = pcap_open_live(dev, BUFSIZ, promiscuous, 1000, errbuf);
        } else if (! strncmp(type, "pcap-file", 9)) {
            filename = dev;
            handle = pcap_open_offline(filename, errbuf);
        } else {
            fprintf(stderr, "You specified an unrecognizable source type.\n");
            exit(EXIT_FAILURE);
        }

        if (handle == NULL) {
            fprintf(stderr, "Couldn't open device or file: %s\n", dev, errbuf);
            exit(EXIT_FAILURE);
        }

        if (! config_setting_lookup_string(source, "filter", &filter_exp)) {
            fprintf(stderr, "Could not find valid filtering definition. Defaulting to NULL.\n");
            filter_exp = NULL;
        }

        if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
            fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
            return(2);
        }
        if (pcap_setfilter(handle, &fp) == -1) {
            fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
            return(2);
        }

        int pcap_fd = pcap_fileno(handle);
        state->watch_fd_for_reads(pcap_fd, handle, pcap_cb);
    }

    state->run();

    return(0);
}

static void usage (int status) {
    printf ("anthidium - \
anthidium\n");
    printf ("Usage: anthidium [OPTION]... [FILE]...\n");
    printf ("\
Options:\n\
  -h, --help                 display this help and exit\n\
  -c, --config=<file>        specifies the location of a config file\n\
");
    exit (status);
}
