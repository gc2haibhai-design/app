#include <jni.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <sys/stat.h>
#include <dlfcn.h>
#include <curl/curl.h>
#include <ctime>
#include <fcntl.h>
#include <sys/types.h>
#include <vector>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <sys/mman.h>
#ifndef MFD_CLOEXEC
#define MFD_CLOEXEC 0x0001U
#endif

typedef int (*memfd_create_t)(const char *name, unsigned int flags);

memfd_create_t getMemfdCreate() {
    static memfd_create_t fn = nullptr;
    if (!fn) {
        void* libc = dlopen("libc.so", RTLD_NOW);
        if (libc) {
            fn = (memfd_create_t)dlsym(libc, "memfd_create");
        }
    }
    return fn;
}


void logError(const char *errorMessage) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath),
             "/sdcard/Android/data/%s/Logs.txt", Gamepackage);

    int fd = open(filePath, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd != -1) {
        write(fd, errorMessage, strlen(errorMessage));
        write(fd, "\n", 1);
        close(fd);
    }
}

std::string KaushikDec(const unsigned char* data, int len, unsigned char key = 0x5A) {
    std::string result;
    for (int i = 0; i < len; ++i) {
        result += data[i] ^ key;
    }
    return result;
}

struct MMemoryStruct {
    char *memory = nullptr;
    size_t size = 0;
};

static size_t WWriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    MMemoryStruct *mem = (MMemoryStruct *)userp;

    char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        exit(0);
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = '\0';
    return realsize;
}


static int ProgressCallback(
    void*,
    curl_off_t dltotal,
    curl_off_t dlnow,
    curl_off_t,
    curl_off_t
) {
    if (dltotal > 0) {
        KaushikSettings::DownloadProgress =
            (float)dlnow * 100.0f / (float)dltotal;
    }
    return 0;
}

bool DownloadPayload(const char* url, MemoryStruct& data, const char* pkg) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WWriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&data);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, ProgressCallback);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return (res == CURLE_OK);
}

int LoadSoFromMemory(const char* Gamepackage, const char* fileName, const char* memory, size_t size) {
    const char ELF_MAGIC[] = {0x7F, 'E', 'L', 'F'};
    const char* elfStart = nullptr;

    for (size_t i = 0; i < size - 4; ++i) {
        if (memcmp(memory + i, ELF_MAGIC, 4) == 0) {
            elfStart = memory + i;
            break;
        }
    }

    if (!elfStart) return 1;

    memfd_create_t memfd_fn = getMemfdCreate();
    int fd = -1;
    std::string path;

    if (memfd_fn) {
        fd = memfd_fn(fileName, MFD_CLOEXEC);
        if (fd >= 0) {
            ssize_t written = write(fd, elfStart, size - (elfStart - memory));
            if (written >= 0 && (size_t)written == size - (elfStart - memory)) {
                lseek(fd, 0, SEEK_SET);
                char temp[64];
                snprintf(temp, sizeof(temp), "/proc/self/fd/%d", fd);
                path = temp;

                void* handle = dlopen(path.c_str(), RTLD_NOW);
                if (handle) {
                    close(fd);
                    return 0;
                }
            }
            close(fd);
        }
    }

    // fallback to file
    std::string fallbackDir;
    if (access("/data/local/tmp", W_OK) == 0) {
        fallbackDir = "/data/local/tmp/";
    } else {
        fallbackDir = std::string("/data/data/") + Gamepackage + "/files/";
        mkdir(fallbackDir.c_str(), 0700);
    }

    path = fallbackDir + fileName;
    std::ofstream tempFile(path, std::ios::binary);
    if (!tempFile.is_open()) return 5;

    tempFile.write(elfStart, size - (elfStart - memory));
    tempFile.close();

    chmod(path.c_str(), 0700);

    void* handle = dlopen(path.c_str(), RTLD_NOW);
    int result = 0;
    if (!handle) {
        result = 4;
    }

    remove(path.c_str());
    return result;
}
// --- Encrypted data ---

const unsigned char kaushik[] = {0x74, 0x2E, 0x3F, 0x37, 0x2A, 0x2C, 0x35, 0x33, 0x39, 0x3F, 0x74, 0x29, 0x35};
const int libKaushik = sizeof(kaushik);

void* Load_Lib(void*)
{
    if (!KaushikSettings::DownloadLib)
        return nullptr;

    KaushikSettings::LibDownloading = true;
    KaushikSettings::LibLoaded = false;
    KaushikSettings::DownloadProgress = 0.0f;

    MemoryStruct data{};
    std::string url = KaushikSettings::LibUrl;
    std::string libName = KaushikDec(kaushik, libKaushik);

    if (DownloadPayload(url.c_str(), data, Gamepackage))
    {
        int res = LoadSoFromMemory(
            Gamepackage,
            libName.c_str(),
            data.memory,
            data.size
        );

        if (res == 0)
            KaushikSettings::LibLoaded = true;
    }

    KaushikSettings::LibDownloading = false;
    KaushikSettings::LibThreadStarted = false; // 🔓 allow retry if needed

    if (data.memory)
        free(data.memory);

    return nullptr;
}