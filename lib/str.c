#include "str.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const str STR_NIL = {.data = NULL, .size = 0};

str str_from_native(char *native) {
    size_t size = strlen(native);
    str string = {.data = native, .size = size};
    return string;
}

str str_from_buffer(char *buffer, size_t size) {
    str string = {.data = buffer, .size = size};
    return string;
}

size_t str_index_of(str string, str substring) {
    if (string.size < substring.size) {
        return SIZE_MAX;
    }

    int max_index = string.size - substring.size;
    for (int index = 0; index <= max_index; index++) {
        if (memcmp(string.data + index, substring.data, substring.size) == 0) {
            return index;
        }
    }

    return SIZE_MAX;
}

str str_slice(str string, size_t start, size_t chars) {
    if (start + chars > string.size) {
        return STR_NIL;
    }

    str slice = {.data = string.data + start, .size = chars};
    return slice;
}

char *str_to_native(str string, char *buffer) {
    memcpy(buffer, string.data, string.size);
    buffer[string.size] = '\0';
    return buffer;
}

int str_compare(str first, str second) {
    char first_buffer[first.size + 1];
    char second_buffer[first.size + 1];

    char *first_native = str_to_native(first, first_buffer);
    char *second_native = str_to_native(second, second_buffer);

    return strcmp(first_native, second_native);
}

bool str_equals(str first, str second) {
    return first.size == second.size && str_compare(first, second) == 0;
}

bool str_is_nil(str string) {
    return string.data == STR_NIL.data && string.size == STR_NIL.size;
}

static str str_token_recursive(str string, str substring, size_t token,
                               bool has_substring_before) {
    size_t index = str_index_of(string, substring);
    bool substring_was_found = index != SIZE_MAX;

    if (substring_was_found) {
        if (token == 0) {
            return str_slice(string, 0, index);
        }

        str slice = str_slice(string, index + substring.size,
                              string.size - (index + substring.size));
        return str_token_recursive(slice, substring, token - 1, true);
    }

    if (has_substring_before) {
        if (token == 0) {
            return string;
        }

        return STR_NIL;
    }

    return STR_NIL;
}

str str_token(str string, str substring, size_t token) {
    return str_token_recursive(string, substring, token, false);
}

size_t str_tokens(str string, str substring) {
    size_t index = 0;
    for (;;) {
        str token = str_token(string, substring, index);
        if (str_is_nil(token)) {
            return index;
        }
        index++;
    }
}

str *str_tokenize(str string, str substring, str *array) {
    size_t index = 0;
    for (;;) {
        str token = str_token(string, substring, index);
        if (str_is_nil(token)) {
            return array;
        }
        array[index] = token;
        index++;
    }
}

str str_concat(str first, str second, char *buffer) {
    memcpy(buffer, first.data, first.size);
    memcpy((buffer + first.size), second.data, second.size);
    str concatenated = {.data = buffer, .size = first.size + second.size};
    return concatenated;
}

str str_to_lowercase(str string) {
    for (size_t index = 0; index < string.size; index++) {
        string.data[index] = tolower(string.data[index]);
    }
    return string;
}

str str_to_uppercase(str string) {
    for (size_t index = 0; index < string.size; index++) {
        string.data[index] = toupper(string.data[index]);
    }
    return string;
}

static bool is_whitespace(char character) {
    return character == ' ' || character == '\t' || character == '\n' ||
           character == '\r';
}

str str_trim(str string) {
    size_t start = 0;
    while (start < string.size && is_whitespace(string.data[start])) {
        start++;
    }

    size_t end = string.size - 1;
    while (is_whitespace(string.data[end])) {
        end--;
        if (end == 0) {
            break;
        }
    }

    if (start >= end) {
        str trimmed = {.data = string.data, .size = 0};
        return trimmed;
    }

    size_t chars = (end + 1) - start;
    return str_slice(string, start, chars);
}

static size_t str_occurrences_recursive(str string, str substring,
                                        size_t occurrences) {
    size_t index = str_index_of(string, substring);

    if (index == SIZE_MAX) {
        return occurrences;
    }

    str slice = str_slice(string, index + substring.size,
                          string.size - (index + substring.size));
    return str_occurrences_recursive(slice, substring, occurrences + 1);
}

size_t str_occurrences(str string, str substring) {
    return str_occurrences_recursive(string, substring, 0);
}

size_t str_replace_size(str string, str find, str replace) {
    size_t occurrences = str_occurrences(string, find);
    if (occurrences == 0) {
        return string.size;
    }

    return string.size - find.size * occurrences + replace.size * occurrences;
}

void __str_print(str string) {
    char buffer[string.size + 1];
    printf("%s\n", str_to_native(string, buffer));
}
