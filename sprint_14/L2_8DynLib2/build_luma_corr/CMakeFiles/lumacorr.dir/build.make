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
CMAKE_SOURCE_DIR = /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/build_luma_corr

# Include any dependencies generated for this target.
include CMakeFiles/lumacorr.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lumacorr.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lumacorr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lumacorr.dir/flags.make

CMakeFiles/lumacorr.dir/main.cpp.o: CMakeFiles/lumacorr.dir/flags.make
CMakeFiles/lumacorr.dir/main.cpp.o: /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr/main.cpp
CMakeFiles/lumacorr.dir/main.cpp.o: CMakeFiles/lumacorr.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/build_luma_corr/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lumacorr.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lumacorr.dir/main.cpp.o -MF CMakeFiles/lumacorr.dir/main.cpp.o.d -o CMakeFiles/lumacorr.dir/main.cpp.o -c /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr/main.cpp

CMakeFiles/lumacorr.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lumacorr.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr/main.cpp > CMakeFiles/lumacorr.dir/main.cpp.i

CMakeFiles/lumacorr.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lumacorr.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr/main.cpp -o CMakeFiles/lumacorr.dir/main.cpp.s

# Object files for target lumacorr
lumacorr_OBJECTS = \
"CMakeFiles/lumacorr.dir/main.cpp.o"

# External object files for target lumacorr
lumacorr_EXTERNAL_OBJECTS =

lumacorr: CMakeFiles/lumacorr.dir/main.cpp.o
lumacorr: CMakeFiles/lumacorr.dir/build.make
lumacorr: /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr/ImgLibDll/lib/libImgLibDll.so
lumacorr: CMakeFiles/lumacorr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/build_luma_corr/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lumacorr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lumacorr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lumacorr.dir/build: lumacorr
.PHONY : CMakeFiles/lumacorr.dir/build

CMakeFiles/lumacorr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lumacorr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lumacorr.dir/clean

CMakeFiles/lumacorr.dir/depend:
	cd /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/build_luma_corr && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/LumaCorr /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/build_luma_corr /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/build_luma_corr /home/atamiev/GitHub/cpp_practice/sprint_14/L2_8DynLib2/LibProject/build_luma_corr/CMakeFiles/lumacorr.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lumacorr.dir/depend

