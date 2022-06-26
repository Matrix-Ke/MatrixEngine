cmake_minimum_required(VERSION 3.11)

# 防止直接在源文件下生成项目
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
        FATAL_ERROR
        "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

# =====================================全局设置=======================================
# 相关变量设置
# set(BUILD_USE_64BITS on)
set(CMAKE_DEBUG_POSTFIX "_d")
set(ENGINE_ROOT_DIR "Engine")
set(PROJECT_VERSION 1.0.0)
Project(MatrixEngine LANGUAGES CXX VERSION ${PROJECT_VERSION})
message(STATUS "Version: ${PROJECT_VERSION}")

# 设置c++ 版本 目前选择17版
set(CMAKE_CXX_STANDARD 17) # 方法一，全局设置
set(CMAKE_CXX_FLAGS "/GR-") # 设置关闭RTTI
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 方法二，通过依赖的方式设置
# set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
# add_library(CPP_compiler_flags  INTERFACE)
# target_compile_features(CPP_compiler_flags INTERFACE cxx_std_14)
# set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
# set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
# target_compile_options(CPP_compiler_flags INTERFACE
# "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
# "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
# )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Bin")

# Cmake划分目录
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(ENGINE_SOURCE_RUNTIME_DIR ${CMAKE_SOURCE_DIR}/Engine/Source/Runtime)

# ==================================引入外部包====================================
include(CMake/SetUpConfigurations.cmake)

# ===================================定义函数========================================
# 添加子文件夹
function(fAdd_all_subdirectory)
    file(GLOB _children LIST_DIRECTORIES true RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
    set(_dirlist "")

    foreach(_child ${_children})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_child}/CMakeLists.txt)
            list(APPEND _dirlist ${_child})
            add_subdirectory(${_child})
        endif()
    endforeach()
endfunction()

# ==========================================Cmake Debug=====================================
# file(GENERATE OUTPUT "./../generator_test.txt" CONTENT "$<IF:1,cpp,cxxx>")
# file(GLOB _children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/*)
# message(STATUS files = ${_dirlist})

# =======================================添加项目依赖=================================
# add_dependencies(RigelEditor rgcore)

# =======================================添加子目录====================================
fAdd_all_subdirectory()
