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
#include <eonessa/eonessa.h>
#include <eonessa/eonessa_util.h>
#include <eocene/eocene.h>
#include <eocene/eocene_util.h>
#include "anthidium.h"

struct ec_state *state;
eocene_wireline_parse *wireline_callbacks;
int number_of_wireline_modules = 0;
lua_State* master_lua_state;

int j=0;

sub_eonessa_parse module_array[MAX_NUM_OF_SUBMODULES+1];

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

/*    memset(&en, 0, sizeof (struct eonessa));
    memset(&ena, 0, sizeof (struct eonessa_arp));
    memset(&en4, 0, sizeof (struct eonessa_ipv4));
    memset(&enu, 0, sizeof (struct eonessa_udp));
    memset(&ent, 0, sizeof (struct eonessa_tcp));
    clump.number_of_ether_headers = 1;
    clump.eonessa[0] = &en; 
*/
    dump_buffer(frame, header.len);
/*
    r = eonessa_parse(frame, header.len, EN_CAP_TYPE_PCAP, &en);
    if (r) {
        fprintf(stderr, "Invalid frame.\n");
        fprintf(stderr, "======================================\n");
        return;
    }
    destination_mac_in_colon_format(&en);
    source_mac_in_colon_format(&en);
    destination_oui_in_dash_format(&en);
    source_oui_in_dash_format(&en);
    fprintf (stderr, "Destination MAC: %s\n", en.destination_mac_colon_format);
    fprintf (stderr, "Source MAC: %s\n", en.source_mac_colon_format);
    fprintf (stderr, "Destination OUI: %s\n", en.destination_oui_dash_format);
    fprintf (stderr, "Source OUI: %s\n", en.source_oui_dash_format);
    fprintf(stderr, "Payload ethertype = %04x. Payload length is %d.\n", en.payload_ethertype, en.payload_length);
    fprintf(stderr, "The Frame size is %d.\n", en.frame_size);
    if (en.contents & EN_CONTAINS_MPLS_TAGS) {
        fprintf (stderr, "MPLS Tags found(%d).\n", en.number_of_mpls_tags);
        for (i=0;i<en.number_of_mpls_tags;i++) {
            fprintf (stderr, "Tag #%d:\n", i);
            fprintf (stderr, "  label = %05x (hex)\n", en.mpls_tags[i].label);
            fprintf (stderr, "  cos = %d\n", en.mpls_tags[i].cos);
            fprintf (stderr, "  stack bit = %d\n", en.mpls_tags[i].stack_bit);
            fprintf (stderr, "  ttl = %02x (hex)\n", en.mpls_tags[i].ttl);
        }
    }
    if (en.contents & EN_CONTAINS_VLAN_TAGS) {
        fprintf (stderr, "VLAN Tags found(%d).\n", en.number_of_vlan_tags);
        for (i=0;i<en.number_of_vlan_tags;i++) {
            fprintf (stderr, "Tag #%d:\n", i);
            fprintf (stderr, "  tag type = %04x (hex)\n", en.vlan_tags[i].tag_type);
            fprintf (stderr, "  priority = %d\n", en.vlan_tags[i].priority);
            fprintf (stderr, "  canonical format = %d\n", en.vlan_tags[i].canonical_format);
            fprintf (stderr, "  vlan = %d\n", en.vlan_tags[i].vlan);
        }
    }
    switch (en.payload_ethertype) {
        case EN_ETHER_IPV4:
            r = eonessa_parse_ipv4(en.payload_pointer, en.payload_length, &en4, 0);
            if (r) {
                fprintf(stderr, "Invalid packet.\n");
                fprintf(stderr, "======================================\n");
                return;
            }
            ipv4_destination_ip_in_decimal(&en4);
            ipv4_source_ip_in_decimal(&en4);
            fprintf (stderr, "IPv4 packet data:\n");
            fprintf (stderr, "  version=%d.\n", en4.version);
            fprintf (stderr, "  header_length=%d.\n", en4.header_length);
            fprintf (stderr, "  dscp=%d.\n", en4.dscp);
            fprintf (stderr, "  ecn=%d.\n", en4.ecn);
            fprintf (stderr, "  total_length=%d.\n", en4.total_length);
            fprintf (stderr, "  identification=%d.\n", en4.identification);
            fprintf (stderr, "  flags=%d.\n", en4.flags);
            fprintf (stderr, "  fragment_offset=%d.\n", en4.fragment_offset);
            fprintf (stderr, "  ttl=%d.\n", en4.ttl);
            fprintf (stderr, "  protocol=%x (hex).\n", en4.protocol);
            fprintf (stderr, "  checksum=%x (hex).\n", en4.checksum);
            fprintf (stderr, "  source ip = %s.\n", en4.source_ip_decimal);
            fprintf (stderr, "  destination ip = %s.\n", en4.destination_ip_decimal);
            fprintf (stderr, "  number of options = %d.\n", en4.number_of_options);
            fprintf (stderr, "  payload length = %d.\n", en4.total_length - en4.header_length*4);
            fprintf (stderr, "  payload offset = %d.\n", en4.header_length*4);
            if (en4.number_of_options > 0) {
                fprintf (stderr, "  IPv4 options were found.\n");
            }
            for (i=0;i<en4.number_of_options;i++) {
                fprintf (stderr, "    copy flag = %0d\n", en4.header_options[i].copy_flag);
                fprintf (stderr, "    class type = %0d\n", en4.header_options[i].class_type);
                fprintf (stderr, "    option number = %0d\n", en4.header_options[i].number);
                fprintf (stderr, "    length = %0d\n", en4.header_options[i].length);
            }
            break;
        default:
            goto out;
            break;
    }
    switch (en4.protocol) {
        case EN_PROT_UDP:
            r = eonessa_parse_udp(en4.payload_pointer, en4.payload_length, &enu, 0);
            if (r) {
                fprintf(stderr, "Invalid UDP message.\n");
                fprintf(stderr, "======================================\n");
                return;
            }
            fprintf (stderr, "  UDP message data:\n");
            fprintf (stderr, "    source port=%d.\n", enu.source_port);
            fprintf (stderr, "    destination port=%d.\n", enu.destination_port);
            fprintf (stderr, "    length=%d.\n", enu.length);
            fprintf (stderr, "    checksum=%d.\n", enu.checksum);
            fprintf (stderr, "    payload length=%d.\n", enu.payload_length);
            break;
        case EN_PROT_TCP:
            r = eonessa_parse_tcp(en4.payload_pointer, en4.payload_length, &ent, 0);
            if (r) {
                fprintf(stderr, "Invalid TCP message.\n");
                fprintf(stderr, "======================================\n");
                return;
            }
            fprintf (stderr, "  TCP message data:\n");
            fprintf (stderr, "    source port=%d.\n", ent.source_port);
            fprintf (stderr, "    destination port=%d.\n", ent.destination_port);
            fprintf (stderr, "    sequence number=%d.\n", ent.sequence_number);
            fprintf (stderr, "    acknownledgement number=%d.\n", ent.acknowledgement_number);
            fprintf (stderr, "    data offset=%d.\n", ent.data_offset);
            fprintf (stderr, "    flags=%d.\n", ent.flags);
            fprintf (stderr, "    window_size=%d.\n", ent.window_size);
            fprintf (stderr, "    checksum=%d.\n", ent.checksum);
            fprintf (stderr, "    urgent pointer=%d.\n", ent.urgent_pointer);
            fprintf (stderr, "    number of options=%d.\n", ent.number_of_options);
            fprintf (stderr, "    payload length=%d.\n", ent.payload_length);
            if (ent.number_of_options > 0) {
                fprintf (stderr, "    TCP options were found.\n");
            }
            for (i=0;i<ent.number_of_options;i++) {
                fprintf (stderr, "      option number = %0d\n", ent.header_options[i].number);
                fprintf (stderr, "      length = %0d\n", ent.header_options[i].length);
            }
            break;
         default:
            goto out;
            break;
    }

out:
*/
    // Further processing
    for (i=0; i<number_of_wireline_modules; i++) {
        (*wireline_callbacks[i]) (frame, header.len, EN_CAP_TYPE_PCAP);
    }

/*    sub_eonessa_parse module_caller = NULL;
    for (i=0; module_caller=module_array[i]; i++) {
        (*module_caller) (&clump);
    }
    fprintf(stderr, "Just called all submodules.\n");*/

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
    char *module_path = NULL;
    config_setting_t *modules;
    config_setting_t *sources;
    config_setting_t *wireline_modules;
    char *data_store_module = NULL;
    char *event_module = NULL;
    int number_of_modules = 0;
    int number_of_sources = 0;
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

    config_lookup_string(&cfg, "module_path", &module_path);
    if (module_path) {
        error = set_eocene_module_search_path (module_path);
        if (error) {
            fprintf(stderr, "Unable to set module search path.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        /* If not specified, it should default to the correct location */
    }

    modules = config_lookup(&cfg, "load_modules");
    if (!modules) {
        fprintf(stderr, "configuration item 'load_modules' could not be found.\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }
    if (config_setting_is_array(modules) != CONFIG_TRUE) {
        fprintf(stderr, "configuration item 'load_modules' is not an array.\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }
    number_of_modules = config_setting_length(modules);
    memset(module_array, 0, sizeof(sub_eonessa_parse)*(MAX_NUM_OF_SUBMODULES+1));

    for (i=0; i<number_of_modules; i++) {
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

    wireline_modules = config_lookup(&cfg, "wireline_modules");
    if (!wireline_modules) {
        fprintf(stderr, "configuration item 'wireline_modules' could not be found.\n");
        exit(EXIT_FAILURE);
    }
    if (config_setting_is_array(wireline_modules) != CONFIG_TRUE) {
        fprintf(stderr, "configuration item 'wireline_modules' is not an array.\n");
        config_destroy(&cfg);
        exit(EXIT_FAILURE);
    }
    number_of_wireline_modules = config_setting_length(wireline_modules);

    wireline_callbacks = malloc((number_of_wireline_modules) * sizeof(eocene_wireline_parse));
    for (i=0; i<number_of_wireline_modules; i++) {
        eocene_init eocene_init_ref;
        eocene_wireline_parse eocene_wireline_parse_ref;
        config_setting_t *module_config;
        const char *module = config_setting_get_string_elem(wireline_modules, i);
//        result = find_eocene_symbol (module, "init", &eocene_init_ref);
        result = find_eocene_symbol (module, "parse", &eocene_wireline_parse_ref);
        if (result) {
            fprintf (stderr, "Danger Will Robinson!\n");
        }
//        result = (*eocene_init_ref) (&module_config, state);
        wireline_callbacks[i] = eocene_wireline_parse_ref;
    }
    //wireline_callbacks[i+1] = NULL;

    sources = config_lookup(&cfg, "sources");
    if (!sources) {
        fprintf(stderr, "configuration item 'sources' could not be found.\n");
        exit(EXIT_FAILURE);
    }
    if (config_setting_is_list(sources) != CONFIG_TRUE) {
        fprintf(stderr, "configuration item 'sources' is not a list.\n");
        exit(EXIT_FAILURE);
    }
    number_of_sources = config_setting_length(sources);

    for (i=0; i<number_of_sources; i++) {
        const char *dev = NULL;
        const char *type = NULL;
        const char *filter_exp = NULL;
        const char *filename = NULL;
        int promiscuous = 0;
        bpf_u_int32 mask;
        bpf_u_int32 net;
        config_setting_t *source;
        char *source_string;

        source = config_setting_get_elem(sources, i);

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
