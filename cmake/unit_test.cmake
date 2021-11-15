#*******************************************************************************
# @file unit_test.cmake
# @author Florian Eigentler
# @brief
# @version 0.1
# @date 2021-11-08
# @copyright Copyright (c) 2021
#******************************************************************************/

#*******************************************************************************
# Add subdirecotries
#******************************************************************************/
file(GLOB ut_target_sources
    test/*.c
)

#*******************************************************************************
# Build target
#******************************************************************************/
foreach(ut_target_source ${ut_target_sources})
    get_filename_component(test_name ${ut_target_source} NAME_WE)
    set(test_target ${target}_${test_name})

    add_executable(${test_target} ${ut_target_source})
    add_dependencies(${test_target} ${target})
    target_link_libraries(${test_target} ${target})

    set_target_properties(${test_target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

    add_test(
        NAME ${test_target} COMMAND ${test_target}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests
    )
endforeach()
