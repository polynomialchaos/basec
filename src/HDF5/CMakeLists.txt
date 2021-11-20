#*******************************************************************************
# @file CMakeLists.txt
# @author Florian Eigentler
# @brief
# @version 0.1
# @date 2021-11-08
# @copyright Copyright (c) 2021
#*******************************************************************************
set(target HDF5)

#*******************************************************************************
# Add subdirecotries
#******************************************************************************/
file(GLOB target_sources
    src/*.c
)

#*******************************************************************************
# External libraries
#******************************************************************************/
find_package(HDF5 COMPONENTS C REQUIRED)

#*******************************************************************************
# Build target
#******************************************************************************/
add_library(${target} OBJECT ${target_sources})
target_link_libraries( ${target} Utils MPI
    ${HDF5_C_HL_LIBRARIES} ${HDF5_C_LIBRARIES})

target_include_directories(${target} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${HDF5_C_INCLUDE_DIRS}>"
    "$<INSTALL_INTERFACE:include>" "$<INSTALL_INTERFACE:${HDF5_C_INCLUDE_DIRS}>"
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