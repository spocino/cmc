#ifndef libmc_memory_buffer
#define libmc_memory_buffer

#include "allocator.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t size;
    uint8_t data[];
} mc_buffer;

typedef struct {
    size_t size, capacity;
    mc_allocator *allocator;
    uint8_t *data;
} mc_buffer_builder;

static inline mc_buffer_builder mc_new_buffer_builder(mc_allocator *allocator) {
    return (mc_buffer_builder) {
        .size = 0,
        .capacity = 0,
        .allocator = allocator,
        .data = NULL
    };
}

static inline void mc_buffer_builder_free(mc_buffer_builder *builder) {
    mc_free(builder->allocator, builder->data);
    builder->data = NULL;
    builder->capacity = 0;
    builder->size = 0;
}

static inline void mc_buffer_builder_write_buffer(mc_buffer_builder *builder, const mc_buffer *buffer) {
    size_t next_power_of_2 = 8;
    while (next_power_of_2 < builder->size + buffer->size) next_power_of_2 <<= 1;
    if (builder->size + buffer->size > builder->capacity) {
        builder->capacity = (builder->capacity) ? builder->capacity * 2 : next_power_of_2;
        builder->data = (uint8_t*)(builder->data ? 
            mc_realloc(builder->allocator, builder->data, builder->capacity) :
            mc_malloc(builder->allocator, builder->capacity));
    }

    for (size_t i = 0; i < buffer->size; i++)
        builder->data[builder->size + i] = buffer->data[i];
    
    builder->size += buffer->size;
}

static inline mc_buffer *mc_buffer_builder_build(mc_buffer_builder *builder, mc_allocator *allocator) {
    mc_buffer *buffer = (mc_buffer*)mc_malloc(allocator, sizeof(mc_buffer) + builder->size * sizeof(uint8_t));
    buffer->size = builder->size;
    for (size_t i = 0; i < buffer->size; i++) {
        buffer->data[i] = builder->data[i];
    }
    return buffer;
}

#define mc_with_buffer_builder(name, alloc) \
for ( \
    mc_buffer_builder name = mc_new_buffer_builder(alloc); \
    name.allocator; \
    mc_buffer_builder_free(&name), name.allocator = NULL)

#endif
