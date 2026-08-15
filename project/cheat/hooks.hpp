#pragma once
#include "functions.hpp"
#include "../sdk/shadow_vmt.hpp"
#include "../encrypt/importer.hpp"
#include <array>
#include <string>

bool vgknohack;



namespace defines {
    static flinearcolor health_color;
    static flinearcolor high_health = { 0.0f,255.0f,0.0f,1.0f };
    static flinearcolor normal_health = { 255, 151, 0 ,1.0f };
    static flinearcolor low_heath = { 255.0f,0.0f,0.f,1.0f };
    static flinearcolor blackcolor_1 = { 0.5f, 0.5f, 0.5f, 1.0f };
    static flinearcolor visuals_color = { 255.0f,255.0f,255.0f,1.0f };
}
typedef unsigned char   uint8;


struct ABP_Sky_Sphere_C {
    uintptr_t* Sky_Sphere_mesh; // 0x3B8
    USceneComponentHelpers* Base; // 0x3C0
    UMaterialInstanceDynamic* Sky_material; // 0x3C8
    bool Refresh_material; // 0x3D0
    uint8_t pad_3D1[0x7];
    uobject* Directional_light_actor; // 0x3D8
    bool Colors_determined_by_sun_position; // 0x3E0
    uint8_t pad_3E1[0x3];
    float Sun_height; // 0x3E4
    float Sun_brightness; // 0x3E8
    float Horizon_Falloff; // 0x3EC
    flinearcolor Zenith_Color; // 0x3F0
    flinearcolor Horizon_color; // 0x400
    flinearcolor Cloud_color; // 0x410
    flinearcolor Overall_Color; // 0x420
    float Cloud_speed; // 0x430
    float Cloud_opacity; // 0x434
    float Stars_brightness; // 0x438
    uint8_t pad_43C[0x4];
    uobject* Horizon_color_curve; // 0x440
    uobject* Zenith_color_curve;  // 0x448
    uobject* Cloud_color_curve;   // 0x450
};
static fstring get_class_name(uobject* object) {
    if (!object) return {};

    // UClass is at offset 0x10 in UObject
    uobject* clazz = memory::read<uobject*>((uintptr_t)object + 0x10);
    if (!clazz) return {};

    return system::get_object_name(clazz);
}

ashootercharacter* publicact;
struct FTViewTarget
{
    acknowledgedpawn* Target;
    FMinimalViewInfo POV;
    aplayerstate* PlayerState;
};

namespace enums
{
    enum class ecachedteamcolor : uint8_t {
        cachedteamcolor_invalid = 0,
        cachedteamcolor_friendly = 1,
        cachedteamcolor_enemy = 2,
        cachedteamcolor_absolute = 3,
        cachedteamcolor_max = 4
    };

    enum class earesoutlinemode : uint8_t {
        none = 0,
        outline = 1,
        block = 2,
        enemy = 3,
        alwaysoutline = 4,
        alwaysenemy = 5,
        earesoutlinemode_max = 6
    };
} using namespace enums;

namespace hooks
{
    uworld* UWorldClass;
    using draw_transition = void(*)(ugameviewportclient* viewportclient, std::uintptr_t a2, std::uint64_t a3);
    inline draw_transition draw_transition_o = 0;
    void(__fastcall* oHkDeath)(void*, void*);
    static shadow_vmt draw_transition_vmt;
    static inline SLIGHTS::vmt::shadow shadowViewport;
 
    void call_drawui(ucanvas* canvas);

    void hk_draw_transition(ugameviewportclient* viewportclient, std::uintptr_t a2, std::uint64_t a3);

    auto SetCameraCachePOVHook(uintptr_t PlayerCameraManager, FMinimalViewInfo* ViewInfo);
    void q9F_init();

    void hkProcessEvent(void* class_, uobject* function, void* params, uintptr_t magic, void* original_fn);

    using tProcessEvent = void(*)(void*, uobject*, void*, uintptr_t, void*);
    tProcessEvent oProcessEvent = nullptr;
    void Rehook(uworld* Uworld, aplayercontroller* PlayerController, aplayercameramanager* cameramanager);
    SLIGHTS::vmt::shadow viewport_shadow;
    SLIGHTS::vmt::shadow camera_shadow;
}