cmake_minimum_required(VERSION 3.21.0...3.22.2)
project(cmc VERSION 0.1.0
            DESCRIPTION "A Minecraft client/server compatible with version 1.18"
            LANGUAGES C)

set(CMAKE_C_STANDARD 17)

# use vcpkg
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
else()
    set(CMAKE_TOOLCHAIN_FILE "submodules/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

find_package(glfw3 CONFIG REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include(CTest)
enable_testing()

add_executable(cmc_server src/server.c)
target_include_directories(cmc_server PRIVATE include)

add_executable(cmc_client src/client.c)
target_include_directories(cmc_client PRIVATE include)

add_executable(cmc_test_buffer_builder tests/libmc/buffer_builder.c)
target_include_directories(cmc_test_buffer_builder PRIVATE include)
add_test(NAME buffer_builder COMMAND cmc_test_buffer_builder)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
