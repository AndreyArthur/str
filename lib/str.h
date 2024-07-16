#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    char *data;
    size_t size;
} str;

extern const str STR_NIL;

str str_from_native(char *native);

str str_from_buffer(char *buffer, size_t size);

size_t str_index_of(str string, str substring);

char *str_to_native(str string, char *buffer);

str str_slice(str string, size_t start, size_t chars);

int str_compare(str first, str second);

bool str_equals(str first, str second);

bool str_is_nil(str string);

str str_token(str string, str substring, size_t token);

size_t str_tokens(str string, str substring);

str *str_tokenize(str string, str substring, str *array);

str str_concat(str first, str second, char *buffer);

str str_to_uppercase(str string);

str str_to_lowercase(str string);

str str_trim(str string);

size_t str_occurrences(str string, str substring);

size_t str_replace_size(str string, str find, str replace);

void __str_print(str string);

#endif
