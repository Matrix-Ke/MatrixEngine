# Math基础的数学运算模块，提供一下基础功能：
# #基础的数学计算模块math， 对C语言常用的数学函数的封装， 以及大量的宏定义
# #向量运算单元Vector，这个提供了向量运算功能
# #矩阵运算单元Matrix，提供给引擎的空间便换，矩阵运算

set(SharedLibName "Math")

# ===============================文件分组==============================
FILE(GLOB_RECURSE HeaderFiles ./*.h ./*.inl) # GLOB 获取./include/目录下的*.h 储存在变量HEAD_RIGEL_EDITOR中
FILE(GLOB_RECURSE SourceFiles ./*.cpp) # GLOB 递归获取./include/目录和子目录下的*.cpp 储存在变量HEAD_RIGEL_EDITOR中
source_group("Header Files" FILES ${HeaderFiles})
source_group("Source Files" FILES ${SourceFiles})
add_library(${SharedLibName} SHARED ${HeaderFiles} ${SourceFiles})

# source_group(TREE  ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles} ${SourceFiles})
set_target_properties(${SharedLibName} PROPERTIES FOLDER ${ENGINE_ROOT_DIR}/${SECOND_LEVEL_DIR})

# ==============================设置target属性=============================
target_compile_definitions(${SharedLibName} PRIVATE $<$<CONFIG:Debug>: _TEST_MACRO_>)
target_compile_definitions(${SharedLibName} PUBLIC "UNICODE; _UNICODE")
target_include_directories(${SharedLibName} PRIVATE "${ENGINE_SOURCE_RUNTIME_DIR}")

# public 和 private 尽量多注意
target_link_libraries(${SharedLibName} PRIVATE "Core")

if(MSVC)
    target_link_options(${SharedLibName} PRIVATE
        $<$<CONFIG:Debug>:/INCREMENTAL> # default is incremental
        $<$<CONFIG:Release>:/INCREMENTAL:NO> # 是否开启增量编译
    )
endif()

# #==========================================生成器表达式 Debug=====================================
# file(GENERATE OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../generator_test.txt" CONTENT "$<$<BOOL:release>:dbghelp>\n")