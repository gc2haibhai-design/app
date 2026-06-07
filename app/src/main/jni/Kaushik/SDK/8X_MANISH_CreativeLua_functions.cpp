// SDK GENERATE BY TELEGRAM ;- (@Manish8x) (4.3.0 -- 64Bit) DM TO BUY TOOL AVLABLE FOR SELL
// Telegram:- @Manish8x
// GEN ONThu Mar 19 07:20:55 2026
 
#include "../SDK.hpp"

namespace SDK
{
//---------------------By Tg @Manish8x---------------------------
//Functions
//---------------------By Tg @Manish8x---------------------------

// Function CreativeLua.CreativeBridgeLuaVM.UGCLuaError
// (Final, Native, Public, Const)
// Parameters:
// int                            ErrCode                        (Parm, ZeroConstructor, IsPlainOldData)

void UCreativeBridgeLuaVM::UGCLuaError(int ErrCode)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CreativeLua.CreativeBridgeLuaVM.UGCLuaError");

	UCreativeBridgeLuaVM_UGCLuaError_Params params;
	params.ErrCode = ErrCode;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function CreativeLua.CreativeBridgeLuaVM.RegisterSluaCallUgcluaEventHandler
// (Final, Native, Public)

void UCreativeBridgeLuaVM::RegisterSluaCallUgcluaEventHandler()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CreativeLua.CreativeBridgeLuaVM.RegisterSluaCallUgcluaEventHandler");

	UCreativeBridgeLuaVM_RegisterSluaCallUgcluaEventHandler_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function CreativeLua.CreativeBridgeLuaVM.PostInit
// (Native, Public, BlueprintCallable)

void UCreativeBridgeLuaVM::PostInit()
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CreativeLua.CreativeBridgeLuaVM.PostInit");

	UCreativeBridgeLuaVM_PostInit_Params params;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	UObject *currentObj = (UObject *) this;
	currentObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;
}


// Function CreativeLua.CreativeEnvLuaVMFactory.CreateCreativeEnvLuaVM
// (Final, Native, Static, Public, BlueprintCallable)
// Parameters:
// struct FString                 InLuaFilePath                  (Parm, ZeroConstructor)
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// class UCreativeEnvLuaVM*       ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UCreativeEnvLuaVM* UCreativeEnvLuaVMFactory::CreateCreativeEnvLuaVM(const struct FString& InLuaFilePath, class UObject* WorldContextObject)
{
	static UFunction *pFunc = 0;
	if (!pFunc)
		pFunc  = UObject::FindObject<UFunction>("Function CreativeLua.CreativeEnvLuaVMFactory.CreateCreativeEnvLuaVM");

	UCreativeEnvLuaVMFactory_CreateCreativeEnvLuaVM_Params params;
	params.InLuaFilePath = InLuaFilePath;
	params.WorldContextObject = WorldContextObject;

	auto flags = pFunc->FunctionFlags;
	pFunc->FunctionFlags |= 0x400;

	static auto defaultObj = StaticClass()->GetDefaultObject();
	defaultObj->ProcessEvent(pFunc, &params);

	pFunc->FunctionFlags = flags;

	return params.ReturnValue;
}


}

