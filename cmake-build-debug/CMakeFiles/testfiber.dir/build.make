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
include CMakeFiles/testfiber.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testfiber.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testfiber.dir/flags.make

CMakeFiles/testfiber.dir/tests/test_fiber.cc.o: CMakeFiles/testfiber.dir/flags.make
CMakeFiles/testfiber.dir/tests/test_fiber.cc.o: ../tests/test_fiber.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xie2481/Silly/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testfiber.dir/tests/test_fiber.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testfiber.dir/tests/test_fiber.cc.o -c /home/xie2481/Silly/tests/test_fiber.cc

CMakeFiles/testfiber.dir/tests/test_fiber.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testfiber.dir/tests/test_fiber.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xie2481/Silly/tests/test_fiber.cc > CMakeFiles/testfiber.dir/tests/test_fiber.cc.i

CMakeFiles/testfiber.dir/tests/test_fiber.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testfiber.dir/tests/test_fiber.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xie2481/Silly/tests/test_fiber.cc -o CMakeFiles/testfiber.dir/tests/test_fiber.cc.s

CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.requires:

.PHONY : CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.requires

CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.provides: CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.requires
	$(MAKE) -f CMakeFiles/testfiber.dir/build.make CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.provides.build
.PHONY : CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.provides

CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.provides.build: CMakeFiles/testfiber.dir/tests/test_fiber.cc.o


# Object files for target testfiber
testfiber_OBJECTS = \
"CMakeFiles/testfiber.dir/tests/test_fiber.cc.o"

# External object files for target testfiber
testfiber_EXTERNAL_OBJECTS =

../bin/testfiber: CMakeFiles/testfiber.dir/tests/test_fiber.cc.o
../bin/testfiber: CMakeFiles/testfiber.dir/build.make
../bin/testfiber: ../lib/libSilly.so
../bin/testfiber: CMakeFiles/testfiber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xie2481/Silly/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/testfiber"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testfiber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testfiber.dir/build: ../bin/testfiber

.PHONY : CMakeFiles/testfiber.dir/build

CMakeFiles/testfiber.dir/requires: CMakeFiles/testfiber.dir/tests/test_fiber.cc.o.requires

.PHONY : CMakeFiles/testfiber.dir/requires

CMakeFiles/testfiber.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testfiber.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testfiber.dir/clean

CMakeFiles/testfiber.dir/depend:
	cd /home/xie2481/Silly/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xie2481/Silly /home/xie2481/Silly /home/xie2481/Silly/cmake-build-debug /home/xie2481/Silly/cmake-build-debug /home/xie2481/Silly/cmake-build-debug/CMakeFiles/testfiber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testfiber.dir/depend

