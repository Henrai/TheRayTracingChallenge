include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

FetchContent_MakeAvailable(googletest)




set(TEST_BINARY "UnitTests")

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${TEST_BINARY} ${TEST_SOURCES})


target_link_libraries(
  ${TEST_BINARY}
  PRIVATE  RayTracer_lib gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_BINARY})