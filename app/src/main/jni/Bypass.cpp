#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <dlfcn.h>
#include <libgen.h>
#include <unwind.h>
#include <pthread.h>
#include <sstream>
#include <locale>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include "Includes/oxorany.cpp"
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "Includes/KittyMemory/MemoryPatch.h"
#include "Includes/Macros.h"
#include "Includes/Tools.h" 

#define targetLibName OBFUSCATE("libanogs.so")
#define targetLibName OBFUSCATE("libhdmpve.so")
#define targetLibName OBFUSCATE("libanort.so")
#define targetLibName OBFUSCATE("libTBlueData.so")
#define targetLibName OBFUSCATE("libCrashKit.so")
#define targetLibName OBFUSCATE("libRoosterNN.so")
auto ret = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
char *dword_57F060;
char *qword_1C9D48;
#define HIBYTE
#define ARM64_SYSREG
#define _ReadStatusReg
using namespace std;
#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t
uintptr_t ANOGSo;
#define SLEEP_TIME 1000LL / 60LL
#define targetLibName OBFUSCATE("libUE4.so")
#define targetLibName OBFUSCATE("libanogs.so")

#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t

#define _QWORD uint64_t
#define _OWORD uint64_t


#define _BOOL8 uint64_t
#define XOR_KEY 0xA5A5A5A5

static inline uintptr_t xor_runtime(uintptr_t val)
{
    volatile uintptr_t key = XOR_KEY;
    return val ^ key;
}
uintptr_t libANOSize = 0;
uintptr_t libANOAlloc = 0;
uintptr_t libANOBase = 0;
uintptr_t libUE4Size = 0;
uintptr_t libUE4Alloc = 0;
uintptr_t libUE4Base = 0;
uintptr_t libanogsBase = 0;
uintptr_t libanogsSize = 0;
uintptr_t libanogsAlloc = 0;
DWORD NewBase = 0;
DWORD TBlueBase = 0;
DWORD AntBase = 0;
DWORD BufferBase = 0;
DWORD HdmpveBase = 0;
DWORD roosterBase = 0;
DWORD roosterSize = 0;
DWORD roosterAlloc = 0;

DWORD EGLBase = 0;
DWORD EGLSize = 0;
DWORD EGLAlloc = 0;

#include <unordered_map>
#include <string>
DWORD libcSize = 0;
DWORD libcAlloc = 0;

uintptr_t getLibraryBase(void* addr)
{
    Dl_info info;
    if (dladdr(addr, &info) && info.dli_fbase)
        return (uintptr_t)info.dli_fbase;
    return 0;
}
#include <stddef.h>
#include <stdio.h>


#include <sys/prctl.h>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/prctl.h>
#include <signal.h>
#include <stdlib.h>

std::atomic<bool> triggered{false};

std::atomic<bool> safe_exit_started{false};



void DeepSafeExit()
{
    prctl(PR_SET_PDEATHSIG, SIGKILL); // अगर parent7 मरे तो kill (safety)
    sleep(1);                         // गेम को time दो stable दिखने का
    syscall(SYS_exit, 0);             // direct syscall-based exit
}

//------------------ end xor string obfuscation ----------------//
// Get Library Base Address Properly
size_t getLibrarySize(const char *libraryName)
{
    FILE *mapsFile = fopen("/proc/self/maps", "r");
    if (mapsFile == nullptr)
    {
        return 0;
    }

    char line[256];
    size_t size = 0;
    uintptr_t startAddr = 0, endAddr = 0;
    while (fgets(line, sizeof(line), mapsFile))
    {
        if (strstr(line, libraryName))
        {
            sscanf(line, "%lx-%lx", &startAddr, &endAddr);
            size = endAddr - startAddr;
            break;
        }
    }

    fclose(mapsFile);
    return size;
}

void chfiles(){

    char mode[] = "0555";
    char *path = "/data/data/com.pubg.imobile/files/ano_tmp";
    char *path2 = "/data/data/com.pubg.imobile/files";
    int m = strtol(mode,0,8);
    while(true){
        chmod(path,m);
        chmod(path2,m);
        sleep(1);
    }

}
void chRestore(){
    char mode[] = "0777";
    char *path = "/data/data/com.pubg.imobile/files/ano_tmp";
    char *path2 = "/data/data/com.pubg.imobile/files";
    int m = strtol(mode,0,8);
    chmod(path,m);
    chmod(path2,m);
    LOGI(OBFUSCATE("permissions restored"));
}

#include <unordered_map>
size_t ApplySkins(const char *s) {
     static const std::unordered_map<std::string, std::string> replacements = {
	
         {"403003", "1404048"},
         {"404026", "1404050"},
         
         {"1405385", "1407625"}, // Sandsylph
        {"1405269", "1407625"}, // Winter Highness Set
        {"404151", "1407625"},  // BAPE Sta Mid
        {"1405884", "1406327"}, // BAPE Sta Mid
        {"1405113", "1407387"}, // The Reaper's End Set
        {"1405548", "1407366"}, // Wind Spirit Jia'er
        {"403006", "1405207"},  // Ryan Set
        {"403020", "1405628"},  // Golden Pharaoh Divine Set
        {"403032", "1407470"},  // Carefree Exiled Immortal
        {"403224", "1406891"},  // Soul-Eater Underworld King
        {"403160", "1406386"},  // Zero Combat Suit
        {"403002", "1407387"},  // Phantom Night Shinigami Set
        {"403198", "1400687"},  // Halloween Mummy 
        {"403124", "1406387"},  // Asuka
	
         /*
         // Bags 
         {"501001","1501001637"}//erflare Backpack (Lv. 1)
        ,{"501002", "1501002637"}//Backpack (Lv. 2)
        ,{"501003", "1501003637"}//Backpack (Lv. 3)
        */
        
          // Backpacks
        {"501001", "1501001220"},  // Backpack (Lv. 1)
        {"501002", "1501002220"},  // Backpack (Lv. 2)
        {"501003", "1501003220"},  // Backpack (Lv. 3)
		
        
         //------ HELMET ------ //
         
        {"502101","1502003014"},
        {"502002","1502003014"},
        {"502003","1502003014"}

       };
    auto it = replacements.find(s);
    if (it != replacements.end()) {
    strcpy((char *)s, it->second.c_str());
    }
    return strlen(s);
}

template<typename T>
bool WriteMemoryy(uintptr_t address, T value) {
    T* ptr = (T*)address;
    *ptr = value;
    return true;
}

uintptr_t get_module_base(const char* module_name) {
    FILE* fp = fopen("/proc/self/maps", "r");
    if (!fp) return 0;

    uintptr_t base = 0;
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, module_name)) {
            char* dash = strchr(line, '-');
            if (!dash) continue;
            *dash = 0;
            base = strtoull(line, NULL, 16);
            break;
        }
    }
    fclose(fp);
    return base;
}

// ---------- Generic Macro ----------

#define WRITE_MEMORY(lib, offset, value) do { \
    uintptr_t base = get_module_base(lib); \
    if (base) { \
        WriteMemoryy(base + offset, value); \
    } else { \
        LOGI("Module %s base not found!\n", lib); \
    } \
} while(0)

// ---------- Type-specific Macros ----------

    

int Write_DWORD(long int addr, uint32_t value) {
    Tools::WriteAddr((void*)(addr), (void*)&value, sizeof(uint32_t));
    return 0;
}

int Write_QWORD(long int addr, uint64_t value) {
    Tools::WriteAddr((void*)(addr), (void*)&value, sizeof(uint64_t));
    return 0;
}

int Write_FLOAT(long int addr, float value) {
    Tools::WriteAddr((void*)(addr), (void*)&value, sizeof(float));
    return 0;
}


int Write_DOUBLE(long int addr, double value) {
    Tools::WriteAddr((void*)(addr), (void*)&value, sizeof(double));
    return 0;
}

int Write_BYTE(long int addr, uint8_t value) {
    Tools::WriteAddr((void*)(addr), (void*)&value, sizeof(uint8_t));
    return 0;
}
int Write_WORD(long int addr, uint16_t value) {
    Tools::WriteAddr((void*)(addr), (void*)&value, sizeof(uint16_t));
    return 0;
}





void* osub_memcpy = nullptr;
void* hsub_memcpy(void* dest, const void* src, size_t size) {
    static void* (*real_memcpy)(void*, const void*, size_t) = nullptr;
    if (!real_memcpy)
        real_memcpy = (void* (*)(void*, const void*, size_t))dlsym(RTLD_NEXT, "memcpy");
    uintptr_t addr = (uintptr_t)src;
    if (libanogsBase && addr >= libanogsBase && addr < libanogsBase + libanogsSize) {
        uintptr_t offset = addr - libanogsBase;
        if (libanogsAlloc && offset + size <= libanogsSize) {
            return real_memcpy(dest, (const void*)(libanogsAlloc + offset), size);
        }
    }
    if (libUE4Base && addr >= libUE4Base && addr < libUE4Base + libUE4Size) {
        uintptr_t offset = addr - libUE4Base;
        if (libUE4Alloc && offset + size <= libUE4Size) {
            return real_memcpy(dest, (const void*)(libUE4Alloc + offset), size);
        }
    }
    return real_memcpy(dest, src, size);
}


//ADD HOOK DEFINE HERE 
__int64 __fastcall (*VtableCheck)(__int64 a1, unsigned __int64 a2, void *a3, double a4);
__int64 __fastcall VtableHub(__int64 a1, unsigned __int64 a2, void *a3, double a4)
{
    int Case = (int)(intptr_t)a2;
    if (Case == 924 || Case == 867 || Case == 899 || Case == 914) return 0;
    return VtableCheck(a1, a2, a3, a4);
}

__int64 __fastcall sub_228168(__int64 a1, unsigned __int8 *a2, unsigned int a3)
{
    __int64 result = 0xFFFFFFFFLL;
    void *v7;
    __int64 v8;
    __int64 v9;
    _QWORD *v10;

    if (a2 && a3 - 1001 >= 0xFFFFFC18)
    {
        if (*(_QWORD *)(a1 + 16) > 0x400uLL)
            return 0xFFFFFFFFLL;

        if (*a2 > 0x10u)
        {
            (a1 + 1064);
            v7 = *(void **)(a1 + 26);
            *(_WORD *)(a1 + 24) = a3;
            memcpy(v7, a2, a3);
            (a1 + 1064);
        }

        if (v8)
        {
            v9 = v8;
            (a1 + 1064);

            v10 = *(_QWORD **)(a1 + 8);
            if (v10 == *(_QWORD **)(a1 + 16))
            {
                (a1);
                v10 = *(_QWORD **)(a1 + 8);
            }

            if (v10)
            {
                *v10 = v9;
                *(_QWORD *)(a1 + 8) += 8LL;
            }

            (a1 + 1064);
            return 0LL;
        }
        else
        {
            return 0xFFFFFFFFLL;
        }
    }

    return result;
}
__int64 ThunderOp()
{
 return 0LL;
}

int sub_275A0C(const char *a1, int a2, int a3)
{
    if (a1 && ( strstr(a1, "suspicious"))) {
        return 0;
    }
    return sub_275A0C(a1, a2, a3);
}
__int64 (*osub_46EFD0)(_DWORD *a1, unsigned char *a2, int a3);
__int64 __fastcall hsub_46EFD0(_DWORD *a1, unsigned char *a2, int a3)
{
    bool validZip =
        a2 &&
        a2[0] == 0x50 &&
        a2[1] == 0x4B &&
        a2[2] == 0x03 &&
        a2[3] == 0x04;

    if (!validZip) {
        return 0LL;
    }

    return osub_46EFD0(a1, a2, a3);
}

int (*orig_gettimeofday)(struct timeval *tv, struct timezone *tz);

int hook_gettimeofday(struct timeval *tv, struct timezone *tz) {
    int ret = orig_gettimeofday ? orig_gettimeofday(tv, tz) : 0;
    if (!tv) return ret;

    static time_t s = 0; static suseconds_t u = 0;
    if (!s) { s = tv->tv_sec; u = tv->tv_usec; }

    tv->tv_sec = s;
    u += rand() % 5;
    if(u > 999999) { u -= 1000000; s++; }
    tv->tv_usec = u;

    return ret;
}

__int64 BT_DMG()
{
  return 0LL;
}


void *dack_thread(void *) {
auto ANOGS = Tools::GetBaseAddress("libanogs.so");
    while (!ANOGS) {
        ANOGS = Tools::GetBaseAddress("libanogs.so");
        sleep(1);
    }
    do {
        sleep(1);
    } while (!isLibraryLoaded("libanogs.so"));
    static const char hack_tag[] = "UE4_HOOK_ACTIVE";
    __android_log_print(ANDROID_LOG_INFO, "HOOK", "%s", hack_tag);
    HOOK_LIB("libanogs.so", "0x51FA80", hook_gettimeofday, orig_gettimeofday);//->> GettimOfDay
HOOK_LIB("libanogs.so","0x51F980", hsub_memcpy, osub_memcpy);
PATCH_LIB("libanogs.so","0x3A564C","C0 03 5F D6");//VIOLATION
PATCH_LIB("libanogs.so","0x330494","00 00 80 D2 C0 03 5F D6");
HOOK_LIB("libanogs.so","0x3A564C",VtableHub,VtableCheck);
HOOK_LIB("libanogs.so","0x46EFD0",hsub_46EFD0,osub_46EFD0);// Memory tree
PATCH_LIB("libUE4.so","0x6152F70","00 00 80 D2 C0 03 5F D6");
MemoryPatch::createWithHex("libUE4.so",0x67866E4,"1F 20 03 D5").Modify();
MemoryPatch::createWithHex("libUE4.so",0x5952F70,"00 00 80 D2 C0 03 5F D6").Modify();
PATCH_LIB("libanogs.so","0x3A564C","C0 03 5F D6");//VIOLATION
PATCH_LIB("libanogs.so","0x2234B0","00 00 80 D2 C0 03 5F D6");
PATCH_LIB("libanogs.so","0x268174","C0 03 5F D6");//3RD-PARTY
PATCH_LIB("libanogs.so","0x3A4CCC","00 00 80 D2 C0 03 5F D6");
MemoryPatch::createWithHex("libanogs.so",0x4EDC4C, "00 00 80 52 C0 03 5F D6").Modify();
MemoryPatch::createWithHex("libanogs.so",0x4ED954, "00 00 80 52 C0 03 5F D6").Modify();
PATCH_LIB("libanogs.so","0x4E057C","00 00 80 D2 C0 03 5F D6");
PATCH_LIB("libanogs.so","0x4E62FC","00 00 80 D2 C0 03 5F D6");
PATCH_LIB("libanogs.so","0x4E778C","00 00 80 D2 C0 03 5F D6");
PATCH_LIB("libanogs.so","0x4E6E1C","00 00 80 D2 C0 03 5F D6");
PATCH_LIB("libanogs.so","0x4E7D64","00 00 80 D2 C0 03 5F D6");
HOOK_LIB_NO_ORIG("libanogs.so","0x275A0C",sub_275A0C);
PATCH_LIB("libanogs.so","0x371418","00 00 80 D2 C0 03 5F D6");
HOOK_LIB_NO_ORIG("libUE4.so","0xC25DF70", ApplySkins); //skin
HOOK_LIB_NO_ORIG("libUE4.so","0x790AC40",BT_DMG);//Fake Damage BT
	LOGI(oxorany("Bypass initialized sex"));
    chRestore();//restore permissions
    sleep(55);//lobby wait
    chfiles();//change permissions + 7day f
    return NULL;
}

void *crash_thread()
{
    ANOGSo = findLibrary("libanogs.so");

    while (true)
    {
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count();

        *(int64_t *)(ANOGSo + (0x5755D8)) = 1;
		*(int64_t *)(ANOGSo + (0x5755D8)) = 1;
        *(int64_t *)(ANOGSo + (0x5755D8)) = 1;
        auto td = std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count() -
                  t1;
        std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
    }
}

void *crashfix_thread(void *)
{
    do
    {
        sleep(1);
    } while (!isLibraryLoaded("libanogs.so"));
	sleep(10);
   crash_thread();
    return NULL;
}


__attribute__((constructor)) void mainload() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, dack_thread, NULL);       
    //pthread_create(&ptid, NULL, crashfix_thread, NULL);   
   // pthread_create(&ptid, NULL, ue4_thread, NULL);          
}