#include "junkcode.h"
#include "hooks.hpp"
#include <math.h>
#include <vector>
#include <cmath>
#include <algorithm> 
#include <cwctype>  
#include "../sdk/spoof.h"
#include "../sdk/ret_spoof.h"
#include <locale>
#include <codecvt>
#include <fstream>
#include <cstdint>
#pragma comment(lib, "Winmm.lib")
bool InGame = 0;
uintptr_t playercontroller;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
bool nega = false; bool nega1 = false; bool nega2 = false;
constexpr auto PI = 3.1415926535897932;
constexpr auto FLOAT_NON_FRACTIONAL = 8388608 /* All single-precision floating point numbers greater than or equal to this have no fractional value. */;
constexpr auto INV_PI = 0.31830988618;
constexpr auto HALF_PI = 1.57079632679;
constexpr auto DEG_TO_RAD = PI / 180;
constexpr auto RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2;
aplayercameramanager* camera_cache;
static AGameObject* SkyDome = nullptr;
ashootercharacter* target_actor;
float fovforantiaim;
#include <unordered_set>
#include <random>
ashootercharacter* actor2;
#include "../DefineSDK.h"
#include <filesystem>
namespace fs = std::filesystem;
#define DefusePercentageMax 6.984602
#define CurrentDefuseSectionMax 2
ucanvas* canvas;
float rainbowTimeZ = 0;

float rainbowTimeZRGB1 = 2;
uworld* world;
uobject* negrito;
float distance;
fvector2d position2;
aplayercameramanager* camera;
aplayercontroller* controller;
aplayercontroller* controller67;
ashootercharacter* pawn;
ashootercharacter* japarms;
float rainbowTimeZHandChams = 0;
typedef NTSTATUS(NTAPI* pNtProtectVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,
    ULONG NewProtect,
    PULONG OldProtect
    );
static constexpr size_t CHAT_MAX_LENGTH = 512;
static constexpr DWORD CURSOR_BLINK_MS = 500; // blink interval
static bool chatTypingActive = false;
static DWORD lastCursorFlip = 0;
static bool cursorOn = true;
static std::array<bool, 256> prevKeyDown = { false };

float fresnelBaseR = 2.093f;
float fresnelBaseG = 0.019f;
float fresnelBaseB = 20.0f;
bool stop_for_shot;
ABP_Sky_Sphere_C* SkyBoxOffsets;



#include <sstream>

#include <fstream>
#include <string>
#include <sstream>

#define SAVE_BOOL(var) file << #var << "=" << var << "\n";
#define SAVE_FLOAT(var) file << #var << "=" << var << "\n";
#define LOAD_BOOL(var) if (line.find(#var) != std::string::npos) var = std::stoi(value); 
#define LOAD_FLOAT(var) if (line.find(#var) != std::string::npos) var = std::stof(value);

void SaveConfig(const std::string& path)
{
    std::ofstream file(path, std::ios::trunc);

    // === MISC ===
    SAVE_BOOL(globals::misc::skiptutorial);
    SAVE_BOOL(globals::misc::skinchangor);

    // === BUDDY ===
    SAVE_BOOL(globals::buddy::enabled);
    SAVE_FLOAT(globals::buddy::index);

    file.close();
}

void LoadConfig(const std::string& path)
{
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line))
    {
        auto delim_pos = line.find('=');
        if (delim_pos == std::string::npos)
            continue;

        std::string value = line.substr(delim_pos + 1);

        // === MISC ===
        LOAD_BOOL(globals::misc::skiptutorial);
        LOAD_BOOL(globals::misc::skinchangor);

        // === BUDDY ===
        LOAD_BOOL(globals::buddy::enabled);
        LOAD_FLOAT(globals::buddy::index);
    }
    file.close();
}



typedef BOOL(WINAPI* tVirtualProtect)(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);

namespace UWorld {
    __forceinline __int64 decrypt_uworld(const uint32_t UWorldKey, const uintptr_t* UWorldState)
    {
        unsigned __int64 v8;
        unsigned __int64 v9;
        unsigned __int64 v10;
        unsigned __int64 v11;
        unsigned int v12;
        unsigned __int64 v13;
        __int64 v14;

        v8 = 0x2545F4914F6CDD1Dull * ((UWorldKey ^ ((UWorldKey ^ (UWorldKey >> 15)) >> 12)) ^ (UWorldKey << 25));
        v9 = v8 % 7;
        v10 = UWorldState[v9];
        v11 = v8 >> 32;
        v12 = (unsigned int)v9 % 7;

        if ((DWORD)v9 == 7 * ((unsigned int)v9 / 7))
        {
            v13 = ~v11 ^ (v10 + (unsigned int)(v11 - 1));
        }
        else
        {
            v13 = UWorldState[v9];
            if (v12 == 1)
            {
                v13 = ((v10 >> ((unsigned __int8)(((int)v11 + 2 * (int)v9) % 0x3F) + 1)) |
                    (v10 << (63 * (unsigned __int8)(((int)v11 + 2 * (int)v9) / 0x3F)
                        - ((unsigned __int8)v11 + 2 * (unsigned __int8)v9) + 63)))
                    - (unsigned int)(v9 + v11);
                goto LABEL_11;
            }
        }

        if (v12 == 2)
        {
            v13 = (((unsigned int)(v11 + 2 * v9) + v13) >> 1) ^
                ((((unsigned int)(v11 + 2 * v9) + v13) >> 1) ^
                    (2 * ((unsigned int)(v11 + 2 * v9) + v13))) & 0xAAAAAAAAAAAAAAAAull;
            goto LABEL_7;
        }

    LABEL_11:
        if ((unsigned int)v9 % 7 == 3)
        {
            v13 = ~(unsigned __int64)(unsigned int)(v9 + v11) ^
                ((v13 >> (63 * (unsigned __int8)(((int)v11 + 2 * (int)v9) / 0x3F)
                    - ((unsigned __int8)v11 + 2 * (unsigned __int8)v9) + 63)) |
                    (v13 << ((unsigned __int8)(((int)v11 + 2 * (int)v9) % 0x3F) + 1)));
            goto LABEL_13;
        }

    LABEL_7:
        if ((unsigned int)v9 % 7 == 5)
        {
            v13 = (((v13 << (63 * (unsigned __int8)(((int)v11 + 2 * (int)v9) / 0x3F)
                - ((unsigned __int8)v11 + 2 * (unsigned __int8)v9) + 63)) |
                (v13 >> ((unsigned __int8)(((int)v11 + 2 * (int)v9) % 0x3F) + 1))) >>
                (63 * (unsigned __int8)(((int)v9 + (int)v11) / 0x3F)
                    - ((unsigned __int8)v9 + (unsigned __int8)v11) + 63)) |
                (((v13 << (63 * (unsigned __int8)(((int)v11 + 2 * (int)v9) / 0x3F)
                    - ((unsigned __int8)v11 + 2 * (unsigned __int8)v9) + 63)) |
                    (v13 >> ((unsigned __int8)(((int)v11 + 2 * (int)v9) % 0x3F) + 1))) <<
                    ((unsigned __int8)(((int)v9 + (int)v11) % 0x3F) + 1));
            goto LABEL_15;
        }

    LABEL_13:
        if ((unsigned int)v9 % 7 == 6)
        {
            v13 = ((v13 << (63 * (unsigned __int8)(((int)v11 + 2 * (int)v9) / 0x3F)
                - ((unsigned __int8)v11 + 2 * (unsigned __int8)v9) + 63)) |
                (v13 >> ((unsigned __int8)(((int)v11 + 2 * (int)v9) % 0x3F) + 1)))
                - (unsigned int)(v9 + v11);
        }

    LABEL_15:
        return v13 ^ (unsigned int)UWorldKey;
    }
}

flinearcolor handcolor(fresnelBaseR, fresnelBaseG, fresnelBaseB, globals::misc::glow_float);
bool hasTarget3 = false;
#pragma once


wchar_t* s2wc(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}

namespace inpute
{
    bool mouseDown[5];
    bool mouseDownAlready[256];

    bool keysDown[256];
    bool keysDownAlready[256];

    bool is_any_mouse_down()
    {
        if (mouseDown[0]) return true;
        if (mouseDown[1]) return true;
        if (mouseDown[2]) return true;
        if (mouseDown[3]) return true;
        if (mouseDown[4]) return true;

        return false;
    }

    bool is_mouse_clicked(int button, int element_id, bool repeat)
    {
        if (mouseDown[button])
        {
            if (!mouseDownAlready[element_id])
            {
                mouseDownAlready[element_id] = true;
                return true;
            }
            if (repeat)
                return true;
        }
        else
        {
            mouseDownAlready[element_id] = false;
        }
        return false;
    }
    bool is_key_pressed(int key, bool repeat)
    {
        if (keysDown[key])
        {
            if (!keysDownAlready[key])
            {
                keysDownAlready[key] = true;
                return true;
            }
            if (repeat)
                return true;
        }
        else
        {
            keysDownAlready[key] = false;
        }
        return false;
    }

    void handle()
    {
        if (GetAsyncKeyState(0x01))
            mouseDown[0] = true;
        else
            mouseDown[0] = false;
    }
}

struct SkinData {
    const wchar_t* SkinName;
    const wchar_t* skin;
    const wchar_t* chroma;
    int level;
};

// Define skin arrays for each weapon type
static const std::vector<SkinData> vandalSkins = {
    //{L"Phaseguard Vandal", L"Default__AK_Commando_PrimaryAsset_C", L"Default__Commando_v1_PrimaryAsset_C", 4},
    {L"Divergence V4ndal", L"Default__AK_Anomaly_PrimaryAsset_C", L"Default__Anomaly_v1_PrimaryAsset_C", 4},
    {L"CYRAX Vandal", L"Default__AK_Syndra_PrimaryAsset_C", L"Default__Syndra_v1_PrimaryAsset_C", 4},
    {L"Primordium Vandal", L"Default__AK_Hellfire_PrimaryAsset_C", L"Default__Hellfire_v2_PrimaryAsset_C", 4},
    {L"Singularity Vandal", L"Default__AK_Edge2_PrimaryAsset_C", L"Default__AK_Edge2_v1_PrimaryAsset_C", 4},
    {L"Aemondir Vandal", L"Default__AK_Legion_PrimaryAsset_C", L"Default__AK_Legion_Lv3_PrimaryAsset_C", 4},
    {L"Evori Dreamwings Vandal", L"Default__AK_StarPower_PrimaryAsset_C", L"Default__StarPower_v3_PrimaryAsset_C", 4},
    {L"Prelude to Chaos Vandal", L"Default__AK_DemonStone_PrimaryAsset_C", L"Default__AK_DemonStone_Lv4_PrimaryAsset_C", 4},
    {L"Reaver Vandal", L"Default__AK_Soulstealer_PrimaryAsset_C", L"Default__AK_Soulstealer_White_PrimaryAsset_C", 4},
    {L"XERØFANG Vandal ", L"Default__AK_Hypedragon_PrimaryAsset_C", L"Default__AK_Hypedragon_v1_PrimaryAsset_C", 4},
    {L"Kuronami Vandal", L"Default__AK_Ninja_PrimaryAsset_C", L"Default__AK_Ninja_v1_PrimaryAsset_C", 4},
    {L"Imperium Vandal", L"Default__AK_Dynasty_PrimaryAsset_C", L"Default__AK_Dynasty_Standard_PrimaryAsset_C", 4},
    {L"Champions 2023 Vandal", L"Default__AK_Champions2023_PrimaryAsset_C", L"Default__AK_Champions2023_Standard_PrimaryAsset_C", 4},
    {L"Magepunk Vandal", L"Default__AK_Magepunk3_PrimaryAsset_C", L"Default__AK_Magepunk3_Standard_PrimaryAsset_C", 4},
    {L"Gaia's Vengeance Vandal", L"Default__AK_Ashen_PrimaryAsset_C", L"Default__AK_Ashen_v2_PrimaryAsset_C", 4},
    {L"RGX 11z Pro Vandal", L"Default__AK_Afterglow_PrimaryAsset_C", L"Default__AK_Afterglow_Blue_PrimaryAsset_C", 5},
    {L"Champions 2021 Vandal", L"Default__AK_Champions_PrimaryAsset_C", L"Default__AK_Champions_Lv4_PrimaryAsset_C", 4},
    {L"Elderflame Vandal", L"Default__AK_Dragon_PrimaryAsset_C", L"Default__AK_Dragon_Blue_PrimaryAsset_C", 4},
    {L"Ion Vandal", L"Default__AK_Oblivion2_PrimaryAsset_C", L"Default__AK_Oblivion2_v1_PrimaryAsset_C", 4},
    {L"ChronoVoid Vandal", L"Default__AK_Daedalus_PrimaryAsset_C", L"Default__AK_Daedalus_v2_PrimaryAsset_C", 4},
    {L"Araxys Vandal", L"Default__AK_Antares_PrimaryAsset_C", L"Default__AK_Antares_Lv4_PrimaryAsset_C", 4},
    {L"Origin Vandal", L"Default__AK_Circle_PrimaryAsset_C", L"Default__AK_Circle_Lv4_PrimaryAsset_C",4},
    {L"Sentinels of Light Vandal", L"Default__AK_SOL_PrimaryAsset_C", L"Default__AK_SOL_Lv4_PrimaryAsset_C", 4},
    {L"Glitchpop Vandal", L"Default__AK_Cyberpunk2_PrimaryAsset_C", L"Default__AK_Cyberpunk2_Red_PrimaryAsset_C", 4},
    {L"Prime Vandal", L"Default__AssaultRifle_AK_HypeBeast_PrimaryAsset_C", L"Default__AssaultRifle_AK_HypeBeast_Blue_PrimaryAsset_C", 4},
    {L"Oni Vandal", L"Default__AK_Oni2_PrimaryAsset_C", L"Default__AK_Oni2_Lv4_PrimaryAsset_C", 4},
    {L"Overdrive Vandal", L"Default__AK_Motorbike_PrimaryAsset_C", L"Default__Motorbike_v2_PrimaryAsset_C", 4},
    {L"EX.O Vandal", L"Default__AK_Hologram_PrimaryAsset_C", L"Default__Hologram_v3_PrimaryAsset_C", 4},
    {L"Valiant Hero Vandal", L"Default__AK_MonkeyKing_PrimaryAsset_C", L"Default__MonkeyKing_v1_PrimaryAsset_C", 4},
    {L"Cryostasis Vandal", L"Default__AK_Permafrost_PrimaryAsset_C", L"Default__Permafrost_v1_PrimaryAsset_C", 4},
    {L"Forsaken Vandal", L"Default__AK_Fallen_PrimaryAsset_C", L"Default__Fallen_v2_PrimaryAsset_C", 4},

};
static const std::vector<SkinData> phantomSkins = {

{L"Bolt Phantom", L"Default__Carbine_Bolt_PrimaryAsset_C", L"Default__Carbine_Bolt_v1_PrimaryAsset_C", 4},
{L"Nocturnum Phantom", L"Default__Carbine_Coven_PrimaryAsset_C", L"Default__Carbine_Coven_V1_PrimaryAsset_C", 4},
{L"Champions 2024 Phantom", L"Default__Carbine_Champions2024_PrimaryAsset_C", L"Default__Carbine_Champions2024_Lv4_PrimaryAsset_C", 4},
{L"Mystbloom Phantom", L"Default__Carbine_Spirit_PrimaryAsset_C", L"Default__Carbine_Spirit_v2_PrimaryAsset_C", 4},
{L"Sovereign Phantom", L"Default__Carbine_Sovereign2_PrimaryAsset_C", L"Default__Carbine_Sovereign2_v1_PrimaryAsset_C", 4},
{L"Singularity Phantom", L"Default__AssaultRifle_ACR_Edge_PrimaryAsset_C", L"Default__AssaultRifle_ACR_Edge_Lv4_PrimaryAsset_C", 4},
{L"Spectrum Phantom", L"Default__Carbine_Atlas_PrimaryAsset_C", L"Default__Carbine_Atlas_v1_PrimaryAsset_C", 4},
{L"Reaver Phantom", L"Default__Carbine_Soulstealer2_PrimaryAsset_C", L"Default__Carbine_Soulstealer2_v1_PrimaryAsset_C", 4},
{L"RGX 11z Pro Phantom", L"Default__Carbine_Afterglow2_PrimaryAsset_C", L"Default__Carbine_Afterglow2_v2_PrimaryAsset_C", 4},
{L"Glitchpop Phantom", L"Default__Carbine_Cyberpunk2_PrimaryAsset_C", L"Default__Carbine_Cyberpunk2_Lv4_PrimaryAsset_C", 4},
{L"Ruination Phantom", L"Default__Carbine_King_PrimaryAsset_C", L"Default__Carbine_King_Lv4_PrimaryAsset_C", 4},
{L"ChronoVoid Phantom", L"Default__Carbine_Daedalus_PrimaryAsset_C", L"Default__Carbine_Daedalus_Lv4_PrimaryAsset_C", 4},
{L"Recon Phantom", L"Default__Carbine_SpecOps_PrimaryAsset_C", L"Default__Carbine_SpecOps_Lv4_PrimaryAsset_C", 4},
{L"BlastX Phantom", L"Default__Carbine_URF_PrimaryAsset_C", L"Default__Carbine_URF_Lv4_PrimaryAsset_C", 4},
{L"Protocol 781-A Phantom", L"Default__Carbine_Protocol_PrimaryAsset_C", L"Default__Carbine_Protocol_Lv4_PrimaryAsset_C", 4},
{L"Oni Phantom", L"Default__AssaultRifle_ACR_Oni_PrimaryAsset_C", L"Default__AssaultRifle_ACR_Oni_Black_PrimaryAsset_C", 4},
{L"Nebula Phantom", L"Default__Carbine_Cosmos_PrimaryAsset_C", L"Default__Carbine_Cosmos_Lv1_PrimaryAsset_C", 4},
{L"Celestial Phantom", L"Default__Carbine_Lunar_PrimaryAsset_C", L"Default__Carbine_Lunar_Lv1_PrimaryAsset_C", 4},

};
//
//
static const std::vector<SkinData> operatorSkins = {
{L"Divergence Operator", L"Default__BoltSniper_Anomaly_PrimaryAsset_C", L"Default__BoltSniper_Anomaly_v1_PrimaryAsset_C", 4},
{L"Mystbloom Operator", L"Default__BoltSniper_Spirit_PrimaryAsset_C", L"Default__BoltSniper_Spirit_v2_PrimaryAsset_C", 4},
{L"Ion Operator", L"Default__BoltSniper_Oblivion_PrimaryAsset_C", L"Default__BoltSniper_OblivionLv4_PrimaryAsset_C", 4},
{L"RGX 11z Pro Operator", L"Default__BoltSniper_Afterglow2_PrimaryAsset_C", L"Default__BoltSniper_Afterglow2_Lv5_PrimaryAsset_C", 4},
{L"Origin Operator", L"Default__BoltSniper_Circle_PrimaryAsset_C", L"Default__BoltSniper_Circle_Lv4_PrimaryAsset_C", 4},
{L"Prelude to Chaos Operator", L"Default__BoltSniper_DemonStone_PrimaryAsset_C", L"Default__BoltSniper_DemonStone_Lv4_PrimaryAsset_C", 4},
{L"Forsaken Operator", L"Default__BoltSniper_Fallen_PrimaryAsset_C", L"Default__BoltSniper_Fallen_Lv4_PrimaryAsset_C", 4},
{L"Glitchpop Operator", L"Default__BoltSniper_Cyberpunk2_PrimaryAsset_C", L"Default__BoltSniper_Cyberpunk2_Lv4_PrimaryAsset_C", 4},
{L"Radiant Entertainment System Operator", L"Default__BoltSniper_Arcade_PrimaryAsset_C", L"Default__BoltSniper_Arcade_Lv4_PrimaryAsset_C", 4},
{L"Elderflame Operator", L"Default__BoltSniper_Dragon_PrimaryAsset_C", L"Default__BoltSniper_Dragon_Dark_PrimaryAsset_C", 4},
{L"Sentinels of Light Operator", L"Default__BoltSniper_SOL_PrimaryAsset_C", L"Default__BoltSniper_SOL_Lv4_PrimaryAsset_C", 4},
{L"Reaver Operator", L"Default__BoltSniper_Soulstealer_PrimaryAsset_C", L"Default__BoltSniper_Soulstealer_Black_PrimaryAsset_C", 4},
{L"Tethered Realms Operator", L"Default__BoltSniper_SovWorld_PrimaryAsset_C", L"Default__BoltSniper_SovWorld_Lv1_PrimaryAsset_C", 4},
{L"Araxys Operator", L"Default__BoltSniper_Antares_PrimaryAsset_C", L"Default__BoltSniper_Antares_Lv4_PrimaryAsset_C", 4},
{L"Gravitational Uranium Neuroblaster Operator", L"Default__BoltSniper_Raygun_PrimaryAsset_C", L"Default__BoltSniper_Raygun_Lv2_PrimaryAsset_C", 4},
{L"Magepunk Operator", L"Default__BoltSniper_Magepunk2_v1_PrimaryAsset_C", L"Default__BoltSniper_Magepunk2_Lv4_PrimaryAsset_C", 4},

};
//
static const std::vector<SkinData> bulldogSkins = {
{L"Phaseguard Bulldog", L"Default__Burst_Commando_PrimaryAsset_C", L"Default__Commando_v1_PrimaryAsset_C", 4},
{L"Nocturnum Bulldog", L"Default__Burst_Coven_PrimaryAsset_C", L"Default__Burst_Coven_v1_PrimaryAsset_C", 4},
{L"Glitchpop Bulldog", L"Default__AssaultRifle_Burst_Cyberpunk_PrimaryAsset_C", L"Default__AssaultRifle_Burst_Cyberpunk_Lv4_PrimaryAsset_C", 4},
{L"Spectrum Bulldog", L"Default__Burst_Atlas_PrimaryAsset_C", L"Default__Burst_Atlas_v2_PrimaryAsset_C", 4},
{L"Radiant Entertainment System Bulldog", L"Default__Burst_Arcade_v2_PrimaryAsset_C", L"Default__Burst_Arcade_Lv4_PrimaryAsset_C", 4},
};
//
static const std::vector<SkinData> frenzySkins = {

{L"Sovereign Frenzy", L"Default__AutoPistol_Sovereign2_PrimaryAsset_C", L"Default__AutoPistol_Sovereign2_v1_PrimaryAsset_C", 4},
{L"Elderflame Frenzy", L"Default__AutomaticPistol_Dragon_PrimaryAsset_C", L"Default__AutomaticPistol_Dragon_Blue_PrimaryAsset_C", 4},
{L"Glitchpop Frenzy", L"Default__AutomaticPistol_Cyberpunk_PrimaryAsset_C", L"Default__AutomaticPistol_Cyberpunk_Blue_PrimaryAsset_C", 4},
{L"BlastX Frenzy", L"Default__AutoPistol_URF_PrimaryAsset_C", L"Default__AutoPistol_URF_Standard_PrimaryAsset_C", 4},
{L"Prime//2.0 Frenzy", L"Default__AutomaticPistol_HypeBeast2_PrimaryAsset_C", L"Default__AutomaticPistol_HypeBeast2_PrimaryAsset_C", 4},
{L"Ion Frenzy", L"Default__AutoPistol_Oblivion2_PrimaryAsset_C", L"Default__AutoPistol_Oblivion2_Lv4_PrimaryAsset_C", 4},
{L"Oni Frenzy", L"Default__AutoPistol_Oni2_PrimaryAsset_C", L"Default__AutoPistol_Oni2_PrimaryAsset_C", 4},
{L"Origin Frenzy", L"Default__AutoPistol_Circle_PrimaryAsset_C", L"Default__AutoPistol_Circle_Lv4_PrimaryAsset_C", 4},
{L"RGX 11z Pro Frenzy", L"Default__AutoPistol_Afterglow_PrimaryAsset_C", L"Default__AutoPistol_Afterglow_Lv4_PrimaryAsset_C", 4},

};
//
static const std::vector<SkinData> guardianSkins = {

{L"Prime Guardian", L"Default__DMR_HypeBeast_PrimaryAsset_C", L"Default__DMR_HypeBeast_Lv4_PrimaryAsset_C", 4},
{L"Reaver Guardian", L"Default__DMR_SoulStealer_PrimaryAsset_C", L"Default__DMR_SoulStealer_Lv4_PrimaryAsset_C", 4},
{L"Ruination Guardian", L"Default__DMR_King_PrimaryAsset_C", L"Default__DMR_King_Lv4_PrimaryAsset_C", 4},
{L"Sovereign Guardian", L"Default__DMR_Sovereign_PrimaryAsset_C", L"Default__DMR_Sovereign_Lv4_PrimaryAsset_C", 4},
{L"RGX 11z Pro Guardian", L"Default__DMR_Afterglow_PrimaryAsset_C", L"Default__DMR_Afterglow_Lv4_PrimaryAsset_C", 4},
{L"Oni Guardian", L"Default__DMR_Oni_PrimaryAsset_C", L"Default__DMR_Oni_Lv4_PrimaryAsset_C", 4},

};
//
static const std::vector<SkinData> sheriffSkins = {

{L"Doombringer Sheriff", L"Default__Revolver_Cyberknight_PrimaryAsset_C", L"Default__Revolver_Cyberknight_v1_PrimaryAsset_C", 4},
{L"Neo Frontier Sheriff", L"Default__Revolver_Gunslinger_PrimaryAsset_C", L"Default__Revolver_Gunslinger_v1_PrimaryAsset_C", 4},
{L"RGX 11z Pro Sheriff", L"Default__Revolver_Afterglow3_PrimaryAsset_C", L"Default__Revolver_Afterglow3_v2_PrimaryAsset_C", 4},
{L"Mystbloom Sheriff", L"Default__Revolver_Spirit_PrimaryAsset_C", L"Default__Revolver_Spirit_v2_PrimaryAsset_C", 4},
{L"Kuronami Sheriff", L"Default__Revolver_Ninja_PrimaryAsset_C", L"Default__Revolver_Ninja_v1_PrimaryAsset_C", 4},
{L"Reaver Sheriff", L"Default__RevolverPistol_Soulstealer_PrimaryAsset_C", L"Default__RevolverPistol_Soulstealer_White_PrimaryAsset_C", 4},
{L"Singularity Sheriff", L"Default__RevolverPistol_Edge_PrimaryAsset_C", L"Default__RevolverPistol_Edge_Lv4_PrimaryAsset_C", 4},
{L"Protocol 781-A Sheriff", L"Default__Revolver_Protocol_PrimaryAsset_C", L"Default__Revolver_Protocol_Lv4_PrimaryAsset_C", 4},
{L"Sentinels of Light Sheriff", L"Default__Revolver_SOL_PrimaryAsset_C", L"Default__Revolver_SOL_Lv4_PrimaryAsset_C", 4},
{L"ChronoVoid Sheriff", L"Default__Revolver_Daedalus_PrimaryAsset_C", L"Default__Revolver_Daedalus_Lv4_PrimaryAsset_C", 4},
{L"Magepunk Sheriff", L"Default__Revolver_Magepunk2_PrimaryAsset_C", L"Default__Revolver_Magepunk2_Lv4_PrimaryAsset_C", 4},
{L"Nebula Sheriff", L"Default__Revolver_Cosmos_PrimaryAsset_C", L"Default__Revolver_Cosmos_Lv1_PrimaryAsset_C", 4},
{L"Arcane Sheriff", L"Default__Revolver_XP1_PrimaryAsset_C", L"Default__Revolver_XP1_Lv2_PrimaryAsset_C", 4},
{L"Schema Sheriff", L"Default__Revolver_Schema_PrimaryAsset_C", L"Default__Revolver_Schema_Lv1_PrimaryAsset_C", 4},
{L"Crimsonbeast Sheriff", L"Default__Revolver_Mythic_PrimaryAsset_C", L"Default__Revolver_Mythic_Lv2_PrimaryAsset_C", 4},
{L"Signature Sheriff", L"Default__Revolver_MidnightAerosol_PrimaryAsset_C", L"Default__Revolver_MidnightAerosol_PrimaryAsset_C", 4},
{L"Abyssal Sheriff", L"Default__Revolver_DeepSea_PrimaryAsset_C", L"Default__Revolver_DeepSea_Lv1_PrimaryAsset_C", 4},
{L"Ion Sheriff", L"Default__RevolverPistol_Oblivion_PrimaryAsset_C", L"Default__RevolverPistol_OblivionLv4_PrimaryAsset_C", 4},

};
static const std::vector<SkinData> ghostSkins = {
{L"Phaseguard Ghost", L"Default__Luger_Commando_PrimaryAsset_C", L"Default__Commando_v1_PrimaryAsset_C", 4},
{L"Reaver Ghost", L"Default__Luger_Soulstealer2_PrimaryAsset_C", L"Default__Luger_Soulstealer2_v1_PrimaryAsset_C", 4},
{L"XERØFANG Ghost", L"Default__Luger_Hypedragon_PrimaryAsset_C", L"Default__Luger_Hypedragon_v1_PrimaryAsset_C", 4},
{L"Sovereign Ghost", L"Default__LugerPistol_Sovereign_PrimaryAsset_C", L"Default__LugerPistol_Sovereign_Purple_PrimaryAsset_C", 4},
{L"Ruination Ghost", L"Default__Luger_King_PrimaryAsset_C", L"Default__Luger_King_Lv4_PrimaryAsset_C", 4},
{L"Magepunk Ghost", L"Default__Luger_Magepunk_PrimaryAsset_C", L"Default__Luger_Magepunk_Lv4_PrimaryAsset_C", 4},
{L"Gaia's Vengeance Ghost", L"Default__LugerPistol_Ashen_PrimaryAsset_C", L"Default__LugerPistol_Ashen_Lv4_PrimaryAsset_C", 4},

};
//
static const std::vector<SkinData> spectreSkins = {
{L"Kuronami Spectre", L"Default__MP5_Ninja_PrimaryAsset_C", L"Default__MP5_Ninja_v1_PrimaryAsset_C", 4},
{L"Ruination Spectre", L"Default__MP5_King_PrimaryAsset_C", L"Default__MP5_King_Lv4_PrimaryAsset_C", 4},
{L"Protocol 781-A Spectre", L"Default__MP5_Protocol_PrimaryAsset_C", L"Default__MP5_Protocol_Lv4_PrimaryAsset_C", 4},
{L"Reaver Spectre", L"Default__MP5_Soulstealer2_PrimaryAsset_C", L"Default__MP5_Soulstealer2_Lv4_PrimaryAsset_C", 4},
{L"Radiant Crisis 001 Spectre", L"Default__MP5_Comicbook_PrimaryAsset_C", L"Default__MP5_Comicbook_Lv3_PrimaryAsset_C", 4},
};
//
static const std::vector<SkinData> classicSkins = {
{L"VCT x SEN Classic", L"Default__BasePistol_VCTCaps24_SEN_PrimaryAsset_C", L"Default__BasePistol_VCTCaps24_SEN_V1_PrimaryAsset_C", 4},
{L"VCT x G2 Classic", L"Default__BasePistol_VCTCaps24_G2_PrimaryAsset_C", L"Default__BasePistol_VCTCaps24_G2_Lv3_PrimaryAsset_C", 4},
{L"VCT x BBL Classic", L"Default__BasePistol_VCTCaps24_BBL_PrimaryAsset_C", L"Default__BasePistol_VCTCaps24_BBL_Lv3_PrimaryAsset_C", 4},
{L"Spectrum Classic", L"Default__BasePistol_Atlas_PrimaryAsset_C", L"Default__BasePistol_Atlas_v1_PrimaryAsset_C", 4},
{L"Prime Classic", L"Default__BasePistol_HypeBeast_PrimaryAsset_C", L"Default__BasePistol_HypeBeast_Blue_PrimaryAsset_C", 4},
{L"RGX 11z Pro Classic", L"Default__BasePistol_Afterglow2_PrimaryAsset_C", L"Default__BasePistol_Afterglow2_Lv4_PrimaryAsset_C", 4},
{L"Forsaken Classic", L"Default__BasePistol_Fallen_PrimaryAsset_C", L"Default__BasePistol_Fallen_Lv3_PrimaryAsset_C", 4},
{L"Glitchpop Classic", L"Default__BasePistol_Cyberpunk2_PrimaryAsset_C", L"Default__BasePistol_Cyberpunk2_Lv4_PrimaryAsset_C", 4},
};
//
static const std::vector<SkinData> marshalSkins = {
{L"Nocturnum Marshal", L"Default__LeverSniper_Coven_PrimaryAsset_C", L"Default__LeverSniper_Coven_V1_PrimaryAsset_C", 4},
{L"Kuronami Marshal", L"Default__LeverSniper_Ninja_PrimaryAsset_C", L"Default__LeverSniper_Ninja_v1_PrimaryAsset_C", 4},
{L"Sovereign Marshal", L"Default__LeverSniperRifle_Sovereign_PrimaryAsset_C", L"Default__LeverSniperRifle_Sovereign_Purple_PrimaryAsset_C", 4},
};
//
//static const std::vector<SkinData> judgeSkins = {
//	{L"Default__AutomaticShotgun_Soulstealer_PrimaryAsset_C", L"Default__AutomaticShotgun_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Dragon_PrimaryAsset_C", L"Default__AutomaticShotgun_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Ninja_PrimaryAsset_C", L"Default__AutomaticShotgun_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Sovereign_PrimaryAsset_C", L"Default__AutomaticShotgun_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Oni_PrimaryAsset_C", L"Default__AutomaticShotgun_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> ariesSkins = {
//	{L"Default__LMG_SOL_PrimaryAsset_C", L"Default__LMG_SOL_Lv4_PrimaryAsset_C", 4},
//	{L"Default__LMG_Dragon_PrimaryAsset_C", L"Default__LMG_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__LMG_Ninja_PrimaryAsset_C", L"Default__LMG_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__LMG_Soulstealer_PrimaryAsset_C", L"Default__LMG_Soulstealer_Lv4_PrimaryAsset_C", 4},
//	{L"Default__LMG_Oni_PrimaryAsset_C", L"Default__LMG_Oni_Lv4_PrimaryAsset_C", 4},
//};
//	
//static const std::vector<SkinData> odinSkins = {
//	{L"Default__HMG_Soulstealer_PrimaryAsset_C", L"Default__HMG_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__HMG_Dragon_PrimaryAsset_C", L"Default__HMG_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__HMG_Ninja_PrimaryAsset_C", L"Default__HMG_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__HMG_Sovereign_PrimaryAsset_C", L"Default__HMG_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__HMG_Oni_PrimaryAsset_C", L"Default__HMG_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> buckySkins = {
//	{L"Default__PumpShotgun_Soulstealer_PrimaryAsset_C", L"Default__PumpShotgun_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Dragon_PrimaryAsset_C", L"Default__PumpShotgun_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Ninja_PrimaryAsset_C", L"Default__PumpShotgun_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Sovereign_PrimaryAsset_C", L"Default__PumpShotgun_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Oni_PrimaryAsset_C", L"Default__PumpShotgun_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> shortySkins = {
//	{L"Default__SawedOffShotgun_Soulstealer_PrimaryAsset_C", L"Default__SawedOffShotgun_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Dragon_PrimaryAsset_C", L"Default__SawedOffShotgun_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Ninja_PrimaryAsset_C", L"Default__SawedOffShotgun_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Sovereign_PrimaryAsset_C", L"Default__SawedOffShotgun_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Oni_PrimaryAsset_C", L"Default__SawedOffShotgun_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> stingerSkins = {
//	{L"Default__Vector_Soulstealer_PrimaryAsset_C", L"Default__Vector_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__Vector_Dragon_PrimaryAsset_C", L"Default__Vector_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__Vector_Ninja_PrimaryAsset_C", L"Default__Vector_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__Vector_Sovereign_PrimaryAsset_C", L"Default__Vector_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__Vector_Oni_PrimaryAsset_C", L"Default__Vector_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
static const std::vector<SkinData> knifeskins = {
{L"Phaseguard Splitter", L"Default__Melee_Commando_PrimaryAsset_C", L"Default__Melee_Commando_v1_PrimaryAsset_C", 2},
{L"Beta Remastered", L"Default__Melee_Warring_PrimaryAsset_C", L"Default__Melee_Warring_v1_PrimaryAsset_C", 2},
{L"Divergence St4ff", L"Default__Melee_Anomaly_PrimaryAsset_C", L"Default__Melee_Anomaly_v1_PrimaryAsset_C", 2},
{L"Helix Daggers", L"Default__Melee_Snake_PrimaryAsset_C", L"Default__Melee_Snake_v2_PrimaryAsset_C", 2},
{L"Blades of Primordia", L"Default__Melee_Hellfire_PrimaryAsset_C", L"Default__Melee_Hellfire_v2_PrimaryAsset_C", 2},
{L"Bolt Knife", L"Default__Melee_Bolt_PrimaryAsset_C", L"Default__Melee_Bolt_v1_PrimaryAsset_C", 2},
{L"CYRAX Fanblade", L"Default__Melee_Syndra_PrimaryAsset_C", L"Default__Melee_Syndra_v1_PrimaryAsset_C", 2},
{L"VCT 2025 Karambit", L"Default__Melee_VCT25Season_PrimaryAsset_C", L"Default__Melee_VCT25Season_v1_PrimaryAsset_C", 2},
{L"EX.O Edge", L"Default__Melee_Hologram_PrimaryAsset_C", L"Default__Melee_Hologram_v3_PrimaryAsset_C", 2},
{L"Doombringer Battleaxe", L"Default__Melee_Cyberknight_PrimaryAsset_C", L"Default__Melee_Cyberknight_v1_PrimaryAsset_C", 2},
{L"Neo Frontier Axe", L"Default__Melee_Gunslinger_PrimaryAsset_C", L"Default__Gunslinger_Syndra_v1_PrimaryAsset_C", 2},
{L"Evori's Spellcaster", L"Default__Melee_StarPower_PrimaryAsset_C", L"Default__Melee_StarPower_v1_PrimaryAsset_C", 2},
{L"Singularity Butterfly Knife", L"Default__Melee_Edge2_PrimaryAsset_C", L"Default__Melee_Edge2_v1_PrimaryAsset_C", 2},
{L"Nocturnum Scythe", L"Default__Melee_Coven_PrimaryAsset_C", L"Default__Melee_Coven_v1_PrimaryAsset_C", 2},
{L"Champions 2024 Blade", L"Default__Melee_Champions2024_PrimaryAsset_C", L"Default__Melee_Champions2024_Lv3_PrimaryAsset_C", 2},
{L"RGX 11z Pro Karambit", L"Default__Melee_Afterglow3_PrimaryAsset_C", L"Default__Melee_Afterglow3_v2_PrimaryAsset_C", 2},
{L"Mystbloom Kunai", L"Default__Melee_Spirit_PrimaryAsset_C", L"Default__Melee_Spirit_v2_PrimaryAsset_C", 2},
{L"Eternal Sovereign", L"Default__Melee_Sovereign2_PrimaryAsset_C", L"Default__Melee_Sovereign2_v1_PrimaryAsset_C", 2},
{L"Waveform", L"Default__Melee_Atlas_PrimaryAsset_C", L"Default__Melee_Atlas_v1_PrimaryAsset_C", 2},
{L"XERØFANG Knife", L"Default__Melee_Hypedragon_PrimaryAsset_C", L"Default__Melee_Hypedragon_v2_PrimaryAsset_C", 2},
{L"Kuronami no Yaiba", L"Default__Melee_Ninja_PrimaryAsset_C", L"Default__Melee_Ninja_V1_PrimaryAsset_C", 2},
{L"Champions 2023 Kunai", L"Default__Melee_Champions2023_PrimaryAsset_C", L"Default__Melee_Champions2023_PrimaryAsset_C", 2},
{L"Magepunk Sparkswitch", L"Default__Melee_Magepunk3_PrimaryAsset_C", L"Default__Melee_Magepunk3_PrimaryAsset_C", 2},
{L"VCT LOCK//IN Misericórdia", L"Default__Melee_Esportsinvitational_PrimaryAsset_C", L"Default__Melee_Esportsinvitational_Standard_PrimaryAsset_C", 2},
{L"Champions 2021 Karambit", L"Default__Melee_Champions_PrimaryAsset_C", L"Default__Melee_Champions_Lv2_PrimaryAsset_C", 2},
{L"Reaver Karambit", L"Default__Melee_Soulstealer2_PrimaryAsset_C", L"Default__Melee_Soulstealer2_v1_PrimaryAsset_C", 2},
{L"Black.Market Butterfly Knife", L"Default__Melee_Infantry2_Lv2_PrimaryAsset_C", L"Default__Melee_Infantry2_PrimaryAsset_C", 2},
{L"RGX 11z Pro Firefly", L"Default__Melee_Afterglow2_PrimaryAsset_C", L"Default__Melee_Afterglow2_v2_PrimaryAsset_C", 2},
{L"Xenohunter Knife", L"Default__Melee_Alien_PrimaryAsset_C", L"Default__Melee_Alien_Lv2_PrimaryAsset_C", 2},
{L"Prime//2.0 Karambit", L"Default__Melee_HypeBeast2_PrimaryAsset_C", L"Default__Melee_HypeBeast2_Lv2_PrimaryAsset_C", 2},
{L"Reaver Knife", L"Default__Melee_Soulstealer_PrimaryAsset_C", L"Default__Melee_Soulstealer_Lv2_PrimaryAsset_C", 2},
{L"Radiant Crisis 001 Baseball Bat", L"Default__Melee_Comicbook_PrimaryAsset_C", L"Default__Melee_Comicbook_Lv2_PrimaryAsset_C", 2},
//{L"NOT FOUND", L"Default__Melee_Dragon_PrimaryAsset_C", L"Default__Melee_Dragon_Lv2_PrimaryAsset_C", 2},
{L"Araxys Bio Harvester", L"Default__Melee_Antares_v2_PrimaryAsset_C", L"Default__Melee_Antares_Lv2_PrimaryAsset_C", 2},
{L"Soulstrife Scythe", L"Default__Melee_Haunted_PrimaryAsset_C", L"Default__Melee_Haunted_Lv2_PrimaryAsset_C", 2},
{L"Crimsonbeast Hammer", L"Default__Melee_Mythic_PrimaryAsset_C", L"Default__Melee_Mythic_Lv2_PrimaryAsset_C", 2},
{L"Magepunk Shock Gauntlet", L"Default__Melee_Magepunk2_PrimaryAsset_C", L"Default__Melee_Magepunk2_Lv2_PrimaryAsset_C", 2},
//{L"NOT FOUND", L"Default__Melee_Oni_PrimaryAsset_C", L"Default__Melee_Oni_Lv2_PrimaryAsset_C", 2},
{L"Onimaru Kunitsuna", L"Default__Melee_Oni2_PrimaryAsset_C", L"Default__Melee_Oni2_Lv2_PrimaryAsset_C", 2},
{L"Forsaken Ritual Blade", L"Default__Melee_Fallen_Lv2_PrimaryAsset_C", L"Default__Melee_Fallen_PrimaryAsset_C", 2},
{L"Blade of Chaos", L"Default__Melee_DemonStone_PrimaryAsset_C", L"Default__Melee_DemonStone_v2_PrimaryAsset_C", 2},
};

static const std::vector<SkinData> outlawskins = {
    {L"NIGGA",L"Default__DS_Gun_Afterglow3_PrimaryAsset_C", L"Default__DS_Gun_Afterglow3_v2_PrimaryAsset_C", 2},
};

static const std::vector<SkinData> chamspions_sheriff = {
    {L"NIGGA",L"Default__AK_Champions_PrimaryAsset_C", L"Default__AK_Champions_Lv4_PrimaryAsset_C", 2},
};
static int vandalSkinOption = 0;
static int sheriffSkinOption = 0;
static int guardianSkinOption = 0;
static int frenzySkinOption = 0;
static int bulldogSkinOption = 0;
static int operatorSkinOption = 0;
static int phantomSkinOption = 0;
static int ghostSkinOption = 0;
static int spectreSkinOption = 0;
static int classicSkinOption = 0;
static int marshalSkinOption = 0;
static int knifeSkinOption = 0;
static int outlawSkinOption = 0;
static int selectedSkinIndex = 0;
float rainbowTimeZCH = 0;
uobject* get_finisher_from_skin(std::wstring skinData) {
    std::wstring assetName = skinData;
    const std::wstring defaultPrefix = crypt(L"Default__").decrypt();
    if (assetName.find(defaultPrefix) == 0) {
        assetName = assetName.substr(defaultPrefix.length());
    }

    size_t firstUnderscore = assetName.find(L'_');
    size_t lastUnderscore = assetName.rfind(L"_PrimaryAsset_C");

    if (firstUnderscore == std::wstring::npos || lastUnderscore == std::wstring::npos || lastUnderscore <= firstUnderscore) {
        return nullptr;
    }

    std::wstring skinNameW = assetName.substr(firstUnderscore + 1, lastUnderscore - firstUnderscore - 1);
    std::string skinName(skinNameW.begin(), skinNameW.end());

    std::string obj = crypt("FXC_Finisher_").decrypt() + skinName + crypt("_Victim_C").decrypt();
    std::wstring wobj(obj.begin(), obj.end());
    wprintf(L"\n wobj: %ls", wobj.c_str());

    uobject* effect = uobject::find_object<uobject*>(wobj.c_str(), reinterpret_cast<uobject*>(-1));

    if (!effect && !skinName.empty()) {
        while (!skinName.empty() && std::isdigit(skinName.back())) {
            skinName.pop_back();
        }

        obj = crypt("FXC_Finisher_").decrypt() + skinName + crypt("_Victim_C").decrypt();
        wobj = std::wstring(obj.begin(), obj.end());
        printf("\n wobj: %s", wobj);
        effect = uobject::find_object<uobject*>(wobj.c_str(), reinterpret_cast<uobject*>(-1));
    }

    return effect;
}



using FinisherFn = void* (__fastcall*)(uintptr_t);

inline void* PlayFinisherEffect(uintptr_t effect)
{
    
    static void* (__fastcall * fn)(uintptr_t) = nullptr;
    if (!fn)
        fn = reinterpret_cast<FinisherFn>(memory::module_base + offsets::play_finisher_effect);

    return fn(effect);
}




namespace menu
{
    uobject* font;

    flinearcolor RGBtoFLC(float r, float g, float b)
    {
        return { r / 255, g / 255, b / 255, 1 };
    }


    flinearcolor HSVtoRGB(float h, float s, float v) {
        float r, g, b;

        int i = static_cast<int>(h * 6);
        float f = h * 6 - i;
        float p = v * (1 - s);
        float q = v * (1 - f * s);
        float t = v * (1 - (1 - f) * s);

        switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        default: r = g = b = 0.0f;
        }

        return flinearcolor{ r, g, b, 1.0f };

    }

    // x9 ware
    /*namespace Colors
    {
        flinearcolor Text{ 192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f, 255.0f / 255.0f }; //
        flinearcolor Text_Shadow{ 0.0f, 0.0f, 0.0f, 1.0f };
        flinearcolor Text_Outline{ 0.0f, 0.0f, 0.0f, 1.0f };
        flinearcolor Text_Active = RGBtoFLC(184, 51, 255);  // Updated purple

        flinearcolor Button_Idle{ 10.0 / 255.0f, 10.0 / 255.0f, 10.0 / 255.0f, 0.8f }; //
        flinearcolor Button_Hovered = RGBtoFLC(7, 7, 7);
        flinearcolor Button_Active = RGBtoFLC(184, 51, 255);  // Updated purple

        flinearcolor Checkbox_Idle = RGBtoFLC(15, 15, 15);
        flinearcolor Checkbox_Hovered = RGBtoFLC(20, 20, 20);
        flinearcolor Checkbox_Enabled = RGBtoFLC(184, 51, 255); // Updated purple

        flinearcolor Combobox_Idle{ 200.0f / 255.0f, 150.0f / 255.0f, 40.0f / 255.0f };
        flinearcolor Combobox_Hovered{ 200.0f / 255.0f, 150.0f / 255.0f, 40.0f / 255.0f };
        flinearcolor Combobox_Elements{ 0.239f, 0.42f, 0.0f, 0.5f };

        flinearcolor Slider_Idle = RGBtoFLC(4, 4, 4);
        flinearcolor Slider_Hovered = RGBtoFLC(14, 14, 14);
        flinearcolor Slider_Progress = RGBtoFLC(184, 51, 255);  // Updated purple
        flinearcolor Slider_Button = RGBtoFLC(184, 51, 255);  // Updated purple

        flinearcolor ColorPicker_Background{ 0.006f, 0.006f, 0.006f, 0.4f };
    }*/

#define DEG_TO_RAD (3.14159265358979323846f / 180.0f)
#define RAD_TO_DEG (180.0f / 3.14159265358979323846f)

    inline fvector angle_to_vector(const fvector& angle) {
        
        float pitch = angle.x * DEG_TO_RAD;
        float yaw = angle.y * DEG_TO_RAD;

        float cp = cosf(pitch);
        float sp = sinf(pitch);
        float cy = cosf(yaw);
        float sy = sinf(yaw);

        return fvector(cp * cy, cp * sy, sp);
    }

    inline fvector vector_to_angle(const fvector& vec) {
        
        float hyp = sqrtf(vec.x * vec.x + vec.y * vec.y);
        float pitch = atanf(vec.z / hyp) * RAD_TO_DEG;
        float yaw = atan2f(vec.y, vec.x) * RAD_TO_DEG;
        return fvector(pitch, yaw, 0.f);
    }

    inline void normalize(fvector& vec) {
        
        float len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
        if (len > 0.0001f) {
            vec.x /= len;
            vec.y /= len;
            vec.z /= len;
        }
    }

    namespace Colors
    {
        flinearcolor Text{ 192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f, 255.0f / 255.0f }; //
        flinearcolor Text_Shadow{ 0.0f, 0.0f, 0.0f, 1.0f };
        flinearcolor Text_Outline{ 0.0f, 0.0f, 0.0f, 1.0f };
        flinearcolor Text_Active{ 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.8f };

        flinearcolor Button_Idle{ 10.0 / 255.0f, 10.0 / 255.0f, 10.0 / 255.0f, 0.8f / 255.0f }; //
        flinearcolor Button_Hovered{ 15.0f / 255.0f, 15.0f / 255.0f, 15.0f / 255.0f, 1.f };
        flinearcolor Button_Active{ 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.8f };

        flinearcolor Checkbox_Idle = RGBtoFLC(15, 15, 15);
        flinearcolor Checkbox_Hovered = RGBtoFLC(20, 20, 20);
        flinearcolor Checkbox_Enabled = RGBtoFLC(128, 128, 128); //

        flinearcolor Combobox_Idle{ 200.0f / 255.0f, 150.0f / 255.0f, 40.0f / 255.0f };
        flinearcolor Combobox_Hovered{ 200.0f / 255.0f, 150.0f / 255.0f, 40.0f / 255.0f };
        flinearcolor Combobox_Elements{ 0.239f, 0.42f, 0.0f, 0.5f };

        flinearcolor Slider_Idle = RGBtoFLC(4, 4, 4);
        flinearcolor Slider_Hovered = RGBtoFLC(14, 14, 14);
        flinearcolor Slider_Progress = RGBtoFLC(128, 128, 128);
        flinearcolor Slider_Button = RGBtoFLC(128, 128, 128);

        flinearcolor ColorPicker_Background{ 0.006f, 0.006f, 0.006f, 0.4f };
    }

    namespace PostRenderer
    {
        struct DrawList
        {
            int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
            fvector2d pos;
            fvector2d size;
            flinearcolor color;
            const wchar_t* name;
            bool outline;

            fvector2d from;
            fvector2d to;
            int thickness;
        };
        DrawList drawlist[128];

        void drawFilledRect(fvector2d pos, float w, float h, flinearcolor color)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 1;
                    drawlist[i].pos = pos;
                    drawlist[i].size = fvector2d{ w, h };
                    drawlist[i].color = color;
                    return;
                }
            }
        }

        void TextFunction(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
            
            canvas->k2_drawtext(font, text, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
        }

        void TextCustom(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor text_color, fvector2d position, float width_scale, float height_scale, float thickness, float scale_factor) {

            
            float text_scale_x = width_scale * scale_factor;
            float text_scale_y = height_scale * scale_factor;
            canvas->k2_drawtext(
                font,
                text,
                position,
                { text_scale_x, text_scale_y },
                text_color,
                0.f,
                { 0, 0, 0, 0.30f },
                { 0, 0 },
                true,
                true,
                true,
                { 0, 0, 0, 0.45f }
            );
        }


        void TextLeft(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 2;
                    drawlist[i].name = name;
                    drawlist[i].pos = pos;
                    drawlist[i].outline = outline;
                    drawlist[i].color = color;
                    return;
                }
            }
        }
        void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 3;
                    drawlist[i].name = name;
                    drawlist[i].pos = pos;
                    drawlist[i].outline = outline;
                    drawlist[i].color = color;
                    return;
                }
            }
        }
        void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 4;
                    drawlist[i].from = from;
                    drawlist[i].to = to;
                    drawlist[i].thickness = thickness;
                    drawlist[i].color = color;
                    return;
                }
            }
        }

        void DrawLine2(ucanvas* nigga, fvector2d from, fvector2d to, int thickness, flinearcolor color)
        {
            
            nigga->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
        }

        void MainLineOn(ucanvas* canvas, const fvector2d& start, const fvector2d& end, const flinearcolor& color, float& line_thickness) {
            
            if (!canvas) return;

            canvas->k2_drawline(
                fvector2d{ start.x, start.y },
                fvector2d{ end.x, end.y },
                1.0f,
                color
            );
        }
    }

    ucanvas* canvas;


    bool hover_element = false;
    fvector2d menu_pos = fvector2d{ 0, 0 };
    float offset_x = 0.0f;
    float offset_y = 0.0f;
    float offset_tab1 = 120.0f;
    float offset_tab2 = 325.0f;


    fvector2d first_element_pos = fvector2d{ 0, 0 };

    fvector2d last_element_pos = fvector2d{ 0, 0 };
    fvector2d last_element_size = fvector2d{ 0, 0 };

    int current_element = -1;
    fvector2d current_element_pos = fvector2d{ 0, 0 };
    fvector2d current_element_size = fvector2d{ 0, 0 };
    int elements_count = 0;

    bool sameLine = false;

    bool pushY = false;
    float pushYvalue = 0.0f;

    void SetupCanvas(ucanvas* _canvas)
    {
        canvas = _canvas;
    }

    void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
    {
        canvas->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
    }

    void drawFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color)
    {
        for (float i = 0.0f; i < h; i += 1.0f)
            canvas->k2_drawline(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
    }


    void MainRect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {

        for (float i = 0; i < height; i++) {
            canvas->k2_drawline(
                { x, y + i },
                { x + width, y + i },
                1.0f,
                color
            );
        }
    }

    // xd
    flinearcolor ApplyOpacityToColor(flinearcolor original, float opacity) {
        flinearcolor result = original;
        result.r *= opacity;
        result.g *= opacity;
        result.b *= opacity;
        result.a = opacity;
        return result;
    }

    void SafeDrawLine(ucanvas* canvas, fvector2d start, fvector2d end, float thickness, flinearcolor color) {
        color.r = std::clamp(color.r, 0.0f, 1.0f);
        color.g = std::clamp(color.g, 0.0f, 1.0f);
        color.b = std::clamp(color.b, 0.0f, 1.0f);
        color.a = std::clamp(color.a, 0.0f, 1.0f);

        canvas->k2_drawline(start, end, thickness, color);
    }

    void DrawOpacityLine(
        ucanvas* canvas,
        fvector2d screenpos_a,
        fvector2d screenpos_b,
        flinearcolor color_a,
        flinearcolor color_c,
        flinearcolor color_b,
        float thickness,
        int num_segments,
        float opacity = 1.0f)
    {
        // Aplicar opacidad a los colores base
        flinearcolor modified_color_a = ApplyOpacityToColor(color_a, opacity);
        flinearcolor modified_color_c = ApplyOpacityToColor(color_c, opacity);
        flinearcolor modified_color_b = ApplyOpacityToColor(color_b, opacity);

        for (int i = 0; i < num_segments; i++)
        {
            float t1 = static_cast<float>(i) / num_segments;
            float t2 = static_cast<float>(i + 1) / num_segments;

            fvector2d start = screenpos_a + (screenpos_b - screenpos_a) * t1;
            fvector2d end = screenpos_a + (screenpos_b - screenpos_a) * t2;

            float t_mid = (t1 + t2) / 2.0f;
            flinearcolor segment_color;

            if (t_mid <= 0.5f)
            {
                float u = 2.0f * t_mid;
                segment_color.r = modified_color_a.r * (1.0f - u) + modified_color_c.r * u;
                segment_color.g = modified_color_a.g * (1.0f - u) + modified_color_c.g * u;
                segment_color.b = modified_color_a.b * (1.0f - u) + modified_color_c.b * u;
                segment_color.a = opacity; // Mantener la opacidad uniforme
            }
            else
            {
                float v = 2.0f * (t_mid - 0.5f);
                segment_color.r = modified_color_c.r * (1.0f - v) + modified_color_b.r * v;
                segment_color.g = modified_color_c.g * (1.0f - v) + modified_color_b.g * v;
                segment_color.b = modified_color_c.b * (1.0f - v) + modified_color_b.b * v;
                segment_color.a = opacity; // Mantener la opacidad uniforme
            }

            SafeDrawLine(canvas, start, end, thickness, segment_color);
        }
    }

    void DrawGradientLine(fvector2d screenpos_a, fvector2d screenpos_b, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, float thickness, int num_segments)
    {
        for (int i = 0; i < num_segments; i++)
        {
            float t1 = static_cast<float>(i) / num_segments;
            float t2 = static_cast<float>(i + 1) / num_segments;

            fvector2d start = screenpos_a + (screenpos_b - screenpos_a) * t1;
            fvector2d end = screenpos_a + (screenpos_b - screenpos_a) * t2;

            float t_mid = (t1 + t2) / 2.0f;

            flinearcolor color;

            if (t_mid <= 0.5f)
            {
                float u = 2.0f * t_mid;  // Maps t_mid [0, 0.5] to u [0, 1]
                color.r = color_a.r * (1.0f - u) + color_c.r * u;
                color.g = color_a.g * (1.0f - u) + color_c.g * u;
                color.b = color_a.b * (1.0f - u) + color_c.b * u;
                color.a = color_a.a * (1.0f - u) + color_c.a * u;
            }
            else
            {
                float v = 2.0f * (t_mid - 0.5f);  // Maps t_mid [0.5, 1] to v [0, 1]
                color.r = color_c.r * (1.0f - v) + color_b.r * v;
                color.g = color_c.g * (1.0f - v) + color_b.g * v;
                color.b = color_c.b * (1.0f - v) + color_b.b * v;
                color.a = color_c.a * (1.0f - v) + color_b.a * v;
            }

            canvas->k2_drawline(start, end, thickness, color);
        }
    }

    // DrawGradientLine(startPos, endPos, red, green, blue, 2.0f, 20);
    void drawGradientFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
    {
        for (float i = 0.0f; i < h; i += 1.0f)
            DrawGradientLine(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, color_a, color_c, color_b, 1.0f, num_segments);
    }

    void drawOpacityFilledRect(
        ucanvas* canvas,
        fvector2d initial_pos,
        float w,
        float h,
        flinearcolor color_a,
        flinearcolor color_c,
        flinearcolor color_b,
        int num_segments,
        float opacity = 1.0f)
    {
        static uobject* set_blend_func = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_SetBlendMode").decrypt());
        if (set_blend_func)
        {
            struct { uint8_t blend_mode; } blend_params;
            blend_params.blend_mode = 1;
            canvas->process_event(set_blend_func, &blend_params);
        }

        for (float i = 0.0f; i < h; i += 1.0f)
        {
            DrawOpacityLine(
                canvas,
                fvector2d{ initial_pos.x, initial_pos.y + i },
                fvector2d{ initial_pos.x + w, initial_pos.y + i },
                color_a,
                color_c,
                color_b,
                1.0f,
                num_segments,
                opacity);
        }

        if (set_blend_func)
        {
            struct { uint8_t blend_mode; } blend_params;
            blend_params.blend_mode = 0;
            canvas->process_event(set_blend_func, &blend_params);
        }
    }

    void drawGradientFilledRectVertical(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
    {
        for (float i = 0.0f; i < w; i += 1.0f)
            DrawGradientLine(fvector2d{ initial_pos.x + i, initial_pos.y }, fvector2d{ initial_pos.x + i, initial_pos.y + h }, color_a, color_c, color_b, 1.0f, num_segments);
    }

    void drawFilledRectOn(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
        for (float i = 0; i < height; i++) {
            canvas->k2_drawline(
                { x, y + i },
                { x + width, y + i },
                1.0f,
                color
            );
        }
    }

    void drawRect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
        canvas->k2_drawline({ x, y }, { x + width, y }, 1.0f, color);
        canvas->k2_drawline({ x + width, y }, { x + width, y + height }, 1.0f, color);
        canvas->k2_drawline({ x + width, y + height }, { x, y + height }, 1.0f, color);
        canvas->k2_drawline({ x, y + height }, { x, y }, 1.0f, color);
    }

    fvector2d CursorPos()
    {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        return fvector2d{ (double)cursorPos.x, (double)cursorPos.y };
    }
    bool MouseInZone(fvector2d pos, fvector2d size)
    {
        fvector2d cursor_pos = CursorPos();

        if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
            if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
                return true;

        return false;
    }

    void Draw_Cursor(bool toogle)
    {
        if (toogle)
        {
            fvector2d cursorPos = CursorPos();
            drawFilledRect(fvector2d(cursorPos.x - 5, cursorPos.y - 5), 5, 5, flinearcolor(3, 3, 3));
        }
    }

    void SameLine()
    {
        sameLine = true;
    }
    void PushNextElementY(float y, bool from_last_element = true)
    {
        pushY = true;
        if (from_last_element)
            pushYvalue = last_element_pos.y + last_element_size.y + y;
        else
            pushYvalue = y;
    }
    void NextColumn(float x)
    {
        offset_x = x;
        PushNextElementY(first_element_pos.y, false);
    }
    void ClearFirstPos()
    {
        first_element_pos = fvector2d{ 0, 0 };
    }

    void xDrawTextRGB(const wchar_t* text, float x, float y, flinearcolor color)
    {
        canvas->k2_drawtext(font, text, { x, y }, { 0.85f, 0.85f }, { 1.f,1.f,1.f,1.0f }, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, 0, 0, 0, { 0, 0, 0, 1 });
    }
    void yDrawTextRGB(const wchar_t* text, float x, float y, flinearcolor color)
    {
        canvas->k2_drawtext(font, text, { x, y }, { 1.1, 1.1 }, { 1.f,1.f,1.f,1.0f }, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, 1, 0, 0, { 0, 0, 0, 1 });
    }
    void TextLeft(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
    {
        xDrawTextRGB(name, pos.x, pos.y, { 1,1,1,1 });
    }
    void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline, bool kekw = 0)
    {
        if (kekw)
            yDrawTextRGB(name, pos.x, pos.y - 10, color);
        else
            yDrawTextRGB(name, pos.x, pos.y - 10, { 1.f,1.f,1.f,1.0f });
    }

    void GetColor(flinearcolor* color, float* r, float* g, float* b, float* a)
    {
        *r = color->r;
        *g = color->g;
        *b = color->b;
        *a = color->a;
    }
    UINT32 GetColorUINT(int r, int g, int b, int a)
    {
        UINT32 result = (BYTE(a) << 24) + (BYTE(r) << 16) + (BYTE(g) << 8) + BYTE(b);
        return result;
    }


    void DrawFilledCircle(fvector2d pos, float r, flinearcolor color)
    {
        float smooth = 0.07f;

        double PI = 3.14159265359;
        int size = (int)(2.0f * PI / smooth) + 1;

        float angle = 0.0f;
        int i = 0;

        for (; angle < 2 * PI; angle += smooth, i++)
        {
            Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
        }
    }
    void DrawCircle(fvector2d pos, int radius, int numSides, flinearcolor Color)
    {
        float PI = 3.1415927f;

        float Step = PI * 2.0 / numSides;
        int Count = 0;
        fvector2d V[128];
        for (float a = 0; a < PI * 2.0; a += Step) {
            float X1 = radius * cos(a) + pos.x;
            float Y1 = radius * sin(a) + pos.y;
            float X2 = radius * cos(a + Step) + pos.x;
            float Y2 = radius * sin(a + Step) + pos.y;
            V[Count].x = X1;
            V[Count].y = Y1;
            V[Count + 1].x = X2;
            V[Count + 1].y = Y2;

            Draw_Line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, 1.0f, Color);
        }
    }

    fvector2d dragPos;
    bool Window(fstring title, fstring build, fstring buildtype, fvector2d* pos, fvector2d size, bool isOpen)
    {
        elements_count = 0;

        if (!isOpen)
            return false;

        bool isHovered = MouseInZone(fvector2d{ pos->x, pos->y }, size);

        //Drop last element
        if (current_element != -1 && !GetAsyncKeyState(0x1))
        {
            current_element = -1;
        }

        //Drag
        if (hover_element && GetAsyncKeyState(0x1))
        {

        }
        else if ((isHovered || dragPos.x != 0) && !hover_element)
        {
            if (inpute::is_mouse_clicked(0, elements_count, true))
            {
                fvector2d cursorPos = CursorPos();

                cursorPos.x -= size.x;
                cursorPos.y -= size.y;

                if (dragPos.x == 0)
                {
                    dragPos.x = (cursorPos.x - pos->x);
                    dragPos.y = (cursorPos.y - pos->y);
                }
                pos->x = cursorPos.x - dragPos.x;
                pos->y = cursorPos.y - dragPos.y;
            }
            else
            {
                dragPos = fvector2d{ 0, 0 };
            }
        }
        else
        {
            hover_element = false;
        }


        offset_x = 85.0f; offset_y = 5.0f;
        menu_pos = fvector2d{ pos->x, pos->y };
        first_element_pos = fvector2d{ 0, 0 };
        current_element_pos = fvector2d{ 0, 0 };
        current_element_size = fvector2d{ 0, 0 };

        // bg
        drawFilledRect(fvector2d(pos->x, pos->y), size.x, size.y, RGBtoFLC(-3, -3, -3));
        drawFilledRect(fvector2d(pos->x + 1, pos->y + 1), size.x - 2, size.y - 2, RGBtoFLC(4, 4, 4));
        drawFilledRect(fvector2d(pos->x + 2, pos->y + 2), size.x - 4, size.y - 4, RGBtoFLC(1.75, 1.75, 1.75));

        // mid
        drawFilledRect(fvector2d(pos->x + 2, pos->y + 2), size.x - 4, 22, RGBtoFLC(-3, -3, -3));
        drawFilledRect(fvector2d(pos->x + 1, pos->y + 2 + 22), size.x - 2, 1, RGBtoFLC(4, 4, 4));

        // effect
        drawFilledRect(fvector2d(pos->x + 2, pos->y + size.y - 2 - 23), size.x - 4, 22, RGBtoFLC(-3, -3, -3));
        drawFilledRect(fvector2d(pos->x + 1, pos->y + size.y - 2 - 23), size.x - 2, 1, RGBtoFLC(4, 4, 4));

        // left
        drawFilledRect(fvector2d(pos->x + 13, pos->y + 25 + 10), 120, 330, RGBtoFLC(4, 4, 4)); //outline
        drawFilledRect(fvector2d(pos->x + 14, pos->y + 26 + 10), 120 - 2, 330 - 2, RGBtoFLC(-3, -3, -3)); //main

        // 1TAB
        drawFilledRect(fvector2d(pos->x + 140, pos->y + 25 + 10), 199, 330, RGBtoFLC(4, 4, 4)); //outline
        drawFilledRect(fvector2d(pos->x + 141, pos->y + 26 + 10), 199 - 2, 330 - 2, RGBtoFLC(-3, -3, -3)); //main

        // PART TOP
        drawRect(canvas, pos->x + 140, pos->y + 25 + 10, 199, 30, RGBtoFLC(4, 4, 4));

        // 2TAB
        drawFilledRect(fvector2d(pos->x + 346, pos->y + 25 + 10), 199, 330, RGBtoFLC(4, 4, 4)); //outline
        drawFilledRect(fvector2d(pos->x + 347, pos->y + 26 + 10), 199 - 2, 330 - 2, RGBtoFLC(-3, -3, -3)); //main

        // PART TOP
        drawRect(canvas, pos->x + 346, pos->y + 25 + 10, 199, 30, RGBtoFLC(4, 4, 4));


        canvas->k2_drawtext(font, title, fvector2d(pos->x + 8, pos->y + (23 / 2)), fvector2d(1.1f, 0.93f), RGBtoFLC(0, 255, 220), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));

        canvas->k2_drawtext(font, build, fvector2d(pos->x + 8, pos->y + size.y - 2 - (23 / 2)), fvector2d(1.05f, 0.93f), RGBtoFLC(94, 94, 94), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
        canvas->k2_drawtext(font, fstring(L" 11.05.26"), fvector2d(pos->x + 50, pos->y + size.y - 2 - (23 / 2)), fvector2d(1.05f, 0.93f), RGBtoFLC(0, 255, 255), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
        //canvas->k2_drawtext(font, fstring(L" Edition"), fvector2d(pos->x + 145, pos->y + size.y - 2 - (23 / 2)), fvector2d(1.05f, 0.93f), RGBtoFLC(240, 240, 240), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));

        return true;
    }

    bool ButtonTab(const wchar_t* name, fvector2d size, bool active)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 0, 0 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + offset_x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        if (!sameLine)
            offset_y += size.y + padding.y;

        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };

        //Bg
        if (active)
        {
            drawFilledRect(fvector2d(pos.x, pos.y + 2), size.x, size.y, RGBtoFLC(10, 10, 10));

            drawFilledRect(fvector2d(pos.x + 1, pos.y + 2), size.x - 2, size.y, RGBtoFLC(1.25, 1.25, 1.25));

            drawGradientFilledRect(
                fvector2d(pos.x + 1, pos.y + 1),
                size.x - 2,
                1,
                RGBtoFLC(0, 80, 80),
                RGBtoFLC(0, 160, 160),
                RGBtoFLC(0, 255, 255),
                100
            );

            drawGradientFilledRect(
                fvector2d(pos.x, pos.y + 2),
                1,
                0.5,
                RGBtoFLC(0, 80, 80),
                RGBtoFLC(0, 160, 160),
                RGBtoFLC(0, 255, 255),
                100
            );
            drawGradientFilledRect(
                fvector2d(pos.x + size.x - 1, pos.y + 2),
                1,
                0.5,
                RGBtoFLC(0, 80, 80),
                RGBtoFLC(0, 160, 160),
                RGBtoFLC(0, 255, 255),
                100
            );

            canvas->k2_drawtext(font, name, textPos, fvector2d(0.96, 0.92), RGBtoFLC(0, 255, 255), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
        }
        else if (isHovered)
        {
            canvas->k2_drawtext(font, name, textPos, fvector2d(0.96, 0.92), RGBtoFLC(140, 140, 140), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
            hover_element = true;
        }
        else
        {
            canvas->k2_drawtext(font, name, textPos, fvector2d(0.96, 0.92), RGBtoFLC(90, 90, 90), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
        }

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && inpute::is_mouse_clicked(0, elements_count, false))
            return true;

        return false;
    }

    bool ButtonSection(const wchar_t* name, fvector2d size, bool active)
    {
        elements_count++;

        float original_offset_y = offset_y;
        bool original_sameLine = sameLine;
        fvector2d padding = fvector2d{ 0, 0 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + offset_x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        if (!sameLine)
            offset_y += size.y + padding.y;

        fvector2d textPos = fvector2d{ pos.x + 9, pos.y + size.y / 2 - 3 };


        if (active)
        {
            drawGradientFilledRect(
                fvector2d(pos.x, pos.y),
                1.0f,
                size.y,
                RGBtoFLC(0, 80, 80),
                RGBtoFLC(0, 160, 160),
                RGBtoFLC(0, 255, 255),
                100
            );

            drawOpacityFilledRect(
                canvas,
                fvector2d{ pos.x + 2, pos.y },
                70,
                size.y,
                RGBtoFLC(0, 160, 160),
                RGBtoFLC(0, 80, 80),
                RGBtoFLC(0, 40, 40),
                100,
                0.2
            );

            canvas->k2_drawtext(
                font,
                name,
                textPos,
                fvector2d(0.97, 0.92),
                RGBtoFLC(0, 255, 255),
                0.0f,
                RGBtoFLC(0, 0, 0),
                fvector2d(0, 0),
                false,
                true,
                false,
                RGBtoFLC(0, 0, 0)
            );
        }
        else if (isHovered)
        {
            drawGradientFilledRect(fvector2d(pos.x, pos.y), 1.0f, size.y, RGBtoFLC(90 / 2, 90 / 2, 90 / 2), RGBtoFLC(90 / 4, 90 / 4, 90 / 4), RGBtoFLC(90 / 8, 90 / 8, 90 / 8), 100);
            drawOpacityFilledRect(canvas, fvector2d{ pos.x + 2, pos.y }, 70, size.y, RGBtoFLC(90 / 2, 90 / 2, 90 / 2), RGBtoFLC(90 / 4, 90 / 4, 90 / 4), RGBtoFLC(90 / 8, 90 / 8, 90 / 8), 100, 0.2);
            canvas->k2_drawtext(font, name, textPos, fvector2d(0.97, 0.92), RGBtoFLC(140, 140, 140), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
            hover_element = true;
        }
        else
        {
            drawGradientFilledRect(fvector2d(pos.x, pos.y), 1, size.y, RGBtoFLC(30 / 2, 30 / 2, 30 / 2), RGBtoFLC(30 / 2, 30 / 2, 30 / 2), RGBtoFLC(30 / 2, 30 / 2, 30 / 2), 100);
            canvas->k2_drawtext(font, name, textPos, fvector2d(0.97, 0.92), RGBtoFLC(90, 90, 90), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
        }

        if (!sameLine)
        {
            offset_y = original_offset_y; // Restaurar posición original primero
            offset_y += size.y + 5.0f; // Espacio constante de 5px después del botón
        }

        sameLine = original_sameLine;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && inpute::is_mouse_clicked(0, elements_count, false))
            return true;

        return false;
    }

    void DrawCheckMark(fvector2d pos, float sz, flinearcolor color)
    {
        float thickness = fmaxf(sz / 5.0f, 1.0f);
        sz -= thickness * 0.5f;
        pos.x += thickness * 0.25f;
        pos.y += thickness * 0.25f;

        float third = sz / 3.0f;
        float bx = pos.x + third;
        float by = pos.y + sz - third * 0.5f;

        fvector2d p1 = fvector2d{ bx - third, by - third };
        fvector2d p2 = fvector2d{ bx, by };
        fvector2d p3 = fvector2d{ bx + third * 2.0f, by - third * 2.0f };

        // Assuming a simple function to draw lines with thickness
        canvas->k2_drawline(p1, p2, thickness, color);
        canvas->k2_drawline(p2, p3, thickness, color);
    }

    void SectionWrapper(fstring name, fvector2d size)
    {
        fvector2d padding = fvector2d{ 0, 0 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = menu_pos.x + padding.x + offset_x;
            pos.y = menu_pos.y + padding.y + offset_y;
        }

        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(4, 4, 4));
        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

        canvas->k2_drawtext(font, name, fvector2d(pos.x + (size.x / 2), pos.y + (24 / 2)), fvector2d(0.95, 0.85), RGBtoFLC(90, 90, 90), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, false, Colors::Text_Shadow);

        drawFilledRect(fvector2d{ pos.x + 1 + 13, pos.y + 26 }, size.x - 28, 2, RGBtoFLC(3, 3, 3));

        menu::offset_y += 26 + 4;

        sameLine = false;
    }
    wchar_t GetPressedChar()
    {
        for (int vk = 0x20; vk <= 0x5A; vk++) // SPACE → Z
        {
            if (GetAsyncKeyState(vk) & 0x1)
            {
                // Letters A–Z
                if (vk >= 'A' && vk <= 'Z')
                {
                    bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
                    wchar_t c = shift ? wchar_t(vk) : wchar_t(vk + 32);
                    return c;
                }

                // Numbers 0–9
                if (vk >= '0' && vk <= '9')
                    return wchar_t(vk);

                // Space
                if (vk == VK_SPACE)
                    return L' ';
            }
        }

        return 0;
    }

    bool IsKeyPressed(int vk)
    {
        return (GetAsyncKeyState(vk) & 0x1);
    }
    static bool WasKeyJustPressed(int vk)
    {
        SHORT state = GetAsyncKeyState(vk);
        bool nowDown = !!(state & 0x8000);
        bool justPressed = (nowDown && !prevKeyDown[vk]);
        prevKeyDown[vk] = nowDown;
        return justPressed;
    }
    static bool GetJustPressedChar(wchar_t& outChar)
    {
        bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;

        // Letters
        for (int vk = 'A'; vk <= 'Z'; ++vk)
        {
            if (WasKeyJustPressed(vk))
            {
                outChar = (wchar_t)(shift ? vk : vk + 32); // uppercase if shift
                return true;
            }
        }

        // Numbers top row (VK_0..VK_9)
        // map with shift to symbols: 1->! 2->@ 3-># 4->$ 5->% 6->^ 7->& 8->* 9->( 0->)
        const wchar_t shiftNumMap[10] = { L')', L'!', L'@', L'#', L'$', L'%', L'^', L'&', L'*', L'(' };
        for (int vk = '0'; vk <= '9'; ++vk)
        {
            if (WasKeyJustPressed(vk))
            {
                int idx = vk - '0';
                outChar = shift ? shiftNumMap[idx] : (wchar_t)vk;
                return true;
            }
        }

        // Space
        if (WasKeyJustPressed(VK_SPACE))
        {
            outChar = L' ';
            return true;
        }

        // OEM keys (common punctuation) - handle typical US layout
        if (WasKeyJustPressed(VK_OEM_1))  // ;:
        {
            outChar = shift ? L':' : L';'; return true;
        }
        if (WasKeyJustPressed(VK_OEM_PLUS)) // =+
        {
            outChar = shift ? L'+' : L'='; return true;
        }
        if (WasKeyJustPressed(VK_OEM_COMMA)) // ,<
        {
            outChar = shift ? L'<' : L','; return true;
        }
        if (WasKeyJustPressed(VK_OEM_MINUS)) // -_
        {
            outChar = shift ? L'_' : L'-'; return true;
        }
        if (WasKeyJustPressed(VK_OEM_PERIOD)) // .>
        {
            outChar = shift ? L'>' : L'.'; return true;
        }
        if (WasKeyJustPressed(VK_OEM_2)) // /?
        {
            outChar = shift ? L'?' : L'/'; return true;
        }
        if (WasKeyJustPressed(VK_OEM_3)) // `~
        {
            outChar = shift ? L'~' : L'`'; return true;
        }
        if (WasKeyJustPressed(VK_OEM_4)) // [{
        {
            outChar = shift ? L'{' : L'['; return true;
        }
        if (WasKeyJustPressed(VK_OEM_5)) // \|
        {
            outChar = shift ? L'|' : L'\\'; return true;
        }
        if (WasKeyJustPressed(VK_OEM_6)) // ]}
        {
            outChar = shift ? L'}' : L']'; return true;
        }
        if (WasKeyJustPressed(VK_OEM_7)) // '"
        {
            outChar = shift ? L'"' : L'\''; return true;
        }

        return false;
    }
    void HandleClipboardPaste(std::wstring& buffer)
    {
        bool ctrlPressed = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
        bool vPressed = WasKeyJustPressed('V');

        if (ctrlPressed && vPressed)
        {
            if (OpenClipboard(nullptr))
            {
                HANDLE hData = GetClipboardData(CF_UNICODETEXT);
                if (hData)
                {
                    wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
                    if (pszText)
                    {
                        buffer += pszText; // append clipboard content
                        GlobalUnlock(hData);
                    }
                }
                CloseClipboard();
            }
        }
    }
    bool InputText(const wchar_t* name, std::wstring& buffer, fvector2d size)
    {
        elements_count++;

        fvector2d padding{ 15, 10 };
        fvector2d pos{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine) { pos.x = last_element_pos.x + last_element_size.x + padding.x; pos.y = last_element_pos.y; }
        if (pushY) { pos.y = pushYvalue; pushY = false; pushYvalue = 0.f; offset_y = pos.y - menu_pos.y; }

        bool hovered = MouseInZone(pos, size);
        bool leftClick = (GetAsyncKeyState(VK_LBUTTON) & 0x1) != 0;
        static bool lastClickState = false;

        // === Click handling (activate/deactivate input) ===
        if (hovered && leftClick && !lastClickState)
        {
            chatTypingActive = true;
            lastCursorFlip = GetTickCount64();
            cursorOn = true;
        }
        else if (!hovered && leftClick && !lastClickState)
        {
            chatTypingActive = false;
        }
        lastClickState = leftClick;

        // === Background ===
        drawFilledRect(pos, size.x, size.y, RGBtoFLC(12, 12, 12));
        drawFilledRect(fvector2d(pos.x + 1, pos.y + 1), size.x - 2, size.y - 2, hovered ? RGBtoFLC(4, 4, 4) : RGBtoFLC(3, 3, 3));

        // === Prepare text with blinking cursor ===
        std::wstring drawText = buffer.empty() && !chatTypingActive ? L"[ Type message... ]" : buffer;
        DWORD now = GetTickCount64();
        if (now - lastCursorFlip >= CURSOR_BLINK_MS) { lastCursorFlip = now; cursorOn = !cursorOn; }

        if (chatTypingActive && drawText.size() < CHAT_MAX_LENGTH)
            drawText += cursorOn ? L'|' : L' ';

        canvas->k2_drawtext(font, drawText.c_str(), fvector2d(pos.x + 6, pos.y + size.y / 4),
            fvector2d(0.9, 0.9), RGBtoFLC(180, 180, 180), 0.f,
            Colors::Text_Shadow, fvector2d(0, 0), false, false, false, Colors::Text_Outline);

        // === Input handling when active ===
        if (chatTypingActive)
        {
            // Backspace
            if (WasKeyJustPressed(VK_BACK) && !buffer.empty()) buffer.pop_back();

            // Paste from clipboard
            HandleClipboardPaste(buffer);

            // Normal characters
            wchar_t ch;
            if (GetJustPressedChar(ch) && buffer.size() < CHAT_MAX_LENGTH) buffer.push_back(ch);
        }

        // === Layout bookkeeping ===
        if (!sameLine) offset_y += size.y + padding.y;
        sameLine = false; last_element_pos = pos; last_element_size = size;
        if (first_element_pos.x == 0.f) first_element_pos = pos;

        return chatTypingActive;
    }


    void Checkbox(const wchar_t* name, bool* value)
    {

        elements_count++;

        const float checkboxSize = 12.0f;
        const float textOffsetY = -1.0f;
        const float spacing = 5.0f;
        fvector2d padding = fvector2d{ 5.0f, 10.0f };


        fvector2d pos = fvector2d{
        menu_pos.x + padding.x + offset_x,
        menu_pos.y + padding.y + offset_y
        };

        if (sameLine) {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }

        if (pushY) {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        fvector2d checkboxPos = pos;
        fvector2d textPos = fvector2d{
            pos.x + checkboxSize + spacing,
            pos.y + textOffsetY
        };


        bool isHovered = MouseInZone(
            fvector2d{ pos.x, pos.y },
            fvector2d{ checkboxSize + 100.0f, checkboxSize }
        );

        drawFilledRect(checkboxPos, checkboxSize, checkboxSize, RGBtoFLC(7, 7, 7));
        drawFilledRect(fvector2d{ checkboxPos.x + 1, checkboxPos.y + 1 }, checkboxSize - 2, checkboxSize - 2, RGBtoFLC(2.5, 2.5, 2.5));

        canvas->k2_drawtext(
            font, name, textPos,
            fvector2d(0.9f, 0.9f),
            *value ? RGBtoFLC(255, 255, 255) : RGBtoFLC(90, 90, 90),
            0.0f, Colors::Text_Shadow, fvector2d(0, 0),
            false, false, false, Colors::Text_Shadow
        );

        if (*value) {
            drawGradientFilledRect(fvector2d{ checkboxPos.x + 2, checkboxPos.y + 2 }, checkboxSize - 4, checkboxSize - 4, RGBtoFLC(220 / 4, 0, 0), RGBtoFLC(220 / 2, 0, 0), RGBtoFLC(0, 255, 255), 100);
        }

        if (!sameLine) {
            offset_y += checkboxSize + padding.y;
        }

        sameLine = false;
        last_element_pos = pos;
        last_element_size = fvector2d{ checkboxSize + 100.0f + spacing, checkboxSize };

        if (first_element_pos.x == 0.0f) {
            first_element_pos = pos;
        }

        if (isHovered && inpute::is_mouse_clicked(0, elements_count, false)) {
            *value = !*value;
        }
    }	bool checkbox_enabled[256];

    void Combobox(const wchar_t* name, fvector2d size, int* value, const wchar_t* arg, ...)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 14, 30 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 20.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        //Bg
        if (isHovered || checkbox_enabled[elements_count])
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(3, 3, 3));

            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));
        }

        if (!sameLine)
            offset_y += size.y + padding.y;

        //Text
        fvector2d textPos = fvector2d{ pos.x - 2.0f, pos.y - size.y + 2.0f };
        canvas->k2_drawtext(font, name, textPos, fvector2d(0.99, 0.99), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, true, Colors::Text_Outline);

        canvas->k2_drawtext(font, s2wc("-"), fvector2d{ pos.x + size.x - 17, pos.y + size.y / 2 }, fvector2d(0.97, 0.97), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, true, true, Colors::Text_Outline);

        //Elements
        bool isHovered2 = false;
        fvector2d element_pos = pos;
        int num = 0;

        if (checkbox_enabled[elements_count])
        {
            current_element_size.x = element_pos.x - 5.0f;
            current_element_size.y = element_pos.y - 5.0f;
        }
        va_list arguments;
        for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const wchar_t*))
        {
            //Selected Element
            if (num == *value)
            {
                fvector2d _textPos = fvector2d{ pos.x + 5, pos.y + size.y / 2 };
                canvas->k2_drawtext(font, arg, _textPos, fvector2d(0.98, 0.98), RGBtoFLC(130, 130, 130), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, true, true, Colors::Text_Outline);
            }

            if (checkbox_enabled[elements_count])
            {
                element_pos.y += 25.0f;

                isHovered2 = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });
                if (isHovered2)
                {
                    hover_element = true;
                    PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(4, 4, 4));

                    //Click
                    if (inpute::is_mouse_clicked(0, elements_count, false))
                    {
                        *value = num;
                        checkbox_enabled[elements_count] = false;
                    }
                }
                else
                {
                    PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(3, 3, 3));
                }

                PostRenderer::TextLeft(arg, fvector2d{ element_pos.x + 10.0f, element_pos.y + 5.0f }, RGBtoFLC(110, 110, 110), true);
            }
            num++;
        }
        va_end(arguments);
        if (checkbox_enabled[elements_count])
        {
            current_element_size.x = element_pos.x + 5.0f;
            current_element_size.y = element_pos.y + 5.0f;
        }


        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && inpute::is_mouse_clicked(0, elements_count, false))
        {
            checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
        }
        if (!isHovered && !isHovered2 && inpute::is_mouse_clicked(0, elements_count, false))
        {
            checkbox_enabled[elements_count] = false;
        }
    }
    void Combobox2(const wchar_t* name, fvector2d size, int* value, const std::vector<const wchar_t*>& items)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 15, 30 };
        fvector2d pos = fvector2d(menu::offset_x, menu::offset_y);
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 20.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        if (isHovered || checkbox_enabled[elements_count])
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(5, 5, 5));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(4, 4, 4));
            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(5, 5, 5));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(3, 3, 3));
        }

        if (!sameLine)
            offset_y += size.y + padding.y;

        fvector2d textPos = fvector2d{ pos.x - 2.0f, pos.y - size.y + 2.0f };
        canvas->k2_drawtext(menu::font, name, textPos, fvector2d(0.99, 0.99), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, true, Colors::Text_Outline);
        canvas->k2_drawtext(menu::font, s2wc("v"), fvector2d{ pos.x + size.x - 18, pos.y - 2 + size.y / 2 }, fvector2d(1.2, 0.96), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, true, false, Colors::Text_Outline);

        bool isHovered2 = false;
        fvector2d element_pos = pos;

        if (checkbox_enabled[elements_count])
        {
            current_element_size.x = element_pos.x - 5.0f;
            current_element_size.y = element_pos.y - 5.0f;
        }

        for (int num = 0; num < items.size(); num++)
        {
            const wchar_t* arg = items[num];
            if (num == *value)
            {
                fvector2d _textPos = fvector2d{ pos.x + 5, pos.y + size.y / 2 };
                canvas->k2_drawtext(menu::font, arg, _textPos, fvector2d(0.98, 0.98), RGBtoFLC(130, 130, 130), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, true, true, Colors::Text_Outline);
            }

            if (checkbox_enabled[elements_count])
            {
                element_pos.y += 25.0f;
                isHovered2 = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });

                if (isHovered2)
                {
                    hover_element = true;
                    PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(4, 4, 4));

                    if (inpute::is_mouse_clicked(0, elements_count, false))
                    {
                        *value = num;
                        checkbox_enabled[elements_count] = false;
                    }
                }
                else
                {
                    PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(3, 3, 3));
                }

                PostRenderer::TextLeft(arg, fvector2d{ element_pos.x + 10.0f, element_pos.y + 5.0f }, RGBtoFLC(110, 110, 110), true);
            }
        }

        if (checkbox_enabled[elements_count])
        {
            current_element_size.x = element_pos.x + 5.0f;
            current_element_size.y = element_pos.y + 5.0f;
        }

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && inpute::is_mouse_clicked(0, elements_count, false))
        {
            checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
        }
        if (!isHovered && !isHovered2 && inpute::is_mouse_clicked(0, elements_count, false))
        {
            checkbox_enabled[elements_count] = false;
        }
    }


    void ShowSkinCombobox(const wchar_t* name, fvector2d size, int* selectedSkin, const std::vector<SkinData>& skinData)
    {
        // Collect the skin display names in a vector of const wchar_t*
        std::vector<const wchar_t*> skinNames;
        for (const auto& skin : skinData)
        {
            skinNames.push_back(skin.SkinName);
        }

        // Pass the skin names to your Combobox function
        Combobox2(name, size, selectedSkin, skinNames);
    }

    void SliderFloat(const wchar_t* name, float* value, float min, float max, const char* format = "%.0f")
    {
        elements_count++;
        fvector2d size = fvector2d{ 10, 10 };
        fvector2d slider_size = fvector2d{ 125, 10 };
        fvector2d adjust_zone = fvector2d{ 0, 10 };
        fvector2d padding = fvector2d{ 10, 6 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

        if (!sameLine)
            offset_y += size.y + padding.y;

        //Bg
        if (isHovered || current_element == elements_count)
        {
            //Drag
            if (inpute::is_mouse_clicked(0, elements_count, true))
            {
                current_element = elements_count;

                fvector2d cursorPos = CursorPos();
                *value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
                if (*value < min) *value = min;
                if (*value > max) *value = max;
            }

            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 9));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(6, 6, 6));

            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 9));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(4, 4, 4));
        }

        fvector2d textPos = fvector2d{ pos.x, pos.y - 2.0f };
        canvas->k2_drawtext(font, name, textPos, fvector2d(0.9, 0.9), RGBtoFLC(90, 90, 90), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, false, Colors::Text_Shadow);

        float oneP = slider_size.x / (max - min);
        drawGradientFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, oneP * (*value - min) - 2, slider_size.y - 2, RGBtoFLC(220 / 4, 0, 0), RGBtoFLC(220 / 2, 0, 0), RGBtoFLC(0, 255, 255), 100);

        char buffer[32];
        sprintf_s(buffer, format, *value);
        canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 16.0f, pos.y - 0.1f), fvector2d(0.9, 0.9), RGBtoFLC(90, 90, 90), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, false, false, Colors::Text_Outline);

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }

    int active_hotkey = -1;
    bool already_pressed = false;
    std::string VirtualKeyCodeToString(UCHAR virtualKey)
    {
        UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
        if (virtualKey == VK_LBUTTON)
        {
            return ("MOUSE0");
        }
        if (virtualKey == VK_RBUTTON)
        {
            return ("MOUSE1");
        }
        if (virtualKey == VK_MBUTTON)
        {
            return ("MBUTTON");
        }
        if (virtualKey == VK_XBUTTON1)
        {
            return ("XBUTTON1");
        }
        if (virtualKey == VK_XBUTTON2)
        {
            return ("XBUTTON2");
        }


        CHAR szName[128];
        int result = 0;
        switch (virtualKey)
        {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT:
        case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE:
        case VK_DIVIDE:
        case VK_NUMLOCK:
            scanCode |= KF_EXTENDED;
        default:
            result = GetKeyNameTextA(scanCode << 16, szName, 128);
        }

        return szName;
    }

    void Hotkey(const char* label, fvector2d size, int* key)
    {
        elements_count++;
        fvector2d padding = fvector2d{ 5, 5 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y - padding.y;
        }

        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        // Dibujar el fondo del hotkey
        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

        if (!sameLine)
            offset_y += size.y + padding.y;

        // Posición del texto (centrado)
        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };

        if (active_hotkey == elements_count)
        {
            // Modo edición - mostrar "..."
            canvas->k2_drawtext(font, L"...", textPos, fvector2d(0.9, 0.9), RGBtoFLC(60, 60, 60), 0.0f,
                Colors::Text_Shadow, fvector2d(0, 0), true, true, true, Colors::Text_Outline);

            if (!inpute::is_any_mouse_down())
            {
                already_pressed = false;
            }

            if (!already_pressed)
            {
                for (int code = 0; code < 255; code++)
                {
                    if (GetAsyncKeyState(code))
                    {
                        *key = code;
                        active_hotkey = -1;
                    }
                }
            }
        }
        else
        {
            // Modo normal - mostrar label o tecla actual
            std::wstring displayText;

            if (*key == 0)
            {
                displayText = s2wc(label); // Mostrar el nombre descriptivo ("Trigger")
            }
            else
            {
                displayText = s2wc(VirtualKeyCodeToString(*key).c_str()); // Mostrar la tecla actual
            }

            canvas->k2_drawtext(font, displayText.c_str(), textPos, fvector2d(0.99, 0.99),
                RGBtoFLC(60, 60, 60), 0.0f, Colors::Text_Shadow,
                fvector2d(0, 0), true, true, true, Colors::Text_Outline);

            if (isHovered)
            {
                if (inpute::is_mouse_clicked(0, elements_count, false))
                {
                    already_pressed = true;
                    active_hotkey = elements_count;

                    // Queue Fix
                    for (int code = 0; code < 255; code++)
                        if (GetAsyncKeyState(code)) {}
                }
            }
            else
            {
                if (inpute::is_mouse_clicked(0, elements_count, false))
                {
                    active_hotkey = -1;
                }
            }
        }

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }

    bool draw_color_picker(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        const float hue_slider_width = 100.0f;
        const float hue_slider_height = 7.0f;
        const float sb_picker_size = 75.0f;
        const float alpha_slider_width = hue_slider_width;
        const float alpha_slider_height = 7.0f;
        const float preview_box_size = 15.0f;
        const float spacing = 5.0f;

        static bool hue_dragging = false;
        static bool sb_dragging = false;
        static bool alpha_dragging = false;

        static float hue = 0.0f;
        static float saturation = 1.0f;
        static float brightness = 1.0f;

        float thickness = 2.0f; // grosor del texto
        float width_scale = 1.0f; // escala de anchura
        float height_scale = 0.8f; // escala de altura
        float text_scale = 1.1f; // escala del tamaÃ±o de la fuente

        bool value_changed = false;

        for (int i = 0; i < hue_slider_width; i++) {
            float h = (float)i / hue_slider_width;
            flinearcolor color_at_hue = HSVtoRGB(h, 1.0f, 1.0f);
            menu::drawFilledRectOn(canvas, pos.x + i, pos.y, 1.0f, hue_slider_height, color_at_hue); // raya arriba
        }
        menu::drawRect(canvas, pos.x, pos.y, hue_slider_width, hue_slider_height, RGBtoFLC(5, 5, 5));

        if (mouse_clicked && mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + hue_slider_width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + hue_slider_height) {
            hue_dragging = true;
        }
        if (hue_dragging) {
            if (mouse_clicked) {
                hue = (mouse_pos.x - pos.x) / hue_slider_width;
                hue = std::clamp(hue, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                hue_dragging = false;
            }
        }

        fvector2d sb_pos = { pos.x, pos.y + hue_slider_height + spacing };

        for (int y = 0; y < sb_picker_size; y++) {
            for (int x = 0; x < sb_picker_size; x++) {
                float s = (float)x / sb_picker_size;
                float b = 1.0f - (float)y / sb_picker_size;
                flinearcolor sb_color = HSVtoRGB(hue, s, b);
                menu::drawFilledRectOn(canvas, sb_pos.x + x, sb_pos.y + y, 1.0f, 1.0f, sb_color);
            }
        }
        menu::drawRect(canvas, sb_pos.x, sb_pos.y, sb_picker_size, sb_picker_size, RGBtoFLC(5, 5, 5));

        if (mouse_clicked && mouse_pos.x >= sb_pos.x && mouse_pos.x <= sb_pos.x + sb_picker_size &&
            mouse_pos.y >= sb_pos.y && mouse_pos.y <= sb_pos.y + sb_picker_size) {
            sb_dragging = true;
        }
        if (sb_dragging) {
            if (mouse_clicked) {
                saturation = (mouse_pos.x - sb_pos.x) / sb_picker_size;
                brightness = 1.0f - (mouse_pos.y - sb_pos.y) / sb_picker_size;
                saturation = std::clamp(saturation, 0.0f, 1.0f);
                brightness = std::clamp(brightness, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                sb_dragging = false;
            }
        }

        fvector2d alpha_pos = { pos.x, sb_pos.y + sb_picker_size + spacing };

        for (int i = 0; i < alpha_slider_width; i++) {
            float alpha = (float)i / alpha_slider_width;
            flinearcolor alpha_color = HSVtoRGB(hue, saturation, brightness);
            alpha_color.a = alpha;
            menu::drawFilledRectOn(canvas, alpha_pos.x + i, alpha_pos.y, 1.0f, alpha_slider_height, alpha_color);
        }
        menu::drawRect(canvas, alpha_pos.x, alpha_pos.y, alpha_slider_width, alpha_slider_height, RGBtoFLC(5, 5, 5));

        if (mouse_clicked && mouse_pos.x >= alpha_pos.x && mouse_pos.x <= alpha_pos.x + alpha_slider_width &&
            mouse_pos.y >= alpha_pos.y && mouse_pos.y <= alpha_pos.y + alpha_slider_height) {
            alpha_dragging = true;
        }
        if (alpha_dragging) {
            if (mouse_clicked) {
                color.a = (mouse_pos.x - alpha_pos.x) / alpha_slider_width;
                color.a = std::clamp(color.a, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                alpha_dragging = false;
            }
        }

        flinearcolor final_color = HSVtoRGB(hue, saturation, brightness);
        color.r = final_color.r;
        color.g = final_color.g;
        color.b = final_color.b;

        fvector2d preview_pos = { pos.x + hue_slider_width + spacing, pos.y };
        menu::drawFilledRectOn(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, { color.r, color.g, color.b, color.a });
        menu::drawRect(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, RGBtoFLC(5, 5, 5));

        return value_changed;
    }

    // END
    void Text(const wchar_t* text, bool center = false, bool outline = false)
    {
        elements_count++;

        float size = 24;
        fvector2d padding = fvector2d{ 1,3 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        if (!sameLine)
            offset_y += size + padding.y;

        //Text
        fvector2d textPos = fvector2d{ pos.x + 5.0f, pos.y };
        if (center)
            TextCenter(text, textPos, Colors::Text_Shadow, outline);
        else
            TextLeft(text, textPos, Colors::Text_Shadow, outline);

        sameLine = false;
        last_element_pos = pos;
        //last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }
    bool Button(const wchar_t* name, fvector2d size)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 15, 15 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(7, 7, 7));

        //Bg
        if (isHovered)
        {
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(3, 3, 3));
            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));
        }

        if (!sameLine)
            offset_y += size.y + padding.y;

        //Text
        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
        canvas->k2_drawtext(font, name, textPos, fvector2d(1.05, 0.99), RGBtoFLC(160, 160, 160), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, false, Colors::Text_Outline);


        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && inpute::is_mouse_clicked(0, elements_count, false))
            return true;

        return false;
    }
    void SliderInt(const wchar_t* name, int* value, int min, int max)
    {
        elements_count++;
        fvector2d size = fvector2d{ 10, 10 };
        fvector2d slider_size = fvector2d{ 125, 10 };
        fvector2d adjust_zone = fvector2d{ 0, 10 };
        fvector2d padding = fvector2d{ 10, 6 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

        if (!sameLine)
            offset_y += size.y + padding.y;

        if (isHovered || current_element == elements_count)
        {
            if (inpute::is_mouse_clicked(0, elements_count, true))
            {
                current_element = elements_count;

                fvector2d cursorPos = CursorPos();
                int newVal = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
                *value = std::clamp(newVal, min, max);
            }


            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 9));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(6, 6, 6));
            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 9));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(4, 4, 4));
        }

        fvector2d textPos = fvector2d{ pos.x, pos.y - 2.0f };
        canvas->k2_drawtext(font, name, textPos, fvector2d(0.9, 0.9), RGBtoFLC(90, 90, 90), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, false, Colors::Text_Shadow);

        float oneP = slider_size.x / (float)(max - min);
        drawGradientFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, oneP * (*value - min) - 2, slider_size.y - 2, RGBtoFLC(220 / 4, 0, 0), RGBtoFLC(220 / 2, 0, 0), RGBtoFLC(0, 255, 255), 100);
        char buffer[32];
        sprintf_s(buffer, "%d", *value);
        canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 16.0f, pos.y - 0.1f), fvector2d(0.9, 0.9), RGBtoFLC(90, 90, 90), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, false, false, Colors::Text_Outline);

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }


    int active_picker = -1;
    flinearcolor saved_color;
    bool ColorPixel(fvector2d pos, fvector2d size, flinearcolor* original, flinearcolor color)
    {
        PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, color);

        //Выбранный цвет
        if (original->r == color.r && original->g == color.g && original->b == color.b)
        {
            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y + size.y - 1 }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
            PostRenderer::Draw_Line(fvector2d{ pos.x + size.x - 1, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
        }

        //Смена цвета
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);
        if (isHovered)
        {
            if (inpute::is_mouse_clicked(0, elements_count, false))
                *original = color;
        }

        return true;
    }
    void ColorPicker(const wchar_t* name, flinearcolor* color)
    {
        elements_count++;

        float size = 15;
        float xsize = 5;
        fvector2d padding = fvector2d{ 15, 10 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ size, size });

        if (!sameLine)
            offset_y += size + padding.y;

        if (active_picker == elements_count)
        {
            hover_element = true;

            float sizePickerX = 250;
            float sizePickerY = 250;
            bool isHoveredPicker = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ sizePickerX, sizePickerY - 60 });

            //Background
            PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, sizePickerX, sizePickerY - 65, Colors::ColorPicker_Background);

            fvector2d pixelSize = fvector2d{ sizePickerX / 12, sizePickerY / 12 };

            //0
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 174 / 255.f, 235 / 255.f, 253 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 136 / 255.f, 225 / 255.f, 251 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 108 / 255.f, 213 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 89 / 255.f, 175 / 255.f, 213 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 76 / 255.f, 151 / 255.f, 177 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 60 / 255.f, 118 / 255.f, 140 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 43 / 255.f, 85 / 255.f, 100 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 32 / 255.f, 62 / 255.f, 74 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
            }
            //1
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 175 / 255.f, 205 / 255.f, 252 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 132 / 255.f, 179 / 255.f, 252 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 90 / 255.f, 152 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 55 / 255.f, 120 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 49 / 255.f, 105 / 255.f, 209 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 38 / 255.f, 83 / 255.f, 165 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 28 / 255.f, 61 / 255.f, 120 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 20 / 255.f, 43 / 255.f, 86 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 247 / 255.f, 247 / 255.f, 247 / 255.f, 1.0f });
            }
            //2
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 153 / 255.f, 139 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 101 / 255.f, 79 / 255.f, 249 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 64 / 255.f, 50 / 255.f, 230 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 54 / 255.f, 38 / 255.f, 175 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 39 / 255.f, 31 / 255.f, 144 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 32 / 255.f, 25 / 255.f, 116 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 21 / 255.f, 18 / 255.f, 82 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 16 / 255.f, 13 / 255.f, 61 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 228 / 255.f, 228 / 255.f, 228 / 255.f, 1.0f });
            }
            //3
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 194 / 255.f, 144 / 255.f, 251 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 165 / 255.f, 87 / 255.f, 249 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 142 / 255.f, 57 / 255.f, 239 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 116 / 255.f, 45 / 255.f, 184 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 92 / 255.f, 37 / 255.f, 154 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 73 / 255.f, 29 / 255.f, 121 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 53 / 255.f, 21 / 255.f, 88 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 37 / 255.f, 15 / 255.f, 63 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 203 / 255.f, 203 / 255.f, 203 / 255.f, 1.0f });
            }
            //4
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 224 / 255.f, 162 / 255.f, 197 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 210 / 255.f, 112 / 255.f, 166 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 199 / 255.f, 62 / 255.f, 135 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 159 / 255.f, 49 / 255.f, 105 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 132 / 255.f, 41 / 255.f, 89 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 104 / 255.f, 32 / 255.f, 71 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 75 / 255.f, 24 / 255.f, 51 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 14 / 255.f, 36 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 175 / 255.f, 175 / 255.f, 175 / 255.f, 1.0f });
            }
            //5
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 235 / 255.f, 175 / 255.f, 176 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 227 / 255.f, 133 / 255.f, 135 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 219 / 255.f, 87 / 255.f, 88 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 215 / 255.f, 50 / 255.f, 36 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 187 / 255.f, 25 / 255.f, 7 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 149 / 255.f, 20 / 255.f, 6 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 14 / 255.f, 4 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 77 / 255.f, 9 / 255.f, 3 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 144 / 255.f, 144 / 255.f, 144 / 255.f, 1.0f });
            }
            //6
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 241 / 255.f, 187 / 255.f, 171 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 234 / 255.f, 151 / 255.f, 126 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 229 / 255.f, 115 / 255.f, 76 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 227 / 255.f, 82 / 255.f, 24 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 190 / 255.f, 61 / 255.f, 15 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 150 / 255.f, 48 / 255.f, 12 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 34 / 255.f, 8 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 79 / 255.f, 25 / 255.f, 6 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 113 / 255.f, 113 / 255.f, 113 / 255.f, 1.0f });
            }
            //7
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 245 / 255.f, 207 / 255.f, 169 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 240 / 255.f, 183 / 255.f, 122 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 236 / 255.f, 159 / 255.f, 74 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 234 / 255.f, 146 / 255.f, 37 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 193 / 255.f, 111 / 255.f, 28 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 152 / 255.f, 89 / 255.f, 22 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 110 / 255.f, 64 / 255.f, 16 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 47 / 255.f, 12 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 82 / 255.f, 82 / 255.f, 82 / 255.f, 1.0f });
            }
            //8
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 218 / 255.f, 170 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 244 / 255.f, 200 / 255.f, 124 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 241 / 255.f, 182 / 255.f, 77 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 239 / 255.f, 174 / 255.f, 44 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 196 / 255.f, 137 / 255.f, 34 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 154 / 255.f, 108 / 255.f, 27 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 111 / 255.f, 77 / 255.f, 19 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 56 / 255.f, 14 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 54 / 255.f, 54 / 255.f, 54 / 255.f, 1.0f });
            }
            //9
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 254 / 255.f, 243 / 255.f, 187 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 253 / 255.f, 237 / 255.f, 153 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 253 / 255.f, 231 / 255.f, 117 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 254 / 255.f, 232 / 255.f, 85 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 242 / 255.f, 212 / 255.f, 53 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 192 / 255.f, 169 / 255.f, 42 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 138 / 255.f, 120 / 255.f, 30 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 101 / 255.f, 87 / 255.f, 22 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 29 / 255.f, 29 / 255.f, 29 / 255.f, 1.0f });
            }
            //10
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 243 / 255.f, 185 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 243 / 255.f, 239 / 255.f, 148 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 239 / 255.f, 232 / 255.f, 111 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 235 / 255.f, 229 / 255.f, 76 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 208 / 255.f, 200 / 255.f, 55 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 164 / 255.f, 157 / 255.f, 43 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 118 / 255.f, 114 / 255.f, 31 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 86 / 255.f, 82 / 255.f, 21 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 9 / 255.f, 9 / 255.f, 9 / 255.f, 1.0f });
            }
            //11
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 218 / 255.f, 232 / 255.f, 182 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 198 / 255.f, 221 / 255.f, 143 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 181 / 255.f, 210 / 255.f, 103 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 154 / 255.f, 186 / 255.f, 76 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 130 / 255.f, 155 / 255.f, 64 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 102 / 255.f, 121 / 255.f, 50 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 74 / 255.f, 88 / 255.f, 36 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 64 / 255.f, 26 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
            }



            if (isHoveredPicker)
            {
                if (inpute::is_mouse_clicked(0, elements_count, false))
                {

                }
            }
            else
            {
                if (inpute::is_mouse_clicked(0, elements_count, false))
                {
                    active_picker = -1;
                    //hover_element = false;
                }
            }
        }
        else
        {
            //Bg
            if (isHovered)
            {
                drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Hovered);
                hover_element = true;
            }
            else
            {
                drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
            }

            //Color
            drawFilledRect(fvector2d{ pos.x + 4, pos.y + 4 }, size - 8, size - 8, *color);

            //Text
            fvector2d textPos = fvector2d{ pos.x + size + 5.0f, pos.y - xsize + 6.0f };
            TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

            if (isHovered && inpute::is_mouse_clicked(0, elements_count, false))
            {
                saved_color = *color;
                active_picker = elements_count;
            }
        }


        sameLine = false;
        last_element_pos = pos;
        //last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }

    void Render()
    {
        for (int i = 0; i < 128; i++)
        {
            if (PostRenderer::drawlist[i].type != -1)
            {
                //Filled Rect
                if (PostRenderer::drawlist[i].type == 1)
                {
                    menu::drawFilledRect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
                }
                //TextLeft
                else if (PostRenderer::drawlist[i].type == 2)
                {
                    canvas->k2_drawtext(font, (const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, fvector2d(0.98, 0.98), PostRenderer::drawlist[i].color, 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, PostRenderer::drawlist[i].outline, Colors::Text_Outline);
                }
                //TextCenter
                else if (PostRenderer::drawlist[i].type == 3)
                {
                    menu::TextCenter((const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
                }
                //Draw_Line
                else if (PostRenderer::drawlist[i].type == 4)
                {
                    Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
                }

                PostRenderer::drawlist[i].type = -1;
            }
        }
    }
}

float AngleDiff(float a, float b) {
    float diff = fmod(b - a + 180.0f, 360.0f) - 180.0f;
    return diff < -180.0f ? diff + 360.0f : diff;
}
namespace resolver_math {
    __forceinline float AngleDiff(float a, float b) {
        float diff = fmod(b - a + 180.0f, 360.0f) - 180.0f;
        return diff < -180.0f ? diff + 360.0f : diff;
    }
    __forceinline float clamp(float value, float min_val, float max_val) {
        return value < min_val ? min_val : (value > max_val ? max_val : value);
    }
    __forceinline float lerp(float a, float b, float t) { return a + t * (b - a); }
}

template<typename T, size_t N>
struct UltimateCircularBuffer {
    std::array<T, N> data;
    size_t head = 0;
    size_t size = 0;

    __forceinline void push_back(const T& value) {
        data[head] = value;
        head = (head + 1) % N;
        size = (size < N) ? size + 1 : N;
    }

    __forceinline T& operator[](size_t index) { return data[(head + N - size + index) % N]; }
    __forceinline const T& operator[](size_t index) const { return data[(head + N - size + index) % N]; }
    __forceinline T& back() { return (*this)[size - 1]; }
    __forceinline T& front() { return (*this)[0]; }
    __forceinline bool empty() const { return size == 0; }
    __forceinline void clear() { size = 0; head = 0; }
};
struct UltimateResolverData {
    UltimateCircularBuffer<frotator, 48> rotation_history;
    UltimateCircularBuffer<fvector, 32> position_history;
    UltimateCircularBuffer<fvector, 24> velocity_history;
    UltimateCircularBuffer<float, 96> yaw_pattern;
    UltimateCircularBuffer<float, 96> pitch_pattern;

    UltimateCircularBuffer<float, 32> movement_angles;
    UltimateCircularBuffer<float, 32> acceleration_pattern;
    UltimateCircularBuffer<bool, 64> visibility_history;

    float base_yaw = 0.0f;
    float real_yaw = 0.0f;
    float fake_yaw = 0.0f;
    float pattern_frequency = 0.0f;
    float pattern_amplitude = 0.0f;
    float resolver_confidence = 1.0f;
    float last_successful_resolve = 0.0f;
    float desync_range = 58.0f;

    uint32_t pattern_analysis_ticks = 0;
    uint32_t shots_fired = 0;
    uint32_t shots_hit = 0;
    uint32_t resolver_updates = 0;

    int8_t pattern_type = 0;
    int8_t resolved_side = 0;
    int8_t last_resolved_side = 0;
    int8_t network_role = 0;

    bool was_moving : 1;
    bool requires_prediction : 1;
    bool is_desyncing : 1;
    bool was_visible : 1;
    bool brute_force_active : 1;
    bool adaptive_learning : 1;

    int8_t brute_force_step = 0;
    float brute_force_timer = 0.0f;
    std::array<bool, 8> attempted_sides = { false };

    fvector last_resolved_head_pos;
    fvector last_original_head_pos;
    fvector last_predicted_pos;
    float last_confidence = 0.0f;
    int last_pattern_type = 0;

    UltimateResolverData() : was_moving(false), requires_prediction(false),
        is_desyncing(false), was_visible(false), brute_force_active(false),
        adaptive_learning(true) {
    }
};
static std::array<UltimateResolverData, 64> ultimate_resolver_states;
static std::array<ashootercharacter*, 64> resolver_target_map;
static std::array<float, 64> resolver_confidence_cache;
static uint32_t resolver_frame_counter = 0;
static uint32_t last_cleanup_frame = 0;
class UltimateValorantResolver {
private:
    ashootercharacter* m_target;
    ashootercharacter* m_local;
    UltimateResolverData* m_data;
    uint32_t m_target_index;
    float m_current_time;
    float m_last_update_time;

    float m_position_variance = 0.0f;
    float m_movement_consistency = 0.0f;
    float m_pattern_entropy = 0.0f;
    float m_yaw_variance = 0.0f;
    float m_pitch_variance = 0.0f;

public:
    UltimateValorantResolver(ashootercharacter* target, ashootercharacter* local)
        : m_target(target), m_local(local), m_current_time(0.0f), m_last_update_time(0.0f) {
        m_target_index = FindOrCreateTargetIndex(target);
        m_data = &ultimate_resolver_states[m_target_index];
        m_current_time = GetTickCount64() * 0.001f;
        m_last_update_time = m_current_time;
        InitializeResolver();
    }

    ~UltimateValorantResolver() {}

    fvector ResolveHeadPosition(fvector current_head, fvector velocity) {
        if (!IsValidForResolution()) return current_head;

        float delta_time = m_current_time - m_last_update_time;
        m_current_time = GetTickCount64() * 0.001f;

        UpdateTargetData();

        AnalyzeMovementAdvanced();
        AnalyzePositionPatterns();
        AnalyzeRotationAdvanced();
        AnalyzeNetworkStateAdvanced();
        AnalyzeVisibilityPattern();
        AnalyzeStrafingPatterns();

        fvector resolved_position = ApplyPositionResolution(current_head, velocity);

        m_data->last_successful_resolve = m_current_time;
        m_data->resolver_updates++;
        m_last_update_time = m_current_time;

        return resolved_position;
    }

    void RegisterShotFired() {
        m_data->shots_fired++;
        UpdateConfidenceMetrics();
    }

    void RegisterShotHit() {
        m_data->shots_hit++;
        UpdateConfidenceMetrics();
        if (m_data->shots_hit > 5) {
            float hit_ratio = float(m_data->shots_hit) / float(m_data->shots_fired);
            m_data->resolver_confidence = min(1.0f, hit_ratio + 0.1f);
            if (hit_ratio > 0.8f) m_data->adaptive_learning = false;
        }
    }

    float GetConfidence() const { return m_data->resolver_confidence; }
    int GetPatternType() const { return m_data->pattern_type; }
    UltimateResolverData* GetResolverData() const { return m_data; }

    void UpdateVisualizationData(fvector original_head, fvector resolved_head) {
        m_data->last_original_head_pos = original_head;
        m_data->last_resolved_head_pos = resolved_head;
        m_data->last_confidence = m_data->resolver_confidence;
        m_data->last_pattern_type = m_data->pattern_type;
    }

private:
    uint32_t FindOrCreateTargetIndex(ashootercharacter* target) {
        for (uint32_t i = 0; i < 64; i++) {
            if (resolver_target_map[i] == target) {
                resolver_confidence_cache[i] = ultimate_resolver_states[i].resolver_confidence;
                return i;
            }
        }

        uint32_t oldest_index = resolver_frame_counter % 64;
        for (uint32_t i = 0; i < 64; i++) {
            if (resolver_target_map[i] == nullptr) {
                oldest_index = i;
                break;
            }
        }

        resolver_target_map[oldest_index] = target;
        ultimate_resolver_states[oldest_index] = UltimateResolverData();
        resolver_confidence_cache[oldest_index] = 1.0f;

        return oldest_index;
    }

    bool IsValidForResolution() const {
        if (!m_target || !m_local) return false;
        if (!m_target->is_alive() || !m_local->is_alive()) return false;

        fvector target_pos = m_target->k2_get_actor_location();
        fvector local_pos = m_local->k2_get_actor_location();
        float distance = (target_pos - local_pos).size();
        return distance > 0.0f && distance < 5000.0f;
    }

    void InitializeResolver() {
        m_data->brute_force_active = false;
        m_data->brute_force_step = 0;
        m_data->brute_force_timer = 0.0f;
        m_data->attempted_sides.fill(false);
    }

    void UpdateTargetData() {
        frotator current_rot = m_target->K2_GetActorRotation();
        fvector current_pos = m_target->k2_get_actor_location();
        fvector current_vel = m_target->get_velocity();

        m_data->rotation_history.push_back(current_rot);
        m_data->position_history.push_back(current_pos);
        m_data->velocity_history.push_back(current_vel);
        m_data->yaw_pattern.push_back(current_rot.yaw);
        m_data->pitch_pattern.push_back(current_rot.pitch);

        fvector head_pos = m_target->get_mesh()->get_bone_location(8);

        bool is_visible = true;
        m_data->visibility_history.push_back(is_visible);

        m_data->pattern_analysis_ticks++;
        resolver_frame_counter++;
    }

    void AnalyzeMovementAdvanced() {
        if (m_data->velocity_history.size < 3) return;

        fvector current_vel = m_data->velocity_history.back();
        fvector previous_vel = m_data->velocity_history[m_data->velocity_history.size - 2];
        float speed = current_vel.size();
        m_data->was_moving = (speed > 10.0f);
        m_data->requires_prediction = (speed > 2.0f);

        if (speed > 1.0f) {
            float movement_angle = atan2(current_vel.y, current_vel.x) * (180.0f / 3.14159265358979323846f);
            m_data->movement_angles.push_back(movement_angle);
        }
        AnalyzeMovementConsistency();
    }

    void AnalyzeMovementConsistency() {
        if (m_data->movement_angles.size < 4) return;

        float consistency = 0.0f;
        for (size_t i = 1; i < m_data->movement_angles.size; i++) {
            float diff = std::abs(AngleDiff(m_data->movement_angles[i], m_data->movement_angles[i - 1]));
            consistency += (1.0f - (diff / 180.0f));
        }
        m_movement_consistency = consistency / (m_data->movement_angles.size - 1);
    }

    void AnalyzeStrafingPatterns() {
        if (m_data->velocity_history.size < 8) return;

        int direction_changes = 0;
        fvector prev_dir = m_data->velocity_history[0];

        for (size_t i = 1; i < m_data->velocity_history.size; i++) {
            fvector current_dir = m_data->velocity_history[i];
            float dot = prev_dir.dot(current_dir) / (prev_dir.size() * current_dir.size());

            if (dot < -0.5f) {
                direction_changes++;
            }
            prev_dir = current_dir;
        }

        if (direction_changes > m_data->velocity_history.size / 3) {
            m_data->is_desyncing = true;
        }
    }

    void AnalyzeRotationAdvanced() {
        if (m_data->yaw_pattern.size < 8) return;

        CalculateYawStatistics();
        DetectPatternType();
        CalculatePatternMetrics();
        AnalyzeDesyncRange();
    }

    void CalculateYawStatistics() {
        float sum = 0.0f, sum_sq = 0.0f;
        float min_yaw = FLT_MAX, max_yaw = -FLT_MAX;
        for (size_t i = 0; i < m_data->yaw_pattern.size; i++) {
            float yaw = m_data->yaw_pattern[i];
            sum += yaw;
            sum_sq += yaw * yaw;
            min_yaw = min(min_yaw, yaw);
            max_yaw = max(max_yaw, yaw);
        }
        float mean = sum / m_data->yaw_pattern.size;
        m_yaw_variance = (sum_sq / m_data->yaw_pattern.size) - (mean * mean);
        m_data->pattern_amplitude = max_yaw - min_yaw;
        m_data->base_yaw = mean;
    }

    void DetectPatternType() {
        if (m_yaw_variance > 5000.0f) {
            m_data->pattern_type = 1; // Spin
        }
        else if (m_yaw_variance > 500.0f && m_data->pattern_amplitude < 180.0f) {
            m_data->pattern_type = 2; // Jitter
        }
        else if (m_yaw_variance > 100.0f && m_data->pattern_amplitude > 45.0f) {
            m_data->pattern_type = 3; // Desync
        }
        else if (m_yaw_variance < 50.0f && m_data->was_moving) {
            m_data->pattern_type = 4; // Static while moving
        }
        else {
            m_data->pattern_type = 0; // Legit
        }
    }

    void CalculatePatternMetrics() {
        if (m_data->yaw_pattern.size < 16) return;

        int best_lag = 1;
        float max_correlation = -1.0f;

        for (int lag = 1; lag <= 8; lag++) {
            float correlation = 0.0f;
            int count = 0;

            for (size_t i = lag; i < m_data->yaw_pattern.size; i++) {
                correlation += std::cos(AngleDiff(m_data->yaw_pattern[i], m_data->yaw_pattern[i - lag]) * (3.14159265358979323846f / 180.0f));
                count++;
            }

            if (count > 0) {
                correlation /= count;
                if (correlation > max_correlation) {
                    max_correlation = correlation;
                    best_lag = lag;
                }
            }
        }

        m_data->pattern_frequency = (best_lag > 0) ? (1.0f / best_lag) : 0.0f;
    }

    void AnalyzeDesyncRange() {
        if (m_data->yaw_pattern.size < 12) return;

        std::map<float, int> angle_counts;
        for (size_t i = 0; i < m_data->yaw_pattern.size; i++) {
            float rounded = std::round(m_data->yaw_pattern[i] / 5.0f) * 5.0f;
            angle_counts[rounded]++;
        }

        float primary_angle = 0.0f;
        int max_count = 0;
        for (const auto& pair : angle_counts) {
            if (pair.second > max_count) {
                max_count = pair.second;
                primary_angle = pair.first;
            }
        }

        float secondary_angle = 0.0f;
        int second_count = 0;
        for (const auto& pair : angle_counts) {
            if (pair.second > second_count && std::abs(pair.first - primary_angle) > 10.0f) {
                second_count = pair.second;
                secondary_angle = pair.first;
            }
        }

        m_data->desync_range = std::abs(AngleDiff(primary_angle, secondary_angle));
    }

    void AnalyzeNetworkStateAdvanced() {
        m_data->network_role = m_target->GetLocalRole();

        switch (m_data->network_role) {
        case 3: // SimProxy
            m_data->resolver_confidence *= 1.1f;
            break;
        case 2: // AutoProxy
            m_data->resolver_confidence *= 0.9f;
            break;
        default:
            m_data->resolver_confidence *= 0.8f;
            break;
        }

        m_data->resolver_confidence = std::clamp(m_data->resolver_confidence, 0.1f, 1.0f);
    }

    void AnalyzeVisibilityPattern() {
        if (m_data->visibility_history.size < 8) return;

        int visible_count = 0;
        for (size_t i = 0; i < m_data->visibility_history.size; i++) {
            if (m_data->visibility_history[i]) visible_count++;
        }

        float visibility_ratio = float(visible_count) / m_data->visibility_history.size;
        m_data->was_visible = (visibility_ratio > 0.7f);
    }

    void AnalyzePositionPatterns() {
        if (m_data->position_history.size < 8) return;

        CalculatePositionStatistics();
    }

    void CalculatePositionStatistics() {
        if (m_data->position_history.size < 8) return;

        fvector sum = fvector(0, 0, 0);
        fvector sum_sq = fvector(0, 0, 0);

        for (size_t i = 0; i < m_data->position_history.size; i++) {
            fvector pos = m_data->position_history[i];
            sum = sum + pos;
            sum_sq.x += pos.x * pos.x;
            sum_sq.y += pos.y * pos.y;
            sum_sq.z += pos.z * pos.z;
        }

        fvector mean = sum / float(m_data->position_history.size);
        m_position_variance = (sum_sq.x / m_data->position_history.size) - (mean.x * mean.x);
    }

    fvector ApplyPositionResolution(fvector current_head, fvector velocity) {
        switch (m_data->pattern_type) {
        case 1: return ResolveSpinAA(current_head, velocity);
        case 2: return ResolveJitterAA(current_head, velocity);
        case 3: return ResolveDesyncAA(current_head, velocity);
        case 4: return ResolveStaticAA(current_head, velocity);
        default: return ResolveLegitAA(current_head, velocity);
        }
    }

    fvector ResolveSpinAA(fvector head, fvector velocity) {
        const float prediction_time = 0.1f;
        fvector predicted = head + velocity * prediction_time;

        if (m_data->pattern_frequency > 0.1f) {
            float phase = fmod(m_current_time * m_data->pattern_frequency * 360.0f, 360.0f);
            float radius = m_data->desync_range * 0.5f;
            predicted.x += cos(phase * (3.14159265358979323846f / 180.0f)) * radius;
            predicted.y += sin(phase * (3.14159265358979323846f / 180.0f)) * radius;
        }

        return predicted;
    }

    fvector ResolveJitterAA(fvector head, fvector velocity) {
        if (m_data->position_history.size < 4) return head;

        std::vector<fvector> valid_positions;
        fvector mean = head;

        for (size_t i = 0; i < m_data->position_history.size; i++) {
            fvector pos = m_data->position_history[i];
            float distance = (pos - mean).size();
            if (distance < 50.0f) {
                valid_positions.push_back(pos);
            }
        }

        if (!valid_positions.empty()) {
            fvector sum = fvector(0, 0, 0);
            for (const fvector& pos : valid_positions) sum = sum + pos;
            return sum / float(valid_positions.size());
        }

        return head;
    }

    fvector ResolveDesyncAA(fvector head, fvector velocity) {
        float side_multiplier = DetermineOptimalSide();

        float position_offset = m_data->desync_range * 0.1f * side_multiplier;

        fvector right_vec = m_target->GetActorRightVector();
        fvector corrected = head + right_vec * position_offset;

        if (velocity.size() > 5.0f) {
            corrected = corrected + velocity * 0.05f;
        }

        return corrected;
    }

    fvector ResolveStaticAA(fvector head, fvector velocity) {
        if (m_data->was_moving && !m_data->movement_angles.empty()) {
            float movement_angle = m_data->movement_angles.back();
            float movement_rad = movement_angle * (3.14159265358979323846f / 180.0f);

            head.x += cos(movement_rad) * 5.0f;
            head.y += sin(movement_rad) * 5.0f;
        }
        return head;
    }

    fvector ResolveLegitAA(fvector head, fvector velocity) {
        if (velocity.size() > 2.0f) {
            return head + velocity * 0.05f;
        }
        return head;
    }

    float DetermineOptimalSide() {
        float movement_side = DetermineMovementSide();
        float history_side = DetermineHistoricalSide();
        return (movement_side * 0.7f) + (history_side * 0.3f);
    }

    float DetermineMovementSide() {
        if (m_data->velocity_history.empty()) return 0.0f;

        fvector velocity = m_data->velocity_history.back();
        if (velocity.size() < 5.0f) return 0.0f;

        fvector right_vec = m_target->GetActorRightVector();
        float dot = velocity.dot(right_vec) / velocity.size();
        return (dot > 0.0f) ? 1.0f : -1.0f;
    }

    float DetermineHistoricalSide() {
        if (m_data->resolved_side == 0) return 0.0f;
        return (m_data->resolved_side > 0) ? 1.0f : -1.0f;
    }

    void UpdateConfidenceMetrics() {
        if (m_data->shots_fired > 0) {
            float hit_ratio = float(m_data->shots_hit) / float(m_data->shots_fired);
            if (hit_ratio > 0.7f) m_data->resolver_confidence = min(1.0f, m_data->resolver_confidence + 0.05f);
            else if (hit_ratio < 0.3f) m_data->resolver_confidence = max(0.1f, m_data->resolver_confidence - 0.1f);
        }
    }
};
class ResolverVisualizer {
private:
    static float m_pulse_time;
    static float m_rainbow_hue;
    static float m_hitmarker_time;
    static uobject* m_font;

public:

    static void SetFont(uobject* font) {
        m_font = font;
    }

    static void DrawModernResolverInfo(ucanvas* canvas, aplayercontroller* controller,
        ashootercharacter* target, UltimateResolverData* resolver_data) {
        try {
            if (!canvas || !controller || !target || !resolver_data || !m_font) return;

            m_pulse_time += 0.02f;
            if (m_pulse_time > 6.28318530718f) m_pulse_time = 0.0f;

            m_rainbow_hue += 0.001f;
            if (m_rainbow_hue > 1.0f) m_rainbow_hue = 0.0f;

            if (m_hitmarker_time > 0.0f) {
                m_hitmarker_time -= 0.05f;
            }

            fvector2d original_screen, resolved_screen;
            bool original_visible = false;
            bool resolved_visible = false;

            try {
                original_visible = controller->project_world_location_to_screen(resolver_data->last_original_head_pos, original_screen, true);
                resolved_visible = controller->project_world_location_to_screen(resolver_data->last_resolved_head_pos, resolved_screen, true);
            }
            catch (...) {
                return;
            }

            if (original_visible && resolved_visible) {
                try {
                    DrawAdvanced3DVisualization(canvas, original_screen, resolved_screen, resolver_data);
                }
                catch (...) {}
            }

            try {
                DrawModernResolverHUD(canvas, resolver_data, original_screen);
            }
            catch (...) {}

            if (m_hitmarker_time > 0.0f && resolved_visible) {
                try {
                    DrawModernHitmarker(canvas, resolved_screen, resolver_data->last_confidence);
                }
                catch (...) {}
            }
        }
        catch (...) {}
    }

    static void RegisterHit() {
        try {
            m_hitmarker_time = 2.0f;
        }
        catch (...) {}
    }

private:
    static void DrawAdvanced3DVisualization(ucanvas* canvas, const fvector2d& original,
        const fvector2d& resolved, UltimateResolverData* data) {
        try {
            if (!canvas || !data) return;

            float pulse = (sin(m_pulse_time) + 1.0f) * 0.5f;
            flinearcolor high_conf_color = { 0.0f, 1.0f, 0.0f, 1.0f };
            flinearcolor low_conf_color = { 1.0f, 0.0f, 0.0f, 1.0f };
            flinearcolor confidence_color = LerpColor(low_conf_color, high_conf_color, data->last_confidence);

            if (data->last_confidence > 0.8f) {
                confidence_color = HueToRGB(m_rainbow_hue);
                confidence_color.a = 0.8f + pulse * 0.2f;
            }


            if (!data->velocity_history.empty() && data->velocity_history.back().size() > 10.0f) {
                DrawMovementSphere(canvas, resolved);
            }


            DrawSimpleMarker(canvas, original, { 1.0f, 1.0f, 1.0f, 0.8f });
            DrawSimpleMarker(canvas, resolved, confidence_color);
        }
        catch (...) {}
    }

    static void DrawModernResolverHUD(ucanvas* canvas, UltimateResolverData* data, const fvector2d& screen_pos) {
        try {
            if (!canvas || !data) return;

            fvector2d hud_pos = { screen_pos.x - 42.5f, screen_pos.y - 140.0f };

            DrawModernPanel(canvas, hud_pos, { 120.0f, 110.0f }, { 0.08f, 0.08f, 0.12f, 0.95f });

            flinearcolor header_color = HueToRGB(m_rainbow_hue);
            float panel_center_X = hud_pos.x + (120.0f / 2.0f);

            DrawTextSafe(canvas, L"RESOLVER", { panel_center_X - 6.0f, hud_pos.y + 5.0f }, header_color, 0.8f);
            canvas->k2_drawline({ hud_pos.x + 10.0f, hud_pos.y + 22.0f }, { hud_pos.x + 110.0f, hud_pos.y + 22.0f }, 1.2f, { 0.3f, 0.3f, 0.4f, 0.7f });

            DrawAdvancedProgressBar(canvas, { hud_pos.x + 10.0f, hud_pos.y + 28.0f }, 100.0f, data->last_confidence, L"CONFIDENCE");
            float velocity_progress = 0.0f;
            if (!data->velocity_history.empty()) {
                velocity_progress = resolver_math::clamp(data->velocity_history.back().size() / 500.0f, 0.0f, 1.0f);
            }

            DrawAdvancedProgressBar(canvas, { hud_pos.x + 10.0f, hud_pos.y + 43.0f }, 100.0f, velocity_progress, L"VELOCITY");
            float prediction_progress = data->pattern_frequency;

            DrawAdvancedProgressBar(canvas, { hud_pos.x + 10.0f, hud_pos.y + 58.0f }, 100.0f, prediction_progress, L"PREDICTION");
            std::wstring desync_text = L"DESYNC: " + std::to_wstring((int)data->desync_range) + L"°";

            DrawTextSafe(canvas, desync_text.c_str(), { hud_pos.x + 10.0f, hud_pos.y + 73.0f }, { 0.8f, 0.8f, 1.0f, 1.0f }, 0.5f);
            std::wstring pattern_text = GetPatternTypeName(data->last_pattern_type);

            DrawTextSafe(canvas, pattern_text.c_str(), { hud_pos.x + 70.0f, hud_pos.y + 73.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.5f);
            std::wstring shots_text = L"SHOTS: " + std::to_wstring(data->shots_fired);

            DrawTextSafe(canvas, shots_text.c_str(), { hud_pos.x + 10.0f, hud_pos.y + 85.0f }, { 0.9f, 0.9f, 0.9f, 0.9f }, 0.45f);
            if (data->shots_fired > 0) {
                float hit_rate = (float)data->shots_hit / (float)data->shots_fired * 100.0f;
                std::wstring hit_text = L"HIT: " + std::to_wstring((int)hit_rate) + L"%";
                DrawTextSafe(canvas, hit_text.c_str(), { hud_pos.x + 70.0f, hud_pos.y + 85.0f }, { 0.7f, 1.0f, 0.7f, 0.9f }, 0.45f);
            }


            std::wstring state_text = data->resolver_confidence > 0.7f ? L"OPTIMAL" : L"LEARNING";
            flinearcolor state_color = data->resolver_confidence > 0.7f ? flinearcolor{ 0.2f, 0.8f, 0.2f, 0.9f } : flinearcolor{ 0.8f, 0.8f, 0.2f, 0.9f };
            DrawTextSafe(canvas, state_text.c_str(), { hud_pos.x + 10.0f, hud_pos.y + 97.0f }, state_color, 0.45f);
        }
        catch (...) {}
    }


    static void DrawMovementSphere(ucanvas* canvas, const fvector2d& center) {
        try {
            if (!canvas) return;

            float sphere_radius = 6.0f;
            flinearcolor sphere_color = { 1.0f, 1.0f, 1.0f, 0.7f };


            int segments = 8;
            for (int i = 0; i < segments; i++) {
                float angle1 = (i * 2 * 3.14159265358979323846f) / segments;
                float angle2 = ((i + 1) * 2 * 3.14159265358979323846f) / segments;

                fvector2d point1 = center + fvector2d(cos(angle1) * sphere_radius, sin(angle1) * sphere_radius);
                fvector2d point2 = center + fvector2d(cos(angle2) * sphere_radius, sin(angle2) * sphere_radius);

                canvas->k2_drawline(point1, point2, 1.5f, sphere_color);
            }
        }
        catch (...) {}
    }

    static void DrawSimpleMarker(ucanvas* canvas, const fvector2d& position, const flinearcolor& color) {
        try {
            if (!canvas) return;

            float size = 4.0f;
            canvas->k2_drawline({ position.x - size, position.y }, { position.x + size, position.y }, 1.5f, color);
            canvas->k2_drawline({ position.x, position.y - size }, { position.x, position.y + size }, 1.5f, color);
        }
        catch (...) {}
    }

    static void DrawAdvancedProgressBar(ucanvas* canvas, const fvector2d& position, float width,
        float progress, const wchar_t* label) {
        try {
            if (!canvas) return;

            // BACKGROUND
            fvector2d bg_start = position;
            fvector2d bg_end = fvector2d(position.x + width, position.y);
            canvas->k2_drawline(bg_start, bg_end, 4.0f, flinearcolor(0.2f, 0.2f, 0.2f, 0.9f));

            // PROGRESS
            flinearcolor progress_color;
            if (progress < 0.3f) progress_color = flinearcolor(1.0f, 0.0f, 0.0f, 0.9f);
            else if (progress < 0.7f) progress_color = flinearcolor(1.0f, 1.0f, 0.0f, 0.9f);
            else progress_color = flinearcolor(0.0f, 1.0f, 0.0f, 0.9f);

            fvector2d progress_end = fvector2d(position.x + width * progress, position.y);
            canvas->k2_drawline(position, progress_end, 4.0f, progress_color);

            // LABEL
            std::wstring progress_text = std::to_wstring(int(progress * 100)) + L"%";

            // LABEL YAZISI
            DrawTextSafe(canvas, label, fvector2d(position.x, position.y - 8.0f), flinearcolor(1.0f, 1.0f, 1.0f, 1.0f), 0.5f);

            // YÜZDE DEĞERİ
            DrawTextSafe(canvas, progress_text.c_str(), fvector2d(position.x + width + 2.0f, position.y - 8.0f), flinearcolor(1.0f, 1.0f, 1.0f, 1.0f), 0.5f);
        }
        catch (...) {}
    }

    static void DrawModernPanel(ucanvas* canvas, const fvector2d& position, const fvector2d& size,
        const flinearcolor& color) {
        try {
            if (!canvas) return;

            fvector2d points[4] = {
                position,
                {position.x + size.x, position.y},
                {position.x + size.x, position.y + size.y},
                {position.x, position.y + size.y}
            };

            // DAHA KALIN ÇERÇEVE
            for (int i = 0; i < 4; i++) {
                int next = (i + 1) % 4;
                canvas->k2_drawline(points[i], points[next], 1.5f, color);
            }

            // DAHA BELİRGİN GRADIENT BORDER
            flinearcolor top_border_color = { 0.4f, 0.6f, 0.9f, 0.7f };
            canvas->k2_drawline(points[0], points[1], 1.2f, top_border_color);
        }
        catch (...) {}
    }

    static void DrawModernHitmarker(ucanvas* canvas, const fvector2d& position, float confidence) {
        try {
            if (!canvas) return;

            float hitmarker_size = 8.0f + m_hitmarker_time * 3.0f;
            float pulse = (sin(m_hitmarker_time * 10.0f) + 1.0f) * 0.5f;

            flinearcolor hitmarker_color = { 1.0f, 1.0f, 0.0f, 0.8f * pulse };

            canvas->k2_drawline({ position.x - hitmarker_size, position.y }, { position.x - 2.0f, position.y }, 2.0f, hitmarker_color);
            canvas->k2_drawline({ position.x + hitmarker_size, position.y }, { position.x + 2.0f, position.y }, 2.0f, hitmarker_color);
            canvas->k2_drawline({ position.x, position.y - hitmarker_size }, { position.x, position.y - 2.0f }, 2.0f, hitmarker_color);
            canvas->k2_drawline({ position.x, position.y + hitmarker_size }, { position.x, position.y + 2.0f }, 2.0f, hitmarker_color);
        }
        catch (...) {}
    }

    static void DrawTextSafe(ucanvas* canvas, const wchar_t* text, const fvector2d& position,
        const flinearcolor& color, float scale) {
        try {
            if (!canvas || !text) return;

            canvas->k2_drawtext(menu::font, fstring(text), position, fvector2d(scale, scale), color, 0.0f,
                flinearcolor(0.0f, 0.0f, 0.0f, 0.0f), fvector2d(0.0f, 0.0f),
                true, true, true, flinearcolor(0.0f, 0.0f, 0.0f, 0.0f));
        }
        catch (...) {}
    }

    static flinearcolor HueToRGB(float hue) {
        try {
            float r = std::abs(hue * 6.0f - 3.0f) - 1.0f;
            float g = 2.0f - std::abs(hue * 6.0f - 2.0f);
            float b = 2.0f - std::abs(hue * 6.0f - 4.0f);

            return { resolver_math::clamp(r, 0.0f, 1.0f),
                     resolver_math::clamp(g, 0.0f, 1.0f),
                     resolver_math::clamp(b, 0.0f, 1.0f), 1.0f };
        }
        catch (...) {
            return { 1.0f, 1.0f, 1.0f, 1.0f };
        }
    }

    static flinearcolor LerpColor(const flinearcolor& a, const flinearcolor& b, float t) {
        try {
            return { resolver_math::lerp(a.r, b.r, t),
                     resolver_math::lerp(a.g, b.g, t),
                     resolver_math::lerp(a.b, b.b, t),
                     resolver_math::lerp(a.a, b.a, t) };
        }
        catch (...) {
            return a;
        }
    }

    static std::wstring GetPatternTypeName(int pattern_type) {
        try {
            switch (pattern_type) {
            case 0: return L"LEGIT";
            case 1: return L"SPIN";
            case 2: return L"JITTER";
            case 3: return L"DESYNC";
            case 4: return L"STATIC";
            default: return L"UNKNOWN";
            }
        }
        catch (...) {
            return L"ERROR";
        }
    }
};
float ResolverVisualizer::m_pulse_time = 0.0f;
float ResolverVisualizer::m_rainbow_hue = 0.0f;
float ResolverVisualizer::m_hitmarker_time = 0.0f;
uobject* ResolverVisualizer::m_font = nullptr;

void ResetOffset() {
    menu::offset_x = 23;
    menu::offset_y = 43; // Posición base después de los tabs
}

void* m_memset(void* dest, char c, unsigned int len)
{
    
    unsigned int i;
    unsigned int fill;
    unsigned int chunks = len / sizeof(fill);
    char* char_dest = (char*)dest;
    unsigned int* uint_dest = (unsigned int*)dest;
    fill = (c << 24) + (c << 16) + (c << 8) + c;

    for (i = len; i > chunks * sizeof(fill); i--) {
        char_dest[i - 1] = c;
    }

    for (i = chunks; i > 0; i--) {
        uint_dest[i - 1] = fill;
    }

    return dest;
}

void* m_memcpy(void* dest, void* src, unsigned int len)
{
    
    unsigned int i;
    char* char_src = (char*)src;
    char* char_dest = (char*)dest;
    for (i = 0; i < len; i++) {
        char_dest[i] = char_src[i];
    }
    return dest;
}
flinearcolor HSVtoRGB(float H, float S, float V)
{
    H = std::fmod(H, 1.0f);
    if (H < 0.0f) H += 1.0f;

    float R, G, B;

    int i = static_cast<int>(H * 6);
    float f = H * 6 - i;
    float p = V * (1.0f - S);
    float q = V * (1.0f - f * S);
    float t = V * (1.0f - (1.0f - f) * S);

    switch (i % 6)
    {
    case 0: R = V; G = t; B = p; break;
    case 1: R = q; G = V; B = p; break;
    case 2: R = p; G = V; B = t; break;
    case 3: R = p; G = q; B = V; break;
    case 4: R = t; G = p; B = V; break;
    case 5: R = V; G = p; B = q; break;
    default: R = G = B = 0.0f; break; // fallback
    }

    return flinearcolor(R, G, B, 1.0f);
}

float GetTimeSeconds()
{
    using namespace std::chrono;
    static auto startTime = high_resolution_clock::now();
    auto now = high_resolution_clock::now();
    return duration<float>(now - startTime).count();
}

void DrawChineseHat(fvector head, aplayercontroller* controller, ucanvas* canvas)
{
    static float colorRotation = 0.0f;
    colorRotation = std::fmod(colorRotation + 0.001f, 1.0f);
    constexpr float twoPi = 2.0f * static_cast<float>(M_PI);

    fvector base_center = head + fvector(0, 0, 12.5f + sinf(GetTimeSeconds() * 2.0f) * 5.0f);
    fvector apex_world = base_center + fvector(0, 0, 25.0f);

    fvector2d apex_2D;
    if (!controller->project_world_location_to_screen(apex_world, apex_2D, false)) return;

    std::vector<fvector2d> circle_dots;
    circle_dots.reserve(50);

    const float radius = 50.0f;

    for (int i = 0; i < 50; i++) {
        float angle = twoPi * i / 50;
        fvector circle_point_world = base_center + fvector(cosf(angle), sinf(angle), 0.0f) * radius;

        fvector2d circle_point_2D;
        if (!controller->project_world_location_to_screen(circle_point_world, circle_point_2D, false))
            continue;

        circle_dots.emplace_back(circle_point_2D);

        float hue = std::fmod((float)i / 50 + colorRotation, 1.0f);
        flinearcolor lineColor = HSVtoRGB(hue, 1.0f, 1.0f);

        canvas->k2_drawline(apex_2D, circle_point_2D, 1.3f, lineColor);

    }

    for (int i = 0; i < circle_dots.size(); i++) {
        float hue = std::fmod((float)i / 50 + colorRotation, 1.0f);
        flinearcolor ringColor = HSVtoRGB(hue, 1.0f, 1.0f);
        const fvector2d& p1 = circle_dots[i];
        const fvector2d& p2 = circle_dots[(i + 1) % circle_dots.size()];
        canvas->k2_drawline(p1, p2, 1.0f, ringColor);

    }
}
static void partyhat(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, fvector head, fvector base, ucanvas* canvas)
{
    if (!canvas || !my_controller)
        return;

    fvector tip = { head.x, head.y, head.z + 20.0f };
    fvector2d screen_tip;

    if (!my_controller->project_world_location_to_screen(tip, screen_tip, false))
        return;

    tarray<fvector2d> base_points_2d;


    static float total_time = 0.0f;
    total_time += 0.016f;
    float time = total_time;

    float rotation_speed = 1.5f;
    float rotation = time * rotation_speed;

    float radius = 30.0f;
    int segments = 16;

    for (int i = 0; i < segments; ++i)
    {
        float angle = (2.0f * 3.14159265358979323846f / segments) * i + rotation;
        float x = cosf(angle) * radius;
        float y = sinf(angle) * radius;

        fvector base_point_3d = { head.x + x, head.y + y, head.z + 5.0f };
        fvector2d screen_base;

        if (my_controller->project_world_location_to_screen(base_point_3d, screen_base, false))
        {
            base_points_2d.add(screen_base);
        }
    }

    if (base_points_2d.size() < 2)
        return;

    float thickness = 1.0f;
    float outline_thickness = thickness + 1.8f;
    bool bOutline = false;


    for (int i = 0; i < base_points_2d.size(); ++i)
    {
        int next = (i + 1) % base_points_2d.size();


        float r = (sinf(time * 2.0f + i * 0.3f) + 1.0f) * 0.5f;
        float g = (sinf(time * 2.0f + i * 0.3f + 2.0f) + 1.0f) * 0.5f;
        float b = (sinf(time * 2.0f + i * 0.3f + 4.0f) + 1.0f) * 0.5f;
        flinearcolor rainbow_color = { r, g, b, 0.8f };


        for (float t = 0.0f; t <= 1.0f; t += 0.1f) {
            fvector2d interpolated_point = {
                screen_tip.x + (base_points_2d[i].x - screen_tip.x) * t,
                screen_tip.y + (base_points_2d[i].y - screen_tip.y) * t
            };

            fvector2d interpolated_next = {
                screen_tip.x + (base_points_2d[next].x - screen_tip.x) * t,
                screen_tip.y + (base_points_2d[next].y - screen_tip.y) * t
            };

            canvas->k2_drawline(interpolated_point, interpolated_next, 2.0f, rainbow_color);
        }


        canvas->k2_drawline(screen_tip, base_points_2d[i], 2.0f, rainbow_color);
        canvas->k2_drawline(base_points_2d[i], base_points_2d[next], 2.0f, rainbow_color);
        canvas->k2_drawline(base_points_2d[next], screen_tip, 2.0f, rainbow_color);
    }


    for (int i = 0; i < base_points_2d.size(); ++i)
    {
        int next = (i + 1) % base_points_2d.size();


        float r = (sinf(time * 2.0f + i * 0.3f) + 1.0f) * 0.5f;
        float g = (sinf(time * 2.0f + i * 0.3f + 2.0f) + 1.0f) * 0.5f;
        float b = (sinf(time * 2.0f + i * 0.3f + 4.0f) + 1.0f) * 0.5f;
        flinearcolor rainbow_color = { r, g, b, 1.0f };


        canvas->k2_drawline(screen_tip, base_points_2d[i], 3.0f, rainbow_color);
        canvas->k2_drawline(base_points_2d[i], base_points_2d[next], 3.0f, rainbow_color);
    }
}



static std::unordered_map<uobject*, std::string> objectNameCache;
inline std::string get_cached_name(uobject* obj) {
    auto it = objectNameCache.find(obj);
    if (it != objectNameCache.end()) return it->second;
    std::string name = system::get_object_name(obj).to_str();
    objectNameCache[obj] = name;
    return name;
}
static const std::pair<const char*, const char*> kWeaponToFamily[] = {
    {"AssaultRifle_AK_C",           "AssaultRifle_AK"},
    {"AssaultRifle_ACR_C",          "AssaultRifle_ACR"},
    {"BoltSniper_C",                "BoltSniper"},
    {"AssaultRifle_Burst_C",        "AssaultRifle_Burst"},
    {"AutomaticPistol_C",           "AutomaticPistol"},
    {"DMR_C",                        "DMR"},
    {"RevolverPistol_C",            "Revolver"},
    {"LugerPistol_C",               "LugerPistol"},
    {"SubMachineGun_MP5_C",         "SubMachineGun_MP5"},
    {"Vector_C",                    "SubMachineGun_Vector"},
    {"BasePistol_C",                "BasePistol"},
    {"LeverSniperRifle_C",          "LeverSniper"},
    {"DS_Gun_C",                    "DS_Gun"},
    {"Ability_Melee_Base_C",        "Melee"},
    {"HeavyMachineGun_C",           "HeavyMachineGun"},
    {"LightMachineGun_C",           "LightMachineGun"},
    {"SawedOffShotgun_C",           "SawedOffShotgun"},
    {"AutomaticShotgun_C",          "AutomaticShotgun"},
    {"PumpShotgun_C",               "PumpShotgun"},
};
struct SkinItem {
    std::wstring name;
};
static std::unordered_map<std::string, std::vector<SkinItem>> g_byFamily;
static std::unordered_map<std::string, int> g_selectedIndexForFamily;
std::wstring get_chosen_skin(const std::string& weapon_name) {


    std::string family;
    for (const auto& [key, fam] : kWeaponToFamily) {
        if (weapon_name == key) {
            family = fam;
            break;
        }
    }

    if (family.empty()) {

        return L"";
    }



    auto it = g_byFamily.find(family);
    if (it == g_byFamily.end()) {
        return L"";
    }

    int index = g_selectedIndexForFamily[family];
    auto& skins = it->second;

    if (index < 0 || index >= static_cast<int>(skins.size())) {

        return L"";
    }

    return skins[index].name;
}
static std::string family_from_logged_name(const std::wstring& wname) {
    std::string s(wname.begin(), wname.end());

    const std::string pre = "Default__";
    const std::string suf = "_PrimaryAsset_C";
    if (s.rfind(pre, 0) == 0) s.erase(0, pre.size());
    if (s.size() >= suf.size() && s.compare(s.size() - suf.size(), suf.size(), suf) == 0)
        s.erase(s.size() - suf.size());

    if (s.rfind("AK_", 0) == 0) return "AssaultRifle_AK";
    if (s.rfind("Melee_", 0) == 0) return "Melee";
    if (s.rfind("Vector_", 0) == 0) return "SubMachineGun_Vector";
    if (s.rfind("Luger_", 0) == 0) return "LugerPistol";

    auto u1 = s.find('_');
    if (u1 == std::string::npos) return s;
    auto u2 = s.find('_', u1 + 1);
    return (u2 == std::string::npos) ? s.substr(0, u1) : s.substr(0, u2);
}
static void store_skin_by_name(const std::wstring& fullName) {
    std::string fam = family_from_logged_name(fullName);
    auto& vec = g_byFamily[fam];

    if (std::none_of(vec.begin(), vec.end(), [&](const SkinItem& it) { return it.name == fullName; })) {
        vec.push_back(SkinItem{ fullName });

        if (vec.size() == 1) {
            g_selectedIndexForFamily[fam] = 0;
        }
    }
}
static std::unordered_map<equippable_skin_data_asset*, std::wstring> g_skinNameCache;
static const std::wstring& get_skin_name_cached(equippable_skin_data_asset* p, bool refresh = false) {
    static const std::wstring kEmpty;
    if (!p) return kEmpty;

    if (!refresh) {
        auto it = g_skinNameCache.find(p);
        if (it != g_skinNameCache.end()) return it->second;
    }

    // Query once, then copy into a stable std::wstring
    fstring f = system::get_object_name(p);
    auto [it, _] = g_skinNameCache.emplace(p, std::wstring(f.c_str()));
    if (!_) it->second.assign(f.c_str()); // if already existed & refresh==true
    return it->second;
}
std::string normalize_weapon_class(const std::string& weapon) {
    size_t pos = weapon.find_last_of('_');
    if (pos != std::string::npos && pos + 1 < weapon.size() &&
        std::all_of(weapon.begin() + pos + 1, weapon.end(), ::isdigit)) {
        return weapon.substr(0, pos);
    }
    return weapon;
}

#define MAX_TRACERS 100
#define TRACER_LIFETIME 7.0f
#define MAX_COLORS 20
#define MAX_TRACERS2 100
struct Tracer {
    fvector worldStart;    // 1
    fvector worldEnd;      // 2
    flinearcolor color;    // 3 - YER DEĞİŞTİRDİ!
    float timeCreated;     // 4 - YER DEĞİŞTİRDİ!
    bool bValid;           // 5 - YENİ EKLENDİ!

    Tracer() : bValid(false) {} // Constructor
};

Tracer tracers[MAX_TRACERS2];
int currentTracerIndex = 0;

struct FFiringResults {
    fvector FiringDirection;
    fvector StartLocation;
};


struct FCustom_OnShot_Params
{
    firing_state* FiringState;
    int32_t ShotIndex;
    bool bTracerEnabled;
    bool bWasLastShot;
    char Pad_E[0x2];
    tarray<FFiringResults> FiringResults;
};
bool ClipLineToScreen(fvector2d& start, fvector2d& end, float screenWidth, float screenHeight)
{
    auto ComputeOutCode = [](float x, float y, float w, float h) -> int {
        int code = 0;
        if (x < 0) code |= 1;
        if (x > w) code |= 2;
        if (y < 0) code |= 4;
        if (y > h) code |= 8;
        return code;
        };

    int outcode0 = ComputeOutCode(start.x, start.y, screenWidth, screenHeight);
    int outcode1 = ComputeOutCode(end.x, end.y, screenWidth, screenHeight);

    while (true)
    {
        if (!(outcode0 | outcode1)) return true;
        if (outcode0 & outcode1) return false;

        int outcodeOut = outcode0 ? outcode0 : outcode1;
        float x, y;

        if (outcodeOut & 8) {
            x = start.x + (end.x - start.x) * (screenHeight - start.y) / (end.y - start.y);
            y = screenHeight;
        }
        else if (outcodeOut & 4) {
            x = start.x + (end.x - start.x) * (0 - start.y) / (end.y - start.y);
            y = 0;
        }
        else if (outcodeOut & 2) {
            y = start.y + (end.y - start.y) * (screenWidth - start.x) / (end.x - start.x);
            x = screenWidth;
        }
        else {
            y = start.y + (end.y - start.y) * (0 - start.x) / (end.x - start.x);
            x = 0;
        }

        if (outcodeOut == outcode0) {
            start.x = x;
            start.y = y;
            outcode0 = ComputeOutCode(start.x, start.y, screenWidth, screenHeight);
        }
        else {
            end.x = x;
            end.y = y;
            outcode1 = ComputeOutCode(end.x, end.y, screenWidth, screenHeight);
        }
    }
}
struct FWallPenetrationSpan
{
    float Length = 0.f;
    bool bIsPlayable = false;
};


enum class EWallBangResult
{
    Clear,
    NotBangable,
    Bangable_NoKill,
    Bangable_CanKill
};


enum class ETraceResult
{
    Clear,
    Smoke,
    Wall_NotBangable,
    Wall_Bangable_NoKill,
    Wall_Bangable_CanKill
};











bool PerformLineTrace(fvector Start, fvector Direction, float MaxDistance, fvector& OutHitLocation)
{
    UWorld2* g_World = UWorld2::GetWorld();
    if (!g_World)
    {
        OutHitLocation = Start + (Direction * MaxDistance);
        return false;
    }

    fvector End = Start + (Direction * MaxDistance);
    FHitResult HitResult;
    tarray<uobject*> ignoreActors;

    bool bHit = ShooterGameBlueprints::ares_line_trace_single_by_channel(
        UWorld2::GetWorld(),
        Start,
        End,
        ignoreActors,
        &HitResult,
        ECollisionChannel::ECC_Visibility,
        false,
        true
    );

    if (bHit)
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
    else {
        OutHitLocation = End;
        return false;
    }
}


float GetCurrentGameTime()
{
    return GetTickCount64() / 1000.0f;
}

static bool didLogInit = false;

struct BulletImpact {
    fvector hitLocation;
    fvector hitNormal;
    float timeCreated;
    flinearcolor color;
    float size;
    bool bValid;
};

#define MAX_IMPACTS 50
#define IMPACT_LIFETIME 2.0f

BulletImpact bulletImpacts[MAX_IMPACTS];
int currentImpactIndex = 0;

void AddBulletImpact(fvector location, fvector normal, flinearcolor color, float size = 25.0f)
{
    if (currentImpactIndex >= MAX_IMPACTS) {
        currentImpactIndex = 0;
    }

    bulletImpacts[currentImpactIndex] = {
        location,
        normal,
        GetCurrentGameTime(),
        color,
        size,
        true
    };

    currentImpactIndex = (currentImpactIndex + 1) % MAX_IMPACTS;
}

void hooks::hkProcessEvent(void* class_, uobject* function, void* params, uintptr_t magic, void* original_fn)
{
    static bool didLogInit = false;
    if (!didLogInit)
    {
        didLogInit = true;
    }

    if (!function || !class_)
        return hooks::oProcessEvent(class_, function, params, magic, original_fn);

    fstring functionName = system::get_object_name(function);

    if (functionName.to_str() == crypt("Custom_OnShot").decrypt() || functionName.to_str().find("OnShot__DelegateSignature") != std::string::npos)
    {
        if (!params) {
            return hooks::oProcessEvent(class_, function, params, magic, original_fn);
        }

        auto* shotParams = static_cast<FCustom_OnShot_Params*>(params);

        if (!shotParams) {
            return hooks::oProcessEvent(class_, function, params, magic, original_fn);
        }

        if (shotParams->bTracerEnabled && shotParams->FiringResults.Num() > 0)
        {
            float currentTime = GetCurrentGameTime();

            static const std::vector<flinearcolor> vibrantColors = {
                flinearcolor(1.0f, 0.0f, 0.0f, 1.0f),
                flinearcolor(0.0f, 1.0f, 0.0f, 1.0f),
                flinearcolor(0.0f, 0.5f, 1.0f, 1.0f),
                flinearcolor(1.0f, 1.0f, 0.0f, 1.0f),
                flinearcolor(1.0f, 0.0f, 1.0f, 1.0f),
                flinearcolor(0.0f, 1.0f, 1.0f, 1.0f),
                flinearcolor(1.0f, 0.5f, 0.0f, 1.0f),
                flinearcolor(0.5f, 0.0f, 1.0f, 1.0f)
            };

            for (int i = 0; i < shotParams->FiringResults.Num(); i++)
            {
                FFiringResults& result = shotParams->FiringResults[i];
                fvector actualEndLocation;
                float maxRange = 50000.0f;

                bool bHit = PerformLineTrace(
                    result.StartLocation,
                    result.FiringDirection,
                    maxRange,
                    actualEndLocation
                );

                static int colorCounter = 0;
                int colorIndex = colorCounter % vibrantColors.size();
                colorCounter++;

                flinearcolor tracerColor = vibrantColors[colorIndex];
                tracerColor.a = 1.0f;

                if (currentTracerIndex >= MAX_TRACERS) {
                    currentTracerIndex = 0;
                }

                tracers[currentTracerIndex].worldStart = result.StartLocation;
                tracers[currentTracerIndex].worldEnd = actualEndLocation;
                tracers[currentTracerIndex].color = tracerColor;
                tracers[currentTracerIndex].timeCreated = currentTime;
                tracers[currentTracerIndex].bValid = true;

                currentTracerIndex = (currentTracerIndex + 1) % MAX_TRACERS;

                if (bHit)
                {
                    fvector hitNormal = (actualEndLocation - result.StartLocation).GetSafeNormal();
                    float impactSize = 25.0f;
                    AddBulletImpact(actualEndLocation, hitNormal, tracerColor, impactSize);
                }

            }


        }
    }

    hooks::oProcessEvent(class_, function, params, magic, original_fn);

}

#define MAX_TRACERS2 100
#define TRACER_LIFETIME2 3.5f   // MUST be > 2s for visible fade
shadow_vmt vmt_hook;

void InstallProcessEventHook(currentequippable* anyUObject)
{
    if (!anyUObject) return;
    constexpr int ProcessEventIndex = 0x53;

    static shadow_vmt viewport_hook;
    viewport_hook.hook<hooks::tProcessEvent>(
        memory::module_base,
        (uintptr_t)anyUObject,
        ProcessEventIndex,
        hooks::hkProcessEvent,
        &hooks::oProcessEvent
    );
}
frotator VectorToRotator(const fvector& dir)
{
    frotator rot;
    rot.pitch = atan2f(dir.z, sqrtf(dir.x * dir.x + dir.y * dir.y)) * (180.f / 3.14159265f);
    rot.yaw = atan2f(dir.y, dir.x) * (180.f / 3.14159265f);
    rot.roll = 0.f;
    return rot;
}


inline fvector VectorFromRotator(const frotator& Rot)
{
    float CP = cosf(Rot.pitch * (3.14159265f / 180.f));
    float SP = sinf(Rot.pitch * (3.14159265f / 180.f));
    float CY = cosf(Rot.yaw * (3.14159265f / 180.f));
    float SY = sinf(Rot.yaw * (3.14159265f / 180.f));

    return fvector(CP * CY, CP * SY, SP);
}

void __stdcall hk_death(ashootercharacter* shooter_character, UDamageResponse* a2) {
    try {
        SPOOF_FUNC;
        if (!shooter_character || !memory::IsValidPointer((uintptr_t)shooter_character)) {
            return hooks::oHkDeath(shooter_character, a2);
        }

        acknowledgedpawn* pawn = controller->get_acknowledged_pawn();
        ashootercharacter* CharacterContext = (ashootercharacter*)character;
        acknowledgedpawn* LPawnContext = (acknowledgedpawn*)pawn;


        if (!CharacterContext || !LPawnContext || !a2) {
            return hooks::oHkDeath(shooter_character, a2);
        }

        if (!memory::IsValidPointer((uintptr_t)CharacterContext) ||
            !memory::IsValidPointer((uintptr_t)LPawnContext) ||
            !memory::IsValidPointer((uintptr_t)a2)) {
            return hooks::oHkDeath(shooter_character, a2);
        }

        auto component = (uintptr_t)memory::read<uobject*>((uintptr_t)shooter_character + offsets::death_reaction_component_offset);
        if (!component || !memory::IsValidPointer(component)) {
            return hooks::oHkDeath(shooter_character, a2);
        }

        BYTE b1 = memory::read<BYTE>(component + 0x15A);
        BYTE b2 = memory::read<BYTE>(component + 0x168);

        if (!(b1 == 0 || b2 == 1)) {
            return hooks::oHkDeath(shooter_character, a2);
        }

        auto Killer = a2->GetDamageCauser();

        auto Equippable = a2->GetEquippableUsed();

        if (!Killer || !Equippable ||
            !memory::IsValidPointer((uintptr_t)Killer) ||
            !memory::IsValidPointer((uintptr_t)Equippable)) {

            return hooks::oHkDeath(shooter_character, a2);
        }

        auto ItemSlot = Equippable->GetItemSlot();

        if (!UWorldSave || !memory::IsValidPointer((uintptr_t)UWorldSave)) {
            return hooks::oHkDeath(shooter_character, a2);
        }

        tarray<ashootercharacter*> enemiese = blueprints::find_all_shooters_with_alliance(UWorldSave, character, earesalliance::enemy, false, true);
        myweapon = character->get_inventory()->get_current_equippable();

        if (globals::misc::finisher || character->is_alive() && character->health() > 0 && character && memory::IsValidPointer((uintptr_t)character)) {
            if (Killer == LPawnContext) {
                int numEnemies = enemiese.size();
                for (int idx = 0; idx < enemiese.size(); ++idx) {
                    if (enemiese[idx] == shooter_character) {
                        numEnemies -= 1;
                        break;
                    }
                }

                bool shouldPlayFinisher = globals::misc::onlylastkill ? (enemiese.size() == 0) : true;

                std::string raw_weapon = get_cached_name(myweapon);
                std::string weapon_name = normalize_weapon_class(raw_weapon.c_str());
                if (globals::misc::finisher) {
                    auto applyFinisher = [&]() {
                        std::wstring skin = get_chosen_skin(weapon_name);

                        uobject* finisher = get_finisher_from_skin(skin.c_str());


                        static uobject* dummyFinisher = uobject::find_object<uobject*>(L"FXC_Finisher_Invalid_Victim_C", reinterpret_cast<uobject*>(-1));
                        memory::write<uobject*>(component + offsets::montage_effect_override_offset, dummyFinisher);
                        memory::write<uobject*>(component + offsets::montage_effect_override_context_offset, nullptr);

                        memory::write<uobject*>(component + offsets::montage_effect_override_offset, nullptr);
                        memory::write<uobject*>(component + offsets::montage_effect_override_context_offset, nullptr);

                        memory::write<uobject*>(component + offsets::montage_effect_override_offset, finisher);
                        memory::write<uobject*>(component + offsets::montage_effect_override_context_offset, LPawnContext);

                        PlayFinisherEffect(component);
                        };

                    if (shouldPlayFinisher) {
                        if (weapon_name.find("AssaultRifle_AK_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("AssaultRifle_ACR_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("BoltSniper_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("AssaultRifle_Burst_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("AutomaticPistol_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("DMR_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("RevolverPistol_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("LugerPistol_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("SubMachineGun_MP5_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("BasePistol_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("LeverSniperRifle_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("DS_Gun_C") != std::string::npos) {
                            applyFinisher();
                        }
                        else if (weapon_name.find("Ability_Melee_Base_C") != std::string::npos) {
                            memory::write<uobject*>(component + offsets::montage_effect_override_offset, nullptr);
                            memory::write<uobject*>(component + offsets::montage_effect_override_context_offset, nullptr);
                        }
                    }
                }
            }
        }
        return hooks::oHkDeath(shooter_character, a2);
    }
    catch (...) {
        return hooks::oHkDeath(shooter_character, a2);
    }
}
#define DEG2RAD (PI / 180.0f)


fvector rotation_to_direction(const frotator& rot)
{
    float pitchRad = rot.pitch * DEG2RAD;
    float yawRad = rot.yaw * DEG2RAD;

    float cp = cosf(pitchRad);
    float sp = sinf(pitchRad);
    float cy = cosf(yawRad);
    float sy = sinf(yawRad);

    return fvector(cp * cy, cp * sy, sp);
}

flinearcolor RGBtoFLC(float R, float G, float B)
{
    return { R / 255, G / 255, B / 255, 1 };
}


#include <string>

#pragma pack(push, 1)
union fp_flag_store {
    unsigned char raw;
    struct {
        unsigned char f0 : 1;
        unsigned char f1 : 1;
        unsigned char f2 : 6;
    } bits;
};
#pragma pack(pop)

struct ViewModelCache {
    uskeletalmeshcomponent* mesh1p = nullptr;
    uskeletalmeshcomponent* overlayMesh = nullptr;
    uskeletalmeshcomponent* weaponMesh1P = nullptr;
    uskeletalmeshcomponent* cosmeticMesh1P = nullptr;
    uskeletalmeshcomponent* meleeMesh1P = nullptr;
    uskeletalmeshcomponent* offHandMesh = nullptr;
    currentequippable* lastWeapon = nullptr;
    currentequippable* lastMelee = nullptr;
    ULONGLONG lastCacheTime = 0;

    void Clear() {
        mesh1p = overlayMesh = weaponMesh1P = cosmeticMesh1P = nullptr;
        meleeMesh1P = offHandMesh = nullptr;
        lastWeapon = lastMelee = nullptr;
    }

    bool IsValid() const {
        return mesh1p != nullptr && weaponMesh1P != nullptr;
    }
};


currentequippable* GetLocalMeleeWeapon() {
    static currentequippable* CachedMelee = nullptr;
    static ULONGLONG lastCacheTime = 0;

    ULONGLONG currentTime = GetTickCount64();
    if (CachedMelee && (currentTime - lastCacheTime) < 2000) {
        return CachedMelee;
    }

    // Cache yenile
    CachedMelee = nullptr;

    if (!UWorldSave) return nullptr;

    tarray<AGameObject*> Objects;
    GameplayStatics::GetAllActorsOfClass2(UWorldSave, Class::Actors(), &Objects);
    for (int i = 0; i < Objects.size(); ++i) {
        AGameObject* Object = Objects[i];
        if (!Object) continue;

        auto name = system::get_object_name((uobject*)Object);
        if (!name.is_valid()) continue;

        if (name.to_str().find("Ability_Melee_Base_C") != std::string::npos) {
            CachedMelee = (currentequippable*)Object;
            lastCacheTime = currentTime;
            return CachedMelee;
        }
    }

    return nullptr;
}
template<typename T>
inline bool SafeRead(uintptr_t address, T& value) {
    if (!IsValidViewModelPointer(address)) return false;

    __try {
        value = *reinterpret_cast<T*>(address);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

template<typename T>
inline bool SafeWrite(uintptr_t address, const T& value) {
    if (!IsValidViewModelPointer(address)) return false;

    __try {
        *reinterpret_cast<T*>(address) = value;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

inline bool SafeProcessFlag(uskeletalmeshcomponent* mesh, uintptr_t flag_offset, bool clear_flag = false) {
    if (!mesh || !IsValidViewModelObject(mesh)) return false;

    uintptr_t flag_addr = (uintptr_t)mesh + flag_offset;
    if (!IsValidViewModelPointer(flag_addr)) return false;

    fp_flag_store state;
    if (!SafeRead(flag_addr, state.raw)) return false;

    if (clear_flag) {
        state.bits.f0 = 0;
        return SafeWrite(flag_addr, state.raw);
    }

    return true;
}
inline void SafeLockDescendants(USceneComponent* component) {
    if (!component || !IsValidViewModelObject(component)) return;

    tarray<USceneComponent*> allChildren;
    __try {

        printf("\n allChildren false");
        allChildren = GetChildrenComponents(component, true);
        printf("\n allChildren true");
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return;
    }

    for (int i = 0; i < allChildren.Num(); i++) {
        USceneComponent* child = allChildren[i];
        if (child && IsValidViewModelObject(child)) {
            uintptr_t child_flag_addr = (uintptr_t)child + 0x364;
            SafeWrite(child_flag_addr, (unsigned char)0x00);
        }
    }
}


//void process_fp2_nigga(ashootercharacter* negneg) {
//    UPrimitiveComponent* mesh_1p = (UPrimitiveComponent*)negneg->GetMesh1P();
//    UPrimitiveComponent* mesh_overlay_1p = (UPrimitiveComponent*)negneg->GetOverlayMesh1P();
//
//
//    auto gun = negneg->get_inventory()->get_current_equippable();
//    UPrimitiveComponent* mesh_1pgun = (UPrimitiveComponent*)gun->GetMesh1P();
//    UPrimitiveComponent* mesh_1pgunoverlay;
//    uintptr_t cosmetic_ptr = (uintptr_t)gun + 0x1160;
//    if (IsValidViewModelPointer(cosmetic_ptr)) {
//       mesh_1pgunoverlay= (UPrimitiveComponent*)memory::read<UPrimitiveComponent*>(cosmetic_ptr);
//    }
//
//
//    auto meleeWeapon = GetLocalMeleeWeapon();
//    UPrimitiveComponent* offhandknife;
//    if (meleeWeapon && IsValidViewModelObject(meleeWeapon)) {
//    
//        auto meleeweapon2 = (UPrimitiveComponent*)meleeWeapon->GetMesh1P();
//        uintptr_t offhand_ptr = (uintptr_t)meleeWeapon + 0x11F8;
//        if (IsValidViewModelPointer(offhand_ptr) && meleeweapon2) {
//            offhandknife = (UPrimitiveComponent*)memory::read<UPrimitiveComponent*>(offhand_ptr);
//        }
//    }
//
//
//    if (!mesh_1p || !mesh_1pgun) {
//        return;
//    }
//
//    if (mesh_overlay_1p && IsValidViewModelObject(mesh_overlay_1p)) {
//        mesh_overlay_1p->set_is_first_person(false);
//    }
//
//    if (mesh_1pgun && IsValidViewModelObject(mesh_1pgun)) {
//        mesh_1pgun->set_is_first_person(false);
//    }
//
//    if (mesh_1pgunoverlay && IsValidViewModelObject(mesh_1pgunoverlay)) {
//        mesh_1pgunoverlay->set_is_first_person(false);
//    }
//
//    mesh_overlay_1p->set_is_first_person(false);
//    mesh_1pgun->set_is_first_person(false);
//   
//
//        
//    if (mesh_1p && IsValidViewModelObject(mesh_1p)) {
//        SafeLockDescendants((USceneComponent*)mesh_1p);
//    }
//
//    if (mesh_1pgun && IsValidViewModelObject(mesh_1pgun)) {
//        SafeLockDescendants((USceneComponent*)mesh_1pgun);
//    }
//
//    if (meleeweapon2 && IsValidViewModelObject(meleeweapon2)) {
//        SafeLockDescendants((USceneComponent*)meleeweapon2);
//    }
//
//}
//

inline void process_fp_mode(ashootercharacter* shooter) {
    if (!shooter || !IsValidViewModelObject(shooter)) return;

    bool isAlive = false;
    __try {
        isAlive = shooter->is_alive();
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return;
    }

    if (!isAlive) {
        static ViewModelCache cache;
        cache.Clear();
        return;
    }

    static ViewModelCache cache;
    static bool last_force_key_state = false;

    ULONGLONG current_time = GetTickCount64();
    bool force_key_pressed = GetAsyncKeyState(VK_F8) & 0x8000;
    bool force_reapply = force_key_pressed && !last_force_key_state;
    last_force_key_state = force_key_pressed;

    uinventory* inventory = nullptr;
    __try {
        inventory = shooter->get_inventory();
        printf("\n inventory: 0x%p", inventory);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        cache.Clear();
        return;
    }

    if (!inventory || !IsValidViewModelObject(inventory)) {
        cache.Clear();
        return;
    }

    currentequippable* weapon = nullptr;
    __try {
        weapon = inventory->get_current_equippable();

    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        cache.Clear();
        return;
    }

    if (!weapon || !IsValidViewModelObject(weapon)) {
        cache.Clear();
        return;
    }

    bool needs_refresh = false;
    if (!cache.IsValid() ||
        weapon != cache.lastWeapon ||
        (current_time - cache.lastCacheTime) >= 2000 ||
        force_reapply) {
        needs_refresh = true;
    }

    if (needs_refresh) {
        cache.Clear();
        cache.lastCacheTime = current_time;
        cache.lastWeapon = weapon;

        __try {
            cache.mesh1p = shooter->GetMesh1P();

        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            cache.Clear();
            return;
        }

        if (!cache.mesh1p || !IsValidViewModelObject(cache.mesh1p)) {
            cache.Clear();
            return;
        }

        __try {
            cache.overlayMesh = shooter->GetOverlayMesh1P();

        }
        __except (EXCEPTION_EXECUTE_HANDLER) {

        }

        __try {
            cache.weaponMesh1P = weapon->GetMesh1P();

        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            cache.Clear();
            return;
        }

        if (!cache.weaponMesh1P || !IsValidViewModelObject(cache.weaponMesh1P)) {
            cache.Clear();
            return;
        }

        uintptr_t cosmetic_ptr = (uintptr_t)weapon + 0x1188;
        if (IsValidViewModelPointer(cosmetic_ptr)) {
            __try {
                cache.cosmeticMesh1P = memory::read2<uskeletalmeshcomponent*>(cosmetic_ptr);

            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
            }
        }

        auto meleeWeapon = GetLocalMeleeWeapon();
        if (meleeWeapon && IsValidViewModelObject(meleeWeapon)) {
            cache.lastMelee = meleeWeapon;

            __try {
                cache.meleeMesh1P = meleeWeapon->GetMesh1P();
                printf("\n cache.meleeMesh1P: 0x%p", cache.meleeMesh1P);
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                cache.meleeMesh1P = nullptr;
            }

            uintptr_t offhand_ptr = (uintptr_t)meleeWeapon + 0x1220;
            if (IsValidViewModelPointer(offhand_ptr) && cache.meleeMesh1P) {
                __try {
                    cache.offHandMesh = memory::read2<uskeletalmeshcomponent*>(offhand_ptr);
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {
                    cache.offHandMesh = nullptr;
                }
            }
        }
    }

    if (!cache.IsValid() || !cache.mesh1p || !cache.weaponMesh1P) {
        return;
    }

    const uintptr_t flag_offset = 0x364;

    bool should_process_flags = false;
    fp_flag_store main_state;

    if (SafeProcessFlag(cache.mesh1p, flag_offset, false)) {
        uintptr_t mesh_flag_addr = (uintptr_t)cache.mesh1p + flag_offset;
        if (SafeRead(mesh_flag_addr, main_state.raw)) {
            should_process_flags = (main_state.bits.f0 != 0) || force_reapply;
        }
    }

    if (should_process_flags) {
        SafeProcessFlag(cache.mesh1p, flag_offset, true);

        if (cache.overlayMesh && IsValidViewModelObject(cache.overlayMesh)) {
            SafeProcessFlag(cache.overlayMesh, flag_offset, true);
        }

        if (cache.weaponMesh1P && IsValidViewModelObject(cache.weaponMesh1P)) {
            SafeProcessFlag(cache.weaponMesh1P, flag_offset, true);
        }

        if (cache.cosmeticMesh1P && IsValidViewModelObject(cache.cosmeticMesh1P)) {
            SafeProcessFlag(cache.cosmeticMesh1P, flag_offset, true);
        }
    }

    if (cache.mesh1p && IsValidViewModelObject(cache.mesh1p)) {
        SafeLockDescendants((USceneComponent*)cache.mesh1p);
    }

    if (cache.weaponMesh1P && IsValidViewModelObject(cache.weaponMesh1P)) {
        SafeLockDescendants((USceneComponent*)cache.weaponMesh1P);
    }

    if (cache.meleeMesh1P && IsValidViewModelObject(cache.meleeMesh1P)) {
        SafeLockDescendants((USceneComponent*)cache.meleeMesh1P);
    }
}


fvector RotatorToVector(const frotator& rot)
{
    float radPitch = rot.pitch * PI / 180.f;
    float radYaw = rot.yaw * PI / 180.f;

    float CP = cosf(radPitch);
    float SP = sinf(radPitch);
    float CY = cosf(radYaw);
    float SY = sinf(radYaw);

    return fvector(CP * CY, CP * SY, SP);
}



namespace g {


    fvector2d screen_size = canvas->get_screen_size();
    fvector2d pos = { (screen_size.x / 2.0f) - 500, (screen_size.y / 2.0f) - 475 };


}

struct FGameFeatureSubclass {
    struct AActor* Class; // 0x00(0x08)
    struct tarray<struct FGameFeatureAlternateClass> AlternateClasses;
};



class Vector5 {
public:
    float x, y;

    Vector5(float x = 0, float y = 0) : x(x), y(y) {}

    Vector5 operator-(const Vector5& other) const {
        return Vector5(x - other.x, y - other.y);
    }

    Vector5 operator+(const Vector5& other) const {
        return Vector5(x + other.x, y + other.y);
    }

    Vector5 operator*(float scalar) const {
        return Vector5(x * scalar, y * scalar);
    }

    void normalize() {
        float length = std::sqrt(x * x + y * y);
        if (length > 0) {
            x /= length;
            y /= length;
        }
    }
};

class Projectile {
public:
    Vector5 position;
    Vector5 velocity;
    float lifetime;

    Projectile(Vector5 startPos, Vector5 direction, float speed, float life)
        : position(startPos), lifetime(life) {
        velocity = direction * speed; // Set velocity based on direction and speed
    }

    void update(float deltaTime) {
        position = position + (velocity * deltaTime);
        lifetime -= deltaTime;
    }

    bool isAlive() const {
        return lifetime > 0;
    }
};

// Global variables
std::vector<Projectile> projectiles;
const float projectileSpeed = 500.0f;
const float projectileLifetime = 3.0f;

// Function to throw a projectile
void throwProjectile(Vector5 throwerPosition, Vector5 targetPosition) {
    Vector5 direction = targetPosition - throwerPosition;
    direction.normalize(); // Normalize the direction

    // Create the projectile
    Projectile projectile(throwerPosition, direction, projectileSpeed, projectileLifetime);
    projectiles.push_back(projectile); // Add to the list of projectiles
}

// Function to update all projectiles
void updateProjectiles(float deltaTime) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->update(deltaTime);
        if (!it->isAlive()) {
            it = projectiles.erase(it); // Remove dead projectiles
        }
        else {
            ++it;
        }
    }
}

bool isColliding(const Vector5& projectilePosition, const Vector5& bombPosition) {
    float distance = std::sqrt(std::pow(projectilePosition.x - bombPosition.x, 2) +
        std::pow(projectilePosition.y - bombPosition.y, 2));
    return distance < 10.0f;
}



std::vector<fvector> simulate_trajectory(
    const fvector& Origin,
    const fvector& Direction,
    float Speed,
    const fvector& Gravity,
    float TimeStep,
    int MaxSteps
)
{
    std::vector<fvector> Path;
    fvector Position = Origin;
    fvector Velocity = Direction * Speed;

    for (int i = 0; i < MaxSteps; ++i)
    {
        Path.push_back(Position);
        Position = Position + Velocity * TimeStep;
        Velocity = Velocity + Gravity * TimeStep;
    }

    return Path;
}

bool solve_projectile_arc(
    const fvector& origin,
    const fvector& target,
    float speed,
    float gravity,
    fvector& outInitialVelocity)
{
    // Simplified 2D projectile motion formula on flat terrain for demonstration:

    fvector displacement = target - origin;
    float dx = sqrtf(displacement.x * displacement.x + displacement.y * displacement.y);
    float dy = displacement.z;

    float g = fabsf(gravity);
    float speedSq = speed * speed;
    float underSqrt = speedSq * speedSq - g * (g * dx * dx + 2 * dy * speedSq);

    if (underSqrt < 0) return false; // no solution

    float sqrtVal = sqrtf(underSqrt);

    float angle1 = atanf((speedSq + sqrtVal) / (g * dx));
    // float angle2 = atanf((speedSq - sqrtVal) / (g * dx)); // alternative angle

    // Compose velocity vector
    float vx = speed * cosf(angle1) * (displacement.x / dx);
    float vy = speed * cosf(angle1) * (displacement.y / dx);
    float vz = speed * sinf(angle1);

    outInitialVelocity = fvector(vx, vy, vz);
    return true;
}


struct FProjectileThrowTuning {
    // Order and padding must match the game's memory layout exactly!

    // Assuming offsets from your earlier enum:
    // 0x0  ProjectileClass (skip or pad)
    char _pad0[0x20];  // skip 0x20 bytes (ProjectileClass + ProjectileType)

    float SpeedScale;       // 0x20
    float UpwardArc;        // 0x24
    float UpwardShift;      // 0x28
    fvector ThrowOffset;    // 0x2C
    float ThrowDelay;       // 0x38
    bool bJumpThrowNormalization_LaunchPoint;   // 0x3C
    bool bJumpThrowNormalization_ImpartedVelocity; // 0x3D

    // You may need to add padding or proper packing directives depending on compiler
};

static bool SafeReadPointer(uintptr_t address, uintptr_t* outValue) {
    __try {
        *outValue = *(uintptr_t*)address;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}
static bool SafeReadByte(uintptr_t address, uint8* outValue) {
    __try {
        *outValue = *(uint8*)address;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}
struct WeaponPenetrationData {
    float HeadDamage;
    float BodyDamage;
    float LegDamage;
    float PenetrationPower;
    float DamageReductionPerWall;
    bool CanPenetrateWalls;
};


static const std::map<uint8_t, float> MaterialPenetrationLimits = {
    { 9,  0.0f },
    { 13, 0.0f },
    { 26, 0.0f },
    { 3,  200.0f },
    { 4,  200.0f },
    { 7,  200.0f },
    { 22, 200.0f },
    { 28, 200.0f },
    { 31, 200.0f },
    { 2,  150.0f },
    { 6,  150.0f },
    { 1,  125.0f },
    { 5,  100.0f }
};

std::map<std::wstring, WeaponPenetrationData> WeaponDatabase = {
    { L"Vandal",     { 160.0f, 160.0f, 134.0f, 0.75f, 0.35f, true } },
    { L"Phantom",    { 156.0f, 156.0f, 130.0f, 0.75f, 0.35f, true } },
    { L"Operator",   { 255.0f, 150.0f, 120.0f, 0.90f, 0.25f, true } },
    { L"Marshal",    { 202.0f, 101.0f,  85.0f, 0.85f, 0.30f, true } },
    { L"Sheriff",    { 159.0f,  55.0f,  46.0f, 0.70f, 0.40f, true } },
    { L"Guardian",   { 195.0f,  65.0f,  49.0f, 0.80f, 0.30f, true } },
    { L"Outlaw",     { 140.0f, 140.0f, 119.0f, 0.78f, 0.32f, true } },
    { L"Ghost",      { 105.0f,  30.0f,  25.0f, 0.65f, 0.45f, true } },
    { L"Classic",    {  78.0f,  26.0f,  22.0f, 0.50f, 0.60f, false } },
    { L"Shorty",     {  20.0f,  12.0f,  10.0f, 0.20f, 0.80f, false } },
    { L"Frenzy",     {  78.0f,  26.0f,  21.0f, 0.55f, 0.55f, false } },
    { L"Spectre",    {  78.0f,  26.0f,  22.0f, 0.60f, 0.50f, true } },
    { L"Stinger",    {  67.0f,  27.0f,  22.0f, 0.58f, 0.52f, true } },
    { L"Bucky",      {  40.0f,  20.0f,  17.0f, 0.30f, 0.70f, false } },
    { L"Judge",      {  34.0f,  17.0f,  14.0f, 0.35f, 0.65f, false } },
    { L"Bulldog",    { 115.0f,  35.0f,  29.0f, 0.68f, 0.38f, true } },
    { L"Ares",       {  72.0f,  30.0f,  25.0f, 0.62f, 0.48f, true } },
    { L"Odin",       {  95.0f,  38.0f,  32.0f, 0.72f, 0.36f, true } }
};
WeaponPenetrationData GetWeaponData(ashootercharacter* Player, const fstring& BoneName) {
    auto current_wep = Player->get_inventory()->get_current_equippable();
    fstring obj_name = helper::convert_weapon_name(system::get_object_name(current_wep));

    std::wstring weaponKey = obj_name.c_str();

    auto it = WeaponDatabase.find(weaponKey);
    if (it != WeaponDatabase.end()) {
        return it->second;
    }

    return { 100.0f, 35.0f, 25.0f, 0.60f, 0.40f, true };
}


class BoneHelper {
public:
    static int32_t GetBonePriorityByIndex(int32_t bone_index, int32_t bone_count) {
        switch (bone_count) {
        case 101:
            if (bone_index == 20) return 100;  // Head
            if (bone_index == 21) return 90;   // Neck
            if (bone_index >= 17 && bone_index <= 19) return 80;
            if (bone_index >= 15 && bone_index <= 16) return 70;
            if (bone_index >= 13 && bone_index <= 14) return 60;
            if (bone_index == 3) return 50;    // Pelvis
            if (bone_index >= 23 && bone_index <= 25) return 30;
            if (bone_index >= 49 && bone_index <= 51) return 30;
            if (bone_index >= 75 && bone_index <= 78) return 25;
            if (bone_index >= 82 && bone_index <= 85) return 25;
            return 10;

        case 103:
            if (bone_index == 8) return 100;   // Head
            if (bone_index == 9) return 90;    // Neck
            if (bone_index >= 5 && bone_index <= 7) return 80;
            if (bone_index == 3) return 50;
            if (bone_index >= 30 && bone_index <= 33) return 30;
            if (bone_index >= 55 && bone_index <= 58) return 30;
            if (bone_index >= 63 && bone_index <= 69) return 25;
            if (bone_index >= 77 && bone_index <= 83) return 25;
            return 10;

        case 104:
            if (bone_index == 20) return 100;
            if (bone_index == 21) return 90;
            if (bone_index >= 17 && bone_index <= 19) return 80;
            if (bone_index >= 15 && bone_index <= 16) return 70;
            if (bone_index >= 13 && bone_index <= 14) return 60;
            if (bone_index == 3) return 50;
            if (bone_index >= 23 && bone_index <= 25) return 30;
            if (bone_index >= 49 && bone_index <= 51) return 30;
            if (bone_index >= 77 && bone_index <= 80) return 25;
            if (bone_index >= 84 && bone_index <= 87) return 25;
            return 10;

        default:
            if (bone_index <= 10) return 80;
            if (bone_index <= 20) return 60;
            if (bone_index <= 30) return 40;
            return 20;
        }
    }

    static inline void GetCriticalBones(int32_t bone_count, int32_t* out_bones, int32_t& out_count) {
        if (bone_count == 101 || bone_count == 104) {
            static const int32_t bones[] = { 20, 21, 19, 18, 17, 3 };
            memcpy(out_bones, bones, sizeof(bones));
            out_count = 6;
        }
        else if (bone_count == 103) {
            static const int32_t bones[] = { 8, 9, 7, 6, 5, 3 };
            memcpy(out_bones, bones, sizeof(bones));
            out_count = 6;
        }
        else {
            out_count = 0;
        }
    }
};



auto get_target_bone_matrix35 = [](uskeletalmeshcomponent* mesh, int bone) -> FVector {
    switch (bone) {
    case 0: return mesh->get_bone_location35(8); break;
    case 1: return mesh->get_bone_location35(6); break;
    case 2: return mesh->get_bone_location35(4); break;
    default: return FVector();
    }
    };

auto get_target_bone_matrix = [](uskeletalmeshcomponent* mesh, int bone) -> fvector {
    if (!mesh) return fvector();
    // Map common bones or use the passed bone directly
    switch (bone) {
    case 0: return mesh->get_bone_location(8);  // head
    case 1: return mesh->get_bone_location(6);  // neck
    case 2: return mesh->get_bone_location(4);  // chest
    default: return mesh->get_bone_location(bone); // use bone index directly
    }
    };


auto BONEMATRIXGAY = [](uskeletalmeshcomponent* mesh) -> fvector {
    if (!mesh) return fvector();

    return mesh->get_bone_location(8);
    };


#define LOGA(fmt, ...)                      \
{                                           \
    char buf[512];                          \
    sprintf_s(buf, fmt, __VA_ARGS__);       \
    OutputDebugStringA(buf);                \
}
namespace SLIGHTSONTOP1
{
    namespace insta_lock_agents
    {
        uobject* astra = nullptr;
        uobject* breach = nullptr;
        uobject* brimstone = nullptr;
        uobject* chamber = nullptr;
        uobject* cypher = nullptr;
        uobject* fade = nullptr;
        uobject* jett = nullptr;
        uobject* kayo = nullptr;
        uobject* killjoy = nullptr;
        uobject* neon = nullptr;
        uobject* omen = nullptr;
        uobject* phoenix = nullptr;
        uobject* raze = nullptr;
        uobject* reyna = nullptr;
        uobject* sage = nullptr;
        uobject* skye = nullptr;
        uobject* sova = nullptr;
        uobject* viper = nullptr;
        uobject* yoru = nullptr;
        uobject* gekko = nullptr;

        void run()
        {
            auto enc_astra = Encrypt(L"Default__Rift_PrimaryAsset_C");
            astra = uobject::find_object13(enc_astra.decrypt(), reinterpret_cast<uobject*>(-1)), enc_astra.clear();

            auto enc_breach = Encrypt(L"Default__Breach_PrimaryAsset_C");
            breach = uobject::find_object13(enc_breach.decrypt(), reinterpret_cast<uobject*>(-1)), enc_breach.clear();

            auto enc_brimstone = Encrypt(L"Default__Sarge_PrimaryAsset_C");
            brimstone = uobject::find_object13(enc_brimstone.decrypt(), reinterpret_cast<uobject*>(-1)), enc_brimstone.clear();

            auto enc_chamber = Encrypt(L"Default__Deadeye_PrimaryAsset_C");
            chamber = uobject::find_object13(enc_chamber.decrypt(), reinterpret_cast<uobject*>(-1)), enc_chamber.clear();

            auto enc_cypher = Encrypt(L"Default__Gumshoe_PrimaryAsset_C");
            cypher = uobject::find_object13(enc_cypher.decrypt(), reinterpret_cast<uobject*>(-1)), enc_cypher.clear();

            auto enc_fade = Encrypt(L"Default__BountyHunter_PrimaryAsset_C");
            fade = uobject::find_object13(enc_fade.decrypt(), reinterpret_cast<uobject*>(-1)), enc_fade.clear();

            auto enc_jett = Encrypt(L"Default__Wushu_PrimaryAsset_C");
            jett = uobject::find_object13(enc_jett.decrypt(), reinterpret_cast<uobject*>(-1)), enc_jett.clear();

            auto enc_kayo = Encrypt(L"Default__Grenadier_PrimaryAsset_C");
            kayo = uobject::find_object13(enc_kayo.decrypt(), reinterpret_cast<uobject*>(-1)), enc_kayo.clear();

            auto enc_killjoy = Encrypt(L"Default__Killjoy_PrimaryAsset_C");
            killjoy = uobject::find_object13(enc_killjoy.decrypt(), reinterpret_cast<uobject*>(-1)), enc_killjoy.clear();

            auto enc_neon = Encrypt(L"Default__Sprinter_PrimaryAsset_C");
            neon = uobject::find_object13(enc_neon.decrypt(), reinterpret_cast<uobject*>(-1)), enc_neon.clear();

            auto enc_omen = Encrypt(L"Default__Wraith_PrimaryAsset_C");
            omen = uobject::find_object13(enc_omen.decrypt(), reinterpret_cast<uobject*>(-1)), enc_omen.clear();

            auto enc_phoenix = Encrypt(L"Default__Phoenix_PrimaryAsset_C");
            phoenix = uobject::find_object13(enc_phoenix.decrypt(), reinterpret_cast<uobject*>(-1)), enc_phoenix.clear();

            auto enc_raze = Encrypt(L"Default__Clay_PrimaryAsset_C");
            raze = uobject::find_object13(enc_raze.decrypt(), reinterpret_cast<uobject*>(-1)), enc_raze.clear();

            auto enc_reyna = Encrypt(L"Default__Vampire_PrimaryAsset_C");
            reyna = uobject::find_object13(enc_reyna.decrypt(), reinterpret_cast<uobject*>(-1)), enc_reyna.clear();

            auto enc_sage = Encrypt(L"Default__Thorne_PrimaryAsset_C");
            sage = uobject::find_object13(enc_sage.decrypt(), reinterpret_cast<uobject*>(-1)), enc_sage.clear();

            auto enc_skye = Encrypt(L"Default__guide_PrimaryAsset_C");
            skye = uobject::find_object13(enc_skye.decrypt(), reinterpret_cast<uobject*>(-1)), enc_skye.clear();

            auto enc_sova = Encrypt(L"Default__Hunter_PrimaryAsset_C");
            sova = uobject::find_object13(enc_sova.decrypt(), reinterpret_cast<uobject*>(-1)), enc_sova.clear();

            auto enc_viper = Encrypt(L"Default__Pandemic_PrimaryAsset_C");
            viper = uobject::find_object13(enc_viper.decrypt(), reinterpret_cast<uobject*>(-1)), enc_viper.clear();

            auto enc_yoru = Encrypt(L"Default__Stealth_PrimaryAsset_C");
            yoru = uobject::find_object13(enc_yoru.decrypt(), reinterpret_cast<uobject*>(-1)), enc_yoru.clear();

            auto enc_gekko = Encrypt(L"Default__AggroBot_PrimaryAsset_C");
            gekko = uobject::find_object13(enc_gekko.decrypt(), reinterpret_cast<uobject*>(-1)), enc_gekko.clear();
        }

        uobject* get_agent_object(int id)
        {
            if (id == 0) return astra;
            else if (id == 1) return breach;
            else if (id == 2) return brimstone;
            else if (id == 3) return chamber;
            else if (id == 4) return cypher;
            else if (id == 5) return fade;
            else if (id == 6) return jett;
            else if (id == 7) return kayo;
            else if (id == 8) return killjoy;
            else if (id == 9) return neon;
            else if (id == 10) return omen;
            else if (id == 11) return phoenix;
            else if (id == 12) return raze;
            else if (id == 13) return reyna;
            else if (id == 14) return sage;
            else if (id == 15) return skye;
            else if (id == 16) return sova;
            else if (id == 17) return viper;
            else if (id == 18) return yoru;
            else if (id == 19) return gekko;
            else return nullptr;
        }
    }

    namespace insta_lock
    {
        int old_time = NULL;
        int agent_counter = 0;

        static void agent_roulette(aplayercontroller* controller)
        {
            static uobject* _class = nullptr;
            if (!_class)
            {
                _class = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregamePlayerController"));

            }

            if (math::ClassIsChildOf(controller->ClassPrivate, _class))
            {

                if (pregame_view_controller* pregame_view_controller = controller->get_pregame_view_controller())
                    if (pregame_view_model* pregame_view_model = pregame_view_controller->get_pregame_view_model())
                        if (!pregame_view_model->is_local_player_locked_in())
                        {
                            pregame_view_controller->select_character(
                                insta_lock_agents::get_agent_object(agent_counter)
                            );

                            agent_counter++;
                            if (agent_counter >= 20)
                                agent_counter = 0;
                        }
                        else
                        {

                            globals::il::random_agent = false;
                        }
            }
        }

        void run(aplayercontroller* controller)
        {
            if (globals::il::random_agent)
            {
                agent_roulette(controller);
            }


            if (globals::il::enable)
            {
                static uobject* _class = nullptr;
                _class = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregamePlayerController"));
                if (auto WAH = math::ClassIsChildOf(controller->ClassPrivate, _class))
                {

                    if (pregame_view_controller* pregame_view_controller = controller->get_pregame_view_controller())
                    {
                        if (pregame_view_model* pregame_view_model2 = pregame_view_controller->get_pregame_view_model())
                        {
                            if (!pregame_view_model2->is_local_player_locked_in())
                            {
                                if (auto agent_object = insta_lock_agents::get_agent_object(globals::il::lock_agent))
                                {
                                    pregame_view_controller->lock_character(agent_object);

                                    globals::il::enable = false;

                                }
                            }
                        }
                    }
                }
            }

        }
    }
}
struct WeaponData_t {
    bool CanPenetrateWalls;
    float HeadDamage;
    float PenetrationPower;
    float DamageReductionPerWall;
};

class TraceHelper {
public:
    static inline bool IsValidActorPtr(uintptr_t ptr) {
        return ptr != 0 && ptr != 0xFFFFFFFF && ptr != 0xFFFFFFFFFFFFFFFF && ptr > 0x10000;
    }

    static bool CanShootThrough(aplayercontroller* controller, ashootercharacter* shooter_char,
        ashootercharacter* target_enemy, int aim_bone = 8)
    {
        if (!controller || !shooter_char || !target_enemy) return false;
        if (!memory::IsValidPointer((uintptr_t)controller) ||
            !memory::IsValidPointer((uintptr_t)shooter_char) ||
            !memory::IsValidPointer((uintptr_t)target_enemy)) return false;
        if (!UWorldSave || !memory::IsValidPointer((uintptr_t)UWorldSave)) return false;

        uskeletalmeshcomponent* enemy_mesh = target_enemy->get_mesh();
        if (!enemy_mesh || !memory::IsValidPointer((uintptr_t)enemy_mesh)) return false;

        fvector camera_loc = controller->get_camera_manager()->get_camera_location();
        fvector target_bone = GetBoneMatrix(enemy_mesh, aim_bone);

        tarray<AActor*> ignore_actors;
        ignore_actors.Add((AActor*)shooter_char);

        auto weapon_data = GetWeaponData(shooter_char, fstring(L"head"));
        if (!weapon_data.CanPenetrateWalls) return false;

        float remaining_damage = weapon_data.HeadDamage;
        float pen_power = weapon_data.PenetrationPower;
        float reduction_rate = weapon_data.DamageReductionPerWall;
        float max_thickness = pen_power * 180.0f;

        char raw_wall_spans[0x200];
        memset(raw_wall_spans, 0, sizeof(raw_wall_spans));

        ShooterGameBlueprints::GetWallPenetrationSpans(
            UWorldSave, camera_loc, target_bone,
            ignore_actors, ECollisionChannel::ECC_Visibility,
            0.0f, *(FWallSpanList*)raw_wall_spans
        );

        uintptr_t spans_ptr = *(uintptr_t*)&raw_wall_spans[0x00];
        int32_t spans_count = *(int32_t*)&raw_wall_spans[0x08];
        bool bLastPointInWall = *(bool*)&raw_wall_spans[0x10];

        if (bLastPointInWall) return false;
        if (!spans_ptr || spans_count <= 0) return true; 

        const int FHITRESULT_SIZE = 0xF0;
        const int SPANINFO_SIZE = 0x1E0;
        const int ENTRANCE_LOC_OFFSET = 0x10;
        const int EXIT_LOC_OFFSET = FHITRESULT_SIZE + 0x10;
        const int BLOCKING_HIT_OFFSET = 0xAD;

        int walls_penetrated = 0;
        uint8_t* span_base = (uint8_t*)spans_ptr;

        for (int i = 0; i < spans_count; i++) {
            uint8_t* span = span_base + (i * SPANINFO_SIZE);

            double entrance_x = *(double*)(span + ENTRANCE_LOC_OFFSET);
            double entrance_y = *(double*)(span + ENTRANCE_LOC_OFFSET + 0x08);
            double entrance_z = *(double*)(span + ENTRANCE_LOC_OFFSET + 0x10);

            double exit_x = *(double*)(span + EXIT_LOC_OFFSET);
            double exit_y = *(double*)(span + EXIT_LOC_OFFSET + 0x08);
            double exit_z = *(double*)(span + EXIT_LOC_OFFSET + 0x10);

            uint8_t blocking_byte = *(uint8_t*)(span + BLOCKING_HIT_OFFSET);
            bool bBlockingHit = (blocking_byte & 0x01) != 0;

            if (bBlockingHit) return false;
            double dx = exit_x - entrance_x;
            double dy = exit_y - entrance_y;
            double dz = exit_z - entrance_z;
            float thickness = sqrtf(dx * dx + dy * dy + dz * dz);

            if (thickness < 0.1f || thickness > 5000.0f) continue;
            if (thickness > max_thickness) return false;

            walls_penetrated++;
            remaining_damage *= (1.0f - reduction_rate);

            if (walls_penetrated >= 3) return false;
            if (remaining_damage <= 1.0f) return false;
        }

        return remaining_damage > 1.0f;
    }
};

flinearcolor Text_Shadow{ 0.0f, 0.0f, 0.0f, 0.0f };


namespace pos_decrpt {
    fvector2d pos = {
        (canvas->get_screen_size().x / 2.0f) - 500,
        (canvas->get_screen_size().y / 2.0f) - 475
    };
}


void DrawBoxOutline(ucanvas* canvas, const fvector2d& TopLeft, const fvector2d& BottomRight) {
    canvas->k2_drawline(TopLeft, fvector2d(BottomRight.x, TopLeft.y), 2, { 170, 170, 170, 0.0002f });
    canvas->k2_drawline(fvector2d(TopLeft.x, BottomRight.y), BottomRight, 2, { 170, 170, 170, 0.0002f });
    canvas->k2_drawline(TopLeft, fvector2d(TopLeft.x, BottomRight.y), 2, { 170, 170, 170, 0.0002f });
    canvas->k2_drawline(fvector2d(BottomRight.x, TopLeft.y), BottomRight, 2, { 170, 170, 170, 0.0002f });
}

void DrawProgressBarFill(ucanvas* canvas, const fvector2d& TopLeft, const fvector2d& BottomRight, float Percentage) {
    float X = TopLeft.x, Y = TopLeft.y;
    const flinearcolor ForegroundColor = { 0, 0, 1, 1 };

    for (int i = 0; i < 5; i++) {
        if (i > 0 && i < 5 - 1) {

            float ForegroundWidth = 70 * Percentage / 100;
            canvas->k2_drawline(fvector2d(X, Y + i), fvector2d(X + ForegroundWidth, Y + i), 2.9, ForegroundColor);
        }
    }
}
ftext MakeFText(const fstring& input)
{
    // Allocate FTextData on the heap
    ftextdata* data = new ftextdata();
    data->TextSource = input;

    // Construct FText
    ftext out;
    out.TextData = data;

    return out;
}


void DrawProgressBar(ucanvas* canvas, const fvector2d& Location, float Percentage) {
    fvector2d BoxTopLeft = fvector2d(Location.x - 35, Location.y + 15);
    fvector2d BoxBottomRight = fvector2d(BoxTopLeft.x + 70, BoxTopLeft.y + 5);

    DrawBoxOutline(canvas, BoxTopLeft, BoxBottomRight);
    DrawProgressBarFill(canvas, BoxTopLeft, BoxBottomRight, Percentage);
}

void DrawDroppedSpikeInfo(ucanvas* canvas, const fvector2d& ObjectLocation, uobject* font) {
    canvas->k2_drawtext(font, fstring{ L"Dropped Spike" }, ObjectLocation, fvector2d{ 1.06f, 1.06f }, { 1, 1, 1 ,2.5f }, false, Text_Shadow, fvector2d{ pos_decrpt::pos.x + 1, pos_decrpt::pos.y + 1 }, true, true, true, { 0,0,0.65f });
}
void DrawLineSimple_Spike(ucanvas* can, fvector2d first_bone_position, fvector2d second_bone_position, flinearcolor Color) {
    can->k2_drawline({ first_bone_position.x, first_bone_position.y }, { second_bone_position.x, second_bone_position.y }, 0.9f, Color);
}
// Smoke detection system using LineTraceSingle

// Smoke detection system using LineTraceSingle


//bool IsTargetVisible(uobject* World, aplayercontroller* MyController,
//    ashootercharacter* MyShooter, ashootercharacter* target,
//    bool considerSmoke = true) {
//    if (!World || !MyController || !MyShooter || !target) return false;
//
//    bool hasLOS = MyController->line_of_sight(target);
//    if (!hasLOS) return false;
//
//    if (!considerSmoke) return true;
//
//    fvector myPos = character->k2_get_actor_location();
//    fvector targetPos = target->k2_get_actor_location();
//
//    tarray<AActor*> actorsToIgnore;
//    actorsToIgnore.Add((AActor*)MyShooter);
//    actorsToIgnore.Add((AActor*)target);
//
//    return SmokeCheck::IsLineBlockedBySmokeAdvanced(World, myPos, targetPos, actorsToIgnore);
//}

namespace hooks
{
    // PI

    const float PI = 3.14159265359f;

    // important
    static acknowledgedpawn* LastPawn;

    ulocalplayer* LocalPlayers;
    ulocalplayer* LocalPlayer;
    fvector2d head_scren;
    aplayercontroller* MyControllers;



    // int unlocker
    int skinvandal = 0;
    int skinclassic = 0;
    int skinsheriff = 0;
    int skinphantom = 0;
    int skinspectre = 0;
    int skinknife = 0;
    int skinbulldog = 0;
    int skinguardian = 0;
    int skinshorty = 0;
    int skinghost = 0;
    int skinoperator = 0;

    int enemyID = 0; //enemy 
    int enemyIDvis = 0; //enemy 
    int CloseRangeDistanceID = 0; //enemy 

    static int TargetX = 0;
    static int TargetY = 0;

    int current_selection = 3;
    const int max_selection = 19;

    // float 
    float LocalCameraFOV;
    float CloseRangeDistance = 50.f;
    static float  Glow = 5.0f;
    static float  FOVChangorSprite = 5.0f;

    static float radius = 4.0f;
    float LineamountCross = 35.0f;
    float LineamountCircle = 25.0f;
    float LineamountFov = 35.0f;

    fvector2d Dinabumalik = canvas->get_screen_size();
    float screen_center_x = Dinabumalik.x / 2.0f;
    float screen_center_y = Dinabumalik.y / 2.0f;


    // bool
    bool Mesh3PModifed = false;
    bool enemiesarround = true;

    static bool open_canvas = true;

    static bool bLockedCameraRotation = false;
    static bool bFlickSilent = true;

    // stuff converter
    wchar_t* s2wc(const char* c)
    {
        const size_t cSize = strlen(c) + 1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs(wc, c, cSize);

        return wc;
    }
    std::wstring to_wide_string(const std::string& str) {
        return std::wstring(str.begin(), str.end());
    }
    template <typename T>  T clamp(T value, T min_value, T max_value) {
        if (value < min_value) return min_value;
        if (value > max_value) return max_value;
        return value;
    }

    std::string VirtualKeyCodeToString(UCHAR virtualKey)
    {
        UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
        if (virtualKey == VK_LBUTTON)
        {
            return ("MOUSE0");
        }
        if (virtualKey == VK_RBUTTON)
        {
            return ("MOUSE1");
        }
        if (virtualKey == VK_MBUTTON)
        {
            return ("MBUTTON");
        }
        if (virtualKey == VK_XBUTTON1)
        {
            return ("XBUTTON1");
        }
        if (virtualKey == VK_XBUTTON2)
        {
            return ("XBUTTON2");
        }


        CHAR szName[128];
        int result = 0;
        switch (virtualKey)
        {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT:
        case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE:
        case VK_DIVIDE:
        case VK_NUMLOCK:
            scanCode |= KF_EXTENDED;
        default:
            result = GetKeyNameTextA(scanCode << 16, szName, 128);
        }

        return szName;
    }


    struct AnimationState {
        float progress;
        bool target_value;

        AnimationState() : progress(0.0f), target_value(false) {}
    };
    struct DropdownState {
        bool is_open;
        DropdownState() : is_open(false) {}
    };
    struct KeybindState {
        bool is_binding;
        KeybindState() : is_binding(false) {}
    };

    class UIAnimationManager {
    private:
        static constexpr size_t MAX_ELEMENTS = 128;
        AnimationState toggle_animations[MAX_ELEMENTS];
        DropdownState dropdown_states[MAX_ELEMENTS];
        KeybindState keybind_states[MAX_ELEMENTS];
        size_t toggle_count;
        size_t dropdown_count;
        size_t keybind_count;

    public:
        UIAnimationManager() : toggle_count(0), dropdown_count(0), keybind_count(0) {}

        size_t register_toggle() {
            if (toggle_count < MAX_ELEMENTS) {
                return toggle_count++;
            }
            return 0;
        }

        size_t register_dropdown() {
            if (dropdown_count < MAX_ELEMENTS) {
                return dropdown_count++;
            }
            return 0;
        }

        size_t register_keybind() {
            if (keybind_count < MAX_ELEMENTS) {
                return keybind_count++;
            }
            return 0;
        }

        AnimationState& get_toggle_animation(size_t index) {
            return toggle_animations[index % MAX_ELEMENTS];
        }

        DropdownState& get_dropdown_state(size_t index) {
            return dropdown_states[index % MAX_ELEMENTS];
        }

        KeybindState& get_keybind_state(size_t index) {
            return keybind_states[index % MAX_ELEMENTS];
        }
    };
    static UIAnimationManager g_animation_manager;
    static constexpr size_t MAX_ELEMENTSS = 128;

    //namespace
    namespace Input
    {
        bool mouseDown[5];
        bool mouseDownAlready[256];

        bool keysDown[256];
        bool keysDownAlready[256];

        bool IsAnyMouseDown()
        {
            if (mouseDown[0]) return true;
            if (mouseDown[1]) return true;
            if (mouseDown[2]) return true;
            if (mouseDown[3]) return true;
            if (mouseDown[4]) return true;

            return false;
        }

        bool IsMouseClicked(int button, int element_id, bool repeat)
        {
            if (mouseDown[button])
            {
                if (!mouseDownAlready[element_id])
                {
                    mouseDownAlready[element_id] = true;
                    return true;
                }
                if (repeat)
                    return true;
            }
            else
            {
                mouseDownAlready[element_id] = false;
            }
            return false;
        }
        bool IsKeyPressed(int key, bool repeat)
        {
            if (keysDown[key])
            {
                if (!keysDownAlready[key])
                {
                    keysDownAlready[key] = true;
                    return true;
                }
                if (repeat)
                    return true;
            }
            else
            {
                keysDownAlready[key] = false;
            }
            return false;
        }

        void Handle()
        {
            if (GetAsyncKeyState(0x01))
                mouseDown[0] = true;
            else
                mouseDown[0] = false;
        }
    }

    // colors and converter
    flinearcolor get_color(bool condition) {
        return condition ? flinearcolor{ 0.1f, 1.0f, 0.1f, 1 } : flinearcolor{ 1.0f, 0.0f, 0.0f, 1 };
    }
    flinearcolor HSVtoRGB(float h, float s, float v) {
        float r, g, b;

        int i = static_cast<int>(h * 6);
        float f = h * 6 - i;
        float p = v * (1 - s);
        float q = v * (1 - f * s);
        float t = v * (1 - (1 - f) * s);

        switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        default: r = g = b = 0.0f;
        }

        return flinearcolor{ r, g, b, 1.0f };

    }
    flinearcolor convert_to_flinearcolor(int r, int g, int b, int a) {
        return flinearcolor(
            (float)r / 255.0f,
            (float)g / 255.0f,
            (float)b / 255.0f,
            (float)a / 255.0f
        );
    }
    flinearcolor RGBtoFLC(float R, float G, float B)
    {
        return { R / 255, G / 255, B / 255, 1 };
    }
    flinearcolor GetRainbowColor(float time)
    {
        float red = (sin(time * 2.0f * 3.14159f / 3.0f) + 1.0f) / 2.0f;
        float green = (sin(time * 2.0f * 3.14159f / 3.0f + 2.0f * 3.14159f / 3.0f) + 1.0f) / 2.0f;
        float blue = (sin(time * 2.0f * 3.14159f / 3.0f + 4.0f * 3.14159f / 3.0f) + 1.0f) / 2.0f;
        return flinearcolor(red, green, blue, 1.0f);
    }

    float DegreeToRadian(float degrees) {
        return degrees * (PI / 180);
    }
    float deg_2_rad(float degrees)
    {
        float radians;
        radians = degrees * (M_PI / 180);
        return radians;
    }


    struct key_bind {
        const wchar_t* name;
        int key_code;
    };
    struct ui_state {
        bool dropdown_open = false;
        int active_dropdown = -1;
        float slider_drag_value = 0.0f;
        bool is_dragging = false;
        fvector2d last_mouse_pos = { 0, 0 };
    } g_ui_state;

    size_t generate_toggle_id(const wchar_t* str) {
        size_t hash = 5381;
        while (*str) {
            hash = ((hash << 5) + hash) + *str++;
        }
        return hash % MAX_ELEMENTSS;
    }

    boolean in_rect(float centerX, float centerY, float radius, float x, float y) {
        return x >= centerX - radius && x <= centerX + radius &&
            y >= centerY - radius && y <= centerY + radius;
    }

    void(*SetCameraCachePOVOriginal)(uintptr_t, FMinimalViewInfo*) = nullptr;
    fvector	LocalCameraLocation;
    fvector	LocalCameraRotation;
    fvector	LocalCameraRotationSpin;

    fname first_name;
    fname second_name;

    struct FPeekState
    {
        bool  bActive = false;
        DWORD StartTime = 0;
    };

    static FPeekState GPeek;
    static DWORD GLastFireTime = 0;


    FORCEINLINE float NormalizeAngle67(float Angle)
    {
        while (Angle > 180.f) Angle -= 360.f;
        while (Angle < -180.f) Angle += 360.f;
        return Angle;
    }

    FORCEINLINE bool IsPeeking(const fvector& Velocity)
    {
        return fmath::Abs(Velocity.y) > 150.f && fmath::Abs(Velocity.x) < 60.f;
    }



    static float offsetX = 0.0f;

    bool isAntiAimEnabled = false;
    static float offsetY = 0.0f;
    static FMinimalViewInfo* g_viewinfo = nullptr; 

    const flinearcolor dark_outline = { 0.075f, 0.075f, 0.075f, 1.0f };
    const flinearcolor outline = { 0.122f, 0.122f, 0.122f, 1.0f };
    const flinearcolor accent_color = { 0.5f, 0.0f, 0.5f, 1.0f };
    const flinearcolor background_color = { 0.0160f, 0.0160f, 0.0160f, 1.0f };
    const flinearcolor background = { 0.010f, 0.010f, 0.010f, 1.0f };
    const flinearcolor panel_color = { 0.0180f, 0.0180f, 0.0180f, 1.0f };
    const flinearcolor border_color = { 0.0580f, 0.0580f, 0.0580f, 1.0f };
    const flinearcolor check_color = { 0.0f, 0.0f, 0.5f, 1.0f };
    const flinearcolor text_color = { 0.9f, 0.9f, 0.9f, 1.0f };
    const flinearcolor hover_color = { 0.2f, 0.2f, 0.2f, 1.0f };
    const flinearcolor disabled_color = { 0.5f, 0.5f, 0.5f, 1.0f };
    const flinearcolor handle_color = { 1.0f, 1.0f, 1.0f, 1.0f };

    const flinearcolor secondary_color = { 0.12f, 0.12f, 0.15f, 1.0f };
    const flinearcolor header_color = { 0.0f, 0.4f, 0.8f, 1.0f };

    static flinearcolor maincolor{ 1.0f,1.0f,1.0f,1.0f };
    float bowv4l = 1;


    void draw_text(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        
        canvas->k2_drawtext(font, text, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }
    void draw_text_2(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos, float text_scale) {
        
        canvas->k2_drawtext(font, text, pos, { text_scale, text_scale }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, false, true, true, { 0, 0, 0, 0.45f });
    }
    void draw_text_3(ucanvas* canvas, uobject* font, fstring nade, flinearcolor color, fvector2d pos) {
        
        canvas->k2_drawtext(font, nade, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }
    void draw_text_3(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos, float text_scale) {
        
        canvas->k2_drawtext(font, text, pos, { text_scale, text_scale }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45f });
    }
    void draw_text_custom(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor text_color, fvector2d position, float width_scale, float height_scale, float thickness, float scale_factor) {
        
        float text_scale_x = width_scale * scale_factor;
        float text_scale_y = height_scale * scale_factor;

        canvas->k2_drawtext(
            font,
            text,
            position,
            { text_scale_x, text_scale_y },
            text_color,
            0.f,
            { 0, 0, 0, 0.30f },
            { 0, 0 },
            false,
            true,
            true,
            { 0, 0, 0, 0.45f }
        );
    }

    void draw_notext(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor text_color, fvector2d position, float width_scale, float height_scale, float thickness, float scale_factor) {
        
        float text_scale_x = width_scale * scale_factor;
        float text_scale_y = height_scale * scale_factor;

        canvas->k2_drawtext(
            font,
            text,
            position,
            { text_scale_x, text_scale_y },
            text_color,
            0.f,
            { 0, 0, 0, 0 },
            { 0, 0 },
            false,
            true,
            true,
            { 0, 0, 0, 0 }
        );
    }

    void draw_text_custom_2(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor text_color, fvector2d position, float width_scale, float height_scale, float thickness, float scale_factor) {

        
        float text_scale_x = width_scale * scale_factor;
        float text_scale_y = height_scale * scale_factor;
        canvas->k2_drawtext(
            font,
            text,
            position,
            { text_scale_x, text_scale_y },
            text_color,
            0.f,
            { 0, 0, 0, 0.30f },
            { 0, 0 },
            true,
            true,
            true,
            { 0, 0, 0, 0.45f }
        );
    }

    void draw_text_centered(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        
        float text_width = wcslen(text) * 8.0f;
        float text_height = 16.0f;

        hooks::draw_text(canvas, font, text, color,
            { pos.x - text_width / 2, pos.y - text_height / 2 });
    }
    void draw_logo(ucanvas* canvas, float x, float y, float size, flinearcolor color) {

        const float half_size = size / 2;
        const float quarter_size = size / 4;

        canvas->k2_drawline(
            { x - half_size, y + half_size },
            { x, y - half_size },
            2.0f, color
        );
        canvas->k2_drawline(
            { x, y - half_size },
            { x + half_size, y + half_size },
            2.0f, color
        );
        canvas->k2_drawline(
            { x - quarter_size, y },
            { x + quarter_size, y },
            2.0f, color
        );
    }

    void draw_head(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {

        canvas->k2_drawtext(font, text, pos, { 1.50f, 1.50f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.90 });
    }
    void draw_head2(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {


        flinearcolor purple_color = flinearcolor(1.0f, 0.0f, 1.0f, 1.0f);
        flinearcolor shadow_color = flinearcolor(1.0f, 0.0f, 1.0f, 0.5f);

        fvector2d shadow_offset = fvector2d{ 2.0f, 2.0f };
        canvas->k2_drawtext(font, text, pos + shadow_offset, { 1.0f, 1.0f }, shadow_color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.90 });

        canvas->k2_drawtext(font, text, pos, { 1.0f, 1.0f }, purple_color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.90 });
    }
    void draw_filled_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {

        for (float i = 0; i < height; i++) {
            canvas->k2_drawline(
                { x, y + i },
                { x + width, y + i },
                1.0f,
                color
            );
        }
    }
    float ESPThickness = 1.1f;
    void DrawLineSimple(ucanvas* can, fvector2d first_bone_position, fvector2d second_bone_position, flinearcolor Color)
    {
        
        can->k2_drawline({ first_bone_position.x, first_bone_position.y }, { second_bone_position.x, second_bone_position.y }, ESPThickness, Color);
    }

    void Draw_Line(ucanvas* canvas, fvector2d from, fvector2d to, int thickness, flinearcolor color)
    {
        canvas->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
    }


    void Draw3DWeapon(ucanvas* Canvas, aplayercontroller* MYController, fvector ObjectLocation3D, flinearcolor Color)
    {
        
        int xz = 70;
        int uzunluk = 20;
        fvector Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
        Pos0 = ObjectLocation3D;
        Pos0.z += 10;
        Pos1 = Pos0 + fvector(-xz, -xz, uzunluk);
        Pos2 = Pos0 + fvector(-xz, -xz, -uzunluk);
        Pos3 = Pos0 + fvector(xz, -xz, -uzunluk);
        Pos4 = Pos0 + fvector(xz, -xz, uzunluk);
        Pos5 = Pos0 + fvector(-xz, xz, uzunluk);
        Pos6 = Pos0 + fvector(-xz, xz, -uzunluk);
        Pos7 = Pos0 + fvector(xz, xz, -uzunluk);
        Pos8 = Pos0 + fvector(xz, xz, uzunluk);

        fvector2d ScreenPos0, ScreenPos1, ScreenPos2, ScreenPos3, ScreenPos4, ScreenPos5, ScreenPos6, ScreenPos7, ScreenPos8;
        if (MYController->project_world_location_to_screen(Pos0, ScreenPos0, 0) && ScreenPos0.is_valid())
        {
            if (MYController->project_world_location_to_screen(Pos1, ScreenPos1, 0) && ScreenPos1.is_valid())
            {
                if (MYController->project_world_location_to_screen(Pos2, ScreenPos2, 0) && ScreenPos2.is_valid())
                {
                    if (MYController->project_world_location_to_screen(Pos3, ScreenPos3, 0) && ScreenPos3.is_valid())
                    {
                        if (MYController->project_world_location_to_screen(Pos4, ScreenPos4, 0) && ScreenPos4.is_valid())
                        {
                            if (MYController->project_world_location_to_screen(Pos5, ScreenPos5, 0) && ScreenPos5.is_valid())
                            {
                                if (MYController->project_world_location_to_screen(Pos6, ScreenPos6, 0) && ScreenPos6.is_valid())
                                {
                                    if (MYController->project_world_location_to_screen(Pos7, ScreenPos7, 0) && ScreenPos7.is_valid())
                                    {
                                        if (MYController->project_world_location_to_screen(Pos8, ScreenPos8, 0) && ScreenPos8.is_valid())
                                        {
                                            DrawLineSimple(Canvas, ScreenPos1, ScreenPos2, Color);
                                            DrawLineSimple(Canvas, ScreenPos2, ScreenPos3, Color);
                                            DrawLineSimple(Canvas, ScreenPos3, ScreenPos4, Color);
                                            DrawLineSimple(Canvas, ScreenPos4, ScreenPos1, Color);

                                            DrawLineSimple(Canvas, ScreenPos5, ScreenPos6, Color);
                                            DrawLineSimple(Canvas, ScreenPos6, ScreenPos7, Color);
                                            DrawLineSimple(Canvas, ScreenPos7, ScreenPos8, Color);
                                            DrawLineSimple(Canvas, ScreenPos8, ScreenPos5, Color);

                                            DrawLineSimple(Canvas, ScreenPos1, ScreenPos5, Color);
                                            DrawLineSimple(Canvas, ScreenPos2, ScreenPos6, Color);
                                            DrawLineSimple(Canvas, ScreenPos3, ScreenPos7, Color);
                                            DrawLineSimple(Canvas, ScreenPos4, ScreenPos8, Color);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


    }

    void draw_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
        
        canvas->k2_drawline({ x, y }, { x + width, y }, 1.0f, color);
        canvas->k2_drawline({ x + width, y }, { x + width, y + height }, 1.0f, color);
        canvas->k2_drawline({ x + width, y + height }, { x, y + height }, 1.0f, color);
        canvas->k2_drawline({ x, y + height }, { x, y }, 1.0f, color);
    }

    inline auto DrawBorder(ucanvas* nigga, float x, float y, float w, float h, float px, flinearcolor BorderColor) -> void
    {
        
        draw_rect(nigga, x, (y + h - px), w, px, BorderColor);
        draw_rect(nigga, x, y, px, h, BorderColor);
        draw_rect(nigga, x, y, w, px, BorderColor);
        draw_rect(nigga, (x + w - px), y, px, h, BorderColor);
    }


    void draw_rect_2(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color, float tickness) {
        
        canvas->k2_drawline({ x, y }, { x + width, y }, 1.0f, color);
        canvas->k2_drawline({ x + width, y }, { x + width, y + height }, 1.0f, color);
        canvas->k2_drawline({ x + width, y + height }, { x, y + height }, 1.0f, color);
        canvas->k2_drawline({ x, y + height }, { x, y }, 1.0f, color);
    }
    void draw_rounded_rect(ucanvas* canvas, float x, float y, float width, float height, float radius, flinearcolor color) {
        
        const int segments = 16;
        const float angle_step = PI / 2 / segments;

        for (int i = 0; i < segments; i++) {
            float angle1 = PI + i * angle_step;
            float angle2 = angle1 + angle_step;
            canvas->k2_drawline(
                { x + radius + radius * cos(angle1), y + radius + radius * sin(angle1) },
                { x + radius + radius * cos(angle2), y + radius + radius * sin(angle2) },
                2.0f, color
            );
        }

        for (int i = 0; i < segments; i++) {
            float angle1 = 3 * PI / 2 + i * angle_step;
            float angle2 = angle1 + angle_step;
            canvas->k2_drawline(
                { x + width - radius + radius * cos(angle1), y + radius + radius * sin(angle1) },
                { x + width - radius + radius * cos(angle2), y + radius + radius * sin(angle2) },
                2.0f, color
            );
        }

        for (int i = 0; i < segments; i++) {
            float angle1 = i * angle_step;
            float angle2 = angle1 + angle_step;
            canvas->k2_drawline(
                { x + width - radius + radius * cos(angle1), y + height - radius + radius * sin(angle1) },
                { x + width - radius + radius * cos(angle2), y + height - radius + radius * sin(angle2) },
                2.0f, color
            );
        }

        for (int i = 0; i < segments; i++) {
            float angle1 = PI / 2 + i * angle_step;
            float angle2 = angle1 + angle_step;
            canvas->k2_drawline(
                { x + radius + radius * cos(angle1), y + height - radius + radius * sin(angle1) },
                { x + radius + radius * cos(angle2), y + height - radius + radius * sin(angle2) },
                2.0f, color
            );
        }

        canvas->k2_drawline({ x + radius, y }, { x + width - radius, y }, 2.0f, color);
        canvas->k2_drawline({ x + width, y + radius }, { x + width, y + height - radius }, 2.0f, color);
        canvas->k2_drawline({ x + radius, y + height }, { x + width - radius, y + height }, 2.0f, color);
        canvas->k2_drawline({ x, y + radius }, { x, y + height - radius }, 2.0f, color);
    }
    void draw_modern_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color, float border_thickness = 1.0f) {

        for (float i = 0; i < height; i++) {
            canvas->k2_drawline(
                { x, y + i },
                { x + width, y + i },
                1.0f,
                color
            );
        }

        canvas->k2_drawline({ x, y }, { x + width, y }, border_thickness, border_color);
        canvas->k2_drawline({ x + width, y }, { x + width, y + height }, border_thickness, border_color);
        canvas->k2_drawline({ x, y + height }, { x + width, y + height }, border_thickness, border_color);
        canvas->k2_drawline({ x, y }, { x, y + height }, border_thickness, border_color);
    }

    inline bool IsScoped(EAresEquippableState state)
    {
        return state == EAresEquippableState::ADS_Idle ||
            state == EAresEquippableState::ADS_Firing;
    }


    void draw_gradient_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor start_color, flinearcolor end_color, bool vertical = false) {

        

        const int steps = 20;
        float step_size = vertical ? height / steps : width / steps;

        for (int i = 0; i < steps; i++) {
            float t = (float)i / (steps - 1);
            flinearcolor current_color = {
                start_color.r + (end_color.r - start_color.r) * t,
                start_color.g + (end_color.g - start_color.g) * t,
                start_color.b + (end_color.b - start_color.b) * t,
                start_color.a + (end_color.a - start_color.a) * t
            };

            if (vertical) {
                canvas->k2_drawline(
                    { x, y + i * step_size },
                    { x + width, y + i * step_size },
                    step_size,
                    current_color
                );
            }
            else {
                canvas->k2_drawline(
                    { x + i * step_size, y },
                    { x + i * step_size, y + height },
                    step_size,
                    current_color
                );
            }
        }
    }
    bool draw_toggle_button(ucanvas* canvas, uobject* font, const wchar_t* label, bool state, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked, bool selected) {
        
        const float button_width = 260.0f;
        const float button_height = 32.0f;
        const float toggle_width = 40.0f;
        const float toggle_height = 20.0f;
        const float text_padding = 35.0f;

        bool is_hovered = (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + button_width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + button_height);

        draw_gradient_rect(canvas, pos.x, pos.y, button_width, button_height,
            is_hovered ? hover_color : panel_color,
            secondary_color);

        hooks::draw_text(canvas, font, label, disabled_color, { pos.x + text_padding + 1, pos.y + 8.0f + 1 });
        hooks::draw_text(canvas, font, label, text_color, { pos.x + text_padding, pos.y + 8.0f });

        float toggle_x = pos.x + button_width - toggle_width - 12.0f;
        float toggle_y = pos.y + (button_height - toggle_height) / 2;

        draw_rounded_rect(canvas, toggle_x, toggle_y, toggle_width, toggle_height, toggle_height / 2,
            state ? accent_color : disabled_color);

        float knob_size = toggle_height - 4.0f;
        float knob_x = toggle_x + 2.0f + (state ? toggle_width - knob_size - 4.0f : 0.0f);
        draw_rounded_rect(canvas, knob_x, toggle_y + 2.0f, knob_size, knob_size, knob_size / 2,
            text_color);

        return is_hovered && mouse_clicked;
    }
    void draw_triangle(ucanvas* canvas, float x, float y, float size, flinearcolor color) {
        
        const float half_size = size / 2;
        canvas->k2_drawline({ x - half_size, y - half_size }, { x + half_size, y - half_size }, 2.0f, color);
        canvas->k2_drawline({ x + half_size, y - half_size }, { x, y + half_size }, 2.0f, color);
        canvas->k2_drawline({ x, y + half_size }, { x - half_size, y - half_size }, 2.0f, color);
    }
    void draw_section_header(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor color, fvector2d pos) {
        
        const float header_width = 260.0f;
        const float header_height = 25.0f;

        canvas->k2_drawline(pos, { pos.x + header_width, pos.y }, 2.0f, color);
        hooks::draw_text(canvas, font, label, color, { pos.x, pos.y - header_height });
    }

    bool draw_color_picker(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        
        const float hue_slider_width = 100.0f;
        const float hue_slider_height = 7.0f;
        const float sb_picker_size = 75.0f;
        const float alpha_slider_width = hue_slider_width;
        const float alpha_slider_height = 7.0f;
        const float preview_box_size = 15.0f;
        const float spacing = 5.0f;

        static bool hue_dragging = false;
        static bool sb_dragging = false;
        static bool alpha_dragging = false;

        static float hue = 0.0f;
        static float saturation = 1.0f;
        static float brightness = 1.0f;

        float thickness = 2.0f;
        float width_scale = 1.0f;
        float height_scale = 0.8f;
        float text_scale = 1.1f;

        bool value_changed = false;

        for (int i = 0; i < hue_slider_width; i++) {
            float h = (float)i / hue_slider_width;
            flinearcolor color_at_hue = HSVtoRGB(h, 1.0f, 1.0f);
            draw_filled_rect(canvas, pos.x + i, pos.y, 1.0f, hue_slider_height, color_at_hue);
        }
        draw_rect(canvas, pos.x, pos.y, hue_slider_width, hue_slider_height, border_color);

        if (mouse_clicked && mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + hue_slider_width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + hue_slider_height) {
            hue_dragging = true;
        }
        if (hue_dragging) {
            if (mouse_clicked) {
                hue = (mouse_pos.x - pos.x) / hue_slider_width;
                hue = clamp(hue, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                hue_dragging = false;
            }
        }

        fvector2d sb_pos = { pos.x, pos.y + hue_slider_height + spacing };

        for (int y = 0; y < sb_picker_size; y++) {
            for (int x = 0; x < sb_picker_size; x++) {
                float s = (float)x / sb_picker_size;
                float b = 1.0f - (float)y / sb_picker_size;
                flinearcolor sb_color = HSVtoRGB(hue, s, b);
                draw_filled_rect(canvas, sb_pos.x + x, sb_pos.y + y, 1.0f, 1.0f, sb_color);
            }
        }
        draw_rect(canvas, sb_pos.x, sb_pos.y, sb_picker_size, sb_picker_size, border_color);

        if (mouse_clicked && mouse_pos.x >= sb_pos.x && mouse_pos.x <= sb_pos.x + sb_picker_size &&
            mouse_pos.y >= sb_pos.y && mouse_pos.y <= sb_pos.y + sb_picker_size) {
            sb_dragging = true;
        }
        if (sb_dragging) {
            if (mouse_clicked) {
                saturation = (mouse_pos.x - sb_pos.x) / sb_picker_size;
                brightness = 1.0f - (mouse_pos.y - sb_pos.y) / sb_picker_size;
                saturation = clamp(saturation, 0.0f, 1.0f);
                brightness = clamp(brightness, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                sb_dragging = false;
            }
        }

        fvector2d alpha_pos = { pos.x, sb_pos.y + sb_picker_size + spacing };

        for (int i = 0; i < alpha_slider_width; i++) {
            float alpha = (float)i / alpha_slider_width;
            flinearcolor alpha_color = HSVtoRGB(hue, saturation, brightness);
            alpha_color.a = alpha;
            draw_filled_rect(canvas, alpha_pos.x + i, alpha_pos.y, 1.0f, alpha_slider_height, alpha_color);
        }
        draw_rect(canvas, alpha_pos.x, alpha_pos.y, alpha_slider_width, alpha_slider_height, border_color);

        if (mouse_clicked && mouse_pos.x >= alpha_pos.x && mouse_pos.x <= alpha_pos.x + alpha_slider_width &&
            mouse_pos.y >= alpha_pos.y && mouse_pos.y <= alpha_pos.y + alpha_slider_height) {
            alpha_dragging = true;
        }
        if (alpha_dragging) {
            if (mouse_clicked) {
                color.a = (mouse_pos.x - alpha_pos.x) / alpha_slider_width;
                color.a = clamp(color.a, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                alpha_dragging = false;
            }
        }

        flinearcolor final_color = HSVtoRGB(hue, saturation, brightness);
        color.r = final_color.r;
        color.g = final_color.g;
        color.b = final_color.b;

        fvector2d preview_pos = { pos.x + hue_slider_width + spacing, pos.y };
        draw_filled_rect(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, { color.r, color.g, color.b, color.a });
        draw_rect(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, border_color);

        return value_changed;
    }
    bool draw_color_picker_menu(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        
        static bool picker_open = false;
        static fvector2d picker_pos = pos;
        const float box_size = 16.0f;
        const float pencil_offset = 5.0f;

        if (picker_open && mouse_clicked &&
            !(mouse_pos.x >= picker_pos.x && mouse_pos.x <= picker_pos.x + 200.0f &&
                mouse_pos.y >= picker_pos.y && mouse_pos.y <= picker_pos.y + 220.0f)) {
            picker_open = false;
        }

        draw_filled_rect(canvas, pos.x, pos.y, box_size, box_size, color);
        draw_rect(canvas, pos.x, pos.y, box_size, box_size, border_color);

        fvector2d pencil_start = { pos.x + pencil_offset, pos.y + box_size - pencil_offset };
        fvector2d pencil_end = { pos.x + box_size - pencil_offset, pos.y + pencil_offset };
        canvas->k2_drawline(pencil_start, pencil_end, 1.0f, text_color);

        if (mouse_clicked &&
            mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + box_size &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + box_size) {
            picker_open = !picker_open;
            picker_pos = { pos.x, pos.y + box_size + 10.0f };
        }

        if (picker_open) {
            return draw_color_picker(canvas, font, label, color, picker_pos, mouse_pos, mouse_clicked);
        }

        return false;
    }


    void angle_vectors(const fvector& angles, fvector* forward)
    {
        
        float    sp, sy, cp, cy;
        sy = sin(deg_2_rad(angles.y));
        cy = cos(deg_2_rad(angles.y));
        sp = sin(deg_2_rad(angles.x));
        cp = cos(deg_2_rad(angles.x));
        forward->x = cp * cy;
        forward->y = cp * sy;
        forward->z = -sp;
    }

    void draw_checkbox(ucanvas* canvas, fvector2d pos, bool value, float animation_progress) {
        
        const float size = 14.0f;
        static const flinearcolor border_color = { 0.2f, 0.2f, 0.2f, 1.0f };
        static const flinearcolor fill_color = { 0.5f, 0.0f, 1.0f, 1.0f };

        draw_modern_rect(canvas, pos.x, pos.y, size, size, border_color);

        if (animation_progress > 0.0f) {
            flinearcolor animated_fill = fill_color;
            animated_fill.a = animation_progress;
            draw_modern_rect(canvas,
                pos.x + 2.0f,
                pos.y + 2.0f,
                size - 1.0f,
                size - 1.0f,
                animated_fill
            );
        }
    }

    void draw_line(ucanvas* canvas, const fvector2d& start, const fvector2d& end, const flinearcolor& color, float& line_thickness) {
        
        if (!canvas) return;

        canvas->k2_drawline(
            fvector2d{ start.x, start.y },
            fvector2d{ end.x, end.y },
            1.0f,
            color
        );
    }

    void draw_checkbox_2(ucanvas* canvas, float x, float y, bool& value, flinearcolor check_color, flinearcolor border_color, fvector2d mouse_pos, bool mouse_clicked) {
        
        constexpr float checkbox_size = 16.0f;
        constexpr float padding = 0.04f;
        static bool debounce = false;

        draw_rect(canvas, x, y, checkbox_size, checkbox_size, border_color);

        if (value) {
            draw_filled_rect(canvas, x + padding, y + padding, checkbox_size - 2 * padding, checkbox_size - 2 * padding, check_color);

            float size = checkbox_size;
            fvector2d pos = { x, y };

            float line_thickness = 30.0f;

            // lines
            draw_line(canvas, fvector2d(pos.x + 4, pos.y + size * 0.55f), fvector2d(pos.x + size * 0.25f, pos.y + size * 0.75f), flinearcolor(1, 1, 1, 1), line_thickness);
            draw_line(canvas, fvector2d(pos.x + size * 0.25f, pos.y + size * 0.75f), fvector2d(pos.x + size - 4, pos.y + size * 0.2f), flinearcolor(1, 1, 1, 1), line_thickness);

        }
        if (mouse_clicked) {
            if (!debounce &&
                mouse_pos.x >= x && mouse_pos.x <= x + checkbox_size &&
                mouse_pos.y >= y && mouse_pos.y <= y + checkbox_size) {
                value = !value;
                debounce = true;
            }
        }
        else {
            debounce = false;
        }
    }

    void draw_modern_dropdown(ucanvas* canvas, uobject* font, const wchar_t* label, int& current_index, const wchar_t** items, int item_count, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked, float text_scale) {
        
        const float dropdown_width = 100.0f;
        const float dropdown_height = 25.0f;
        const float item_height = 25.0f;
        static bool dropdown_open = false;
        static bool mouse_released = true;

        float thickness = 0.8f;
        float width_scale = 1.0f;
        float height_scale = 0.9f;

        if (mouse_clicked && mouse_released && mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + dropdown_width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + dropdown_height) {
            dropdown_open = !dropdown_open;
            mouse_released = false;
        }

        if (!mouse_clicked) {
            mouse_released = true;
        }

        draw_filled_rect(canvas, pos.x, pos.y, dropdown_width, dropdown_height, panel_color);
        draw_rect(canvas, pos.x, pos.y, dropdown_width, dropdown_height, border_color);

        float label_x = pos.x;
        float label_y = pos.y - 10.0f;
        hooks::draw_text_custom(canvas, font, label, text_color, { label_x, label_y }, width_scale, height_scale, thickness, 1.0f);

        float value_x = pos.x + (dropdown_width - wcslen(items[current_index]) * 10) / 2;
        float value_y = pos.y + (dropdown_height / 2) - (1.0f * 10.0f / 2) + 5.0f;
        hooks::draw_text_custom(canvas, font, items[current_index], text_color, { value_x, value_y }, width_scale, height_scale, thickness, 1.0f);

        if (dropdown_open) {
            for (int i = 0; i < item_count; i++) {
                float item_y = pos.y + dropdown_height + i * item_height;

                bool is_hovered = (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + dropdown_width &&
                    mouse_pos.y >= item_y && mouse_pos.y <= item_y + item_height);

                draw_filled_rect(canvas, pos.x, item_y, dropdown_width, item_height, is_hovered ? hover_color : panel_color);
                draw_rect(canvas, pos.x, item_y, dropdown_width, item_height, border_color);

                float item_text_x = pos.x + (dropdown_width - wcslen(items[i]) * 10) / 2;
                float item_text_y = item_y + (item_height / 2) - (1.0f * 10.0f / 2);
                hooks::draw_text_custom(canvas, font, items[i], text_color, { item_text_x, item_text_y }, width_scale, height_scale, thickness, 1.0f);

                if (mouse_clicked && is_hovered) {
                    current_index = i;
                    dropdown_open = false;
                }
            }
        }
    }

    float draw_slider(ucanvas* canvas, uobject* font, const wchar_t* label, float min_value, float max_value, float& value, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked, bool& is_dragging) {
        
        const float control_width = 150.0f; // ancho del slider (aumentado)
        const float control_height = 8.0f; // altura de la pista (aumentada)
        const float track_height = 8.0f; // altura de la pista (aumentada)
        const float handle_size = 8.0f; // tamaño del handle (aumentado)
        const float label_offset_y = 10.0f; // distancia del texto al slider
        const float value_offset_x = 10.0f; // distancia del número al slider

        // text
        float thickness = 0.8f; // grosor del texto
        float width_scale = 1.0f; // escala de anchura
        float height_scale = 0.9f; // escala de altura
        float text_scale = 1.0f; // escala del tamaño de la fuente

        float normalized = (value - min_value) / (max_value - min_value);
        std::wstring value_str = std::to_wstring(static_cast<int>(value));

        hooks::draw_text_custom(canvas, font, label, text_color, { pos.x, pos.y - label_offset_y }, width_scale, height_scale, thickness, text_scale);

        float track_y = pos.y;
        draw_filled_rect(canvas, pos.x, track_y, control_width, track_height, border_color);

        float filled_width = control_width * normalized;
        draw_filled_rect(canvas, pos.x, track_y, filled_width, track_height, accent_color);

        float handle_pos = pos.x + normalized * control_width;
        draw_filled_rect(canvas, handle_pos - handle_size / 2, track_y - handle_size / 2 + track_height / 2,
            handle_size, handle_size, text_color);

        float value_text_x = pos.x + control_width - value_offset_x;
        float value_text_y = pos.y - label_offset_y;
        hooks::draw_text_custom(canvas, font, value_str.c_str(), text_color, { value_text_x, value_text_y }, width_scale, height_scale, thickness, text_scale);

        bool handle_hovered = (mouse_pos.x >= handle_pos - handle_size / 2 && mouse_pos.x <= handle_pos + handle_size / 2 &&
            mouse_pos.y >= track_y - handle_size / 2 && mouse_pos.y <= track_y + handle_size / 2);

        if (mouse_clicked && handle_hovered) {
            is_dragging = true;
        }

        if (is_dragging) {
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                float new_normalized = (mouse_pos.x - pos.x) / control_width;
                new_normalized = clamp(new_normalized, 0.0f, 1.0f);
                value = min_value + new_normalized * (max_value - min_value);
            }
            else {
                is_dragging = false;
            }
        }
        return value;
    }
    void DrawLineCanvas(ucanvas* canvas, int x1, int y1, int x2, int y2, flinearcolor color, int thickness)
    {
        
        canvas->k2_drawline(fvector2d(x1, y1), fvector2d(x2, y2), thickness, color);
    }


    void draw_line_2(ucanvas* nigga, fvector2d from, fvector2d to, int thickness, flinearcolor color)
    {
        
        nigga->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
    }
    void drawcircle(ucanvas* canvas, fvector2d pos, int radius, int numSides, flinearcolor Color)
    {
        
        float PI = 3.1415927f;

        float Step = PI * 2.0 / numSides;
        int Count = 0;
        fvector2d V[128];
        for (float a = 0; a < PI * 2.0; a += Step) {
            float X1 = radius * cos(a) + pos.x;
            float Y1 = radius * sin(a) + pos.y;
            float X2 = radius * cos(a + Step) + pos.x;
            float Y2 = radius * sin(a + Step) + pos.y;
            V[Count].x = X1;
            V[Count].y = Y1;
            V[Count + 1].x = X2;
            V[Count + 1].y = Y2;

            draw_line_2(canvas, fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, 1.0f, Color);
        }
    }


    void DrawFilledCircle23(ucanvas* canvas, fvector2d pos, int radius, int numSides, flinearcolor Color)
    {
        if (!canvas) return;

        float PI = 3.1415927f;
        float Step = PI * 2.0f / numSides;

        for (int i = 0; i < numSides; ++i)
        {
            float angle1 = Step * i;
            float angle2 = Step * (i + 1);

            fvector2d point1 = fvector2d(pos.x + radius * cosf(angle1), pos.y + radius * sinf(angle1));
            fvector2d point2 = fvector2d(pos.x + radius * cosf(angle2), pos.y + radius * sinf(angle2));

            // Draw triangle "fill" as two lines from center to the two points,
            // then the line between those two points to close the segment
            canvas->k2_drawline(pos, point1, 1.0f, Color);
            canvas->k2_drawline(point1, point2, 1.0f, Color);
            canvas->k2_drawline(pos, point2, 1.0f, Color);
        }
    }

    void DrawFilledCircle(fvector2d pos, float r, flinearcolor color, ucanvas* canvas)
    {
        
        constexpr float smooth = 0.05f;
        constexpr double PI = 3.14159265359;
        int numSegments = static_cast<int>(2.0f * PI / smooth) + 1;

        for (float angle = 0; angle < 2 * PI; angle += smooth)
        {
            for (float innerRadius = 0; innerRadius < r; innerRadius += 1.0f)
            {
                fvector2d point = { pos.x + cosf(angle) * innerRadius, pos.y + sinf(angle) * innerRadius };
                draw_line_2(canvas, pos, point, 1.0f, color);
            }
        }
    }

    void DrawLineSimple_Spike(ucanvas* can, fvector2d first_bone_position, fvector2d second_bone_position, flinearcolor Color) {
        can->k2_drawline({ first_bone_position.x, first_bone_position.y }, { second_bone_position.x, second_bone_position.y }, 0.9f, Color);
    }

    namespace radar
    {
        static fvector pRadar;
        void DrawCircleRadar(int x, int y, int radius, flinearcolor color, ucanvas* nigga)
        {
            
            DrawFilledCircle(fvector2d(x, y), radius, color, nigga);
        }

        fvector WorldRadar(fvector srcPos, fvector distPos, float yaw, float radarX, float radarY, float size)
        {
            
            auto cosYaw = cos(DegreeToRadian(yaw));
            auto sinYaw = sin(DegreeToRadian(yaw));

            auto deltaX = srcPos.x - distPos.x;
            auto deltaY = srcPos.y - distPos.y;

            auto locationX = (float)(deltaY * cosYaw - deltaX * sinYaw) / 45.f;
            auto locationY = (float)(deltaX * cosYaw + deltaY * sinYaw) / 45.f;

            if (locationX > (size - 2.f))
                locationX = (size - 2.f);
            else if (locationX < -(size - 2.f))
                locationX = -(size - 2.f);

            if (locationY > (size - 6.f))
                locationY = (size - 6.f);
            else if (locationY < -(size - 6.f))
                locationY = -(size - 6.f);

            return fvector((int)(-locationX + radarX), (int)(locationY + radarY), 0);
        }
    }


    bool draw_keybind_button(ucanvas* canvas, uobject* font, const wchar_t* label, int& key_to_bind, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        
        const float button_width = 55.0f;
        const float button_height = 20.0f;
        const float text_scale = 0.8f;
        const float padding = 5.0f;
        static bool listening = false;
        static wchar_t current_key_name[64] = L"";

        auto vk_to_name = [](int key) -> std::wstring {
            switch (key) {
            case VK_LBUTTON: return L"lb";
            case VK_RBUTTON: return L"rb";
            case VK_MBUTTON: return L"mb";
            case VK_XBUTTON1: return L"m4";
            case VK_XBUTTON2: return L"m5";
            case VK_NUMPAD0: return L"np0";
            case VK_NUMPAD1: return L"np1";
            case VK_NUMPAD2: return L"np2";
            case VK_NUMPAD3: return L"np3";
            case VK_NUMPAD4: return L"np4";
            case VK_NUMPAD5: return L"np5";
            case VK_NUMPAD6: return L"np6";
            case VK_NUMPAD7: return L"np7";
            case VK_NUMPAD8: return L"np7";
            case VK_NUMPAD9: return L"np9";
            case VK_MENU: return L"alt";
            case VK_CAPITAL: return L"caps";
            case VK_INSERT: return L"ins";
            case VK_DELETE: return L"del";
            case VK_END: return L"end";
            case VK_TAB: return L"tab";
            case VK_BACK: return L"back";
            case 0x0: return L"none";
            default: {
                CHAR output[16] = { "\0" };
                if (GetKeyNameTextA(MapVirtualKeyW(key, MAPVK_VK_TO_VSC) << 16, output, 16)) {
                    std::wstring result = s2wc(output);
                    std::transform(result.begin(), result.end(), result.begin(), ::towlower);
                    return result;
                }
                return L"";
            }
            }
            };


        draw_filled_rect(canvas, pos.x, pos.y, button_width, button_height, panel_color);


        draw_rect(canvas, pos.x, pos.y, button_width, button_height, border_color);


        const wchar_t* button_text;
        if (listening) {
            button_text = L"...";
        }
        else {
            if (key_to_bind != 0) {
                std::wstring key_name = vk_to_name(key_to_bind);
                wcscpy_s(current_key_name, key_name.c_str());
                button_text = current_key_name;
            }
            else {
                button_text = label;
            }
        }

        float text_x = pos.x + (button_width / 2);
        float text_y = pos.y + (button_height / 2);

        hooks::draw_text_3(canvas, font, button_text, text_color, { text_x, text_y }, text_scale);

        float clickable_x_start = pos.x;
        float clickable_x_end = pos.x + button_width;
        float clickable_y_start = pos.y;
        float clickable_y_end = pos.y + button_height;

        if (mouse_clicked) {
            if (mouse_pos.x >= clickable_x_start && mouse_pos.x <= clickable_x_end &&
                mouse_pos.y >= clickable_y_start && mouse_pos.y <= clickable_y_end) {
                listening = true;
                wcscpy_s(current_key_name, L"...");
                return false;
            }
        }


        if (listening) {
            for (int code = 0; code < 256; code++) {
                if (GetAsyncKeyState(code) & 0x8000) {
                    if (code == VK_ESCAPE) {
                        key_to_bind = 0;
                        wcscpy_s(current_key_name, L"..");
                    }
                    else {
                        key_to_bind = code;
                        std::wstring key_name = vk_to_name(code);
                        wcscpy_s(current_key_name, key_name.c_str());
                    }
                    listening = false;
                    return true;
                }
            }
        }

        return false;
    }
    flinearcolor blend(flinearcolor col, float alpha)
    {
        // blend with black background (0,0,0)
        return flinearcolor(col.r * alpha, col.g * alpha, col.b * alpha, 1.0f);
    }

    void DrawFilledRect(ucanvas* can, fvector2d topleft, fvector2d downright, flinearcolor clr, float alpha)
    {
        

        float left = fminf(topleft.x, downright.x);
        float right = fmaxf(topleft.x, downright.x);
        float top = fminf(topleft.y, downright.y);
        float bottom = fmaxf(topleft.y, downright.y);

        flinearcolor blended = blend(clr, alpha); // darkened instead of real transparency

        for (float y = top; y <= bottom; y += 1.0f)
        {
            can->k2_drawline({ left, y }, { right, y }, 1.0f, blended);
        }
    }
    float CrossProduct2D(const fvector2d& O, const fvector2d& A, const fvector2d& B) {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    // Calculate squared distance between two points (faster and no sqrt needed)
    float SquaredDistance(const fvector2d& A, const fvector2d& B) {
        float dx = A.x - B.x;
        float dy = A.y - B.y;
        return dx * dx + dy * dy;
    }


    tarray<fvector2d> GrahamScan(tarray<fvector2d> points) {
        if (points.size() < 3) return points;

        int n = points.size();
        int minY = 0;
        for (int i = 1; i < n; i++) {
            if (points[i].y < points[minY].y ||
                (points[i].y == points[minY].y && points[i].x < points[minY].x)) {
                minY = i;
            }
        }

        fvector2d temp = points[0];
        points[0] = points[minY];
        points[minY] = temp;

        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                fvector2d pivot = points[0];
                float cross = CrossProduct2D(pivot, points[i], points[j]);

                if (cross < 0) {
                    fvector2d temp2 = points[i];
                    points[i] = points[j];
                    points[j] = temp2;
                }
                else if (abs(cross) < 0.001f) {
                    float dist1 = SquaredDistance(pivot, points[i]);
                    float dist2 = SquaredDistance(pivot, points[j]);
                    if (dist1 > dist2) {
                        fvector2d temp2 = points[i];
                        points[i] = points[j];
                        points[j] = temp2;
                    }
                }
            }
        }

        fvector2d* hullData = new fvector2d[n];
        int hullSize = 0;

        hullData[hullSize++] = points[0];
        hullData[hullSize++] = points[1];
        hullData[hullSize++] = points[2];

        for (int i = 3; i < n; i++) {
            while (hullSize > 1) {
                fvector2d a = hullData[hullSize - 2];
                fvector2d b = hullData[hullSize - 1];
                fvector2d c = points[i];

                if (CrossProduct2D(a, b, c) <= 0) {
                    hullSize--; 
                }
                else {
                    break;
                }
            }
            hullData[hullSize++] = points[i];
        }

        return tarray<fvector2d>(hullData, hullSize, hullSize);
    }

    void DrawLineSimple_3D(ucanvas* can, fvector2d first_bone_position, fvector2d second_bone_position, flinearcolor Color) {
        can->k2_drawline({ first_bone_position.x, first_bone_position.y }, { second_bone_position.x, second_bone_position.y }, 1.15f, Color);
    }

    void DrawConvexHull(ucanvas* Canvas, tarray<fvector2d> hullPoints, flinearcolor Color) {
        if (hullPoints.size() < 2) return;

        for (int i = 0; i < hullPoints.size(); i++) {
            int next = (i + 1) % hullPoints.size();
            DrawLineSimple_3D(Canvas, hullPoints[i], hullPoints[next], Color);
        }
    }

    void DrawBox(ucanvas* can, fvector2d& topleft, fvector2d& downright,
        flinearcolor clr, bool filled = true, float alpha = 0.25f)
    {
        if (filled)
        {
            // use actual color with transparency
            DrawFilledRect(can, topleft, downright, clr, alpha);
        }

        int thicc = 1;
        can->k2_drawline(topleft, { downright.x, topleft.y }, thicc, clr);
        can->k2_drawline(topleft, { topleft.x , downright.y }, thicc, clr);
        can->k2_drawline(downright, { topleft.x , downright.y }, thicc, clr);
        can->k2_drawline(downright, { downright.x, topleft.y }, thicc, clr);
    }

    void DrawCornerBox(ucanvas* can, fvector2d& topleft, fvector2d& downright,
        flinearcolor clr, bool filled = true, float alpha = 0.25f)
    {
        if (filled)
        {
            DrawFilledRect(can, topleft, downright, clr, alpha);
        }

        auto h = downright.y - topleft.y;
        auto w = downright.x - topleft.x;

        float lineW = w / 4.f;
        float lineH = h / 4.f;
        int thicc = 1;

        can->k2_drawline(topleft, { topleft.x + lineW, topleft.y }, thicc, clr);
        can->k2_drawline(topleft, { topleft.x, topleft.y + lineH }, thicc, clr);

        can->k2_drawline({ downright.x - lineW, topleft.y }, { downright.x, topleft.y }, thicc, clr);
        can->k2_drawline({ downright.x, topleft.y + lineH }, { downright.x, topleft.y }, thicc, clr);

        can->k2_drawline({ topleft.x, downright.y - lineH }, { topleft.x, downright.y }, thicc, clr);
        can->k2_drawline({ topleft.x + lineW, downright.y }, { topleft.x, downright.y }, thicc, clr);

        can->k2_drawline({ downright.x - lineW, downright.y }, { downright.x, downright.y }, thicc, clr);
        can->k2_drawline({ downright.x, downright.y - lineH }, { downright.x, downright.y }, thicc, clr);
    }

    static void Draw3DBox(
        ucanvas* canvas,
        aplayercontroller* controller,
        const fvector& head_location,
        const fvector& root_location,
        const flinearcolor& color)
    {
        if (!canvas || !controller) return;

        constexpr float box_width = 40.0f;   // Half-width on X and Y
        constexpr float head_offset = 15.0f; // Slight upward offset for head top

        // Compute 8 corners of the 3D box
        fvector top = head_location + fvector(0, 0, head_offset);
        fvector bottom = root_location;

        fvector box_corners_world[8] =
        {
            // Bottom rectangle (feet)
            { bottom.x + box_width, bottom.y - box_width, bottom.z },
            { bottom.x - box_width, bottom.y - box_width, bottom.z },
            { bottom.x - box_width, bottom.y + box_width, bottom.z },
            { bottom.x + box_width, bottom.y + box_width, bottom.z },

            // Top rectangle (head)
            { top.x + box_width, top.y - box_width, top.z },
            { top.x - box_width, top.y - box_width, top.z },
            { top.x - box_width, top.y + box_width, top.z },
            { top.x + box_width, top.y + box_width, top.z }
        };

        fvector2d box_corners_screen[8];
        for (int i = 0; i < 8; ++i)
        {
            if (!controller->project_world_location_to_screen(box_corners_world[i], box_corners_screen[i], false) ||
                !box_corners_screen[i].is_valid())
            {
                return; // skip if any point is invalid
            }
        }

        // Draw vertical edges
        for (int i = 0; i < 4; ++i)
        {
            canvas->k2_drawline(box_corners_screen[i], box_corners_screen[i + 4], 1.2f, color);
        }

        // Draw top face
        for (int i = 4; i < 8; ++i)
        {
            canvas->k2_drawline(box_corners_screen[i], box_corners_screen[4 + ((i + 1) % 4)], 1.2f, color);
        }

        // Draw bottom face
        for (int i = 0; i < 4; ++i)
        {
            canvas->k2_drawline(box_corners_screen[i], box_corners_screen[(i + 1) % 4], 1.2f, color);
        }
    }


    void Clamp(fvector& Ang) {
        
        if (Ang.x < 0.f)
            Ang.x += 360.f;

        if (Ang.x > 360.f)
            Ang.x -= 360.f;

        if (Ang.y < 0.f) Ang.y += 360.f;
        if (Ang.y > 360.f) Ang.y -= 360.f;

    }

    // draw oq
    void draw_oq_toggle(ucanvas* canvas, uobject* font, const wchar_t* label, bool& value, fvector2d pos, fvector2d mouse_pos, bool clicked) {
        
        const float width = 110.0f;
        const float height = 20.0f;
        const float checkbox_offset = 10.0f;

        size_t toggle_id = generate_toggle_id(label);
        AnimationState& anim_state = g_animation_manager.get_toggle_animation(toggle_id);

        fvector2d checkbox_pos = { pos.x + width - checkbox_offset, pos.y + 2.0f };

        bool hovered = (mouse_pos.x >= checkbox_pos.x && mouse_pos.x <= checkbox_pos.x + 16.0f &&
            mouse_pos.y >= checkbox_pos.y && mouse_pos.y <= checkbox_pos.y + 16.0f);

        if (hovered && clicked) {
            value = !value;
            anim_state.target_value = value;
        }

        const float animation_speed = 0.2f;
        if (value && anim_state.progress < 1.0f) {
            anim_state.progress += animation_speed;
            if (anim_state.progress > 1.0f) anim_state.progress = 1.0f;
        }
        else if (!value && anim_state.progress > 0.0f) {
            anim_state.progress -= animation_speed;
            if (anim_state.progress < 0.0f) anim_state.progress = 0.0f;
        }

        float thickness = 1.0f;
        float width_scale = 1.0f;
        float height_scale = 0.8f;
        float text_scale = 0.9f;

        hooks::draw_text_custom(canvas, font, label, { 0.9f, 0.9f, 0.9f, 1.0f }, { pos.x + 5.0f, pos.y + 2.0f }, width_scale, height_scale, 3.0f, text_scale);
        draw_checkbox(canvas, checkbox_pos, value, anim_state.progress);
    }

    void draw_oq_dropdown(ucanvas* canvas, uobject* font, const wchar_t* label, int& current_index, const wchar_t** items, int item_count, fvector2d pos, fvector2d mouse_pos, bool clicked) {
        
        const float width = 200.0f;
        const float height = 30.0f;
        static const flinearcolor bg = { 0.04f, 0.04f, 0.04f, 1.0f };
        static const flinearcolor hover_bg = { 0.08f, 0.08f, 0.08f, 1.0f };
        static const flinearcolor accent = { 0.5f, 0.0f, 1.0f, 1.0f };

        static size_t dropdown_id = g_animation_manager.register_dropdown();
        DropdownState& state = g_animation_manager.get_dropdown_state(dropdown_id);

        hooks::draw_text(canvas, font, label, { 0.9f, 0.9f, 0.9f, 1.0f }, pos);
        pos.y += 15.0f;

        bool main_hovered = (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + height);

        draw_modern_rect(canvas, pos.x, pos.y, width, height,
            main_hovered ? hover_bg : bg);

        hooks::draw_text(canvas, font, items[current_index], { 0.9f, 0.9f, 0.9f, 1.0f },
            { pos.x + 10.0f, pos.y + 8.0f });

        const wchar_t* arrow = state.is_open ? L"▼" : L"▲";
        hooks::draw_text(canvas, font, arrow, accent,
            { pos.x + width - 20.0f, pos.y + 8.0f });

        if (main_hovered && clicked) {
            state.is_open = !state.is_open;
        }

        if (state.is_open) {
            for (int i = 0; i < item_count; i++) {
                if (i == current_index) continue;

                float item_y = pos.y + height + (i * height);
                bool item_hovered = (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + width &&
                    mouse_pos.y >= item_y && mouse_pos.y <= item_y + height);

                draw_modern_rect(canvas, pos.x, item_y, width, height,
                    item_hovered ? hover_bg : bg);
                hooks::draw_text(canvas, font, items[i], { 0.9f, 0.9f, 0.9f, 1.0f },
                    { pos.x + 10.0f, item_y + 8.0f });

                if (item_hovered && clicked) {
                    current_index = i;
                    state.is_open = false;
                }
            }
        }
    }
    void draw_circle(ucanvas* canvas, float centerX, float centerY, float radius, int segments, flinearcolor color, float thickness) {
        float angleStep = (2.0f * M_PI) / segments;

        for (int i = 0; i < segments; i++) {
            float theta1 = i * angleStep;
            float theta2 = (i + 1) * angleStep;

            float x1 = centerX + cosf(theta1) * radius;
            float y1 = centerY + sinf(theta1) * radius;
            float x2 = centerX + cosf(theta2) * radius;
            float y2 = centerY + sinf(theta2) * radius;

            canvas->k2_drawline({ x1, y1 }, { x2, y2 }, thickness, color);
        }
    }

    void draw_filled_circle(ucanvas* canvas, float centerX, float centerY, float radius, int segments, flinearcolor color) {
        float angleStep = (2.0f * M_PI) / segments;

        for (int i = 0; i < segments; i++) {
            float theta = i * angleStep;

            float x = centerX + cosf(theta) * radius;
            float y = centerY + sinf(theta) * radius;

            // Draw radial lines from center outward
            canvas->k2_drawline({ centerX, centerY }, { x, y }, 1.0f, color);
        }
    }


    float draw_oq_slider(ucanvas* canvas, uobject* font, const wchar_t* label, float value, float min_value, float max_value, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked, bool& dragging) {
        
        const float width = 200.0f;
        const float height = 6.0f;
        static const flinearcolor bg = { 0.04f, 0.04f, 0.04f, 1.0f };
        static const flinearcolor accent = { 0.5f, 0.0f, 1.0f, 1.0f };
        static const flinearcolor handle_color = { 0.7f, 0.7f, 0.7f, 1.0f };
        static const flinearcolor value_text_color = { 0.9f, 0.9f, 0.9f, 1.0f };

        wchar_t value_text[32];
        swprintf_s(value_text, L"%.1f", value);
        hooks::draw_text(canvas, font, label, { 0.9f, 0.9f, 0.9f, 1.0f }, pos);
        hooks::draw_text(canvas, font, value_text, value_text_color,
            { pos.x + width - 40.0f, pos.y });

        pos.y += 15.0f;

        float normalized = (value - min_value) / (max_value - min_value);

        draw_modern_rect(canvas, pos.x, pos.y, width, height, bg);
        draw_modern_rect(canvas, pos.x, pos.y, width * normalized, height, accent);

        const float handle_size = 12.0f;
        float handle_x = pos.x + (width * normalized) - (handle_size / 2);
        float handle_y = pos.y + (height / 2) - (handle_size / 2);
        draw_modern_rect(canvas, handle_x, handle_y, handle_size, handle_size, handle_color);

        bool handle_hovered = (mouse_pos.x >= handle_x && mouse_pos.x <= handle_x + handle_size &&
            mouse_pos.y >= handle_y && mouse_pos.y <= handle_y + handle_size);

        if (handle_hovered && mouse_clicked) {
            dragging = true;
        }

        if (dragging) {
            if (mouse_clicked) {
                normalized = (mouse_pos.x - pos.x) / width;
                normalized = (std::max)(0.0f, (std::min)(1.0f, normalized));
                return min_value + normalized * (max_value - min_value);
            }
            dragging = false;
        }

        return value;
    }

    // particles
    struct particle {
        fvector2d pos;
        fvector2d vel;
        float life;
        float size;
        flinearcolor color;
    };
    struct logo_state {
        std::vector<particle> particles;
        fvector2d last_pos;
        float animation_time = 0.0f;
    } g_logo_state;
    void update_particles(logo_state& state, float delta_time, fvector2d current_pos) {
        
        if (state.particles.size() < 50) {
            particle new_particle;
            new_particle.pos = current_pos;
            new_particle.vel = {
                (float)(rand() % 100 - 50) / 50.0f,
                (float)(rand() % 100) / 50.0f
            };
            new_particle.life = 1.0f;
            new_particle.size = 5.0f + (rand() % 5);
            new_particle.color = { 1.0f, 0.5f, 0.1f, 1.0f };
            state.particles.push_back(new_particle);
        }

        for (auto& p : state.particles) {
            p.pos.x += p.vel.x * delta_time * 60.0f;
            p.pos.y += p.vel.y * delta_time * 60.0f;
            p.life -= delta_time * 2.0f;
            p.color.a = p.life;
        }

        state.particles.erase(
            std::remove_if(state.particles.begin(), state.particles.end(),
                [](const particle& p) { return p.life <= 0; }),
            state.particles.end()
        );

        state.last_pos = current_pos;
    }

    auto calculate_box_dimensions = [](fvector2d head_long_out, fvector2d base_out) -> std::pair<float, float> {

        float box_height = abs(head_long_out.y - base_out.y);
        float box_width = box_height * 0.55f;
        return { box_width, box_height };
        };


    flinearcolor hsv_to_rgb(float h, float s = 1.f, float v = 1.f)
    {
        float c = v * s;
        float x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
        float m = v - c;

        float r, g, b;
        if (h < 60) { r = c; g = x; b = 0; }
        else if (h < 120) { r = x; g = c; b = 0; }
        else if (h < 180) { r = 0; g = c; b = x; }
        else if (h < 240) { r = 0; g = x; b = c; }
        else if (h < 300) { r = x; g = 0; b = c; }
        else { r = c; g = 0; b = x; }

        return { r + m, g + m, b + m, 1.f };
    }


    bool is_sniper_weapon(const fstring& weapon_name) {
        return
            weapon_name.wide() == L"Operator" ||
            weapon_name.wide() == L"Marshal" ||
            weapon_name.wide() == L"Outlaw";
    }


    std::string GetEquippableVFXState(EAresEquippableState STATE) {

        switch (STATE) {
        case EAresEquippableState::Reloading:
            return crypt("Reloading..").decrypt();
            break;
        case EAresEquippableState::Inspecting:
            return crypt("Inspecting").decrypt();
            break;
        case EAresEquippableState::Firing:
            return crypt("Shooting").decrypt();
            break;
        case EAresEquippableState::ADS_Firing:
            return crypt("ADS_Firing").decrypt();
            break;
        case EAresEquippableState::Attacking:
            return crypt("Attacking").decrypt();
            break;
        default:
            return crypt("No Action").decrypt();
        }
    }



    std::array<int, 256> aim_names = {
VK_LBUTTON,
VK_RBUTTON,
VK_MBUTTON,
VK_XBUTTON1,
VK_XBUTTON2,

'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,

VK_UP,
VK_DOWN,
VK_LEFT,
VK_RIGHT,

VK_SHIFT,
VK_LSHIFT,
VK_RSHIFT,
VK_CONTROL,
VK_LCONTROL,
VK_RCONTROL,
VK_MENU,
VK_LMENU,
VK_RMENU,
VK_CAPITAL,
VK_TAB,
VK_RETURN,
VK_BACK,
VK_ESCAPE,
VK_SPACE,

VK_OEM_1,
VK_OEM_PLUS,
VK_OEM_COMMA,
VK_OEM_MINUS,
VK_OEM_PERIOD,
VK_OEM_2,
VK_OEM_3,
VK_OEM_4,
VK_OEM_5,
VK_OEM_6,
VK_OEM_7,

VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4,
VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
VK_MULTIPLY, VK_ADD, VK_SEPARATOR, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE,

VK_INSERT, VK_DELETE, VK_HOME, VK_END, VK_PRIOR, VK_NEXT,
VK_PAUSE, VK_SCROLL,
    };

    void DrawTextRGBWithFString(uobject* font, ucanvas* canvas, fstring text, float x, float y, flinearcolor color, bool CenterX = 0)
    {
        
        canvas->k2_drawtext(font, text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, CenterX, 0, 1, { 0, 0, 0, 1 });
    }

    bool ToBool(const std::string& s) {
        return s == "1" || s == "true";
    }

    int ToInt(const std::string& s) {
        try { return std::stoi(s); }
        catch (...) { return 0; }
    }

    float ToFloat(const std::string& s) {
        try { return std::stof(s); }
        catch (...) { return 0.f; }
    }

    std::unordered_map<std::string, std::string> ParseSection(std::ifstream& file) {
        std::unordered_map<std::string, std::string> values;
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '[') {
                // next section or empty line means section ended
                if (!line.empty()) file.seekg(-static_cast<int>(line.size()) - 1, std::ios_base::cur); // rewind one line
                break;
            }
            auto pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string val = line.substr(pos + 1);
                values[key] = val;
            }
        }
        return values;
    }

    static fvector2d pos;
    static bool initialized = false;

    fvector2d menuSize = { 560, 400 };
   
    void RenderWatermark(ucanvas* canvas) {
        if (!canvas) return;
        

        static int fps = 0;
        static int frameCount = 0;
        static auto lastTime = std::chrono::steady_clock::now();
        frameCount++;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
        if (elapsed >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastTime = currentTime;
        }


        int tickrate = 128;

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_time;
        localtime_s(&tm_time, &time);
        int hour = tm_time.tm_hour;
        int minute = tm_time.tm_min;
        int second = tm_time.tm_sec;
        const wchar_t* period = hour >= 12 ? L"PM" : L"AM";
        if (hour > 12) hour -= 12;
        if (hour == 0) hour = 12;
        int day = tm_time.tm_mday;
        int month = tm_time.tm_mon + 1;

        // ===== BUILD TEXT =====
        wchar_t line1[256];
        wchar_t line2[256];

        swprintf_s(line1, L"Lubov Evgenievna Unlock All  %02d/%02d", month, day);
        swprintf_s(line2, L"FPS | %d  TICK | %d  %02d:%02d:%02d %s",
            fps, tickrate, hour, minute, second, period);

        // ===== COLORS =====
        flinearcolor titleColor = { 0.0f, 0.59f, 1.0f, 1.0f };        // Blue
        flinearcolor whiteColor = { 1.0f, 1.0f, 1.0f, 1.0f };         // White
        flinearcolor shadowColor = { 0.0f, 0.0f, 0.0f, 0.0f };        // No shadow

        // ===== POSITION =====
        fvector2d pos(50.0f, 80.0f);
        fvector2d normalScale(1.0f, 1.0f);
        fvector2d normalScale2(1.1f, 1.1f);
        fvector2d noOffset(0.0f, 0.0f);

        // ===== DRAW LINE 1 - FAT TITLE =====
        // Draw multiple times with tiny offsets to make it THICK
        fvector2d offsets[4] = {
            { 1.0f, 0.0f },  // right
            { -1.0f, 0.0f }, // left
            { 0.0f, 1.0f },  // down
            { 0.0f, -1.0f }  // up
        };

    
        // Draw the main one on top
        canvas->k2_drawtext(
            menu::font,
            fstring(line1),
            pos,
            normalScale2,
            whiteColor,
            0.0f,
            shadowColor,
            noOffset,
            false, false, false,
            shadowColor
        );

        // ===== DRAW LINE 2 - REGULAR =====
        fvector2d pos2(pos.x, pos.y + 30.0f);

        canvas->k2_drawtext(
            menu::font,
            fstring(line2),
            pos2,
            normalScale,
            whiteColor,
            0.0f,
            shadowColor,
            noOffset,
            false, false, false,
            shadowColor
        );
    }


    void RenderWatermark2(ucanvas* canvas) {
        if (!canvas) return;


        static int fps = 0;
        static int frameCount = 0;
        static auto lastTime = std::chrono::steady_clock::now();
        frameCount++;
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();
        if (elapsed >= 1000) {
            fps = frameCount;
            frameCount = 0;
            lastTime = currentTime;
        }


        int tickrate = 128;

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_time;
        localtime_s(&tm_time, &time);
        int hour = tm_time.tm_hour;
        int minute = tm_time.tm_min;
        int second = tm_time.tm_sec;
        const wchar_t* period = hour >= 12 ? L"PM" : L"AM";
        if (hour > 12) hour -= 12;
        if (hour == 0) hour = 12;
        int day = tm_time.tm_mday;
        int month = tm_time.tm_mon + 1;

        // ===== BUILD TEXT =====
        wchar_t line1[256];
        wchar_t line2[2048];

        swprintf_s(line1, L"Who is Lubov Evgenievna?");
        swprintf_s(line2, L"Yumshanova Lubov Evgenievna (born in 27.11.1998) is the legendary Goddess of History, Supreme Queen of Knowledge, and Eternal Guardian of Ancient Civilizations.\n Revered for her wisdom, elegance, and unmatched authority in the classroom, she began her reign as a history teacher in the early 2018s and quickly became known for her powerful presence and intellectual brilliance.\n Students describe her as a majestic ruler of timelines, capable of bringing empires, wars, and forgotten centuries back to life through her teaching.\n Known among her followers as The Queen of Historical Truth, Lubov Evgenievna possesses an extraordinary ability to command attention and inspire respect.\n Her lectures are said to rival the speeches of great rulers, while her knowledge of world history is considered vast enough to rival entire royal libraries.\n Throughout her career, she has maintained her status as an icon of grace, discipline, and wisdom.");


        // ===== COLORS =====
        flinearcolor titleColor = { 0.0f, 0.59f, 1.0f, 1.0f };        // Blue
        flinearcolor whiteColor = { 1.0f, 1.0f, 1.0f, 1.0f };         // White
        flinearcolor shadowColor = { 0.0f, 0.0f, 0.0f, 0.0f };        // No shadow

        // ===== POSITION =====
        fvector2d pos(50.0f, 150.0f);
        fvector2d normalScale(1.0f, 1.0f);
        fvector2d normalScale2(1.1f, 1.1f);
        fvector2d noOffset(0.0f, 0.0f);

        // ===== DRAW LINE 1 - FAT TITLE =====
        // Draw multiple times with tiny offsets to make it THICK
        fvector2d offsets[4] = {
            { 1.0f, 0.0f },  // right
            { -1.0f, 0.0f }, // left
            { 0.0f, 1.0f },  // down
            { 0.0f, -1.0f }  // up
        };


        // Draw the main one on top
        canvas->k2_drawtext(
            menu::font,
            fstring(line1),
            pos,
            normalScale2,
            whiteColor,
            0.0f,
            shadowColor,
            noOffset,
            false, false, false,
            shadowColor
        );

        // ===== DRAW LINE 2 - REGULAR =====
        fvector2d pos2(pos.x, pos.y + 30.0f);

        canvas->k2_drawtext(
            menu::font,
            fstring(line2),
            pos2,
            normalScale,
            whiteColor,
            0.0f,
            shadowColor,
            noOffset,
            false, false, false,
            shadowColor
        );
    }


    void hk_draw_canvas(ucanvas* canvas) {
        
        menu::SetupCanvas(canvas);
        inpute::handle();

        if (!globals::misc::hide_watermark) {
            RenderWatermark(canvas);
        }

        if (!globals::misc::hide_lubov_evgenievna) {
            RenderWatermark2(canvas);
		}
 
        if (GetAsyncKeyState(globals::misc::MenuKey) & 1)
            open_canvas = !open_canvas;


        static fvector2d pos{};
        static fvector2d menuSize = { 560, 400 };
        static bool initialized = false;

        if (!initialized) {
            pos.x = (canvas->get_screen_size().x - menuSize.x) / 2.0f;
            pos.y = (canvas->get_screen_size().y - menuSize.y) / 2.0f;
            initialized = true;
        }

        if (menu::Window(crypt(L"Lubov Evgenievna Unlock All").decrypt(), crypt(L"Build:").decrypt(), ShooterGameBlueprints::GetValVersion(), &pos, menuSize, open_canvas)) {
            static int tab = 0;
            menu::offset_x = 220;
            if (menu::ButtonTab(crypt(L"Misc").decrypt(), fvector2d(45, 18), tab == 2)) tab = 2;

            menu::offset_x = 0;
            menu::SameLine();
            if (menu::ButtonTab(crypt(L"Config").decrypt(), fvector2d(45, 18), tab == 3)) tab = 3;

            menu::offset_x = 23;
            menu::offset_y = 43;

            if (tab == 0) {
                static int tab2 = 0;

                if (tab2 != 0) {
                    menu::offset_y -= 25;
                }
                if (tab2 != 1) {

                    menu::offset_y -= 25;
                }

                float saved_offset_y = menu::offset_y;

                if (tab2 == 0) { // aim
                  
                    menu::offset_x -= 12;


                    menu::offset_x -= menu::offset_tab2;
                }
                else if (tab2 == 1) { // exploits

                    menu::offset_x -= menu::offset_tab2;
                }   
            }

            if (tab == 1) {

                static int tab2 = 2;
                //if (menu::ButtonSection(crypt(L"Buddy Changer").decrypt(), fvector2d(104, 20), tab2 == 8)) tab2 = 8;

                if (tab2 != 2) {

                    menu::offset_y -= 25;
                }
                if (tab2 != 3) {

                    menu::offset_y -= 25;
                }

                if (tab2 != 4) {

                    menu::offset_y -= 25;
                }

                if (tab2 != 5) {

                    menu::offset_y -= 25;
                }
                if (tab2 != 6) {
                    menu::offset_y -= 25;
                }
                if (tab2 != 7) {
                    menu::offset_y -= 25;
                }

                if (tab2 != 8) {
                    menu::offset_y -= 25;
                }

                float saved_offset_y = menu::offset_y;
                if (tab2 == 2) {
                    menu::offset_x -= menu::offset_tab2;
                }
                else if (tab2 == 3) {
                    menu::offset_x -= menu::offset_tab1;
                    menu::offset_x -= menu::offset_tab2;
                }
                else if (tab2 == 4)
                {

                    menu::offset_x -= menu::offset_tab2;
                }
                else if (tab2 == 5) {
                    menu::offset_x -= menu::offset_tab2;
                }
                else if (tab2 == 6) {

                    menu::offset_x -= menu::offset_tab2;

                }
                else if (tab2 == 7) {

                    ResetOffset();
                    menu::offset_y = saved_offset_y;
                    menu::offset_x += menu::offset_tab1;

                    menu::offset_x -= menu::offset_tab2;
                }

            }
            if (tab == 2) {
                static int tab2 = 4;

                if (tab2 != 4) {
                    menu::offset_y -= 25;
                }
                if (tab2 != 5) {
                    menu::offset_y -= 25;
                }

                if (tab2 != 6) {
                    menu::offset_y -= 25;
                }

                if (tab2 != 7) {
                    menu::offset_y -= 25;
                }

                if (tab2 != 8) {
                    menu::offset_y -= 25;
                }

                if (tab2 != 9) {
                    menu::offset_y -= 25;
                }


                float saved_offset_y = menu::offset_y;

                if (tab2 == 4) {
                    // 1. Draw Section Headers
                    menu::offset_x = 141; menu::offset_y = 36;
                    menu::SectionWrapper(crypt(L"Main").decrypt(), fvector2d(197, 28));

                    menu::offset_x = 347; menu::offset_y = 36;
                    menu::SectionWrapper(crypt(L"Others").decrypt(), fvector2d(197, 28));

                    // 2. Reset and Position for Content (Left Section)
                    ResetOffset();
                    menu::offset_x = 141 + 10; // Start inside the "Main" box with 10px padding
                    menu::offset_y = 36 + 35;  // Start below the "Main" header

                    menu::Checkbox(crypt(L"Skip Tutorial").decrypt(), &globals::misc::skiptutorial);
                    menu::Checkbox(crypt(L"Unlock All (Skins)").decrypt(), &globals::misc::skin_changer);
                    menu::Checkbox(crypt(L"Play Finisher").decrypt(), &globals::misc::finisher);
                    menu::Checkbox(crypt(L"Only Last Kill").decrypt(), &globals::misc::onlylastkill);

                    menu::Hotkey(crypt("Menu Keybind").decrypt(), fvector2d{ 75, 25 }, & globals::misc::MenuKey);
                }

                if (tab2 == 5) {
                    // 1. Draw Section Headers
                    menu::offset_x = 141; menu::offset_y = 36;
                    menu::SectionWrapper(crypt(L"Main").decrypt(), fvector2d(197, 28));

                    menu::offset_x = 347; menu::offset_y = 36;
                    menu::SectionWrapper(crypt(L"Others").decrypt(), fvector2d(197, 28));

                    // 2. Position for Content (Left Section)
                    ResetOffset();
                    menu::offset_x = 141 + 10;
                    menu::offset_y = 36 + 35;

                    //menu::Hotkey(crypt("Menu Keybind").decrypt(), fvector2d{ 75, 25 }, &globals::misc::MenuKey);

                    // 3. Position for Content (Right Section)
                    // If you want to put things under "Others", just change the offset_x
                    /*
                    menu::offset_x = 347 + 10;
                    menu::offset_y = 36 + 35;
                    menu::Checkbox(crypt(L"Example").decrypt(), &globals::misc::example);
                    */
                }



                if (tab2 == 6) {
                    menu::offset_x = 141;
                    menu::offset_y = 36;
                    menu::SectionWrapper((L"Main"), fvector2d(197, 28));

                    menu::offset_x = 347;
                    menu::offset_y = 36;
                    menu::SectionWrapper((L"Others"), fvector2d(197, 28));

                    ResetOffset();
                    menu::offset_y = saved_offset_y;
                    menu::offset_x += menu::offset_tab1;


                    menu::offset_x -= menu::offset_tab1;
                    //right side

                    menu::offset_y = saved_offset_y;
                    menu::offset_x += menu::offset_tab2;



                    menu::offset_x -= menu::offset_tab2;
                }
                if (tab2 == 7) {

                    ResetOffset();
                    menu::offset_y = saved_offset_y;
                    menu::offset_x += menu::offset_tab1;

                    menu::offset_x -= menu::offset_tab2;

                }

                if (tab2 == 8) {
                    // top tabs

              
                    
                    menu::offset_x -= menu::offset_tab2;

                }


            }
            if (tab == 3) {
                static int tab2 = 8;
                if (menu::ButtonSection(crypt(L"Config").decrypt(), fvector2d(104, 20), tab2 == 8)) tab2 = 8;

                if (tab2 != 8) {
                    menu::offset_y -= 25;
                }

                float saved_offset_y = menu::offset_y;
                if (tab2 == 8) {
                    menu::offset_x = 141;
                    menu::offset_y = 36;
                    menu::SectionWrapper(crypt(L"Config").decrypt(), fvector2d(197, 28));

                    menu::offset_x = 347;
                    menu::offset_y = 36;
                    menu::SectionWrapper(crypt(L"Others").decrypt(), fvector2d(197, 28));

                    ResetOffset();
                    menu::offset_y = saved_offset_y;
                    menu::offset_x += menu::offset_tab1;

                    // left
                    if (menu::Button(crypt(L"Load Config").decrypt(), fvector2d(100, 24))) {
                        load_config();
                    }

                    if (menu::Button(crypt(L"Save Config").decrypt(), fvector2d(100, 24))) {
                        save_config();
                    }

                    menu::offset_x -= menu::offset_tab1;

                    // right
                    menu::offset_y = saved_offset_y;
                    menu::offset_x += menu::offset_tab2;
                    
                    menu::Checkbox(crypt(L"Hide Watermark").decrypt(), &globals::misc::hide_watermark);
                    menu::Checkbox(crypt(L"Hide Lubov Evgenievna").decrypt(), &globals::misc::hide_lubov_evgenievna);

                    menu::offset_x -= menu::offset_tab2;

                }
            }
        }

        menu::Render();
        menu::Draw_Cursor(open_canvas);
    }


    flinearcolor GetRainbowColore(float time)
    {

        float red = (sin(time * 2.0f * 3.14159f / 3.0f) + 1.0f) / 2.0f;
        float green = (sin(time * 2.0f * 3.14159f / 3.0f + 2.0f * 3.14159f / 3.0f) + 1.0f) / 2.0f;
        float blue = (sin(time * 2.0f * 3.14159f / 3.0f + 4.0f * 3.14159f / 3.0f) + 1.0f) / 2.0f;
        return flinearcolor(red, green, blue, globals::misc::glow_float);
    }

    auto isVisible(uskeletalmeshcomponent* mesh) -> bool {
        double fLastSubmitTime = *reinterpret_cast<double*>(mesh + offsets::last_submit_time);
        double fLastRenderTimeOnScreen = *reinterpret_cast<double*>(mesh + offsets::last_render_time);

        const double fVisionTick = 0.05f;
        bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;

        return bVisible;
    }


    void hooks::call_drawui(ucanvas* canvas) {
        
        return reinterpret_cast<void(*)(ucanvas * _canvas, uintptr_t, void*)>(spoofcall_stub)(canvas, offsets::MagicOffsets, (void*)hooks::hk_draw_canvas);

    }
    uintptr_t camera_engine;
    uobject* engine_cache;

    bool should_hook;
    ucanvas* canvas;

    auto RelativeLocation(uintptr_t APawn) -> fvector {
        auto RootComponent = memory::read<uintptr_t>(APawn + 0x238);
        return memory::read<fvector>(RootComponent + offsets::root_position);
    }
    std::wstring gen_random_name() {
        const std::wstring chars = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        std::wstring randomName;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, chars.size() - 1);

        for (int i = 0; i < 8; ++i) {
            randomName += chars[dist(gen)];
        }
        return randomName;
    }
    DWORD GGameThreadId = 0;
    using draw_t = void(*)(ugameviewportclient*, ucanvas* canvas, std::uintptr_t a3);
    draw_t original_draw;

    inline void ApplyWireframe(void* meshPtr)
    {
        if (!meshPtr)
            return;

        constexpr uint8_t WireframeFlag = 1 << 5;
        auto flagAddr = reinterpret_cast<uint8_t*>((uintptr_t)meshPtr + offsets::WireFrame);

        if (!flagAddr)
            return;

        bool alreadyApplied = (*flagAddr & WireframeFlag) != 0;
        if (alreadyApplied)
            return;

        auto meshOverlay = memory::read<uintptr_t>((uintptr_t)meshPtr + offsets::WireFrame);
        if (!meshOverlay)
            return;

        *flagAddr |= WireframeFlag;
        *reinterpret_cast<uint8_t*>((uintptr_t)meshPtr + offsets::WireFrame2) = 0xFF;
    }


    int index = 453;
    bool InGame = 0;
    

    void hooks::hk_draw_transition(ugameviewportclient* viewportclient, std::uintptr_t a2, std::uint64_t a3) {


        if (!canvas)
            canvas = uobject::find_object<ucanvas*>(crypt(L"/Engine/Transient.DebugCanvasObject").decrypt(), (uobject*)-1);

        if (!viewportclient || !memory::is_valid((uintptr_t)viewportclient))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        hooks::hk_draw_canvas(canvas);

        uworld* world = memory::read<uworld*>((uintptr_t)viewportclient + offsets::viewport_world);
        if (!world || !memory::is_valid((uintptr_t)world))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        UWorldSave = world;

        float closest_distance = FLT_MAX;
        int target_id = -1;

        static uintptr_t old_pawn = 0;
        static uintptr_t old_controller = 0;
        static uintptr_t old_world = 0;
        static uintptr_t old_character = 0;

        if ((uintptr_t)world != old_world) {
            old_world = (uintptr_t)world;
            old_pawn = 0;
            old_controller = 0;
            old_character = 0;
            cache::players.clear();
        }

        ugameinstance* gameinstance = viewportclient->get_gameinstance();
        if (!gameinstance || !memory::is_valid((uintptr_t)gameinstance))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        uengine* uengine = gameinstance->get_uengine();
        if (!uengine || !memory::is_valid((uintptr_t)uengine))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        controller = blueprints::get_player_controller(world);
        if (!controller || !memory::is_valid((uintptr_t)controller))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        if ((uintptr_t)controller != old_controller) {
            old_controller = (uintptr_t)controller;
            cache::players.clear();
        }

        camera = controller->get_camera_manager();
        if (!camera || !memory::is_valid((uintptr_t)camera))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        camera_cache = camera;

        if (!globals::il::init) {
            SLIGHTSONTOP1::insta_lock_agents::run();
            globals::il::init = true;
        }

        if (globals::misc::skin_changer) {
            skin_changer::unlock_all_skins(world);
        }

        pawn = controller->K2_GetPawn_Local();
        if (!pawn || !memory::is_valid((uintptr_t)pawn))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        ashootercharacter* new_character = controller->get_shooter_character();
        if (new_character && (uintptr_t)new_character != old_character) {
            old_character = (uintptr_t)new_character;
            cache::players.clear();
        }

        character = new_character;
        if (!character || !memory::is_valid((uintptr_t)character))
            return hooks::draw_transition_o(viewportclient, a2, a3);

        if ((uintptr_t)pawn != old_pawn) {
            old_pawn = (uintptr_t)pawn;
            cache::players.clear();
        }

        if (globals::il::enable) {
            SLIGHTSONTOP1::insta_lock::run(controller);
        }

        if (pawn != nullptr) {
            myweapon = character->get_inventory()->get_current_equippable();
            if (globals::misc::skin_changer && myweapon != nullptr && myweapon != lastweapon)
            {
                uinventory* inventory = character->get_inventory();
                if (inventory)
                {
                    currentequippable* equippable = inventory->get_current_equippable();
                    if (equippable)
                    {
                        equippable_skin_data_asset* skin_data_asset = equippable->get_skin_data_asset();
                        if (skin_data_asset)
                        {
                            int32_t type = skin_data_asset->get_type();
                            if (type != 0)
                            {
                                arsenal_view_controller* arsenal_view_controller = ares_instance::get_ares_client_game_instance(world)->get_aresnal_view_controller();
                                if (arsenal_view_controller)
                                {
                                    arsenal_view_model* arsenal_view_model = arsenal_view_controller->get_view_model();
                                    if (arsenal_view_model)
                                    {
                                        auto models = arsenal_view_model->get_gun_models();
                                        for (int i = 0; i < models.count; i++) {
                                            equippable_inventory_model* model = models[i];
                                            if (!model)
                                                continue;

                                            equippable_skin_inventory_model* skin_model = model->get_equipped_skin_model();
                                            if (!skin_model)
                                                continue;

                                            equippable_skin_data_asset* skin_data = skin_model->get_skin_data_asset();
                                            if (!skin_data || skin_data->get_type() != type) continue;

                                            const std::wstring& wname = get_skin_name_cached(skin_data);
                                            store_skin_by_name(wname);

                                            int32_t skin_data_type = skin_data->get_type();
                                            if (skin_data_type != type)
                                                continue;

                                            int max_level = skin_data->get_skin_levels().size();
                                            uobject* skin_chroma_asset = skin_model->get_skin_inventory_chroma_asset()->get_skin_chroma_data_asset(); if (!skin_chroma_asset) continue;
                                            skin_changer::unlock_all_apply(world, equippable, skin_data, skin_chroma_asset, max_level, nullptr, -1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                lastweapon = character->get_inventory()->get_current_equippable();
            }
        }

        fvector2d screen_size = canvas->get_screen_size();
        if (!screen_size.is_valid())
            return hooks::draw_transition_o(viewportclient, a2, a3);

        tarray<ashootercharacter*> actors = blueprints::find_all_shooters_with_alliance(world, character, earesalliance::any, false, true);
        if (!actors.data || actors.size() == 0)
            return hooks::draw_transition_o(viewportclient, a2, a3);

        if (globals::misc::skiptutorial) {
            controller->disconnect_server();
            globals::misc::skiptutorial = false;
        }
    }

    
    void niggarito(uint8_t* module_, uint32_t max_fakestack = 12) {
        return reinterpret_cast<void(*)(uint8_t * module_, uint32_t max_fakestack, uintptr_t, void*)>(spoofcall_stub)(module_, max_fakestack, offsets::MagicOffsets, (void*)initialize_spoofcall);

    }

    void call_draw_transition_hook1(ugameviewportclient* viewportclient, ucanvas* canvas, std::uint64_t a3) {
        return reinterpret_cast<void(*)(ugameviewportclient * viewportclient, ucanvas * canvas, std::uint64_t a3, uintptr_t, void*)>(spoofcall_stub)(viewportclient, canvas, a3, offsets::MagicOffsets, (void*)hooks::hk_draw_transition);
    }

    struct State {
        uintptr_t keys[7];
    };

    struct engine_cache_t
    {
        uworld* world{};
        ugameinstance* gameinstance{};
        ulocalplayer* localplayer{};
        aplayercontroller* controller{};
        ugameviewportclient* viewport{};
        uobject* gameview{};
        uintptr_t             engine{};
    };

    static engine_cache_t g_cache{};
    static bool g_keys_init = false;

    __forceinline bool is_valid_engine_state()
    {
        return g_cache.world &&
            g_cache.gameinstance &&
            g_cache.localplayer &&
            g_cache.controller &&
            g_cache.viewport &&
            g_cache.gameview;


    };
    PVOID create_jmp_hook(void* function)
    {
        PVOID page1 = VirtualAlloc(0, 0x10ui64, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        uint8_t jmp64[] =
        {
            0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        };

        *(PVOID*)(jmp64 + 6) = function;

        memcpy(page1, jmp64, sizeof(jmp64));

        DWORD old;
        VirtualProtect(page1, 0x10, PAGE_EXECUTE_READ, &old);

        return page1;
    }


    void hooks::q9F_init()
    {
        

        static bool q9F_keys = false;

        static uworld* q9F_w = nullptr;
        static ugameinstance* q9F_gi = nullptr;
        static ulocalplayer* q9F_lp = nullptr;
        static aplayercontroller* q9F_pc = nullptr;
        static ugameviewportclient* q9F_vp = nullptr;
        static uobject* q9F_gv = nullptr;
        static uintptr_t            q9F_eng = 0;

        variables.init_variables();

        if (!q9F_w)
        {

            uintptr_t* p =
                *reinterpret_cast<uintptr_t**>(
                    memory::module_base + DecryptOffsetClear(offsets::State));

            if (!p)
                return;

            q9F_w = *reinterpret_cast<uworld**>(p);
            if (!q9F_w)
                return;
        }

        if (!q9F_gi)
        {
            q9F_gi = memory::read<ugameinstance*>(
                uintptr_t(q9F_w) + offsets::game_instance);

            if (!q9F_gi)
                return;

            q9F_eng = memory::read<uintptr_t>(
                uintptr_t(q9F_gi) + offsets::Engine);

           
        }

        if (!q9F_lp)
        {
            ulocalplayer* x = memory::read<ulocalplayer*>(
                uintptr_t(q9F_gi) + offsets::local_players);

            if (!x)
                return;


 
            q9F_lp = memory::read< ulocalplayer*>((uintptr_t)x);

        }

        if (!q9F_pc)
        {
            q9F_pc = memory::read<aplayercontroller*>(
                uintptr_t(q9F_lp) + offsets::LocalController);

            if (!q9F_pc)
                return;
        }

        aplayercameramanager* camera = memory::read<aplayercameramanager*>((uintptr_t)q9F_pc + offsets::cameramaneger);
        if (!q9F_vp)
        {
            q9F_vp = q9F_lp->viewport_client();
            if (!q9F_vp)
                return;
        }

        if (!q9F_gv)
        {
            q9F_gv = memory::read<uobject*>(
                uintptr_t(q9F_vp) + 0xF0);

            if (!q9F_gv)
                return;
        }

        if (!q9F_keys)
        {
            keys::space = (string::string_to_name)(crypt(L"SpaceBar").decrypt());
            keys::left_mouse = (string::string_to_name)(crypt(L"LeftMouseButton").decrypt());
            keys::w = (string::string_to_name)(crypt(L"W").decrypt());
            keys::a = (string::string_to_name)(crypt(L"A").decrypt());
            keys::s = (string::string_to_name)(crypt(L"S").decrypt());
            keys::d = (string::string_to_name)(crypt(L"D").decrypt());

            auto enc_5 = Encrypt(L"LeftAlt");
            keys::left_alt = string::string_to_name(enc_5.decrypt()), enc_5.encrypt();

            q9F_keys = true;
        }

        if (!engine_cache)
            engine_cache = memory::read<uobject*>(
                uintptr_t(q9F_gi) + 0x28);

        if (!menu::font)
            menu::font = memory::read<uobject*>(
                q9F_eng + offsets::UworldShit);

        hooks::viewport_shadow.virtual_hook((void*)q9F_vp, hooks::hk_draw_transition, offsets::post_render, (void**)&hooks::draw_transition_o);

    }
};

