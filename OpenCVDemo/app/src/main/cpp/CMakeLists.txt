cmake_minimum_required(VERSION 3.4.1)

#设置生成的so动态库最后输出的路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

#批量引入,使用 ${source_files}
#file(GLOB source_files "include/nfc/*.c")

add_library(
        native-lib
        SHARED
        native-lib.cpp bitmapUtils.cpp crop.cpp jni_utils.cpp)
#引入opencv 4.1.0
add_library(opencv_java4 SHARED IMPORTED)
set_target_properties(opencv_java4 PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libopencv_java4.so)
include_directories(${CMAKE_SOURCE_DIR}/include/)

find_library(
        log-lib
        log)

#其他so的依赖
#target_link_libraries(serial_port
#        ${log-lib})

target_link_libraries(
        native-lib
        opencv_java4
        jnigraphics
        ${log-lib})