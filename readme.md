# MaxtirxEngine

## 引擎开发设计
- [引擎开发日志](./Doc/TodoList.md)
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
* 与平台相关的接口必须带有MX前缀
* 函数，命名空间采用PascalCase风格（毕竟UE也是这个风格的）
* 枚举类必须E开头
* 成员变量加m开头
* 静态变量需要加s开头
* 结构体变量不需要

## 版本管理规范
### 分支规范
* 主分支： master
* 功能分支：feature
* 测试分支：test
* 开发分支： dev
* 修复分支： debug
### 代码提交规范
* commit形式： 【tag】：xxxxx； 目前可用tag如下: feature,bug, doc, cmake，demo
* master分支只允许feature和debug分支merge，其他分支无合并权限