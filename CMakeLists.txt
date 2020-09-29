####################################################################################
# Welcome to the CMake build system for StatePattern Steering Behaviours examples. #
# This is the main file where the general build environment is set-up and the      #
# the build configuration options are initialized.                                 #
####################################################################################

cmake_minimum_required(VERSION 3.15.0)

##################################################################
#############               SOLUTION                 #############
##################################################################

project(SteeringBehaviours LANGUAGES CXX)

##################################################################
#############            ARRIBAR PROJECT             #############
##################################################################

add_subdirectory(Arribar/)

##################################################################
#############           DEAMBULAR PROJECT            #############
##################################################################

add_subdirectory(Deambular/)

##################################################################
#############            ESCAPAR PROJECT             #############
##################################################################

add_subdirectory(Escapar/)

##################################################################
#############       FSMCOMPORTAMIENTOS PROJECT       #############
##################################################################

add_subdirectory(FSMyComportamientos/)

##################################################################
#############       INTERCEPTAREVADIR PROJECT        #############
##################################################################

add_subdirectory(InterceptarEvadir/)

##################################################################
#############       OBSTACULOSPAREDES PROJECT        #############
##################################################################

add_subdirectory(ObstaculosParedes/)

##################################################################
#############           GENERAL CONFIG               #############
##################################################################

# Make CXX_STANDARD version a requirement (it won't compile with older version)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Visual Studio specific config
if (MSVC)
    # Multiprocesor compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" CACHE STRING "compile flags" FORCE)
endif ()