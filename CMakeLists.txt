# CMakeList.txt: cmd_tools 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.0...3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cmd_tools")

# 添加所有的第三方依赖库
add_subdirectory(lib)

# 添加源码目录到项目
add_subdirectory(src)

# 添加头文件信息，包含到源码级别即可
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

list(APPEND SOURCES ${NEW_SOURCES})
message("All source files: ${NEW_SOURCES}")
message("All source files: ${SOURCES}")
# 将源代码添加到此项目的可执行文件。
add_executable (cmd_tools "cmd_tools.cpp" ${SOURCES})
if (WIN32)
    message("Configuring for Windows")
    target_link_libraries(cmd_tools iphlpapi ws2_32)
    target_compile_definitions(cmd_tools PRIVATE _CRT_SECURE_NO_WARNINGS)
elseif (UNIX)
    message("Configuring for Unix-like system")
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cmd_tools PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
