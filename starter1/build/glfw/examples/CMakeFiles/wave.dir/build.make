# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xinwen/Desktop/6.837-fall18/starter1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xinwen/Desktop/6.837-fall18/starter1/build

# Include any dependencies generated for this target.
include glfw/examples/CMakeFiles/wave.dir/depend.make

# Include the progress variables for this target.
include glfw/examples/CMakeFiles/wave.dir/progress.make

# Include the compile flags for this target's objects.
include glfw/examples/CMakeFiles/wave.dir/flags.make

glfw/examples/wave.app/Contents/Resources/glfw.icns: ../glfw/examples/glfw.icns
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Copying OS X content glfw/examples/wave.app/Contents/Resources/glfw.icns"
	$(CMAKE_COMMAND) -E copy /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/examples/glfw.icns glfw/examples/wave.app/Contents/Resources/glfw.icns

glfw/examples/CMakeFiles/wave.dir/wave.c.o: glfw/examples/CMakeFiles/wave.dir/flags.make
glfw/examples/CMakeFiles/wave.dir/wave.c.o: ../glfw/examples/wave.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xinwen/Desktop/6.837-fall18/starter1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object glfw/examples/CMakeFiles/wave.dir/wave.c.o"
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wave.dir/wave.c.o   -c /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/examples/wave.c

glfw/examples/CMakeFiles/wave.dir/wave.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wave.dir/wave.c.i"
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/examples/wave.c > CMakeFiles/wave.dir/wave.c.i

glfw/examples/CMakeFiles/wave.dir/wave.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wave.dir/wave.c.s"
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/examples/wave.c -o CMakeFiles/wave.dir/wave.c.s

glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires:

.PHONY : glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires

glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides: glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires
	$(MAKE) -f glfw/examples/CMakeFiles/wave.dir/build.make glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides.build
.PHONY : glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides

glfw/examples/CMakeFiles/wave.dir/wave.c.o.provides.build: glfw/examples/CMakeFiles/wave.dir/wave.c.o


glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o: glfw/examples/CMakeFiles/wave.dir/flags.make
glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o: ../glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xinwen/Desktop/6.837-fall18/starter1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o"
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/wave.dir/__/deps/glad.c.o   -c /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/deps/glad.c

glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/wave.dir/__/deps/glad.c.i"
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/deps/glad.c > CMakeFiles/wave.dir/__/deps/glad.c.i

glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/wave.dir/__/deps/glad.c.s"
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/deps/glad.c -o CMakeFiles/wave.dir/__/deps/glad.c.s

glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires:

.PHONY : glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires

glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides: glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires
	$(MAKE) -f glfw/examples/CMakeFiles/wave.dir/build.make glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides.build
.PHONY : glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides

glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.provides.build: glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o


# Object files for target wave
wave_OBJECTS = \
"CMakeFiles/wave.dir/wave.c.o" \
"CMakeFiles/wave.dir/__/deps/glad.c.o"

# External object files for target wave
wave_EXTERNAL_OBJECTS =

glfw/examples/wave.app/Contents/MacOS/wave: glfw/examples/CMakeFiles/wave.dir/wave.c.o
glfw/examples/wave.app/Contents/MacOS/wave: glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o
glfw/examples/wave.app/Contents/MacOS/wave: glfw/examples/CMakeFiles/wave.dir/build.make
glfw/examples/wave.app/Contents/MacOS/wave: glfw/src/libglfw3.a
glfw/examples/wave.app/Contents/MacOS/wave: glfw/examples/CMakeFiles/wave.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xinwen/Desktop/6.837-fall18/starter1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable wave.app/Contents/MacOS/wave"
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wave.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glfw/examples/CMakeFiles/wave.dir/build: glfw/examples/wave.app/Contents/MacOS/wave
glfw/examples/CMakeFiles/wave.dir/build: glfw/examples/wave.app/Contents/Resources/glfw.icns

.PHONY : glfw/examples/CMakeFiles/wave.dir/build

glfw/examples/CMakeFiles/wave.dir/requires: glfw/examples/CMakeFiles/wave.dir/wave.c.o.requires
glfw/examples/CMakeFiles/wave.dir/requires: glfw/examples/CMakeFiles/wave.dir/__/deps/glad.c.o.requires

.PHONY : glfw/examples/CMakeFiles/wave.dir/requires

glfw/examples/CMakeFiles/wave.dir/clean:
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/wave.dir/cmake_clean.cmake
.PHONY : glfw/examples/CMakeFiles/wave.dir/clean

glfw/examples/CMakeFiles/wave.dir/depend:
	cd /Users/xinwen/Desktop/6.837-fall18/starter1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xinwen/Desktop/6.837-fall18/starter1 /Users/xinwen/Desktop/6.837-fall18/starter1/glfw/examples /Users/xinwen/Desktop/6.837-fall18/starter1/build /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples /Users/xinwen/Desktop/6.837-fall18/starter1/build/glfw/examples/CMakeFiles/wave.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw/examples/CMakeFiles/wave.dir/depend

