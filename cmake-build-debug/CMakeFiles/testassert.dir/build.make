# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/xie2481/Silly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xie2481/Silly/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/testassert.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testassert.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testassert.dir/flags.make

CMakeFiles/testassert.dir/tests/test_assert.cc.o: CMakeFiles/testassert.dir/flags.make
CMakeFiles/testassert.dir/tests/test_assert.cc.o: ../tests/test_assert.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xie2481/Silly/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testassert.dir/tests/test_assert.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testassert.dir/tests/test_assert.cc.o -c /home/xie2481/Silly/tests/test_assert.cc

CMakeFiles/testassert.dir/tests/test_assert.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testassert.dir/tests/test_assert.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xie2481/Silly/tests/test_assert.cc > CMakeFiles/testassert.dir/tests/test_assert.cc.i

CMakeFiles/testassert.dir/tests/test_assert.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testassert.dir/tests/test_assert.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xie2481/Silly/tests/test_assert.cc -o CMakeFiles/testassert.dir/tests/test_assert.cc.s

CMakeFiles/testassert.dir/tests/test_assert.cc.o.requires:

.PHONY : CMakeFiles/testassert.dir/tests/test_assert.cc.o.requires

CMakeFiles/testassert.dir/tests/test_assert.cc.o.provides: CMakeFiles/testassert.dir/tests/test_assert.cc.o.requires
	$(MAKE) -f CMakeFiles/testassert.dir/build.make CMakeFiles/testassert.dir/tests/test_assert.cc.o.provides.build
.PHONY : CMakeFiles/testassert.dir/tests/test_assert.cc.o.provides

CMakeFiles/testassert.dir/tests/test_assert.cc.o.provides.build: CMakeFiles/testassert.dir/tests/test_assert.cc.o


# Object files for target testassert
testassert_OBJECTS = \
"CMakeFiles/testassert.dir/tests/test_assert.cc.o"

# External object files for target testassert
testassert_EXTERNAL_OBJECTS =

../bin/testassert: CMakeFiles/testassert.dir/tests/test_assert.cc.o
../bin/testassert: CMakeFiles/testassert.dir/build.make
../bin/testassert: ../lib/libSilly.so
../bin/testassert: CMakeFiles/testassert.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xie2481/Silly/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/testassert"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testassert.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testassert.dir/build: ../bin/testassert

.PHONY : CMakeFiles/testassert.dir/build

CMakeFiles/testassert.dir/requires: CMakeFiles/testassert.dir/tests/test_assert.cc.o.requires

.PHONY : CMakeFiles/testassert.dir/requires

CMakeFiles/testassert.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testassert.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testassert.dir/clean

CMakeFiles/testassert.dir/depend:
	cd /home/xie2481/Silly/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xie2481/Silly /home/xie2481/Silly /home/xie2481/Silly/cmake-build-debug /home/xie2481/Silly/cmake-build-debug /home/xie2481/Silly/cmake-build-debug/CMakeFiles/testassert.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testassert.dir/depend

