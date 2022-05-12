# FILE(GLOB HeaderFiles ./*.h)  #GLOB 获取./include/目录下的*.h 储存在变量HEAD_RIGEL_EDITOR中
# FILE(GLOB SourceFiles ./*.cpp)#GLOB 递归获取./include/目录和子目录下的*.cpp 储存在变量HEAD_RIGEL_EDITOR中
# source_group("Header Files" FILES ${HeaderFiles})
# source_group("Source Files" FILES ${SourceFiles})
set(DemoName "")
getCurrentDirName(DemoName)

FILE(GLOB SourceFiles ./*.cpp)
FILE(GLOB ResourceFile ./*.json)
message(STATUS ResourceFile = ${ResourceFile})
source_group("Source Files" FILES ${SourceFiles})
source_group("Resource File" FILES ${ResourceFile})
add_executable(${DemoName} ${SourceFiles} ${ResourceFile})
set_target_properties(${DemoName} PROPERTIES FOLDER ${SampleName}/${DemoName})

add_dependencies(${DemoName} "Core")
target_include_directories(${DemoName} PRIVATE ${ENGINE_SOURCE_RUNTIME_DIR})
target_link_libraries(${DemoName} "Core")