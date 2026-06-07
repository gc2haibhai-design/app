#pragma once

// SDK GENERATE BY TELEGRAM ;- (@Manish8x) (4.3.0 -- 64Bit) DM TO BUY TOOL AVLABLE FOR SELL
// Telegram:- @Manish8x
// GEN ONThu Mar 19 07:20:49 2026
 
namespace SDK
{
//---------------------By Tg @Manish8x---------------------------
//Classes
//---------------------By Tg @Manish8x---------------------------

// Class Renderer.SparseVolumeTextureViewerComponent
// 0x0030 (0x0960 - 0x0930)
class USparseVolumeTextureViewerComponent : public UPrimitiveComponent
{
public:
	float                                              Frame;                                                    // 0x0930(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              FrameRate;                                                // 0x0934(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      bPlayIng : 1;                                             // 0x0938(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      bLooping : 1;                                             // 0x0938(0x0001) (Edit, BlueprintVisible)
	unsigned char                                      bReversePlayback : 1;                                     // 0x0938(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bBlockingStreamingRequests : 1;                           // 0x0938(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bApplyPerFrameTransforms : 1;                             // 0x0938(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      bPivotAtCentroid : 1;                                     // 0x0938(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0939(0x0003) MISSED OFFSET
	float                                              VoxelSize;                                                // 0x093C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	ESparseVolumeTexturePreviewAttribute               PreviewAttribute;                                         // 0x0940(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0941(0x0003) MISSED OFFSET
	int                                                MipLevel;                                                 // 0x0944(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Extinction;                                               // 0x0948(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x14];                                      // 0x094C(0x0014) MISSED OFFSET

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class Renderer.SparseVolumeTextureViewerComponent");
		return pStaticClass;
	}

};


// Class Renderer.SparseVolumeTextureViewer
// 0x0008 (0x04B8 - 0x04B0)
class ASparseVolumeTextureViewer : public AInfo
{
public:
	class USparseVolumeTextureViewerComponent*         SparseVolumeTextureViewerComponent;                       // 0x04B0(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
        static UClass *pStaticClass = 0;
        if (!pStaticClass)
            pStaticClass = UObject::FindClass("Class Renderer.SparseVolumeTextureViewer");
		return pStaticClass;
	}

};


}

