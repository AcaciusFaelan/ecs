enable_testing()

file(GLOB TEST_FILES "tests/*.cpp")

foreach(test_file ${TEST_FILES})
  get_filename_component(test_name ${test_file} NAME_WE)
  add_executable(${test_name} ${test_file})
  target_include_directories(${test_name} PRIVATE src)
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
