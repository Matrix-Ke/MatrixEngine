cmake_minimum_required(VERSION  3.11)

#=====================================全局设置=======================================
#相关变量设置
set(BUILD_USE_64BITS on)
set(CMAKE_DEBUG_POSTFIX "_d")
set(PROJECT_VERSION  1.0.0)
Project(MatrixEngine  LANGUAGES CXX  VERSION ${PROJECT_VERSION})
message(STATUS "Version: ${PROJECT_VERSION}")
#设置c++ 版本 目前选择14版 
set(CMAKE_CXX_STANDARD 17) #方法一，全局设置
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#方法二，通过依赖的方式设置
# set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
# add_library(CPP_compiler_flags  INTERFACE)
# target_compile_features(CPP_compiler_flags INTERFACE cxx_std_14)
# set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
# set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
# target_compile_options(CPP_compiler_flags INTERFACE
#   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
#   "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
# )


#===================================定义函数========================================
#添加子文件夹
function(fAdd_all_subdirectory)
    file(GLOB _children  LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  ${CMAKE_CURRENT_SOURCE_DIR}/*)
    set(_dirlist "")
    foreach(_child ${_children})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_child}/CMakeLists.txt)
            list(APPEND _dirlist ${_child})
            add_subdirectory(${_child})
        endif()
    endforeach()
endfunction()


# #尽量不要是强制使用set(CMAKE_BUILD_TYPE release)这种形式， 把配置写死在代码中,如果没有buildType就提供STRING提示选择
set(DefaultBuildType "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DefaultBuildType}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DefaultBuildType}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


#=======================================Cmake划分目录===================================
# set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# macro(set_target_folder_if_exist target folder)
#   if(TARGET ${target})
#     set_target_properties(${target} PROPERTIES FOLDER ${folder})
#   endif()
# endmacro()
# # 调用：
# set_target_folder_if_exist(cmake_exe cmake)




#==========================================Cmake Debug===================================== 
# file(GENERATE OUTPUT "./../generator_test.txt" CONTENT "$<IF:1,cpp,cxxx>")
# file(GLOB _children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/*)
# message(STATUS files = ${_dirlist})


#=======================================添加子目录====================================
fAdd_all_subdirectory()



#=======================================添加项目依赖=================================
# add_dependencies(RigelEditor rgcore)



#=======================================文件安装=====================================
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
  INSTALL_DESTINATION "Bin/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
  VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)