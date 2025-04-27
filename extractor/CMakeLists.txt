cmake_minimum_required(VERSION 3.13)
project(CaseVisitor)

# 自动找 llvm-config
find_program(LLVM_CONFIG_EXECUTABLE NAMES llvm-config REQUIRED)

# 用llvm-config拿到编译参数
execute_process(COMMAND ${LLVM_CONFIG_EXECUTABLE} --cxxflags
                OUTPUT_VARIABLE LLVM_CXXFLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${LLVM_CONFIG_EXECUTABLE} --ldflags
                OUTPUT_VARIABLE LLVM_LDFLAGS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND ${LLVM_CONFIG_EXECUTABLE} --libs --system-libs
                OUTPUT_VARIABLE LLVM_LIBS
                OUTPUT_STRIP_TRAILING_WHITESPACE)

# 拿到LLVM版本（可选，检查）
execute_process(COMMAND ${LLVM_CONFIG_EXECUTABLE} --version
                OUTPUT_VARIABLE LLVM_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Using llvm-config: ${LLVM_CONFIG_EXECUTABLE}")
message(STATUS "LLVM version: ${LLVM_VERSION}")

# 添加编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXXFLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LDFLAGS}")

# 添加头文件
include_directories(
    ${CMAKE_SOURCE_DIR}
)

# 最重要的！加上Tooling, AST等模块
set(LLVM_EXTRA_LIBS clang-cpp)

add_executable(CaseVisitor CaseVisitor.cpp)

# 链接
target_link_libraries(CaseVisitor ${LLVM_EXTRA_LIBS} ${LLVM_LIBS})

