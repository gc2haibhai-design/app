/*
 *  @date   : 2020/02/04
 *  @Creator : @Mrkaushikhaxor
 *  Https://t.me/KaushikCracking
 */


#include "Tools.h"
#include "obfuscate.h"

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/md5.h>

#if defined(__aarch64__)
#define process_vm_readv_syscall 270
#define process_vm_writev_syscall 271
#endif

pid_t target_pid = -1;

ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count, const struct iovec *__remote_iov, unsigned long __remote_iov_count, unsigned long __flags, bool iswrite) {
    return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

bool pvm(void *address, void *buffer, size_t size, bool write = false) {
    struct iovec local[1];
    struct iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = address;
    remote[0].iov_len = size;

    if (target_pid == -1) {
        target_pid = getpid();
    }

    ssize_t bytes = process_v(target_pid, local, 1, remote, 1, 0, write);
    return bytes == size;
}

void Tools::Hook(void *target, void *replace, void **backup) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    void *p = (void *) ((uintptr_t) target - ((uintptr_t) target % page_size) - page_size);
    if (mprotect(p, (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0) {
		DobbyHook(target, replace, backup);
    }
}


bool Tools::Read(void *addr, void *buffer, size_t length) {
    return memcpy(buffer, addr, length) != 0;
}

bool Tools::Write(void *addr, void *buffer, size_t length) {
    return memcpy(addr, buffer, length) != 0;
}

bool Tools::ReadAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(buffer, addr, length) != 0;
}

bool Tools::WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}

bool Tools::PVM_ReadAddr(void *addr, void *buffer, size_t length) {
    return pvm(addr, buffer, length, false);
}

bool Tools::PVM_WriteAddr(void *addr, void *buffer, size_t length) {
    return pvm(addr, buffer, length, true);
}

bool Tools::IsPtrValid(void *addr) {
    if (!addr) {
        return false;
    }
    static int fd = -1;
    if (fd == -1) {
        fd = open("/dev/random", O_WRONLY);
    }
    return write(fd, addr, 4) >= 0;
}

uintptr_t Tools::GetBaseAddress(const char *name) {
    uintptr_t base = 0;
    char line[512];

    FILE *f = fopen("/proc/self/maps", "r");

    if (!f) {
        return 0;
    }

    while (fgets(line, sizeof line, f)) {
        uintptr_t tmpBase;
        char tmpName[256];
        if (sscanf(line, "%" PRIXPTR "-%*" PRIXPTR " %*s %*s %*s %*s %s", &tmpBase, tmpName) > 0) {
            if (!strcmp(basename(tmpName), name)) {
                base = tmpBase;
                break;
            }
        }
    }

    fclose(f);
    return base;
}

uintptr_t Tools::GetEndAddress(const char *name) {
    uintptr_t end = 0;
    char line[512];

    FILE *f = fopen("/proc/self/maps", "r");

    if (!f) {
        return 0;
    }

    while (fgets(line, sizeof line, f)) {
        uintptr_t tmpEnd;
        char tmpName[256];
        if (sscanf(line, "%*" PRIXPTR "-%" PRIXPTR " %*s %*s %*s %*s %s", &tmpEnd, tmpName) > 0) {
            if (!strcmp(basename(tmpName), name)) {
                end = tmpEnd;
            } else {
                if (end)
                    break;
            }
        }
    }

    fclose(f);
    return end;
}

#define INRANGE(x, a, b)        (x >= a && x <= b)
#define getBits(x)              (INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte(x)              (getBits(x[0]) << 4 | getBits(x[1]))

uintptr_t Tools::FindPattern(const char *lib, const char *pattern) {
    auto start = GetBaseAddress(lib);
    if (!start)
        return 0;

    auto end = GetEndAddress(lib);
    if (!end)
        return 0;

    auto curPat = reinterpret_cast<const unsigned char *>(pattern);
    uintptr_t firstMatch = 0;
    for (uintptr_t pCur = start; pCur < end; ++pCur) {
        if (*(uint8_t *) curPat == (uint8_t) '\?' || *(uint8_t *) pCur == getByte(curPat)) {
            if (!firstMatch) {
                firstMatch = pCur;
            }
            curPat += (*(uint16_t *) curPat == (uint16_t) '\?\?' || *(uint8_t *) curPat != (uint8_t) '\?') ? 2 : 1;
            if (!*curPat) {
                return firstMatch;
            }
            curPat++;
            if (!*curPat) {
                return firstMatch;
            }
        } else if (firstMatch) {
            pCur = firstMatch;
            curPat = reinterpret_cast<const unsigned char *>(pattern);
            firstMatch = 0;
        }
    }
    return 0;
}

std::string Tools::RandomString(const int len) {
    static const char alphanumerics[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    srand((unsigned) time(0) * getpid());

    std::string tmp;
    tmp.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp += alphanumerics[rand() % (sizeof(alphanumerics) - 1)];
    }
    return tmp;
}


const char* Tools::GetPackageName(JNIEnv* env, jobject context) {
    jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
    jmethodID getPackageNameMethod = env->GetMethodID(contextClass, OBFUSCATE("getPackageName"), OBFUSCATE("()Ljava/lang/String;"));
    jstring packageName = (jstring) env->CallObjectMethod(context, getPackageNameMethod);
    return env->GetStringUTFChars(packageName, 0);
}

const char* Tools::GetVersionName(JNIEnv* env, jobject context) {
    jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
    jmethodID getPackageManagerMethod = env->GetMethodID(contextClass, OBFUSCATE("getPackageManager"), OBFUSCATE("()Landroid/content/pm/PackageManager;"));
    jobject packageManager = env->CallObjectMethod(context, getPackageManagerMethod);

    jmethodID getPackageNameMethod = env->GetMethodID(contextClass, OBFUSCATE("getPackageName"), OBFUSCATE("()Ljava/lang/String;"));
    jstring packageName = (jstring) env->CallObjectMethod(context, getPackageNameMethod);

    jclass pmClass = env->GetObjectClass(packageManager);
    jmethodID getPackageInfoMethod = env->GetMethodID(pmClass, OBFUSCATE("getPackageInfo"),
        OBFUSCATE("(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;"));
    jobject packageInfo = env->CallObjectMethod(packageManager, getPackageInfoMethod, packageName, 0);

    jclass packageInfoClass = env->GetObjectClass(packageInfo);
    jfieldID versionNameField = env->GetFieldID(packageInfoClass, OBFUSCATE("versionName"), OBFUSCATE("Ljava/lang/String;"));
    jstring versionName = (jstring) env->GetObjectField(packageInfo, versionNameField);

    return env->GetStringUTFChars(versionName, 0);
}

const char* Tools::GetApkSize(JNIEnv* env, jobject context) {
    static char sizeStr[128];

    jclass contextClass = env->GetObjectClass(context);
    jmethodID getPackageManager = env->GetMethodID(contextClass, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject packageManager = env->CallObjectMethod(context, getPackageManager);

    jmethodID getPackageName = env->GetMethodID(contextClass, "getPackageName", "()Ljava/lang/String;");
    jstring packageName = (jstring) env->CallObjectMethod(context, getPackageName);

    const char* packageNameStr = env->GetStringUTFChars(packageName, 0);

    jclass pmClass = env->GetObjectClass(packageManager);
    jmethodID getPackageInfo = env->GetMethodID(pmClass, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageInfo = env->CallObjectMethod(packageManager, getPackageInfo, packageName, 0);

    jclass pkgInfoClass = env->GetObjectClass(packageInfo);
    jfieldID appInfoField = env->GetFieldID(pkgInfoClass, "applicationInfo", "Landroid/content/pm/ApplicationInfo;");
    jobject appInfo = env->GetObjectField(packageInfo, appInfoField);

    jclass appInfoClass = env->GetObjectClass(appInfo);
    jfieldID sourceDirField = env->GetFieldID(appInfoClass, "sourceDir", "Ljava/lang/String;");
    jstring sourceDir = (jstring) env->GetObjectField(appInfo, sourceDirField);

    const char* apkPath = env->GetStringUTFChars(sourceDir, 0);

    long apkSize = 0;
    FILE* apkFile = fopen(apkPath, "rb");
    if (apkFile) {
        fseek(apkFile, 0, SEEK_END);
        apkSize = ftell(apkFile);
        fclose(apkFile);
    }

    env->ReleaseStringUTFChars(sourceDir, apkPath);

    // Get OBB size
    long obbSize = 0;
    char obbPath[512];
    snprintf(obbPath, sizeof(obbPath), "/sdcard/Android/obb/%s", packageNameStr);

    DIR* dir = opendir(obbPath);
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                char fullPath[1024];
                snprintf(fullPath, sizeof(fullPath), "%s/%s", obbPath, entry->d_name);
                FILE* obbFile = fopen(fullPath, "rb");
                if (obbFile) {
                    fseek(obbFile, 0, SEEK_END);
                    obbSize += ftell(obbFile);
                    fclose(obbFile);
                }
            }
        }
        closedir(dir);
    }

    env->ReleaseStringUTFChars(packageName, packageNameStr);

    long totalSize = apkSize + obbSize;

    // Convert to human-readable format
    auto formatSize = [](long bytes, char* out, size_t outSize) {
        if (bytes >= (1024L * 1024 * 1024)) {
            snprintf(out, outSize, "%.2f GB", bytes / (1024.0 * 1024 * 1024));
        } else if (bytes >= (1024L * 1024)) {
            snprintf(out, outSize, "%.2f MB", bytes / (1024.0 * 1024));
        } else if (bytes >= 1024L) {
            snprintf(out, outSize, "%.2f KB", bytes / 1024.0);
        } else {
            snprintf(out, outSize, "%ld B", bytes);
        }
    };

    char apkStr[32], obbStr[32], totalStr[32];
    formatSize(apkSize, apkStr, sizeof(apkStr));
    formatSize(obbSize, obbStr, sizeof(obbStr));
    formatSize(totalSize, totalStr, sizeof(totalStr));

    snprintf(sizeStr, sizeof(sizeStr), "APK: %s, OBB: %s, Total: %s", apkStr, obbStr, totalStr);
    return sizeStr;
}

const char *Tools::GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, OBFUSCATE("getContentResolver"), OBFUSCATE("()Landroid/content/ContentResolver;"));
    jclass settingSecureClass = env->FindClass(OBFUSCATE("android/provider/Settings$Secure"));
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, OBFUSCATE("getString"), OBFUSCATE("(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;"));

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(OBFUSCATE("android_id")));
    return env->GetStringUTFChars(str, 0);
}


const char *Tools::GetAndroidVersion(JNIEnv *env) {
	jclass buildClass = env->FindClass("android/os/Build$VERSION");
	jfieldID releaseId = env->GetStaticFieldID(buildClass, "RELEASE", "Ljava/lang/String;");
	auto str = (jstring)env->GetStaticObjectField(buildClass, releaseId);
	return env->GetStringUTFChars(str, 0);
	}

const char *Tools::GetDeviceModel(JNIEnv *env) {
	jclass buildClass = env->FindClass(OBFUSCATE("android/os/Build"));
	jfieldID modelId = env->GetStaticFieldID(buildClass, OBFUSCATE("MODEL"), OBFUSCATE("Ljava/lang/String;"));
	
	auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
	return env->GetStringUTFChars(str, 0);
}

const char *Tools::GetDeviceBrand(JNIEnv *env) {
	jclass buildClass = env->FindClass(OBFUSCATE("android/os/Build"));
	jfieldID modelId = env->GetStaticFieldID(buildClass, OBFUSCATE("BRAND"), OBFUSCATE("Ljava/lang/String;"));
	
	auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
	return env->GetStringUTFChars(str, 0);
}


const char *Tools::GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(OBFUSCATE("java/util/UUID"));

    auto len = strlen(uuid);

    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, OBFUSCATE("nameUUIDFromBytes"), OBFUSCATE("([B)Ljava/util/UUID;"));
    jmethodID toStringMethod = env->GetMethodID(uuidClass, OBFUSCATE("toString"), OBFUSCATE("()Ljava/lang/String;"));

    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}

std::string Tools::CalcMD5(std::string s) {
    std::string result;

    unsigned char hash[MD5_DIGEST_LENGTH];
    char tmp[4];

    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, s.c_str(), s.length());
    MD5_Final(hash, &md5);
    for (unsigned char i : hash) {
        sprintf(tmp, "%02x", i);
        result += tmp;
    }
    return result;
}

std::string Tools::CalcSHA256(std::string s) {
    std::string result;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    char tmp[4];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, s.c_str(), s.length());
    SHA256_Final(hash, &sha256);
    for (unsigned char i : hash) {
        sprintf(tmp, "%02x", i);
        result += tmp;
    }
    return result;
}
