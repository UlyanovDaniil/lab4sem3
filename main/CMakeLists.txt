# Get all cpp-files in the current directory
file(GLOB main_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


foreach(main_filename ${main_list})
  # Get file name without extension
  get_filename_component(sample ${main_filename} NAME_WE)

  # Add and configure executable file to be produced
  add_executable(${sample} ${main_filename})
  target_link_libraries(${sample} ${MP2_LIBRARY})
  set_target_properties(${sample} PROPERTIES
    OUTPUT_NAME "${sample}"
    PROJECT_LABEL "${sample}"
    RUNTIME_OUTPUT_DIRECTORY "../")
endforeach()
