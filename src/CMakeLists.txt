# 自定义函数遍历目录
function(collect_sources DIR)
    file(GLOB_RECURSE NEW_SOURCES "${DIR}/*.cpp" "${DIR}/*.c")
    list(APPEND SOURCES ${NEW_SOURCES})
    set(SOURCES ${SOURCES} CACHE INTERNAL "Collected sources" ) # 设置为全局变量（不是很合理）
endfunction()

# 调用函数遍历当前目录
# collect_sources(${CMAKE_CURRENT_SOURCE_DIR}) # 使用函数方法，变量提升有问题

#file(GLOB_RECURSE NEW_SOURCES "${DIR}/*.cpp" "${DIR}/*.c")
file(GLOB NEW_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*/*.c")

# set(NEW_SOURCES PARENT_SCOPE)
set(NEW_SOURCES ${NEW_SOURCES} PARENT_SCOPE)

# 打印收集到的源文件
message("Collected source files: ${NEW_SOURCES}")
