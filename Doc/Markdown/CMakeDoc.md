# 基础知识

## cmake使用方式
* 当使用者将你的库作为第三方库来使用的时候，CMAKE_SOURCE_DIR 以及 CMAKE_BINARY_DIR 就会变成使用者所在项目的变量了。那么，在你的库中，CMake 获取的 CMAKE_SOURCE_DIR 就会是 project-root，而不是你可能想要的 project-root/extern/your-lib-root CMAKE_BINARY_DIR 同理。因此，正确的做法是使用 PROJECT_SOURCE_DIR 以及 PROJECT_BINARY_DIR，他们的获取是 CMake 根据遇到的最近的 project() 命令来决定的。
## CMake理解
* cmake是构建系统生成器，主要功能是描述项目结构，表达模块依赖， 从而项目友好的方式表达构建过程
* Cmake 围绕构建目标声明，一切围绕着target
### 开头

```cmake
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project (<project-name> VERSION 1.2.3.4)
# CMAKE_PROJECT_NAME
# PROJECT_VERSION
# - PROJECT_VERSION_MAJOR
# - PROJECT_VERSION_MINOR
# - PROJECT_VERSION_PATCH
# - PROJECT_VERSION_TWEAK
# PROJECT_SOURCE_DIR
```

### 路径变量

- `<project_name>_BINARY_DIR` 含 `project()` 的 `CMakeLists.txt` 所在目录的子文件 `build/` 
- `<project_name>_SOURCE_DIR`：含 `project()` 的 `CMakeLists.txt` 所在目录
- `CMAKE_BINARY_DIR`：`build/` 
- `CMAKE_SOURCE_DIR`：最上级 `CMakeLists.txt` 所在目录
- `CMAKE_CURRENT_BINARY_DIR`：`build/` 内，`CMAKE_CURRENT_SOURCE_DIR` 关于 `CMAKE_SOURCE_DIR` 的相对路径加上 `<project_name>_SOURCE_DIR` 
- `CMAKE_CURRENT_SOURCE_DIR`：正在处理的 `CMakeLists.txt` 所在目录
- `CMAKE_CURRENT_LIST_DIR`：正在处理的 `CMakeLists.txt` 所在目录
  - 当使用 `include()` 时，该变量与 `CMAKE_CURRENT_SOURCE_DIR` 不同
  - （貌似）使用 `find_package()` 时，该变量与 `CMAKE_CURRENT_SOURCE_DIR` 不同

### 变量

- [set](https://cmake.org/cmake/help/v3.16/command/set.html) 

```cmake
# normal
set(<variable-name> <value>... [PARENT_SCOPE])
# cache
set(<variable-name> <value>... CACHE <type> <docstring> [FORCE])
# type: BOOL, FILEPATH, PATH, STRING
# FORCE: 每次 configure 都会刷新
```

- 变量需要区分变量名和变量值，如 `var` 和 `${var}` 

- 变量可以嵌套取值

  ```cmake
  set(A_A aa)
  set(var A)
  message(STATUS "${A_${var}}") # aa
  ```

- [unset](https://cmake.org/cmake/help/latest/command/unset.html)
  ```
  unset(<variable> [CACHE | PARENT_SCOPE])
  ```
  - 

### 类型

- 字符串 [string](https://cmake.org/cmake/help/v3.16/command/string.html) 

  - 基础

    - 格式 `"..."`，如 `"dd${var}dd"`，`"a string"` 

    - 转义字符加双斜杠，如 `"...\\n..."` 

    - 特殊字符加单斜杠，如 `"...\"..."` 

    - `${var}` 不同于 `"${var}"` 

      ```cmake
      set(specialStr "aaa;bbb")
      
      # example 1
      message(STATUS ${specialStr}) # aaabbb
      message(STATUS "${specialStr}") # aaa;bbb
      
      # example 2
      function(PrintVar var)
        message(STATUS "${var}")
      endfunction()
      
      PrintVar(${specialStr}) # aaa
      PrintVar("${specialStr}") # aaa;bbb
      ```

  - find：`string(FIND <string> <substring> <output_variable> [REVERSE])`，未找到则结果为 `-1` 

  - manipulation

    ```cmake
    string(APPEND <string-var> [<input>...])
    string(PREPEND <string-var> [<input>...])
    string(CONCAT <out-var> [<input>...])
    string(JOIN <glue> <out-var> [<input>...])
    string(TOLOWER <string> <out-var>)
    string(TOUPPER <string> <out-var>)
    string(LENGTH <string> <out-var>)
    string(SUBSTRING <string> <begin> <length> <out-var>)
    string(STRIP <string> <out-var>)
    string(GENEX_STRIP <string> <out-var>)
    string(REPEAT <string> <count> <out-var>)
    ```

  - comparison：`string(COMPARE <op> <string1> <string2> <out-var>)` 

  - hashing：`string(<HASH> <out-var> <input>)` 

- 列表 [list](https://cmake.org/cmake/help/v3.16/command/list.html) 

  - 创建：`set(<list_name> <item>...)` 或 `set(<list_name> "${item_0};${item_1};...;${item_n}")` 

### 调试

[message](https://cmake.org/cmake/help/v3.16/command/message.html) 

```cmake
message(STATUS/WARNING/FATAL_ERROR "str")
```

### 函数

- 按名传参和按值传参

```cmake
function(PrintVar var)
  message(STATUS "${var}: ${${var}}") 
  set(${var}  "kklTest" PARENT_SCOPE) 可以传引用
endfunction()

function(PrintValue value)
  message(STATUS "${value}")
endfunction()

set(num 3)
PrintVar(num)
PrintValue(${num})
```

- [cmake_parse_arguments](https://cmake.org/cmake/help/v3.16/command/cmake_parse_arguments.html) 

```cmake
cmake_parse_arguments("ARG" # prefix
                      <options> # TRUE / FALSE
                      <one_value_keywords>
                      <multi_value_keywords> # list
                      ${ARGN})
# 结果为 ARG_*
# - ARG_<option>
# - ARG_<one_value_keyword>
# - ARG_<multi_value_keyword>
```

- list 作为参数
  - 调用时写成 `${list}` 会被展开成多个参数
  - 调用时写成 `"${list}"`，函数内部参数即为正常 list
  - 调用时写成 `<list>`，函数内部需使用 `${arg_list}` 得到正常 list

### 控制流

- 循环 n 次

```cmake
set(i 0)
while(i LESS <n>)
  # ...
  math(EXPR i "${i} + 1")
endwhile()
```

- 遍历单个 list

```cmake
foreach(v ${list})
  # ... ${v}
endforeach()
```

- 遍历两个等长 list

```cmake
list(LENGTH <list0> n)
set(i 0)
while(i LESS n)
  list(GET <list0> ${i} v0)
  list(GET <list1> ${i} v1)
  # ...
  math(EXPR i "${i} + 1")
endwhile()
```

- 遍历结构 list

```cmake
list(LENGTH <struct_list> n)
set(i 0)
while(i LESS n)
  list(SUBLIST <struct_list> ${i} <struct_size> <obj>)
  list(GET <obj> 0 <field_0>)
  list(GET <obj> 1 <field_1>)
  # ...
  list(GET <obj> k <field_k>) # k == <struct_size> - 1
  
  # ...
  math(EXPR i "${i} + ${struct_size}")
endwhile()
```

### 正则表达式

- string

```cmake
string(REGEX
	MATCH
	<regular_expression>
	<output_variable>
	<input> [<input>...])
# 匹配一次
# CMAKE_MATCH_<n>
# - 由 '()' 句法捕获
# - n : 0, 1, ..., 9
# - CMAKE_MATCH_0 == <output_variable>
# - n == CMAKE_MATCH_COUNT

string(REGEX
	MATCHALL
	<regular_expression>
	<output_variable>
	<input> [<input>...])
# 匹配多次，结果为 list
# CMAKE_MATCH_* 无用

string(REGEX
	REPLACE
	<regular_expression>
	<replacement_expression>
	<output_variable>
	<input> [<input>...])
# \1, \2, ..., \9 表示 '()' 捕获的结果
# 在 <replacement_expression> 中需要写成 \\1, \\2, ..., \\9
```

- list

```cmake
list(FILTER <list>
  INCLUDE/EXCLUDE
  REGEX <regular_expression>)
# INCLUDE: 将所有匹配替换成 <list>
# EXCLUDE: 将所有匹配从 <list> 排除
```

### target

- add: [add_executable](https://cmake.org/cmake/help/v3.16/command/add_executable.html), [add_library](https://cmake.org/cmake/help/v3.16/command/add_library.html) 

```cmake
# 1. add target
  # 1.1 exe
  add_executable(<name> [<source>...])

  # 1.2 lib/dll
    # 1.2.1 normal
    add_library(<name> STATIC|SHARED [<source>...])
    # 1.2.2 interface : e.g. pure head files
    add_library(<name> INTERFACE)

# 2. alias
add_library(<alias> ALIAS <target>)
# <alias> 可以用命名空间 <namespace>::<id>，如 Ubpa::XXX
```

- source: 

```cmake
target_sources(<target>
  PUBLIC    <item>...
  PRIVATE   <item>...
  INTERFACE <item>...
)

# gather sources
file(GLOB_RECURSE sources
  # header files
  <path>/*.h
  <path>/*.hpp
  <path>/*.hxx
  <path>/*.inl
  
  # source files
  <path>/*.c
  
  <path>/*.cc
  <path>/*.cpp
  <path>/*.cxx
  
  # shader files
  <path>/*.vert # glsl vertex shader
  <path>/*.tesc # glsl tessellation control shader
  <path>/*.tese # glsl tessellation evaluation shader
  <path>/*.geom # glsl geometry shader
  <path>/*.frag # glsl fragment shader
  <path>/*.comp # glsl compute shader
  
  <path>/*.hlsl
  
  # Qt files
  <path>/*.qrc
  <path>/*.ui
)

foreach(source ${sources})
  get_filename_component(dir ${source} DIRECTORY)
  if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${dir})
    source_group("src" FILES ${source})
  else()
    file(RELATIVE_PATH rdir ${PROJECT_SOURCE_DIR} ${dir})
    if(MSVC)
      string(REPLACE "/" "\\" rdir_MSVC ${rdir})
      set(rdir "${rdir_MSVC}")
    endif()
    source_group(${rdir} FILES ${source})
  endif()
endforeach()
```
- source_group 
  ```
  source_group(<name> [FILES <src>...] [REGULAR_EXPRESSION <regex>])
  source_group(TREE <root> [PREFIX <prefix>] [FILES <src>...])
  ```
  - 用于定义工程中的源码属于哪个目录组, 主要用于 Visual Studio 中. 有以下选项:
  - TREE CMake 会自动检测 <src> 文件路径来确定需要创建的 source groups, 使得工程中的目录结构和实际文件在磁盘上的目录结构一致. 根据 <root> 指定的根路径将 <src> 中的路径截断为相对路径;
  - PREFIX 在 <root> 路径中的 Source group 和文件会被放在 <prefix> group 中;
  - FILES 将显式指定的所有源文件都放在 <name> group 中, 如果是相对路径, 则是以当前源码路径为参考;
  - REGULAR_EXPRESSION 可以匹配到正则表达式的源码文件会被放在 <name> group 中. 如果某个源码文件可以和多个组进行匹配, 则该文件会被归到最后一个组; 如果某个源码文件没有和任一个组匹配上, 则该文件会被归到正则表达式的最后一个组.

- definition
```cmake
target_compile_definitions(<target>
  PUBLIC    <item>...
  PRIVATE   <item>...
  INTERFACE <item>...
)
# <item> => #define <item>
```

- include directorie

```cmake
target_include_directories(mylib PUBLIC
  $<BUILD_INTERFACE:<absolute_path>>
  $<INSTALL_INTERFACE:<relative_path>>  # <install_prefix>/<relative_path>
)
# e.g.
# - <absolute_path>: ${PROJECT_SOURCE_DIR}/include
# - <relative_path>: <package_name>/include
```

- link library

```cmake
target_link_libraries(<target>
  PUBLIC    <item>...
  PRIVATE   <item>...
  INTERFACE <item>...
)
```
- [add_custom_command](https://cmake.org/cmake/help/latest/command/add_custom_command.html)
```
add_custom_command(OUTPUT output1 [output2 ...]
                   COMMAND command1 [ARGS] [args1...]
                   [COMMAND command2 [ARGS] [args2...] ...]
                   [MAIN_DEPENDENCY depend]
                   [DEPENDS [depends...]]
                   [BYPRODUCTS [files...]]
                   [IMPLICIT_DEPENDS <lang1> depend1
                                    [<lang2> depend2] ...]
                   [WORKING_DIRECTORY dir]
                   [COMMENT comment]
                   [DEPFILE depfile]
                   [JOB_POOL job_pool]
                   [VERBATIM] [APPEND] [USES_TERMINAL]
                   [COMMAND_EXPAND_LISTS])
eg: add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )
```

- [add_custom_target](cmake.org/cmake/help/latest/command/add_custom_target.html)
  ```
  add_custom_target(Name [ALL] [command1 [args1...]]
                  [COMMAND command2 [args2...] ...]
                  [DEPENDS depend depend depend ... ]
                  [BYPRODUCTS [files...]]
                  [WORKING_DIRECTORY dir]
                  [COMMENT comment]
                  [JOB_POOL job_pool]
                  [VERBATIM] [USES_TERMINAL]
                  [COMMAND_EXPAND_LISTS]
                  [SOURCES src1 [src2...]])
  eg: add_custom_target(CopyTask
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config ${CMAKE_CURRENT_SOURCE_DIR}/etc
  )
  ```
  - ${CMAKE_COMMAND}是CMake的路径，-E使CMake运行命令而不是构建
  - ALL：表明该目标会被添加到默认的构建目标，使得它每次都被运行；
    - COMMAND：指定要在构建时执行的命令行；
    - DEPENDS：指定命令所依赖的文件；
    - COMMENT：在构建时执行命令之前显示给定消息；
    - WORKING_DIRECTORY：使用给定的当前工作目录执行命令。如果它是相对路径，它将相对于对应于当前源目录的构建树目录；
    - BYPRODUCTS：指定命令预期产生的文件。
### file

- Reading

  - READ: `file(READ <filename> <out>)` 
  - STRINGS: `file(STRINGS <filename> <variable> [<options>...])` 
  - HASH: `file(<HASH> <filename> <variable>)` 
    - `<HASH>`：`MD5/SHA1/SHA224/SHA256/SHA384/SHA512/SHA3_224/SHA3_256/SHA3_384/SHA3_512` 

- Writing

  - WRITE/APPEND: `file(WRITE/APPEND <filename> <content>...)` 
  - TOUCH: `file(TOUCH [<files>...])` 
    - 若文件不存在，创建空文件
    - 若文件存在，则更新访问和/或修改时间
    - TOUCH_NOCREATE
  - GENERATE: `file(GENERATE OUTPUT <output_file> <INPUT input-file|CONTENT content>)` 
    - 在 **generation 阶段** 生成文件
    - 可添加 `CONTIDION <expression>`，其中 `<expression> == 0/1` 

- file system

  - GLOB

    ```cmake
    file(GLOB/GLOB_RECURSE <out_list>
         [LIST_DIRECTORIES true|false] # 是否包含目录
         [RELATIVE <path>] # 相对路径
         [CONFIGURE_DEPENDS] # 将结果的所有文件作为 rebuild 的检测对象
         [<globbing-expressions>...] # 简化版的正则表达式
         )
    ```

    - `<globbing-expressions>` 
      - ref：[Linux Programmer's Manual GLOB](http://man7.org/linux/man-pages/man7/glob.7.html) 
      - `?`：匹配单个字符
      - `*`：匹配**文件名/文件夹名**内的任意个字符
      - `**`：跨目录匹配任意个字符
      - `[...]`：同于正则表达式的 `[...]` 
      - `[!...]`：补

  - RENAME：`file(RENAME <oldname> <newname>)`，移动文件或文件夹

  - REMOVE：`file(REMOVE/REMOVE_RECURSE [<files>...])` 

    - `REMOVE`：删除文件，不能删除文件夹
    - `REMOVE_RECURSE`：删除文件或文件夹

  - MAKE_DIRECTORY：`file(MAKE_DIRECTORY [<directories>...])`，递归创建文件夹

  - COPY/INSTALL：`file(COPY/INSTALL <files>... DESTINATION <dir>`，拷贝/安装文件

- path conversion

  - `file(RELATIVE_PATH <variable> <directory> <file>)` 
  - `file(TO_CMAKE_PATH "<path>" <variable>)`，`'/'` 
  - `file(TO_NATIVE_PATH "<path>" <variable>)`，Windows `'\\'`，其他 `'/'` 

- transfer

  - `file(DOWNLOAD <url> <file> [<options>...])` 
    - `INACTIVITY_TIMEOUT <seconds>`：无响应等待时长
    - `TIMEOUT <seconds>`：总等待时长
    - `SHOW_PROGReSS`：进度
    - `STATUS <variable>`：状态为两个值的 list，前者为 0 时表示无错
    - `EXPECTED_HASH <HASH>=<value>`：哈希值

### [CMake系列安装，打包，导出](blog.xizhibei.me/2020/04/20/cmake-5-install-package-and-export/)
* 使用第三方库的三种方式：
  1. 安装子文件夹(和工程一起编译，调试)
  2. 安装编译产物
  3. 导出编译目录
* 安装编译产物： Cmake为此提供了完善的支持，主要是: a安装,b导出,c打包
* 导出编译目录: 这种方式不需要第三方库作为子文件夹放在使用者的项目中，它只需要导出编译目录，然后将 target 导出到 $HOME/.cmake/packages 供使用
- install
  ```cmake
  install(<FILES|PROGRAMS> files...
        TYPE <type> | DESTINATION <dir>
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [RENAME <name>] [OPTIONAL] [EXCLUDE_FROM_ALL])

  install(TARGETS <target>...
    EXPORT "${PROJECT_NAME}Targets" # 链接 export
    RUNTIME DESTINATION bin # .exe, .dll
    LIBRARY DESTINATION "${package_name}/lib" # non-DLL shared library
    ARCHIVE DESTINATION "${package_name}/lib" # .lib
  )
  install(FILES "${PROJECT_SOURCE_DIR}/include" DESTINATION "${package_name}/include")
  ```
  - FILES|PROGRAMS若为相对路径给出的文件名，将相对于当前源目录进行解释。其中，FILES为普通的文本文件，PROGRAMS指的是非目标文件的可执行程序(如脚本文件)
  - TARGETS：安装编译后的产物 target：library 以及 executable 都可以作为参数；
  - FILES：安装其它文件，比如配置文件；
  - PROGRAMS：安装可执行文件，脚本之类的，与 FILES 一样，区别在于可执行权限；
  - DIRECTORY：安装整个目录，比如文档目录，另外，你可以利用 FILES_MATCHING PATTERN "*.h" 参数来安装库所需要的头文件；
  - CODE 与 SCRIPT：这两样属于高级模式了，你可以通过它们来实现自定义安装；
  
- export()
  - export() Export targets from the build tree for use by outside projects(从构建树导出目标提供给外部工程使用)，，其实就是为了支持find_package(), 
  - find_package() 需要包的mylibconfig.cmake以及版本查找mylibconfigVersion.cmake文件

- package
- `<namespace>` 
- `<package_name>` 
  - e.g. `${PROJECT_NAME}_${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR}_${PROJECT_VERSION_PATCH}` 
- target name：`${PROJECT_NAME}_${relative_path}`，其中 `/` 要转成 `_` 
  - `string(REPLACE "/" "_" targetName "${PROJECT_NAME}_${relative_path}")` 

- bin, dll, lib path
  ```cmake
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/lib")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/lib")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/lib")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/lib")
  ```


- debug postfix

  - dll, lib: `set(CMAKE_DEBUG_POSTFIX d)` 
  - exe: `set_target_properties(<target> PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})` 
  - set_target_properties(target1 target2 ...
                      PROPERTIES prop1 value1
                      prop2 value2 ...)

- find_package
  ```
  find_package(<PackageName> [version] [REQUIRED] [[COMPONENTS] [components...]])
  ```
  - 后面都是可选项，最基础的使用形式就是 find_package 加一个 PackageName 信息。CMake 会在约定路径和通过选项指定的路径下搜索名为 FindPackageName.cmake 的文件，并执行其中的逻辑以设置一些关键的变量。约定的 PackageName_FOUND 标识是否找到对应的依赖以进行差别处理逻辑，其他的变量则根据不同 FindPackageName.cmake 的策略有所不同，通常包括该依赖暴露的头文件信息，可供链接的库的信息，以及库的构建目标等等，并可能按照模块进行划分以获得更细粒度的导出控制。
  

- add_test
  ```
  add_test(NAME <name> COMMAND <command> [<arg>...]
         [CONFIGURATIONS <config>...]
         [WORKING_DIRECTORY <dir>]
         [COMMAND_EXPAND_LISTS])
  eg: add_test(NAME mytest
         COMMAND testDriver --config $<CONFIG>
                            --exe $<TARGET_FILE:myexe>)
  ```
  - 

- include
  ```
    include(<file|module> [OPTIONAL] [RESULT_VARIABLE <VAR>] [NO_POLICY_SCOPE])
  ```
  - include指令用来载入并运行来自于文件或模块的CMake代码

- option
  ```
  option(<variable> "<help_text>" [value])
  ```
  - cmake中option起到编译开关的作用，CMakeLists.txt中option以前的语句，变量按未定义处理，option之后的语句，变量才被定义。另外，注意，option命令定义的变量不影响c或c++源码中#ifdef或者#ifndef逻辑判断，具体见案例代码。


- config
  ```cmake
  include(CMakePackageConfigHelpers)
  
  configure_package_config_file(${PROJECT_SOURCE_DIR}/config/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${package_name}/cmake" # 仅生成文件使用，后续还需要自行 install
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
    PATH_VARS "${package_name}/include"
  )
  
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY ExactVersion
  )
  
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
                ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
          DESTINATION “${PROJECT_NAME}/cmake”
  )
  ```

# 配合 VS

- cmake -G "Visual Studio 16 2019" -A x64 -S ./ -B ./build

