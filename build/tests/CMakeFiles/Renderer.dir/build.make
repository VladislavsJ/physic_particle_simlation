# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/Renderer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/Renderer.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/Renderer.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/Renderer.dir/flags.make

tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o: tests/CMakeFiles/Renderer.dir/flags.make
tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp
tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o: tests/CMakeFiles/Renderer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o"
	cd /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o -MF CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o.d -o CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp

tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Renderer.dir/__/src/Renderer.cpp.i"
	cd /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp > CMakeFiles/Renderer.dir/__/src/Renderer.cpp.i

tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Renderer.dir/__/src/Renderer.cpp.s"
	cd /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp -o CMakeFiles/Renderer.dir/__/src/Renderer.cpp.s

# Object files for target Renderer
Renderer_OBJECTS = \
"CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o"

# External object files for target Renderer
Renderer_EXTERNAL_OBJECTS =

tests/Renderer: tests/CMakeFiles/Renderer.dir/__/src/Renderer.cpp.o
tests/Renderer: tests/CMakeFiles/Renderer.dir/build.make
tests/Renderer: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.6.1
tests/Renderer: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.6.1
tests/Renderer: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.6.1
tests/Renderer: /usr/lib/gcc/x86_64-linux-gnu/13/libgomp.so
tests/Renderer: /usr/lib/x86_64-linux-gnu/libpthread.a
tests/Renderer: tests/CMakeFiles/Renderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Renderer"
	cd /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Renderer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/Renderer.dir/build: tests/Renderer
.PHONY : tests/CMakeFiles/Renderer.dir/build

tests/CMakeFiles/Renderer.dir/clean:
	cd /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/Renderer.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/Renderer.dir/clean

tests/CMakeFiles/Renderer.dir/depend:
	cd /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0 /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/tests /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/tests /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/tests/CMakeFiles/Renderer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/Renderer.dir/depend

