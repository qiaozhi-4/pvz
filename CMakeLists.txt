cmake_minimum_required(VERSION 3.28) # 指定 CMake 版本
project(pvz LANGUAGES CXX) # 显式指定使用 C++ 需要 C 语言时再添加

set(CMAKE_CXX_STANDARD 17) # 指定使用 C++17 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 要求必须支持 C++17

# Options(可选编译选项)
option(IMGUI_ENABLE_DEMO "构建 ImGui 演示窗口" OFF) # 控制是否编译 ImGui 自带的 Demo 窗口（即 imgui_demo.cpp）

# ImGui 源码路径
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui-1.92.2)

# ImGui 需要编译的文件
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_dx12.cpp
        ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
)

# 创建一个库(内容为上面需要编译的文件)[使用 OBJECT 库的好处是避免重复编译 ImGui 源文件，同时保持模块化]
add_library(imgui_obj OBJECT ${IMGUI_SOURCES})

# 为指定目标（这里是 imgui_obj）设置头文件搜索路径
target_include_directories(imgui_obj PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

# ===== 自己的代码=====
# 递归收集指定目录中的文件，生成文件列表
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
# 创建一个可执行文件目标，名为 pvz（生成 pvz.exe）,并链接到所需文件
add_executable(
        pvz
        ${APP_SOURCES}
        $<TARGET_OBJECTS:imgui_obj>
)

# 为指定目标（这里是 pvz.exe）设置头文件搜索路径
target_include_directories(pvz PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 指定目标（这里是 pvz 可执行文件）需要链接的库
#target_link_libraries(pvz PRIVATE d3d12 dxgi d3dcompiler dwmapi)
target_link_libraries(pvz PRIVATE d3d12 dxgi d3dcompiler dwmapi -static-libgcc -static-libstdc++)

# Windows 特定定义
# -DUNICODE：告诉 Windows API 使用 Unicode 版本的函数（例如，CreateWindowW 而不是 CreateWindowA）
# -D_UNICODE：告诉 C/C++ 标准库使用 Unicode（例如，wchar_t 类型的字符串，如 L"Hello"）
if (WIN32)
    add_definitions(-DUNICODE -D_UNICODE)
endif ()