#include "helper.h"
#include <stddef.h>

void* emalloc(size_t bytes, const char* errmsg) {
    void* mem = malloc(bytes);
    if (!mem) {
        if (!errmsg) {
            fprintf(stderr, "Could not allocate more memory.\n");
        } else {
            fprintf(stderr, "%s", errmsg);
        }
        return NULL;
    }

    return mem;
}
