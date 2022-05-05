set(SharedLibName "Container")


#===============================文件分组==============================
FILE(GLOB HeaderFiles ./*.h ./*.inl )  #GLOB 获取./include/目录下的*.h 储存在变量HEAD_RIGEL_EDITOR中
FILE(GLOB SourceFiles ./*.cpp)#GLOB 递归获取./include/目录和子目录下的*.cpp 储存在变量HEAD_RIGEL_EDITOR中
source_group("Header Files" FILES ${HeaderFiles})
source_group("Source Files" FILES ${SourceFiles})

add_library(${SharedLibName} SHARED ${HeaderFiles} ${SourceFiles})
set_target_properties(${SharedLibName} PROPERTIES FOLDER ${ENGINE_ROOT_DIR}/${SECOND_LEVEL_DIR})
set_target_properties(${SharedLibName} PROPERTIES LINKER_LANGUAGE CXX)




#==============================设置target属性=============================
target_compile_definitions(${SharedLibName}  PRIVATE  $<$<CONFIG:Debug>: _TEST_MACRO_> )
target_compile_definitions(${SharedLibName} PUBLIC  "UNICODE; _UNICODE" )
target_include_directories(${SharedLibName}  PRIVATE ${ENGINE_SOURCE_RUNTIME_DIR})
# target_link_directories(${SharedLibName} PRIVATE ${THIRD_PARTY_DIR}/TBB/Lib)
target_link_libraries(${SharedLibName} PRIVATE "Core")  

# #==========================================生成器表达式 Debug===================================== 
# file(GENERATE OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../generator_test.txt" CONTENT "$<$<BOOL:release>:dbghelp>\n")