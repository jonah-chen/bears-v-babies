# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/hina/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/hina/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/211.7442.42/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hina/Code/bears-v-babies

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hina/Code/bears-v-babies/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bears_v_babies.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bears_v_babies.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bears_v_babies.dir/flags.make

CMakeFiles/bears_v_babies.dir/main.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bears_v_babies.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/main.cpp.o -c /home/hina/Code/bears-v-babies/main.cpp

CMakeFiles/bears_v_babies.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/main.cpp > CMakeFiles/bears_v_babies.dir/main.cpp.i

CMakeFiles/bears_v_babies.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/main.cpp -o CMakeFiles/bears_v_babies.dir/main.cpp.s

CMakeFiles/bears_v_babies.dir/game.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/game.cpp.o: ../game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bears_v_babies.dir/game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/game.cpp.o -c /home/hina/Code/bears-v-babies/game.cpp

CMakeFiles/bears_v_babies.dir/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/game.cpp > CMakeFiles/bears_v_babies.dir/game.cpp.i

CMakeFiles/bears_v_babies.dir/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/game.cpp -o CMakeFiles/bears_v_babies.dir/game.cpp.s

CMakeFiles/bears_v_babies.dir/monster.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/monster.cpp.o: ../monster.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bears_v_babies.dir/monster.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/monster.cpp.o -c /home/hina/Code/bears-v-babies/monster.cpp

CMakeFiles/bears_v_babies.dir/monster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/monster.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/monster.cpp > CMakeFiles/bears_v_babies.dir/monster.cpp.i

CMakeFiles/bears_v_babies.dir/monster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/monster.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/monster.cpp -o CMakeFiles/bears_v_babies.dir/monster.cpp.s

CMakeFiles/bears_v_babies.dir/cards.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/cards.cpp.o: ../cards.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/bears_v_babies.dir/cards.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/cards.cpp.o -c /home/hina/Code/bears-v-babies/cards.cpp

CMakeFiles/bears_v_babies.dir/cards.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/cards.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/cards.cpp > CMakeFiles/bears_v_babies.dir/cards.cpp.i

CMakeFiles/bears_v_babies.dir/cards.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/cards.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/cards.cpp -o CMakeFiles/bears_v_babies.dir/cards.cpp.s

CMakeFiles/bears_v_babies.dir/provoke.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/provoke.cpp.o: ../provoke.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/bears_v_babies.dir/provoke.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/provoke.cpp.o -c /home/hina/Code/bears-v-babies/provoke.cpp

CMakeFiles/bears_v_babies.dir/provoke.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/provoke.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/provoke.cpp > CMakeFiles/bears_v_babies.dir/provoke.cpp.i

CMakeFiles/bears_v_babies.dir/provoke.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/provoke.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/provoke.cpp -o CMakeFiles/bears_v_babies.dir/provoke.cpp.s

CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.o: ../dumpster-dive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.o -c /home/hina/Code/bears-v-babies/dumpster-dive.cpp

CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/dumpster-dive.cpp > CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.i

CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/dumpster-dive.cpp -o CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.s

CMakeFiles/bears_v_babies.dir/io.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/io.cpp.o: ../io.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/bears_v_babies.dir/io.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/io.cpp.o -c /home/hina/Code/bears-v-babies/io.cpp

CMakeFiles/bears_v_babies.dir/io.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/io.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/io.cpp > CMakeFiles/bears_v_babies.dir/io.cpp.i

CMakeFiles/bears_v_babies.dir/io.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/io.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/io.cpp -o CMakeFiles/bears_v_babies.dir/io.cpp.s

CMakeFiles/bears_v_babies.dir/play-head.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/play-head.cpp.o: ../play-head.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/bears_v_babies.dir/play-head.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/play-head.cpp.o -c /home/hina/Code/bears-v-babies/play-head.cpp

CMakeFiles/bears_v_babies.dir/play-head.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/play-head.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/play-head.cpp > CMakeFiles/bears_v_babies.dir/play-head.cpp.i

CMakeFiles/bears_v_babies.dir/play-head.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/play-head.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/play-head.cpp -o CMakeFiles/bears_v_babies.dir/play-head.cpp.s

CMakeFiles/bears_v_babies.dir/play-part.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/play-part.cpp.o: ../play-part.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/bears_v_babies.dir/play-part.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/play-part.cpp.o -c /home/hina/Code/bears-v-babies/play-part.cpp

CMakeFiles/bears_v_babies.dir/play-part.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/play-part.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/play-part.cpp > CMakeFiles/bears_v_babies.dir/play-part.cpp.i

CMakeFiles/bears_v_babies.dir/play-part.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/play-part.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/play-part.cpp -o CMakeFiles/bears_v_babies.dir/play-part.cpp.s

CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.o: ../play-lulluby.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.o -c /home/hina/Code/bears-v-babies/play-lulluby.cpp

CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/play-lulluby.cpp > CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.i

CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/play-lulluby.cpp -o CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.s

CMakeFiles/bears_v_babies.dir/play-dismember.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/play-dismember.cpp.o: ../play-dismember.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/bears_v_babies.dir/play-dismember.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/play-dismember.cpp.o -c /home/hina/Code/bears-v-babies/play-dismember.cpp

CMakeFiles/bears_v_babies.dir/play-dismember.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/play-dismember.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/play-dismember.cpp > CMakeFiles/bears_v_babies.dir/play-dismember.cpp.i

CMakeFiles/bears_v_babies.dir/play-dismember.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/play-dismember.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/play-dismember.cpp -o CMakeFiles/bears_v_babies.dir/play-dismember.cpp.s

CMakeFiles/bears_v_babies.dir/play-swap.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/play-swap.cpp.o: ../play-swap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/bears_v_babies.dir/play-swap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/play-swap.cpp.o -c /home/hina/Code/bears-v-babies/play-swap.cpp

CMakeFiles/bears_v_babies.dir/play-swap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/play-swap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/play-swap.cpp > CMakeFiles/bears_v_babies.dir/play-swap.cpp.i

CMakeFiles/bears_v_babies.dir/play-swap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/play-swap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/play-swap.cpp -o CMakeFiles/bears_v_babies.dir/play-swap.cpp.s

CMakeFiles/bears_v_babies.dir/comm.cpp.o: CMakeFiles/bears_v_babies.dir/flags.make
CMakeFiles/bears_v_babies.dir/comm.cpp.o: ../comm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/bears_v_babies.dir/comm.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bears_v_babies.dir/comm.cpp.o -c /home/hina/Code/bears-v-babies/comm.cpp

CMakeFiles/bears_v_babies.dir/comm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bears_v_babies.dir/comm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hina/Code/bears-v-babies/comm.cpp > CMakeFiles/bears_v_babies.dir/comm.cpp.i

CMakeFiles/bears_v_babies.dir/comm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bears_v_babies.dir/comm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hina/Code/bears-v-babies/comm.cpp -o CMakeFiles/bears_v_babies.dir/comm.cpp.s

# Object files for target bears_v_babies
bears_v_babies_OBJECTS = \
"CMakeFiles/bears_v_babies.dir/main.cpp.o" \
"CMakeFiles/bears_v_babies.dir/game.cpp.o" \
"CMakeFiles/bears_v_babies.dir/monster.cpp.o" \
"CMakeFiles/bears_v_babies.dir/cards.cpp.o" \
"CMakeFiles/bears_v_babies.dir/provoke.cpp.o" \
"CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.o" \
"CMakeFiles/bears_v_babies.dir/io.cpp.o" \
"CMakeFiles/bears_v_babies.dir/play-head.cpp.o" \
"CMakeFiles/bears_v_babies.dir/play-part.cpp.o" \
"CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.o" \
"CMakeFiles/bears_v_babies.dir/play-dismember.cpp.o" \
"CMakeFiles/bears_v_babies.dir/play-swap.cpp.o" \
"CMakeFiles/bears_v_babies.dir/comm.cpp.o"

# External object files for target bears_v_babies
bears_v_babies_EXTERNAL_OBJECTS =

bears_v_babies: CMakeFiles/bears_v_babies.dir/main.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/game.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/monster.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/cards.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/provoke.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/dumpster-dive.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/io.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/play-head.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/play-part.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/play-lulluby.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/play-dismember.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/play-swap.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/comm.cpp.o
bears_v_babies: CMakeFiles/bears_v_babies.dir/build.make
bears_v_babies: CMakeFiles/bears_v_babies.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable bears_v_babies"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bears_v_babies.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bears_v_babies.dir/build: bears_v_babies

.PHONY : CMakeFiles/bears_v_babies.dir/build

CMakeFiles/bears_v_babies.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bears_v_babies.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bears_v_babies.dir/clean

CMakeFiles/bears_v_babies.dir/depend:
	cd /home/hina/Code/bears-v-babies/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hina/Code/bears-v-babies /home/hina/Code/bears-v-babies /home/hina/Code/bears-v-babies/cmake-build-debug /home/hina/Code/bears-v-babies/cmake-build-debug /home/hina/Code/bears-v-babies/cmake-build-debug/CMakeFiles/bears_v_babies.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bears_v_babies.dir/depend
