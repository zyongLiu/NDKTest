cmake_minimum_required(VERSION 3.10.2)

project("opencvdemo2")

add_library( # Sets the name of the library.
             native-lib
             SHARED
             native-lib.cpp )

#file(GLOB opencv_java4_libs "${CMAKE_SOURCE_DIR}/staticlibs/${ANDROID_ABI}/libopencv_*.a")


#引入opencv 4.5.2
set(OPENCV_LIBS calib3d core dnn features2d flann gapi highgui imgcodecs imgproc ml objdetect photo stitching video videoio)
FOREACH(OPENCV_LIB ${OPENCV_LIBS})
    add_library(${OPENCV_LIB} STATIC IMPORTED)
    set_target_properties(${OPENCV_LIB} PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/opencv/staticlibs/${ANDROID_ABI}/libopencv_${OPENCV_LIB}.a)
ENDFOREACH(OPENCV_LIB)

set(3EDPARTY_LIBS ade
        cpufeatures
        IlmImf
        ittnotify
        libjpeg-turbo
        libopenjp2
        libpng
        libprotobuf
        libtiff
        libwebp
        quirc
        tbb
        tegra_hal)
FOREACH(3EDPARTY_LIB ${3EDPARTY_LIBS})
    add_library(${3EDPARTY_LIB} STATIC IMPORTED)
    set_target_properties(${3EDPARTY_LIB} PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/opencv/3rdparty/libs/${ANDROID_ABI}/lib${3EDPARTY_LIB}.a)
ENDFOREACH(3EDPARTY_LIB)


#  表示以引入静态库的方式引入StaticTest
#add_library(opencv_java4 STATIC IMPORTED)
#  设置目标导入路径，这里是一行
#set_target_properties(opencv_java4 PROPERTIES IMPORTED_LOCATION ${opencv_java4_libs})
include_directories(${CMAKE_SOURCE_DIR}/include/)



find_library( # Sets the name of the path variable.
              log-lib
              log )

target_link_libraries( # Specifies the target library.
        native-lib

        dnn
        features2d
        flann
        gapi
        highgui
        imgcodecs
        imgproc
        ml
        objdetect
        photo
        stitching
        video
        videoio
        core
        calib3d

        ade
        cpufeatures
        IlmImf
        ittnotify
        libjpeg-turbo
        libopenjp2
        libpng
        libprotobuf
        libtiff
        libwebp
        quirc
        tbb
        tegra_hal

        ${log-lib} )