#ifndef STRBUF_H
#define STRBUF_H

#include "str.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t capacity;
    size_t size;
    char *content;
} strbuf_data;

typedef struct {
    strbuf_data *data;
} strbuf;

strbuf strbuf_init();

void strbuf_free(strbuf buf);

size_t strbuf_capacity(strbuf buf);

size_t strbuf_size(strbuf buf);

void strbuf_write_native(strbuf buf, const char *native);

void strbuf_write_str(strbuf buf, str string);

void strbuf_write_char(strbuf buf, char character);

char *strbuf_to_owned_native(strbuf buf);

#endif
