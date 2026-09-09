cmake_minimum_required(VERSION 3.13)

# Standalone project, same shape as LAB1. The version of this file in the
# lab brief was a drop-in for the pico-examples tree: it called
# example_auto_set_url(), which is defined only by pico-examples' own
# top-level CMake, and it never called pico_sdk_init(). Neither works here.
#
# Build:
#   cmake -B build -DPICO_BOARD=pico_w -S .
#   cmake --build build -j
include(pico_sdk_import.cmake)

project(lab2 C CXX ASM)

pico_sdk_init()

# --------------------------------------------------------------------
# GPIO - INPUT: button on GP20 gates an LED on GP15.
# --------------------------------------------------------------------
add_executable(picow_blink_button picow_blink_button.c)
target_link_libraries(picow_blink_button pico_stdlib)
pico_enable_stdio_usb(picow_blink_button 1)
pico_enable_stdio_uart(picow_blink_button 0)
pico_add_extra_outputs(picow_blink_button)
target_compile_options(picow_blink_button PRIVATE -Wall -Wextra)

# --------------------------------------------------------------------
# GPIO - OUTPUT: 1 s high / 2 s low pulse train on GP15.
# --------------------------------------------------------------------
add_executable(pulse pulse.c)
target_link_libraries(pulse pico_stdlib)
pico_enable_stdio_usb(pulse 1)
pico_enable_stdio_uart(pulse 0)
pico_add_extra_outputs(pulse)
target_compile_options(pulse PRIVATE -Wall -Wextra)

# --------------------------------------------------------------------
# UART receiver for the paired task. Pico B runs this; Pico A runs
# pico-examples/uart/hello_uart.
#
# stdio_uart is deliberately OFF. uart_rx.c reads uart0 on GP0/GP1, and
# those are the same pins stdio would claim - printf and the received
# data would then fight over one peripheral. Read the printf over USB.
# --------------------------------------------------------------------
add_executable(uart_rx uart/uart_rx.c)
target_link_libraries(uart_rx pico_stdlib hardware_uart)
pico_enable_stdio_usb(uart_rx 1)
pico_enable_stdio_uart(uart_rx 0)
pico_add_extra_outputs(uart_rx)
target_compile_options(uart_rx PRIVATE -Wall -Wextra)

# --------------------------------------------------------------------
# The EXERCISE target goes here once ex2.c exists: UART1 on GP8/GP9,
# GP22 selects between sending '1' and sending 'A'..'Z'.
# --------------------------------------------------------------------
# add_executable(ex2 ex2.c)
# target_link_libraries(ex2 pico_stdlib hardware_uart)
# pico_enable_stdio_usb(ex2 1)
# pico_enable_stdio_uart(ex2 0)
# pico_add_extra_outputs(ex2)
# target_compile_options(ex2 PRIVATE -Wall -Wextra)

# bughunt/ and cmdparse/ are separate standalone projects with their own
# pico_sdk_init(). Configure them from inside their own folders - they
# cannot be add_subdirectory()'d into this one.
