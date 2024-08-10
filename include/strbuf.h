#ifndef STRBUF_H
#define STRBUF_H

#include "str.h"
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Structure representing the internal data of a string buffer.
 */
typedef struct {
    size_t capacity; /**< The total capacity of the string buffer */
    size_t size;     /**< The current size of the string buffer */
    char *content;   /**< Pointer to the content of the string buffer */
} strbuf_data;

/**
 * @brief Structure representing a string buffer.
 */
typedef struct {
    strbuf_data *data; /**< Pointer to the internal data of the string buffer */
} strbuf;

/**
 * @brief Initialize a new string buffer.
 *
 * @return A newly initialized string buffer.
 */
strbuf strbuf_init();

/**
 * @brief Free the memory associated with a string buffer.
 *
 * @param buf The string buffer to free.
 */
void strbuf_free(strbuf buf);

/**
 * @brief Get the capacity of a string buffer.
 *
 * @param buf The string buffer.
 * @return The capacity of the string buffer.
 */
size_t strbuf_capacity(strbuf buf);

/**
 * @brief Get the current size of a string buffer.
 *
 * @param buf The string buffer.
 * @return The current size of the string buffer.
 */
size_t strbuf_size(strbuf buf);

/**
 * @brief Write a native C string to the string buffer.
 *
 * @param buf The string buffer.
 * @param native The native C string to write.
 */
void strbuf_write_native(strbuf buf, const char *native);

/**
 * @brief Write a `str` structure to the string buffer.
 *
 * @param buf The string buffer.
 * @param string The `str` structure to write.
 */
void strbuf_write_str(strbuf buf, str string);

/**
 * @brief Write a single character to the string buffer.
 *
 * @param buf The string buffer.
 * @param character The character to write.
 */
void strbuf_write_char(strbuf buf, char character);

/**
 * @brief Convert the contents of the string buffer to a newly allocated native
 * C string.
 *
 * @param buf The string buffer.
 * @return A pointer to the newly allocated native C string. The caller is
 * responsible for freeing the memory.
 */
char *strbuf_to_owned_native(strbuf buf);

#endif
