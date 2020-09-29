####################################################################################
# Welcome to the CMake build system for Arribar example.                           #
####################################################################################

cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_BUILD_TYPE Release)

# Find SFML
## If you want to link SFML statically
#set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_FIND_PATH ${CMAKE_PREFIX_PATH})
set(SFML_INCLUDE_PATH "${SFML_FIND_PATH}/include")
find_package(SFML 2.5 REQUIRED system window graphics audio)

# Find Box2D
set(BOX2D_FIND_PATH ${CMAKE_PREFIX_PATH})
set(BOX2D_INCLUDE_PATH "${BOX2D_FIND_PATH}/include")
find_package(box2d REQUIRED)

# Headers
set(PROJECT_INCLUDE_DIRS)
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${SFML_INCUDE_PATH})
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ${BOX2D_INCUDE_PATH})
set(PROJECT_INCLUDE_DIRS ${PROJECT_INCLUDE_DIRS} ../Libreria/include)
include_directories(${PROJECT_INCLUDE_DIRS})

# Preprocessor defines
set(DEFINES)
add_compile_definitions(${DEFINES})

# Libraries Dirs
set(PROJECT_LINK_DIRS)
set(PROJECT_LINK_DIRS ${PROJECT_LINK_DIRS} ${SFML_LIBRARIES})
set(PROJECT_LINK_DIRS ${PROJECT_LINK_DIRS} ${BOX2D_LIBRARIES})
set(PROJECT_LINK_DIRS ${PROJECT_LINK_DIRS} ../Libreria/lib)
link_directories(${PROJECT_LINK_DIRS})

# Sources
set(PROJECT_SOURCES)
file(GLOB_RECURSE PROJECT_SOURCES RELATIVE ${PROJECT_SOURCE_DIR}/Arribar/ *.c *.cpp *.h *.hpp)

# Create a executable
add_executable(Arribar ${PROJECT_SOURCES})

# Libraries
set(PROJECT_LINK_LIBS)
set(PROJECT_LINK_LIBS "StatePattern" "sfml-main" "sfml-system" "sfml-graphics" "sfml-window" "sfml-audio")

target_link_libraries(Arribar PRIVATE box2d::box2d ${PROJECT_LINK_LIBS})

# Output folder
set_target_properties(Arribar PROPERTIES PDB_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin/)
set_target_properties(Arribar PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin/)

# Set compiler to C++17
set_property(TARGET Arribar PROPERTY CXX_STANDARD 17)