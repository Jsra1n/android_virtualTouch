cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
# --- 修改开始 ---
# 不要直接 set(NDK_PATH D:/...)，这样换台电脑就报错了
# 我们改用判断：如果环境变量里有 ANDROID_NDK_HOME，就用环境变量的
if(NOT DEFINED NDK_PATH)
    if(DEFINED ENV{ANDROID_NDK_LATEST_HOME})
        set(NDK_PATH $ENV{ANDROID_NDK_LATEST_HOME})
    elseif(DEFINED ENV{ANDROID_NDK_HOME})
        set(NDK_PATH $ENV{ANDROID_NDK_HOME})
    else()
        # 这里写你本地的路径，作为保底
        set(NDK_PATH "D:/android-ndk-r27c")
    endif()
endif()

set(ANDROID_ABI arm64-v8a)
set(CMAKE_TOOLCHAIN_FILE ${NDK_PATH}/build/cmake/android.toolchain.cmake)
# --- 修改结束 ---

project(android_virtualTouch-a)

include_directories(
        ./include
        ./include/tools
)

file(GLOB_RECURSE src "./src/*.cpp")

add_executable(touch ${src})

find_library(log-lib log PATHS ${ANDROID_NDK}/sources/android)

target_link_libraries(touch ${log-lib})
