set(SharedLibName "Function")

# ===============================文件分组==============================
FILE(GLOB_RECURSE HeaderFiles *.h *.inl *.hpp) # GLOB 获取./include/目录下的*.h 储存在变量HEAD_RIGEL_EDITOR中
FILE(GLOB_RECURSE SourceFiles *.cpp) # GLOB 递归获取./include/目录和子目录下的*.cpp 储存在变量HEAD_RIGEL_EDITOR中

# source_group("Header Files" FILES ${HeaderFiles})
# source_group("Source Files" FILES ${SourceFiles})
# message(STATUS ${SharedLibName}.HeaderFiles = ${HeaderFiles})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeaderFiles} ${SourceFiles})
add_library(${SharedLibName} SHARED ${HeaderFiles} ${SourceFiles})

set_target_properties(${SharedLibName} PROPERTIES FOLDER ${ENGINE_ROOT_DIR}/${SECOND_LEVEL_DIR})

# ==============================设置target属性=============================
target_compile_definitions(${SharedLibName} PRIVATE $<$<CONFIG:Debug>: _TEST_MACRO_>)
target_compile_definitions(${SharedLibName} PUBLIC "UNICODE; _UNICODE")
target_include_directories(${SharedLibName} PRIVATE "${ENGINE_SOURCE_RUNTIME_DIR}")
target_include_directories(${SharedLibName} PRIVATE "${ENGINE_SOURCE_RUNTIME_DIR}/Function")

# public 和 private 尽量多注意
target_link_libraries(${SharedLibName} PRIVATE "Core;Container;Math")

if(MSVC)
    target_link_options(${SharedLibName} PRIVATE
        $<$<CONFIG:Debug>:/INCREMENTAL> # default is incremental
        $<$<CONFIG:Release>:/INCREMENTAL:NO> # 是否开启增量编译
    )
endif()

# #==========================================生成器表达式 Debug=====================================
# file(GENERATE OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../generator_test.txt" CONTENT "$<$<BOOL:release>:dbghelp>\n")