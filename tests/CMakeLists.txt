cmake_minimum_required(VERSION 2.6)

set(test_src_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE test_src_files ${test_src_dir}/*_test.cc)

set(libs_dir "${CMAKE_CURRENT_SOURCE_DIR}/libs")
include_directories(${libs_dir})

add_custom_target(run-tests COMMAND "")
set(test_bin_dir "${CMAKE_CURRENT_BINARY_DIR}/test-bin")

foreach(test_src_file ${test_src_files})
    get_filename_component(test_name "${test_src_file}" NAME_WE)
    add_executable("${test_name}" "${test_src_file}")
    add_dependencies("${test_name}" ${lib_utf8str})
    target_link_libraries("${test_name}" ${lib_utf8str})

    add_custom_command(TARGET run-tests
        COMMAND "${test_bin_dir}/${test_name}")
    add_dependencies(run-tests "${test_name}")

    set_target_properties("${test_name}" PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${test_bin_dir}")
endforeach()
