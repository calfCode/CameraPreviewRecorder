#include <jni.h>
#include <string>
#include "CommonTools.h"

extern "C" {
#include "libavutil/opt.h"
#include "libavutil/mathematics.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/imgutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/timestamp.h"
#include "libavcodec/avcodec.h"
//#include "libavfilter/avfiltergraph.h"
//#include "libavfilter/avcodec.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
}

#define LOG_TAG "BRUCE"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_camerapreviewrecorder_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    av_register_all();
    avcodec_register_all();
//    const AVCodec* avCodec  = avcodec_find_encoder(AV_CODEC_ID_H264);
//    if (avCodec!=NULL){
//        if (avCodec->type == AVMEDIA_TYPE_VIDEO){
//            LOGI("avCodec->name=%s",avCodec->name);
//        }
//        LOGI("Can  find encoder");
//    } else{
//
//        LOGI("Can not find encoder");
//        avCodec  = avcodec_find_decoder(AV_CODEC_ID_H264);
//        if (avCodec== NULL){
//            LOGI("Can not find decoder");
//        }else{
//            LOGI("Can  find decoder");
//        }
//    }
//    AVCodec* avCodec = av_codec_next(NULL);
//    while (avCodec!=NULL){
//        if (avCodec->type == AVMEDIA_TYPE_VIDEO){
//            LOGI("avCodec->name=%s",avCodec->name);
//        }
//
//        avCodec = av_codec_next(avCodec);
//    }
//

    return env->NewStringUTF(hello.c_str());
}