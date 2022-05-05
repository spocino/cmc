#ifndef libmc_testing_test_allocator_h
#define libmc_testing_test_allocator_h

#include <libmc/memory/allocator.h>

#include <stdlib.h>
#include <stddef.h>

static void *mc_test_malloc(mc_allocator *self, size_t size) {
    (void)(self);
    return malloc(size);
}

static void *mc_test_realloc(mc_allocator *self, void *ptr, size_t new_size) {
    (void)(self);
    return realloc(ptr, new_size);
}

static void mc_test_free(mc_allocator *self, void *ptr) {
    (void)(self);
    free(ptr);
}

static mc_allocator mc_test_allocator = {
    .data = NULL,
    .malloc = mc_test_malloc,
    .realloc = mc_test_realloc,
    .free = mc_test_free
};

#endif