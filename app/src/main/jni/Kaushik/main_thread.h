int GetAndroidSdkVersion() {
        char prop_value[PROP_VALUE_MAX];
        __system_property_get(OBFUSCATE("ro.build.version.sdk"), prop_value);
        return atoi(prop_value);
}


void *main_thread(void *) {
    AutoLoginFromFile();
    StartOnlineMonitor();
    
    while (!UE4) { UE4 = Tools::GetBaseAddress("libUE4.so"); sleep(1); }
    
    while (!g_App) { g_App = *reinterpret_cast<android_app**>(UE4 + GNativeAndroidApp_Offset); std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
    while (!FName::GNames) { FName::GNames = reinterpret_cast<TNameEntryArray*(*)()>(UE4 + GNames_Offset)(); std::this_thread::sleep_for(std::chrono::milliseconds(100)); }

    UObject::GUObjectArray = (FUObjectArray*)(UE4 + GUObject_Offset);
    
    shadowhook_init(shadowhook_mode_t::SHADOWHOOK_MODE_UNIQUE, 0);
    
	shadowhook_hook_func_addr((void*)(UE4 + EglSwap_Offset), (void*)_eglSwapBuffers, (void**)&orig_eglSwapBuffers);
//  shadowhook_hook_func_addr((void*)(UE4 + LaunchBP), (void*)hook_LaunchBP, (void**)&orig_LaunchBP);	
	shadowhook_hook_sym_name("/system/lib64/libandroid.so", "ANativeWindow_getWidth",(void *)_ANativeWindow_getWidth,(void **)&orig_ANativeWindow_getWidth);
    shadowhook_hook_sym_name("/system/lib64/libandroid.so", "ANativeWindow_getHeight",(void *)_ANativeWindow_getHeight,(void **)&orig_ANativeWindow_getHeight);
		
	if (GetAndroidSdkVersion() < 35) {
        shadowhook_hook_sym_name("/system/lib64/libinput.so", "_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE",(void *)onInputEvent,(void **)&orig_onInputEvent); //Android 15 & above
    }

    if (GetAndroidSdkVersion() > 34) {
        shadowhook_hook_sym_name("/system/lib64/libinput.so", "_ZN7android12_GLOBAL__N_121initializeMotionEventERNS_11MotionEventERKNS_12InputMessageE",(void *)onInputEvent,(void **)&orig_onInputEvent); //Android 15
    }
    
    shadowhook_hook_func_addr((void*)(UE4 + ShortEvent_Offset), (void*)xBulletInner, (void**)&BulletInner);	
    shadowhook_hook_func_addr((void*)(UE4 + ProcessEvent_Offset_Child), (void*)hook_ProcessEvent, (void**)&orig_ProcessEvent);

    items_data = json::parse(JSON_ITEMS);

    return nullptr;
}


#include "Lua_Injection.h"
void* lua_thread(void*)
{
    while (!UE4)
    {
        UE4 = Tools::GetBaseAddress("libUE4.so");
        sleep(1);
    }

    Lua::luaL_loadbufferx_Ptr = (decltype(Lua::luaL_loadbufferx_Ptr))(UE4 + 0xAC9EE48);
    Lua::lua_pcall_Ptr = (decltype(Lua::lua_pcall_Ptr))(UE4 + 0xAC7B638);
    Lua::lua_tostring_Ptr = (decltype(Lua::lua_tostring_Ptr))(UE4 + 0xAC79A58);
    Lua::sub_BA003F8_Ptr = (decltype(Lua::sub_BA003F8_Ptr))(UE4 + 0xB99E000);

    while(true)
    {
        void* ctx = Lua::GetLuaState();

        if(ctx)
        {
            sleep(10);
            Lua::ExecuteLuaScript(ctx, KillCounterScript, "KillCounter");
            break;
        }

        sleep(1);
    }

    return nullptr;
}

__attribute__((constructor))
void _init() {
      pthread_t A1, B1;
      pthread_create(&A1, nullptr, main_thread, 0);
 //   pthread_create(&B1, nullptr, kaushik_thread, 0);
     // pthread_create(&B1, nullptr, lua_thread, 0);
  }
  