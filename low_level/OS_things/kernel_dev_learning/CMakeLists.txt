cmake_minimum_required(VERSION 3.31.5)

# Cross compiling stuff
set(CMAKE_SYSTEM_NAME i686-elf)
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_C_FLAGS "-nostdlib -ffreestanding -std=gnu99 -O2 -Wall -Wextra")
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_ASM_NASM_FLAGS "-felf32")
set(CMAKE_FIND_ROOT_PATH /usr/i686-elf)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(simpleos C ASM_NASM)

add_library(boot OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/src/boot/multiboot.asm)
add_library(kernel OBJECT ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/kernel.c)

add_executable(simpleos.bin $<TARGET_OBJECTS:boot> $<TARGET_OBJECTS:kernel>)
target_link_options(simpleos.bin PRIVATE -lgcc -T ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/linker.ld)
