include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(googletest)


add_executable(Constexpr_Queue_tests)

target_sources(Constexpr_Queue_tests
    PRIVATE
        functionality_tests.cpp
        types_tests.cpp
)

target_link_libraries(Constexpr_Queue_tests
    PRIVATE
        gtest_main
        Constexpr_Queue
)

include(GoogleTest)
gtest_discover_tests(Constexpr_Queue_tests)


add_executable(Constexpr_Queue_consteval_test)

target_compile_options(Constexpr_Queue_consteval_test PRIVATE -Werror=invalid-constexpr -O0)

target_sources(Constexpr_Queue_consteval_test
    PRIVATE
        consteval_compilation_test.cpp
)
target_link_libraries(Constexpr_Queue_consteval_test
    PRIVATE
        Constexpr_Queue
)