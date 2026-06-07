#pragma once

// SDK GENERATE BY TELEGRAM ;- (@Manish8x) (4.3.0 -- 64Bit) DM TO BUY TOOL AVLABLE FOR SELL
// Telegram:- @Manish8x
// GEN ONThu Mar 19 07:21:01 2026
 
namespace SDK
{
//---------------------By Tg @Manish8x---------------------------
//Classes
//---------------------By Tg @Manish8x---------------------------

// Class CableComponent.CableActor
// 0x0008 (0x04B8 - 0x04B0)
class ACableActor : public AActor
{
public:
	class UCableComponent*                             CableComponent;                                           // 0x04B0(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class CableComponent.CableActor");
		return pStaticClass;
	}

};


// Class CableComponent.CableComponent
// 0x0080 (0x0A00 - 0x0980)
class UCableComponent : public UMeshComponent
{
public:
	struct FComponentReference                         AttachEndTo;                                              // 0x0980(0x0018) (Edit)
	struct FName                                       AttachEndToSocketName;                                    // 0x0998(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     EndLocation;                                              // 0x09A0(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              CableLength;                                              // 0x09AC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                NumSegments;                                              // 0x09B0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              SubstepTime;                                              // 0x09B4(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                SolverIterations;                                         // 0x09B8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableStiffness;                                         // 0x09BC(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableCollision;                                         // 0x09BD(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x2];                                       // 0x09BE(0x0002) MISSED OFFSET
	float                                              CollisionFriction;                                        // 0x09C0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     CableForce;                                               // 0x09C4(0x000C) (Edit, BlueprintVisible, IsPlainOldData)
	float                                              CableGravityScale;                                        // 0x09D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              CableWidth;                                               // 0x09D4(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                NumSides;                                                 // 0x09D8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              TileMaterial;                                             // 0x09DC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x20];                                      // 0x09E0(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class CableComponent.CableComponent");
		return pStaticClass;
	}


	void SetAttachEndTo(class AActor* Actor, const struct FName& ComponentProperty, const struct FName& SocketName);
	void GetCableParticleLocations(TArray<struct FVector>* Locations);
	class USceneComponent* GetAttachedComponent();
	class AActor* GetAttachedActor();
};


}

