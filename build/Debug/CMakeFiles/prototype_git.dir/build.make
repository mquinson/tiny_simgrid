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
CMAKE_SOURCE_DIR = /home/ehsan/projects/prototype_git

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ehsan/projects/prototype_git/build/Debug

# Include any dependencies generated for this target.
include CMakeFiles/prototype_git.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/prototype_git.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prototype_git.dir/flags.make

CMakeFiles/prototype_git.dir/src/test.cpp.o: CMakeFiles/prototype_git.dir/flags.make
CMakeFiles/prototype_git.dir/src/test.cpp.o: ../../src/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ehsan/projects/prototype_git/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prototype_git.dir/src/test.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prototype_git.dir/src/test.cpp.o -c /home/ehsan/projects/prototype_git/src/test.cpp

CMakeFiles/prototype_git.dir/src/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prototype_git.dir/src/test.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ehsan/projects/prototype_git/src/test.cpp > CMakeFiles/prototype_git.dir/src/test.cpp.i

CMakeFiles/prototype_git.dir/src/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prototype_git.dir/src/test.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ehsan/projects/prototype_git/src/test.cpp -o CMakeFiles/prototype_git.dir/src/test.cpp.s

CMakeFiles/prototype_git.dir/src/test.cpp.o.requires:

.PHONY : CMakeFiles/prototype_git.dir/src/test.cpp.o.requires

CMakeFiles/prototype_git.dir/src/test.cpp.o.provides: CMakeFiles/prototype_git.dir/src/test.cpp.o.requires
	$(MAKE) -f CMakeFiles/prototype_git.dir/build.make CMakeFiles/prototype_git.dir/src/test.cpp.o.provides.build
.PHONY : CMakeFiles/prototype_git.dir/src/test.cpp.o.provides

CMakeFiles/prototype_git.dir/src/test.cpp.o.provides.build: CMakeFiles/prototype_git.dir/src/test.cpp.o


CMakeFiles/prototype_git.dir/src/Simulation.cpp.o: CMakeFiles/prototype_git.dir/flags.make
CMakeFiles/prototype_git.dir/src/Simulation.cpp.o: ../../src/Simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ehsan/projects/prototype_git/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/prototype_git.dir/src/Simulation.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prototype_git.dir/src/Simulation.cpp.o -c /home/ehsan/projects/prototype_git/src/Simulation.cpp

CMakeFiles/prototype_git.dir/src/Simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prototype_git.dir/src/Simulation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ehsan/projects/prototype_git/src/Simulation.cpp > CMakeFiles/prototype_git.dir/src/Simulation.cpp.i

CMakeFiles/prototype_git.dir/src/Simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prototype_git.dir/src/Simulation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ehsan/projects/prototype_git/src/Simulation.cpp -o CMakeFiles/prototype_git.dir/src/Simulation.cpp.s

CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.requires:

.PHONY : CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.requires

CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.provides: CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.requires
	$(MAKE) -f CMakeFiles/prototype_git.dir/build.make CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.provides.build
.PHONY : CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.provides

CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.provides.build: CMakeFiles/prototype_git.dir/src/Simulation.cpp.o


CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o: CMakeFiles/prototype_git.dir/flags.make
CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o: ../../src/UnfoldingChecker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ehsan/projects/prototype_git/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o -c /home/ehsan/projects/prototype_git/src/UnfoldingChecker.cpp

CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ehsan/projects/prototype_git/src/UnfoldingChecker.cpp > CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.i

CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ehsan/projects/prototype_git/src/UnfoldingChecker.cpp -o CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.s

CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.requires:

.PHONY : CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.requires

CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.provides: CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.requires
	$(MAKE) -f CMakeFiles/prototype_git.dir/build.make CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.provides.build
.PHONY : CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.provides

CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.provides.build: CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o


CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o: CMakeFiles/prototype_git.dir/flags.make
CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o: ../../src/UnfoldingEvent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ehsan/projects/prototype_git/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o -c /home/ehsan/projects/prototype_git/src/UnfoldingEvent.cpp

CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ehsan/projects/prototype_git/src/UnfoldingEvent.cpp > CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.i

CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ehsan/projects/prototype_git/src/UnfoldingEvent.cpp -o CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.s

CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.requires:

.PHONY : CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.requires

CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.provides: CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.requires
	$(MAKE) -f CMakeFiles/prototype_git.dir/build.make CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.provides.build
.PHONY : CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.provides

CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.provides.build: CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o


# Object files for target prototype_git
prototype_git_OBJECTS = \
"CMakeFiles/prototype_git.dir/src/test.cpp.o" \
"CMakeFiles/prototype_git.dir/src/Simulation.cpp.o" \
"CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o" \
"CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o"

# External object files for target prototype_git
prototype_git_EXTERNAL_OBJECTS =

prototype_git: CMakeFiles/prototype_git.dir/src/test.cpp.o
prototype_git: CMakeFiles/prototype_git.dir/src/Simulation.cpp.o
prototype_git: CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o
prototype_git: CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o
prototype_git: CMakeFiles/prototype_git.dir/build.make
prototype_git: CMakeFiles/prototype_git.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ehsan/projects/prototype_git/build/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable prototype_git"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prototype_git.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prototype_git.dir/build: prototype_git

.PHONY : CMakeFiles/prototype_git.dir/build

CMakeFiles/prototype_git.dir/requires: CMakeFiles/prototype_git.dir/src/test.cpp.o.requires
CMakeFiles/prototype_git.dir/requires: CMakeFiles/prototype_git.dir/src/Simulation.cpp.o.requires
CMakeFiles/prototype_git.dir/requires: CMakeFiles/prototype_git.dir/src/UnfoldingChecker.cpp.o.requires
CMakeFiles/prototype_git.dir/requires: CMakeFiles/prototype_git.dir/src/UnfoldingEvent.cpp.o.requires

.PHONY : CMakeFiles/prototype_git.dir/requires

CMakeFiles/prototype_git.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prototype_git.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prototype_git.dir/clean

CMakeFiles/prototype_git.dir/depend:
	cd /home/ehsan/projects/prototype_git/build/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ehsan/projects/prototype_git /home/ehsan/projects/prototype_git /home/ehsan/projects/prototype_git/build/Debug /home/ehsan/projects/prototype_git/build/Debug /home/ehsan/projects/prototype_git/build/Debug/CMakeFiles/prototype_git.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prototype_git.dir/depend

