# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(Tests LANGUAGES CXX)

# ---- Find Google Test ----

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

# ---- Tests ----

add_executable(
    NitroTests 
    source/JsonHelperTest.cpp
    source/RectangleTest.cpp
    source/RectangleIntersectionTest.cpp
    utilities/Comparisons.cpp
)

target_include_directories(NitroTests 
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(NitroTests
    PRIVATE nitro_rectangles_lib
    PRIVATE gtest_main
    PRIVATE gmock_main
)

target_compile_features(NitroTests PRIVATE cxx_std_20)

enable_testing()
include(GoogleTest)
gtest_discover_tests(NitroTests)

# ---- End-of-file commands ----

add_folders(Test)
