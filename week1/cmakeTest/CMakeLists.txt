# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.9)

# 指定为C++11 版本
set(CMAKE_CXX_STANDARD 11)

# 项目信息
project (Demo1)

# 指定生成目标
add_executable(Demo steepestDescent.cpp)