/*
 *  @date   : 2020/02/04
 *  @Creator : @Mrkaushikhaxor
 *  Https://t.me/KaushikCracking
 * Imgui Src Created By - @Mrkaushikhaxor                    
 * PUBG SUPPORT - GL/KR/VN/TW/BGMI ( Easy To Update )      
 * Change Sdk And Sdk.hpp + Offsets For Update             
 * Optimized Source Fully Lag Fix And Crash Fix            
 * Runtime Library Patch Hook And Non Hook Function Added     
 */
#include <jni.h>
#include <string>
#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <sys/limits.h>
#include <sys/mman.h>
#include <imgui/imgui.h>
#include <iostream>
#include <chrono>
#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>


#include <dirent.h>
#include <cstdlib>
#include <cstring>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/system_properties.h>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"


#include "Includes/Tools.h"
#include "Includes/StrEnc.h"
#include "Includes/shadowhook/shadowhook.h"
//#include "Includes/AetherHook/AetherHook.h"
#include "Includes/KittyMemory/MemoryPatch.h"
#include "Includes/And64InlineHook.hpp"
#include "Includes/ScreenShot/screenshot.h"
//#include "Includes/oxorany.cpp"
#include "Includes/Dobby/dobby.h"

#include "Kaushik/settings.h"
#include "Kaushik/Vector2.hpp"
#include "Kaushik/Vector3.hpp"
#include "Kaushik/Items.h"
#include "Kaushik/obfuscate.h"
#include "Kaushik/json.hpp"
#include "Kaushik/Rect.h"
#include "Kaushik/Iconcpp.h"
//#include "Kaushik/Menu.h"
#include "Kaushik/Font.h"
#include "Kaushik/Icon.h"
#include "Kaushik/HUD.h"
#include "Kaushik/HUD2.h"
#include "Kaushik/XorStr.hpp"
#include "Kaushik/Social.h"
#include "Kaushik/SDK.hpp"
#include "Offset.h"
#include "Kaushik.h"




using namespace SDK;

using json = nlohmann::json;

json items_data;
#define SLEEP_TIME 1000LL / 60LL
#define IM_PI 3.14159265358979323846f
#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))

static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
static float isRedV2 = 0.0f, isGreenV2 = 0.01f, isBlueV2 = 0.0f;
float menu[4] = { 0/255.f, 255/255.f, 0/255.f, 1.000f };

const char* getPackageName() {
    static char packageName[256] = {0};

    FILE* file = fopen("/proc/self/cmdline", "r");
    if (file) {
        fread(packageName, sizeof(char), sizeof(packageName) - 1, file);
        fclose(file);
    }

    return packageName;
}

const char* Gamepackage = getPackageName();


uintptr_t OpenSLES;
uintptr_t UE4;
uintptr_t Anogs;
uintptr_t swappy;
FVector targetAimPos;

char extras[32];
static char keyForLogin[64];
android_app *g_App = 0;
time_t expiredDate = 0;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;

ImFont* Injector;
ImFont* Injector2;
ImFont* Social;
float size_child = 0;
static float SliderFloat = 0;
static int a = 0;
static int AimVis = 0;

time_t rng = 0;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;
std::map<int, bool> Items;
std::map<int, float *> ItemColors;
std::string g_Token, g_Auth;




void MemorySkin();
void LobbySkins();

namespace KaushikSettings{
        inline bool bValid = false;
        inline bool isLogin = false;
        inline bool initImGui = false;

                
        inline bool LineTop;
	    inline bool Alert;
        inline bool Box;
        inline bool Skeleton;
        inline bool Health;
        inline bool Name;
        inline bool Distance;
        inline bool TeamID;
              
        inline bool AimBot;
        inline float AimDis = 120.0f;
        inline bool AimIgnoreKnocked;
        inline bool AimVisCheck;
		inline bool AimIgnoreBot;
		inline float AimBotCross = 450.0f;
        inline float AimBotRecc = 1.0;
        inline bool AutoAim;
        inline bool AimSmooth = 3.0f;
		inline bool SmallAim;
		inline int algorithm = 0;
        inline int Btalgorithm = 0;
		inline int trackingType = 1;
        inline int scopeAndFire = 0;
		
		inline bool BulletTrack;
		inline bool UpdateVolley;
		inline bool BtLaunch;
		inline float BtDis = 200.0f;
		inline bool SilentAim;
        inline bool BtIgnoreKnocked;
        inline bool BtVisCheck;
		inline bool BtIgnoreBot;
        
        inline bool ShowSkin;          
        inline bool SmallCross;
        inline bool CrossHair;
		inline bool WideView;
        inline bool FieldOfView;
		inline float FieldOfViewRange = 110;
		inline bool Autofire;
		inline bool FastPara;
		inline float SetZoom = 10.0f;
		inline bool Fps120 = true;
		inline bool RainSnow;
		inline bool Instant;		
        inline bool FastShoot;
		inline bool BlockUpdate = true;
		
		inline bool Magic;
		inline bool Ggxhit;
		inline bool GgxhitRgb;
		inline bool ActiveAllesp;
		inline bool PlayerDance;
		inline bool MaxStepHeight;
        inline bool CarSize;
        inline int CarrSize = 4.0f;
		inline bool CrazyCar;
		inline bool Cross360;
		inline bool GodView;
		inline bool Parachute;
        inline bool ShowDamage;
		inline bool IpadView;
		inline bool FPPCamera;
		inline bool Skinnn;
        inline bool WallHack;
        inline bool MuzzleCheck;
        inline bool SkateboardBoost;
		
		inline bool CheatEnabled1 = true;
		inline bool CheatEnabled2 = false;
		inline bool First_Ui = true;
		inline bool Second_Ui = false;
		inline bool Auto_uUi = false;
		inline bool SafeMenu = false;
        inline bool BrutalMenu = false;
		inline bool ESPOnline = false;
	    inline bool take_screenshot_flag = false;
	    
	    inline bool Online_Same = false;
	    inline bool ServerOff = false; // Server On
        inline bool VersionUp = false; // Check Passed
        inline int ServerVersion = 0;
        inline bool NetFailed = false;
        inline bool DownloadLib = false;
        inline std::string LibUrl;
        
        inline bool LibDownloading = false;   // abhi download ho rahi?
        inline bool LibLoaded = false;         // load complete?
        inline float DownloadProgress = 0.0f; // 0 - 100
        
        
        inline std::atomic<bool> LibReady{false};
        std::atomic<bool> LibThreadStarted{false};
        
        
        inline bool Network_Ui = true;
		
}


#include "Kaushik/DrawEsp.h"
#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(g_LocalController, w, true, s)
/*
 *  @date   : 2020/02/04
 *  @Creator : @Mrkaushikhaxor
 *  Https://t.me/KaushikCracking
 */

#include "Kaushik/BtShoot.cpp"
#include "Kaushik/Faaltu.h"

int32_t (*orig_ANativeWindow_getWidth)(ANativeWindow *window);
int32_t _ANativeWindow_getWidth(ANativeWindow *window)
{
screenWidth = orig_ANativeWindow_getWidth(window);
return orig_ANativeWindow_getWidth(window);
}


int32_t (*orig_ANativeWindow_getHeight)(ANativeWindow *window);
int32_t _ANativeWindow_getHeight(ANativeWindow *window)
{
screenHeight = orig_ANativeWindow_getHeight(window);
return orig_ANativeWindow_getHeight(window);
}

void RPC_Teleport(const FVector& destLocation) {
    if (!g_LocalPlayer || !g_LocalController) return;

ASTExtraBaseCharacter* baseChar = static_cast<ASTExtraBaseCharacter*>(g_LocalPlayer);
    if (!baseChar) return;

FRotator currentRotation = g_LocalController->PlayerCameraManager->CameraCache.POV.Rotation; 
baseChar->RPC_Client_TeleportToStart(true, destLocation, currentRotation, ETeleportPawnType::ETeleportPawnType__NormalTeleport, 0);
baseChar->RPC_Client_TeleportToFinish(true, destLocation, currentRotation, ETeleportPawnType::ETeleportPawnType__NormalTeleport, 0);

}

//------------ ESP DRAW FUNCTION --------------//
void DrawESP(ImDrawList *draw) {
    if (KaushikSettings::ESPOnline && !g_Token.empty() && !g_Auth.empty() && g_Token == g_Auth) {

        static USTExtraGameInstance *Instance = nullptr;
        if (!Instance)
            Instance = UObject::FindObject<USTExtraGameInstance>("STExtraGameInstance Transient.UAEGameEngine_1.STExtraGameInstance_1");

        if (Instance != nullptr) {
            auto& UserSettings = Instance->UserDetailSetting;

            UserSettings.IsSupportMSAA = 3;
            UserSettings.DeviceSupportHDR = 4;
            UserSettings.UserHDRSetting = 4;
            UserSettings.IsOpenHDR = 4;

            UserSettings.PUBGDeviceFPSDef = 120;
            UserSettings.PUBGDeviceFPSLow = 120;
            UserSettings.PUBGDeviceFPSMid = 120;
            UserSettings.PUBGDeviceFPSHigh = 120;
            UserSettings.PUBGDeviceFPSHDR = 120;
            UserSettings.PUBGDeviceFPSUltralHigh = 120;
            UserSettings.PUBGDeviceFPSUltimateHigh = 120;
            UserSettings.PUBGDeviceFPSUltimateHighTA = 120;

            UserSettings.DeviceQualityLevel = 120;
            UserSettings.PUBGDeviceUpdateFlag = 120;
            UserSettings.PUBGDeviceFPSUltimateHigh = 120;
        }
        

        auto Actors = GetNecessaryActors();
        auto GWorld = GetFullWorld();

        int totalEnemies = 0, totalBots = 0;

        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localController = 0;

        for (int i = 0; i < Actors.size(); i++) {
            auto Actor = Actors[i];
            if (isObjectInvalid(Actor))
                continue;

            if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
                localController = (ASTExtraPlayerController *)Actor;
                break;
            }
        }

        if (localController) {
            for (int i = 0; i < Actors.size(); i++) {
                auto Actor = Actors[i];
                if (isObjectInvalid(Actor))
                    continue;

                if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                    if (((ASTExtraPlayerCharacter *)Actor)->PlayerKey == localController->PlayerKey) {
                        localPlayer = (ASTExtraPlayerCharacter *)Actor;
                        break;
                    }
                }
            }
        }

        if (GWorld) {
            UNetDriver *NetDriver = GWorld->NetDriver;
            if (NetDriver) {
                UNetConnection *ServerConnection = NetDriver->ServerConnection;
                if (ServerConnection) {
                    localController = (ASTExtraPlayerController *)ServerConnection->PlayerController;
                }
            }
        }

        if (localPlayer) {
            if (localPlayer->PartHitComponent) {
                auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
                for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {

                    ConfigCollisionDistSqAngles[j].Angle = 90.0f;
                }
                localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
            }
                      
      
                    if (KaushikSettings::FieldOfView) {
                                localPlayer->ThirdPersonCameraComponent->SetFieldOfView(KaushikSettings::FieldOfViewRange);
                            }

                            if (KaushikSettings::WideView) {
                                static ULocalPlayer* UlocalPlayer = nullptr;

                                if (!UlocalPlayer) {
                                    UlocalPlayer = static_cast<ULocalPlayer*>(
                                        GetObjectByClass(ULocalPlayer::StaticClass(), false)
                                    );
                                }

                                if (!UlocalPlayer)
                                    return;

                                static EAspectRatioAxisConstraint OrigView;
                                static bool bSaved = false;

                                if (!bSaved) {
                                    OrigView = UlocalPlayer->AspectRatioAxisConstraint;
                                    bSaved = true;
                                }

                                if (KaushikSettings::WideView) {
                                    UlocalPlayer->AspectRatioAxisConstraint =
                                        EAspectRatioAxisConstraint::AspectRatio_MaintainYFOV;
                                } else {
                                    UlocalPlayer->AspectRatioAxisConstraint = OrigView;
                                }
                            }

                            if (!localController == 0 && KaushikSettings::Auto_uUi) {
                                // KaushikSettings::SafeMenu = true;
                                KaushikSettings::BrutalMenu = true;
                            }
                            
                            if (KaushikSettings::CrossHair){
                            Write<float>(UE4 + 0x5B216DC, 8.47963525e-21);
                            }
                            if (KaushikSettings::Ggxhit){
                            Write<float>(UE4 + 0x9C85AE4, 8.95671814e-21);
                            }

                            if (KaushikSettings::BulletTrack) {
                                ASTExtraPlayerCharacter* Target = GetTargetByPussy();
                                long PlayerAimLineColor = IM_COL32(255, 255, 255, 200);

                                if (Target) {
                                    FVector HEAD;
                                    HEAD = Target->GetBonePos("Head", {0, 0, 0});

                                    ImVec2 headPosSC;
                                    if (W2S(HEAD, (FVector2D*)&headPosSC)) {
                                        draw->AddLine(
                                            headPosSC,
                                            {(float)glWidth / 2, (float)glHeight},
                                            PlayerAimLineColor,
                                            1.0f
                                        );
                                    }
                                }
                            }

               
			    	
                      for (int i = 0; i < Actors.size(); i++)
                        {
                            auto Actor = Actors[i];

                            if (isObjectInvalid(Actor))
                                continue;

                            if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {

                            auto Player = (ASTExtraPlayerCharacter*)Actor;

                            if (Player->PlayerKey == localPlayer->PlayerKey)
                                continue;

                            if (Player->TeamID == localPlayer->TeamID)
                                continue;

                            if (Player->bDead)
                                continue;

                            if (Player->bHidden)
                                continue;

                            if (!Player->RootComponent)
                                continue;
                                
                            float Distance = localPlayer->GetDistanceTo(Player) / 100.0f;
                            if (Distance > 500)
                                continue;            
                                
                                
                            auto bEnsure = Player->bRepEnsure;
                            bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0}, true);

                            ImU32 SCOLOR, SCOLOR2, SCOLOR3;

                            if (IsVisible)
                            {
                                SCOLOR  = IM_COL32(70, 200, 70, 200);
                                SCOLOR2 = IM_COL32(70, 200, 70, 120);
                                SCOLOR3 = IM_COL32(0, 255, 0, 255);
                            }
                            else
                            {
                                SCOLOR  = IM_COL32(200, 90, 90, 170);
                                SCOLOR2 = IM_COL32(200, 90, 90, 120);
                                SCOLOR3 = IM_COL32(255, 0, 0, 255);
                            }

                            if (Player->bEnsure)
                            {
                                SCOLOR  = IM_COL32(230, 230, 230, 200);
                                SCOLOR3 = IM_COL32(255, 255, 255, 255);
                            }
                        
                            if (KaushikSettings::Alert && !Player->bEnsure)
                            {
                                FVector MyPos = Player->CurrentVehicle ? Player->CurrentVehicle->RootComponent->RelativeLocation : Player->RootComponent->RelativeLocation;
                                FVector EnPos = localPlayer->CurrentVehicle ? localPlayer->CurrentVehicle->RootComponent->RelativeLocation : localPlayer->RootComponent->RelativeLocation;

                                bool shit = false;
                                FVector EntityPos = WorldToRadar(localController->PlayerCameraManager->CameraCache.POV.Rotation.Yaw, MyPos, EnPos, NULL, NULL, Vector3(glWidth, glHeight, 0), shit);

                                FVector angle;
                                Vector3 forward((float)(glWidth / 2) - EntityPos.X, (float)(glHeight / 2) - EntityPos.Y, 0.0f);
                                VectorAnglesRadar(forward, angle);

                                float rad = DEG2RAD(angle.Y + 180.f);
                                float newX = (glWidth / 2) + (55 / 2) * 8 * cosf(rad);
                                float newY = (glHeight / 2) + (55 / 2) * 8 * sinf(rad);

                                std::array<Vector3, 3> points{
                                    Vector3(newX - ((90 / 4 + 3.5f) / 2), newY - ((55 / 4 + 3.5f) / 2), 0.f),
                                    Vector3(newX + ((90 / 4 + 3.5f) / 4), newY, 0.f),
                                    Vector3(newX - ((90 / 4 + 3.5f) / 2), newY + ((55 / 4 + 3.5f) / 2), 0.f)
                                };

                                std::string label = (Player->Health == 0.0f) ? "Down" : std::to_string((int)Distance);
                                auto textSize = ImGui::CalcTextSize(label.c_str(), 0, density / 20.0f);
                                ImU32 color = (Player->Health == 0.0f) ? IM_COL32(255,0,0,255) : IM_COL32(255,255,255,255);

                                draw->AddText(Injector, density / 23.0f, {newX - (textSize.x / 2), newY + 5.f}, color, label.c_str());
                                RotateTriangle(points, angle.Y + 180.f);

                                draw->AddCircle(ImVec2(newX, newY), 9.0f, IM_COL32(255,255,255,255));
                                draw->AddCircleFilled(ImVec2(newX, newY), 5.0f, SCOLOR2);
                            }
    
    
                            FVector HeadPos = Player->GetBonePos("Head", {}); 
                            HeadPos.Z += 1.0f;

                            FVector RootPos = Player->GetBonePos("Root", {}),
                                    upper_r = Player->GetBonePos("upperarm_r", {}),
                                    lowerarm_r = Player->GetBonePos("lowerarm_r", {}),
                                    hand_r = Player->GetBonePos("hand_r", {}),
                                    upper_l = Player->GetBonePos("upperarm_l", {}),
                                    lowerarm_l = Player->GetBonePos("lowerarm_l", {}),
                                    hand_l = Player->GetBonePos("hand_l", {}),
                                    thigh_l = Player->GetBonePos("thigh_l", {}),
                                    calf_l = Player->GetBonePos("calf_l", {}),
                                    foot_l = Player->GetBonePos("foot_l", {}),
                                    thigh_r = Player->GetBonePos("thigh_r", {}),
                                    calf_r = Player->GetBonePos("calf_r", {}),
                                    foot_r = Player->GetBonePos("foot_r", {}),
                                    neck_01 = Player->GetBonePos("neck_01", {}),
                                    pelvis = Player->GetBonePos("pelvis", {}),
                                    spine_01 = Player->GetBonePos("spine_01", {}),
                                    spine_02 = Player->GetBonePos("spine_02", {}),
                                    spine_03 = Player->GetBonePos("spine_03", {});

                            ImVec2 HeadPosSC, RootPosSC, upper_rPoSC, lowerarm_rPoSC, hand_rPoSC,
                                   upper_lPoSC, lowerarm_lSC, hand_lPoSC, thigh_lPoSC, calf_lPoSC,
                                   foot_lPoSC, thigh_rPoSC, calf_rPoSC, foot_rPoSC, neck_01PoSC,
                                   pelvisPoSC, spine_01PoSC, spine_02PoSC, spine_03PoSC;

                            if (W2S(HeadPos,(FVector2D*)&HeadPosSC) && W2S(upper_r,(FVector2D*)&upper_rPoSC) &&
                                W2S(upper_l,(FVector2D*)&upper_lPoSC) && W2S(lowerarm_r,(FVector2D*)&lowerarm_rPoSC) &&
                                W2S(hand_r,(FVector2D*)&hand_rPoSC) && W2S(lowerarm_l,(FVector2D*)&lowerarm_lSC) &&
                                W2S(hand_l,(FVector2D*)&hand_lPoSC) && W2S(thigh_l,(FVector2D*)&thigh_lPoSC) &&
                                W2S(calf_l,(FVector2D*)&calf_lPoSC) && W2S(foot_l,(FVector2D*)&foot_lPoSC) &&
                                W2S(thigh_r,(FVector2D*)&thigh_rPoSC) && W2S(calf_r,(FVector2D*)&calf_rPoSC) &&
                                W2S(foot_r,(FVector2D*)&foot_rPoSC) && W2S(neck_01,(FVector2D*)&neck_01PoSC) &&
                                W2S(pelvis,(FVector2D*)&pelvisPoSC) && W2S(RootPos,(FVector2D*)&RootPosSC) &&
                                W2S(spine_01,(FVector2D*)&spine_01PoSC) && W2S(spine_02,(FVector2D*)&spine_02PoSC) &&
                                W2S(spine_03,(FVector2D*)&spine_03PoSC))
                            {
                                if (KaushikSettings::LineTop){
                                    draw->AddLine({(float)glWidth / 2, 70}, HeadPosSC, SCOLOR, 2.0f);
                            }
                                if (KaushikSettings::BrutalMenu) {
                                    draw->AddLine({(float)glWidth / 2, 70}, HeadPosSC, SCOLOR3, 2.0f);
                            }
                            
                       /*     
                            weapoMuzzleAndLineOfSight(
            localController,
            g_LocalController,
            localPlayer,
            Player,
            true
        );*/
                            
                            if (KaushikSettings::Skeleton) {

                                if (Distance < 30.f)
                                    for (auto& p : {neck_01PoSC, upper_rPoSC, upper_lPoSC, lowerarm_rPoSC, lowerarm_lSC, thigh_rPoSC, thigh_lPoSC, calf_lPoSC, calf_rPoSC})
                                        draw->AddCircleFilled(p, 1.0f, IM_COL32(255,255,255,150));

                                static float last = 0.f;
                                static ImU32 Cneck, Cupr, Cupl, Clr, Cll, Csp3, Csp2, Csp1, Cpelv, Ctl, Ctr, Ccl, Ccr;

                                float now = ImGui::GetTime();
                                if (now - last > 0.10f) {
                                    auto V = [&](const char* b)->ImU32 {
                                        if (Player->Health == 0.0f)
                                            return IM_COL32(255,165,0,150);

                                        return localController->LineOfSightTo(
                                            localController->PlayerCameraManager,
                                            Player->GetBonePos(b, {}), true
                                        ) ? IM_COL32(0,255,0,150) : IM_COL32(255,0,0,150);
                                    };

                                    Cneck=V("neck_01"); Cupr=V("upperarm_r"); Cupl=V("upperarm_l");
                                    Clr=V("lowerarm_r"); Cll=V("lowerarm_l");
                                    Csp3=V("spine_03"); Csp2=V("spine_02"); Csp1=V("spine_01");
                                    Cpelv=V("pelvis"); Ctl=V("thigh_l"); Ctr=V("thigh_r");
                                    Ccl=V("calf_l"); Ccr=V("calf_r");

                                    last = now;
                                }

                                draw->AddLine(upper_rPoSC, neck_01PoSC, Cneck, 1);
                                draw->AddLine(upper_lPoSC, neck_01PoSC, Cneck, 1);
                                draw->AddLine(upper_rPoSC, lowerarm_rPoSC, Cupr, 1);
                                draw->AddLine(lowerarm_rPoSC, hand_rPoSC, Clr, 1);
                                draw->AddLine(upper_lPoSC, lowerarm_lSC, Cupl, 1);
                                draw->AddLine(lowerarm_lSC, hand_lPoSC, Cll, 1);

                                draw->AddLine(neck_01PoSC, spine_03PoSC, Csp3, 1);
                                draw->AddLine(spine_03PoSC, spine_02PoSC, Csp2, 1);
                                draw->AddLine(spine_02PoSC, spine_01PoSC, Csp1, 1);
                                draw->AddLine(spine_01PoSC, pelvisPoSC, Cpelv, 1);
                                draw->AddLine(neck_01PoSC, HeadPosSC, Cneck, 1);

                                draw->AddLine(pelvisPoSC, thigh_lPoSC, Ctl, 1);
                                draw->AddLine(thigh_lPoSC, calf_lPoSC, Ctl, 1);
                                draw->AddLine(calf_lPoSC, foot_lPoSC, Ccl, 1);
                                draw->AddLine(pelvisPoSC, thigh_rPoSC, Ctr, 1);
                                draw->AddLine(thigh_rPoSC, calf_rPoSC, Ctr, 1);
                                draw->AddLine(calf_rPoSC, foot_rPoSC, Ccr, 1);
                            }

                            if (KaushikSettings::Name && !Player->bEnsure) {
                                float boxWidth = density / 1.6f - std::min(((density / 1.6f) / 2 / 00.0f) * Distance, (density / 1.6f) / 2);
                                float boxHeight = boxWidth * 0.13f;

                                std::string s = Player->PlayerName.ToString();
                                draw->AddText(Injector2, density / 27.0f,
                                    {HeadPosSC.x - (boxWidth / 5.0f), HeadPosSC.y - (boxHeight * 1.499f)},
                                    IM_COL32(255,255,255,220), s.c_str());
                            }

                            if (KaushikSettings::Distance && !Player->bEnsure) {
                                float boxWidth = density / 1.6f - std::min(((density / 1.6f) / 2 / 00.0f) * Distance, (density / 1.6f) / 2);

                                std::string s = std::to_string((int)Distance) + " M";
                                auto textSize = ImGui::CalcTextSize(s.c_str(), 0, density / 35.0f);

                                draw->AddText(Injector2, density / 26.0f,
                                    {RootPosSC.x - (textSize.x / 4.5f), RootPosSC.y},
                                    IM_COL32(255,255,255,220), s.c_str());
                            }
    
    
                            if (KaushikSettings::BrutalMenu) {

                                if (Distance < 30.f)
                                    for (auto& p : {neck_01PoSC, upper_rPoSC, upper_lPoSC, lowerarm_rPoSC, lowerarm_lSC, thigh_rPoSC, thigh_lPoSC, calf_lPoSC, calf_rPoSC})
                                        draw->AddCircleFilled(p, 1.5f, IM_COL32(255,255,255,255));

                                static float last = 0.f;
                                static ImU32 Cneck, Cupr, Cupl, Clr, Cll, Csp3, Csp2, Csp1, Cpelv, Ctl, Ctr, Ccl, Ccr;

                                float now = ImGui::GetTime();
                                if (now - last > 0.10f) {
                                    auto V = [&](const char* b) {
                                        return localController->LineOfSightTo(localController->PlayerCameraManager, Player->GetBonePos(b, {}), true)
                                            ? IM_COL32(0,255,0,255) : IM_COL32(255,0,0,255);
                                    };

                                    Cneck=V("neck_01"); Cupr=V("upperarm_r"); Cupl=V("upperarm_l");
                                    Clr=V("lowerarm_r"); Cll=V("lowerarm_l");
                                    Csp3=V("spine_03"); Csp2=V("spine_02"); Csp1=V("spine_01");
                                    Cpelv=V("pelvis"); Ctl=V("thigh_l"); Ctr=V("thigh_r");
                                    Ccl=V("calf_l"); Ccr=V("calf_r");
                                    last = now;
                                }

                                draw->AddLine(upper_rPoSC, neck_01PoSC, Cneck, 1.5f);
                                draw->AddLine(upper_lPoSC, neck_01PoSC, Cneck, 1.5f);
                                draw->AddLine(upper_rPoSC, lowerarm_rPoSC, Cupr, 1.5f);
                                draw->AddLine(lowerarm_rPoSC, hand_rPoSC, Clr, 1.5f);
                                draw->AddLine(upper_lPoSC, lowerarm_lSC, Cupl, 1.5f);
                                draw->AddLine(lowerarm_lSC, hand_lPoSC, Cll, 1.5f);

                                draw->AddLine(neck_01PoSC, spine_03PoSC, Csp3, 1.5f);
                                draw->AddLine(spine_03PoSC, spine_02PoSC, Csp2, 1.5f);
                                draw->AddLine(spine_02PoSC, spine_01PoSC, Csp1, 1.5f);
                                draw->AddLine(spine_01PoSC, pelvisPoSC, Cpelv, 1.5f);
                                draw->AddLine(neck_01PoSC, HeadPosSC, Cneck, 1.5f);

                                draw->AddLine(pelvisPoSC, thigh_lPoSC, Ctl, 1.5f);
                                draw->AddLine(thigh_lPoSC, calf_lPoSC, Ctl, 1.5f);
                                draw->AddLine(calf_lPoSC, foot_lPoSC, Ccl, 1.5f);
                                draw->AddLine(pelvisPoSC, thigh_rPoSC, Ctr, 1.5f);
                                draw->AddLine(thigh_rPoSC, calf_rPoSC, Ctr, 1.5f);
                                draw->AddLine(calf_rPoSC, foot_rPoSC, Ccr, 1.5f);
                            }

    
                            if (KaushikSettings::BrutalMenu && !Player->bEnsure) {
                                float boxWidth = density / 1.6f - std::min(((density / 1.6f) / 2 / 00.0f) * Distance, (density / 1.6f) / 2);
                                std::string s = std::to_string((int)Distance) + " M";
                                auto textSize = ImGui::CalcTextSize(s.c_str(), 0, density / 35.0f);

                                draw->AddText(Injector2, density / 26.0f,
                                    {RootPosSC.x - (textSize.x / 4.5f), RootPosSC.y},
                                    IM_COL32(255,255,255,225), s.c_str());
                            }

                            if (KaushikSettings::Health && !Player->bEnsure) {
                                int CurHP = std::clamp((int)Player->Health, 0, (int)Player->HealthMax);
                                int MaxHP = (int)Player->HealthMax;

                                float HealthPercent = (float)CurHP / MaxHP;
                                long HPColor;

                                if (HealthPercent <= 0.25f)      HPColor = IM_COL32(255,0,0,150);
                                else if (HealthPercent <= 0.50f) HPColor = IM_COL32(255,165,0,150);
                                else if (HealthPercent <= 0.75f) HPColor = IM_COL32(255,255,0,150);
                                else                              HPColor = IM_COL32(0,255,0,150);

                                if (Player->Health == 0.0f && !Player->bDead) {
                                    HPColor = IM_COL32(200,0,0,180);
                                    CurHP = Player->NearDeathBreath;
                                    if (Player->NearDeatchComponent)
                                        MaxHP = Player->NearDeatchComponent->BreathMax;
                                }

                                float boxWidth = density / 7.0f - std::min(((density / 7.0f) / 2 / 00.0f) * Distance, (density / 7.0f) / 2);
                                float boxHeight = boxWidth * 0.13f;

                                ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2), HeadPosSC.y - (boxHeight * 2.0f)};
                                ImVec2 vEndFilled = {vStart.x + (CurHP * boxWidth / MaxHP), vStart.y + boxHeight};
                                ImVec2 vEndRect = {vStart.x + boxWidth, vStart.y + boxHeight};

                                draw->AddRectFilled(vStart, vEndRect, IM_COL32(0,0,0,180));
                                draw->AddRectFilled(vStart, vEndFilled, HPColor);
                            }
   
   
      }}// Esp loop End
      
      
      
     
      
                            if (KaushikSettings::GgxhitRgb && Actor->IsA(ASurviveHUD::StaticClass())) {
                                ASurviveHUD* xRGB = (ASurviveHUD*)Actor;

                                static float cnt = 0.0f;
                                const float PI = 3.14159265358979f, speed = 0.9f;

                                cnt = fmod(cnt + speed, 2.0f * PI);

                                float r = cosf(cnt) * 0.5f + 0.5f;
                                float g = cosf(cnt - 2.0f * PI / 3.0f) * 0.5f + 0.5f;
                                float b = cosf(cnt - 4.0f * PI / 3.0f) * 0.5f + 0.5f;

                                SDK::FLinearColor premiumColor(r, g, b, 1.0f);

                                xRGB->HitPerform.HitBodyDrawColor = premiumColor;
                                xRGB->HitPerform.HitHeadDrawColor = premiumColor;
                            }
    
                            if (Actor->IsA(ASTExtraGrenadeBase::StaticClass())) {
                                auto Throw = (ASTExtraGrenadeBase*)Actor;
                                auto RootComponent = Actor->RootComponent;
                                if (!RootComponent || Throw->bHidden) continue;

                                float Distance = Throw->GetDistanceTo(localPlayer) / 100.f;
                                if (Distance > 100) continue;

                                FVector2D GrenadePos;
                                if (W2S(Throw->K2_GetActorLocation(), &GrenadePos)) {
                                    std::string classname = Throw->GetName(), s;
                                    auto drawLabel = [&](const std::string &label) {
                                        s = label + " - " + std::to_string((int)Distance) + "M";
                                        auto textSize = ImGui::CalcTextSize2(s.c_str(), 0, ((float)density / 22.0f));
                                        draw->AddText(Injector2, ((float)density / 22.0f),
                                                      {GrenadePos.X - (textSize.x / 2), GrenadePos.Y},
                                                      ImColor(isRedV2, isBlueV2, isGreenV2, 8.0f),
                                                      s.c_str());
                                    };

                                    if (classname.find("BP_Projectile_BurnGrenade_C") != std::string::npos) drawLabel("Molotov");
                                    else if (classname.find("BP_Projectile_SmokeBomb_C") != std::string::npos) drawLabel("Smoke");
                                    else if (classname.find("BP_Projectile_StunGrenade_C") != std::string::npos) drawLabel("Stun");
                                    else if (classname.find("BP_Projectile_FragGrenade_C") != std::string::npos) drawLabel("Grenade");
                                    else if (classname.find("BP_Projectile_Apple_C") != std::string::npos) drawLabel("Apple");
                                }
                            }

                            //-- Start ScreenShot
                            if (Actor->IsA(ASTExtraGameStateBase::StaticClass())) {
                                static int screenshot_stage = 0;
                                static bool flag_on = false;
                                static bool waiting = false;
                                static std::chrono::steady_clock::time_point start_time;

                                auto InGame = (ASTExtraGameStateBase*)Actor;
                                int aliveTeams = (int)InGame->AliveTeamNum;

                                // Stage 0: Wait for AliveTeamNum == 5
                                if (aliveTeams == 5 && screenshot_stage == 0) {
                                    if (!waiting) {
                                        start_time = std::chrono::steady_clock::now();
                                        waiting = true;
                                    } else {
                                        auto now = std::chrono::steady_clock::now();
                                        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();

                                        if (elapsed >= 3) {
                                            KaushikSettings::take_screenshot_flag = true;
                                            start_time = std::chrono::steady_clock::now(); // for turning off
                                            flag_on = true;
                                            waiting = false;
                                            screenshot_stage = 1;
                                        }
                                    }
                                }

                                // Stage 1: Wait for AliveTeamNum == 1
                                if (aliveTeams == 1 && screenshot_stage == 1) {
                                    if (!waiting) {
                                        start_time = std::chrono::steady_clock::now();
                                        waiting = true;
                                    } else {
                                        auto now = std::chrono::steady_clock::now();
                                        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();

                                        if (elapsed >= 3) {
                                            KaushikSettings::take_screenshot_flag = true;
                                            start_time = std::chrono::steady_clock::now(); // for turning off
                                            flag_on = true;
                                            waiting = false;
                                            screenshot_stage = 2; // done
                                        }
                                    }
                                }

                                // Auto turn off after 300ms
                                if (flag_on) {
                                    auto now = std::chrono::steady_clock::now();
                                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();

                                    if (elapsed > 300) {
                                        KaushikSettings::take_screenshot_flag = false;
                                        flag_on = false;
                                    }
                                }
                            }
/*
                            // GoldenToken Display
                            if (Actor->IsA(APickUpWrapperActor::StaticClass())) {
                                auto PickUp = (APickUpWrapperActor*)Actor;
                                if (!PickUp->RootComponent) continue;

                                float Distance = PickUp->GetDistanceTo(localPlayer) / 100.f;
                                if (Distance > 10 || PickUp->bHidden) continue;

                                FVector2D tokenPos;
                                if (W2S(PickUp->K2_GetActorLocation(), &tokenPos)) {
                                    std::string className = PickUp->GetName();
                                    if (className.find("GoldenTokenWrapper_C") != std::string::npos) {
                                        std::string s = "Money - " + std::to_string((int)Distance) + "M";
                                        draw->AddText(Injector2, (density / 28.0f), {tokenPos.X, tokenPos.Y}, IM_COL32(255, 255, 0, 220), s.c_str());
                                    }
                                }
                            }
                            */

                            // Item ID to Info Mapping
                            std::unordered_map<int, std::pair<std::string, uint32_t>> itemIdToDisplayInfo;
                            for (auto& cat : items_data) {
                                for (auto& item : cat["Items"]) {
                                    int id = item["itemId"].get<int>();
                                    std::string name = item["itemName"].get<std::string>();
                                    uint32_t color = strtoul(item["itemTextColor"].get<std::string>().c_str(), nullptr, 16);
                                    itemIdToDisplayInfo[id] = {name, color};
                                    Items[id] = true;
                                }
                            }

                            // Display items by item ID
                            if (Actors[i]->IsA(APickUpWrapperActor::StaticClass())) {
                                auto PickUp = (APickUpWrapperActor*)Actors[i];
                                int itemId = PickUp->DefineID.TypeSpecificID;

                                if (Items.count(itemId) && Items[itemId] && PickUp->RootComponent && !PickUp->bHidden) {
                                    float Distance = PickUp->GetDistanceTo(g_LocalPlayer) / 100.f;
                                    if (Distance <= 0.1f || Distance > 20.0f) continue;

                                    FVector2D itemPos;
                                    if (W2S(PickUp->K2_GetActorLocation(), &itemPos)) {
                                        std::string name;
                                        uint32_t color = 0xFF000000;

                                        if (itemIdToDisplayInfo.count(itemId)) {
                                            name = itemIdToDisplayInfo[itemId].first;
                                            color = itemIdToDisplayInfo[itemId].second;
                                        }

                                        name += " - " + std::to_string((int)Distance) + "M";
                                        draw->AddText(Injector2, (density / 28.0f), {itemPos.X, itemPos.Y}, color, name.c_str());
                                    }
                                }
                            }
                        }
                    }
  
  
  
    	g_LocalController = localController;
		g_LocalPlayer = localPlayer;

	    float fontSize = (float)density / 15.0f;
        float y = 40.0f;
        ImFont* font = ImGui::GetFont();

        ImVec2 textSize = font->CalcTextSizeA(fontSize,FLT_MAX,0.0f,creditText.c_str());
        float x = (glWidth - textSize.x) * 0.5f;
        
        ImVec2 textPos = ImVec2(x, y);

        ImU32 red = IM_COL32(255, 0, 0, 255);

        draw->AddText(NULL, fontSize, ImVec2(x - 1, y), red, creditText.c_str());
        draw->AddText(NULL, fontSize, ImVec2(x + 1, y), red, creditText.c_str());
        draw->AddText(NULL, fontSize, ImVec2(x, y - 1), red, creditText.c_str());
        draw->AddText(NULL, fontSize, ImVec2(x, y), red, creditText.c_str());
     
       static float lastClickTime = 0.0f;
       float currentTime = ImGui::GetTime();
       ImVec2 mousePos = ImGui::GetMousePos();
       bool isHovering = mousePos.x >= textPos.x && mousePos.x <= textPos.x + textSize.x &&
       mousePos.y >= textPos.y && mousePos.y <= textPos.y + textSize.y;
       if (isHovering && ImGui::IsMouseClicked(0)) {
       if (currentTime - lastClickTime < 0.3f) {
       system("rm -rf /data/data/com.pubg.imobile/databases");
       system("rm -rf /storage/Android/data/com.pubg.imobile/files/UE4Game/ShadowTrackerExtra/ShadowTrackerExtra/Saved/SaveGames/logininfoFile.json");
       ShowInfoToast("DataBase Remove Successful!");
       }
       lastClickTime = currentTime;
       }
/*       
if(KaushikSettings::AimBot || KaushikSettings::BulletTrack){
draw->AddCircle(ImVec2(glWidth / 2.0f, glHeight / 2.0f), KaushikSettings::AimBotCross*0.5f, IM_COL32(255, 255, 255, 55), 100, 0.5f);
}*/}
}//server
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||


#include "Kaushik/Login.h"
#include "Kaushik/OnlineSo.h"
static std::string Filepath =
    "/sdcard/Android/data/" + std::string(Gamepackage) + "/key.lic";


#include "Kaushik/DrawUi.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||
                     
                     
                     if(KaushikSettings::ActiveAllesp){
			         KaushikSettings::LineTop = true;
					 KaushikSettings::Health = true;
					 KaushikSettings::Distance = true;
					 KaushikSettings::Skeleton = true;
				 	//KaushikSettings::Box = true;
					 KaushikSettings::TeamID = true;
					 KaushikSettings::Name = true;
					 KaushikSettings::Alert = true;
					 KaushikSettings::FieldOfView = true;
					 }
                     


					 if(KaushikSettings::AimBot){
					 KaushikSettings::AimVisCheck = true;
					 KaushikSettings::AimIgnoreKnocked = true;
	 				 }
                      
                      
                     if (KaushikSettings::bValid && KaushikSettings::SafeMenu) {
                     KaushikSettings::ActiveAllesp = true;
                     KaushikSettings::AimBot = true;
                     }
                     
                    if (KaushikSettings::bValid && KaushikSettings::BrutalMenu) {
                        
                     //KaushikSettings::MaxStepHeight = true;
                     //KaushikSettings::GgxhitRgb = true;
                    // KaushikSettings::Ggxhit = true;
                     KaushikSettings::BulletTrack = true;
                  //   KaushikSettings::MuzzleCheck = true;
                     KaushikSettings::WideView = true;
                     KaushikSettings::CrossHair = true;
                     KaushikSettings::ShowDamage = true;
                     //KaushikSettings::FastPara = true;
                    // KaushikSettings::FieldOfView = true;
                    // KillMessage = true;
                    
                     }
              

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~||

void AutoLoginFromFile();
bool SaveKeyToFile(const std::string& path, const char* key);
bool fileExists(const std::string& path);
bool isFileEmpty(const std::string& path);
void GetKeyFromFile();
void deleteKeyFile();

// ===== GLOBALS =====
static std::string err;

static char keybuf[64] = {0};
static char keyForLogin[64] = {0};
static char lastKeyBuf[64] = {0};

static bool requireRestart = false;
static bool autoLoginDone = false;
static bool restartTimerStarted = false;
static double restartStartTime = 0.0;
static bool loginInProgress = false;
static bool loginFinished = false;
static std::string loginResult;

static bool showVirtualKeyboard = false;

static std::string statusText = "Paste or enter your license key";
static ImVec4 statusColor = ImVec4(0.55f, 0.55f, 0.55f, 1);



if (!autoLoginDone)
    {
        AutoLoginFromFile();
        autoLoginDone = true;
    }
    
if (KaushikSettings::First_Ui)
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1,1,1,1));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.93f,0.93f,0.95f,1));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.86f,0.86f,0.89f,1));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.82f,0.82f,0.86f,1));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.78f,0.78f,0.82f,1));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.05f,0.05f,0.05f,1));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 14);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12,10));

    ImGui::SetNextWindowPos(
        ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f,
               ImGui::GetIO().DisplaySize.y * 0.5f),
        ImGuiCond_Always,
        ImVec2(0.5f, 0.5f)
    );

    ImGui::SetNextWindowSize(ImVec2(520, 0), ImGuiCond_Always);

    ImGui::Begin("KAUSHIK_LOGIN", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );

    float w = ImGui::GetContentRegionAvail().x;
    const char* title = MOD_NAME_TEXT;

    ImGui::SetCursorPosX((w - ImGui::CalcTextSize(title).x) * 0.5f);
    ImGui::TextUnformatted(title);

    ImGui::Dummy(ImVec2(0, 12));

    float frameH = ImGui::GetFrameHeight();
    float kbW = frameH + 16.0f;

    ImGui::BeginGroup();

    if (ImGui::Button(ICON_FA_KEYBOARD, ImVec2(kbW, frameH)))
        showVirtualKeyboard = !showVirtualKeyboard;

    ImGui::SameLine(0, 8);

    ImGui::PushItemWidth(w - kbW - 8);
    ImGui::InputTextWithHint("##key", "Enter Your License Key", keybuf, sizeof(keybuf));
    ImGui::PopItemWidth();

    ImGui::EndGroup();

    ImGui::Dummy(ImVec2(0, 12));

    float btnW = (w - 10) / 2;

    if (ImGui::Button("Paste Your Key", ImVec2(btnW, 42)))
    {
        auto clip = getClipboardText();
        if (!clip.empty())
        {
            strncpy(keybuf, clip.c_str(), sizeof(keybuf));
            keybuf[sizeof(keybuf) - 1] = '\0';
        }
        else
        {
            statusText = "Clipboard is empty";
            statusColor = ImVec4(1,0.3f,0.3f,1);
        }
    }

    ImGui::SameLine(0, 10);
    ImGui::Button("Telegram", ImVec2(btnW, 42));

    if (showVirtualKeyboard)
{
    ImGui::Dummy(ImVec2(0, 8));

    ImGui::BeginChild(
        "##virtual_keyboard",
        ImVec2(0, 270),   // fixed height so it is visible
        true,
        ImGuiWindowFlags_NoScrollbar
    );

    DrawVirtualKeyboard(keybuf, sizeof(keybuf));

    ImGui::EndChild();

    if (ImGui::Button("Done", ImVec2(-1, 42)))
        showVirtualKeyboard = false;
}
    if (strcmp(lastKeyBuf, keybuf) != 0)
    {
        strcpy(lastKeyBuf, keybuf);
        if (strlen(keybuf) > 0)
        {
            statusText = std::string("Key: ") + keybuf;
            statusColor = ImVec4(0.35f,0.65f,0.35f,1);
        }
        else
        {
            statusText = "Paste or enter your license key";
            statusColor = ImVec4(0.55f,0.55f,0.55f,1);
        }
    }

    ImGui::Dummy(ImVec2(0, 8));

if (requireRestart)
{
    if (!restartTimerStarted)
    {
        restartTimerStarted = true;
        restartStartTime = ImGui::GetTime();
    }

    double elapsed = ImGui::GetTime() - restartStartTime;
    int remaining = 3 - (int)elapsed;

    if (remaining < 0)
        remaining = 0;

    ImGui::Dummy(ImVec2(0, 6));
    ImGui::TextColored(
        ImVec4(0.4f, 0.4f, 0.4f, 1),
        "Restarting in %d...",
        remaining
    );

    if (elapsed >= 3.0)
    {
        exit(0);
    }
}
else
{
    if (ImGui::Button("LOGIN", ImVec2(-1, 46)))
    {
        if (strlen(keybuf) == 0)
        {
            statusText = "Paste or enter your license key";
            statusColor = ImVec4(0.55f,0.55f,0.55f,1);
        }
        else
        {
            err = Login(keybuf);
            if (err == "OK")
            {
                if (SaveKeyToFile(Filepath, keybuf))
                {
                    requireRestart = true;
                    statusText = "Key saved. Please restart app";
                    statusColor = ImVec4(0.35f,0.65f,0.35f,1);
                }
                else
                {
                    statusText = "Failed to save key";
                    statusColor = ImVec4(1,0.25f,0.25f,1);
                }
            }
            else
            {
                statusText = err;
                statusColor = ImVec4(1,0.25f,0.25f,1);
            }
        }
    }
}

    ImGui::Dummy(ImVec2(0, 6));
    ImGui::TextColored(statusColor, "%s", statusText.c_str());

    ImGui::End();

    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(6);
}

if (KaushikSettings::Second_Ui && KaushikSettings::bValid)
{
    ImGui::SetNextWindowSize(ImVec2(168, 120));
    ImGui::SetNextWindowPos(
        ImGui::GetMainViewport()->GetCenter(),
        ImGuiCond_Appearing,
        ImVec2(0.5f, 0.5f)
    );

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1,1,1,1));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);

    if (ImGui::Begin("##LoadingWindow", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove))
    {
        static auto server_off_time = std::chrono::steady_clock::now();
        static auto failed_time     = std::chrono::steady_clock::now();
        static auto check_time      = std::chrono::steady_clock::now(); // ✅ FIX #1
        static auto start_time      = std::chrono::steady_clock::now();

        static bool failed_triggered = false;

        const char* text = nullptr;
        static char buffer[64];
        bool showAnimation = false;
        bool centerTextTop = false;
        bool showButton = false;

        auto now = std::chrono::steady_clock::now();
        ImGui::PushFont(Injector2);

        if (KaushikSettings::NetFailed)
        {
            text = "Network Failed";
            centerTextTop = true;
            showButton = true;

            if (!failed_triggered) {
                failed_time = now;
                failed_triggered = true;
            }/*
            if (std::chrono::duration_cast<std::chrono::seconds>(now - failed_time).count() > 4)
                exit(0);*/
        }
        else if (KaushikSettings::ServerOff)
        {
            text = "Server Off";
            centerTextTop = true;
            showButton = true;
/*
            if (std::chrono::duration_cast<std::chrono::seconds>(now - server_off_time).count() > 4)
              exit(0);*/
        }
        else
        {
            auto elapsed_time =
                std::chrono::duration_cast<std::chrono::seconds>(now - check_time).count();

            if (elapsed_time < 3)
            {
                text = "Check Device";
                showAnimation = true;
            }
            else
            {
                if (KaushikSettings::VersionUp)
                {
                    snprintf(buffer, sizeof(buffer),
                             "Update in (v%d)",
                             KaushikSettings::ServerVersion);
                    text = buffer;
                    centerTextTop = true;
                    showButton = true;

                    if (!failed_triggered) {
                        failed_time = now;
                        failed_triggered = true;
                    }/*
                    if (std::chrono::duration_cast<std::chrono::seconds>(now - failed_time).count() > 4)
                        exit(0);*/
                }
                else
                {
                    if (KaushikSettings::DownloadLib)
                    {
               /*         if (!KaushikSettings::LibThreadStarted)
    {
        KaushikSettings::LibThreadStarted = true;
        pthread_t t;
        pthread_create(&t, nullptr, Load_Lib, nullptr);
        pthread_detach(t);
    }
         */
                        if (KaushikSettings::LibDownloading)
                        {
                            snprintf(buffer, sizeof(buffer),
                                     "Load %.0f%%",
                                     KaushikSettings::DownloadProgress);
                            text = buffer;
                            showAnimation = true;
                        }
                        else if (KaushikSettings::LibLoaded)
                        {
                            text = "Loaded...";
                            showAnimation = true;
                        }
                        else
                        {
                            text = "Sync..";
                            showAnimation = true;
                        }
                    }
                    else
                    {
                        text = "Success !";
                        showAnimation = true;
                    }
                }
            }
        }
        
        
        ImGui::PopFont();
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 textSize = ImGui::CalcTextSize(text);

        if (centerTextTop)
{
    static bool tg_timer_started = false;
    static auto tg_time = std::chrono::steady_clock::now();

    auto now = std::chrono::steady_clock::now();

    if (!tg_timer_started)
    {
        tg_time = now;
        tg_timer_started = true;
    }

    int tg_elapsed =
        std::chrono::duration_cast<std::chrono::seconds>(now - tg_time).count();

    ImGui::SetCursorPos(ImVec2((windowSize.x - textSize.x) / 2, 10));
    ImGui::Text("%s", text);

    if (showButton && tg_elapsed < 2)
    {
        float bw = ImGui::GetContentRegionAvailWidth();
        ImGui::SetCursorPos(ImVec2((windowSize.x - bw) / 2, windowSize.y / 2));

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(1,1,1,1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1,1,1,0.8f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(1,1,1,0.6f));
        ImGui::PushStyleColor(ImGuiCol_Border,        ImVec4(1,1,1,1));
        ImGui::PushFont(Social);

        if (ImGui::Button("V", ImVec2(bw, 0)))
        {
            std::string url = UserName;
            OpenURL(url.c_str());
        }

        ImGui::PopFont();
        ImGui::PopStyleColor(4);
    }
    else if (showButton && tg_elapsed < 4)
    {
        int countdown = 4 - tg_elapsed; // 2 → 1

        char tgText[32];
        snprintf(tgText, sizeof(tgText), "Opening TG %d", countdown);

        ImVec2 tsize = ImGui::CalcTextSize(tgText);
        ImGui::SetCursorPos(
            ImVec2((windowSize.x - tsize.x) / 2,
                   (windowSize.y - tsize.y) / 2));
        ImGui::Text("%s", tgText);
    }
    else if (showButton && tg_elapsed >= 4)
    {
        static bool tg_opened = false;
    static auto exit_time = std::chrono::steady_clock::now();

    if (!tg_opened)
    {
        std::string url = UserName;
            OpenURL(url.c_str());
        
        exit_time = now;
        tg_opened = true;
    }
    if (std::chrono::duration_cast<std::chrono::seconds>(now - exit_time).count() >= 1)
    {
        exit(0);
        }
    }
}
        else
        {
            if (showAnimation)
            {
                ImDrawList* dl = ImGui::GetWindowDrawList();
                ImVec2 c = ImGui::GetCursorScreenPos();
                c.x += 68; c.y += 26;
                DrawLoadingAnimation(dl, c, 45, 5, 4, IM_COL32(0,0,0,255));
            }

            ImGui::SetCursorPos(
                ImVec2((windowSize.x - textSize.x)/2,
                       (windowSize.y - textSize.y)/2 + 40));
            ImGui::Text("%s", text);
        }
    auto elapsed_after_login =
        std::chrono::duration_cast<std::chrono::seconds>(now - start_time).count();
            
    static bool toast_triggered = false;
         if (elapsed_after_login > 2 && !toast_triggered) {
               toast_triggered = true;
                 std::string msg = std::string("Happy Cheat: ") + keyForLogin;
                    ShowInfoToast(msg.c_str());
               }
        if (KaushikSettings::Online_Same && KaushikSettings::bValid)
{
    if (elapsed_after_login >= 4)
        KaushikSettings::ESPOnline = true;

    if (elapsed_after_login >= 6)
    {
        KaushikSettings::Auto_uUi = true;
        KaushikSettings::Second_Ui = false;
        
    }
}

        ImGui::End();
    }

    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

ImGui::Render();
MemorySkin();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
if (KaushikSettings::take_screenshot_flag) {
    std::string path = TakeScreenshot(glWidth, glHeight);
    std::thread sendThread([path]() {
    SendScreenshotToTelegram(path.c_str());
    });
    sendThread.detach();
    KaushikSettings::take_screenshot_flag = false;
}
return orig_eglSwapBuffers(dpy, surface);
}

void (*orig_onInputEvent)(void *thiz, void *ex_ab, void *ex_ac);
void onInputEvent(void *thiz, void *ex_ab, void *ex_ac)
{
    orig_onInputEvent(thiz, ex_ab, ex_ac);
    if (KaushikSettings::initImGui)
    {
        ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)thiz, {(float)screenWidth / (float)glWidth, (float)screenHeight / (float)glHeight});
    }
    return;
}


#include "Kaushik_Skin.h"
//---------------------------------------------------------------------------------------------------------------------------------//

void xShootBulletInner(FVector* StartLocation, FRotator* StartRotation)
{
    if (!StartLocation || !StartRotation)
        return;

    if (!g_LocalPlayer || !g_LocalPlayer->bIsWeaponFiring)
        return;

    auto Target = GetTargetByPussy();
    if (!Target)
        return;

    FVector targetAimPos = Target->GetBonePos("Head", FVector(0, 0, 0));

    if (!std::isfinite(targetAimPos.X) || 
        !std::isfinite(targetAimPos.Y) || 
        !std::isfinite(targetAimPos.Z))
        return;

    FRotator aimRotation = ToRotator(*StartLocation, targetAimPos);

    if (!std::isfinite(aimRotation.Pitch) || !std::isfinite(aimRotation.Yaw) || !std::isfinite(aimRotation.Roll))
        return;

    aimRotation.Pitch = std::clamp(aimRotation.Pitch, -89.9f, 89.9f);
    aimRotation.Yaw   = fmodf(aimRotation.Yaw, 360.0f);

    *StartRotation = aimRotation;
    *StartLocation = targetAimPos;
}


int64_t (*orig_ProcessEvent)(UObject* Object, UFunction* Function, void* Params);
int64_t hook_ProcessEvent(UObject* Object, UFunction* Function, void* Params)
{
    if (!Object || !Function)
        return orig_ProcessEvent(Object, Function, Params);

    std::string fnName = Function->GetFullName();

   /* if (KaushikSettings::BulletTrack &&
        fnName == "Function ShadowTrackerExtra.STEShootWeaponProjectComponent.ShootBulletInner")
    {
        auto* shootParams = reinterpret_cast<USTEShootWeaponProjectComponent_ShootBulletInner_Params*>(Params);
        if (shootParams)
        {
            xShootBulletInner(&shootParams->StartLoc, &shootParams->StartRot);
        }
    }*/

    if (KaushikSettings::ShowDamage &&
        g_LocalPlayer && g_LocalController &&
        fnName.find("ClientOnDamageToOther") != std::string::npos)
    {
        auto localController = reinterpret_cast<ASTExtraPlayerController *>(Object);
        auto Params_ = reinterpret_cast<ASTExtraPlayerController_ClientOnDamageToOther_Params *>(Params);

        if (Params_)
        {
            auto damage = Params_->_DamageToOther;
            auto HUD = reinterpret_cast<ASurviveHUD *>(localController->MyHUD);
            if (HUD)
            {
                HUD->AddHitDamageNumberWithConfig(damage, g_LocalPlayer, g_LocalController, 0, 1, 1, 1);
            }
        }
    }

    return orig_ProcessEvent(Object, Function, Params);
}


#define SLEEP_TIME 1000LL / 120LL
void* kaushik_thread(void*)
{
    while (true)
    {
        auto t1 = std::chrono::steady_clock::now();

        auto localPlayer     = g_LocalPlayer;
        auto localController = g_LocalController;

        if (localPlayer && localController)
        {
            if (KaushikSettings::CrossHair)
            {
                auto weaponManager = localPlayer->WeaponManagerComponent;

                if (weaponManager)
                {
                    auto slot      = weaponManager->GetCurrentUsingPropSlot();
                    int  slotValue = static_cast<int>(slot.GetValue());

                    if (slotValue >= 1 && slotValue <= 3)
                    {
                        auto currentWeapon =
                            (ASTExtraShootWeapon*)weaponManager->CurrentWeaponReplicated;

                        if (currentWeapon)
                        {
                            auto shootComp = currentWeapon->ShootWeaponEntityComp;

                            if (shootComp && shootComp->GameDeviationFactor != 0.0f)
                            {
                                shootComp->GameDeviationFactor = 0.0f;
                            }
                        }
                    }
                }
            }

            if (KaushikSettings::Ggxhit)
            {
                if (localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS)
                {
                    auto myHUD = (ASurviveHUD*)localController->MyHUD;
                    if (!myHUD)
                        continue;

                    auto hitPerformPtr = &myHUD->HitPerform;
                    if (!hitPerformPtr)
                        continue;

                    uintptr_t hitPerformAddress =
                        *(uintptr_t*)(uintptr_t)hitPerformPtr;

                    if (!hitPerformAddress)
                        continue;

                    float maxImpact = 3999.0f;

                    *(float*)(hitPerformAddress + 0x10) = maxImpact;
                    *(float*)(hitPerformAddress + 0x50) = maxImpact;
                    *(float*)(hitPerformAddress + 0x90) = maxImpact;
                    *(float*)(hitPerformAddress + 0xD0) = maxImpact;

                    float time = fmodf(clock() * 0.001f, 6.28f);

                    float r = (sin(time) + 1.0f) * 0.5f;
                    float g = (sin(time + 2.0f) + 1.0f) * 0.5f;
                    float b = (sin(time + 4.0f) + 1.0f) * 0.5f;

                    FLinearColor rainbowColor(r, g, b, 1.0f);

                    myHUD->SetHitPerformColor(
                        EHitPerformColorType::EHitPerformColor_Head,
                        rainbowColor
                    );

                    myHUD->SetHitPerformColor(
                        EHitPerformColorType::EHitPerformColor_Body,
                        rainbowColor
                    );
                }
            }
    
            if (KaushikSettings::FastPara)
            {
                int check = 0;

                uintptr_t para =
                    (uintptr_t)localPlayer + 0x4780;

                Tools::PVM_ReadAddr(
                    (void*)para,
                    &check,
                    sizeof(check)
                );

                auto world = GetFullWorld();

                if (world && world->PersistentLevel)
                {
                    if (check == 65794)
                    {
                        world->PersistentLevel
                            ->WorldSettings
                            ->MinUndilatedFrameTime = 0.100f;
                    }
                    else
                    {
                        world->PersistentLevel
                            ->WorldSettings
                            ->MinUndilatedFrameTime = 0.0005f;
                    }
                }
            }

            if (KaushikSettings::MaxStepHeight)
            {
                uintptr_t characterMovement =
                    *(uintptr_t*)((uintptr_t)localPlayer + 0x1D38);

                if (characterMovement)
                {
                    *(float*)(characterMovement + 0x1B8) = 3999.9f;
                }
            }
        }

        auto td =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - t1
            ).count();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(
                SLEEP_TIME > td ? SLEEP_TIME - td : 0
            )
        );
    }

    return nullptr;
}

/*
 *  @date   : 2020/02/04
 *  @Creator : @Mrkaushikhaxor
 *  Https://t.me/KaushikCracking
 */

bool fileExists(const std::string& path)
{
    std::ifstream f(path);
    return f.good();
}

bool isFileEmpty(const std::string& path)
{
    std::ifstream f(path);
    return f.peek() == std::ifstream::traits_type::eof();
}

bool SaveKeyToFile(const std::string& path, const char* key)
{
    std::ofstream f(path, std::ios::out | std::ios::trunc);
    if (!f.is_open()) return false;
    f << key;
    f.close();
    return true;
}

void GetKeyFromFile()
{
    memset(keyForLogin, 0, sizeof(keyForLogin));

    int fd = open(Filepath.c_str(), O_RDONLY);
    if (fd == -1)
        return;

    int n = read(fd, keyForLogin, sizeof(keyForLogin) - 1);
    close(fd);

    if (n <= 0)
        return;

    keyForLogin[n] = '\0';

    // 🔥 trim newline / spaces
    for (int i = 0; keyForLogin[i]; i++)
    {
        if (keyForLogin[i] == '\n' || keyForLogin[i] == '\r')
        {
            keyForLogin[i] = '\0';
            break;
        }
    }
}

void deleteKeyFile()
{
    char path[256];
    sprintf(path, "/sdcard/Android/data/%s/key.lic", Gamepackage);
    remove(path);
}
void AutoLoginFromFile()
{
    if (!fileExists(Filepath) || isFileEmpty(Filepath))
        return;

    GetKeyFromFile();

    // safety
    if (strlen(keyForLogin) < 5)
        return;

    std::string r = Login(keyForLogin);

    if (r == "OK")
    {
        KaushikSettings::isLogin    = true;
        KaushikSettings::First_Ui  = false;
        KaushikSettings::Second_Ui = true;
    }
    else
    {
        KaushikSettings::isLogin    = false;
        KaushikSettings::First_Ui  = true;
        KaushikSettings::Second_Ui = false;
    }
}
void StartOnlineMonitor() {
    std::thread([]() {
            MonitorOnlineStatus();
    }).detach();
}

#include "Kaushik/main_thread.h"