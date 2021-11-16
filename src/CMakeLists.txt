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

#*******************************************************************************
# Build target
#******************************************************************************/
if(shared_lib)
    add_library(${target} SHARED)
else()
    add_library(${target} STATIC)
endif()
target_link_libraries( ${target} Utils)
set_target_properties(${target} PROPERTIES VERSION ${PROJECT_VERSION})

#*******************************************************************************
# Install target
#******************************************************************************/
install( DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h" )
install( TARGETS ${target} EXPORT ${install_target}
    RUNTIME DESTINATION bin INCLUDES DESTINATION include
    LIBRARY DESTINATION lib ARCHIVE DESTINATION lib )

install( EXPORT ${install_target} DESTINATION share/cmake )