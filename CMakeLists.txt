cmake_minimum_required(VERSION 3.10)

# 1. 项目名称
project(CH347_Control C)

# 2. 设置 C 标准 (通常 C99 或 C11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 3. 定义路径变量 (基于你的目录结构)
# 使用 ${CMAKE_SOURCE_DIR} 确保路径是相对于工程根目录的绝对路径
set(INC_DIR       "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR       "${CMAKE_SOURCE_DIR}/lib")
set(SRC_DIR       "${CMAKE_SOURCE_DIR}/src")
set(BIN_DIR       "${CMAKE_SOURCE_DIR}/bin")
set(THIRD_PARTY   "${CMAKE_SOURCE_DIR}/third_party/ch347")

# 4. 包含头文件目录
# 这里添加了 include 和 third_party/mylib 两个位置
include_directories(
    "${INC_DIR}"
    "${THIRD_PARTY}"
)

# 5. 指定源文件
# 这里直接列出你的两个源文件
set(SOURCES 
    "${SRC_DIR}/ch347_demo.c"
)

# 6. 生成可执行文件
add_executable(CH347_Demo ${SOURCES})

# 7. 链接静态库 (.lib)
# 注意：Windows下路径不区分大小写，但最好保持一致
# 假设你的 lib 文件直接位于 lib/CH347DLL.lib
target_link_libraries(CH347_Demo PRIVATE 
    "${LIB_DIR}/CH347DLL.lib"
)
