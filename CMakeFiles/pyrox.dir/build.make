# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/zinic/projects/Pyrox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zinic/projects/Pyrox

# Include any dependencies generated for this target.
include CMakeFiles/pyrox.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pyrox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pyrox.dir/flags.make

CMakeFiles/pyrox.dir/ev_test.c.o: CMakeFiles/pyrox.dir/flags.make
CMakeFiles/pyrox.dir/ev_test.c.o: ev_test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zinic/projects/Pyrox/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/pyrox.dir/ev_test.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/pyrox.dir/ev_test.c.o   -c /home/zinic/projects/Pyrox/ev_test.c

CMakeFiles/pyrox.dir/ev_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pyrox.dir/ev_test.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/zinic/projects/Pyrox/ev_test.c > CMakeFiles/pyrox.dir/ev_test.c.i

CMakeFiles/pyrox.dir/ev_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pyrox.dir/ev_test.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/zinic/projects/Pyrox/ev_test.c -o CMakeFiles/pyrox.dir/ev_test.c.s

CMakeFiles/pyrox.dir/ev_test.c.o.requires:
.PHONY : CMakeFiles/pyrox.dir/ev_test.c.o.requires

CMakeFiles/pyrox.dir/ev_test.c.o.provides: CMakeFiles/pyrox.dir/ev_test.c.o.requires
	$(MAKE) -f CMakeFiles/pyrox.dir/build.make CMakeFiles/pyrox.dir/ev_test.c.o.provides.build
.PHONY : CMakeFiles/pyrox.dir/ev_test.c.o.provides

CMakeFiles/pyrox.dir/ev_test.c.o.provides.build: CMakeFiles/pyrox.dir/ev_test.c.o

CMakeFiles/pyrox.dir/main.c.o: CMakeFiles/pyrox.dir/flags.make
CMakeFiles/pyrox.dir/main.c.o: main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zinic/projects/Pyrox/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/pyrox.dir/main.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/pyrox.dir/main.c.o   -c /home/zinic/projects/Pyrox/main.c

CMakeFiles/pyrox.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pyrox.dir/main.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/zinic/projects/Pyrox/main.c > CMakeFiles/pyrox.dir/main.c.i

CMakeFiles/pyrox.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pyrox.dir/main.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/zinic/projects/Pyrox/main.c -o CMakeFiles/pyrox.dir/main.c.s

CMakeFiles/pyrox.dir/main.c.o.requires:
.PHONY : CMakeFiles/pyrox.dir/main.c.o.requires

CMakeFiles/pyrox.dir/main.c.o.provides: CMakeFiles/pyrox.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/pyrox.dir/build.make CMakeFiles/pyrox.dir/main.c.o.provides.build
.PHONY : CMakeFiles/pyrox.dir/main.c.o.provides

CMakeFiles/pyrox.dir/main.c.o.provides.build: CMakeFiles/pyrox.dir/main.c.o

# Object files for target pyrox
pyrox_OBJECTS = \
"CMakeFiles/pyrox.dir/ev_test.c.o" \
"CMakeFiles/pyrox.dir/main.c.o"

# External object files for target pyrox
pyrox_EXTERNAL_OBJECTS =

pyrox: CMakeFiles/pyrox.dir/ev_test.c.o
pyrox: CMakeFiles/pyrox.dir/main.c.o
pyrox: CMakeFiles/pyrox.dir/build.make
pyrox: CMakeFiles/pyrox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable pyrox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pyrox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pyrox.dir/build: pyrox
.PHONY : CMakeFiles/pyrox.dir/build

CMakeFiles/pyrox.dir/requires: CMakeFiles/pyrox.dir/ev_test.c.o.requires
CMakeFiles/pyrox.dir/requires: CMakeFiles/pyrox.dir/main.c.o.requires
.PHONY : CMakeFiles/pyrox.dir/requires

CMakeFiles/pyrox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pyrox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pyrox.dir/clean

CMakeFiles/pyrox.dir/depend:
	cd /home/zinic/projects/Pyrox && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zinic/projects/Pyrox /home/zinic/projects/Pyrox /home/zinic/projects/Pyrox /home/zinic/projects/Pyrox /home/zinic/projects/Pyrox/CMakeFiles/pyrox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pyrox.dir/depend

