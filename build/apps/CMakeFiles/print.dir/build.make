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
include apps/CMakeFiles/print.dir/depend.make

# Include the progress variables for this target.
include apps/CMakeFiles/print.dir/progress.make

# Include the compile flags for this target's objects.
include apps/CMakeFiles/print.dir/flags.make

apps/CMakeFiles/print.dir/print.cpp.o: apps/CMakeFiles/print.dir/flags.make
apps/CMakeFiles/print.dir/print.cpp.o: ../apps/print.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/henn/dev/ArcadeBT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/CMakeFiles/print.dir/print.cpp.o"
	cd /home/henn/dev/ArcadeBT/build/apps && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/print.dir/print.cpp.o -c /home/henn/dev/ArcadeBT/apps/print.cpp

apps/CMakeFiles/print.dir/print.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/print.dir/print.cpp.i"
	cd /home/henn/dev/ArcadeBT/build/apps && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/henn/dev/ArcadeBT/apps/print.cpp > CMakeFiles/print.dir/print.cpp.i

apps/CMakeFiles/print.dir/print.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/print.dir/print.cpp.s"
	cd /home/henn/dev/ArcadeBT/build/apps && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/henn/dev/ArcadeBT/apps/print.cpp -o CMakeFiles/print.dir/print.cpp.s

# Object files for target print
print_OBJECTS = \
"CMakeFiles/print.dir/print.cpp.o"

# External object files for target print
print_EXTERNAL_OBJECTS =

apps/print: apps/CMakeFiles/print.dir/print.cpp.o
apps/print: apps/CMakeFiles/print.dir/build.make
apps/print: src/libarcade.a
apps/print: /home/henn/local/lib/libz3.so.4.8.15.0
apps/print: apps/CMakeFiles/print.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/henn/dev/ArcadeBT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable print"
	cd /home/henn/dev/ArcadeBT/build/apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/print.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/CMakeFiles/print.dir/build: apps/print

.PHONY : apps/CMakeFiles/print.dir/build

apps/CMakeFiles/print.dir/clean:
	cd /home/henn/dev/ArcadeBT/build/apps && $(CMAKE_COMMAND) -P CMakeFiles/print.dir/cmake_clean.cmake
.PHONY : apps/CMakeFiles/print.dir/clean

apps/CMakeFiles/print.dir/depend:
	cd /home/henn/dev/ArcadeBT/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/henn/dev/ArcadeBT /home/henn/dev/ArcadeBT/apps /home/henn/dev/ArcadeBT/build /home/henn/dev/ArcadeBT/build/apps /home/henn/dev/ArcadeBT/build/apps/CMakeFiles/print.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/CMakeFiles/print.dir/depend
