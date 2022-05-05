#include <libmc/testing/test_allocator.h>

#include <libmc/memory/buffer.h>

#include <stdio.h>
#include <string.h>

int main(void) {
    mc_allocator *talloc = &mc_test_allocator;
    mc_buffer *test_buffer = malloc(sizeof(mc_buffer) + 4 * sizeof(uint8_t));
    test_buffer->size = 4;
    memcpy(test_buffer->data, "test", 4);

    mc_buffer_builder builder1 = mc_new_buffer_builder(talloc);
    mc_buffer_builder_write_buffer(&builder1, test_buffer);
    mc_buffer *builder1_buffer = mc_buffer_builder_build(&builder1, talloc);
    mc_buffer_builder_free(&builder1);

    if (memcmp(builder1_buffer->data, "test", 4)) {
        fputs("buffer allocation or writing non-functional\n", stderr);
        return EXIT_FAILURE;
    }

    mc_with_buffer_builder(builder2, talloc) {
        mc_buffer_builder_write_buffer(&builder2, test_buffer);
        mc_buffer *builder2_buffer = mc_buffer_builder_build(&builder2, talloc);

        if (memcmp(builder2_buffer->data, "test", 4)) {
            fputs("mc_with_buffer_builder macro malformed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}