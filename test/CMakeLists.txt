message("TEST source files: ${SOURCES}")
add_executable(tools_test tmain.cpp test_info.cpp ${SOURCES})
target_link_libraries(tools_test PRIVATE gtest argparse_static)
add_test(NAME tools_test COMMAND tools_test)
