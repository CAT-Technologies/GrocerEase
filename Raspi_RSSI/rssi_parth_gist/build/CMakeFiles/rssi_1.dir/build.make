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
CMAKE_SOURCE_DIR = /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/build

# Include any dependencies generated for this target.
include CMakeFiles/rssi_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rssi_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rssi_1.dir/flags.make

CMakeFiles/rssi_1.dir/src/rssi_1.c.o: CMakeFiles/rssi_1.dir/flags.make
CMakeFiles/rssi_1.dir/src/rssi_1.c.o: ../src/rssi_1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/rssi_1.dir/src/rssi_1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rssi_1.dir/src/rssi_1.c.o   -c /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/src/rssi_1.c

CMakeFiles/rssi_1.dir/src/rssi_1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rssi_1.dir/src/rssi_1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/src/rssi_1.c > CMakeFiles/rssi_1.dir/src/rssi_1.c.i

CMakeFiles/rssi_1.dir/src/rssi_1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rssi_1.dir/src/rssi_1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/src/rssi_1.c -o CMakeFiles/rssi_1.dir/src/rssi_1.c.s

# Object files for target rssi_1
rssi_1_OBJECTS = \
"CMakeFiles/rssi_1.dir/src/rssi_1.c.o"

# External object files for target rssi_1
rssi_1_EXTERNAL_OBJECTS =

rssi_1: CMakeFiles/rssi_1.dir/src/rssi_1.c.o
rssi_1: CMakeFiles/rssi_1.dir/build.make
rssi_1: CMakeFiles/rssi_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable rssi_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rssi_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rssi_1.dir/build: rssi_1

.PHONY : CMakeFiles/rssi_1.dir/build

CMakeFiles/rssi_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rssi_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rssi_1.dir/clean

CMakeFiles/rssi_1.dir/depend:
	cd /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/build /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/build /home/anmol/Github/GrocerEase/Raspi_RSSI/rssi_parth_gist/build/CMakeFiles/rssi_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rssi_1.dir/depend

