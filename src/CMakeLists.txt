#*******************************************************************************
# @file CMakeLists.txt
# @author Florian Eigentler
# @brief
# @version 0.1
# @date 2021-11-08
# @copyright Copyright (c) 2021
#*******************************************************************************
set(target ${CMAKE_PROJECT_NAME})
set(install_target ${target})

#*******************************************************************************
# Add subdirecotries
#******************************************************************************/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(Utils)
add_subdirectory(JSON)
add_subdirectory(Parameter)
add_subdirectory(Math)
add_subdirectory(MPI)
add_subdirectory(Global)
add_subdirectory(HDF5)

#*******************************************************************************
# Build target
#******************************************************************************/
if(shared_lib)
    add_library(${target} SHARED)
else()
    add_library(${target} STATIC)
endif()
target_link_libraries(${target} Utils JSON Parameter Math MPI Global HDF5)
set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

#*******************************************************************************
# Install target
#******************************************************************************/
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(TARGETS ${target} EXPORT ${install_target}
    RUNTIME DESTINATION bin INCLUDES DESTINATION include
    LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

install(EXPORT ${install_target} DESTINATION share/cmake)