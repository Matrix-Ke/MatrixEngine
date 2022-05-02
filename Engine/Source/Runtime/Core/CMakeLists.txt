set(SharedLibName "MatrixCore")


#===============================文件分组==============================
FILE(GLOB HeaderFiles ./*.h)  #GLOB 获取./include/目录下的*.h 储存在变量HEAD_RIGEL_EDITOR中
FILE(GLOB SourceFiles ./*.cpp)#GLOB 递归获取./include/目录和子目录下的*.cpp 储存在变量HEAD_RIGEL_EDITOR中
source_group("Header Files" FILES ${HeaderFiles})
source_group("Source Files" FILES ${SourceFiles})

add_library(${SharedLibName} SHARED ${HeaderFiles} ${SourceFiles})
set_target_properties(${SharedLibName} PROPERTIES FOLDER ${engine_root_dir}/${second_level_dir})


#==============================设置target属性=============================
target_compile_definitions(${SharedLibName}  PRIVATE  $<$<CONFIG:Debug>: _TEST_MACRO_> )
target_include_directories(${SharedLibName}  INTERFACE ${HeaderFiles})
target_link_libraries(${SharedLibName} PRIVATE dbghelp Winmm)
target_link_directories(${SharedLibName} PRIVATE  )