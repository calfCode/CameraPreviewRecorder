#include "RecordingPreviewScheduler.h";
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "./camera_preview/mv_recording_preview_controller.h"
#include <sys/types.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

#define LOG_TAG "RecordingPreviewScheduler"

static MVRecordingPreviewController *previewController = 0;

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_startEncoding
(JNIEnv * env, jobject obj, jint width, jint height, jint videoBitRate, jint frameRate, jboolean useHardWareEncoding, jstring h264FilePathParam) {
	if(NULL != previewController) {
		const char* h264FilePath = env->GetStringUTFChars(h264FilePathParam, NULL);
		previewController->startEncoding(h264FilePath, width, height, videoBitRate, frameRate, useHardWareEncoding);
		env->ReleaseStringUTFChars(h264FilePathParam, h264FilePath);
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_stopEncoding
(JNIEnv * env, jobject obj) {
	if(NULL != previewController) {
		previewController->stopEncoding();
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_switchCameraFacing
(JNIEnv * env, jobject obj) {
	if(NULL != previewController) {
		previewController->switchCameraFacing();
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_prepareEGLContext
(JNIEnv * env, jobject obj, jobject surface, jint screenWidth, jint screenHeight, jint cameraFacingId) {
	previewController = new MVRecordingPreviewController();
	JavaVM *g_jvm = NULL;
	env->GetJavaVM(&g_jvm);
	jobject g_obj = env->NewGlobalRef(obj);
	if (surface != 0 && NULL != previewController) {
		ANativeWindow* window = ANativeWindow_fromSurface(env, surface);
		if (window != NULL) {
			previewController->prepareEGLContext(window, g_jvm, g_obj, screenWidth, screenHeight, cameraFacingId);
		}
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_createWindowSurface
(JNIEnv * env, jobject obj, jobject surface) {
	if (surface != 0 && NULL != previewController) {
		ANativeWindow* window = ANativeWindow_fromSurface(env, surface);
		if (window != NULL) {
			previewController->createWindowSurface(window);
		}
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_resetRenderSize
(JNIEnv * env, jobject obj, jint screenWidth, jint screenHeight) {
	if(NULL != previewController) {
		previewController->resetRenderSize(screenWidth, screenHeight);
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_destroyWindowSurface
(JNIEnv * env, jobject obj) {
	if(NULL != previewController) {
		previewController->destroyWindowSurface();
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_destroyEGLContext
(JNIEnv * env, jobject obj) {
	if(NULL != previewController) {
		previewController->destroyEGLContext();
		delete previewController;
		previewController = NULL;
	}
}

extern "C" JNIEXPORT void JNICALL Java_com_example_camerapreviewrecorder_camera_preview_RecordingPreviewScheduler_notifyFrameAvailable
(JNIEnv * env, jobject obj) {
	if(NULL != previewController) {
		previewController->notifyFrameAvailable();
	}
}

