cmake_minimum_required(VERSION 3.10.0)

project(Constexpr_Queue
    VERSION 1.0.0
    LANGUAGES CXX
)

option(MaCe_Constexpr_Queue_BUILD_TESTING "Build tests for MaCe Constexpr_Queue" OFF)
option(MaCe_Constexpr_Queue_INSTALL "Enable installation of MaCe::Constexpr_Queue targets and config files" OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
else ()
    if (CMAKE_CXX_STANDARD LESS 20)
        message(FATAL_ERROR "MaCe::Constexpr_queue requires C++20 or higher!")
    endif()
endif ()

add_library(Constexpr_Queue INTERFACE)
add_library(MaCe::Constexpr_Queue ALIAS Constexpr_Queue)

target_include_directories(Constexpr_Queue INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


if (MaCe_Constexpr_Queue_INSTALL)
    install(TARGETS Constexpr_Queue
        EXPORT Constexpr_QueueTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
    )

    install(EXPORT Constexpr_QueueTargets
        FILE Constexpr_QueueTargets.cmake
        NAMESPACE MaCe::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MaCe/Constexpr_Queue
    )

    install(DIRECTORY include/MaCe
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    export(EXPORT Constexpr_QueueTargets
        FILE Constexpr_QueueTargets.cmake
        NAMESPACE MaCe::
    )

    include(CMakePackageConfigHelpers)

    set(Constexpr_Queue_version_file_name "${PROJECT_NAME}-Version.cmake")
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${Constexpr_Queue_version_file_name}"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${Constexpr_Queue_version_file_name}"
        DESTINATION lib/cmake/MaCe/Constexpr_Queue
    )
endif ()


if (MaCe_Constexpr_Queue_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
