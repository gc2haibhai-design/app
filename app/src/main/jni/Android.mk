LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE            := libdobby
LOCAL_SRC_FILES         := Includes/Dobby/lib/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/Includes/Dobby/
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := libshadowhook
LOCAL_SRC_FILES := Includes/shadowhook/libshadowhook.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)Includes/shadowhook/
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcurl
LOCAL_SRC_FILES := Includes/curl/curl-android-$(TARGET_ARCH_ABI)/lib/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libssl
LOCAL_SRC_FILES := Includes/curl/openssl-android-$(TARGET_ARCH_ABI)/lib/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcrypto
LOCAL_SRC_FILES := Includes/curl/openssl-android-$(TARGET_ARCH_ABI)/lib/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE    := pubgm

LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/Includes/curl/curl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/Includes/curl/openssl-android-$(TARGET_ARCH_ABI)/include


LOCAL_SRC_FILES 		:=  Kaushik.cpp\
        Bypass.cpp \
        Includes/ScreenShot/screenshot.cpp\
        Includes/ScreenShot/lodepng.cpp\
        imgui/imgui.cpp    \
        imgui/imgui_draw.cpp\
        imgui/imgui_demo.cpp \
        imgui/imgui_tables.cpp \
        imgui/imgui_widgets.cpp \
        imgui/backends/imgui_impl_android.cpp \
        imgui/backends/imgui_impl_opengl3.cpp \
        Includes/tools.cpp \
        Includes/android_native_app_glue.c \
        Includes/And64InlineHook.cpp\
        Includes/KittyMemory/KittyMemory.cpp \
        Includes/KittyMemory/MemoryPatch.cpp \
        Includes/KittyMemory/MemoryBackup.cpp \
        Includes/KittyMemory/KittyUtils.cpp \
        Kaushik/SDK/8X_MANISH_Basic.cpp \
        Kaushik/SDK/8X_MANISH_Basic_functions.cpp \
        Kaushik/SDK/8X_MANISH_CoreUObject_functions.cpp \
        Kaushik/SDK/8X_MANISH_Engine_functions.cpp \
        Kaushik/SDK/8X_MANISH_ShadowTrackerExtra_functions.cpp \
        Kaushik/SDK/8X_MANISH_Client_functions.cpp \
        

LOCAL_CPP_FEATURES                      := exceptions
LOCAL_LDLIBS                            := -llog -landroid -lEGL -lGLESv2 -lGLESv3 -lGLESv1_CM -lz
LOCAL_STATIC_LIBRARIES					:= libcurl libssl libcrypto libdobby libshadowhook
include $(BUILD_SHARED_LIBRARY)
