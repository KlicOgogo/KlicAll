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
CMAKE_SOURCE_DIR = "/home/andrejka/CLionProjects/Course project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/andrejka/CLionProjects/Course project/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Course_project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Course_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Course_project.dir/flags.make

CMakeFiles/Course_project.dir/main.cpp.o: CMakeFiles/Course_project.dir/flags.make
CMakeFiles/Course_project.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/andrejka/CLionProjects/Course project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Course_project.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_project.dir/main.cpp.o -c "/home/andrejka/CLionProjects/Course project/main.cpp"

CMakeFiles/Course_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_project.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/andrejka/CLionProjects/Course project/main.cpp" > CMakeFiles/Course_project.dir/main.cpp.i

CMakeFiles/Course_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_project.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/andrejka/CLionProjects/Course project/main.cpp" -o CMakeFiles/Course_project.dir/main.cpp.s

CMakeFiles/Course_project.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Course_project.dir/main.cpp.o.requires

CMakeFiles/Course_project.dir/main.cpp.o.provides: CMakeFiles/Course_project.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Course_project.dir/build.make CMakeFiles/Course_project.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Course_project.dir/main.cpp.o.provides

CMakeFiles/Course_project.dir/main.cpp.o.provides.build: CMakeFiles/Course_project.dir/main.cpp.o


CMakeFiles/Course_project.dir/random_graph.cpp.o: CMakeFiles/Course_project.dir/flags.make
CMakeFiles/Course_project.dir/random_graph.cpp.o: ../random_graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/andrejka/CLionProjects/Course project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Course_project.dir/random_graph.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Course_project.dir/random_graph.cpp.o -c "/home/andrejka/CLionProjects/Course project/random_graph.cpp"

CMakeFiles/Course_project.dir/random_graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Course_project.dir/random_graph.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/andrejka/CLionProjects/Course project/random_graph.cpp" > CMakeFiles/Course_project.dir/random_graph.cpp.i

CMakeFiles/Course_project.dir/random_graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Course_project.dir/random_graph.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/andrejka/CLionProjects/Course project/random_graph.cpp" -o CMakeFiles/Course_project.dir/random_graph.cpp.s

CMakeFiles/Course_project.dir/random_graph.cpp.o.requires:

.PHONY : CMakeFiles/Course_project.dir/random_graph.cpp.o.requires

CMakeFiles/Course_project.dir/random_graph.cpp.o.provides: CMakeFiles/Course_project.dir/random_graph.cpp.o.requires
	$(MAKE) -f CMakeFiles/Course_project.dir/build.make CMakeFiles/Course_project.dir/random_graph.cpp.o.provides.build
.PHONY : CMakeFiles/Course_project.dir/random_graph.cpp.o.provides

CMakeFiles/Course_project.dir/random_graph.cpp.o.provides.build: CMakeFiles/Course_project.dir/random_graph.cpp.o


# Object files for target Course_project
Course_project_OBJECTS = \
"CMakeFiles/Course_project.dir/main.cpp.o" \
"CMakeFiles/Course_project.dir/random_graph.cpp.o"

# External object files for target Course_project
Course_project_EXTERNAL_OBJECTS =

Course_project: CMakeFiles/Course_project.dir/main.cpp.o
Course_project: CMakeFiles/Course_project.dir/random_graph.cpp.o
Course_project: CMakeFiles/Course_project.dir/build.make
Course_project: CMakeFiles/Course_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/andrejka/CLionProjects/Course project/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Course_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Course_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Course_project.dir/build: Course_project

.PHONY : CMakeFiles/Course_project.dir/build

CMakeFiles/Course_project.dir/requires: CMakeFiles/Course_project.dir/main.cpp.o.requires
CMakeFiles/Course_project.dir/requires: CMakeFiles/Course_project.dir/random_graph.cpp.o.requires

.PHONY : CMakeFiles/Course_project.dir/requires

CMakeFiles/Course_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Course_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Course_project.dir/clean

CMakeFiles/Course_project.dir/depend:
	cd "/home/andrejka/CLionProjects/Course project/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/andrejka/CLionProjects/Course project" "/home/andrejka/CLionProjects/Course project" "/home/andrejka/CLionProjects/Course project/cmake-build-debug" "/home/andrejka/CLionProjects/Course project/cmake-build-debug" "/home/andrejka/CLionProjects/Course project/cmake-build-debug/CMakeFiles/Course_project.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Course_project.dir/depend

