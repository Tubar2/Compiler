# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/ricardosantos/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/ricardosantos/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ricardosantos/Documents/UnB/Trab_SB_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simulador.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simulador.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simulador.dir/flags.make

CMakeFiles/simulador.dir/simulador.cpp.o: CMakeFiles/simulador.dir/flags.make
CMakeFiles/simulador.dir/simulador.cpp.o: ../simulador.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simulador.dir/simulador.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simulador.dir/simulador.cpp.o -c /Users/ricardosantos/Documents/UnB/Trab_SB_1/simulador.cpp

CMakeFiles/simulador.dir/simulador.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simulador.dir/simulador.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ricardosantos/Documents/UnB/Trab_SB_1/simulador.cpp > CMakeFiles/simulador.dir/simulador.cpp.i

CMakeFiles/simulador.dir/simulador.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simulador.dir/simulador.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ricardosantos/Documents/UnB/Trab_SB_1/simulador.cpp -o CMakeFiles/simulador.dir/simulador.cpp.s

CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.o: CMakeFiles/simulador.dir/flags.make
CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.o: ../aux/montador/montador_aux.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.o -c /Users/ricardosantos/Documents/UnB/Trab_SB_1/aux/montador/montador_aux.cpp

CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ricardosantos/Documents/UnB/Trab_SB_1/aux/montador/montador_aux.cpp > CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.i

CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ricardosantos/Documents/UnB/Trab_SB_1/aux/montador/montador_aux.cpp -o CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.s

CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.o: CMakeFiles/simulador.dir/flags.make
CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.o: ../aux/simulador/simulador_aux.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.o -c /Users/ricardosantos/Documents/UnB/Trab_SB_1/aux/simulador/simulador_aux.cpp

CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ricardosantos/Documents/UnB/Trab_SB_1/aux/simulador/simulador_aux.cpp > CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.i

CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ricardosantos/Documents/UnB/Trab_SB_1/aux/simulador/simulador_aux.cpp -o CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.s

# Object files for target simulador
simulador_OBJECTS = \
"CMakeFiles/simulador.dir/simulador.cpp.o" \
"CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.o" \
"CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.o"

# External object files for target simulador
simulador_EXTERNAL_OBJECTS =

simulador: CMakeFiles/simulador.dir/simulador.cpp.o
simulador: CMakeFiles/simulador.dir/aux/montador/montador_aux.cpp.o
simulador: CMakeFiles/simulador.dir/aux/simulador/simulador_aux.cpp.o
simulador: CMakeFiles/simulador.dir/build.make
simulador: CMakeFiles/simulador.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable simulador"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simulador.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simulador.dir/build: simulador

.PHONY : CMakeFiles/simulador.dir/build

CMakeFiles/simulador.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simulador.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simulador.dir/clean

CMakeFiles/simulador.dir/depend:
	cd /Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ricardosantos/Documents/UnB/Trab_SB_1 /Users/ricardosantos/Documents/UnB/Trab_SB_1 /Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug /Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug /Users/ricardosantos/Documents/UnB/Trab_SB_1/cmake-build-debug/CMakeFiles/simulador.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simulador.dir/depend
