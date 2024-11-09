cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    nitro_rectangles
    VERSION 0.1.0
    DESCRIPTION "Nitro Interview Project"
    HOMEPAGE_URL "https://www.gonitro.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----
add_library(
    nitro_rectangles_lib OBJECT
    src/JsonHelper.cpp
    src/Rectangle.cpp
    src/RectangleIntersection.cpp
)

target_include_directories(
    nitro_rectangles_lib ${warning_guard}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/libs
)

target_compile_features(nitro_rectangles_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(nitro_rectangles_exe src/main.cpp)
add_executable(nitro_rectangles::exe ALIAS nitro_rectangles_exe)

set_property(TARGET nitro_rectangles_exe PROPERTY OUTPUT_NAME nitro_rectangles)

target_compile_features(nitro_rectangles_exe PRIVATE cxx_std_20)

target_link_libraries(nitro_rectangles_exe PRIVATE nitro_rectangles_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT nitro_rectangles_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of nitro_rectangles"
  )
endif()

include(cmake/dev-mode.cmake)
