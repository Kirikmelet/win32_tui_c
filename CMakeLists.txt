cmake_minimum_required(VERSION "3.26")
project(test_c LANGUAGES C)

# Settings
set(C_STANDARD 23)

# Folders
set(TEST_C_DIR "src")
set(TEST_C_INCLUDE_DIR "src")

file(GLOB_RECURSE TEST_C_BIN_SOURCES "${TEST_C_DIR}/*.c" "${TEST_C_INCLUDE_DIR}/*.h")

add_executable(main "${TEST_C_BIN_SOURCES}")
target_include_directories(main PRIVATE "${TEST_C_INCLUDE_DIR}")
