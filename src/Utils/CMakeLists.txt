#*******************************************************************************
# @file CMakeLists.txt
# @author Florian Eigentler
# @brief
# @version 1.0.0
# @date 2022-02-22
# @copyright Copyright (c) 2022 by Florian Eigentler.
#  This work is licensed under terms of the MIT license (<LICENSE>).
#*******************************************************************************
set(target Utils)

#*******************************************************************************
# Add subdirecotries
#******************************************************************************/
file(GLOB target_sources
    src/*.c
)

#*******************************************************************************
# Build target
#******************************************************************************/
add_library(${target} OBJECT ${target_sources})

target_include_directories(${target} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include> PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

#*******************************************************************************
# Unit test target
#******************************************************************************/
include(unit_test)
unit_test(${target} "test/print.c")
unit_test(${target} "test/version.c")
unit_test(${target} "test/logging.c")
unit_test(${target} "test/file.c")
unit_test(${target} "test/memory.c")
unit_test(${target} "test/string.c")
unit_test(${target} "test/string_conversion.c")
unit_test(${target} "test/time.c")
unit_test(${target} "test/linked_list.c")

#*******************************************************************************
# Install target
#******************************************************************************/
install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(TARGETS ${target} EXPORT ${install_target}
    RUNTIME DESTINATION bin INCLUDES DESTINATION include
    LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
