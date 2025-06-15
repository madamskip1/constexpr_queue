cmake_minimum_required(VERSION 3.10.0)

project(Constexpr_Queue)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_STANDARD 20)
endif ()

add_library(Constexpr_Queue INTERFACE)
add_library(MaCe::Constexpr_Queue ALIAS Constexpr_Queue)

target_include_directories(Constexpr_Queue INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

enable_testing()
add_subdirectory(tests)