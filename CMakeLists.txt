cmake_minimum_required(VERSION 2.8.2)

# Download and unpack googletest at configure time
configure_file(thirdparty/gtest/CMakeLists.txt googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

set(PROJECT_NAME chessy)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(SRC_PATH src)
set(SOURCE_FILES ${SRC_PATH}/io_interface.cpp ${SRC_PATH}/solution.cpp ${SRC_PATH}/solver.cpp
        ${SRC_PATH}/colorless_independent_board.cpp ${SRC_PATH}/independent_board.cpp
        ${SRC_PATH}/dominant_board.cpp)
add_executable(${PROJECT_NAME} ${SRC_PATH}/main.cpp ${SOURCE_FILES})

set(TEST_PROJECT_NAME tests)
add_executable(${TEST_PROJECT_NAME} test/tests.cpp ${SOURCE_FILES})
target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main)