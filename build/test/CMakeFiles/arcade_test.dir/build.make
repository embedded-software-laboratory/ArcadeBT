# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/henn/dev/ArcadeBT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/henn/dev/ArcadeBT/build

# Include any dependencies generated for this target.
include test/CMakeFiles/arcade_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/arcade_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/arcade_test.dir/flags.make

test/CMakeFiles/arcade_test.dir/ir/expression_test.cpp.o: test/CMakeFiles/arcade_test.dir/flags.make
test/CMakeFiles/arcade_test.dir/ir/expression_test.cpp.o: ../test/ir/expression_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henn/dev/ArcadeBT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/arcade_test.dir/ir/expression_test.cpp.o"
	cd /home/henn/dev/ArcadeBT/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arcade_test.dir/ir/expression_test.cpp.o -c /home/henn/dev/ArcadeBT/test/ir/expression_test.cpp

test/CMakeFiles/arcade_test.dir/ir/expression_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arcade_test.dir/ir/expression_test.cpp.i"
	cd /home/henn/dev/ArcadeBT/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henn/dev/ArcadeBT/test/ir/expression_test.cpp > CMakeFiles/arcade_test.dir/ir/expression_test.cpp.i

test/CMakeFiles/arcade_test.dir/ir/expression_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arcade_test.dir/ir/expression_test.cpp.s"
	cd /home/henn/dev/ArcadeBT/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henn/dev/ArcadeBT/test/ir/expression_test.cpp -o CMakeFiles/arcade_test.dir/ir/expression_test.cpp.s

test/CMakeFiles/arcade_test.dir/examples_test.cpp.o: test/CMakeFiles/arcade_test.dir/flags.make
test/CMakeFiles/arcade_test.dir/examples_test.cpp.o: ../test/examples_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henn/dev/ArcadeBT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/arcade_test.dir/examples_test.cpp.o"
	cd /home/henn/dev/ArcadeBT/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arcade_test.dir/examples_test.cpp.o -c /home/henn/dev/ArcadeBT/test/examples_test.cpp

test/CMakeFiles/arcade_test.dir/examples_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arcade_test.dir/examples_test.cpp.i"
	cd /home/henn/dev/ArcadeBT/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henn/dev/ArcadeBT/test/examples_test.cpp > CMakeFiles/arcade_test.dir/examples_test.cpp.i

test/CMakeFiles/arcade_test.dir/examples_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arcade_test.dir/examples_test.cpp.s"
	cd /home/henn/dev/ArcadeBT/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henn/dev/ArcadeBT/test/examples_test.cpp -o CMakeFiles/arcade_test.dir/examples_test.cpp.s

# Object files for target arcade_test
arcade_test_OBJECTS = \
"CMakeFiles/arcade_test.dir/ir/expression_test.cpp.o" \
"CMakeFiles/arcade_test.dir/examples_test.cpp.o"

# External object files for target arcade_test
arcade_test_EXTERNAL_OBJECTS =

test/arcade_test: test/CMakeFiles/arcade_test.dir/ir/expression_test.cpp.o
test/arcade_test: test/CMakeFiles/arcade_test.dir/examples_test.cpp.o
test/arcade_test: test/CMakeFiles/arcade_test.dir/build.make
test/arcade_test: /usr/lib/x86_64-linux-gnu/libgtest.a
test/arcade_test: /usr/lib/x86_64-linux-gnu/libgtest_main.a
test/arcade_test: src/libarcade.a
test/arcade_test: /usr/lib/x86_64-linux-gnu/libgtest.a
test/arcade_test: /home/henn/local/lib/libz3.so.4.8.15.0
test/arcade_test: test/CMakeFiles/arcade_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/henn/dev/ArcadeBT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable arcade_test"
	cd /home/henn/dev/ArcadeBT/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arcade_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/henn/dev/ArcadeBT/build/test && /usr/bin/cmake -D TEST_TARGET=arcade_test -D TEST_EXECUTABLE=/home/henn/dev/ArcadeBT/build/test/arcade_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/henn/dev/ArcadeBT/build/test -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=arcade_test_TESTS -D CTEST_FILE=/home/henn/dev/ArcadeBT/build/test/arcade_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -P /usr/share/cmake-3.16/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
test/CMakeFiles/arcade_test.dir/build: test/arcade_test

.PHONY : test/CMakeFiles/arcade_test.dir/build

test/CMakeFiles/arcade_test.dir/clean:
	cd /home/henn/dev/ArcadeBT/build/test && $(CMAKE_COMMAND) -P CMakeFiles/arcade_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/arcade_test.dir/clean

test/CMakeFiles/arcade_test.dir/depend:
	cd /home/henn/dev/ArcadeBT/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/henn/dev/ArcadeBT /home/henn/dev/ArcadeBT/test /home/henn/dev/ArcadeBT/build /home/henn/dev/ArcadeBT/build/test /home/henn/dev/ArcadeBT/build/test/CMakeFiles/arcade_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/arcade_test.dir/depend

