#ifndef libmc_memory_allocator_h
#define libmc_memory_allocator_h

#include <stddef.h>

typedef struct mc_allocator_s {
    void *data;
    void *(*malloc)(struct mc_allocator_s *self, size_t size);
    void *(*realloc)(struct mc_allocator_s *self, void *ptr, size_t new_size);
    void (*free)(struct mc_allocator_s *self, void *ptr);
} mc_allocator;

static inline void *mc_malloc(mc_allocator *allocator, size_t size) {
    return allocator->malloc(allocator, size);
}

static inline void *mc_realloc(mc_allocator *allocator, void *ptr, size_t new_size) {
    return allocator->realloc(allocator, ptr, new_size);
}

static inline void mc_free(mc_allocator *allocator, void *ptr) {
    allocator->free(allocator, ptr);
}

#endif
