# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chen/Desktop/libdivsufsort-2.0.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/Desktop/libdivsufsort-2.0.1

# Include any dependencies generated for this target.
include examples/CMakeFiles/sasearch.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/sasearch.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/sasearch.dir/flags.make

examples/CMakeFiles/sasearch.dir/sasearch.o: examples/CMakeFiles/sasearch.dir/flags.make
examples/CMakeFiles/sasearch.dir/sasearch.o: examples/sasearch.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/chen/Desktop/libdivsufsort-2.0.1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/sasearch.dir/sasearch.o"
	cd /home/chen/Desktop/libdivsufsort-2.0.1/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/sasearch.dir/sasearch.o   -c /home/chen/Desktop/libdivsufsort-2.0.1/examples/sasearch.c

examples/CMakeFiles/sasearch.dir/sasearch.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sasearch.dir/sasearch.i"
	cd /home/chen/Desktop/libdivsufsort-2.0.1/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/chen/Desktop/libdivsufsort-2.0.1/examples/sasearch.c > CMakeFiles/sasearch.dir/sasearch.i

examples/CMakeFiles/sasearch.dir/sasearch.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sasearch.dir/sasearch.s"
	cd /home/chen/Desktop/libdivsufsort-2.0.1/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/chen/Desktop/libdivsufsort-2.0.1/examples/sasearch.c -o CMakeFiles/sasearch.dir/sasearch.s

examples/CMakeFiles/sasearch.dir/sasearch.o.requires:
.PHONY : examples/CMakeFiles/sasearch.dir/sasearch.o.requires

examples/CMakeFiles/sasearch.dir/sasearch.o.provides: examples/CMakeFiles/sasearch.dir/sasearch.o.requires
	$(MAKE) -f examples/CMakeFiles/sasearch.dir/build.make examples/CMakeFiles/sasearch.dir/sasearch.o.provides.build
.PHONY : examples/CMakeFiles/sasearch.dir/sasearch.o.provides

examples/CMakeFiles/sasearch.dir/sasearch.o.provides.build: examples/CMakeFiles/sasearch.dir/sasearch.o

# Object files for target sasearch
sasearch_OBJECTS = \
"CMakeFiles/sasearch.dir/sasearch.o"

# External object files for target sasearch
sasearch_EXTERNAL_OBJECTS =

examples/sasearch: examples/CMakeFiles/sasearch.dir/sasearch.o
examples/sasearch: lib/libdivsufsort.a
examples/sasearch: examples/CMakeFiles/sasearch.dir/build.make
examples/sasearch: examples/CMakeFiles/sasearch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable sasearch"
	cd /home/chen/Desktop/libdivsufsort-2.0.1/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sasearch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/sasearch.dir/build: examples/sasearch
.PHONY : examples/CMakeFiles/sasearch.dir/build

examples/CMakeFiles/sasearch.dir/requires: examples/CMakeFiles/sasearch.dir/sasearch.o.requires
.PHONY : examples/CMakeFiles/sasearch.dir/requires

examples/CMakeFiles/sasearch.dir/clean:
	cd /home/chen/Desktop/libdivsufsort-2.0.1/examples && $(CMAKE_COMMAND) -P CMakeFiles/sasearch.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/sasearch.dir/clean

examples/CMakeFiles/sasearch.dir/depend:
	cd /home/chen/Desktop/libdivsufsort-2.0.1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/Desktop/libdivsufsort-2.0.1 /home/chen/Desktop/libdivsufsort-2.0.1/examples /home/chen/Desktop/libdivsufsort-2.0.1 /home/chen/Desktop/libdivsufsort-2.0.1/examples /home/chen/Desktop/libdivsufsort-2.0.1/examples/CMakeFiles/sasearch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/sasearch.dir/depend
