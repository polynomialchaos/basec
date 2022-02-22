#*******************************************************************************
# @file CMakeLists.txt
# @author Florian Eigentler
# @brief
# @version 1.0.0
# @date 2022-02-22
# @copyright Copyright (c) 2022 by Florian Eigentler.
#  This work is licensed under terms of the MIT license (<LICENSE>).
#*******************************************************************************
set(target MPI)

#*******************************************************************************
# Add subdirecotries
#******************************************************************************/
file(GLOB target_sources
    src/*.c
)

#*******************************************************************************
# External libraries
#******************************************************************************/
if(use_mpi)
    find_package(MPI REQUIRED)
endif()

#*******************************************************************************
# Build target
#******************************************************************************/
add_library(${target} OBJECT ${target_sources})
target_link_libraries(${target} Utils ${MPI_C_LIBRARIES})

target_include_directories(${target} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${MPI_C_INCLUDE_PATH}>"
    "$<INSTALL_INTERFACE:include>" "$<INSTALL_INTERFACE:${MPI_C_INCLUDE_PATH}>"
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#*******************************************************************************
# Unit test target
#******************************************************************************/
include(unit_test)
unit_test(${target} "test/mpi.c")

#*******************************************************************************
# Install target
#******************************************************************************/
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(TARGETS ${target} EXPORT ${install_target}
    RUNTIME DESTINATION bin INCLUDES DESTINATION include
    LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)