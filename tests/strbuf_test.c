#include "../include/strbuf.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_strbuf_init() {
    strbuf buf = strbuf_init();

    assert(buf.data->size == 0);
    assert(buf.data->capacity == 32);

    strbuf_free(buf);
}

void test_strbuf_capacity() {
    strbuf buf = strbuf_init();

    assert(strbuf_capacity(buf) == buf.data->capacity);

    strbuf_free(buf);
}

void test_strbuf_size() {
    strbuf buf = strbuf_init();

    assert(strbuf_size(buf) == buf.data->size);

    strbuf_free(buf);
}

void test_strbuf_write_native() {
    {
        strbuf buf = strbuf_init();

        strbuf_write_native(buf, "Hello, World!");

        assert(strbuf_size(buf) == 13);
        assert(strbuf_capacity(buf) == 32);

        strbuf_free(buf);
    }

    {
        strbuf buf = strbuf_init();

        strbuf_write_native(buf, "The quick brown fox jumps");
        strbuf_write_native(buf, " over the lazy dog.");

        assert(strbuf_size(buf) == 44);
        assert(strbuf_capacity(buf) == 64);

        strbuf_free(buf);
    }
}

void test_strbuf_write_str() {
    strbuf buf = strbuf_init();
    str string = str_from_native("Hello, World!");

    strbuf_write_str(buf, string);

    char native[string.size + 1];
    str_to_native(string, native);
    char *owned = strbuf_to_owned_native(buf);

    assert(strcmp(native, owned) == 0);

    free(owned);
}

void test_strbuf_write_char() {
    strbuf buf = strbuf_init();

    strbuf_write_char(buf, 'H');
    strbuf_write_char(buf, 'i');

    assert(strbuf_size(buf) == 2);
    assert(strbuf_capacity(buf) == 32);

    strbuf_free(buf);
}

void test_strbuf_to_owned_native() {
    strbuf buf = strbuf_init();

    strbuf_write_native(buf, "Hi! Mom.");

    char *native = strbuf_to_owned_native(buf);

    assert(strcmp(native, "Hi! Mom.") == 0);

    free(native);
}

int main() {
    test_strbuf_init();
    test_strbuf_capacity();
    test_strbuf_size();
    test_strbuf_write_native();
    test_strbuf_write_str();
    test_strbuf_write_char();
    test_strbuf_to_owned_native();

    return 0;
}
