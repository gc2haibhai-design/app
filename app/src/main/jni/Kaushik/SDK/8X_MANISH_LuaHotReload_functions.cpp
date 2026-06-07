// SDK GENERATE BY TELEGRAM ;- (@Manish8x) (4.3.0 -- 64Bit) DM TO BUY TOOL AVLABLE FOR SELL
// Telegram:- @Manish8x
// GEN ONThu Mar 19 07:20:59 2026
 
#include "../SDK.hpp"

namespace SDK
{
//---------------------By Tg @Manish8x---------------------------
//Functions
//---------------------By Tg @Manish8x---------------------------

// Function LuaHotReload.LuaHotReloadHelper.OnLuaFileHotUpdate
// (Final, Native, Public)
// Parameters:
// struct FString                 NotifyMessage                  (Parm, ZeroConstructor)

void ULuaHotReloadHelper::OnLuaFileHotUpdate(const struct FString& NotifyMessage)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function LuaHotReload.LuaHotReloadHelper.OnLuaFileHotUpdate");

	ULuaHotReloadHelper_OnLuaFileHotUpdate_Params params;
	params.NotifyMessage = NotifyMessage;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


}

