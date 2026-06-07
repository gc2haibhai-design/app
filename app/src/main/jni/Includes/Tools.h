/*
 *  @date   : 2020/02/04
 *  @Creator : @Mrkaushikhaxor
 *  Https://t.me/KaushikCracking
 */

#include "dobby.h"
#include "Logger.h"
namespace Tools
{
    void Hook(void *target, void *replace, void **backup);
    bool Read(void *addr, void *buffer, size_t length);
    bool Write(void *addr, void *buffer, size_t length);
    bool ReadAddr(void *addr, void *buffer, size_t length);
    bool WriteAddr(void *addr, void *buffer, size_t length);

    bool PVM_ReadAddr(void *addr, void *buffer, size_t length);
    bool PVM_WriteAddr(void *addr, void *buffer, size_t length);

    bool IsPtrValid(void *addr);

    uintptr_t GetBaseAddress(const char *name);
    uintptr_t GetEndAddress(const char *name);
    uintptr_t FindPattern(const char *lib, const char* pattern);

    std::string RandomString(const int len);
    const char* GetAndroidID(JNIEnv* env, jobject context);

    const char* GetPackageName(JNIEnv* env, jobject context);
    const char* GetVersionName(JNIEnv* env, jobject context);
    const char* GetApkSize(JNIEnv* env, jobject context);
    const char *GetAndroidID(JNIEnv *env, jobject context);
	const char *GetAndroidVersion(JNIEnv *env);
	const char *GetDeviceModel(JNIEnv *env);
	const char *GetDeviceBrand(JNIEnv *env);
	const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid);
	
    std::string CalcMD5(std::string s);
    std::string CalcSHA256(std::string s);
}
