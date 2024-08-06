# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("camerapreviewrecorder")

#set(VERSION 3.8.8)
#set(TYPE STATIC)
#set(LIB_EXT so)
#set(POSTPROC OFF)



#set(VERSION 2.7.7)
#set(TYPE STATIC)
#set(LIB_EXT a)
#set(POSTPROC OFF)

set(VERSION 3.4.6)
set(TYPE STATIC)
set(LIB_EXT a)
set(POSTPROC OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/${VERSION}/${ANDROID_ABI}/include)
set(ffmpeg_lib_path ${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/${VERSION}/${ANDROID_ABI}/lib)

add_library( avcodec
        ${TYPE}
        IMPORTED )
add_library( avfilter
        ${TYPE}
        IMPORTED )
add_library( avformat
        ${TYPE}
        IMPORTED )
add_library( avutil
        ${TYPE}
        IMPORTED )
add_library( swresample
        ${TYPE}
        IMPORTED )
add_library( swscale
        ${TYPE}
        IMPORTED )



set_target_properties( avcodec
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavcodec.${LIB_EXT} )
set_target_properties( avfilter
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavfilter.${LIB_EXT}  )
set_target_properties( avformat
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavformat.${LIB_EXT}  )
set_target_properties( avutil
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libavutil.${LIB_EXT}  )
set_target_properties( swresample
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libswresample.${LIB_EXT}  )
set_target_properties( swscale
        PROPERTIES IMPORTED_LOCATION
        ${ffmpeg_lib_path}/libswscale.${LIB_EXT}  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/fdk-aac/${ANDROID_ABI}/include)

set(fdkaac_lib_path ${CMAKE_CURRENT_SOURCE_DIR}/lib/fdk-aac/${ANDROID_ABI}/lib)
add_library( fdk-aac
        STATIC
        IMPORTED )

set_target_properties( fdk-aac
        PROPERTIES IMPORTED_LOCATION
        ${fdkaac_lib_path}/libfdk-aac.a )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/x264/${ANDROID_ABI}/include)

set(x264_lib_path ${CMAKE_CURRENT_SOURCE_DIR}/lib/x264/${ANDROID_ABI}/lib)
add_library( x264
        STATIC
        IMPORTED )

set_target_properties( x264
        PROPERTIES IMPORTED_LOCATION
        ${x264_lib_path}/libx264.a )


include_directories(./)
include_directories(camera_preview)
include_directories(libcommon)
include_directories(libcommon/egl_core)
include_directories(libcommon/message_queue)
include_directories(libcommon/opensl_media)
include_directories(libcommon/opengl_media)
include_directories(libcommon/opengl_media/render)
include_directories(libcommon/opengl_media/texture)
include_directories(libcommon/opengl_media/texture_copier)


add_subdirectory(camera_preview)
add_subdirectory(libcommon)
add_subdirectory(video_encoder)


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        RecordingPreviewScheduler.cpp
        native-lib.cpp)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        avcodec
        avfilter
        avformat
        avutil
        swresample
        swscale
        GLESv2
        EGL
        z
        OpenSLES
        fdk-aac
        x264
        preview-lib
        common-lib
        encoder-lib
        android
        log)