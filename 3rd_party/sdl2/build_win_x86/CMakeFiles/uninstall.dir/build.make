# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\dev\botijo\3rd_party\sdl2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\dev\botijo\3rd_party\sdl2\build_win_x86

# Utility rule file for uninstall.

# Include the progress variables for this target.
include CMakeFiles\uninstall.dir\progress.make

CMakeFiles\uninstall:
	echo >nul && "C:\Program Files\CMake\bin\cmake.exe" -P C:/dev/botijo/3rd_party/sdl2/build_win_x86/cmake_uninstall.cmake

uninstall: CMakeFiles\uninstall
uninstall: CMakeFiles\uninstall.dir\build.make

.PHONY : uninstall

# Rule to build all files generated by this target.
CMakeFiles\uninstall.dir\build: uninstall

.PHONY : CMakeFiles\uninstall.dir\build

CMakeFiles\uninstall.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : CMakeFiles\uninstall.dir\clean

CMakeFiles\uninstall.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\dev\botijo\3rd_party\sdl2 C:\dev\botijo\3rd_party\sdl2 C:\dev\botijo\3rd_party\sdl2\build_win_x86 C:\dev\botijo\3rd_party\sdl2\build_win_x86 C:\dev\botijo\3rd_party\sdl2\build_win_x86\CMakeFiles\uninstall.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\uninstall.dir\depend
