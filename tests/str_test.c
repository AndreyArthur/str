#include "../lib/str.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void test_str_from_native() {
    char native[] = "Hello, World!";
    str string = str_from_native(native);

    assert(string.data == native);
    assert(string.size == 13);
    assert(memcmp(native, string.data, string.size) == 0);
}

void test_str_from_buffer() {
    int size = 128;
    char buffer[size];
    str string = str_from_buffer(buffer, size);

    assert(string.data == buffer);
    assert(string.size == 128);
    assert(memcmp(buffer, string.data, string.size) == 0);
}

void test_str_index_of() {
    {
        str string = str_from_native("Hello, World!");
        str substring = str_from_native("l");

        assert(str_index_of(string, substring) == 2);
    }

    {
        str string = str_from_native("Hello, World!");
        str substring = str_from_native("ld!");

        assert(str_index_of(string, substring) == 10);
    }

    {
        str string = str_from_native("Hello, World!");
        str substring = str_from_native("Earth");

        assert(str_index_of(string, substring) == SIZE_MAX);
    }
}

void test_str_to_native() {
    str string = str_from_native("banana");
    char buffer[string.size + 1];
    char *native = str_to_native(string, buffer);

    assert(native == buffer);
    assert(string.data != native);
    assert(string.size == strlen(native));
    assert(memcmp(string.data, native, string.size) == 0);
}

void test_str_slice() {
    {
        str string = str_from_native("Hello, Mars!");
        str slice = str_slice(string, 7, 4);

        assert(slice.size == 4);
        assert(memcmp(slice.data, "Mars", slice.size) == 0);
        assert(str_index_of(string, slice) == 7);
    }

    {
        str string = str_from_native("Hello, Mars!");
        str slice = str_slice(string, 7, 5);

        assert(str_equals(slice, str_from_native("Mars!")));
    }

    {
        str string = str_from_native("Hello, Mars!");
        str slice = str_slice(string, 7, 6);

        assert(str_is_nil(slice) == true);
    }
}

void test_str_compare() {
    {
        str first = str_from_native("abcde");
        str second = str_from_native("abcde");

        assert(str_compare(first, second) == 0);
    }

    {
        str first = str_from_native("bbcde");
        str second = str_from_native("abcde");

        assert(str_compare(first, second) == 1);
    }

    {
        str first = str_from_native("abcde");
        str second = str_from_native("bbcde");

        assert(str_compare(first, second) == -1);
    }
}

void test_str_equals() {
    {
        str first = str_from_native("abcde");
        str second = str_from_native("abcde");

        assert(str_equals(first, second) == true);
    }

    {
        str first = str_from_native("bbcde");
        str second = str_from_native("abcde");

        assert(str_equals(first, second) == false);
    }
}

void test_str_is_nil() {
    str not_nil = str_from_native("abcde");
    str nil = STR_NIL;

    assert(str_is_nil(not_nil) == false);
    assert(str_is_nil(nil) == true);
}

void test_str_token() {
    {
        str string = str_from_native("take on me");
        str substring = str_from_native(" ");
        str first = str_token(string, substring, 0);
        str second = str_token(string, substring, 1);
        str third = str_token(string, substring, 2);
        str fourth = str_token(string, substring, 3);

        assert(str_equals(first, str_from_native("take")));
        assert(str_equals(second, str_from_native("on")));
        assert(str_equals(third, str_from_native("me")));
        assert(str_is_nil(fourth));
    }

    {
        str string = str_from_native("take on me");
        str substring = str_from_native(",");
        str token = str_token(string, substring, 0);

        assert(str_is_nil(token));
    }
}

void test_str_tokens() {
    {
        str string = str_from_native("banana, apple, orange, grape");
        str substring = str_from_native(", ");

        assert(str_tokens(string, substring) == 4);
    }

    {
        str string = str_from_native(", apple, orange, ");
        str substring = str_from_native(", ");

        assert(str_tokens(string, substring) == 4);
    }

    {
        str string = str_from_native(", ");
        str substring = str_from_native(", ");

        assert(str_tokens(string, substring) == 2);
    }

    {
        str string = str_from_native("");
        str substring = str_from_native(", ");

        assert(str_tokens(string, substring) == 0);
    }
}

void test_str_tokenize() {
    str string = str_from_native("banana, apple, orange, grape");
    str substring = str_from_native(", ");
    size_t size = str_tokens(string, substring);
    str array[size];
    str *tokens = str_tokenize(string, substring, array);

    assert(str_equals(tokens[0], str_from_native("banana")));
    assert(str_equals(tokens[1], str_from_native("apple")));
    assert(str_equals(tokens[2], str_from_native("orange")));
    assert(str_equals(tokens[3], str_from_native("grape")));
}

void test_str_concat() {
    str hello = str_from_native("Hello, ");
    str world = str_from_native("World!");

    char buffer[hello.size + world.size];

    str hello_world = str_concat(hello, world, buffer);

    assert(str_equals(hello_world, str_from_native("Hello, World!")));
}

void test_str_to_uppercase() {
    char native[] = "hello world";
    str string = str_from_native(native);
    str lower = str_to_uppercase(string);

    assert(str_equals(lower, str_from_native("HELLO WORLD")));
}

void test_str_to_lowercase() {
    char native[] = "HELLO WORLD";
    str string = str_from_native(native);
    str lower = str_to_lowercase(string);

    assert(str_equals(lower, str_from_native("hello world")));
}

void test_str_trim() {
    {
        char native[] = " \n \t  Hello, World! \t \r \n  ";
        str string = str_from_native(native);
        str trimmed = str_trim(string);

        assert(str_equals(trimmed, str_from_native("Hello, World!")));
    }

    {
        char native[] = " \n \t \r \n  ";
        str string = str_from_native(native);
        str trimmed = str_trim(string);

        assert(str_equals(trimmed, str_from_native("")));
    }
}

void test_str_occurrences() {
    {
        char native[] = "a fat cat has a hat at head";
        str string = str_from_native(native);
        str substring = str_from_native("at");

        assert(str_occurrences(string, substring) == 4);
    }

    {
        char native[] = "catcatcatcatcat";
        str string = str_from_native(native);
        str substring = str_from_native("cat");

        assert(str_occurrences(string, substring) == 5);
    }
}

void test_str_replace_size() {
    {
        char native[] = "not not, not not!";
        str string = str_from_native(native);
        str find = str_from_native("not");
        str replace = str_from_native("dont");

        assert(str_replace_size(string, find, replace) == 21);
    }

    {
        char native[] = "not not, not not!";
        str string = str_from_native(native);
        str find = str_from_native("not");
        str replace = str_from_native("no");

        assert(str_replace_size(string, find, replace) == 13);
    }
}

void test_str_replace() {
    {
        char native[] = "not not, not not!";
        str string = str_from_native(native);
        str find = str_from_native("not");
        str replace = str_from_native("dont");
        char buffer[str_replace_size(string, find, replace)];
        str replaced = str_replace(string, find, replace, buffer);

        assert(str_equals(replaced, str_from_native("dont dont, dont dont!")));
    }

    {
        char native[] = "not not, not not!";
        str string = str_from_native(native);
        str find = str_from_native("not");
        str replace = str_from_native("no");
        char buffer[str_replace_size(string, find, replace)];
        str replaced = str_replace(string, find, replace, buffer);

        assert(str_equals(replaced, str_from_native("no no, no no!")));
    }

    {
        char native[] = "my dog is not a cat!";
        str string = str_from_native(native);
        str find = str_from_native("not ");
        str replace = str_from_native("");
        char buffer[str_replace_size(string, find, replace)];
        str replaced = str_replace(string, find, replace, buffer);

        assert(str_equals(replaced, str_from_native("my dog is a cat!")));
    }
}

int main() {
    test_str_from_native();
    test_str_from_buffer();
    test_str_index_of();
    test_str_to_native();
    test_str_slice();
    test_str_compare();
    test_str_equals();
    test_str_is_nil();
    test_str_token();
    test_str_tokens();
    test_str_tokenize();
    test_str_concat();
    test_str_to_uppercase();
    test_str_to_lowercase();
    test_str_trim();
    test_str_occurrences();
    test_str_replace_size();
    test_str_replace();

    return 0;
}
