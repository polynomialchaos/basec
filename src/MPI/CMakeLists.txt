#*******************************************************************************
# @file CMakeLists.txt
# @author Florian Eigentler
# @brief
# @version 0.1
# @date 2021-11-08
# @copyright Copyright (c) 2021
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
    find_package( MPI REQUIRED )
    list( APPEND ext_libs ${MPI_C_LIBRARIES} )
    list( APPEND compile_flags ${MPI_C_COMPILE_FLAGS} )
    list( APPEND link_flags ${MPI_C_LINK_FLAGS} )
endif()

#*******************************************************************************
# Build target
#******************************************************************************/
add_library(${target} OBJECT ${target_sources})
target_link_libraries( ${target} Utils ${MPI_C_LIBRARIES})

target_include_directories(${target} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${MPI_C_INCLUDE_PATH}>"
    "$<INSTALL_INTERFACE:include>" "$<INSTALL_INTERFACE:${MPI_C_INCLUDE_PATH}>"
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

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