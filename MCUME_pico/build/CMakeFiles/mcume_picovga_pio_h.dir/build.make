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
CMAKE_SOURCE_DIR = /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/build

# Utility rule file for mcume_picovga_pio_h.

# Include the progress variables for this target.
include CMakeFiles/mcume_picovga_pio_h.dir/progress.make

CMakeFiles/mcume_picovga_pio_h: picovga.pio.h


picovga.pio.h: ../picovga_t4/picovga.pio
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating picovga.pio.h"
	pioasm/pioasm -o c-sdk /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/picovga_t4/picovga.pio /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/build/picovga.pio.h

mcume_picovga_pio_h: CMakeFiles/mcume_picovga_pio_h
mcume_picovga_pio_h: picovga.pio.h
mcume_picovga_pio_h: CMakeFiles/mcume_picovga_pio_h.dir/build.make

.PHONY : mcume_picovga_pio_h

# Rule to build all files generated by this target.
CMakeFiles/mcume_picovga_pio_h.dir/build: mcume_picovga_pio_h

.PHONY : CMakeFiles/mcume_picovga_pio_h.dir/build

CMakeFiles/mcume_picovga_pio_h.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mcume_picovga_pio_h.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mcume_picovga_pio_h.dir/clean

CMakeFiles/mcume_picovga_pio_h.dir/depend:
	cd /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/build /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/build /afs/inf.ed.ac.uk/user/s19/s1970742/Desktop/hons/MCUME/MCUME_pico/build/CMakeFiles/mcume_picovga_pio_h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mcume_picovga_pio_h.dir/depend

