#include <jni.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <android/log.h>

#define LOG_TAG "MyApplication"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT jint JNICALL
Java_com_example_myapplication_MainActivity_openDevice(JNIEnv* env, jobject /* this */) {
    int fd = open("/dev/simple_driver", O_RDWR);
    if (fd < 0) {
        LOGE("Failed to open device: %s", strerror(errno));
        return -errno;
    }
    return fd;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_myapplication_MainActivity_closeDevice(JNIEnv* env, jobject /* this */, jint fd) {
    if (close(fd) < 0) {
        LOGE("Failed to close device: %s", strerror(errno));
        return -errno;
    }
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_myapplication_MainActivity_writeToDevice(JNIEnv* env, jobject /* this */, jint fd, jstring data) {
    const char *nativeString = env->GetStringUTFChars(data, 0);
    ssize_t bytes_written = write(fd, nativeString, strlen(nativeString));
    env->ReleaseStringUTFChars(data, nativeString);

    if (bytes_written < 0) {
        LOGE("Failed to write to device: %s", strerror(errno));
        return -errno;
    }

    LOGI("Wrote %zd bytes to device", bytes_written);
    return bytes_written;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_readFromDevice(JNIEnv* env, jobject /* this */, jint fd, jint length) {
    char buffer[1024] = {0};
    ssize_t bytes_read = read(fd, buffer, length);

    if (bytes_read < 0) {
        LOGE("Failed to read from device: %s", strerror(errno));
        return env->NewStringUTF("");
    }

    LOGI("Read %zd bytes from device", bytes_read);
    return env->NewStringUTF(buffer);
}
