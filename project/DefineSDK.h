
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
enum class EAresEquippableState : uint8_t
{
    Unknown = 0,
    Idle = 1,
    Equipping = 2,
    Inspecting = 3,
    Attacking = 4,
    Firing = 5,
    Reloading = 6,
    ADS_Idle = 7,
    ADS_Firing = 8,
    Count = 9,
    EAresEquippableState_MAX = 10,
};

namespace cache {
    std::vector<ashootercharacter*> players;

}

ashootercharacter* character;
currentequippable* myweapon;
currentequippable* lastweapon;

currentequippable* myweapon2;

currentequippable* lastweapon2;

uworld* UWorldSave;

#define READ(type, addr)  *(type*)(addr)
#define WRITE(type, addr, value) *(type*)(addr) = value

constexpr uintptr_t off_bIsFirstPerson = 0x364; 
constexpr uintptr_t off_bOwnerNoSee = 0x382;
constexpr uintptr_t off_bOnlyOwnerSee = 0x382;

bool IsValidUObject(uobject* obj)
{
    if (!obj) return false;
    if (!memory::IsValidPointer((uintptr_t)obj)) return false;


    void* vtable = *(void**)obj;
    return memory::IsValidPointer((uintptr_t)vtable);
}
inline bool IsValidPtr(const void* ptr) {
    if (!ptr) return false;
    if (reinterpret_cast<uintptr_t>(ptr) < 0x10000) return false;
    if (reinterpret_cast<uintptr_t>(ptr) > 0x7FFFFFFEFFFF) return false;

    MEMORY_BASIC_INFORMATION mbi = {};
    if (VirtualQuery(ptr, &mbi, sizeof(mbi)) == 0) return false;

    if (mbi.State != MEM_COMMIT) return false;
    if (mbi.Protect == PAGE_NOACCESS) return false;
    if (mbi.Protect & PAGE_GUARD) return false;

    return true;
}



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



struct MeshData {
    tarray<fvector> Vertices;
    tarray<int32_t> Triangles;
    tarray<fvector> Normals;
    tarray<fvector2d> UV0;
    tarray<FColor> VertexColors;
    tarray<FProcMeshTangent> Tangents;
};
MeshData ParseOBJFile(const char* filepath) {
    MeshData data;

    std::ifstream file(filepath);
    if (!file.is_open()) {
        //printf("[-] Failed to open OBJ file: %s\n", filepath);
        return data;
    }

    std::vector<fvector> temp_vertices;
    std::vector<fvector2d> temp_uvs;
    std::vector<fvector> temp_normals;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            // Vertex position
            float x, y, z;
            iss >> x >> y >> z;
            temp_vertices.push_back(fvector(x * 100.0f, y * 100.0f, z * 100.0f)); // Scale to UE units
        }
        else if (type == "vt") {
            // UV coordinate
            float u, v;
            iss >> u >> v;
            temp_uvs.push_back(fvector2d(u, 1.0f - v)); // Flip V for UE
        }
        else if (type == "vn") {
            // Normal
            float x, y, z;
            iss >> x >> y >> z;
            temp_normals.push_back(fvector(x, y, z));
        }
        else if (type == "f") {
            // Face (triangle)
            // Format: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
            std::string v1, v2, v3;
            iss >> v1 >> v2 >> v3;

            // Parse indices
            auto parse_face_vertex = [&](const std::string& vert_data) {
                std::istringstream vss(vert_data);
                std::string index_str;
                int v_idx = 0, vt_idx = 0, vn_idx = 0;

                // Parse v/vt/vn format
                std::getline(vss, index_str, '/');
                v_idx = std::stoi(index_str) - 1; // OBJ is 1-indexed

                std::getline(vss, index_str, '/');
                if (!index_str.empty()) vt_idx = std::stoi(index_str) - 1;

                std::getline(vss, index_str, '/');
                if (!index_str.empty()) vn_idx = std::stoi(index_str) - 1;

                // Add to arrays
                int current_index = data.Vertices.Num();
                data.Vertices.Add(temp_vertices[v_idx]);

                if (vt_idx >= 0 && vt_idx < temp_uvs.size()) {
                    data.UV0.Add(temp_uvs[vt_idx]);
                }
                else {
                    data.UV0.Add(fvector2d(0, 0));
                }

                if (vn_idx >= 0 && vn_idx < temp_normals.size()) {
                    data.Normals.Add(temp_normals[vn_idx]);
                }
                else {
                    data.Normals.Add(fvector(0, 0, 1));
                }

                data.VertexColors.Add(FColor(255, 255, 255, 255));

                return current_index;
                };

            int i1 = parse_face_vertex(v1);
            int i2 = parse_face_vertex(v2);
            int i3 = parse_face_vertex(v3);

            // Add triangle indices
            data.Triangles.Add(i1);
            data.Triangles.Add(i2);
            data.Triangles.Add(i3);
        }
    }

    file.close();

    // Generate tangents if needed
    for (int i = 0; i < data.Vertices.Num(); i++) {
        FProcMeshTangent tangent;
        tangent.TangentX = fvector(1, 0, 0);
        tangent.bFlipTangentY = false;
        data.Tangents.Add(tangent);
    }


    return data;
}
bool meshcreated = false;



    
void set_radar(aplayercontroller* controller, bool status) {
    if (auto local_pawn = controller->K2_GetPawn_Local()) {
        auto actors = cache::players;

        for (int i = 0; i < actors.size(); i++) {
            if (auto actor = actors[i]; actor != local_pawn) {
                if (auto character_minimap = actor->get_character_minimap_component(); auto portrait_minimap = actor->get_portrait_minimap_component()) {

                    if (!controller->dormant_server(actor) || !actor->get_mesh())
                        continue;

                    character_minimap->set_observer_status(status);
                    character_minimap->set_visible_status(status);

                    portrait_minimap->set_observer_status(status);
                    portrait_minimap->set_visible_status(status);
                }
            }
        }
    }

}


inline void SetComponentVisibility(USceneComponent* component, bool bNewVisibility, bool bPropagateToChildren)
{
    if (!component || !memory::IsValidPointer((uintptr_t)component))
        return;

    auto function_name = crypt(L"Engine.SceneComponent.SetVisibility").decrypt();
    static uobject* Function = nullptr;
    if (!Function)
        Function = uobject::StaticFindObject(nullptr, nullptr, function_name, false);

    if (!Function)
        return;

    struct {
        bool bNewVisibility;
        bool bPropagateToChildren;
    } Args;

    Args.bNewVisibility = bNewVisibility;
    Args.bPropagateToChildren = bPropagateToChildren;

    ((uobject*)component)->process_event(Function, &Args);
}
inline uskeletalmeshcomponent* FindSightComponent(currentequippable* weapon, uskeletalmeshcomponent* GunMesh1P)
{
    if (!IsValidPtr(weapon) || !memory::IsValidPointer((uintptr_t)weapon)) {
        return nullptr;
    }
    if (!IsValidPtr(GunMesh1P) || !memory::IsValidPointer((uintptr_t)GunMesh1P)) {
        return nullptr;
    }

    USceneComponent* sceneComp =
        reinterpret_cast<USceneComponent*>(GunMesh1P);

    tarray<USceneComponent*> children;

    sceneComp->GetChildrenComponents(true, &children);

    for (int i = 0; i < children.size(); i++)
    {
        USceneComponent* child = children[i];
        if (!IsValidPtr(child) || !memory::IsValidPointer((uintptr_t)child)) {
            continue;
        }

        fstring childName = system::get_object_name((uobject*)child);
        std::string name = childName.ToString();

        // Look for Skeletal MeshComponent with generic name (likely the sight)
        if (name.find("SkeletalMeshComponent_") != std::string::npos)
        {
            uskeletalmeshcomponent* skelMesh = reinterpret_cast<uskeletalmeshcomponent*>(child);
            if (memory::IsValidPointer((uintptr_t)skelMesh)) {
                // Cast to UPrimitiveComponent to access GetNumMaterials
                UPrimitiveComponent* primComp = reinterpret_cast<UPrimitiveComponent*>(skelMesh);
                if (primComp && memory::IsValidPointer((uintptr_t)primComp)) {
                    int32_t numMaterials = primComp->GetNumMaterials();
                    if (numMaterials > 0 && numMaterials < 100) {
                        return skelMesh;
                    }
                }
            }
        }
    }

    return nullptr;
}
UProceduralMeshComponent* ProcMesh;
static uobject* CreateMeshFunc;

namespace helper {
    fstring convert_weapon_name(fstring weapon_name)
    {
        std::wstring weapon_name_str = weapon_name.wide();

        if (weapon_name_str.find(L"Ability_Melee_Base_C") != std::wstring::npos)
            return L"Melee";
        else if (weapon_name_str.find(L"BasePistol_C") != std::wstring::npos)
            return L"Classic";
        else if (weapon_name_str.find(L"SawedOffShotgun_C") != std::wstring::npos)
            return L"Shorty";
        else if (weapon_name_str.find(L"AutomaticPistol_C") != std::wstring::npos)
            return L"Frenzy";
        else if (weapon_name_str.find(L"LugerPistol_C") != std::wstring::npos)
            return L"Ghost";
        else if (weapon_name_str.find(L"RevolverPistol_C") != std::wstring::npos)
            return L"Sheriff";
        else if (weapon_name_str.find(L"Vector_C") != std::wstring::npos)
            return L"Stinger";
        else if (weapon_name_str.find(L"SubMachineGun_MP5") != std::wstring::npos)
            return L"Spectre";
        else if (weapon_name_str.find(L"PumpShotgun_C") != std::wstring::npos)
            return L"Bucky";
        else if (weapon_name_str.find(L"AutomaticShotgun_C") != std::wstring::npos)
            return L"Judge";
        else if (weapon_name_str.find(L"AssaultRifle_Burst_C") != std::wstring::npos)
            return L"Bulldog";
        else if (weapon_name_str.find(L"DMR_C") != std::wstring::npos)
            return L"Guardian";
        else if (weapon_name_str.find(L"AssaultRifle_ACR_C") != std::wstring::npos)
            return L"Phantom";
        else if (weapon_name_str.find(L"AssaultRifle_AK_C") != std::wstring::npos)
            return L"Vandal";
        else if (weapon_name_str.find(L"LeverSniperRifle_C") != std::wstring::npos)
            return L"Marshal";
        else if (weapon_name_str.find(L"BoltSniper_C") != std::wstring::npos)
            return L"Operator";
        else if (weapon_name_str.find(L"LightMachineGun_C") != std::wstring::npos)
            return L"Ares";
        else if (weapon_name_str.find(L"HeavyMachineGun_C") != std::wstring::npos)
            return L"Odin";
        else if (weapon_name_str.find(L"Gun_Deadeye_Q_Pistol_C") != std::wstring::npos)
            return L"Headhunter";
        else if (weapon_name_str.find(L"Ability_Wushu_X_Dagger_Production_C") != std::wstring::npos)
            return L"Blade storm";
        else if (weapon_name_str.find(L"Gun_Sprinter_X_HeavyLightningGun_Production_C") != std::wstring::npos)
            return L"Overdrive";
        else if (weapon_name_str.find(L"DS_Gun_C") != std::wstring::npos)
            return L"Outlaw";
        else if (weapon_name_str.find(L"Gun_Deadeye_X_Giantslayer_Prototype_C") != std::wstring::npos)
            return L"Tour de force";
        return L"Invalid";
    }
}



#define NEAR_PLANE_DISTANCE 10.0f
namespace BulletTrace {
#define MAX_TRACERS2 100
#define TRACER_LIFETIME2 3.5f

#define MAX_TRACE_RANGE 100000.0f
#define TRACER_THICKNESS 0.8f

    // ============================================================================
    // STRUCTURES
    // ============================================================================
    struct Tracer {
        fvector worldStart;
        fvector worldEnd;
        float timeCreated;
        flinearcolor color;
        bool isActive;  // Track active state
    };


    static Tracer g_tracers[MAX_TRACERS2];
    static int g_currentTracerIndex = 0;
    static int g_activeTracerCount = 0;


    static const flinearcolor TRACER_COLORS[8] = {
    flinearcolor(1.0f, 0.0f, 0.0f, 1.0f),    // Pure Red
    flinearcolor(0.0f, 1.0f, 0.0f, 1.0f),    // Pure Green
    flinearcolor(0.0f, 0.5f, 1.0f, 1.0f),    // Bright Blue
    flinearcolor(1.0f, 1.0f, 0.0f, 1.0f),    // Pure Yellow
    flinearcolor(1.0f, 0.3f, 0.0f, 1.0f),    // Bright Orange
    flinearcolor(1.0f, 0.0f, 1.0f, 1.0f),    // Pure Magenta
    flinearcolor(0.0f, 1.0f, 1.0f, 1.0f),    // Pure Cyan
    flinearcolor(1.0f, 0.0f, 0.5f, 1.0f)     // Hot Pink
    };


    struct FFiringResults {
        fvector FiringDirection; // 0x00(0x18)
        fvector StartLocation;   // 0x18(0x18)
    };

    struct FOnShot_Params {
        void* FiringState;                    // 0x00(0x08)
        int32_t ShotIndex;                    // 0x08(0x04)
        bool bTracerEnabled;                  // 0x0c(0x01)
        bool bWasLastShot;                    // 0x0d(0x01)
        char pad_0E[0x2];                     // 0x0e(0x02)
        tarray<FFiringResults> FiringResults; // 0x10(0x10)
    };

    // Your existing Custom_OnShot
    struct FCustom_OnShot_Params {
        void* FiringState;
        int32_t ShotIndex;
        bool bTracerEnabled;
        bool bWasLastShot;
        tarray<FFiringResults> FiringResults;
    };


    inline float GetCurrentGameTime() {
        static uint64_t baseTime = GetTickCount64();
        return (GetTickCount64() - baseTime) * 0.001f;
    }

    inline int ComputeOutCode(float x, float y, float w, float h) {
        int code = 0;
        if (x < 0.0f) code |= 1;
        else if (x > w) code |= 2;
        if (y < 0.0f) code |= 4;
        else if (y > h) code |= 8;
        return code;
    }

    bool ClipLineToScreen(fvector2d& start, fvector2d& end, float screenWidth, float screenHeight) {
        int outcode0 = ComputeOutCode(start.x, start.y, screenWidth, screenHeight);
        int outcode1 = ComputeOutCode(end.x, end.y, screenWidth, screenHeight);

        // Early acceptance
        if (!(outcode0 | outcode1)) return true;

        // Early rejection
        if (outcode0 & outcode1) return false;

        // Clip iteratively
        for (int iter = 0; iter < 4; ++iter) {
            if (!(outcode0 | outcode1)) return true;
            if (outcode0 & outcode1) return false;

            int outcodeOut = outcode0 ? outcode0 : outcode1;
            float x, y;

            if (outcodeOut & 8) {
                x = start.x + (end.x - start.x) * (screenHeight - start.y) / (end.y - start.y);
                y = screenHeight;
            }
            else if (outcodeOut & 4) {
                x = start.x + (end.x - start.x) * (-start.y) / (end.y - start.y);
                y = 0.0f;
            }
            else if (outcodeOut & 2) {
                y = start.y + (end.y - start.y) * (screenWidth - start.x) / (end.x - start.x);
                x = screenWidth;
            }
            else {
                y = start.y + (end.y - start.y) * (-start.x) / (end.x - start.x);
                x = 0.0f;
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

        return false;
    }

    inline bool PerformLineTrace(const fvector& Start, const fvector& Direction, fvector& OutHitLocation) {
        UWorld2* g_World = UWorld2::GetWorld();
        if (!g_World) {
            OutHitLocation = Start + (Direction * MAX_TRACE_RANGE);
            return false;
        }

        fvector End = Start + (Direction * MAX_TRACE_RANGE);
        FHitResult HitResult;
        tarray<uobject*> ActorsToIgnore;

        bool bHit = ShooterGameBlueprints::ares_line_trace_single_by_channel(
            g_World,
            Start,
            End,
            ActorsToIgnore,
            &HitResult,
            ECollisionChannel::ECC_Visibility,
            false,
            true
        );

        OutHitLocation = bHit ? HitResult.Location : End;
        return bHit;
    }


    template<typename T>
    inline bool IsBadReadPtr(T* ptr) {
        if (!ptr) return true;

        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery(ptr, &mbi, sizeof(mbi)) == 0) return true;

        if (mbi.State != MEM_COMMIT) return true;
        if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_EXECUTE) return true;

        return false;
    }

    using tProcessEvent = void(*)(void*, uobject*, void*, uintptr_t, void*);
    tProcessEvent oProcessEvent = nullptr;




    void hkProcessEvent(void* class_, uobject* function, void* params, uintptr_t magic, void* original_fn) {
        // Comprehensive validation
        if (!class_ || IsBadReadPtr(class_)) goto call_original;
        if (!function || IsBadReadPtr(function)) goto call_original;
        if (!oProcessEvent) goto call_original;

        // Validate function name access
        if (!IsBadReadPtr(function)) {
            fstring functionName = system::get_object_name(function);

            if (functionName.ToString() == crypt("Custom_OnShot").decrypt() ||
                functionName.ToString().find("OnShot__DelegateSignature") != std::string::npos) {
                //std::cout << "[SHOT EVENT] " << functionName.ToString() << std::endl;
                auto* shotParams = static_cast<FCustom_OnShot_Params*>(params);

                if (shotParams && !IsBadReadPtr(shotParams) && shotParams->bTracerEnabled) {
                    float currentTime = GetCurrentGameTime();
                    int resultCount = shotParams->FiringResults.Num();

                    // Validate result count
                    if (resultCount > 0 && resultCount < 100) {
                        for (int i = 0; i < resultCount; ++i) {
                            FFiringResults& result = shotParams->FiringResults[i];

                            // Validate result
                            if (IsBadReadPtr(&result)) continue;

                            // Get the ACTUAL hit point first using original trace from camera
                            fvector actualEndLocation;
                            BulletTrace::PerformLineTrace(result.StartLocation, result.FiringDirection, actualEndLocation);

                            // Now try to get muzzle location for VISUAL tracer only
                            fvector muzzleLocation = result.StartLocation; // Default to camera position
                            bool gotMuzzle = false;

                            // Get MyShooter from globals or local player
                            if (character && IsValidPtr(character)) {
                                if (auto inventory = character->get_inventory()) {
                                    if (IsValidPtr(inventory)) {
                                        if (auto weapon = inventory->get_current_equippable()) {
                                            if (IsValidPtr(weapon)) {
                                                if (auto weaponMesh = weapon->GetEquippableMesh()) {
                                                    if (IsValidPtr(weaponMesh)) {

                                                        for (int i = 0; i < 3; i++) {
                                                            fname socket = string::string_to_name(L"MuzzlePoint");
                                                            fvector loc = weaponMesh->GetSocketLocation(socket);

                                                            if (loc.x != 0.0f || loc.y != 0.0f || loc.z != 0.0f) {
                                                                muzzleLocation = loc;
                                                                gotMuzzle = true;
                                                                break;
                                                            }
                                                        }

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            // If we got muzzle location, recalculate the visual end point
                            // by tracing from muzzle to the actual hit point direction
                            if (gotMuzzle) {
                                // Calculate direction from muzzle to actual hit
                                fvector muzzleToHit = actualEndLocation - muzzleLocation;
                                float distance = muzzleToHit.size();

                                if (distance > 0.01f) {
                                    fvector direction = muzzleToHit / distance; // Normalize

                                    // Trace from muzzle in that direction to find visual end
                                    fvector visualEnd;
                                    BulletTrace::PerformLineTrace(muzzleLocation, direction, visualEnd);
                                    actualEndLocation = visualEnd;
                                }
                            }

                            // Select color
                            int colorIndex = (rand() & 7);

                            // Store tracer
                            Tracer& tracer = g_tracers[g_currentTracerIndex];
                            tracer.worldStart = muzzleLocation;           // Visual starts from muzzle
                            tracer.worldEnd = actualEndLocation;          // Visual ends at traced hit
                            tracer.timeCreated = currentTime;
                            tracer.color = TRACER_COLORS[colorIndex];
                            tracer.isActive = true;

                            g_currentTracerIndex = (g_currentTracerIndex + 1) % MAX_TRACERS2;
                            if (g_activeTracerCount < MAX_TRACERS2) g_activeTracerCount++;
                        }
                    }
                }
            }
        }

    call_original:
        if (oProcessEvent) {
            oProcessEvent(class_, function, params, magic, original_fn);
        }
    }



    void RenderBulletTracers(aplayercameramanager* mycamera, aplayercontroller* MyController,
        ucanvas* canvas, ashootercharacter* MyShooter) {
        // Fast validation
        if (!mycamera || IsBadReadPtr(mycamera)) return;
        if (!MyController || IsBadReadPtr(MyController)) return;
        if (!canvas || IsBadReadPtr(canvas)) return;
        if (!MyShooter || IsBadReadPtr(MyShooter)) return;
        if (g_activeTracerCount == 0) return;

        const float currentTime = GetCurrentGameTime();
        const float invLifetime = 1.0f / TRACER_LIFETIME2;

        // Cache camera data with validation
        fvector cameraLocation = mycamera->get_camera_location();
        fvector cameraForward = MyShooter->GetActorForwardVector();
        fvector2d screenSize = canvas->get_screen_size2();

        // Validate screen size
        if (screenSize.x <= 0.0f || screenSize.y <= 0.0f) return;

        const float screenWidth = screenSize.x;
        const float screenHeight = screenSize.y;

        int activeCount = 0;

        // Process tracers
        for (int i = 0; i < MAX_TRACERS2; ++i) {
            Tracer& tracer = g_tracers[i];

            if (!tracer.isActive) continue;

            const float age = currentTime - tracer.timeCreated;

            // Check lifetime
            if (age >= TRACER_LIFETIME2 || age < 0.0f) {
                tracer.isActive = false;
                continue;
            }

            activeCount++;

            // Cache vectors
            fvector start = tracer.worldStart;
            fvector end = tracer.worldEnd;

            // Camera space check
            const fvector toStart = start - cameraLocation;
            const fvector toEnd = end - cameraLocation;
            const float startDot = fvector::DotProduct(toStart, cameraForward);
            const float endDot = fvector::DotProduct(toEnd, cameraForward);

            // Both behind camera - skip
            if (startDot < NEAR_PLANE_DISTANCE && endDot < NEAR_PLANE_DISTANCE) continue;

            // Clip to near plane
            if (startDot < NEAR_PLANE_DISTANCE) {
                float t = (NEAR_PLANE_DISTANCE - startDot) / (endDot - startDot);
                t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;
                start = start + (end - start) * t;
            }
            if (endDot < NEAR_PLANE_DISTANCE) {
                float t = (NEAR_PLANE_DISTANCE - startDot) / (endDot - startDot);
                t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f : t;
                end = start + (end - start) * t;
            }

            // Project to screen
            fvector2d screenStart, screenEnd;
            if (!MyController->project_world_location_to_screen(start, screenStart, false)) continue;
            if (!MyController->project_world_location_to_screen(end, screenEnd, false)) continue;

            // Clip to screen bounds
            if (!BulletTrace::ClipLineToScreen(screenStart, screenEnd, screenWidth, screenHeight)) continue;

            // Calculate fade
            const float normalizedAge = age * invLifetime;
            const float fadeFactorSq = normalizedAge * normalizedAge;
            const float fadeFactor = 1.0f - (fadeFactorSq * normalizedAge);

            // Just make the colors brighter/more saturated
            flinearcolor tracerColor = tracer.color;
            tracerColor.r = tracerColor.r * 3.0f > 1.0f ? 1.0f : tracerColor.r * 3.0f;
            tracerColor.g = tracerColor.g * 3.0f > 1.0f ? 1.0f : tracerColor.g * 3.0f;
            tracerColor.b = tracerColor.b * 3.0f > 1.0f ? 1.0f : tracerColor.b * 3.0f;
            tracerColor.a = fadeFactor;

            canvas->k2_drawline(screenStart, screenEnd, TRACER_THICKNESS, tracerColor);
        }

        // Update active count
        g_activeTracerCount = activeCount;
    }


}

namespace HookManager {
    static void* hooked_objects[64] = { nullptr };
    static int hooked_count = 0;
    static CRITICAL_SECTION hook_cs;
    static bool cs_initialized = false;

    void Initialize() {
        if (!cs_initialized) {
            InitializeCriticalSection(&hook_cs);
            cs_initialized = true;
        }
    }

    bool IsAlreadyHooked(void* ptr) {
        EnterCriticalSection(&hook_cs);
        bool found = false;
        for (int i = 0; i < hooked_count; ++i) {
            if (hooked_objects[i] == ptr) {
                found = true;
                break;
            }
        }
        LeaveCriticalSection(&hook_cs);
        return found;
    }

    void AddHookedObject(void* ptr) {
        EnterCriticalSection(&hook_cs);
        if (hooked_count < 64) {
            hooked_objects[hooked_count++] = ptr;
        }
        LeaveCriticalSection(&hook_cs);
    }

    bool InstallProcessEventHook(uobject* anyUObject) {
        if (!anyUObject || BulletTrace::IsBadReadPtr(anyUObject)) return false;
        if (!memory::module_base) return false;

        Initialize();

        // Check if already hooked
        if (IsAlreadyHooked(anyUObject)) return true;

     
        constexpr int ProcessEventIndex = 0x53;
        shadow_vmt zxczxcxcvxcvkxcvx;
        bool success = zxczxcxcvxcvkxcvx.hook<BulletTrace::tProcessEvent>(
            memory::module_base,
            (uintptr_t)anyUObject,
            ProcessEventIndex,
            BulletTrace::hkProcessEvent,
            &BulletTrace::oProcessEvent
        );

        if (success) {
            AddHookedObject(anyUObject);
        }

        return success;
    }

    void ClearHookedObjects() {
        EnterCriticalSection(&hook_cs);
        memset(hooked_objects, 0, sizeof(hooked_objects));
        hooked_count = 0;
        LeaveCriticalSection(&hook_cs);
    }
}

struct WeaponVariationCache {
    std::wstring weapon_type;
    int variation;
    std::chrono::steady_clock::time_point timestamp;
};

std::unordered_map<uintptr_t, WeaponVariationCache> g_WeaponVariationCache;

#include <mutex>
#include <atomic>
std::mutex g_WeaponCacheMutex;
std::mutex g_WeaponVariationMutex;
std::mutex g_TextMeshMutex;

int GetWeaponVariation(uintptr_t weapon_ptr, const std::wstring& weapon_type) {
    if (weapon_ptr == 0) {
        if (weapon_type == L"Vandal") return rand() % 4 + 1;
        if (weapon_type == L"Phantom") return rand() % 3 + 1;
        return 1;
    }

    auto it = g_WeaponVariationCache.find(weapon_ptr);
    auto now = std::chrono::steady_clock::now();

    if (it == g_WeaponVariationCache.end() || it->second.weapon_type != weapon_type) {
        int variation = 1;

        if (weapon_type == L"Vandal") {
            variation = rand() % 4 + 1;
        }
        else if (weapon_type == L"Phantom") {
            variation = rand() % 3 + 1;
        }
        else {
            variation = 1;
        }

        g_WeaponVariationCache[weapon_ptr] = {
            weapon_type,
            variation,
            now
        };
        return variation;
    }

    return it->second.variation;
}
class UFresnelComponent final : public UActorComponent
{
public:
    char                                         Pad_D8[0x8];                                       // 0x00D8(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
    bool                                          bDirty;                                            // 0x00E0(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                         Pad_E1[0x17];                                      // 0x00E1(0x0017)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* Materials1P;                                       // 0x00F8(0x0050)(Protected, NativeAccessSpecifierProtected)
    uobject* Materials3P;                                       // 0x0148(0x0050)(Protected, NativeAccessSpecifierProtected)
    uobject* Cached3PFresnelSettings;                           // 0x0198(0x0010)(NoDestructor, Protected, NativeAccessSpecifierProtected)
    uobject* Cached1PFresnelSettings;                           // 0x01A8(0x0010)(NoDestructor, Protected, NativeAccessSpecifierProtected)
    uobject* OnIntSettingsChanged; // 0x01B8(0x0014)(ZeroConstructor, InstancedReference, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    uobject* OnBoolSettingsChanged; // 0x01CC(0x0014)(ZeroConstructor, InstancedReference, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    bool                                          UseColorBlindPreferences;                          // 0x01E0(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                         Pad_1E1[0x3];                                      // 0x01E1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         FresnelIntensity;                                  // 0x01E4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                         FresnelOffset;                                     // 0x01E8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                         OriginalFresnelIntensity;                          // 0x01EC(0x0004)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    float                                         OriginalFresnelOffset;                             // 0x01F0(0x0004)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    char                                         Pad_1F4[0x4];     

    float SenIntensity(float intesity) {
        static uobject* function;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FresnelComponent.SetIntensity").decrypt());

        struct
        {
            float intensity;
        } params;

        params.intensity = intesity;


        this->process_event(function, &params);
        return params.intensity;
    }
};
void CleanStaleWeaponVariations() {
    auto now = std::chrono::steady_clock::now();
    for (auto it = g_WeaponVariationCache.begin(); it != g_WeaponVariationCache.end();) {
        if (now - it->second.timestamp > std::chrono::seconds(30)) {
            it = g_WeaponVariationCache.erase(it);
        }
        else {
            ++it;
        }
    }
}

inline bool IsValidViewModelPointer(uintptr_t ptr) {
    if (ptr == 0 || ptr == (uintptr_t)-1 || ptr < 0x10000 || ptr > 0x7FFFFFFFFFFF)
        return false;

    __try {
        MEMORY_BASIC_INFORMATION mbi = { 0 };
        if (VirtualQuery((LPCVOID)ptr, &mbi, sizeof(mbi))) {
            return (mbi.State & MEM_COMMIT) &&
                !(mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD));
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }

    return false;
}

inline bool IsValidViewModelObject(void* obj) {
    if (!obj) return false;
    return IsValidViewModelPointer((uintptr_t)obj);
}
inline tarray<USceneComponent*> GetChildrenComponents(USceneComponent* component, bool bIncludeAllDescendants) {
    tarray<USceneComponent*> result;
    if (!component || !IsValidViewModelObject(component)) return result;

    static UObject* Function = nullptr;
    if (!Function) {
        auto function_name = (L"Engine.SceneComponent.GetChildrenComponents");
        Function = UObject::StaticFindObject(nullptr, nullptr, function_name, false);
    }

    if (!Function || !IsValidViewModelObject(Function)) return result;

    struct {
        bool bIncludeAllDescendants;
        tarray<USceneComponent*> Children;
    } Args;

    Args.bIncludeAllDescendants = bIncludeAllDescendants;
    Args.Children.data = nullptr;
    Args.Children.count = 0;
    Args.Children.max = 0;

    __try {
        component->ProcessEvent(Function, &Args);
        return Args.Children;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return result;
    }
}

static uintptr_t last_weapon_ptr = 0;
static std::wstring last_weapon_name;

struct WeaponCacheEntry
{
    uintptr_t weapon_ptr;
    std::wstring weapon_type;
    std::chrono::steady_clock::time_point last_processed_time;
    bool is_processing;
};

std::unordered_map<uintptr_t, WeaponCacheEntry> g_WeaponCache;
std::chrono::steady_clock::time_point last_global_check = std::chrono::steady_clock::now();
const auto CACHE_TIMEOUT = std::chrono::milliseconds(500); // Clear cache after 500ms of no activity
const auto PROCESS_TIMEOUT = std::chrono::milliseconds(100); // Don't process same weapon more than once per 100ms
std::atomic<bool> is_processing_model2{ false };



void CleanStaleWeaponCache()
{
    auto now = std::chrono::steady_clock::now();
    if (now - last_global_check < CACHE_TIMEOUT)
        return;

    last_global_check = now;

    for (auto it = g_WeaponCache.begin(); it != g_WeaponCache.end();)
    {
        if (now - it->second.last_processed_time > CACHE_TIMEOUT)
            it = g_WeaponCache.erase(it);
        else
            ++it;
    }
}
static uintptr_t lastWorld = 0;
static AGameObject* CachedFogActor = nullptr;
static AGameObject* CachedNiggaActor = nullptr;
static bool FogDomeCached = false;


static AGameObject* CachedSkyDome = nullptr;
static bool SkyDomeCached = false;
static tarray<AGameObject*> CachedAbilityObjects;
static bool AbilityCacheBuilt = false;
static uworld* CachedAbilityWorld = nullptr;
static tarray<AGameObject*> CachedDroppedObjects;
static bool DroppedCached = false;
static uworld* DroppedCachedWorld = nullptr;
__forceinline fvector GetBoneMatrix(void* Mesh, int BoneIndex) {

    if (!Mesh) [[unlikely]]
        return fvector(0.f, 0.f, 0.f);


    if (BoneIndex < 0) [[unlikely]]
        return fvector(0.f, 0.f, 0.f);


    using BoneMatrixFn = fmatrix * (__fastcall*)(void*, fmatrix*, int);
    static const BoneMatrixFn fn = reinterpret_cast<BoneMatrixFn>(memory::module_base + offsets::bone_matrix);


    fmatrix BoneMatrix;


    fn(Mesh, &BoneMatrix, BoneIndex);


    return fvector(BoneMatrix.wplane.x, BoneMatrix.wplane.y, BoneMatrix.wplane.z);
}
namespace defines {
    fvector location = { 0, 0, 0 };
    fvector direction = { 0, 0, 0 };
}

std::unordered_map<uintptr_t, UProceduralMeshComponent*> g_ProcMeshCache;
std::unordered_map<uintptr_t, int> g_LastChildCount;


uintptr_t last_mesh_ptr = 0;

std::unordered_map<uintptr_t, std::unordered_set<USceneComponent*>> g_HiddenChildren;
//
//void run(tarray<ashootercharacter*> actors, aplayercontroller* controller, ucanvas* canvas) {
//    if (auto pawn = controller->K2_GetPawn_Local()) {
//
//        tarray<ashootercharacter*> actor_to_ignore = blueprints::find_all_shooters_with_alliance(UWorldSave, character, earesalliance::any, false, true);
//
//
//
//        static uobject* throw_info;
//      
//        MAWGAGO maw;
//        tarray<AGameObject*> all_actors = GameplayStatics::GetAllActorsOfClass<AGameObject>(UWorldSave, maw.engineactor);
//
//        for (int i = 0; i < all_actors.size(); i++) {
//            if (auto actor = all_actors[i]) {
//                if (string::contains(system::get_object_name(actor).c_str(), L"Molotov_Production_C")) {
//                    // Throw Informations
//                    if (!throw_info) {
//                        throw_info = memory::read<uobject*>(std::uintptr_t(actor) + 0x1070);
//                    }
//                }
//            }
//        }
//
//        tarray<AGameObject*> projectiles = GameplayStatics::GetAllActorsOfClass<AGameObject>(UWorldSave, maw.projectile);
//        for (int i = 0; i < projectiles.size(); i++) {
//            if (auto actor = projectiles[i]) {
//                if (string::contains(system::get_object_name(actor).c_str(), L"Projectile_Sarge")) {
//                    printf("Projectile\n");
//                    if (auto movement_component = memory::read<uobject*>(std::uintptr_t(actor) + 0x510)) {
//                        auto function = uobject::find_object<uobject*>(L"Engine.MovementComponent.GetGravityZ");
//                        float return_value;
//
//                        movement_component->process_event(function, &return_value);
//
//                        printf("Gravity: %f\n", return_value);
//                    }
//
//                }
//
//            }
//        }
//
//        if (auto mesh = pawn->get_mesh()) {
//          
//            if (controller->is_input_key_down(keys::left_mouse))
//                FProjectileThrowTuning throw_ = memory::read<FProjectileThrowTuning>(std::uintptr_t(throw_info) + 0x2e0);
//
//                auto function = uobject::find_object<uobject*>(L"ShooterGame.ProjectileThrowStateComponent.GetThrowingLocationAndDirection");
//                struct {
//                    fvector location;
//                    fvector direction;
//                } params;
//
//                throw_info->process_event(function, &params);
//
//                defines::location = params.location;
//                defines::direction = params.direction;
//            }
//
//            static fvector current_velocity;
//            static fvector currnet_bounce_hit;
//            static fvector current_impact_normal;
//            static fvector last_prediction_location;
//
//            static int bounce_prediction_count;
//
//            if (defines::location.x) {
//
//                current_velocity = defines::direction * 3900.f; // oder 2
//
//                GameplayStatics::path_result result;
//                GameplayStatics::predict_projectile_path(UWorldSave, defines::location, current_velocity, actor_to_ignore, -2500.0f, &result);
//
//
//                fvector2d old_screen_pos;
//                for (int i = 0; i < result.path_data.size(); i++) {
//
//                    auto project = canvas->k2_project(result.path_data[i].location);
//                    if (project.z)
//                    {
//                        canvas->draw_circle(project.x, project.y, 10, 60, { 0, 0, 1, 1 });
//                        if (old_screen_pos.x) {
//
//                            fvector2d new_screen_pos = { project.x, project.y };
//                            canvas->k2_drawline(old_screen_pos, new_screen_pos, 1.f, { 1, 1, 1, 1 });
//                            old_screen_pos = new_screen_pos;
//                        }
//                        else
//                        {
//                            fvector2d new_screen_pos = { project.x, project.y };
//                            old_screen_pos = new_screen_pos;
//                        }
//                    }
//                }
//
//                auto project_last1 = canvas->k2_project(result.hit_result.Location);
//                if (project_last1.z)
//                    canvas->draw_circle(project_last1.x, project_last1.y, 10, 60, { 1, 0, 0, 1 });
//
//                //	current_velocity = result.hit_result.Normal;
//                current_impact_normal = result.hit_result.ImpactNormal;
//                currnet_bounce_hit = result.hit_result.Location;
//
//                for (int i = 0; i < 4; i++)
//                {
//                    // Loop Bounces (Zweiter Bounce)
//                    current_velocity = ::math::mirror_vector_by_normal(current_velocity, current_impact_normal) * 0.35f; // 0.35f = Bounceee
//
//                    GameplayStatics::path_result next_result;
//                    auto current_hit = GameplayStatics::predict_projectile_path(UWorldSave, currnet_bounce_hit, current_velocity, actor_to_ignore, 0, &next_result);
//
//
//                    fvector2d next_screen_old_pos;
//                    for (int i = 0; i < next_result.path_data.size(); i++) {
//
//                        auto project = canvas->k2_project(next_result.path_data[i].location);
//                        if (project.z)
//                        {
//                            canvas->draw_circle(project.x, project.y, 10, 60, { 0, 0, 1, 1 });
//                            if (next_screen_old_pos.x) {
//
//                                fvector2d new_screen_pos = { project.x, project.y };
//                                canvas->k2_drawline(next_screen_old_pos, new_screen_pos, 1.f, { 1, 1, 1, 1 });
//                                next_screen_old_pos = new_screen_pos;
//                            }
//                            else
//                            {
//                                fvector2d new_screen_pos = { project.x, project.y };
//                                next_screen_old_pos = new_screen_pos;
//                            }
//                        }
//                    }
//
//
//                    currnet_bounce_hit = next_result.hit_result.Location;
//                    current_impact_normal = next_result.hit_result.ImpactNormal;
//
//                    auto project_last = canvas->k2_project(next_result.hit_result.Location);
//
//                    if (project_last.z)
//                        canvas->draw_circle(project_last.x, project_last.y, 10, 60, { 0, 1, 0, 1 });
//                }
//
//
//
//
//
//                //// Letzter Bounce
//                //if (last_prediction_location.x) 
//                //{
//                //	auto project_last = canvas->project(last_prediction_location);
//
//                //	if (project_last.z) {
//                //		canvas->draw_circle(project_last.x, project_last.y, 10, 60, { 1, 0, 0, 1 });
//                //		fvector2d new_screen_pos = { project_last.x, project_last.y };
//                //		canvas->draw_line(old_screen_pos, new_screen_pos, 1.f, { 1, 1, 1, 1 });
//                //	}
//                //}
//            }
//        }
//    }
void draw_text(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
    
    canvas->k2_drawtext(font, text, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
}

#include <shlobj.h>     // For SHGetFolderPathA, CSIDL_DESKTOPDIRECTORY, SHGFP_TYPE_CURRENT
#include <shellapi.h>   // Additional shell functions
#include <Shlwapi.h>    // For path functions
#include <mutex>

// Also link against Shell32.lib and Shlwapi.lib in your project settings
// Or add these pragma directives:
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Shlwapi.lib")

std::string get_config_file_path() {
    char desktop_path[MAX_PATH];
    if (SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, SHGFP_TYPE_CURRENT, desktop_path) == S_OK) {
        std::string config_path = std::string(desktop_path) + "\\Config.dat";
        return config_path;
    }
    return "";
}
void save_config() {
    std::string config_path = get_config_file_path();
    if (config_path.empty()) return;

    std::ofstream file(config_path);
    if (!file.is_open()) return;

    auto write_bool = [&](int id, bool value) {
        file << id << "=" << (value ? "1" : "0") << "\n";
        };
    auto write_int = [&](int id, int value) {
        file << id << "=" << value << "\n";
        };
    auto write_float = [&](int id, float value) {
        file << id << "=" << value << "\n";
        };
    auto write_color = [&](int id, const flinearcolor& c) {
        file << id << "=" << c.r << "," << c.g << "," << c.b << "," << c.a << "\n";
        };
    auto write_wstring = [&](int id, const std::wstring& value) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string utf8_str = converter.to_bytes(value);
        file << id << "=" << utf8_str << "\n";
        };

    write_bool(401, globals::misc::skiptutorial);
    write_bool(402, globals::misc::skin_changer);
    write_bool(427, globals::misc::finisher);
    write_bool(428, globals::misc::onlylastkill);


    // ============ INSTALOCK ============
    write_bool(800, globals::il::enable);
    write_bool(801, globals::il::random_agent);
    write_int(802, globals::il::lock_agent);

    
}

void load_config() {
    std::string config_path = get_config_file_path();
    if (config_path.empty()) return;

    std::ifstream file(config_path);
    if (!file.is_open()) return;

    std::string line;

    auto parse_bool = [](const std::string& v) { return v == "1"; };
    auto parse_float = [](const std::string& v) {
        std::istringstream iss(v);
        iss.imbue(std::locale::classic());
        float result = 0.0f;
        iss >> result;
        return result;
        };
    auto parse_int = [](const std::string& v) { return std::stoi(v); };
    auto parse_wstring = [](const std::string& v) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(v);
        };

    while (std::getline(file, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty()) continue;

        size_t delim = line.find('=');
        if (delim == std::string::npos) continue;

        std::string key_str = line.substr(0, delim);
        std::string val = line.substr(delim + 1);

        try {
            int key = std::stoi(key_str);

            switch (key) {

            case 401: globals::misc::skiptutorial = parse_bool(val); break;
            case 402: globals::misc::skin_changer = parse_bool(val); break;
            case 427: globals::misc::finisher = parse_bool(val); break;
            case 428: globals::misc::onlylastkill = parse_bool(val); break;

                // INSTALOCK (800-802)
            case 800: globals::il::enable = parse_bool(val); break;
            case 801: globals::il::random_agent = parse_bool(val); break;
            case 802: globals::il::lock_agent = parse_int(val); break;


                

            default: break;
            }
        }
        catch (...) {
            continue;
        }
    }
}
namespace SPIKELINEUP {
    namespace development { // For testing purposes only.
        namespace defines {
            fvector location = { 0, 0, 0 };
            fvector direction = { 0, 0, 0 };
        }

        struct FProjectileEstimationInfo final
        {
        public:
            float                                         ProjectileSpeed;                                   // 0x0000(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         ProjectileGravityScale;                            // 0x0004(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            fvector                                       ImpartActorVelocityPercentVector;                  // 0x0008(0x0018)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         ImpartVelocityMatchingDirectionFraction;           // 0x0020(0x0004)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            bool                                          bUseTrueVerticalVelocity;                          // 0x0024(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            uint8                                         Pad_25[0x3];                                       // 0x0025(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
            float                                         DownwardVelocityScale;                             // 0x0028(0x0004)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            uint8                                         bBounceAngleAffectsFriction : 1;                   // 0x002C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
            uint8                                         Pad_2D[0x3];                                       // 0x002D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
            float                                         Bounciness;                                        // 0x0030(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         Friction;                                          // 0x0034(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         BounceVelocityProjectileStopThreshold;             // 0x0038(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         BounceStopSurfaceAngle;                            // 0x003C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
        };

        struct FProjectileThrowTuning final
        {
        public:
            uobject*                   ProjectileClass;                                   // 0x0000(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance, NativeAccessSpecifierPublic)
            uobject*                ProjectileType;                                    // 0x0018(0x0008)(ZeroConstructor, Deprecated, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         SpeedScale;                                        // 0x0020(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         UpwardArc;                                         // 0x0024(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         UpwardShift;                                       // 0x0028(0x0004)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            uint8                                         Pad_2C[0x4];                                       // 0x002C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
             fvector                                      ThrowOffset;                                       // 0x0030(0x0018)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            float                                         ThrowDelay;                                        // 0x0048(0x0004)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            bool                                          bJumpThrowNormalization_LaunchPoint;               // 0x004C(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            bool                                          bJumpThrowNormalization_ImpartedVelocity;          // 0x004D(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
            uint8                                         Pad_4E[0x2];                                       // 0x004E(0x0002)(Fixing Struct Size After Last Property [ Dumper-7 ])
        };  
      
        void run(aplayercontroller* controller, ucanvas* canvas) {
            if (auto pawn = controller->K2_GetPawn_Local()) {
                tarray<ashootercharacter*> actor_to_ignore = blueprints::find_all_shooters_with_alliance(UWorldSave, character, earesalliance::any, false, true);
                static uobject* throw_info;

                tarray<AGameObject*> all_actors = GameplayStatics::GetAllActorsOfClass<AGameObject>(UWorldSave, uobject::find_object<uobject*>(L"Engine.Actor"));

                for (int i = 0; i < all_actors.size(); i++) {
                    if (auto actor = all_actors[i]) {
                        if (string::contains(system::get_object_name(actor).c_str(), L"Molotov_Production_C")) {
    
                            if (!throw_info) {
                                throw_info = memory::read<uobject*>(std::uintptr_t(actor) + 0x1070);
                            }
                        }
                    }
                }


                tarray<AGameObject*> projectiles = GameplayStatics::GetAllActorsOfClass<AGameObject>(UWorldSave, uobject::find_object<uobject*>(L"ShooterGame.Projectile"));
                for (int i = 0; i < projectiles.size(); i++) {
                    if (auto actor = projectiles[i]) {
                        if (string::contains(system::get_object_name(actor).c_str(), L"Projectile_Sarge")) {
                            printf("Projectile\n");
                            if (auto movement_component = memory::read<uobject*>(std::uintptr_t(actor) + 0x510)) {
                                auto function = uobject::find_object<uobject*>(L"Engine.MovementComponent.GetGravityZ");
                                float return_value;

                                movement_component->process_event(function, &return_value);

                                printf("Gravity: %f\n", return_value);
                            }

                        }

                    }
                }

                if (auto mesh = pawn->get_mesh()) {

                    if (controller->is_input_key_down(keys::left_alt)) {
                        FProjectileThrowTuning throw_ = memory::read<FProjectileThrowTuning>(std::uintptr_t(throw_info) + 0x2e0);

                        auto function = uobject::find_object<uobject*>(L"ShooterGame.ProjectileThrowStateComponent.GetThrowingLocationAndDirection");
                        struct {
                            fvector location;
                            fvector direction;
                        } params;

                        throw_info->process_event(function, &params);

                        defines::location = params.location;
                        defines::direction = params.direction;
                    }

                    static fvector current_velocity;
                    static fvector currnet_bounce_hit;
                    static fvector current_impact_normal;
                    static fvector last_prediction_location;

                    static int bounce_prediction_count;

                    if (defines::location.x) {

                        current_velocity = defines::direction * 3900.f; // oder 2

                        GameplayStatics::path_result result;
                        GameplayStatics::predict_projectile_path(UWorldSave, defines::location, current_velocity, actor_to_ignore, -2500.0f, &result);


                        fvector2d old_screen_pos;
                        for (int i = 0; i < result.path_data.size(); i++) {

                            auto project = canvas->k2_project(result.path_data[i].location);
                            if (project.z)
                            {
                                canvas->draw_circle(project.x, project.y, 10, 60, { 0, 0, 1, 1 });
                                if (old_screen_pos.x) {

                                    fvector2d new_screen_pos = { project.x, project.y };
                                    canvas->k2_drawline(old_screen_pos, new_screen_pos, 1.f, { 1, 1, 1, 1 });
                                    old_screen_pos = new_screen_pos;
                                }
                                else
                                {
                                    fvector2d new_screen_pos = { project.x, project.y };
                                    old_screen_pos = new_screen_pos;
                                }
                            }
                        }

                        auto project_last1 = canvas->k2_project(result.hit_result.Location);
                        if (project_last1.z)
                            canvas->draw_circle(project_last1.x, project_last1.y, 10, 60, { 1, 0, 0, 1 });

                        //	current_velocity = result.hit_result.Normal;
                        current_impact_normal = result.hit_result.ImpactNormal;
                        currnet_bounce_hit = result.hit_result.Location;

                        for (int i = 0; i < 4; i++)
                        {
                            // Loop Bounces (Zweiter Bounce)
                            current_velocity = math::mirror_vector_by_normal(current_velocity, current_impact_normal) * 0.35f; // 0.35f = Bounceee

                            GameplayStatics::path_result next_result;
                            auto current_hit = GameplayStatics::predict_projectile_path(UWorldSave, currnet_bounce_hit, current_velocity, actor_to_ignore, 0, &next_result);


                            fvector2d next_screen_old_pos;
                            for (int i = 0; i < next_result.path_data.size(); i++) {

                                auto project = canvas->k2_project(next_result.path_data[i].location);
                                if (project.z)
                                {
                                    canvas->draw_circle(project.x, project.y, 10, 60, { 0, 0, 1, 1 });
                                    if (next_screen_old_pos.x) {

                                        fvector2d new_screen_pos = { project.x, project.y };
                                        canvas->k2_drawline(next_screen_old_pos, new_screen_pos, 1.f, { 1, 1, 1, 1 });
                                        next_screen_old_pos = new_screen_pos;
                                    }
                                    else
                                    {
                                        fvector2d new_screen_pos = { project.x, project.y };
                                        next_screen_old_pos = new_screen_pos;
                                    }
                                }
                            }


                            currnet_bounce_hit = next_result.hit_result.Location;
                            current_impact_normal = next_result.hit_result.ImpactNormal;

                            auto project_last = canvas->k2_project(next_result.hit_result.Location);

                            if (project_last.z)
                                canvas->draw_circle(project_last.x, project_last.y, 10, 60, { 0, 1, 0, 1 });
                        }





                        //// Letzter Bounce
                        //if (last_prediction_location.x) 
                        //{
                        //	auto project_last = canvas->project(last_prediction_location);

                        //	if (project_last.z) {
                        //		canvas->draw_circle(project_last.x, project_last.y, 10, 60, { 1, 0, 0, 1 });
                        //		fvector2d new_screen_pos = { project_last.x, project_last.y };
                        //		canvas->draw_line(old_screen_pos, new_screen_pos, 1.f, { 1, 1, 1, 1 });
                        //	}
                        //}
                    }
                }
            }
        }
    }
}
class USkinnedMeshComponent : public uobject
{
public:
    uint8                                         Pad_6D0[0x8];                                      // 0x06D0(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* SkeletalMesh;                                      // 0x06D8(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uobject* SkinnedAsset;                                      // 0x06E0(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    uobject* LeaderPoseComponent;                               // 0x06E8(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    tarray<uobject*>                       SkinCacheUsage;                                    // 0x06F0(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NativeAccessSpecifierPublic)
    bool                                          bSetMeshDeformer;                                  // 0x0700(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    uint8                                         Pad_701[0x7];                                      // 0x0701(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* MeshDeformer;                                      // 0x0708(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, Protected, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    uobject* MeshDeformerInstanceSettings;                      // 0x0710(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, Protected, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    uobject* MeshDeformerInstance;                              // 0x0718(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, NoDestructor, Protected, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    uint8                                         Pad_720[0x178];                                    // 0x0720(0x0178)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* PhysicsAssetOverride;                              // 0x0898(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, AdvancedDisplay, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    int32                                         ForcedLodModel;                                    // 0x08A0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    int32                                         MinLodModel;                                       // 0x08A4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_8A8[0x10];                                     // 0x08A8(0x0010)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         StreamingDistanceMultiplier;                       // 0x08B8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_8BC[0xC];                                      // 0x08BC(0x000C)(Fixing Size After Last Property [ Dumper-7 ])
    tarray<struct uobject*>      LODInfo;                                           // 0x08C8(0x0010)(ZeroConstructor, Transient, NativeAccessSpecifierPublic)
    uint8                                         Pad_8D8[0x24];                                     // 0x08D8(0x0024)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* VisibilityBasedAnimTickOption;                     // 0x08FC(0x0001)(Edit, BlueprintVisible, ZeroConstructor, Config, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_8FD[0x1];                                      // 0x08FD(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
    uint8                                         BitPad_8FE_0 : 3;                                  // 0x08FE(0x0001)(Fixing Bit-Field Size Between Bits [ Dumper-7 ])
    uint8                                         bOverrideMinLod : 1;                               // 0x08FE(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bUseBoundsFromLeaderPoseComponent : 1;             // 0x08FE(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bForceWireframe : 1;                               // 0x08FE(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bDisableMorphTarget : 1;                           // 0x08FE(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bHideSkin : 1;                                     // 0x08FE(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bPerBoneMotionBlur : 1;                            // 0x08FF(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bComponentUseFixedSkelBounds : 1;                  // 0x08FF(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bConsiderAllBodiesForBounds : 1;                   // 0x08FF(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bSyncAttachParentLOD : 1;                          // 0x08FF(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bCanHighlightSelectedSections : 1;                 // 0x08FF(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bRecentlyRendered : 1;                             // 0x08FF(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bForceNonRenderedAnimUpdateRate : 1;               // 0x08FF(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bForceAnimUpdateIfRendered : 1;                    // 0x08FF(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bCastCapsuleDirectShadow : 1;                      // 0x0900(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bCastCapsuleIndirectShadow : 1;                    // 0x0900(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bCPUSkinning : 1;                                  // 0x0900(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bEnableUpdateRateOptimizations : 1;                // 0x0900(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bDisplayDebugUpdateRateOptimizations : 1;          // 0x0900(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bRenderStatic : 1;                                 // 0x0900(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         bIgnoreLeaderPoseComponentLOD : 1;                 // 0x0900(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         BitPad_900_7 : 1;                                  // 0x0900(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
    uint8                                         BitPad_901_0 : 1;                                  // 0x0901(0x0001)(Fixing Bit-Field Size Between Bits [ Dumper-7 ])
    uint8                                         bCachedLocalBoundsUpToDate : 1;                    // 0x0901(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Transient, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected))
    uint8                                         bCachedWorldSpaceBoundsUpToDate : 1;               // 0x0901(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Transient, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected))
    uint8                                         BitPad_901_3 : 1;                                  // 0x0901(0x0001)(Fixing Bit-Field Size Between Bits [ Dumper-7 ])
    uint8                                         bForceMeshObjectUpdate : 1;                        // 0x0901(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Transient, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected))
    uint8                                         bForceUpdateDynamicDataImmediately : 1;            // 0x0901(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
    uint8                                         BitPad_901_6 : 2;                                  // 0x0901(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
    uint8                                         BitPad_902_0 : 3;                                  // 0x0902(0x0001)(Fixing Bit-Field Size Between Bits [ Dumper-7 ])
    uint8                                         bFollowerShouldTickPose : 1;                       // 0x0902(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Transient, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected))
    uint8                                         Pad_903[0x1];                                      // 0x0903(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         CapsuleIndirectShadowMinVisibility;                // 0x0904(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_908[0x40];                                     // 0x0908(0x0040)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* CachedWorldOrLocalSpaceBounds;                     // 0x0948(0x0038)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, NativeAccessSpecifierProtected)
    uobject* CachedWorldToLocalTransform;                       // 0x0980(0x0080)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, NativeAccessSpecifierProtected)
    uobject* DedicatedServerAnimationStatus;                    // 0x0A00(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    uint8                                         Pad_A01[0x1F];                                     // 0x0A01(0x001F)(Fixing Struct Size After Last Property [ Dumper-7 ])


};


std::map<std::wstring, uobject*> g_TextureCache;

/* void RAHHTEXTURE(ashootercharacter* character, UPrimitiveComponent* Weapon, uworld* uworld, int variation, std::wstring weaponName) {

    currentequippable* Equippable = character->get_inventory()->get_current_equippable();
    if (!Equippable || !memory::IsValidPointer((uintptr_t)Equippable)) return;


    fstring weaponTexturePath;
    std::wstring cacheKey;

    if (weaponName == L"Vandal") {
        if (variation == 1) {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin1_tex.png").decrypt());
            cacheKey = crypt(L"Vandal1").decrypt();
        }
        else if (variation == 2) {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin3_tex.png").decrypt());
            cacheKey = crypt(L"Vandal2").decrypt();
        }
        else if (variation == 3) {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin4_tex.png").decrypt());
            cacheKey = crypt(L"Vandal3").decrypt();
        }
        else if (variation == 4) {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin5_tex.png").decrypt());
            cacheKey = crypt(L"Vandal4").decrypt();
        }
        else {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin1_tex.png").decrypt());
            cacheKey = crypt(L"Vandal1").decrypt();
        }
    }
    else if (weaponName == L"Phantom") {
        if (variation == 1) {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\phantom_skin1_tex.png").decrypt());
            cacheKey = crypt(L"Phantom1").decrypt();
        }
        else if (variation == 2) {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\phantom_skin2_tex.png").decrypt());
            cacheKey = crypt(L"Phantom2").decrypt();
        }
        else if (variation == 3) {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\phantom_skin3_tex.png").decrypt());
            cacheKey = crypt(L"Phantom3").decrypt();
        }
        else {
            weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\phantom_skin1_tex.png").decrypt());
            cacheKey = crypt(L"Phantom1").decrypt();
        }
    }
    else if (weaponName == L"Melee") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\bicak_tex.png").decrypt());
        cacheKey = crypt(L"Melee").decrypt();
    }
    else if (weaponName == L"Sheriff") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Sheriff.png").decrypt());
        cacheKey = crypt(L"Sheriff").decrypt();
    }
    else if (weaponName == L"Operator") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Operator.png").decrypt());
        cacheKey = crypt(L"Operator").decrypt();
    }
    else if (weaponName == L"Frenzy") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\frenzy_tex.png").decrypt());
        cacheKey = crypt(L"Frenzy").decrypt();
    }
    else if (weaponName == L"Bulldog") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Bulldog.png").decrypt());
        cacheKey = crypt(L"Bulldog").decrypt();
    }
    else if (weaponName == L"Spectre") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\spectre.png").decrypt());
        cacheKey = crypt(L"Spectre").decrypt();
    }
    else if (weaponName == L"Guardian") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Guardian.png").decrypt());
        cacheKey = crypt(L"Guardian").decrypt();
    }
    else if (weaponName == L"Marshal") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Marshal.jpg").decrypt());
        cacheKey = crypt(L"Marshal").decrypt();
    }
    else if (weaponName == L"Ghost") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\ghost.png").decrypt());
        cacheKey = crypt(L"Ghost").decrypt();
    }
    else if (weaponName == L"Classic") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Classic.png").decrypt());
        cacheKey = crypt(L"Classic").decrypt();
    }
    else if (weaponName == L"Judge") {
        weaponTexturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Judge.png").decrypt());
        cacheKey = crypt(L"Judge").decrypt();
    }

    uobject* WeaponTexture = nullptr;
    auto cacheIt = g_TextureCache.find(cacheKey);
    if (cacheIt != g_TextureCache.end() && memory::IsValidPointer((uintptr_t)cacheIt->second)) {
        WeaponTexture = cacheIt->second;
    }
    else {
        WeaponTexture = drawings::ImportFileAsTexture2D(uworld, weaponTexturePath);
        if (WeaponTexture && memory::IsValidPointer((uintptr_t)WeaponTexture)) {
            g_TextureCache[cacheKey] = WeaponTexture;
        }
    }

    UPrimitiveComponent* GunMesh1P = Weapon;
    if (GunMesh1P && memory::IsValidPointer((uintptr_t)GunMesh1P))
    {
        int32_t numMaterials = GunMesh1P->GetNumMaterials();
        for (int32_t i = 0; i < numMaterials; i++)
        {
            uobject* existingMaterial = GunMesh1P->get_material(i);
            if (!existingMaterial || !memory::IsValidPointer((uintptr_t)existingMaterial)) return;

            uobject* GunDynamicMat = GunMesh1P->create_and_set_material_instance_dynamic_from_material(i, existingMaterial);
            if (GunDynamicMat && memory::IsValidPointer((uintptr_t)GunDynamicMat))
            {
                auto* mat = GunDynamicMat->cast<UMaterialInstanceDynamic>();
                if (mat)
                {

                    const wchar_t* pNames[] = { L"BaseColor", L"Diffuse", L"Albedo", L"Texture" };
                    for (const auto& param : pNames)
                    {
                        mat->set_texture_parameter_value2(string::string_to_name(param), WeaponTexture);
                    }
                    mat->set_scalar_parameter_value2(string::string_to_name(L"TwoSided"), 1.0f);

                }
            }
        }
    }
}*/

//
//bool IsOtherActorVisible(AActor* TargetActor)
//{
//    if (!TargetActor) return false;
//
//    fvector PlayerViewLocation;
//    frotator PlayerViewRotation;
//    controller->GetPlayerViewPoint(PlayerViewLocation, PlayerViewRotation);
//
//    fvector TargetLocation = TargetActor->K2_GetActorLocation();
//    fvector Direction = TargetLocation - PlayerViewLocation;
//    fvector TraceEnd = PlayerViewLocation + Direction * 1.0f;
//
//    FCollisionQueryParams TraceParams(FName(TEXT("VisibilityCheck")), true, PlayerPawn);
//    TraceParams.bTraceComplex = true;
//    TraceParams.bReturnPhysicalMaterial = false;
//
//    FHitResult HitResult;
//
//    bool bHit = World->LineTraceSingleByChannel(
//        HitResult,
//        PlayerViewLocation,
//        TraceEnd,
//        ECC_Visibility,
//        TraceParams
//    );
//
//    if (!bHit) return false;
//
//    AActor* HitActor = HitResult.GetActor();
//    if (!HitActor) return false;
//
//    if (HitActor == TargetActor)
//    {
//        return true;
//    }
//
//    return false;
//
//}
//void ReplaceWeaponMeshWith3DModelTextOnly(currentequippable* Weapon, const char* objFilePath) {
//    if (!Weapon || !Weapon->GetMesh1P()) {
//        return;
//    }
//
//    auto* OriginalMesh = Weapon->GetMesh1P();
//
//    // Get weapon name to use as key for storing models per weapon
//    std::string weapon_name = get_cached_name(Weapon);
//
//    static uclass* ProcMeshClass = nullptr;
//    if (!ProcMeshClass) {
//        UObject* FoundObj = UObject::find_object<UObject>(L"ProceduralMeshComponent.ProceduralMeshComponent");
//        ProcMeshClass = (uclass*)FoundObj;
//        if (!ProcMeshClass) return;
//    }
//
//    UProceduralMeshComponent* ProcMesh = nullptr;
//    auto it = globals::misc::text_model_meshes.find(weapon_name);
//    if (it != globals::misc::text_model_meshes.end() && memory::IsValidPointer((uintptr_t)it->second)) {
//        ProcMesh = (UProceduralMeshComponent*)it->second;
//    }
//
//    if (!ProcMesh || !memory::IsValidPointer((uintptr_t)ProcMesh)) {
//        static uobject* AddComponentFunc = nullptr;
//        if (!AddComponentFunc) {
//            AddComponentFunc = uobject::find_object<uobject*>(L"ShooterGame.ShooterBlueprintLibrary.AddComponentByClass");
//            if (!AddComponentFunc) return;
//        }
//
//        struct AddComponentParams {
//            AActor* Actor;
//            UActorComponent* ComponentClass;
//            UActorComponent* ReturnValue;
//        };
//        AddComponentParams Params;
//        Params.Actor = (AActor*)Weapon;
//        Params.ComponentClass = (UActorComponent*)ProcMeshClass;
//        Params.ReturnValue = nullptr;
//
//        variables.blueprints->process_event(AddComponentFunc, &Params);
//
//        ProcMesh = (UProceduralMeshComponent*)Params.ReturnValue;
//        if (ProcMesh) {
//            globals::misc::text_model_meshes[weapon_name] = (void*)ProcMesh;
//            // Also update the global reference for color updates (backward compatibility)
//            globals::misc::text_model_proc_mesh = (void*)ProcMesh;
//        }
//    }
//
//    if (!ProcMesh) return;
//
//    MeshData weaponMesh = ParseOBJFile(objFilePath);
//    if (weaponMesh.Vertices.Num() == 0) return;
//
//    for (int i = 0; i < weaponMesh.Normals.Num(); i++) {
//        weaponMesh.Normals[i] = weaponMesh.Normals[i] * -1.0f;
//    }
//
//    for (int i = 0; i < weaponMesh.Triangles.Num(); i += 3) {
//        int32_t temp = weaponMesh.Triangles[i + 1];
//        weaponMesh.Triangles[i + 1] = weaponMesh.Triangles[i + 2];
//        weaponMesh.Triangles[i + 2] = temp;
//    }
//
//    if (weaponMesh.VertexColors.Num() == 0) {
//        for (int i = 0; i < weaponMesh.Vertices.Num(); i++) {
//            FColor whiteColor;
//            whiteColor.R = 255;
//            whiteColor.G = 255;
//            whiteColor.B = 255;
//            whiteColor.A = 255;
//            weaponMesh.VertexColors.Add(whiteColor);
//        }
//    }
//
//    static uobject* ClearMeshSectionFunc = nullptr;
//    if (!ClearMeshSectionFunc) {
//        ClearMeshSectionFunc = uobject::find_object<uobject*>(L"ProceduralMeshComponent.ProceduralMeshComponent.ClearMeshSection");
//    }
//    if (ClearMeshSectionFunc) {
//        struct ClearMeshParams {
//            int32_t SectionIndex;
//        };
//        ClearMeshParams ClearParams;
//        ClearParams.SectionIndex = 0;
//        ((uobject*)ProcMesh)->process_event(ClearMeshSectionFunc, &ClearParams);
//    }
//
//    static uobject* CreateMeshFunc = nullptr;
//    if (!CreateMeshFunc) {
//        CreateMeshFunc = uobject::find_object<uobject*>(L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection");
//        if (!CreateMeshFunc) return;
//    }
//
//    struct CreateMeshParams {
//        int32_t SectionIndex;
//        tarray<fvector> Vertices;
//        tarray<int32_t> Triangles;
//        tarray<fvector> Normals;
//        tarray<fvector2d> UV0;
//        tarray<FColor> VertexColors;
//        tarray<FProcMeshTangent> Tangents;
//        bool bCreateCollision;
//    };
//    CreateMeshParams CreateParams;
//    CreateParams.SectionIndex = 0;
//    CreateParams.Vertices = weaponMesh.Vertices;
//    CreateParams.Triangles = weaponMesh.Triangles;
//    CreateParams.Normals = weaponMesh.Normals;
//    CreateParams.UV0 = weaponMesh.UV0;
//    CreateParams.VertexColors = weaponMesh.VertexColors;
//    CreateParams.Tangents = weaponMesh.Tangents;
//    CreateParams.bCreateCollision = false;
//
//    ((uobject*)ProcMesh)->process_event(CreateMeshFunc, &CreateParams);
//
//    static uobject* material = uobject::StaticLoadObject(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Blue_MI.Arcade_Emissive_Blue_MI");
//    static fname baseColorName = string::string_to_name(L"Base Color");
//    static fname emissiveColorName = string::string_to_name(L"Emissive Color");
//    static float rainbowTimeZTextModel = 0.0f;
//
//    if (material) {
//        UPrimitiveComponent* ProcMeshPrimitive = (UPrimitiveComponent*)ProcMesh;
//
//        flinearcolor color;
//        color = flinearcolor{ 255.0f, 255.0f, 255.0f, 1.0f };
//       
//        static uobject* GetNumMaterialsFunc = nullptr;
//        if (!GetNumMaterialsFunc) {
//            GetNumMaterialsFunc = uobject::find_object<uobject*>(L"Engine.MeshComponent.GetNumMaterials");
//        }
//
//        int32_t numMaterials = 1;
//        if (GetNumMaterialsFunc) {
//            struct GetNumMaterialsParams {
//                int32_t ReturnValue;
//            };
//            GetNumMaterialsParams NumMatParams;
//            NumMatParams.ReturnValue = 0;
//            ((uobject*)ProcMesh)->process_event(GetNumMaterialsFunc, &NumMatParams);
//            numMaterials = NumMatParams.ReturnValue;
//            if (numMaterials == 0) numMaterials = 1;
//        }
//
//        for (int32_t i = 0; i < numMaterials; i++) {
//            if (auto dynMat = ProcMeshPrimitive->create_and_set_material_instance_dynamic_from_material(i, material)) {
//                auto matInst = dynMat->cast<UMaterialInstanceDynamic>();
//                if (!matInst) continue;
//
//                matInst->set_vector_parameter_value2(baseColorName, color);
//                matInst->set_vector_parameter_value2(emissiveColorName, color);
//            }
//        }
//    }
//
//    static uobject* AttachFunc = nullptr;
//    if (!AttachFunc) {
//        AttachFunc = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_AttachToComponent");
//    }
//    fname socketName = string::string_to_name(L"R_WeaponPoint");
//    if (AttachFunc) {
//        struct AttachParams {
//            USceneComponent* Parent;
//            int LocationRule;
//            int RotationRule;
//            int ScaleRule;
//            fname SocketName;
//            bool bWeldSimulatedBodies;
//        };
//        AttachParams AttachParamsData;
//        AttachParamsData.Parent = (USceneComponent*)OriginalMesh;
//        AttachParamsData.LocationRule = 2; 
//        AttachParamsData.RotationRule = 2; 
//        AttachParamsData.ScaleRule = 1;
//        AttachParamsData.SocketName = socketName;
//        AttachParamsData.bWeldSimulatedBodies = false;
//        ((uobject*)ProcMesh)->process_event(AttachFunc, &AttachParamsData);
//    }
//
// 
//    fvector location = fvector(globals::misc::text_model_pos_x, globals::misc::text_model_pos_y, globals::misc::text_model_pos_z);
//    frotator rotation = frotator(0, 0, -90); 
//    fvector scale = fvector(1.5, 1.5, 1.5);
//
//    static uobject* SetRelativeScale3DFunc = nullptr;
//    if (!SetRelativeScale3DFunc) {
//        SetRelativeScale3DFunc = uobject::find_object<uobject*>(L"Engine.SceneComponent.SetRelativeScale3D");
//    }
//    if (SetRelativeScale3DFunc) {
//        struct ScaleParams {
//            fvector NewScale3D;
//        };
//        ScaleParams ScaleParamsData;
//        ScaleParamsData.NewScale3D = scale;
//        ((uobject*)ProcMesh)->process_event(SetRelativeScale3DFunc, &ScaleParamsData);
//    }
//
//
//    static uobject* K2_SetRelativeRotationFunc = nullptr;
//    if (!K2_SetRelativeRotationFunc) {
//        K2_SetRelativeRotationFunc = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_SetRelativeRotation");
//    }
//    if (K2_SetRelativeRotationFunc) {
//        struct RotParams {
//            frotator NewRotation;
//            bool bSweep;
//            FHitResult SweepHitResult;
//            bool bTeleport;
//        };
//        RotParams RotParamsData;
//        RotParamsData.NewRotation = rotation;
//        RotParamsData.bSweep = false;
//        RotParamsData.bTeleport = true;
//        ((uobject*)ProcMesh)->process_event(K2_SetRelativeRotationFunc, &RotParamsData);
//    }
//
//    static uobject* SetRelativeLocationFunc = nullptr;
//    if (!SetRelativeLocationFunc) {
//        SetRelativeLocationFunc = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_SetRelativeLocation");
//    }
//    if (SetRelativeLocationFunc) {
//        struct LocParams {
//            fvector NewLocation;
//            bool bSweep;
//            FHitResult SweepHitResult;
//            bool bTeleport;
//        };
//        LocParams LocParamsData;
//        LocParamsData.NewLocation = location;
//        LocParamsData.bSweep = false;
//        LocParamsData.bTeleport = true;
//        ((uobject*)ProcMesh)->process_event(SetRelativeLocationFunc, &LocParamsData);
//    }
//
//    static uobject* SetCollisionEnabledFunc = nullptr;
//    if (!SetCollisionEnabledFunc) {
//        SetCollisionEnabledFunc = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetCollisionEnabled");
//    }
//    if (SetCollisionEnabledFunc) {
//        struct CollisionParams {
//            int32_t NewType; 
//        };
//        CollisionParams CollisionParamsData;
//        CollisionParamsData.NewType = 0; 
//        ((uobject*)ProcMesh)->process_event(SetCollisionEnabledFunc, &CollisionParamsData);
//    }
//
//
//    static uobject* SetCastShadowFunc = nullptr;
//    if (!SetCastShadowFunc) {
//        SetCastShadowFunc = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetCastShadow");
//    }
//    if (SetCastShadowFunc) {
//        struct CastShadowParams {
//            bool bNewCastShadow;
//        };
//        CastShadowParams CastShadowParamsData;
//        CastShadowParamsData.bNewCastShadow = false; // Disable shadow casting
//        ((uobject*)ProcMesh)->process_event(SetCastShadowFunc, &CastShadowParamsData);
//    }
//
//    static uobject* SetReceiveShadowFunc = nullptr;
//    if (!SetReceiveShadowFunc) {
//        SetReceiveShadowFunc = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetReceiveShadow");
//    }
//    if (SetReceiveShadowFunc) {
//        struct ReceiveShadowParams {
//            bool bNewReceiveShadow;
//        };
//        ReceiveShadowParams ReceiveShadowParamsData;
//        ReceiveShadowParamsData.bNewReceiveShadow = false; 
//        ((uobject*)ProcMesh)->process_event(SetReceiveShadowFunc, &ReceiveShadowParamsData);
//    }
//
//    static uobject* SetCollisionResponseToAllChannelsFunc = nullptr;
//    if (!SetCollisionResponseToAllChannelsFunc) {
//        SetCollisionResponseToAllChannelsFunc = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetCollisionResponseToAllChannels");
//    }
//    if (SetCollisionResponseToAllChannelsFunc) {
//        struct CollisionResponseParams {
//            int32_t NewResponse; 
//        };
//        CollisionResponseParams CollisionResponseParamsData;
//        CollisionResponseParamsData.NewResponse = 0; 
//        ((uobject*)ProcMesh)->process_event(SetCollisionResponseToAllChannelsFunc, &CollisionResponseParamsData);
//    }
//
//
//    globals::misc::text_model_proc_mesh = (void*)ProcMesh;
//    static uobject* SetVisibilityFunc = nullptr;
//    if (!SetVisibilityFunc) {
//        SetVisibilityFunc = uobject::find_object<uobject*>(L"Engine.SceneComponent.SetVisibility");
//    }
//
//    if (SetVisibilityFunc) {
//        struct VisParams {
//            bool bNewVisibility;
//            bool bPropagateToChildren;
//        };
//        VisParams VisParamsData;
//
//        VisParamsData.bNewVisibility = true;
//        VisParamsData.bPropagateToChildren = false;
//        ((uobject*)ProcMesh)->process_event(SetVisibilityFunc, &VisParamsData);
//    }
//
//    static uobject* RegisterFunc = nullptr;
//    if (!RegisterFunc) {
//        RegisterFunc = uobject::find_object<uobject*>(L"Engine.ActorComponent.RegisterComponent");
//    }
//    if (RegisterFunc) {
//        ((uobject*)ProcMesh)->process_event(RegisterFunc, nullptr);
//    }
//}

class APostProcessVolume final : public uobject
{
public:
    char                                         Pad_498[0x8];                                      // 0x0498(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
     uobject*                   Settings;                                          // 0x04A0(0x0800)(Edit, BlueprintVisible, Interp, NativeAccessSpecifierPublic)
    float                                         Priority;                                          // 0x0CA0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         BlendRadius;                                       // 0x0CA4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         BlendWeight;                                       // 0x0CA8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         bEnabled : 1;                                      // 0x0CAC(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bUnbound : 1;                                      // 0x0CAC(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         Pad_CAD[0x3];                                      // 0x0CAD(0x0003)(Fixing Struct Size After Last Property [ Dumper-7 ])ultObjImpl<APostProcessVolume>();
   
};


void PPVolume_AddOrUpdateBlendable(APostProcessVolume* PPVolume, uobject* InBlendableObject, float InWeight) {
    static auto fn = uobject::find_object<uobject*>(L"Engine.PostProcessVolume.AddOrUpdateBlendable");
    struct {
        uobject* ObjectPointer;
        uobject* InterfacePointer;
        float InWeight;
    } params;
    params.ObjectPointer = InBlendableObject;
    params.InterfacePointer = InBlendableObject;
    params.InWeight = InWeight;
    ((uobject*)PPVolume)->process_event(fn, &params);
}

void PPVolume_RemoveBlendable(APostProcessVolume* PPVolume, uobject* InBlendableObject) {
    static auto fn = uobject::find_object<uobject*>(L"Engine.PostProcessVolume.RemoveBlendable");
    struct {
        uobject* ObjectPointer;
        uobject* InterfacePointer;
    } params;
    params.ObjectPointer = InBlendableObject;
    params.InterfacePointer = InBlendableObject;
    ((uobject*)PPVolume)->process_event(fn, &params);
}

static APostProcessVolume* CachedPPVolume = nullptr;
static bool bChampionsAttached = false;
APostProcessVolume* FindPostProcessVolume(uobject* World) {
    tarray<AGameObject*> Objects;
    GameplayStatics::GetAllActorsOfClass2(UWorldSave, Class::Actors(), &Objects);

    APostProcessVolume* BestVolume = nullptr;
    float BestPriority = -FLT_MAX;

    for (int i = 0; i < Objects.size(); i++) {
        AGameObject* Obj = Objects[i];
        if (!IsValidPtr(Obj) || !memory::IsValidPointer((uintptr_t)Obj)) continue;

        auto name = system::get_object_name((uobject*)Obj);
        if (!name.is_valid()) continue;

        if (name.ToString().find("PostProcessVolume") != std::string::npos) {
            APostProcessVolume* PPVol = (APostProcessVolume*)Obj;
            if (!memory::IsValidPointer((uintptr_t)PPVol)) continue;

            if (PPVol->bUnbound) {
                BestVolume = PPVol;
                break;
            }
            if (PPVol->Priority > BestPriority) {
                BestPriority = PPVol->Priority;
                BestVolume = PPVol;
            }
        }
    }

    if (BestVolume)
        CachedPPVolume = BestVolume;

    return CachedPPVolume;

}
class UMaterialParameterCollection final : public uobject
{
public:
    uobject* StateId;                                           // 0x0030(0x0010)(ZeroConstructor, DuplicateTransient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    tarray<uobject*>     ScalarParameters;                                  // 0x0040(0x0010)(Edit, ZeroConstructor, NativeAccessSpecifierPublic)
    TArray<uobject*>     VectorParameters;                                  // 0x0050(0x0010)(Edit, ZeroConstructor, NativeAccessSpecifierPublic)
    char                                         Pad_60[0x18];                                      // 0x0060(0x0018)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

static bool g_ChampionsAttached;
void AttachApocalypseMode(ashootercharacter* Player) {
    if (g_ChampionsAttached) return;

    auto particlePath = L"/Game/Equippables/Finishers/Champions/VFX/Champions_SkySphere_PP_VFX.Champions_SkySphere_PP_VFX";
    uobject* particle = uobject::find_object< uobject*>(particlePath);
    if (!IsValidPtr(particle)) uobject::StaticLoadObject(particlePath);
    particle = uobject::find_object< uobject*>(particlePath);

    if (IsValidPtr(particle)) {
        fvector PlayerPos = Player->k2_get_actor_location();
        GameplayStatics::SpawnEmitterAtLocationWithWorld(
            UWorld2::GetWorld(), (UParticleSystem*)particle,
            { PlayerPos.x, PlayerPos.y, PlayerPos.z + 5000.0f },
            frotator(0, 0, 0), fvector(500, 500, 500),
            true, EPSCPoolMethod::None, true, false, 0.0f
        );
    }


    APostProcessVolume* PPVolume = FindPostProcessVolume(UWorldSave);
    if (!PPVolume) return;

    auto matPath = L"/Game/Equippables/Finishers/Champions/VFX/Champions_BrimsExp_PP_MI.Champions_BrimsExp_PP_MI";
    static uobject* material = nullptr;
    if (!IsValidPtr(material)) {
        material = uobject::find_object<uobject*>(matPath);
        if (!IsValidPtr(material)) uobject::StaticLoadObject(matPath);
        material = uobject::find_object< uobject*>(matPath);
    }
    if (!IsValidPtr(material)) return;

    PPVolume->bEnabled = true;
    PPVolume->bUnbound = true;
    PPVolume->BlendWeight = 1.0f;
    PPVolume_AddOrUpdateBlendable(PPVolume, material, 1.0f);

    auto* Col = (UMaterialParameterCollection*)uobject::find_object< uobject*>(L"/Game/Equippables/Finishers/Champions/VFX/Champions_Finisher_COL.Champions_Finisher_COL");
    if (!IsValidPtr(Col)) UObject::StaticLoadObject(L"/Game/Equippables/Finishers/Champions/VFX/Champions_Finisher_COL.Champions_Finisher_COL");
    Col = (UMaterialParameterCollection*)uobject::find_object< uobject*>(L"/Game/Equippables/Finishers/Champions/VFX/Champions_Finisher_COL.Champions_Finisher_COL");
    if (IsValidPtr(Col)) {
        fvector PlayerPos = Player->k2_get_actor_location();

       
        flinearcolor loc{ (float)PlayerPos.x, (float)PlayerPos.y, (float)PlayerPos.z, 0.f };
        Col->set_vector_parameter_value2(string::string_to_name(L"Location"), loc);
        Col->set_scalar_parameter_value2(string::string_to_name(L"Radius"), 99999.0f);
        Col->set_scalar_parameter_value2(string::string_to_name(L"MainOpacity"), 1.f);
        Col->set_scalar_parameter_value2(string::string_to_name(L"R"), 1.0f);

        Col->set_scalar_parameter_value2(string::string_to_name(L"G"), 0.0f);

        Col->set_scalar_parameter_value2(string::string_to_name(L"B"), 0.0f);

    }

    bChampionsAttached = true;
    g_ChampionsAttached = true;


} 
static std::map<uintptr_t, uintptr_t> WeaponMeshCache;          // Maps weapon ptr -> procedural mesh ptr
static std::map<std::string, MeshData> LoadedMeshCache;         // Maps file path -> parsed mesh data
static std::map<std::string, uobject*> LoadedTextureCache;      // Maps texture path -> texture
static std::map<uintptr_t, uintptr_t> WeaponTextMeshCache;      // Maps weapon ptr -> text mesh ptr

static std::map<std::string, MeshData> ModelCache;
static uintptr_t LastWeaponProcessed = 0;
static uobject* LastWorldPtr = nullptr;

static std::map<uintptr_t, bool> WeaponHasCustomMesh;
static std::map<uintptr_t, UProceduralMeshComponent*> WeaponTextMeshMap;

static bool text_meshcreated = false;
static UProceduralMeshComponent* TextMesh = nullptr;


struct WeaponTransform {
    fvector position;
    frotator rotation;
    fvector scale;
};

UProceduralMeshComponent* ProcMesh1P;
void ReplaceWeaponMeshWith3DModel(
    currentequippable* Weapon,
    const char* objFilePath,
    ashootercharacter* character,
    uworld* world,
    int variation,
    std::wstring weaponName
)
{
    if (!Weapon) return;

    auto* OriginalMesh1P = Weapon->GetMesh1P();
    if (OriginalMesh1P)
    {
        uintptr_t key1P = (uintptr_t)OriginalMesh1P;

        static uobject* SetVisibilityFunc =
            uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.SetVisibility").decrypt());

        auto it1P = g_ProcMeshCache.find(key1P);
        if (it1P != g_ProcMeshCache.end())
        {
            struct { bool v; bool p; } vp{ false, true };
            OriginalMesh1P->process_event(SetVisibilityFunc, &vp);

            struct { bool v; bool p; } vp2{ true, true };
            it1P->second->process_event(SetVisibilityFunc, &vp2);
            static uobject* RegisterFunc = nullptr;
            if (!RegisterFunc)
            {
                RegisterFunc = uobject::find_object<uobject*>(L"Engine.ActorComponent.RegisterComponent");
            }

            if (RegisterFunc)
            {
                ((uobject*)ProcMesh1P)->process_event(RegisterFunc, nullptr);
            }
        }
        else
        {
            static uclass* ProcMeshClass =
                uobject::find_object<uclass*>(crypt(L"ProceduralMeshComponent.ProceduralMeshComponent").decrypt());
            if (!ProcMeshClass) return;

            static uobject* AddComponentFunc =
                uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.AddComponentByClass").decrypt());
            if (!AddComponentFunc) return;

            struct {
                AActor* Actor;
                UActorComponent* ComponentClass;
                UActorComponent* ReturnValue;
            } AddParams{ (AActor*)Weapon, (UActorComponent*)ProcMeshClass, nullptr };

            variables.blueprints->process_event(AddComponentFunc, &AddParams);

            ProcMesh1P = (UProceduralMeshComponent*)AddParams.ReturnValue;
            if (!ProcMesh1P) return;

            MeshData mesh = ParseOBJFile(objFilePath);
            if (mesh.Vertices.Num() == 0) return;

            for (auto& normal : mesh.Normals)
                normal *= -1.0f;

            for (int i = 0; i < mesh.Triangles.Num(); i += 3)
                std::swap(mesh.Triangles[i + 1], mesh.Triangles[i + 2]);

            if (mesh.VertexColors.Num() == 0)
            {
                for (int i = 0; i < mesh.Vertices.Num(); i++)
                    mesh.VertexColors.Add(FColor(255, 255, 255, 255));
            }

            static uobject* CreateMeshFunc =
                uobject::find_object<uobject*>(crypt(L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection").decrypt());

            struct {
                int32_t SectionIndex;
                tarray<fvector> Vertices;
                tarray<int32_t> Triangles;
                tarray<fvector> Normals;
                tarray<fvector2d> UV0;
                tarray<FColor> VertexColors;
                tarray<FProcMeshTangent> Tangents;
                bool bCreateCollision;
            } CreateParams{
                0,
                mesh.Vertices,
                mesh.Triangles,
                mesh.Normals,
                mesh.UV0,
                mesh.VertexColors,
                mesh.Tangents,
                false
            };

            ProcMesh1P->process_event(CreateMeshFunc, &CreateParams);
            //RAHHTEXTURE(character, (UPrimitiveComponent*)OriginalMesh1P, world, variation, weaponName);

            static uobject* GetMaterialFunc =
                uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.GetMaterial").decrypt());
            static uobject* SetMaterialFunc =
                uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetMaterial").decrypt());
            if (GetMaterialFunc && SetMaterialFunc)
            {
                struct { int32_t ElementIndex; UMaterialInterface* ReturnValue; } GetMatParams{ 0, nullptr };
                OriginalMesh1P->process_event(GetMaterialFunc, &GetMatParams);

                if (GetMatParams.ReturnValue)
                {
                    struct { int32_t ElementIndex; UMaterialInterface* Material; }
                    SetMatParams{ 0, GetMatParams.ReturnValue };

                    ProcMesh1P->process_event(SetMaterialFunc, &SetMatParams);
                }
            }

            static uobject* CalcTangentsFunc =
                uobject::find_object<uobject*>(
                    crypt(L"ProceduralMeshComponent.K2_CalculateTangentsForMesh").decrypt()
                );

            if (CalcTangentsFunc)
            {
                struct
                {
                    tarray<fvector> Vertices;
                    tarray<int32_t> Triangles;
                    tarray<fvector2d> UVs;
                    tarray<fvector> Normals;
                    tarray<FProcMeshTangent> Tangents;
                } TangentParams{
                    mesh.Vertices,
                    mesh.Triangles,
                    mesh.UV0,
                    mesh.Normals,
                    mesh.Tangents
                };

                ProcMesh1P->process_event(CalcTangentsFunc, &TangentParams);

                struct {
                    int32_t SectionIndex;
                    tarray<fvector> Vertices;
                    tarray<int32_t> Triangles;
                    tarray<fvector> Normals;
                    tarray<fvector2d> UV0;
                    tarray<FColor> VertexColors;
                    tarray<FProcMeshTangent> Tangents;
                    bool bCreateCollision;
                } UpdateParams{
                    0,
                    mesh.Vertices,
                    mesh.Triangles,
                    TangentParams.Normals,
                    mesh.UV0,
                    mesh.VertexColors,
                    TangentParams.Tangents,
                    false
                };

                ProcMesh1P->process_event(CreateMeshFunc, &UpdateParams);
            }

            static uobject* AttachFunc =
                uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_AttachToComponent").decrypt());

            fname Socket = string::string_to_name(crypt(L"R_WeaponPoint").decrypt());

            struct {
                USceneComponent* Parent;
                EAttachmentRule Rule;
                fname SocketName;
            } AttachParams{ (USceneComponent*)OriginalMesh1P, EAttachmentRule::SnapToTarget, Socket };

            ProcMesh1P->process_event(AttachFunc, &AttachParams);

            struct { bool v; bool p; } vp{ false, true };
            OriginalMesh1P->process_event(SetVisibilityFunc, &vp);

            struct { bool v; bool p; } vp3{ true, true };
            ProcMesh1P->process_event(SetVisibilityFunc, &vp3);

            static uobject* RegisterFunc = nullptr;
            if (!RegisterFunc) {
                RegisterFunc = uobject::find_object<uobject*>(L"Engine.ActorComponent.RegisterComponent");
            }
            if (RegisterFunc) {
                ((uobject*)ProcMesh1P)->process_event(RegisterFunc, nullptr);
            }
            else
            {
                ProcMesh1P->SetRelativeScale3D1(fvector(1.5f, 1.5f, 1.5f));
                ProcMesh1P->SetRelativeRotation1(frotator(0, 90, -90));
                ProcMesh1P->K2_AddRelativeLocation(
                    fvector(-0.9434f, 0.943392f, -2.83019f),
                    false, true);
            }

            meshcreated = true;
            g_ProcMeshCache[key1P] = ProcMesh1P;
        }
    }

    
}


// Cache structures
struct WeaponCacheData {
    uintptr_t weapon_ptr;
    std::wstring weapon_type;
    std::chrono::steady_clock::time_point last_processed_time;
    bool is_processing;
    int current_variation;
};

struct VariationCacheData {
    int variation;
    std::chrono::steady_clock::time_point timestamp;
};

// Global caches
static std::unordered_map<uintptr_t, WeaponCacheData> WeaponCache;
static std::unordered_map<std::wstring, uobject*> TextureCache;
static std::unordered_map<uintptr_t, uintptr_t> ProcMeshCache;
static std::unordered_map<uintptr_t, VariationCacheData> VariationCache;
static std::unordered_map<uintptr_t, uintptr_t> TextMeshCache;
static std::mutex CacheMutex;

// Existing statics
static uintptr_t last_applied_weapon_ptr = 0;
static bool is_processing_model = false;
static std::wstring last_processed_weapon_type = L"";
static uintptr_t last_character_ptr = 0;
static int model_load_counter = 0;

static uintptr_t saved_vandal_ptr = 0;
static uintptr_t saved_phantom_ptr = 0;
static uintptr_t saved_ghost_ptr = 0;
static uintptr_t saved_frenzy_ptr = 0;
static uintptr_t saved_melee_ptr = 0;

static int vandal_cycle_index = 0;
static int phantom_cycle_index = 0;
static int ghost_cycle_index = 0;
static int frenzy_cycle_index = 0;

void CleanWeaponCache() {
    std::lock_guard<std::mutex> lock(CacheMutex);
    auto now = std::chrono::steady_clock::now();
    static auto last_check = now;

    if (now - last_check < std::chrono::milliseconds(500))
        return;

    last_check = now;

    for (auto it = WeaponCache.begin(); it != WeaponCache.end();) {
        if (now - it->second.last_processed_time > std::chrono::seconds(5)) {
            it = WeaponCache.erase(it);
        }
        else {
            ++it;
        }
    }
}


void CleanVariationCache() {
    std::lock_guard<std::mutex> lock(CacheMutex);
    auto now = std::chrono::steady_clock::now();
    for (auto it = VariationCache.begin(); it != VariationCache.end();) {
        if (now - it->second.timestamp > std::chrono::seconds(30)) {
            it = VariationCache.erase(it);
        }
        else {
            ++it;
        }
    }
}

int GetWeaponVariation2(uintptr_t weapon_ptr, const std::wstring& weapon_type) {
    std::lock_guard<std::mutex> lock(CacheMutex);

    auto it = VariationCache.find(weapon_ptr);
    if (it != VariationCache.end()) {
        return it->second.variation;
    }

    int variation = 1;
    if (weapon_type == L"Vandal") {
        variation = (rand() % 4) + 1;
    }
    else if (weapon_type == L"Phantom") {
        variation = (rand() % 3) + 1;
    }

    VariationCacheData data;
    data.variation = variation;
    data.timestamp = std::chrono::steady_clock::now();
    VariationCache[weapon_ptr] = data;

    return variation;

}

/* void ApplyWeaponTexture(ashootercharacter* character, UPrimitiveComponent* WeaponMesh, uworld* world, int variation, std::wstring weaponName) {
    if (!character || !WeaponMesh || !world || !memory::IsValidPointer((uintptr_t)WeaponMesh)) return;

    auto inv = character->get_inventory();
    if (!inv || !memory::IsValidPointer((uintptr_t)inv)) return;

    currentequippable* Equippable = inv->get_current_equippable();
    if (!Equippable || !memory::IsValidPointer((uintptr_t)Equippable)) return;

    fstring texturePath;
    std::wstring cacheKey;

    if (weaponName == L"Vandal") {
        if (variation == 1) {
            texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin1_tex.png").decrypt());
            cacheKey = crypt(L"Vandal1").decrypt();
        }
        else if (variation == 2) {
            texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin3_tex.png").decrypt());
            cacheKey = crypt(L"Vandal2").decrypt();
        }
        else if (variation == 3) {
            texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin4_tex.png").decrypt());
            cacheKey = crypt(L"Vandal3").decrypt();
        }
        else if (variation == 4) {
            texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\vandal_skin5_tex.png").decrypt());
            cacheKey = crypt(L"Vandal4").decrypt();
        }
    }
    else if (weaponName == L"Phantom") {
        if (variation == 1) {
            texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\phantom_skin1_tex.png").decrypt());
            cacheKey = crypt(L"Phantom1").decrypt();
        }
        else if (variation == 2) {
            texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\phantom_skin2_tex.png").decrypt());
            cacheKey = crypt(L"Phantom2").decrypt();
        }
        else if (variation == 3) {
            texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\phantom_skin3_tex.png").decrypt());
            cacheKey = crypt(L"Phantom3").decrypt();
        }
    }
    else if (weaponName == L"Melee") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\bicak_tex.png").decrypt());
        cacheKey = crypt(L"Melee").decrypt();
    }
    else if (weaponName == L"Sheriff") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Sheriff.png").decrypt());
        cacheKey = crypt(L"Sheriff").decrypt();
    }
    else if (weaponName == L"Operator") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Operator.png").decrypt());
        cacheKey = crypt(L"Operator").decrypt();
    }
    else if (weaponName == L"Frenzy") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\frenzy_tex.png").decrypt());
        cacheKey = crypt(L"Frenzy").decrypt();
    }
    else if (weaponName == L"Bulldog") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Bulldog.png").decrypt());
        cacheKey = crypt(L"Bulldog").decrypt();
    }
    else if (weaponName == L"Spectre") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\spectre.png").decrypt());
        cacheKey = crypt(L"Spectre").decrypt();
    }
    else if (weaponName == L"Guardian") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Guardian.png").decrypt());
        cacheKey = crypt(L"Guardian").decrypt();
    }
    else if (weaponName == L"Marshal") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Marshal.jpg").decrypt());
        cacheKey = crypt(L"Marshal").decrypt();
    }
    else if (weaponName == L"Ghost") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\ghost.png").decrypt());
        cacheKey = crypt(L"Ghost").decrypt();
    }
    else if (weaponName == L"Classic") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Classic.png").decrypt());
        cacheKey = crypt(L"Classic").decrypt();
    }
    else if (weaponName == L"Judge") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\Judge.png").decrypt());
        cacheKey = crypt(L"Judge").decrypt();
    }
    else if (weaponName == L"Bucky") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\bucky_tex.png").decrypt());
        cacheKey = crypt(L"Bucky").decrypt();
    }
    else if (weaponName == L"Shorty") {
        texturePath = fstring(crypt(L"C:\\Windows\\INF\\CSGO\\shorty_tex.png").decrypt());
        cacheKey = crypt(L"Shorty").decrypt();
    }

    if (cacheKey.empty()) return;

    uobject* WeaponTexture = LoadTextureWithCache(cacheKey, texturePath, world);
    if (!WeaponTexture) return;

    if (!memory::IsValidPointer((uintptr_t)WeaponMesh)) return;

    int32_t numMaterials = WeaponMesh->GetNumMaterials();
    for (int32_t i = 0; i < numMaterials; i++) {
        uobject* existingMaterial = WeaponMesh->get_material(i);
        if (!existingMaterial || !memory::IsValidPointer((uintptr_t)existingMaterial)) continue;

        uobject* dynamicMat = WeaponMesh->create_and_set_material_instance_dynamic_from_material(i, existingMaterial);
        if (dynamicMat && memory::IsValidPointer((uintptr_t)dynamicMat)) {
            auto* mat = (UMaterialInstanceDynamic*)dynamicMat;
            if (mat) {
                const wchar_t* paramNames[] = { L"BaseColor", L"Diffuse", L"Albedo", L"Texture" };
                for (const auto& param : paramNames) {
                    mat->set_texture_parameter_value2(string::string_to_name(param), WeaponTexture);
                }
                mat->set_scalar_parameter_value2(string::string_to_name(L"TwoSided"), 1.0f);
            }
        }
    }
} */

void ReplaceWeaponMesh(
    currentequippable* Weapon,
    const char* objFilePath,
    ashootercharacter* character,
    uworld* world,
    int variation,
    std::wstring weaponName
) {
    if (!Weapon || !character || !world) return;
    if (!memory::IsValidPointer((uintptr_t)Weapon)) return;

    auto* OriginalMesh = Weapon->GetMesh1P();
    if (!OriginalMesh || !memory::IsValidPointer((uintptr_t)OriginalMesh)) return;

    uintptr_t meshKey = (uintptr_t)OriginalMesh;

    // Check cache first
    {
        std::lock_guard<std::mutex> lock(CacheMutex);
        auto cacheIt = ProcMeshCache.find(meshKey);
        if (cacheIt != ProcMeshCache.end()) {
            auto* cachedMesh = (UProceduralMeshComponent*)cacheIt->second;
            if (memory::IsValidPointer((uintptr_t)cachedMesh)) {
                static uobject* SetVisibilityFunc = uobject::find_object<uobject*>(
                    crypt(L"Engine.SceneComponent.SetVisibility").decrypt()
                );

                if (SetVisibilityFunc) {
                    struct { bool visible; bool propagate; } hideParams{ false, true };
                    OriginalMesh->process_event(SetVisibilityFunc, &hideParams);

                    struct { bool visible; bool propagate; } showParams{ true, true };
                    cachedMesh->process_event(SetVisibilityFunc, &showParams);

                    //ApplyWeaponTexture(character, (UPrimitiveComponent*)cachedMesh, world, variation, weaponName);
                }
                return;
            }
            else {
                ProcMeshCache.erase(cacheIt);
            }
        }
    }

    // Get required functions
    static uclass* ProcMeshClass = uobject::find_object<uclass*>(
        crypt(L"ProceduralMeshComponent.ProceduralMeshComponent").decrypt()
    );
    static uobject* AddComponentFunc = uobject::find_object<uobject*>(
        crypt(L"ShooterGame.ShooterBlueprintLibrary.AddComponentByClass").decrypt()
    );
    static uobject* CreateMeshFunc = uobject::find_object<uobject*>(
        crypt(L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection").decrypt()
    );
    static uobject* ClearMeshSectionFunc = uobject::find_object<uobject*>(
        L"ProceduralMeshComponent.ProceduralMeshComponent.ClearMeshSection"
    );
    static uobject* GetMaterialFunc = uobject::find_object<uobject*>(
        crypt(L"Engine.PrimitiveComponent.GetMaterial").decrypt()
    );
    static uobject* SetMaterialFunc = uobject::find_object<uobject*>(
        crypt(L"Engine.PrimitiveComponent.SetMaterial").decrypt()
    );
    static uobject* CalcTangentsFunc = uobject::find_object<uobject*>(
        crypt(L"ProceduralMeshComponent.K2_CalculateTangentsForMesh").decrypt()
    );
    static uobject* AttachFunc = uobject::find_object<uobject*>(
        crypt(L"Engine.SceneComponent.K2_AttachToComponent").decrypt()
    );
    static uobject* SetVisibilityFunc = uobject::find_object<uobject*>(
        crypt(L"Engine.SceneComponent.SetVisibility").decrypt()
    );
    static uobject* SetCollisionEnabledFunc = uobject::find_object<uobject*>(
        L"Engine.PrimitiveComponent.SetCollisionEnabled"
    );
    static uobject* SetCastShadowFunc = uobject::find_object<uobject*>(
        L"Engine.PrimitiveComponent.SetCastShadow"
    );
    static uobject* SetReceiveShadowFunc = uobject::find_object<uobject*>(
        L"Engine.PrimitiveComponent.SetReceiveShadow"
    );
    static uobject* SetCollisionResponseFunc = uobject::find_object<uobject*>(
        L"Engine.PrimitiveComponent.SetCollisionResponseToAllChannels"
    );
    static uobject* RegisterFunc = uobject::find_object<uobject*>(
        L"Engine.ActorComponent.RegisterComponent"
    );

    if (!ProcMeshClass || !AddComponentFunc || !CreateMeshFunc) return;

    // Parse mesh
    MeshData mesh = ParseOBJFile(objFilePath);
    if (mesh.Vertices.Num() == 0) return;

    // Process mesh data
    for (auto& normal : mesh.Normals) normal *= -1.0f;
    for (int i = 0; i < mesh.Triangles.Num(); i += 3)
        std::swap(mesh.Triangles[i + 1], mesh.Triangles[i + 2]);

    if (mesh.VertexColors.Num() == 0) {
        for (int i = 0; i < mesh.Vertices.Num(); i++)
            mesh.VertexColors.Add(FColor(255, 255, 255, 255));
    }

    // Add procedural mesh component
    struct AddComponentParams {
        AActor* Actor;
        UActorComponent* ComponentClass;
        UActorComponent* ReturnValue;
    } addParams{ (AActor*)Weapon, (UActorComponent*)ProcMeshClass, nullptr };

    variables.blueprints->process_event(AddComponentFunc, &addParams);

    auto* ProcMesh = (UProceduralMeshComponent*)addParams.ReturnValue;
    if (!ProcMesh || !memory::IsValidPointer((uintptr_t)ProcMesh)) return;

    // Clear existing mesh sections
    if (ClearMeshSectionFunc) {
        struct ClearMeshParams { int32_t SectionIndex; } clearParams{ 0 };
        ((uobject*)ProcMesh)->process_event(ClearMeshSectionFunc, &clearParams);
    }

    // Create mesh section
    struct CreateMeshParams {
        int32_t SectionIndex;
        tarray<fvector> Vertices;
        tarray<int32_t> Triangles;
        tarray<fvector> Normals;
        tarray<fvector2d> UV0;
        tarray<FColor> VertexColors;
        tarray<FProcMeshTangent> Tangents;
        bool bCreateCollision;
    } createParams{
        0,
        mesh.Vertices,
        mesh.Triangles,
        mesh.Normals,
        mesh.UV0,
        mesh.VertexColors,
        mesh.Tangents,
        false
    };

    ProcMesh->process_event(CreateMeshFunc, &createParams);

    // Apply texture
    // ApplyWeaponTexture(character, (UPrimitiveComponent*)ProcMesh, world, variation, weaponName);

    // Copy material from original
    if (GetMaterialFunc && SetMaterialFunc) {
        struct GetMaterialParams { int32_t ElementIndex; UMaterialInterface* ReturnValue; } getMatParams{ 0, nullptr };
        OriginalMesh->process_event(GetMaterialFunc, &getMatParams);

        if (getMatParams.ReturnValue) {
            struct SetMaterialParams { int32_t ElementIndex; UMaterialInterface* Material; } setMatParams{ 0, getMatParams.ReturnValue };
            ProcMesh->process_event(SetMaterialFunc, &setMatParams);
        }
    }

    // Calculate tangents
    if (CalcTangentsFunc) {
        struct TangentCalcParams {
            tarray<fvector> Vertices;
            tarray<int32_t> Triangles;
            tarray<fvector2d> UVs;
            tarray<fvector> Normals;
            tarray<FProcMeshTangent> Tangents;
        } tangentParams{
            mesh.Vertices,
            mesh.Triangles,
            mesh.UV0,
            mesh.Normals,
            mesh.Tangents
        };

        ProcMesh->process_event(CalcTangentsFunc, &tangentParams);

        struct UpdateMeshParams {
            int32_t SectionIndex;
            tarray<fvector> Vertices;
            tarray<int32_t> Triangles;
            tarray<fvector> Normals;
            tarray<fvector2d> UV0;
            tarray<FColor> VertexColors;
            tarray<FProcMeshTangent> Tangents;
            bool bCreateCollision;
        } updateParams{
            0,
            mesh.Vertices,
            mesh.Triangles,
            tangentParams.Normals,
            mesh.UV0,
            mesh.VertexColors,
            tangentParams.Tangents,
            false
        };

        ProcMesh->process_event(CreateMeshFunc, &updateParams);
    }

    // Attach to weapon point
    if (AttachFunc) {
        fname Socket = string::string_to_name(crypt(L"R_WeaponPoint").decrypt());
        struct AttachToParams {
            USceneComponent* Parent;
            int Rule;
            fname SocketName;
        } attachParams{ (USceneComponent*)OriginalMesh, 1, Socket };
        ProcMesh->process_event(AttachFunc, &attachParams);
    }

    // Set visibility
    if (SetVisibilityFunc) {
        struct { bool visible; bool propagate; } hideOriginal{ false, true };
        OriginalMesh->process_event(SetVisibilityFunc, &hideOriginal);

        struct { bool visible; bool propagate; } showNew{ true, true };
        ProcMesh->process_event(SetVisibilityFunc, &showNew);
    }

    // Disable collision and shadows
    if (SetCollisionEnabledFunc) {
        struct CollisionParams { int32_t NewType; } collisionParams{ 0 };
        ((uobject*)ProcMesh)->process_event(SetCollisionEnabledFunc, &collisionParams);
    }

    if (SetCastShadowFunc) {
        struct ShadowParams { bool bNewCastShadow; } shadowParams{ false };
        ((uobject*)ProcMesh)->process_event(SetCastShadowFunc, &shadowParams);
    }

    if (SetReceiveShadowFunc) {
        struct ReceiveShadowParams { bool bNewReceiveShadow; } receiveParams{ false };
        ((uobject*)ProcMesh)->process_event(SetReceiveShadowFunc, &receiveParams);
    }

    if (SetCollisionResponseFunc) {
        struct ResponseParams { int32_t NewResponse; } responseParams{ 0 };
        ((uobject*)ProcMesh)->process_event(SetCollisionResponseFunc, &responseParams);
    }

    if (RegisterFunc) {
        ((uobject*)ProcMesh)->process_event(RegisterFunc, nullptr);
    }

    // Set transforms
    else {
        ProcMesh->SetRelativeScale3D1(fvector(1.5f, 1.5f, 1.5f));
        ProcMesh->SetRelativeRotation1(frotator(0, 90, -90));
        ProcMesh->K2_AddRelativeLocation(
            fvector(-0.9434f, 0.943392f, -2.83019f),
            false, true);
    }
    {
        std::lock_guard<std::mutex> lock(CacheMutex);
        ProcMeshCache[meshKey] = (uintptr_t)ProcMesh;
    }
}





// Smoke detection system using LineTraceSingle
// Smoke detection system using LineTraceSingle

class USkyLightComponent final : public uobject
{
public:
    bool                                          bRealTimeCapture;                                  // 0x0378(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uobject*                           SourceType;                                        // 0x0379(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_37A[0x6];                                      // 0x037A(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* Cubemap;                                  // 0x0380(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         SourceCubemapAngle;                                // 0x0388(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    int32                                         CubemapResolution;                                 // 0x038C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         SkyDistanceThreshold;                              // 0x0390(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bCaptureEmissiveOnly;                              // 0x0394(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bLowerHemisphereIsBlack;                           // 0x0395(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_396[0x2];                                      // 0x0396(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
    flinearcolor                           LowerHemisphereColor;                              // 0x0398(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         OcclusionMaxDistance;                              // 0x03A8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         Contrast;                                          // 0x03AC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         OcclusionExponent;                                 // 0x03B0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         MinOcclusion;                                      // 0x03B4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    FColor                                 OcclusionTint;                                     // 0x03B8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         bCloudAmbientOcclusion : 1;                        // 0x03BC(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         Pad_3BD[0x3];                                      // 0x03BD(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         CloudAmbientOcclusionStrength;                     // 0x03C0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         CloudAmbientOcclusionExtent;                       // 0x03C4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         CloudAmbientOcclusionMapResolutionScale;           // 0x03C8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         CloudAmbientOcclusionApertureScale;                // 0x03CC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uobject* OcclusionCombineMode;                              // 0x03D0(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_3D1[0x3];                                      // 0x03D1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    uint8                                         bShowIlluminanceMeter : 1;                         // 0x03D4(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         Pad_3D5[0xB3];                                     // 0x03D5(0x00B3)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* BlendDestinationCubemap;                           // 0x0488(0x0008)(ZeroConstructor, Transient, NoDestructor, Protected, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierProtected)
    uint8                                         Pad_490[0xE0];                                     // 0x0490(0x00E0)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:

    void RecaptureSky() {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.RecaptureSky");

        struct {
        } params;

        this->process_event(function, &params);
    }

    void SetCubemap(class UTextureCube* NewCubemap) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetCubemap");

        struct {
            class UTextureCube* NewCubemap;
        } params;

        params.NewCubemap = NewCubemap;

        this->process_event(function, &params);
    }

    void SetCubemapBlend(class UTextureCube* SourceCubemap, class UTextureCube* DestinationCubemap, float InBlendFraction) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetCubemapBlend");

        struct {
            class UTextureCube* SourceCubemap;
            class UTextureCube* DestinationCubemap;
            float InBlendFraction;
        } params;

        params.SourceCubemap = SourceCubemap;
        params.DestinationCubemap = DestinationCubemap;
        params.InBlendFraction = InBlendFraction;

        this->process_event(function, &params);
    }

    void SetIndirectLightingIntensity(float NewIntensity) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetIndirectLightingIntensity");

        struct {
            float NewIntensity;
        } params;

        params.NewIntensity = NewIntensity;

        this->process_event(function, &params);
    }

    void SetIntensity(float NewIntensity) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetIntensity");

        struct {
            float NewIntensity;
        } params;

        params.NewIntensity = NewIntensity;

        this->process_event(function, &params);
    }

    void SetLightColor(flinearcolor NewLightColor) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetLightColor");

        struct {
            flinearcolor NewLightColor;
        } params;

        params.NewLightColor = NewLightColor;

        this->process_event(function, &params);
    }

    void SetLowerHemisphereColor(flinearcolor InLowerHemisphereColor) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetLowerHemisphereColor");

        struct {
            flinearcolor InLowerHemisphereColor;
        } params;

        params.InLowerHemisphereColor = InLowerHemisphereColor;

        this->process_event(function, &params);
    }

    void SetMinOcclusion(float InMinOcclusion) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetMinOcclusion");

        struct {
            float InMinOcclusion;
        } params;

        params.InMinOcclusion = InMinOcclusion;

        this->process_event(function, &params);
    }

    void SetOcclusionContrast(float InOcclusionContrast) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetOcclusionContrast");

        struct {
            float InOcclusionContrast;
        } params;

        params.InOcclusionContrast = InOcclusionContrast;

        this->process_event(function, &params);
    }

    void SetOcclusionExponent(float InOcclusionExponent) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetOcclusionExponent");

        struct {
            float InOcclusionExponent;
        } params;

        params.InOcclusionExponent = InOcclusionExponent;

        this->process_event(function, &params);
    }

    void SetOcclusionTint(FColor InTint) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetOcclusionTint");

        struct {
            FColor InTint;
        } params;

        params.InTint = InTint;

        this->process_event(function, &params);
    }

    void SetSourceCubemapAngle(float NewValue) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetSourceCubemapAngle");

        struct {
            float NewValue;
        } params;

        params.NewValue = NewValue;

        this->process_event(function, &params);
    }

    void SetVolumetricScatteringIntensity(float NewIntensity) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetVolumetricScatteringIntensity");

        struct {
            float NewIntensity;
        } params;

        params.NewIntensity = NewIntensity;

        this->process_event(function, &params);
    }
};



// Class Engine.LightComponentBase
// 0x0050 (0x0380 - 0x0330)
#pragma pack(push, 0x1)
class alignas(0x10) ULightComponentBase : public USceneComponent
{
public:
    uobject*                                  LightGuid;                                         // 0x0330(0x0010)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         Brightness;                                        // 0x0340(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         Intensity;                                         // 0x0344(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    FColor                                 LightColor;                                        // 0x0348(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         bAffectsWorld : 1;                                 // 0x034C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         CastShadows : 1;                                   // 0x034C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         CastStaticShadows : 1;                             // 0x034C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         CastDynamicShadows : 1;                            // 0x034C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bAffectTranslucentLighting : 1;                    // 0x034C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bTransmission : 1;                                 // 0x034C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bCastVolumetricShadow : 1;                         // 0x034C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bCastDeepShadow : 1;                               // 0x034C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bCastRaytracedShadow : 1;                          // 0x034D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         Pad_34E[0x2];                                      // 0x034E(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
    uobject*                          CastRaytracedShadow;                               // 0x0350(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         Pad_351[0x3];                                      // 0x0351(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    char                                         bAffectReflection : 1;                             // 0x0354(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bAffectGlobalIllumination : 1;                     // 0x0354(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         Pad_355[0x3];                                      // 0x0355(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         DeepShadowLayerDistribution;                       // 0x0358(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         IndirectLightingIntensity;                         // 0x035C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         VolumetricScatteringIntensity;                     // 0x0360(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         SamplesPerPixel;                                   // 0x0364(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bLightProbeIntensityOverride;                      // 0x0368(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bLightProbeColorOverride;                          // 0x0369(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bLightProbeIndirectIntensityOverride;              // 0x036A(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         Pad_36B[0x1];                                      // 0x036B(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         LightProbeIntensity;                               // 0x036C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    FColor                                 LightProbeColor;                                   // 0x0370(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         LightProbeIndirectIntensity;                       // 0x0374(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)

};
class alignas(0x10) ULightComponent : public ULightComponentBase
{
public:
    float                                         Temperature;                                       // 0x0378(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         MaxDrawDistance;                                   // 0x037C(0x0004)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         MaxDistanceFadeRange;                              // 0x0380(0x0004)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         bUseTemperature : 1;                               // 0x0384(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         Pad_385[0x3];                                      // 0x0385(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    char                                         ShadowMapChannel;                                  // 0x0388(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         Pad_38C[0x4];                                      // 0x038C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         MinRoughness;                                      // 0x0390(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         SpecularScale;                                     // 0x0394(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         ShadowResolutionScale;                             // 0x0398(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         ShadowBias;                                        // 0x039C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         ShadowSlopeBias;                                   // 0x03A0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         ShadowSharpen;                                     // 0x03A4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         ContactShadowLength;                               // 0x03A8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         ContactShadowLengthInWS : 1;                       // 0x03AC(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         Pad_3AD[0x3];                                      // 0x03AD(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         ContactShadowCastingIntensity;                     // 0x03B0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         ContactShadowNonCastingIntensity;                  // 0x03B4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         InverseSquaredFalloff : 1;                         // 0x03B8(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         CastTranslucentShadows : 1;                        // 0x03B8(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bCastShadowsFromCinematicObjectsOnly : 1;          // 0x03B8(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         bForceCachedShadowsForMovablePrimitives : 1;       // 0x03B8(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         Pad_3B9[0x3];                                      // 0x03B9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    uobject*                      LightingChannels;                                  // 0x03BC(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, AdvancedDisplay, NativeAccessSpecifierPublic)
    char                                         Pad_3BD[0x3];                                      // 0x03BD(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* LightFunctionMaterial;                             // 0x03C0(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    fvector                                LightFunctionScale;                                // 0x03C8(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uobject* IESTexture;                                        // 0x03E0(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    char                                         bUseIESBrightness : 1;                             // 0x03E8(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    char                                         Pad_3E9[0x3];                                      // 0x03E9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         IESBrightnessScale;                                // 0x03EC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         LightFunctionFadeDistance;                         // 0x03F0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         DisabledBrightness;                                // 0x03F4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         bEnableLightShaftBloom : 1;                        // 0x03F8(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         Pad_3F9[0x3];                                      // 0x03F9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         BloomScale;                                        // 0x03FC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         BloomThreshold;                                    // 0x0400(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         BloomMaxBrightness;                                // 0x0404(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    FColor                                 BloomTint;                                         // 0x0408(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bUseRayTracedDistanceFieldShadows;                 // 0x040C(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_40D[0x3];                                      // 0x040D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         RayStartOffsetDepthScale;                          // 0x0410(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_414[0x74];                                     // 0x0414(0x0074)(Fixing Struct Size After Last Property [ Dumper-7 ])

    void SetIntensity(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetIntensity");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }

    void SetLightingChannels(bool Value, bool Value1, bool Value2) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetLightingChannels");

        struct
        {
            bool Value;
            bool Value1;
            bool Value2;
        } params;

        params.Value = Value;

        params.Value1 = Value;

        params.Value2 = Value;


        this->process_event(function, &params);
    }
    void SetLightColor(flinearcolor easd, float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetLightColor");

        struct
        {
            flinearcolor easd;
            float value;
        } params;

        params.easd = easd;
        params.value = Value;

        this->process_event(function, &params);
    }
    void SetLightColor(flinearcolor NewLightColor, bool bSRGB) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetLightColor");

        struct
        {
            flinearcolor NewLightColor;
            bool bSRGB;
        } params;

        params.NewLightColor = NewLightColor;
        params.bSRGB = bSRGB;

        this->process_event(function, &params);
    }

    void SetIndirectLightingIntensity(float NewIntensity) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetIndirectLightingIntensity");

        struct
        {
            float NewIntensity;
        } params;

        params.NewIntensity = NewIntensity;

        this->process_event(function, &params);
    }

    void SetVolumetricScatteringIntensity(float NewIntensity) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetVolumetricScatteringIntensity");

        struct
        {
            float NewIntensity;
        } params;

        params.NewIntensity = NewIntensity;

        this->process_event(function, &params);

    }

    void SetTemperature(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetTemperature");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetUseTemperature(bool Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetUseTemperature");

        struct
        {
            bool value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetEnableLightShaftBloom(bool Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetEnableLightShaftBloom");

        struct
        {
            bool value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetShadowBias(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetShadowBias");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetShadowSlopeBias(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetShadowSlopeBias");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetSpecularScale(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetSpecularScale");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetBloomScale(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetBloomScale");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetBloomThreshold(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetBloomThreshold");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetBloomMaxBrightness(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetBloomMaxBrightness");

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetBloomTint(FColor Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.LightComponent.SetBloomTint");

        struct
        {
            FColor value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }

};


float GetBulletSpeed(currentequippable* weapon) {  // Assuming your weapon class is named agun
    if (!weapon) return 27000.f;

    fstring raw_name = helper::convert_weapon_name(system::get_object_name(weapon));
    std::wstring wname = raw_name.wide();

    static const std::unordered_map<std::wstring, float> weapon_speeds = {
        {L"Vandal", 27000.f}, {L"Phantom", 26000.f}, {L"Ghost", 23500.f},
        {L"Sheriff", 24000.f}, {L"Operator", 45000.f}, {L"Bulldog", 26000.f},
        {L"Stinger", 18000.f}, {L"Classic", 23500.f}, {L"Guardian", 30000.f},
        {L"Marshal", 40000.f}, {L"Bucky", 18000.f}, {L"Judge", 18000.f},
        {L"Ares", 21000.f}, {L"Odin", 21000.f}, {L"Shorty", 18000.f},
        {L"Frenzy", 23500.f}, {L"Headhunter", 23500.f}, {L"Blade storm", 23500.f},
        {L"Overdrive", 21000.f}, {L"Outlaw", 40000.f}, {L"Tour de force", 45000.f}
    };

    auto it = weapon_speeds.find(wname);
    return (it != weapon_speeds.end()) ? it->second : 27000.f;
}

fvector CalculateAimAngles(const fvector& to_target) {
    float distance = to_target.size();
    float normalized_z = to_target.z / distance;
    normalized_z = std::clamp(normalized_z, -1.f, 1.f);

    float pitch = -(acosf(normalized_z) * (180.f / 3.14159265358979323846f) - 90.f);
    float yaw = atan2f(to_target.y, to_target.x) * (180.f / 3.14159265358979323846f);

    return fvector(pitch, yaw, 0.f);
}

bool IsValidWeaponForSpread(const fstring& obj_name) {
    std::wstring wname = obj_name.wide();

    // Weapons that benefit from spread compensation
    static const std::vector<std::wstring> spread_weapons = {
        L"Bulldog", L"Phantom", L"Vandal", L"Operator", L"Marshal",
        L"Sheriff", L"Spectre", L"Outlaw", L"Classic", L"Shorty",
        L"Frenzy", L"Ghost", L"Stinger", L"Bucky", L"Judge",
        L"Guardian", L"Ares", L"Odin"
    };

    for (const auto& weapon : spread_weapons) {
        if (wname == weapon) return true;
    }
    return false;
}


void DrawFiroxESP(ucanvas* canvas, aplayercontroller* controller, ashootercharacter* local_character, ashootercharacter* actor) {
    if (!canvas || !controller || !local_character || !actor) return;

    uskeletalmeshcomponent* mesh = actor->get_mesh();
    if (!mesh) return;

    fvector head_location = mesh->get_bone_location(8);
    if (!head_location.is_valid()) return;

    fvector root_location = mesh->get_bone_location(0);
    if (!root_location.is_valid()) return;

    fvector2d head_screen = controller->project_world_to_screen(head_location);
    fvector2d root_screen = controller->project_world_to_screen(root_location);

    fvector head_extended = { head_location.x, head_location.y, head_location.z + 25 };
    fvector2d head_extended_screen = controller->project_world_to_screen(head_extended);

    if (!root_screen.is_valid() || !head_screen.is_valid() || !head_extended_screen.is_valid())
        return;

    fvector actor_location = actor->k2_get_actor_location();
    fvector local_location = local_character->k2_get_actor_location();
    float distance = local_location.distance(actor_location);

    float health = actor->health();
    float shield = actor->shield();

    float box_height = abs(head_extended_screen.y - root_screen.y);
    float box_width = box_height * 0.6f;
    float box_left = head_screen.x - (box_width / 2);
    float box_right = head_screen.x + (box_width / 2);
    float box_top = head_extended_screen.y;
    float box_bottom = root_screen.y;

    flinearcolor box_color = defines::visuals_color;
    flinearcolor health_color(0.2f, 1.0f, 0.2f, 1.0f);
    flinearcolor shield_color(0.2f, 0.6f, 1.0f, 1.0f);
    flinearcolor bg_color(0.1f, 0.1f, 0.1f, 0.8f);
    flinearcolor transparent_black(0.0f, 0.0f, 0.0f, 0.1f); 

    defines::health_color = health >= 75 ? defines::high_health :
        (health >= 44) ? defines::normal_health : defines::low_heath;

    // Draw filled transparent background
    float corner_length = box_width * 0.2f;

    for (float y = box_top; y <= box_bottom; y += 1.0f) {
        canvas->k2_drawtransparentline(
            fvector2d(box_left, y),
            fvector2d(box_right, y),
            1.0f, transparent_black
        );
    }

    float line_thickness = 1.0f;

    canvas->k2_drawline(
        fvector2d(box_left, box_top),
        fvector2d(box_left + corner_length, box_top),
        line_thickness, box_color
    );
    canvas->k2_drawline(
        fvector2d(box_left, box_top),
        fvector2d(box_left, box_top + corner_length),
        line_thickness, box_color
    );

    canvas->k2_drawline(
        fvector2d(box_right, box_top),
        fvector2d(box_right - corner_length, box_top),
        line_thickness, box_color
    );
    canvas->k2_drawline(
        fvector2d(box_right, box_top),
        fvector2d(box_right, box_top + corner_length),
        line_thickness, box_color
    );

    canvas->k2_drawline(
        fvector2d(box_left, box_bottom),
        fvector2d(box_left + corner_length, box_bottom),
        line_thickness, box_color
    );

    canvas->k2_drawline(
        fvector2d(box_left, box_bottom),
        fvector2d(box_left, box_bottom - corner_length),
        line_thickness, box_color
    );

    canvas->k2_drawline(
        fvector2d(box_right, box_bottom),
        fvector2d(box_right - corner_length, box_bottom),
        line_thickness, box_color
    );
    canvas->k2_drawline(
        fvector2d(box_right, box_bottom),
        fvector2d(box_right, box_bottom - corner_length),
        line_thickness, box_color
    );

    float health_percent = health / 100.0f;
    float health_height = box_height * health_percent;
    float health_start_y = box_bottom - health_height;

    canvas->k2_drawline(
        fvector2d(box_left - 4, box_bottom),
        fvector2d(box_left - 4, box_top),
        2.5, bg_color
    );

    if (health_height > 0) {
        canvas->k2_drawline(
            fvector2d(box_left - 4, box_bottom),
            fvector2d(box_left - 4, health_start_y),
            2.5, defines::health_color
        );
    }
}

fvector RotatorToVector2(frotator rot)
{
    float pitch = rot.pitch * (3.14159265358979323846f / 180.f);
    float yaw = rot.yaw * (3.14159265358979323846f / 180.f);

    fvector vec;
    vec.x = cosf(pitch) * cosf(yaw);
    vec.y = cosf(pitch) * sinf(yaw);
    vec.z = sinf(pitch);

    return vec;
}



static bool bVisible_cached = false;
static bool CanAutoWall_cached = false;
static bool visible_check_cached = false;
static bool g_HellFireAttached = false;
static bool g_NinjaAttached = false;
static bool g_FogAttached = false;
static UProceduralMeshComponent* g_FogMesh = nullptr;
static bool g_FogApplied = false;
static UParticleSystem* g_Particles2[1] = { nullptr }; // Lightning (Loop only)
static bool g_ParticlesLoaded2 = false;


static UParticleSystem* g_Particles[2] = { nullptr };


static UParticleSystem* g_ParticlesNinja[1] = { nullptr };


static bool g_ParticlesLoaded = false;



static std::map<uintptr_t, UParticleSystemComponent*> g_ActiveHellfireEffects;
static std::map<uintptr_t, UParticleSystemComponent*> g_ActiveLightningEffects;

void SkyLightPaths() {
    if (g_ParticlesLoaded2) return;
    g_ParticlesLoaded2 = true;

    const wchar_t* path = L"/Game/Equippables/Finishers/Ninja/VFX/Particles/P_Ninja_finisher_Lighting_Loop.P_Ninja_finisher_Lighting_Loop";

    g_ParticlesNinja[0] = (UParticleSystem*)uobject::StaticLoadObject(path);
    printf("[DEBUG] SkyLight: 0x%p - %ws\n", g_ParticlesNinja[0], path);

    if (g_ParticlesNinja[0]) {
        printf("[SUCCESS] Lightning Loop loaded!\n");
    }
}

void AttachNinjaToPlayerFollowing(ashootercharacter* Player)
{
    if (!Player) return;

    static fvector LastPlayerLocation = fvector(0, 0, 0);
    fvector CurrentLocation = Player->k2_get_actor_location();

    float distance = sqrt(pow(CurrentLocation.x - LastPlayerLocation.x, 2) +
        pow(CurrentLocation.y - LastPlayerLocation.y, 2) +
        pow(CurrentLocation.z - LastPlayerLocation.z, 2));

    if (distance < 1000.0f) return;

    SkyLightPaths();
    if (!g_ParticlesNinja[0]) return;
    float randomAngle = ((float)rand() / RAND_MAX) * 2.0f * PI;
    float randomDistance = 600.0f + ((float)rand() / RAND_MAX) * 2000.0f;
    float heightOffset = 1000.0f + ((float)rand() / RAND_MAX) * 500.0f;

    fvector SpawnLoc;
    SpawnLoc.x = CurrentLocation.x + cos(randomAngle) * randomDistance;
    SpawnLoc.y = CurrentLocation.y + sin(randomAngle) * randomDistance;
    SpawnLoc.z = CurrentLocation.z + heightOffset;

    float scale = 50.0f;

    auto result = GameplayStatics::SpawnEmitterAtLocationWithWorld(
        (uobject*)UWorldSave,
        g_ParticlesNinja[0],
        SpawnLoc,
        frotator(0, 0, 0),
        fvector(scale, scale, scale),
        true, EPSCPoolMethod::None, true, false, 0.0f
    );

    if (result)
    {           
        g_ActiveLightningEffects[(uintptr_t)result] = result;
    }

    LastPlayerLocation = CurrentLocation;
}

void LoadHellFireParticles() {
    if (g_ParticlesLoaded) return;
    g_ParticlesLoaded = true;

    const wchar_t* paths[] = {
        L"/Game/Equippables/Finishers/Hellfire/VFX/Finisher_Hellfire_Debris_ENV_Chroma.Finisher_Hellfire_Debris_ENV_Chroma",
        L"/Game/Equippables/Finishers/Hellfire/VFX/Finisher_Hellfire_Debris_ENV.Finisher_Hellfire_Debris_ENV",
    };

    for (int i = 0; i < 2; i++) {
        g_Particles[i] = (UParticleSystem*)uobject::StaticLoadObject(paths[i]);
      
    }
}

void AttachHellFireToPlayerFollowing(ashootercharacter* Player)
{
    if (!Player) return;

    static fvector LastPlayerLocation = fvector(0, 0, 0);
    fvector CurrentLocation = Player->k2_get_actor_location();

    float distance = sqrt(pow(CurrentLocation.x - LastPlayerLocation.x, 2) +
        pow(CurrentLocation.y - LastPlayerLocation.y, 2) +
        pow(CurrentLocation.z - LastPlayerLocation.z, 2));

    if (distance < 1000.0f) return;

    LoadHellFireParticles();
    if (!g_Particles[0] && !g_Particles[1]) return;

    for (int i = 0; i < 3; i++)
    {
        float randomAngle = ((float)rand() / RAND_MAX) * 2.0f * PI;
        float randomDistance = 600.0f + ((float)rand() / RAND_MAX) * 2000.0f;

        fvector SpawnLoc;
        SpawnLoc.x = CurrentLocation.x + cos(randomAngle) * randomDistance;
        SpawnLoc.y = CurrentLocation.y + sin(randomAngle) * randomDistance;
        SpawnLoc.z = CurrentLocation.z + (-50.0f + ((float)rand() / RAND_MAX) * 200.0f);

        auto result = GameplayStatics::SpawnEmitterAtLocationWithWorld(
            (uobject*)UWorldSave,
            g_Particles[rand() % 2],
            SpawnLoc,
            frotator(0, 0, 0),
            fvector(2.5f, 2.5f, 2.5f),
            true, EPSCPoolMethod::None, true, false, 0.0f
        );

        if (result)
        {
            g_ActiveHellfireEffects[(uintptr_t)result] = result;
        }
    }

    LastPlayerLocation = CurrentLocation;

}


static UParticleSystem* g_HellFireParticles[2] = { nullptr, nullptr };
static bool             g_HellFireParticlesLoaded = false;
static ashootercharacter* g_LastHellFireCharacter = nullptr;

void ResetHellFire() {

    for (auto& pair : g_ActiveHellfireEffects) {
        if (pair.second && IsValidUObject((uobject*)pair.second)) {
            pair.second->Deactivate();
            pair.second->K2_DestroyComponent(pair.second);

        }
    }

    g_ActiveHellfireEffects.clear();

    g_HellFireAttached = false;
    g_LastHellFireCharacter = nullptr;

}


bool ispakdid = false;


void AttachHellFireToPlayer(ashootercharacter* target_character)
{
    if (!target_character || !memory::IsValidPointer((uintptr_t)target_character)) return;
    if (g_HellFireAttached && g_LastHellFireCharacter == target_character) return;

    LoadHellFireParticles();

    srand((unsigned int)GetTickCount64());

    int maxEffects = 12;

    for (int i = 0; i < maxEffects; i++) {
        float angle = ((float)rand() / RAND_MAX) * 2.0f * 3.14159265f;
        float dist = 600.0f + ((float)rand() / RAND_MAX) * 3000.0f;

        fvector relativePos;
        relativePos.x = cos(angle) * dist;
        relativePos.y = sin(angle) * dist;
        relativePos.z = -50.0f + ((float)rand() / RAND_MAX) * 200.0f;

        int particleType = rand() % 2;
        if (!g_HellFireParticles[particleType]) continue;

        float randomScale = 1.5f + ((float)rand() / RAND_MAX) * 2.5f;

        auto rootComp = target_character->K2_GetRootComponent();
        if (!rootComp || !memory::IsValidPointer((uintptr_t)rootComp)) continue;


        GameplayStatics::SpawnEmitterAttached(
            g_HellFireParticles[particleType],
            rootComp,
            fname{},
            relativePos,
            FRotator{ 0.f, 0.f, 0.f },
            fvector(randomScale, randomScale, randomScale),
            EAttachLocation::KeepRelativeOffset,
            true,
            EPSCPoolMethod::None,
            true,
            false,
            0.0f,
            EAresParticleVariantColor::AresVariantBaseColor,
            UWorldSave
        );
    }

    g_HellFireAttached = true;
    g_LastHellFireCharacter = target_character;
}
void ResetSkyLightFire() {

    for (auto& pair : g_ActiveLightningEffects) {
        if (pair.second && IsValidUObject((uobject*)pair.second)) {
            pair.second->Deactivate();
            pair.second->K2_DestroyComponent(pair.second);


        }
    }
    g_ActiveLightningEffects.clear();

}



bool IsValidWeapon(const fstring& obj_name) {
    std::wstring wname = obj_name.wide();

    // All weapons
    static const std::vector<std::wstring> all_weapons = {
        L"Bulldog", L"Phantom", L"Vandal", L"Operator", L"Marshal",
        L"Sheriff", L"Spectre", L"Outlaw", L"Classic", L"Shorty",
        L"Frenzy", L"Ghost", L"Stinger", L"Bucky", L"Judge",
        L"Guardian", L"Ares", L"Odin", L"Headhunter", L"Blade storm",
        L"Overdrive", L"Tour de force"
    };

    for (const auto& weapon : all_weapons) {
        if (wname == weapon) return true;
    }
    return false;
}

class ALight : public AActor
{
public:
    class ULightComponent* LightComponent;                                    // 0x0460(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
    uint8                                         bEnabled : 1;                                      // 0x0468(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Net, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
    uint8                                         Pad_469[0x7];                                      // 0x0469(0x0007)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
    void OnRep_bEnabled(); // Function: 0x3B91170
    void SetAffectTranslucentLighting(bool bNewValue) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.SetAffectTranslucentLighting");

        struct
        {
            bool bNewValue;
        } params;

        params.bNewValue = bNewValue;

        this->process_event(function, &params);
    }


    flinearcolor GetLightColor() {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.GetLightColor");

        struct
        {
            flinearcolor bNewValue;
        } params;

        this->process_event(function, &params);
        return params.bNewValue;
    }


    void SetBrightness(float NewBrightness) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.SetBrightness");

        struct
        {
            float NewBrightness;
        } params;

        params.NewBrightness = NewBrightness;

        this->process_event(function, &params);

    }// Function: 0x43EB920
    void SetCastShadows(bool bNewValue) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.SetCastShadows");

        struct
        {
            bool bNewValue;
        } params;

        params.bNewValue = bNewValue;

        this->process_event(function, &params);

    }// Function: 0x43EB220
    void SetEnabled(bool bSetEnabled) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.SetEnabled");

        struct
        {
            bool bSetEnabled;
        } params;

        params.bSetEnabled = bSetEnabled;

        this->process_event(function, &params);
    }// Function: 0x43EBAD0
    void SetLightColor(flinearcolor NewLightColor) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.SetLightColor");

        struct
        {
            flinearcolor bSetEnabled;
        } params;

        params.bSetEnabled = NewLightColor;

        this->process_event(function, &params);
    }// Function: 0x43EB7E0
    void SetLightFunctionFadeDistance(float NewLightFunctionFadeDistance) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.SetLightFunctionFadeDistance");

        struct
        {
            float NewLightFunctionFadeDistance;
        } params;

        params.NewLightFunctionFadeDistance = NewLightFunctionFadeDistance;

        this->process_event(function, &params);

    }// Function: 0x43EB370
    void SetLightFunctionMaterial(class UMaterialInterface* NewLightFunctionMaterial); // Function: 0x43EB600
    void SetLightFunctionScale(const struct FVector& NewLightFunctionScale); // Function: 0x43EB4A0
    void ToggleEnabled(); // Function: 0x43EBA50

    float GetBrightness() {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.IsEnabled");

        struct
        {
            float bSetEnabled;
        } params;



        this->process_event(function, &params);
        return params.bSetEnabled;
    }
    bool IsEnabled() {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(L"Engine.Light.IsEnabled");

        struct
        {
            bool bSetEnabled;
        } params;



        this->process_event(function, &params);
        return params.bSetEnabled;
    }


};

class UExponentialHeightFogComponent final : public USceneComponent
{
public:
    float                                         FogDensity;                                        // 0x0330(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         FogHeightFalloff;                                  // 0x0334(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uobject* SecondFogData;                                     // 0x0338(0x000C)(Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, NativeAccessSpecifierPublic)
    flinearcolor                           FogInscatteringColor;                              // 0x0344(0x0010)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    flinearcolor                           FogInscatteringLuminance;                          // 0x0354(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    flinearcolor                           SkyAtmosphereAmbientContributionColorScale;        // 0x0364(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_374[0x4];                                      // 0x0374(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
    uobject* InscatteringColorCubemap;                          // 0x0378(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         InscatteringColorCubemapAngle;                     // 0x0380(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    struct flinearcolor                           InscatteringTextureTint;                           // 0x0384(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         FullyDirectionalInscatteringColorDistance;         // 0x0394(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         NonDirectionalInscatteringColorDistance;           // 0x0398(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         DirectionalInscatteringExponent;                   // 0x039C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         DirectionalInscatteringStartDistance;              // 0x03A0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    flinearcolor                           DirectionalInscatteringColor;                      // 0x03A4(0x0010)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    flinearcolor                           DirectionalInscatteringLuminance;                  // 0x03B4(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         FogMaxOpacity;                                     // 0x03C4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         StartDistance;                                     // 0x03C8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         FogCutoffDistance;                                 // 0x03CC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bEnableVolumetricFog;                              // 0x03D0(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_3D1[0x3];                                      // 0x03D1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
    float                                         VolumetricFogScatteringDistribution;               // 0x03D4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    FColor                                 VolumetricFogAlbedo;                               // 0x03D8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    flinearcolor                           VolumetricFogEmissive;                             // 0x03DC(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         VolumetricFogExtinctionScale;                      // 0x03EC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         VolumetricFogDistance;                             // 0x03F0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         VolumetricFogStartDistance;                        // 0x03F4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         VolumetricFogNearFadeInDistance;                   // 0x03F8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    float                                         VolumetricFogStaticLightingScatteringIntensity;    // 0x03FC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    bool                                          bOverrideLightColorsWithFogInscatteringColors;     // 0x0400(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
    uint8                                         Pad_401[0xF];    


    void SetFogDensity(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogDensity").decrypt());

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }

    void SetFogHeightFalloff(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogHeightFalloff").decrypt());

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }

    void SetFogInscatteringColor(flinearcolor Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogInscatteringColor").decrypt());

        struct
        {
            flinearcolor value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }
    void SetFogMaxOpacity(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogMaxOpacity").decrypt());

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }

    void SetStartDistance(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetStartDistance").decrypt());

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }

    void SetFogCutoffDistance(float Value) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetFogCutoffDistance").decrypt());

        struct
        {
            float value;
        } params;

        params.value = Value;

        this->process_event(function, &params);
    }

    void SetVolumetricFog(bool bNewValue) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetVolumetricFog").decrypt());

        struct
        {
            bool value;
        } params;

        params.value = bNewValue;

        this->process_event(function, &params);
    }
    void SetVolumetricFogDistance(float NewValue) {
        static uobject* function = 0;
        if (!function)
            function = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent.SetVolumetricFogDistance").decrypt());

        struct
        {
            float value;
        } params;

        params.value = NewValue;

        this->process_event(function, &params);
    }
};





//void ReplaceWeaponMeshWith3DModel(currentequippable* Weapon, const char* objFilePath, ashootercharacter* character, uworld* Uworld) {
//    if (!Weapon || !Weapon->GetMesh1P())
//        return;
//    {
//        uintptr_t key = (uintptr_t)Weapon;
//        auto it = g_ProcMeshCache.find(key);
//
//        if (it != g_ProcMeshCache.end())
//        {
//            static uobject* SetVisibilityFunc =
//                uobject::find_object<uobject*>(L"Engine.SceneComponent.SetVisibility");
//
//            if (SetVisibilityFunc)
//            {
//                struct { bool v; bool p; } vp;
//
//                vp.v = false;
//                vp.p = true;
//                Weapon->GetMesh1P()->process_event(SetVisibilityFunc, &vp);
//
//                vp.v = true;
//                it->second->process_event(SetVisibilityFunc, &vp);
//            }
//            return;
//        }
//
//        static uclass* ProcMeshClass =
//            uobject::find_object<uclass*>(L"ProceduralMeshComponent.ProceduralMeshComponent");
//        if (!ProcMeshClass)
//            return;
//
//        static uobject* AddComponentFunc =
//            uobject::find_object<uobject*>(L"ShooterGame.ShooterBlueprintLibrary.AddComponentByClass");
//        if (!AddComponentFunc)
//            return;
//
//        struct {
//            AActor* Actor;
//            UActorComponent* ComponentClass;
//            UActorComponent* ReturnValue;
//        } AddParams{ (AActor*)Weapon, (UActorComponent*)ProcMeshClass, nullptr };
//
//        variables.blueprints->process_event(AddComponentFunc, &AddParams);
//        ProcMesh = (UProceduralMeshComponent*)AddParams.ReturnValue;
//        if (!ProcMesh)
//            return;
//
//        MeshData mesh = ParseOBJFile(objFilePath);
//
//        for (auto& normal : mesh.Normals) {
//            normal = normal * -1.0f;
//        }
//
//        // Reverse triangle winding
//        for (int i = 0; i < mesh.Triangles.Num(); i += 3) {
//            int32_t temp = mesh.Triangles[i + 1];
//            mesh.Triangles[i + 1] = mesh.Triangles[i + 2];
//            mesh.Triangles[i + 2] = temp;
//        }
//
//        // Set vertex colors
//        if (mesh.VertexColors.Num() == 0) {
//            for (int i = 0; i < mesh.Vertices.Num(); i++) {
//                mesh.VertexColors.Add(FColor(255, 255, 255, 255));
//            }
//        }
//
//
//        CreateMeshFunc = uobject::find_object<uobject*>(
//            L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection"
//        );
//        if (!CreateMeshFunc) return;
//
//        struct {
//            int32_t SectionIndex;
//            tarray<fvector> Vertices;
//            tarray<int32_t> Triangles;
//            tarray<fvector> Normals;
//            tarray<fvector2d> UV0;
//            tarray<FColor> VertexColors;
//            tarray<FProcMeshTangent> Tangents;
//            bool bCreateCollision;
//        } CreateParams = {
//          0, mesh.Vertices, mesh.Triangles, mesh.Normals,
//          mesh.UV0, mesh.VertexColors, mesh.Tangents, false
//        };
//
//        ProcMesh->process_event(CreateMeshFunc, &CreateParams);
//        auto* OriginalMesh = Weapon->GetMesh1P();
//
//        static uobject* GetMaterialFunc = uobject::find_object<uobject*>(
//            L"Engine.PrimitiveComponent.GetMaterial"
//        );
//
//        if (GetMaterialFunc) {
//            UPrimitiveComponent* GunMesh = (UPrimitiveComponent*)OriginalMesh;
//            UPrimitiveComponent* ProcMeshComponent2 = (UPrimitiveComponent*)ProcMesh;
//            RAHHTEXTURE(character, GunMesh, Uworld);
//            struct { int32_t ElementIndex; UMaterialInterface* ReturnValue; } GetMatParams = { 0, nullptr };
//            OriginalMesh->process_event(GetMaterialFunc, &GetMatParams);
//
//            if (GetMatParams.ReturnValue) {
//                static uobject* SetMaterialFunc = uobject::find_object<uobject*>(
//                    L"Engine.PrimitiveComponent.SetMaterial"
//                );
//                if (SetMaterialFunc) {
//                    struct { int32_t ElementIndex; UMaterialInterface* Material; } SetMatParams = { 0, GetMatParams.ReturnValue };
//                    ProcMesh->process_event(SetMaterialFunc, &SetMatParams);
//                }
//            }
//        }
//
//        static uobject* AttachFunc =
//            uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_AttachToComponent");
//
//        fname Socket = string::string_to_name(L"R_WeaponPoint");
//
//        if (AttachFunc) {
//            struct {
//                USceneComponent* Parent;
//                EAttachmentRule AttachmentRules;
//                fname SocketName;
//            } AttachParams = {
//              (USceneComponent*)OriginalMesh,
//              EAttachmentRule::SnapToTarget,
//              Socket
//            };
//
//            ProcMesh->process_event(AttachFunc, &AttachParams);
//        }
//
//
//        ProcMesh->SetRelativeRotation1(frotator(0, -90, 0), false, true);
//
//        static uobject* SetRelativeLocationFunc = uobject::find_object<uobject*>(
//            L"Engine.SceneComponent.K2_SetRelativeLocation"
//        );
//        if (SetRelativeLocationFunc) {
//            struct {
//                fvector NewLocation;
//                bool bSweep;
//                FHitResult SweepHitResult;
//                bool bTeleport;
//            } LocParams = { fvector(0, 0, 0), false, FHitResult(), false };
//            ProcMesh->process_event(SetRelativeLocationFunc, &LocParams);
//        }
//
//        ProcMesh->SetRelativeScale3D1(fvector(1, 1, 1));
//     
//        static uobject* RegisterFunc = uobject::find_object<uobject*>(
//            L"Engine.CharacterHudComponent.RegisterComponent"
//        );
//        if (RegisterFunc) {
//            ProcMesh->process_event(RegisterFunc, nullptr);
//        }
//
//        auto location = fvector(-0.9434, 0.943392, -2.83019);
//        auto rotation = frotator(0, 90, -90);
//        auto scale = fvector(1.5, 1.5, 1.5);
//
//        fstring converted_name = helper::convert_weapon_name(system::get_object_name((uobject*)Weapon));
//        if (converted_name.wide() == L"Melee") {
//            ProcMesh->SetRelativeScale3D1(fvector(globals::visuals::m_scale, globals::visuals::m_scale, globals::visuals::m_scale));
//            ProcMesh->SetRelativeRotation1(frotator(globals::visuals::m_pitch, globals::visuals::m_yaw, globals::visuals::m_roll));
//            ProcMesh->K2_AddRelativeLocation(fvector(globals::visuals::m_x, globals::visuals::m_y, globals::visuals::m_z), false, true);
//        }
//        else {
//            ProcMesh->SetRelativeScale3D1(fvector(1.5, 1.5, 1.5));
//            ProcMesh->SetRelativeRotation1(frotator(0, 90, -90));
//            ProcMesh->K2_AddRelativeLocation(fvector(-0.9434, 0.943392, -2.83019), false, true);
//        }
//
//        g_ProcMeshCache[key] = ProcMesh;
//
//    }
//
//  
//
//}



frotator NormalToRot3(const fvector& Normal)
{
    frotator Rot{};
    Rot.pitch = atan2f(Normal.z, sqrtf(Normal.x * Normal.x + Normal.y * Normal.y)) * (180.f / 3.14159265f);
    Rot.yaw = atan2f(Normal.y, Normal.x) * (180.f / 3.14159265f);
    Rot.roll = 0.f;
    return Rot;
}

float rainbowTimeZRGB = 0;
static flinearcolor ChamsColor{ 2.093f, 0.019f, 20.0f, 1.0f };
flinearcolor BOSSRAINBOMAW(float time)
{
    




    const float PI = 3.14159265359f;
    float r = 0.5f + 0.5f * sin(time);
    float g = 0.5f + 0.5f * sin(time + 2.0f * PI / 3.0f);
    float b = 0.5f + 0.5f * sin(time + 4.0f * PI / 3.0f);
    return flinearcolor(r, g, b, 1.0f);
}

inline fvector MirrorForLeft(const fvector& v, bool isLeft)
{
    if (!isLeft)
        return v;

    fvector out = v;
    out.x *= -1.f;
    return out;
}



inline float DegToRad(float v)
{
    return v * 0.01745329251f;
}

inline float GetFovScale(float fov)
{
    return std::tan(DegToRad(fov * 0.5f)) /
        std::tan(DegToRad(90.f * 0.5f));
}

inline fvector HandFov(const fvector& v, float s)
{
    return { v.x * s, v.y * s, v.z };
}

inline fvector WeaponFov(const fvector& scale, float fovScale)
{
    // Only scale X/Y (width/side) for widearms, keep Z (depth) intact
    return { scale.x / fovScale, scale.y / fovScale, scale.z };
}




uskeletalmeshcomponent* GetArmsMesh1P(ashootercharacter* character)
{
    if (!character)
        return nullptr;

    return character->GetOverlayMesh1P();
}

uskeletalmeshcomponent* GetWeaponMesh1P(ashootercharacter* character)
{
    if (!character)
        return nullptr;

    auto inventory = character->get_inventory();
    if (!inventory)
        return nullptr;

    auto weapon = inventory->get_current_equippable();
    if (!weapon)
        return nullptr;

    return weapon->GetMesh1P();
}


fvector ApplyFOVScale(const fvector& scale, float fovScale)
{
    return { scale.x * fovScale, scale.y * fovScale, scale.z };
}
void ApplyWideArmsRuntimeAutoFOV(aplayercontroller* pc, ashootercharacter* character, int wideArmsMode)
{
    if (!pc || !character)
        return;

    auto handMesh = character->GetOverlayMesh1P();
    if (!handMesh)
        return;

    auto inventory = character->get_inventory();
    if (!inventory)
        return;

    auto weapon = inventory->get_current_equippable();
    if (!weapon)
        return;

    auto weaponMesh = weapon->GetMesh1P();
    if (!weaponMesh)
        return;

   

    float baseFOV = pc->get_camera_manager()->GetFOVAngle1P();
    float fovScale = 1.0f; // will auto-calc below

    // -------------------------------
    // 1️⃣ Setup scales based on mode
    // -------------------------------
    fvector scaleHand, scaleInspect, scaleKnife;

    switch (wideArmsMode)
    {
    case 0:
        scaleHand = { 2.0f, 1.f, 1.f };
        scaleInspect = { 0.423117f, 1.f, 1.f };
        scaleKnife = { 0.483117f, 1.f, 1.f };
        break;
    case 1:
        scaleHand = { 2.85714f, 2.47619f, 1.f };
        scaleInspect = { 0.423117f, 0.423117f, 1.f };
        scaleKnife = { 0.493506f, 0.532468f, 1.44156f };
        break;
    default:
        scaleHand = { 1.f, 1.f, 1.f };
        scaleInspect = { 1.f, 1.f, 1.f };
        scaleKnife = { 1.f, 1.f, 1.f };
        break;
    }

    // -------------------------------
    // 2️⃣ Check weapon state
    // -------------------------------
    EAresEquippableState state = memory::read<EAresEquippableState>(
        reinterpret_cast<uintptr_t>(weapon) + offsets::CurrentEquippableVFXState
    );

    bool isInspecting = state == EAresEquippableState::Inspecting;
    bool isReloading = state == EAresEquippableState::Reloading;
    bool isScoped = state == EAresEquippableState::ADS_Idle ||
        state == EAresEquippableState::ADS_Firing;

    // -------------------------------
    // 3️⃣ Scoped = reset to default
    // -------------------------------
    if (isScoped)
    {
        handMesh->SetRelativeScale3D({ 1.f, 1.f, 1.f });
        weaponMesh->SetRelativeScale3D({ 1.f, 1.f, 1.f });
       
        return;
    }

    // -------------------------------
    // 4️⃣ Auto FOV scaling based on hand width
    // -------------------------------
    // Wide hands make perspective look zoomed out → compensate
    fovScale = 1.0f / scaleHand.x; // bigger hand → smaller FOV delta

    // Clamp FOV scale for sanity
    if (fovScale < 0.5f) fovScale = 0.5f;
    if (fovScale > 1.0f) fovScale = 1.0f;

    // -------------------------------
    // 5️⃣ Apply scales
    // -------------------------------
    handMesh->SetRelativeScale3D(scaleHand);

    if (isInspecting || isReloading)
        weaponMesh->SetRelativeScale3D({ scaleInspect.x * fovScale, scaleInspect.y * fovScale, scaleInspect.z });
    else if (weapon && system::get_object_name((uobject*)weapon).to_str().find("Ability_Melee_Base_C") != std::string::npos)
        weaponMesh->SetRelativeScale3D({ scaleKnife.x * fovScale, scaleKnife.y * fovScale, scaleKnife.z });
    else
        weaponMesh->SetRelativeScale3D({ 1.f * fovScale, 1.f * fovScale, 1.f });

   
    // -------------------------------
    // 6️⃣ Apply smooth FOV offset
    // -------------------------------
    pc->set_fov(baseFOV * fovScale);
}


int GetEquippableVFXState1(EAresEquippableState STATE) {

    switch (STATE) {
    case EAresEquippableState::Reloading:
        return 1;
        break;
    case EAresEquippableState::Inspecting:
        return 2;
        break;
    case EAresEquippableState::Firing:
        return 3;
        break;
    case EAresEquippableState::ADS_Firing:
        return 4;
        break;
    case EAresEquippableState::Attacking:
        return 5;
        break;
    default:
        return 6;
    }
}



fstring weapon_name(fstring in)
{
    
    if (in.ToString().find("Ability_Melee_Base_C") != std::string::npos)
        return fstring(L"KNIFE");
    if (in.ToString().find("BasePistol_C") != std::string::npos)
        return fstring(L"CLASSIC");
    if (in.ToString().find("TrainingBotBasePistol_C") != std::string::npos)
        return fstring(L"CLASSIC");
    if (in.ToString().find("SawedOffShotgun_C") != std::string::npos)
        return fstring(L"SHORTY");
    if (in.ToString().find("AutomaticPistol_C") != std::string::npos)
        return fstring(L"FRENZY");
    if (in.ToString().find("LugerPistol_C") != std::string::npos)
        return fstring(L"GHOST");
    if (in.ToString().find("RevolverPistol_C") != std::string::npos)
        return fstring(L"SHERIFF");
    if (in.ToString().find("Vector_C") != std::string::npos)
        return fstring(L"STINGER");
    if (in.ToString().find("SubMachineGun_MP5_C") != std::string::npos)
        return fstring(L"SPECTRE");
    if (in.ToString().find("PumpShotgun_C") != std::string::npos)
        return fstring(L"BUCKY");
    if (in.ToString().find("AssaultRifle_Burst_C") != std::string::npos)
        return fstring(L"BULLDOG");
    if (in.ToString().find("DMR_C") != std::string::npos)
        return fstring(L"GUARDIAN");
    if (in.ToString().find("AssaultRifle_ACR_C") != std::string::npos)
        return fstring(L"PHANTOM");
    if (in.ToString().find("AssaultRifle_AK_C") != std::string::npos)
        return fstring(L"VANDAL");
    if (in.ToString().find("LeverSniperRifle_C") != std::string::npos)
        return fstring(L"MARSHAL");
    if (in.ToString().find("BoltSniper_C") != std::string::npos)
        return fstring(L"OPERATOR");
    if (in.ToString().find("LightMachineGun_C") != std::string::npos)
        return fstring(L"ARES");
    if (in.ToString().find("HeavyMachineGun_C") != std::string::npos)
        return fstring(L"ODIN");
    if (in.ToString().find("Bomb_C") != std::string::npos)
        return fstring(L"SPIKE");
    if (in.ToString().find("Pawn_Gumshoe_Q_PossessableCamera_C") != std::string::npos)
        return fstring(L"CYPHER CAMERA");
    if (in.ToString().find("Pawn_Hunter_E_Drone_Prototype_Balance_C") != std::string::npos)
        return fstring(L"SOVA DRONE");
    else
        return fstring(L"ABILITIES");

}


enum class EShooterCharacterCameraState : uint8
{
    FollowRecoilCamera = 0,
    CustomCamera = 1,
    DeathCamera = 2,
    SettledDeathCamera = 3,
    InvalidViewTarget = 4,
    Count = 5,
    EShooterCharacterCameraState_MAX = 6,
};
