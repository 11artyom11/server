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
include bin/server/CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include bin/server/CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include bin/server/CMakeFiles/server.dir/flags.make

bin/server/CMakeFiles/server.dir/src/main.cpp.o: bin/server/CMakeFiles/server.dir/flags.make
bin/server/CMakeFiles/server.dir/src/main.cpp.o: src/server/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aram/workspace/clientserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/server/CMakeFiles/server.dir/src/main.cpp.o"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/main.cpp.o -c /home/aram/workspace/clientserver/src/server/src/main.cpp

bin/server/CMakeFiles/server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/main.cpp.i"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aram/workspace/clientserver/src/server/src/main.cpp > CMakeFiles/server.dir/src/main.cpp.i

bin/server/CMakeFiles/server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/main.cpp.s"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aram/workspace/clientserver/src/server/src/main.cpp -o CMakeFiles/server.dir/src/main.cpp.s

bin/server/CMakeFiles/server.dir/src/server.cpp.o: bin/server/CMakeFiles/server.dir/flags.make
bin/server/CMakeFiles/server.dir/src/server.cpp.o: src/server/src/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aram/workspace/clientserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object bin/server/CMakeFiles/server.dir/src/server.cpp.o"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/server.cpp.o -c /home/aram/workspace/clientserver/src/server/src/server.cpp

bin/server/CMakeFiles/server.dir/src/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/server.cpp.i"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aram/workspace/clientserver/src/server/src/server.cpp > CMakeFiles/server.dir/src/server.cpp.i

bin/server/CMakeFiles/server.dir/src/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/server.cpp.s"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aram/workspace/clientserver/src/server/src/server.cpp -o CMakeFiles/server.dir/src/server.cpp.s

bin/server/CMakeFiles/server.dir/src/handler.cpp.o: bin/server/CMakeFiles/server.dir/flags.make
bin/server/CMakeFiles/server.dir/src/handler.cpp.o: src/server/src/handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aram/workspace/clientserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object bin/server/CMakeFiles/server.dir/src/handler.cpp.o"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/handler.cpp.o -c /home/aram/workspace/clientserver/src/server/src/handler.cpp

bin/server/CMakeFiles/server.dir/src/handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/handler.cpp.i"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aram/workspace/clientserver/src/server/src/handler.cpp > CMakeFiles/server.dir/src/handler.cpp.i

bin/server/CMakeFiles/server.dir/src/handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/handler.cpp.s"
	cd /home/aram/workspace/clientserver/bin/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aram/workspace/clientserver/src/server/src/handler.cpp -o CMakeFiles/server.dir/src/handler.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/src/main.cpp.o" \
"CMakeFiles/server.dir/src/server.cpp.o" \
"CMakeFiles/server.dir/src/handler.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

bin/server/server: bin/server/CMakeFiles/server.dir/src/main.cpp.o
bin/server/server: bin/server/CMakeFiles/server.dir/src/server.cpp.o
bin/server/server: bin/server/CMakeFiles/server.dir/src/handler.cpp.o
bin/server/server: bin/server/CMakeFiles/server.dir/build.make
bin/server/server: lib/src/helpers/liblibdebug_helper.so.1.0.1
bin/server/server: bin/server/CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aram/workspace/clientserver/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable server"
	cd /home/aram/workspace/clientserver/bin/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/server/CMakeFiles/server.dir/build: bin/server/server

.PHONY : bin/server/CMakeFiles/server.dir/build

bin/server/CMakeFiles/server.dir/clean:
	cd /home/aram/workspace/clientserver/bin/server && $(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : bin/server/CMakeFiles/server.dir/clean

bin/server/CMakeFiles/server.dir/depend:
	cd /home/aram/workspace/clientserver && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aram/workspace/clientserver /home/aram/workspace/clientserver/src/server /home/aram/workspace/clientserver /home/aram/workspace/clientserver/bin/server /home/aram/workspace/clientserver/bin/server/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/server/CMakeFiles/server.dir/depend

