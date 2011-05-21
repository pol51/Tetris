CMake_Minimum_Required(VERSION 2.6)

Project(Tetris)
Set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

Link_Libraries (glut)

Include_Directories(src)

File(GLOB_RECURSE source_files src/*)

Add_Executable(Tetris ${source_files})
