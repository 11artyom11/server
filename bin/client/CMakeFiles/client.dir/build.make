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
CMAKE_SOURCE_DIR = /home/aram/workspace/clientserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aram/workspace/clientserver

# Include any dependencies generated for this target.
include bin/client/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include bin/client/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include bin/client/CMakeFiles/client.dir/flags.make

bin/client/CMakeFiles/client.dir/src/client.cpp.o: bin/client/CMakeFiles/client.dir/flags.make
bin/client/CMakeFiles/client.dir/src/client.cpp.o: src/client/src/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aram/workspace/clientserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/client/CMakeFiles/client.dir/src/client.cpp.o"
	cd /home/aram/workspace/clientserver/bin/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/client.cpp.o -c /home/aram/workspace/clientserver/src/client/src/client.cpp

bin/client/CMakeFiles/client.dir/src/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/client.cpp.i"
	cd /home/aram/workspace/clientserver/bin/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aram/workspace/clientserver/src/client/src/client.cpp > CMakeFiles/client.dir/src/client.cpp.i

bin/client/CMakeFiles/client.dir/src/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/client.cpp.s"
	cd /home/aram/workspace/clientserver/bin/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aram/workspace/clientserver/src/client/src/client.cpp -o CMakeFiles/client.dir/src/client.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/client.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

bin/client/client: bin/client/CMakeFiles/client.dir/src/client.cpp.o
bin/client/client: bin/client/CMakeFiles/client.dir/build.make
bin/client/client: bin/client/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aram/workspace/clientserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable client"
	cd /home/aram/workspace/clientserver/bin/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/client/CMakeFiles/client.dir/build: bin/client/client

.PHONY : bin/client/CMakeFiles/client.dir/build

bin/client/CMakeFiles/client.dir/clean:
	cd /home/aram/workspace/clientserver/bin/client && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : bin/client/CMakeFiles/client.dir/clean

bin/client/CMakeFiles/client.dir/depend:
	cd /home/aram/workspace/clientserver && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aram/workspace/clientserver /home/aram/workspace/clientserver/src/client /home/aram/workspace/clientserver /home/aram/workspace/clientserver/bin/client /home/aram/workspace/clientserver/bin/client/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/client/CMakeFiles/client.dir/depend

