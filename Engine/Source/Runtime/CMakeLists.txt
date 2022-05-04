
# get_filename_component(current_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# string(REPLACE " " "_" current_dir_name ${current_dir_name})
# set(SECOND_LEVEL_DIR "${current_dir_name}")
set(SECOND_LEVEL_DIR "")
getCurrentDirName(SECOND_LEVEL_DIR)

fAdd_all_subdirectory()