#include "strbuf.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_CAPACITY 32

strbuf strbuf_init() {
    strbuf_data *data = malloc(sizeof(strbuf_data));
    data->size = 0;
    data->capacity = 32;
    data->content = malloc(sizeof(char) * data->capacity);

    strbuf buf = {.data = data};

    return buf;
}

void strbuf_free(strbuf buf) {
    free(buf.data->content);
    free(buf.data);
    buf.data = NULL;
}

size_t strbuf_capacity(strbuf buf) { return buf.data->capacity; }

size_t strbuf_size(strbuf buf) { return buf.data->size; }

static void strbuf_resize(strbuf buf, size_t size) {
    size_t new_capacity = strbuf_capacity(buf);
    while (size > new_capacity) {
        new_capacity += 32;
    }

    buf.data->content = realloc(buf.data->content, new_capacity);
    buf.data->capacity = new_capacity;
}

void strbuf_write_native(strbuf buf, const char *native) {
    size_t native_size = strlen(native);
    size_t new_buf_size = strbuf_size(buf) + native_size;

    if (new_buf_size <= strbuf_capacity(buf)) {
        memcpy(buf.data->content + strbuf_size(buf), native, native_size);
        buf.data->size = new_buf_size;
        return;
    }

    strbuf_resize(buf, new_buf_size);
    strbuf_write_native(buf, native);
}

void strbuf_write_str(strbuf buf, str string) {
    char native[string.size + 1];
    str_to_native(string, native);

    strbuf_write_native(buf, native);
}

void strbuf_write_char(strbuf buf, char charater) {
    char native[2] = {charater, '\0'};
    strbuf_write_native(buf, native);
}

char *strbuf_to_owned_native(strbuf buf) {
    if (strbuf_size(buf) < strbuf_capacity(buf)) {
        buf.data->content[strbuf_size(buf)] = '\0';
        char *ptr = buf.data->content;

        free(buf.data);

        return ptr;
    }

    strbuf_resize(buf, strbuf_size(buf) + 1);
    return strbuf_to_owned_native(buf);
}
