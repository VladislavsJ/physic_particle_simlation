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
include CMakeFiles/ParticleSimulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ParticleSimulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ParticleSimulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ParticleSimulator.dir/flags.make

CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/BorderInfo.cpp
CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/BorderInfo.cpp

CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/BorderInfo.cpp > CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.i

CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/BorderInfo.cpp -o CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.s

CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Graphs_new.cpp
CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Graphs_new.cpp

CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Graphs_new.cpp > CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.i

CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Graphs_new.cpp -o CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.s

CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Particle.cpp
CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Particle.cpp

CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Particle.cpp > CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.i

CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Particle.cpp -o CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.s

CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/ParticleSystem.cpp
CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/ParticleSystem.cpp

CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/ParticleSystem.cpp > CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.i

CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/ParticleSystem.cpp -o CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.s

CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Physics.cpp
CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Physics.cpp

CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Physics.cpp > CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.i

CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Physics.cpp -o CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.s

CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp
CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp

CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp > CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.i

CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/Renderer.cpp -o CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.s

CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/graphical_items.cpp
CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/graphical_items.cpp

CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/graphical_items.cpp > CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.i

CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/graphical_items.cpp -o CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.s

CMakeFiles/ParticleSimulator.dir/src/main.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/main.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/main.cpp
CMakeFiles/ParticleSimulator.dir/src/main.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/main.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/main.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/main.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/main.cpp

CMakeFiles/ParticleSimulator.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/main.cpp > CMakeFiles/ParticleSimulator.dir/src/main.cpp.i

CMakeFiles/ParticleSimulator.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/main.cpp -o CMakeFiles/ParticleSimulator.dir/src/main.cpp.s

CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/simulation_examples.cpp
CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/simulation_examples.cpp

CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/simulation_examples.cpp > CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.i

CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/simulation_examples.cpp -o CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.s

CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o: CMakeFiles/ParticleSimulator.dir/flags.make
CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o: /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/user_interactions_new.cpp
CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o: CMakeFiles/ParticleSimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o -MF CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o.d -o CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o -c /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/user_interactions_new.cpp

CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/user_interactions_new.cpp > CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.i

CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/src/user_interactions_new.cpp -o CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.s

# Object files for target ParticleSimulator
ParticleSimulator_OBJECTS = \
"CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/main.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o" \
"CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o"

# External object files for target ParticleSimulator
ParticleSimulator_EXTERNAL_OBJECTS =

ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/BorderInfo.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/Graphs_new.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/Particle.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/ParticleSystem.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/Physics.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/Renderer.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/graphical_items.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/main.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/simulation_examples.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/src/user_interactions_new.cpp.o
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/build.make
ParticleSimulator: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.6.1
ParticleSimulator: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.6.1
ParticleSimulator: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.6.1
ParticleSimulator: CMakeFiles/ParticleSimulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable ParticleSimulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ParticleSimulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ParticleSimulator.dir/build: ParticleSimulator
.PHONY : CMakeFiles/ParticleSimulator.dir/build

CMakeFiles/ParticleSimulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ParticleSimulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ParticleSimulator.dir/clean

CMakeFiles/ParticleSimulator.dir/depend:
	cd /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0 /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0 /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build /media/vlad/Shared_w_L/NTNU/new_cXX_folder/physic_balls_V0/build/CMakeFiles/ParticleSimulator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ParticleSimulator.dir/depend

