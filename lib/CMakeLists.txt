# 自定义函数递归遍历目录
function(add_subdirectories_recursive DIR)
    # 获取当前目录下的所有子目录
    file(GLOB CHILD_DIRECTORIES LIST_DIRECTORIES true "${DIR}/*")
    foreach(CHILD_DIR ${CHILD_DIRECTORIES})
        # 检查子目录中是否包含 CMakeLists.txt 文件
        if(IS_DIRECTORY ${CHILD_DIR} AND EXISTS "${CHILD_DIR}/CMakeLists.txt")
            # 添加子目录
            add_subdirectory(${CHILD_DIR})
            # 递归遍历子目录
            add_subdirectories_recursive(${CHILD_DIR})
        endif()
    endforeach()
endfunction()

# 调用函数遍历当前目录
add_subdirectories_recursive(${CMAKE_CURRENT_SOURCE_DIR})