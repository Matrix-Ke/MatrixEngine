
get_filename_component(current_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" current_dir_name ${current_dir_name})
message(STATUS current_dir_name = ${current_dir_name})
set(second_level_dir "${current_dir_name}")


fAdd_all_subdirectory()