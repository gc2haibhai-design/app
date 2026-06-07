#pragma once

// SDK GENERATE BY TELEGRAM ;- (@Manish8x) (4.3.0 -- 64Bit) DM TO BUY TOOL AVLABLE FOR SELL
// Telegram:- @Manish8x
// GEN ONThu Mar 19 07:20:57 2026
 
namespace SDK
{
//---------------------By Tg @Manish8x---------------------------
//Classes
//---------------------By Tg @Manish8x---------------------------

// Class bp_plugin.bp_pluginBPLibrary
// 0x0000 (0x0028 - 0x0028)
class Ubp_pluginBPLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class bp_plugin.bp_pluginBPLibrary");
		return pStaticClass;
	}


	static void bp_pluginSendEvent(const struct FString& jsonEventCmd);
	static int bp_pluginRequestInstallWidget(int wigetType, const struct FString& authInfo);
	static float bp_pluginLaunchMeemoFunction(const struct FString& Param);
	static bool bp_pluginIsInForeground();
	static int bp_pluginGetInstalledWidgetType();
};


}

