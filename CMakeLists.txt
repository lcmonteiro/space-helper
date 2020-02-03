cmake_minimum_required (VERSION 3.10)
# project name
project (SpaceHelper)
# ---------------------------------------------------------
# project properties 
# ---------------------------------------------------------
enable_testing()
# properties
set(CMAKE_CXX_STANDARD 14)
# options
add_compile_options(-Wall -Wextra)
# definitions
# add_definitions(-DVAR_ORDERED_MAP)
# ---------------------------------------------------------
# subscrive subdirectories 
# ---------------------------------------------------------
# dispacher
add_subdirectory(dispatcher)
# -----------------------------------------------------------------------------
# End
# -----------------------------------------------------------------------------