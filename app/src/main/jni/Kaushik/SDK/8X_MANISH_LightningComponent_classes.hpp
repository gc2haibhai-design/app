#pragma once

// SDK GENERATE BY TELEGRAM ;- (@Manish8x) (4.3.0 -- 64Bit) DM TO BUY TOOL AVLABLE FOR SELL
// Telegram:- @Manish8x
// GEN ONThu Mar 19 07:21:02 2026
 
namespace SDK
{
//---------------------By Tg @Manish8x---------------------------
//Classes
//---------------------By Tg @Manish8x---------------------------

// Class LightningComponent.LightningActor
// 0x0008 (0x04B8 - 0x04B0)
class ALightningActor : public AActor
{
public:
	class ULightningComponent*                         LightningComponent;                                       // 0x04B0(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class LightningComponent.LightningActor");
		return pStaticClass;
	}

};


// Class LightningComponent.LightningComponent
// 0x00C0 (0x0A40 - 0x0980)
class ULightningComponent : public UMeshComponent
{
public:
	int                                                MaxFractalTime;                                           // 0x0980(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                PatternMask;                                              // 0x0984(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              LightningWidth;                                           // 0x0988(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              WidthDecay;                                               // 0x098C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              BrightnessDecay;                                          // 0x0990(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bShrinkWidth;                                             // 0x0994(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0995(0x0003) MISSED OFFSET
	int                                                AtlasNum;                                                 // 0x0998(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     SeedStart;                                                // 0x099C(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector                                     SeedEnd;                                                  // 0x09A8(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   ZigZagFraction;                                           // 0x09B4(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   ZigZagDeviationRight;                                     // 0x09BC(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   ZigZagDeviationUp;                                        // 0x09C4(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              ZigZagDeviationDecay;                                     // 0x09CC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ForkFraction;                                             // 0x09D0(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   ForkZigZagDeviationRight;                                 // 0x09D8(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   ForkZigZagDeviationUp;                                    // 0x09E0(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              ForkZigZagDeviationDecay;                                 // 0x09E8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ForkDeviationRight;                                       // 0x09EC(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   ForkDeviationUp;                                          // 0x09F4(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	struct FVector2D                                   ForkDeviationForward;                                     // 0x09FC(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              ForkDeviationDecay;                                       // 0x0A04(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ForkLength;                                               // 0x0A08(0x0008) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              ForkLengthDecay;                                          // 0x0A10(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x2C];                                      // 0x0A14(0x002C) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class LightningComponent.LightningComponent");
		return pStaticClass;
	}


	void SetWidthDecay(float InDecay);
	void SetShrinkWidth(bool InBool);
	void SetPatternMask(int InPatternMask);
	void SetMaxFractalTime(int InMaxFractalTime);
	void SetLightningWidth(float InWidth);
	void SetBrightnessDecay(float InDecay);
	void SetAtlasNum(int InVal);
	void RefreshLightningMesh();
	bool IsShrinkWidth();
	float GetWidthDecay();
	int GetPatternMask();
	int GetMaxFractalTime();
	float GetLightningWidth();
	float GetBrightnessDecay();
	float GetAtlasNum();
};


}

