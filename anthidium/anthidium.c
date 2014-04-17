#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <libconfig.h>
#include <eosimias.h>
#include <eosimias_util.h>
#include <eocene.h>
#include <eonessa.h>
#include "anthidium.h"

struct es_state *state;
eocene_wireline_parse *wireline_callbacks;
int number_of_wireline_modules = 0;

int j=0;

static struct option const long_options[] =
{
    {"help", no_argument, 0, 'h'},
    {"config", required_argument, 0, 'c'},
    {NULL, 0, NULL, 0}
};

int main (int argc, char **argv) {
    int error = 0;
    char *config_file = NULL;
    struct config_t cfg;
    int result;
    int i;
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

    error = eosimias_init(state, &cfg);

    fprintf (stderr, "eosimias_init returned: %s", eosimias_error_string(error));
    
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
