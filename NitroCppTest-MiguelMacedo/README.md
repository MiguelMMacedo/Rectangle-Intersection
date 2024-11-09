# Nitro C++ Proficiency Test

This is my submission for the Nitro C++ Proficiency Test.
This is a console program which takes a command line argument identifying a json file, 
which contains rectangle definitions
The output of the program reports all intersections of the rectangles

See this [PDF](docs/C___Proficiency_test_-_Updated.pdf) for the problem definition

# Prerequisites

Before compiling and running this project, ensure you have the following installed:

- **C++ compiler**: Requires a compiler supporting C++20 (GCC, Clang, MSVC)
- **CMake** (version 3.15 or higher)

# Building with CMake

## Build

To compile the project in release mode with a single-configuration generator, 
such as Unix Makefiles:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

For building in release mode with a multi-configuration generator, 
like those used by Visual Studio:

```sh
cmake -S . -B build
cmake --build build --config Release
```

### Building with MSVC

Note that MSVC by default is not standards compliant and you need to pass some
flags to make it behave properly. See the `flags-msvc` preset in the
[CMakePresets.json](CMakePresets.json) file for the flags and with what
variable to provide them to CMake during configuration.

## Install

Firstly, ensure that the project has been built with the aforementioned commands

To install the release mode artifacts with a single-configuration generator, 
such as Unix Makefiles:

```sh
cmake --install build
```

For a multi-configuration generator, like Visual Studio:

```sh
cmake --install build --config Release
```


