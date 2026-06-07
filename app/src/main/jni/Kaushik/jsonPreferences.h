//
// Created by brian on 24/03/22.
//
#pragma once

#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

struct JsonPreferences {
int xsuit = 0;
int skinm4 = 0;
int skinakm = 0;
int para = 0;
int bag = 0;
int helmet = 0;
bool CoupeRB = false;
android_app *g_App = 0;
bool Dacia = false;
bool UAZ = false;
bool MiniBus = false;
bool BigFoot = false;
bool Boat = false;
bool Mirado = false;
bool Buggy = false;
bool OMirado = false;
bool Moto = false;
bool Emote = false;
bool Helmett = false;
bool Bagg = false;
bool Face = false;
bool Outfit = false;
bool Parachute = false;
bool M416 = false;
bool AKM = false;
bool P90 = false;
bool MINI14 = false;
bool SKS = false;
bool MG3 = false;
bool QBZ = false;
bool FAMAS = false;
bool AMR = false;
bool MK14 = false;
bool SCARL = false;
bool M762 = false;
bool AWM = false;
bool KAR98 = false;
bool M24 = false;
bool M16 = false;
bool M249 = false;
bool DP28 = false;
bool GROZA = false;
bool AUG = false;
bool PAN = false;
bool UZI = false;
bool UMP = false;
bool TOMMY = false;
bool BIZON = false;
bool ACE32 = false;
bool VECTOR = false;

    enum EAimTarget {
        Head = 0,
        Chest = 1
    };

    enum EAimTrigger {
        None = 0,
        Shooting = 1,
        Scoping = 2,
        Both = 3,
        Any = 4
    };

    enum EAimPriority {
        DistancePriority = 0,
        FOVPriority = 1
    };

    std::map<int, bool> Items;

    struct sConfig {
        struct sESPMenu {
            bool Line;
            bool Box;
            bool Skeleton;
            bool Health;
            bool Name;
            bool Distance;
            bool TeamID;
            bool Vehicle;
            bool IgnoreBot;
            bool LootBox;
            bool Throwables;
        };
        sESPMenu ESPMenu{false};

        struct sAimMenu {
            bool EnableAllHack;
            bool Enable;
            bool Autofire;
            bool AimBot;
            bool CameraCache;
            EAimTarget Target;
            EAimTrigger Trigger;
            EAimPriority Priority;
            bool IgnoreKnocked;
            bool IgnoreBot;
            bool Prediction;
            bool VisCheck;
            bool LessRecoil;
            bool Norecoil;
            bool InstantHit;
			bool godw;
			bool AutoParachute;
            bool FastShoot;
            bool HeadShoot;
            bool HitX;
            int Radius = 0;
            bool test5;
            bool SpeedHack;
        };
        sAimMenu SilentAim{false};
		
		struct sModSkin {
  bool Enable = 1;
  bool HitEffect = 0;
  bool KillMessage = 0;
  bool DeadBox = 0;
  int XSuits = 1;
  int AKM = 1;
  int P90 = 1;
  int MG3 = 1;
  int QBZ = 1;
  int FAMAS = 1;
  int AMR = 1;
  int SKS = 1;
  int MINI14 = 1;
  int MK14 = 1;
  int M16A4 = 1;
  int Scar = 1;
  int M416 = 1;
  int Groza = 1;
  int AUG = 1;
  int M762 = 1;
  int ACE32 = 1;
  int Parachute = 1;
  int UZI = 1;
  int UMP = 1;
  int Vector = 1;
  int Thompson = 1;
  int Bizon = 1;
  int K98 = 1;
  int M24 = 1;
  int AWM = 1;
  int DP28 = 1;
  int M249 = 1;
  int Pan = 1;
  int Moto = 1;
  int CoupeRP = 1;
  int UAZ = 1;
  int Dacia = 1;
  int Bigfoot = 1;
  int Mirado = 1;
  int OMirado = 1;
  int Buggy = 1;
  int MiniBus = 1;
  int Boat = 1;
};
sModSkin Skin{nullptr};
        struct sColorsESP {
            float *Line;
            float *Box;
        };
        sColorsESP ColorsESP{nullptr};
    };
    sConfig Config{false};

    // If you add something make sure add it in to_json and from_json functions
    // so it can be synced with the json
    friend void to_json(json &j, const JsonPreferences &p) {
        j = json{{("ESP Line"),      p.Config.ESPMenu.Line},
                 {("ESP Box"),       p.Config.ESPMenu.Box},
                 {("ESP Health"),    p.Config.ESPMenu.Health},
                 {("ESP Name"),      p.Config.ESPMenu.Name},
                 {("ESP Skeleton"),  p.Config.ESPMenu.Skeleton},
                 {("ESP Distance"),  p.Config.ESPMenu.Distance},
                 {("ESP Team ID"),   p.Config.ESPMenu.TeamID},
                 {("ESP IgnoreBot"), p.Config.ESPMenu.IgnoreBot},
                 {("ESP Vehicle"),   p.Config.ESPMenu.Vehicle},
                 {("ESP LootBox"),   p.Config.ESPMenu.LootBox},
                 {("ESP Throwables"),   p.Config.ESPMenu.Throwables},
                 {("ESP Weapon"),    p.Items},
				         {"CoupeRB", p.CoupeRB},
        {"Dacia", p.Dacia},
        {"UAZ", p.UAZ},
        {"MiniBus", p.MiniBus},
        {"BigFoot", p.BigFoot},
        {"Boat", p.Boat},
        {"Mirado", p.Mirado},
        {"Buggy", p.Buggy},
        {"OMirado", p.OMirado},
        {"Moto", p.Moto},
        {"Emote", p.Emote},
        {"Helmett", p.Helmett},
        {"Bagg", p.Bagg},
        {"Face", p.Face},
        {"Outfit", p.Outfit},
        {"Parachute", p.Parachute},
        {"M416", p.M416},
        {"P90", p.P90},
        {"AKM", p.AKM},
        {"MG3", p.MG3},
        {"QBZ", p.QBZ},
        {"FAMAS", p.FAMAS},
        {"AMR", p.AMR},
        {"SKS", p.SKS},
        {"MINI14", p.MINI14},
        {"MK14", p.MK14},
        {"SCARL", p.SCARL},
        {"M762", p.M762},
        {"AWM", p.AWM},
        {"KAR98", p.KAR98},
        {"M24", p.M24},
        {"M16", p.M16},
        {"M249", p.M249},
        {"DP28", p.DP28},
        {"GROZA", p.GROZA},
        {"AUG", p.AUG},
        {"PAN", p.PAN},
        {"UZI", p.UZI},
        {"UMP", p.UMP},
        {"TOMMY", p.TOMMY},
        {"BIZON", p.BIZON},
        {"ACE32", p.ACE32},
        {"VECTOR", p.VECTOR},
		{"XSuits ", p.Config.Skin.XSuits},
        {"AKM ", p.Config.Skin.AKM},
        {"AMR ", p.Config.Skin.AMR},
        {"MG3 ", p.Config.Skin.MG3},
        {"QBZ ", p.Config.Skin.QBZ},
        {"FAMAS ", p.Config.Skin.FAMAS},
        {"SKS ", p.Config.Skin.SKS},
        {"MINI14 ", p.Config.Skin.MINI14},
        {"MK14 ", p.Config.Skin.MK14},
        {"P90 ", p.Config.Skin.P90},
        {"M16A4 ", p.Config.Skin.M16A4},
        {"Scar ", p.Config.Skin.Scar},
        {"M416 ", p.Config.Skin.M416},
        {"Groza ", p.Config.Skin.Groza},
        {"AUG ", p.Config.Skin.AUG},
        {"M762 ", p.Config.Skin.M762},
        {"ACE32 ", p.Config.Skin.ACE32},
        {"Parachute ", p.Config.Skin.Parachute},
        {"UZI ", p.Config.Skin.UZI},
        {"UMP ", p.Config.Skin.UMP},
        {"Vector ", p.Config.Skin.Vector},
        {"Thompson ", p.Config.Skin.Thompson},
        {"Bizon ", p.Config.Skin.Bizon},
        {"K98 ", p.Config.Skin.K98},
        {"M24 ", p.Config.Skin.M24},
        {"AWM ", p.Config.Skin.AWM},
        {"DP28 ", p.Config.Skin.DP28},
        {"M249 ", p.Config.Skin.M249},
        {"Pan ", p.Config.Skin.Pan},
        {"Moto ", p.Config.Skin.Moto},
        {"CoupeRP ", p.Config.Skin.CoupeRP},
        {"UAZ ", p.Config.Skin.UAZ},
        {"Dacia ", p.Config.Skin.Dacia},
        {"Bigfoot ", p.Config.Skin.Bigfoot},
        {"Mirado ", p.Config.Skin.Mirado},
        {"OMirado ", p.Config.Skin.OMirado},
        {"Buggy ", p.Config.Skin.Buggy},
        {"MiniBus ", p.Config.Skin.MiniBus},
        {"Boat ", p.Config.Skin.Boat},
                 {("AimBullet"),    p.Config.SilentAim.Enable},
                 {("AimBot"),    p.Config.SilentAim.AimBot},
                 {("Autofire"),    p.Config.SilentAim.Autofire},
                 {("##Priority"),    p.Config.SilentAim.Priority},
                 //{("##FOV"),         p.Config.SilentAim.Radius},
                 {("##Target"),         p.Config.SilentAim.Target},
                 {("##Trigger"),         p.Config.SilentAim.Trigger},
                 {("Ignore Knocked"),         p.Config.SilentAim.IgnoreKnocked},
                 {("Ignore Bot"),         p.Config.SilentAim.IgnoreBot},
                 {("Prediction"),         p.Config.SilentAim.Prediction},
                 {("Visibility Check"),         p.Config.SilentAim.VisCheck},
                 {("NO Recoil"),         p.Config.SilentAim.Norecoil},
                 {("Instant Hit"),         p.Config.SilentAim.InstantHit},
                 {("FastShoot"),         p.Config.SilentAim.FastShoot},
                 {("Hit Effect"),         p.Config.SilentAim.HitX},
                 //{("Speed Hack (Beta)"),         p.Config.SilentAim.test5},

        };
    }

    friend void from_json(const json &j, JsonPreferences &p) {
        if (j.find(("ESP Line")) != j.end()) {
            j.at(("ESP Line")).get_to(p.Config.ESPMenu.Line);
        }
        if (j.find(("ESP Box")) != j.end()) {
            j.at(("ESP Box")).get_to(p.Config.ESPMenu.Box);
        }
        if (j.find(("ESP Health")) != j.end()) {
            j.at(("ESP Health")).get_to(p.Config.ESPMenu.Health);
        }
        if (j.find(("ESP Name")) != j.end()) {
            j.at(("ESP Name")).get_to(p.Config.ESPMenu.Name);
        }
        if (j.find(("ESP Skeleton")) != j.end()) {
            j.at(("ESP Skeleton")).get_to(p.Config.ESPMenu.Skeleton);
        }
        if (j.find(("ESP Distance")) != j.end()) {
            j.at(("ESP Distance")).get_to(p.Config.ESPMenu.Distance);
        }
        if (j.find(("ESP Team ID")) != j.end()) {
            j.at(("ESP Team ID")).get_to(p.Config.ESPMenu.TeamID);
        }
        if (j.find(("ESP IgnoreBot")) != j.end()) {
            j.at(("ESP IgnoreBot")).get_to(p.Config.ESPMenu.IgnoreBot);
        }
        if (j.find(("ESP Vehicle")) != j.end()) {
            j.at(("ESP Vehicle")).get_to(p.Config.ESPMenu.Vehicle);
        }
        if (j.find(("ESP LootBox")) != j.end()) {
            j.at(("ESP LootBox")).get_to(p.Config.ESPMenu.LootBox);
        }
        if (j.find(("ESP Throwables")) != j.end()) {
            j.at(("ESP Throwables")).get_to(p.Config.ESPMenu.Throwables);
        }
        if (j.find(("ESP Weapon")) != j.end()) {
            j.at(("ESP Weapon")).get_to(p.Items);
        }
		if (j.find("CoupeRB") != j.end()) {
        j.at("CoupeRB").get_to(p.CoupeRB);
    }

    if (j.find("Dacia") != j.end()) {
        j.at("Dacia").get_to(p.Dacia);
    }

    if (j.find("UAZ") != j.end()) {
        j.at("UAZ").get_to(p.UAZ);
    }

    if (j.find("MiniBus") != j.end()) {
        j.at("MiniBus").get_to(p.MiniBus);
    }

    if (j.find("BigFoot") != j.end()) {
        j.at("BigFoot").get_to(p.BigFoot);
    }

    if (j.find("Boat") != j.end()) {
        j.at("Boat").get_to(p.Boat);
    }

    if (j.find("Mirado") != j.end()) {
        j.at("Mirado").get_to(p.Mirado);
    }

    if (j.find("Buggy") != j.end()) {
        j.at("Buggy").get_to(p.Buggy);
    }

    if (j.find("OMirado") != j.end()) {
        j.at("OMirado").get_to(p.OMirado);
    }

    if (j.find("Moto") != j.end()) {
        j.at("Moto").get_to(p.Moto);
    }

    if (j.find("Emote") != j.end()) {
        j.at("Emote").get_to(p.Emote);
    }

    if (j.find("Helmett") != j.end()) {
        j.at("Helmett").get_to(p.Helmett);
    }

    if (j.find("Bagg") != j.end()) {
        j.at("Bagg").get_to(p.Bagg);
    }

    if (j.find("Face") != j.end()) {
        j.at("Face").get_to(p.Face);
    }

    if (j.find("Outfit") != j.end()) {
        j.at("Outfit").get_to(p.Outfit);
    }

    if (j.find("Parachute") != j.end()) {
        j.at("Parachute").get_to(p.Parachute);
    }

    if (j.find("M416") != j.end()) {
        j.at("M416").get_to(p.M416);
    }

    if (j.find("AKM") != j.end()) {
        j.at("AKM").get_to(p.AKM);
    }
    
        if (j.find("P90") != j.end()) {
        j.at("P90").get_to(p.P90);
    }
    
    if (j.find("MG3") != j.end()) {
        j.at("MG3").get_to(p.MG3);
    }
    
    if (j.find("QBZ") != j.end()) {
        j.at("QBZ").get_to(p.QBZ);
    }
    
    if (j.find("FAMAS") != j.end()) {
        j.at("FAMAS").get_to(p.FAMAS);
    }
    
    if (j.find("AMR") != j.end()) {
        j.at("AMR").get_to(p.AMR);
    }
    
    if (j.find("SKS") != j.end()) {
        j.at("SKS").get_to(p.SKS);
    }
    
    if (j.find("MINI14") != j.end()) {
        j.at("MINI14").get_to(p.MINI14);
    }
    
    if (j.find("MK14") != j.end()) {
        j.at("MK14").get_to(p.MK14);
    }
    
    if (j.find("SCARL") != j.end()) {
        j.at("SCARL").get_to(p.SCARL);
    }

    if (j.find("M762") != j.end()) {
        j.at("M762").get_to(p.M762);
    }

    if (j.find("AWM") != j.end()) {
        j.at("AWM").get_to(p.AWM);
    }

    if (j.find("KAR98") != j.end()) {
        j.at("KAR98").get_to(p.KAR98);
    }

    if (j.find("M24") != j.end()) {
        j.at("M24").get_to(p.M24);
    }

    if (j.find("M16") != j.end()) {
        j.at("M16").get_to(p.M16);
    }

    if (j.find("M249") != j.end()) {
        j.at("M249").get_to(p.M249);
    }

    if (j.find("DP28") != j.end()) {
        j.at("DP28").get_to(p.DP28);
    }

    if (j.find("GROZA") != j.end()) {
        j.at("GROZA").get_to(p.GROZA);
    }

    if (j.find("AUG") != j.end()) {
        j.at("AUG").get_to(p.AUG);
    }

    if (j.find("PAN") != j.end()) {
        j.at("PAN").get_to(p.PAN);
    }

    if (j.find("UZI") != j.end()) {
        j.at("UZI").get_to(p.UZI);
    }

    if (j.find("UMP") != j.end()) {
        j.at("UMP").get_to(p.UMP);
    }

    if (j.find("TOMMY") != j.end()) {
        j.at("TOMMY").get_to(p.TOMMY);
    }
	if (j.find("XSuits ") != j.end()) {
        j.at("XSuits ").get_to(p.Config.Skin.XSuits);
    }

    if (j.find("AKM ") != j.end()) {
        j.at("AKM ").get_to(p.Config.Skin.AKM);
    }
    
    if (j.find("P90 ") != j.end()) {
        j.at("P90 ").get_to(p.Config.Skin.P90);
    }
    
    if (j.find("MG3 ") != j.end()) {
        j.at("MG3 ").get_to(p.Config.Skin.MG3);
    }
    
    if (j.find("QBZ ") != j.end()) {
        j.at("QBZ ").get_to(p.Config.Skin.QBZ);
    }
    
    if (j.find("FAMAS ") != j.end()) {
        j.at("FAMAS ").get_to(p.Config.Skin.FAMAS);
    }
    
    if (j.find("AMR ") != j.end()) {
        j.at("AMR ").get_to(p.Config.Skin.AMR);
    }
    
    if (j.find("SKS ") != j.end()) {
        j.at("SKS ").get_to(p.Config.Skin.SKS);
    }
    
    if (j.find("MINI14 ") != j.end()) {
        j.at("MINI14 ").get_to(p.Config.Skin.MINI14);
    }
    
    if (j.find("MK14 ") != j.end()) {
        j.at("MK14 ").get_to(p.Config.Skin.MK14);
    }

    if (j.find("M16A4 ") != j.end()) {
        j.at("M16A4 ").get_to(p.Config.Skin.M16A4);
    }

    if (j.find("Scar ") != j.end()) {
        j.at("Scar ").get_to(p.Config.Skin.Scar);
    }

    if (j.find("M416 ") != j.end()) {
        j.at("M416 ").get_to(p.Config.Skin.M416);
    }

    if (j.find("Groza ") != j.end()) {
        j.at("Groza ").get_to(p.Config.Skin.Groza);
    }

    if (j.find("AUG ") != j.end()) {
        j.at("AUG ").get_to(p.Config.Skin.AUG);
    }

    if (j.find("M762 ") != j.end()) {
        j.at("M762 ").get_to(p.Config.Skin.M762);
    }

    if (j.find("ACE32 ") != j.end()) {
        j.at("ACE32 ").get_to(p.Config.Skin.ACE32);
    }

    if (j.find("Parachute ") != j.end()) {
        j.at("Parachute ").get_to(p.Config.Skin.Parachute);
    }

    if (j.find("UZI ") != j.end()) {
        j.at("UZI ").get_to(p.Config.Skin.UZI);
    }

    if (j.find("UMP ") != j.end()) {
        j.at("UMP ").get_to(p.Config.Skin.UMP);
    }

    if (j.find("Vector ") != j.end()) {
        j.at("Vector ").get_to(p.Config.Skin.Vector);
    }

    if (j.find("Thompson ") != j.end()) {
        j.at("Thompson ").get_to(p.Config.Skin.Thompson);
    }

    if (j.find("Bizon ") != j.end()) {
        j.at("Bizon ").get_to(p.Config.Skin.Bizon);
    }

    if (j.find("K98 ") != j.end()) {
        j.at("K98 ").get_to(p.Config.Skin.K98);
    }

    if (j.find("M24 ") != j.end()) {
        j.at("M24 ").get_to(p.Config.Skin.M24);
    }

    if (j.find("AWM ") != j.end()) {
        j.at("AWM ").get_to(p.Config.Skin.AWM);
    }

    if (j.find("DP28 ") != j.end()) {
        j.at("DP28 ").get_to(p.Config.Skin.DP28);
    }

    if (j.find("M249 ") != j.end()) {
        j.at("M249 ").get_to(p.Config.Skin.M249);
    }

    if (j.find("Pan ") != j.end()) {
        j.at("Pan ").get_to(p.Config.Skin.Pan);
    }

    if (j.find("Moto ") != j.end()) {
        j.at("Moto ").get_to(p.Config.Skin.Moto);
    }

    if (j.find("CoupeRP ") != j.end()) {
        j.at("CoupeRP ").get_to(p.Config.Skin.CoupeRP);
    }

    if (j.find("UAZ ") != j.end()) {
        j.at("UAZ ").get_to(p.Config.Skin.UAZ);
    }

    if (j.find("Dacia ") != j.end()) {
        j.at("Dacia ").get_to(p.Config.Skin.Dacia);
    }

    if (j.find("Bigfoot ") != j.end()) {
        j.at("Bigfoot ").get_to(p.Config.Skin.Bigfoot);
    }

    if (j.find("Mirado ") != j.end()) {
        j.at("Mirado ").get_to(p.Config.Skin.Mirado);
    }

    if (j.find("OMirado ") != j.end()) {
        j.at("OMirado ").get_to(p.Config.Skin.OMirado);
    }

    if (j.find("Buggy ") != j.end()) {
        j.at("Buggy ").get_to(p.Config.Skin.Buggy);
    }

    if (j.find("MiniBus ") != j.end()) {
        j.at("MiniBus ").get_to(p.Config.Skin.MiniBus);
    }

    if (j.find("Boat ") != j.end()) {
        j.at("Boat ").get_to(p.Config.Skin.Boat);
    }
        if (j.find(("AimBullet")) != j.end()) {
            j.at(("AimBullet")).get_to(p.Config.SilentAim.Enable);
        }
        if (j.find(("AimBot")) != j.end()) {
            j.at(("AimBot")).get_to(p.Config.SilentAim.AimBot);
        }
        if (j.find(("Autofire")) != j.end()) {
            j.at(("Autofire")).get_to(p.Config.SilentAim.Autofire);
        }
        if (j.find(("##Priority")) != j.end()) {
            j.at(("##Priority")).get_to(p.Config.SilentAim.Priority);
        }
        //if (j.find(("##FOV")) != j.end()) {
        //    j.at(("##FOV")).get_to(p.Config.SilentAim.Radius);
        //}
        if (j.find(("##Target")) != j.end()) {
            j.at(("##Target")).get_to(p.Config.SilentAim.Target);
        }
        if (j.find(("##Trigger")) != j.end()) {
            j.at(("##Trigger")).get_to(p.Config.SilentAim.Trigger);
        }
        if (j.find(("Ignore Knocked")) != j.end()) {
            j.at(("Ignore Knocked")).get_to(p.Config.SilentAim.IgnoreKnocked);
        }
        if (j.find(("Ignore Bot")) != j.end()) {
            j.at(("Ignore Bot")).get_to(p.Config.SilentAim.IgnoreBot);
        }
        if (j.find(("Prediction")) != j.end()) {
            j.at(("Prediction")).get_to(p.Config.SilentAim.Prediction);
        }
        if (j.find(("Visibility Check")) != j.end()) {
            j.at(("Visibility Check")).get_to(p.Config.SilentAim.VisCheck);
        }
        if (j.find(("NO Recoil")) != j.end()) {
            j.at(("NO Recoil")).get_to(p.Config.SilentAim.Norecoil);
        }
        if (j.find(("Instant Hit")) != j.end()) {
            j.at(("Instant Hit")).get_to(p.Config.SilentAim.InstantHit);
        }
        if (j.find(("FastShoot")) != j.end()) {
            j.at(("FastShoot")).get_to(p.Config.SilentAim.FastShoot);
        }
        if (j.find(("Hit Effect")) != j.end()) {
            j.at(("Hit Effect")).get_to(p.Config.SilentAim.HitX);
        }
        //if (j.find(("Speed Hack (Beta)")) != j.end()) {
        //    j.at(("Speed Hack (Beta)")).get_to(p.Config.SilentAim.test5);
        //}
    }

    std::string GetFilesDirShit() {
        if (!g_App)
            return "";

        auto activity = g_App->activity;
        if (!activity)
            return "";

        auto vm = activity->vm;
        if (!vm)
            return "";

        auto object = activity->clazz;
        if (!object)
            return "";

        std::string FileDirReal;

        JNIEnv *env;
        vm->AttachCurrentThread(&env, nullptr);
        {
            auto wrapper_class = env->FindClass(("android/content/ContextWrapper"));
            auto methodID = env->GetMethodID(wrapper_class, ("getFilesDir"),
                                             ("()Ljava/io/File;"));
            auto objectFile = env->CallObjectMethod(object, methodID);

            auto classFile = env->GetObjectClass(objectFile);
            auto methodIDPath = env->GetMethodID(classFile, ("getAbsolutePath"),
                                                 ("()Ljava/lang/String;"));
            auto stringPath = (jstring) env->CallObjectMethod(objectFile, methodIDPath);
            auto m_FilesDir = env->GetStringUTFChars(stringPath, nullptr);

            FileDirReal += m_FilesDir;
            FileDirReal += ("/Config.json");

            env->ReleaseStringUTFChars(stringPath, m_FilesDir);

            //LOGI("GetFilesDirShit %s", FileDirReal.c_str());
        }
        vm->DetachCurrentThread();

        return FileDirReal;
    }




    bool isStateChanged = false;
    ////////////////////////////////////////////////////////////////

    void load() {
        std::ifstream ifs(GetFilesDirShit().c_str());
        if (ifs.good()) {
            json j = json::parse(ifs);
            *this = j.get<JsonPreferences>();
        } else
            LOGI("Failed to load preferences from %s", GetFilesDirShit().c_str());
    }

    void save() {
        try {
            json j = *this;
            std::ofstream ofs(GetFilesDirShit().c_str());
            ofs << std::setw(4) << j.dump() << std::endl;
        } catch (std::exception &e) {
            LOGI("Failed to save preferences from %s", GetFilesDirShit().c_str());
        }
    }

} preferences;
