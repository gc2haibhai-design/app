#include <chrono>
#include <thread>
#include <fstream>
#include <ctime>
#include <cstring>

#include "SkinLua.h"

// ---------------- LUA NAMESPACE ----------------


#include <fstream>
#include <ctime>
#include <cstdarg>

void WriteLog(const char* format, ...)
{
    char buffer[512];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::ofstream file("/sdcard/lua_injection_log.txt", std::ios::app);

    if (file.is_open())
    {
        time_t now = time(0);
        file << "[" << now << "] " << buffer << std::endl;
        file.close();
    }
}

namespace Lua
{
    int (*luaL_loadbufferx_Ptr)(void* L,const char* buff,size_t size,const char* name,const char* mode)=nullptr;
    int (*lua_pcall_Ptr)(void* L,int nargs,int nresults,int errfunc)=nullptr;
    int64_t (*sub_BA003F8_Ptr)(int a1)=nullptr;
    const char* (*lua_tostring_Ptr)(void* L,int index)=nullptr;

    // -------- GET LUA STATE --------

    void* GetLuaState()
{
    if (!sub_BA003F8_Ptr) 
        return nullptr;

    for (int i = 0; i < 128; i++)
    {
        int64_t result = sub_BA003F8_Ptr(i);

        if (!result) 
            continue;

        void* L = *(void**)(result + 80);

        if (L && ((uintptr_t)L > 0x100000))
            return L;
    }

    return nullptr;
}
    // -------- EXECUTE SCRIPT --------

    bool ExecuteLuaScript(void* L, const char* script, const char* name)
    {
        if (!L || !luaL_loadbufferx_Ptr || !lua_pcall_Ptr)
            return false;
        
        int load_result = luaL_loadbufferx_Ptr(L, script, strlen(script), name, "t");
        if (load_result == 0)
        {
            int exec_result = lua_pcall_Ptr(L, 0, 0, 0);
            if (exec_result != 0 && lua_tostring_Ptr)
            {
                const char* err = lua_tostring_Ptr(L, -1);
                if (err) WriteLog("[Lua] Error: %s", err);
            }
            WriteLog("[Lua] Executed script: %s", name);
            return exec_result == 0;
        }
        else
        {
            if (lua_tostring_Ptr)
            {
                const char* err = lua_tostring_Ptr(L, -1);
                if (err) WriteLog("[Lua] Error: %s", err);
            }
            return false;
        }
    }
}
