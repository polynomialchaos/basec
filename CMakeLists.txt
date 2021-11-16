#*******************************************************************************
# @file CMakeLists.txt
# @author Florian Eigentler
# @brief
# @version 0.1
# @date 2021-11-08
# @copyright Copyright (c) 2021
#*******************************************************************************
cmake_minimum_required(VERSION 3.16.3)

#*******************************************************************************
# CMake settings
#******************************************************************************/
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH} )

#*******************************************************************************
# Project settings
#******************************************************************************/
project(basec VERSION 1.0.0 DESCRIPTION "Base C library")
set(target ${CMAKE_PROJECT_NAME})
set(install_target ${target})

set(build_unit_tests ON)
set(memory_check ON)

if(build_unit_tests)
    enable_testing()
    if(memory_check)
        include(CTest)
        find_program(MEMORYCHECK_COMMAND NAMES valgrind)
        set( MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full \
            --show-leak-kinds=all --show-reachable=yes --track-origins=yes")
    endif()
endif()

#*******************************************************************************
# Compiler settings
#******************************************************************************/
if(CMAKE_C_COMPILER_ID MATCHES GNU)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall -Wextra")
    set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELEASE} -pg")
elseif(CMAKE_C_COMPILER_ID MATCHES AppleClang)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_FLAGS_RELEASE "-O3")
    set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall -Wextra")
    set(CMAKE_C_FLAGS_PROFILE "${CMAKE_C_FLAGS_RELEASE} -pg")
else()
    MESSAGE(FATAL_ERROR
        "Provided unsupported C compiler ${CMAKE_C_COMPILER_ID}!")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: Debug Release" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
        STRINGS Debug Release Profile)
endif()

if( CMAKE_BUILD_TYPE MATCHES "Debug" )
    add_definitions( "-DDEBUG" )
endif()

#*******************************************************************************
# Add subdirecotries
#******************************************************************************/
file(GLOB target_sources
    src/*.c
)

#*******************************************************************************
# Build target
#******************************************************************************/
add_library(${target} SHARED ${target_sources})
set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include> PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#*******************************************************************************
# Unit test target
#******************************************************************************/
if(build_unit_tests)
    include(unit_test)
endif()

#*******************************************************************************
# Install target
#******************************************************************************/
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(TARGETS ${target} EXPORT ${install_target}
    RUNTIME DESTINATION bin INCLUDES DESTINATION include
    LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
