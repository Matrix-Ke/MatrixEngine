set(THIRD_PARTY_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty" )

#======================================全局函数================================
function(getCurrentDirName _current_dir_name)
    get_filename_component(temp_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME )
    string(REPLACE " " "_" temp_dir_name ${temp_dir_name})
    set(${_current_dir_name}  ${temp_dir_name}  PARENT_SCOPE)
endfunction(getCurrentDirName current_dir_name)

# get_filename_component(current_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# string(REPLACE " " "_" current_dir_name ${current_dir_name})

#添加子文件夹必须防止最后面
fAdd_all_subdirectory()