#pragma once

// SDK GENERATE BY TELEGRAM ;- (@Manish8x) (4.3.0 -- 64Bit) DM TO BUY TOOL AVLABLE FOR SELL
// Telegram:- @Manish8x
// GEN ONThu Mar 19 07:20:51 2026
 
namespace SDK
{
//---------------------By Tg @Manish8x---------------------------
//Classes
//---------------------By Tg @Manish8x---------------------------

// Class MRMesh.MeshReconstructorBase
// 0x0000 (0x0028 - 0x0028)
class UMeshReconstructorBase : public UObject
{
public:

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class MRMesh.MeshReconstructorBase");
		return pStaticClass;
	}


	void StopReconstruction();
	void StartReconstruction();
	void PauseReconstruction();
	bool IsReconstructionStarted();
	bool IsReconstructionPaused();
	void DisconnectMRMesh();
	struct FMRMeshConfiguration ConnectMRMesh(class UMRMeshComponent* Mesh);
};


// Class MRMesh.MRMeshComponent
// 0x0050 (0x0980 - 0x0930)
class UMRMeshComponent : public UPrimitiveComponent
{
public:
	class UMaterialInterface*                          Material;                                                 // 0x0930(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	class UMeshReconstructorBase*                      MeshReconstructor;                                        // 0x0938(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               bEnableCollision;                                         // 0x0940(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0941(0x0007) MISSED OFFSET
	TArray<class UBodySetup*>                          BodySetups;                                               // 0x0948(0x0010) (ZeroConstructor, Transient)
	unsigned char                                      UnknownData01[0x28];                                      // 0x0958(0x0028) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class MRMesh.MRMeshComponent");
		return pStaticClass;
	}


	class UMeshReconstructorBase* GetReconstructor();
	void ConnectReconstructor(class UMeshReconstructorBase* Reconstructor);
};


}

