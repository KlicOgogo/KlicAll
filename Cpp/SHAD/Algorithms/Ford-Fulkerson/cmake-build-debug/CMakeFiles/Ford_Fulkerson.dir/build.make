# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /opt/clion-2016.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2016.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andrejka/CLionProjects/Ford-Fulkerson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrejka/CLionProjects/Ford-Fulkerson/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Ford_Fulkerson.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ford_Fulkerson.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ford_Fulkerson.dir/flags.make

CMakeFiles/Ford_Fulkerson.dir/main.cpp.o: CMakeFiles/Ford_Fulkerson.dir/flags.make
CMakeFiles/Ford_Fulkerson.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrejka/CLionProjects/Ford-Fulkerson/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ford_Fulkerson.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ford_Fulkerson.dir/main.cpp.o -c /home/andrejka/CLionProjects/Ford-Fulkerson/main.cpp

CMakeFiles/Ford_Fulkerson.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ford_Fulkerson.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrejka/CLionProjects/Ford-Fulkerson/main.cpp > CMakeFiles/Ford_Fulkerson.dir/main.cpp.i

CMakeFiles/Ford_Fulkerson.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ford_Fulkerson.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrejka/CLionProjects/Ford-Fulkerson/main.cpp -o CMakeFiles/Ford_Fulkerson.dir/main.cpp.s

CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.requires

CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.provides: CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Ford_Fulkerson.dir/build.make CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.provides

CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.provides.build: CMakeFiles/Ford_Fulkerson.dir/main.cpp.o


# Object files for target Ford_Fulkerson
Ford_Fulkerson_OBJECTS = \
"CMakeFiles/Ford_Fulkerson.dir/main.cpp.o"

# External object files for target Ford_Fulkerson
Ford_Fulkerson_EXTERNAL_OBJECTS =

Ford_Fulkerson: CMakeFiles/Ford_Fulkerson.dir/main.cpp.o
Ford_Fulkerson: CMakeFiles/Ford_Fulkerson.dir/build.make
Ford_Fulkerson: CMakeFiles/Ford_Fulkerson.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrejka/CLionProjects/Ford-Fulkerson/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Ford_Fulkerson"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ford_Fulkerson.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ford_Fulkerson.dir/build: Ford_Fulkerson

.PHONY : CMakeFiles/Ford_Fulkerson.dir/build

CMakeFiles/Ford_Fulkerson.dir/requires: CMakeFiles/Ford_Fulkerson.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Ford_Fulkerson.dir/requires

CMakeFiles/Ford_Fulkerson.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ford_Fulkerson.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ford_Fulkerson.dir/clean

CMakeFiles/Ford_Fulkerson.dir/depend:
	cd /home/andrejka/CLionProjects/Ford-Fulkerson/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrejka/CLionProjects/Ford-Fulkerson /home/andrejka/CLionProjects/Ford-Fulkerson /home/andrejka/CLionProjects/Ford-Fulkerson/cmake-build-debug /home/andrejka/CLionProjects/Ford-Fulkerson/cmake-build-debug /home/andrejka/CLionProjects/Ford-Fulkerson/cmake-build-debug/CMakeFiles/Ford_Fulkerson.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ford_Fulkerson.dir/depend
