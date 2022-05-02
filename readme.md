# MaxtirxEngine

## 引擎结构
- 原则：
    - 功能单元划分清晰，模块高内聚低耦合
- 文件夹设计：
```
    ---Root
        --- MatrixEngine
            --- Source
                --- Editor
                --- Runtime
                    --- Core
                    --- Render
                    --- Physics
                --- Developer
            --- Bin
            --- Shader
            --- Resource
            ---ThridParty
                --- TBB
                --- DebugHelper
            --- XXXX
        --- Sample
            --- Demo00
            --- Demo01
            --- DemoXX
        --- Doc
            --- EngineDesignPattern
            --- RenderGraph
        --- Srcipt
            --- build.bat
        --- Cmake
            --- XXX.cmake
        --- build_windows_sln.bat
        --- CMakeLists.txt
        --- readme.md
```
    


## 命名规范
* 所有函数都处于Matrix命名空间下，
* 所有文件命名都必须带有MTX前缀
* 函数，命名空间采用PascalCase风格（毕竟UE也是这个风格的）*
* 枚举类必须E开头
* 成员变量加m开头
* 静态变量需要加s开头
* 结构体变量不需要
