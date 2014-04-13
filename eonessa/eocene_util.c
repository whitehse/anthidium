#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "eocene.h"
#include "eocene_util.h"

char* eocene_error_string(int error) {

    switch (error) {
        case EC_OK:
            return EC_OK_REASON;
            break;
        case EC_FAIL:
            return EC_FAIL_REASON;
            break;
        case EC_NOMEM:
            return EC_NOMEM_REASON;
            break;
        case EC_BUFOVER:
            return EC_BUFOVER_REASON;
            break;
        case EC_BADPARAM:
            return EC_BADPARAM_REASON;
            break;
        case EC_CANT_DLINIT:
            return EC_CANT_DLINIT_REASON;
            break;
        case EC_CANT_DLSETSEARCHPATH:
            return EC_CANT_DLSETSEARCHPATH_REASON;
            break;
        case EC_CANT_DLOPENEXT:
            return EC_CANT_DLOPENEXT_REASON;
            break;
        case EC_CANT_DLCLOSE:
            return EC_CANT_DLCLOSE_REASON;
            break;
        case EC_CANT_DLEXIT:
            return EC_CANT_DLEXIT_REASON;
            break;
        default:
            break;
    }
}
