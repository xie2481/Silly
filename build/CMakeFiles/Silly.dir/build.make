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
CMAKE_BINARY_DIR = /home/xie2481/Silly/build

# Include any dependencies generated for this target.
include CMakeFiles/Silly.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Silly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Silly.dir/flags.make

CMakeFiles/Silly.dir/Silly/log.cc.o: CMakeFiles/Silly.dir/flags.make
CMakeFiles/Silly.dir/Silly/log.cc.o: ../Silly/log.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xie2481/Silly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Silly.dir/Silly/log.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Silly.dir/Silly/log.cc.o -c /home/xie2481/Silly/Silly/log.cc

CMakeFiles/Silly.dir/Silly/log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Silly.dir/Silly/log.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xie2481/Silly/Silly/log.cc > CMakeFiles/Silly.dir/Silly/log.cc.i

CMakeFiles/Silly.dir/Silly/log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Silly.dir/Silly/log.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xie2481/Silly/Silly/log.cc -o CMakeFiles/Silly.dir/Silly/log.cc.s

CMakeFiles/Silly.dir/Silly/log.cc.o.requires:

.PHONY : CMakeFiles/Silly.dir/Silly/log.cc.o.requires

CMakeFiles/Silly.dir/Silly/log.cc.o.provides: CMakeFiles/Silly.dir/Silly/log.cc.o.requires
	$(MAKE) -f CMakeFiles/Silly.dir/build.make CMakeFiles/Silly.dir/Silly/log.cc.o.provides.build
.PHONY : CMakeFiles/Silly.dir/Silly/log.cc.o.provides

CMakeFiles/Silly.dir/Silly/log.cc.o.provides.build: CMakeFiles/Silly.dir/Silly/log.cc.o


CMakeFiles/Silly.dir/Silly/util.cc.o: CMakeFiles/Silly.dir/flags.make
CMakeFiles/Silly.dir/Silly/util.cc.o: ../Silly/util.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xie2481/Silly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Silly.dir/Silly/util.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Silly.dir/Silly/util.cc.o -c /home/xie2481/Silly/Silly/util.cc

CMakeFiles/Silly.dir/Silly/util.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Silly.dir/Silly/util.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xie2481/Silly/Silly/util.cc > CMakeFiles/Silly.dir/Silly/util.cc.i

CMakeFiles/Silly.dir/Silly/util.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Silly.dir/Silly/util.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xie2481/Silly/Silly/util.cc -o CMakeFiles/Silly.dir/Silly/util.cc.s

CMakeFiles/Silly.dir/Silly/util.cc.o.requires:

.PHONY : CMakeFiles/Silly.dir/Silly/util.cc.o.requires

CMakeFiles/Silly.dir/Silly/util.cc.o.provides: CMakeFiles/Silly.dir/Silly/util.cc.o.requires
	$(MAKE) -f CMakeFiles/Silly.dir/build.make CMakeFiles/Silly.dir/Silly/util.cc.o.provides.build
.PHONY : CMakeFiles/Silly.dir/Silly/util.cc.o.provides

CMakeFiles/Silly.dir/Silly/util.cc.o.provides.build: CMakeFiles/Silly.dir/Silly/util.cc.o


CMakeFiles/Silly.dir/Silly/config.cc.o: CMakeFiles/Silly.dir/flags.make
CMakeFiles/Silly.dir/Silly/config.cc.o: ../Silly/config.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xie2481/Silly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Silly.dir/Silly/config.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Silly.dir/Silly/config.cc.o -c /home/xie2481/Silly/Silly/config.cc

CMakeFiles/Silly.dir/Silly/config.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Silly.dir/Silly/config.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xie2481/Silly/Silly/config.cc > CMakeFiles/Silly.dir/Silly/config.cc.i

CMakeFiles/Silly.dir/Silly/config.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Silly.dir/Silly/config.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xie2481/Silly/Silly/config.cc -o CMakeFiles/Silly.dir/Silly/config.cc.s

CMakeFiles/Silly.dir/Silly/config.cc.o.requires:

.PHONY : CMakeFiles/Silly.dir/Silly/config.cc.o.requires

CMakeFiles/Silly.dir/Silly/config.cc.o.provides: CMakeFiles/Silly.dir/Silly/config.cc.o.requires
	$(MAKE) -f CMakeFiles/Silly.dir/build.make CMakeFiles/Silly.dir/Silly/config.cc.o.provides.build
.PHONY : CMakeFiles/Silly.dir/Silly/config.cc.o.provides

CMakeFiles/Silly.dir/Silly/config.cc.o.provides.build: CMakeFiles/Silly.dir/Silly/config.cc.o


# Object files for target Silly
Silly_OBJECTS = \
"CMakeFiles/Silly.dir/Silly/log.cc.o" \
"CMakeFiles/Silly.dir/Silly/util.cc.o" \
"CMakeFiles/Silly.dir/Silly/config.cc.o"

# External object files for target Silly
Silly_EXTERNAL_OBJECTS =

../lib/libSilly.so: CMakeFiles/Silly.dir/Silly/log.cc.o
../lib/libSilly.so: CMakeFiles/Silly.dir/Silly/util.cc.o
../lib/libSilly.so: CMakeFiles/Silly.dir/Silly/config.cc.o
../lib/libSilly.so: CMakeFiles/Silly.dir/build.make
../lib/libSilly.so: CMakeFiles/Silly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xie2481/Silly/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library ../lib/libSilly.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Silly.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Silly.dir/build: ../lib/libSilly.so

.PHONY : CMakeFiles/Silly.dir/build

CMakeFiles/Silly.dir/requires: CMakeFiles/Silly.dir/Silly/log.cc.o.requires
CMakeFiles/Silly.dir/requires: CMakeFiles/Silly.dir/Silly/util.cc.o.requires
CMakeFiles/Silly.dir/requires: CMakeFiles/Silly.dir/Silly/config.cc.o.requires

.PHONY : CMakeFiles/Silly.dir/requires

CMakeFiles/Silly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Silly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Silly.dir/clean

CMakeFiles/Silly.dir/depend:
	cd /home/xie2481/Silly/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xie2481/Silly /home/xie2481/Silly /home/xie2481/Silly/build /home/xie2481/Silly/build /home/xie2481/Silly/build/CMakeFiles/Silly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Silly.dir/depend

