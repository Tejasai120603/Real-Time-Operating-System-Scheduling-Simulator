Ycmake_minimum_required(VERSION 3.13)
project(FreeRTOS_POSIX_Demo C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(FREERTOS_POSIX_PATH "${CMAKE_SOURCE_DIR}/FreeRTOS-Plus-POSIX")

include_directories(
    ${FREERTOS_POSIX_PATH}/include
    ${FREERTOS_POSIX_PATH}/FreeRTOS-Plus-POSIX/include
)

file(GLOB POSIX_SOURCES
    "${FREERTOS_POSIX_PATH}/source/*.c"
)

add_library(freertos_posix STATIC ${POSIX_SOURCES})

add_executable(posix_demo
    ${FREERTOS_POSIX_PATH}/test/posix_demo.c
)

target_link_libraries(posix_demo freertos_posix)

if (MINGW)
    message(STATUS "Building with MinGW on Windows")
    target_compile_options(freertos_posix PRIVATE -Wall -Wextra)
elseif (CMAKE_COMPILER_IS_GNUCC)
    target_compile_options(freertos_posix PRIVATE -Wall -Wextra)
endif()

set_target_properties(freertos_posix PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_target_properties(posix_demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message(STATUS "✅ FreeRTOS+POSIX CMake project configured successfully")
