#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "eosimias.h"
#include "eosimias_util.h"

char* eosimias_error_string(int error) {

    switch (error) {
        case ES_OK:
            return ES_OK_REASON;
            break;
        case ES_FAIL:
            return ES_FAIL_REASON;
            break;
        case ES_NOMEM:
            return ES_NOMEM_REASON;
            break;
        case ES_BUFOVER:
            return ES_BUFOVER_REASON;
            break;
        case ES_BADPARAM:
            return ES_BADPARAM_REASON;
            break;
        case ES_CANT_DLINIT:
            return ES_CANT_DLINIT_REASON;
            break;
        case ES_CANT_DLSETSEARCHPATH:
            return ES_CANT_DLSETSEARCHPATH_REASON;
            break;
        case ES_CANT_DLOPENEXT:
            return ES_CANT_DLOPENEXT_REASON;
            break;
        case ES_CANT_DLSYM:
            return ES_CANT_DLSYM_REASON;
            break;
        case ES_CANT_DLCLOSE:
            return ES_CANT_DLCLOSE_REASON;
            break;
        case ES_CANT_DLEXIT:
            return ES_CANT_DLEXIT_REASON;
            break;
        default:
            break;
    }
}
