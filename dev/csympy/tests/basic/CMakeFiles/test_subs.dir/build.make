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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tim/csympy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tim/csympy

# Include any dependencies generated for this target.
include src/tests/basic/CMakeFiles/test_subs.dir/depend.make

# Include the progress variables for this target.
include src/tests/basic/CMakeFiles/test_subs.dir/progress.make

# Include the compile flags for this target's objects.
include src/tests/basic/CMakeFiles/test_subs.dir/flags.make

src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o: src/tests/basic/CMakeFiles/test_subs.dir/flags.make
src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o: src/tests/basic/test_subs.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tim/csympy/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o"
	cd /home/tim/csympy/src/tests/basic && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test_subs.dir/test_subs.cpp.o -c /home/tim/csympy/src/tests/basic/test_subs.cpp

src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_subs.dir/test_subs.cpp.i"
	cd /home/tim/csympy/src/tests/basic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tim/csympy/src/tests/basic/test_subs.cpp > CMakeFiles/test_subs.dir/test_subs.cpp.i

src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_subs.dir/test_subs.cpp.s"
	cd /home/tim/csympy/src/tests/basic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tim/csympy/src/tests/basic/test_subs.cpp -o CMakeFiles/test_subs.dir/test_subs.cpp.s

src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.requires:
.PHONY : src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.requires

src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.provides: src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.requires
	$(MAKE) -f src/tests/basic/CMakeFiles/test_subs.dir/build.make src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.provides.build
.PHONY : src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.provides

src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.provides.build: src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o

# Object files for target test_subs
test_subs_OBJECTS = \
"CMakeFiles/test_subs.dir/test_subs.cpp.o"

# External object files for target test_subs
test_subs_EXTERNAL_OBJECTS =

src/tests/basic/test_subs: src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o
src/tests/basic/test_subs: src/tests/basic/CMakeFiles/test_subs.dir/build.make
src/tests/basic/test_subs: src/libcsympy.a
src/tests/basic/test_subs: src/teuchos/libteuchos.a
src/tests/basic/test_subs: /usr/lib64/libgmpxx.so
src/tests/basic/test_subs: /usr/lib64/libgmp.so
src/tests/basic/test_subs: src/tests/basic/CMakeFiles/test_subs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test_subs"
	cd /home/tim/csympy/src/tests/basic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_subs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/tests/basic/CMakeFiles/test_subs.dir/build: src/tests/basic/test_subs
.PHONY : src/tests/basic/CMakeFiles/test_subs.dir/build

src/tests/basic/CMakeFiles/test_subs.dir/requires: src/tests/basic/CMakeFiles/test_subs.dir/test_subs.cpp.o.requires
.PHONY : src/tests/basic/CMakeFiles/test_subs.dir/requires

src/tests/basic/CMakeFiles/test_subs.dir/clean:
	cd /home/tim/csympy/src/tests/basic && $(CMAKE_COMMAND) -P CMakeFiles/test_subs.dir/cmake_clean.cmake
.PHONY : src/tests/basic/CMakeFiles/test_subs.dir/clean

src/tests/basic/CMakeFiles/test_subs.dir/depend:
	cd /home/tim/csympy && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tim/csympy /home/tim/csympy/src/tests/basic /home/tim/csympy /home/tim/csympy/src/tests/basic /home/tim/csympy/src/tests/basic/CMakeFiles/test_subs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/tests/basic/CMakeFiles/test_subs.dir/depend
