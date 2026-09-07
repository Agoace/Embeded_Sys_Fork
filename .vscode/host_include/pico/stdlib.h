#ifndef HOST_PICO_STDLIB_H
#define HOST_PICO_STDLIB_H

/*
 * Minimal host replacements for the Pico SDK calls used by LAB1/basic.c.
 * This header is only on the include path of the VS Code host build; Pico
 * CMake builds continue to use the real SDK header.
 */

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

static inline void stdio_init_all(void)
{
}

static inline void sleep_ms(uint32_t milliseconds)
{
    struct timespec remaining = {
        .tv_sec = (time_t)(milliseconds / 1000u),
        .tv_nsec = (long)(milliseconds % 1000u) * 1000000L,
    };

    while (nanosleep(&remaining, &remaining) == -1 && errno == EINTR) {
    }
}

#endif
