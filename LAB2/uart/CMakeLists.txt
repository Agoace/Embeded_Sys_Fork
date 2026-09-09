cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(lab2_uart C CXX ASM)
pico_sdk_init()

# Pico A: UART sender
add_executable(hello_uart hello_uart.c)
target_link_libraries(hello_uart pico_stdlib)
pico_enable_stdio_usb(hello_uart 1)
pico_enable_stdio_uart(hello_uart 0)
pico_add_extra_outputs(hello_uart)

# Pico B: UART receiver with USB terminal output
add_executable(uart_rx uart_rx.c)
target_link_libraries(uart_rx pico_stdlib)
pico_enable_stdio_usb(uart_rx 1)
pico_enable_stdio_uart(uart_rx 0)
pico_add_extra_outputs(uart_rx)

target_compile_options(hello_uart PRIVATE -Wall -Wextra)
target_compile_options(uart_rx PRIVATE -Wall -Wextra)