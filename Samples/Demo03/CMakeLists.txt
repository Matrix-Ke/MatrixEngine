# FILE(GLOB HeaderFiles ./*.h)  #GLOB 获取./include/目录下的*.h 储存在变量HEAD_RIGEL_EDITOR中
# FILE(GLOB SourceFiles ./*.cpp)#GLOB 递归获取./include/目录和子目录下的*.cpp 储存在变量HEAD_RIGEL_EDITOR中
# source_group("Header Files" FILES ${HeaderFiles})
# source_group("Source Files" FILES ${SourceFiles})
set(DemoName  "")
getCurrentDirName(DemoName)

FILE(GLOB  SourceFiles  ./*.cpp)
source_group("Source Files" FILES ${SourceFiles})
add_executable(${DemoName} ${SourceFiles})
add_dependencies(${DemoName} "Core")


#=========================
# message(STATUS ENGINE_SOURCE_RUNTIME_DIR = ${ENGINE_SOURCE_RUNTIME_DIR})
# target_compile_definitions(${DemoName}  "")
set_target_properties(${DemoName} PROPERTIES FOLDER  ${SampleName}/${DemoName})
target_include_directories(${DemoName}   PRIVATE  ${ENGINE_SOURCE_RUNTIME_DIR})

target_link_libraries(${DemoName}  "Core")