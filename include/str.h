#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Structure representing a string.
 */
typedef struct {
    char *data;  /**< Pointer to the string data */
    size_t size; /**< Size of the string */
} str;

/**
 * @brief A constant representing a nil string.
 */
extern const str STR_NIL;

/**
 * @brief Create a string from a native C string.
 *
 * @param native The native C string.
 * @return A string structure representing the native string.
 */
str str_from_native(char *native);

/**
 * @brief Create a string from a buffer with a specified size.
 *
 * @param buffer The buffer containing the string data.
 * @param size The size of the string.
 * @return A string structure representing the buffer.
 */
str str_from_buffer(char *buffer, size_t size);

/**
 * @brief Find the index of a substring within a string.
 *
 * @param string The string to search within.
 * @param substring The substring to search for.
 * @return The index of the substring within the string, or SIZE_MAX if not
 * found.
 */
size_t str_index_of(str string, str substring);

/**
 * @brief Convert a string structure to a native C string.
 *
 * @param string The string structure.
 * @param buffer The buffer to store the native string.
 * @return A pointer to the buffer containing the native string.
 */
char *str_to_native(str string, char *buffer);

/**
 * @brief Slice a portion of a string.
 *
 * @param string The string to slice.
 * @param start The starting index of the slice.
 * @param chars The number of characters to include in the slice.
 * @return A string structure representing the slice.
 */
str str_slice(str string, size_t start, size_t chars);

/**
 * @brief Compare two strings.
 *
 * @param first The first string.
 * @param second The second string.
 * @return 0 if the strings are equal, 1 if the first string is greater, -1 if
 * the second string is greater.
 */
int str_compare(str first, str second);

/**
 * @brief Check if two strings are equal.
 *
 * @param first The first string.
 * @param second The second string.
 * @return true if the strings are equal, false otherwise.
 */
bool str_equals(str first, str second);

/**
 * @brief Check if a string is nil.
 *
 * @param string The string to check.
 * @return true if the string is nil, false otherwise.
 */
bool str_is_nil(str string);

/**
 * @brief Tokenize a string by a substring.
 *
 * @param string The string to tokenize.
 * @param substring The delimiter substring.
 * @param token The index of the token to retrieve.
 * @return A string structure representing the token.
 */
str str_token(str string, str substring, size_t token);

/**
 * @brief Count the number of tokens in a string.
 *
 * @param string The string to tokenize.
 * @param substring The delimiter substring.
 * @return The number of tokens.
 */
size_t str_tokens(str string, str substring);

/**
 * @brief Tokenize a string into an array of strings.
 *
 * @param string The string to tokenize.
 * @param substring The delimiter substring.
 * @param array The array to store the tokens.
 * @return A pointer to the array of tokens.
 */
str *str_tokenize(str string, str substring, str *array);

/**
 * @brief Concatenate two strings.
 *
 * @param first The first string.
 * @param second The second string.
 * @param buffer The buffer to store the concatenated string.
 * @return A string structure representing the concatenated string.
 */
str str_concat(str first, str second, char *buffer);

/**
 * @brief Convert a string to uppercase.
 *
 * @param string The string to convert.
 * @return A string structure representing the uppercase string.
 */
str str_to_uppercase(str string);

/**
 * @brief Convert a string to lowercase.
 *
 * @param string The string to convert.
 * @return A string structure representing the lowercase string.
 */
str str_to_lowercase(str string);

/**
 * @brief Trim whitespace from the beginning and end of a string.
 *
 * @param string The string to trim.
 * @return A string structure representing the trimmed string.
 */
str str_trim(str string);

/**
 * @brief Count the number of occurrences of a substring within a string.
 *
 * @param string The string to search within.
 * @param substring The substring to count.
 * @return The number of occurrences of the substring.
 */
size_t str_occurrences(str string, str substring);

/**
 * @brief Calculate the size of the buffer needed to replace a substring within
 * a string.
 *
 * @param string The string to modify.
 * @param find The substring to find.
 * @param replace The substring to replace with.
 * @return The size of the buffer needed for the replacement.
 */
size_t str_replace_size(str string, str find, str replace);

/**
 * @brief Replace a substring within a string with another substring.
 *
 * @param string The string to modify.
 * @param find The substring to find.
 * @param replace The substring to replace with.
 * @param buffer The buffer to store the modified string.
 * @return A string structure representing the modified string.
 */
str str_replace(str string, str find, str replace, char *buffer);

#endif
