# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler

# Include any dependencies generated for this target.
include CMakeFiles/Interpreter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Interpreter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Interpreter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Interpreter.dir/flags.make

CMakeFiles/Interpreter.dir/interpreter.cpp.o: CMakeFiles/Interpreter.dir/flags.make
CMakeFiles/Interpreter.dir/interpreter.cpp.o: /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/interpreter.cpp
CMakeFiles/Interpreter.dir/interpreter.cpp.o: CMakeFiles/Interpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Interpreter.dir/interpreter.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Interpreter.dir/interpreter.cpp.o -MF CMakeFiles/Interpreter.dir/interpreter.cpp.o.d -o CMakeFiles/Interpreter.dir/interpreter.cpp.o -c /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/interpreter.cpp

CMakeFiles/Interpreter.dir/interpreter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Interpreter.dir/interpreter.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/interpreter.cpp > CMakeFiles/Interpreter.dir/interpreter.cpp.i

CMakeFiles/Interpreter.dir/interpreter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Interpreter.dir/interpreter.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/interpreter.cpp -o CMakeFiles/Interpreter.dir/interpreter.cpp.s

CMakeFiles/Interpreter.dir/json_reader.cpp.o: CMakeFiles/Interpreter.dir/flags.make
CMakeFiles/Interpreter.dir/json_reader.cpp.o: /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/json_reader.cpp
CMakeFiles/Interpreter.dir/json_reader.cpp.o: CMakeFiles/Interpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Interpreter.dir/json_reader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Interpreter.dir/json_reader.cpp.o -MF CMakeFiles/Interpreter.dir/json_reader.cpp.o.d -o CMakeFiles/Interpreter.dir/json_reader.cpp.o -c /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/json_reader.cpp

CMakeFiles/Interpreter.dir/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Interpreter.dir/json_reader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/json_reader.cpp > CMakeFiles/Interpreter.dir/json_reader.cpp.i

CMakeFiles/Interpreter.dir/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Interpreter.dir/json_reader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/json_reader.cpp -o CMakeFiles/Interpreter.dir/json_reader.cpp.s

CMakeFiles/Interpreter.dir/main.cpp.o: CMakeFiles/Interpreter.dir/flags.make
CMakeFiles/Interpreter.dir/main.cpp.o: /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/main.cpp
CMakeFiles/Interpreter.dir/main.cpp.o: CMakeFiles/Interpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Interpreter.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Interpreter.dir/main.cpp.o -MF CMakeFiles/Interpreter.dir/main.cpp.o.d -o CMakeFiles/Interpreter.dir/main.cpp.o -c /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/main.cpp

CMakeFiles/Interpreter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Interpreter.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/main.cpp > CMakeFiles/Interpreter.dir/main.cpp.i

CMakeFiles/Interpreter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Interpreter.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/main.cpp -o CMakeFiles/Interpreter.dir/main.cpp.s

CMakeFiles/Interpreter.dir/token.cpp.o: CMakeFiles/Interpreter.dir/flags.make
CMakeFiles/Interpreter.dir/token.cpp.o: /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/token.cpp
CMakeFiles/Interpreter.dir/token.cpp.o: CMakeFiles/Interpreter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Interpreter.dir/token.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Interpreter.dir/token.cpp.o -MF CMakeFiles/Interpreter.dir/token.cpp.o.d -o CMakeFiles/Interpreter.dir/token.cpp.o -c /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/token.cpp

CMakeFiles/Interpreter.dir/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Interpreter.dir/token.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/token.cpp > CMakeFiles/Interpreter.dir/token.cpp.i

CMakeFiles/Interpreter.dir/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Interpreter.dir/token.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter/token.cpp -o CMakeFiles/Interpreter.dir/token.cpp.s

# Object files for target Interpreter
Interpreter_OBJECTS = \
"CMakeFiles/Interpreter.dir/interpreter.cpp.o" \
"CMakeFiles/Interpreter.dir/json_reader.cpp.o" \
"CMakeFiles/Interpreter.dir/main.cpp.o" \
"CMakeFiles/Interpreter.dir/token.cpp.o"

# External object files for target Interpreter
Interpreter_EXTERNAL_OBJECTS =

main: CMakeFiles/Interpreter.dir/interpreter.cpp.o
main: CMakeFiles/Interpreter.dir/json_reader.cpp.o
main: CMakeFiles/Interpreter.dir/main.cpp.o
main: CMakeFiles/Interpreter.dir/token.cpp.o
main: CMakeFiles/Interpreter.dir/build.make
main: CMakeFiles/Interpreter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Interpreter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Interpreter.dir/build: main
.PHONY : CMakeFiles/Interpreter.dir/build

CMakeFiles/Interpreter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Interpreter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Interpreter.dir/clean

CMakeFiles/Interpreter.dir/depend:
	cd /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/Interpreter /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler /Users/dadidou/Documents/Telecom/1A/Info/Compilation/Imperative_Compiler/CMakeFiles/Interpreter.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Interpreter.dir/depend

