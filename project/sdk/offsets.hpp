#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include "structs.hpp"
#include "../encrypt/xor.hpp"
#include <vector>
#include <unordered_map>

template<class k, class e>
class tmap
{
public:
	k Key;
	e Element;
	char __pad0x[0x8];
};

namespace offsets
{
	namespace radar {
		uintptr_t portrait_minimap = 0x1560; // c
		uintptr_t character_minimap = 0x1568;
	}

	namespace minimap_component {
		uintptr_t observer_status = 0x0698;
		uintptr_t visible_status = 0x0659;
	}

	uintptr_t hkdeath = 0x37;
	uintptr_t post_render = 0x63;
	uintptr_t update_view_target = 0xf2;
	uintptr_t OHkTarget = 0x159;

	constexpr uint64_t fmemory_malloc = 0xC84080;
	constexpr uint64_t play_finisher_effect = 0x62185A0;
	constexpr uint64_t last_submit_time = 0x478;
	constexpr uint64_t last_render_time = 0x47C;


	constexpr uint64_t vtable = 0x53;

	auto State = Encrypt("0xA4B02F0");
	constexpr uint64_t State2 = 0xA4B02F0;
	constexpr uint64_t MeshFPFlag = 0x364;

	constexpr uint64_t Component2World = 0x2D0;

	constexpr uint64_t UworldShit = 0x68;
	constexpr uint64_t UworldShit1 = 0x080;
	constexpr uint64_t ChamsOffset = 0x01270;
	constexpr uint64_t arms = 0x01220;

	constexpr uint64_t AntiFlash = 0x0a28;

	constexpr uint64_t RWX = 0x80;
	constexpr uint64_t ObjectiveIcon = 0x04e0;
	///need Offsets

	constexpr uint64_t static_find_object = 0x108EC30;
	constexpr uint64_t static_laod_object = 0x1091140;

	constexpr uint64_t process_event = 0x103D150;
	constexpr uint64_t bone_matrix = 0x3197400;
	constexpr uint64_t skin_decrypt = 0x3442320;
	constexpr uintptr_t MakeRenderStateDirty = 0x154edb0;
	constexpr uint64_t SetAresOutlineMode = 0x31640D0;

	constexpr uintptr_t outline_modee = 0x0330;
	constexpr uintptr_t attach_children = 0x0110;
	constexpr uintptr_t attach_children_count = 0x0118;

	constexpr uint64_t RandomShit = 0x8;

	constexpr uint64_t MagicOffsets = 0x4B129F0;

	constexpr uint64_t get_fpak_platform_file = 0x0A97E4E8;
	constexpr uint64_t bypass_pak_signing = 0x0A97D370;
	constexpr uint64_t mount_custom_pak = 0x02715000;

	constexpr uint64_t TriggerVEH = 0xC9FA06;
	constexpr uint64_t Inventory = 0x0c08;
	constexpr uint64_t Equippable = 0x0240;
	constexpr uint64_t Mesh1pGun = 0xde0;
	constexpr uint64_t Mesh3pGun = 0xdf0;
	constexpr uint64_t GameViewport = 0x0BD0;
	constexpr uint64_t SkyMeshcomponent = 0x0290;
	constexpr uint64_t Rootcomponent = 0x0290;
	constexpr uint64_t root_position = 0x0170;
	constexpr uint64_t CameraRadar = 0x017C0;
	constexpr uint64_t FresnelIntensity = 0x01E4;
	constexpr uint64_t FresnelComponent = 0x0860;
	constexpr uint64_t CurrentEquippableVFXState = 0x0e30;
	constexpr uint64_t LocalPlayers = 0x040;
	constexpr uint64_t LocalController = 0x038;

	constexpr uint64_t seed_data = 0x4A0;
	constexpr uint64_t stability_component = 0x0490; //stability

	constexpr uint64_t stability_component1 = 0x35E18DD; //stability
	constexpr uint64_t ActiveStabilityComponent = 0x338;

	constexpr uint64_t error_power = 0x49c;
	constexpr uint64_t error_retries = 0x470;



	static auto get_spread_values_enc = Encrypt("0x4DD1390");
	static auto get_spread_angles_enc = Encrypt("0x586BFD0");
	static auto tovector_and_normalize_enc = Encrypt("0xD6AD90");
	static auto toangle_and_normalize_enc = Encrypt("0xD67FB0");
	static auto GetFiringLocationAndDirection_enc = Encrypt("0x6A6C4E0");


	static uintptr_t get_spread_values = DecryptOffsetClear(get_spread_values_enc);
	static uintptr_t get_spread_angles = DecryptOffsetClear(get_spread_angles_enc);
	static uintptr_t tovector_and_normalize = DecryptOffsetClear(tovector_and_normalize_enc);
	static uintptr_t toangle_and_normalize = DecryptOffsetClear(toangle_and_normalize_enc);
	static uintptr_t GetFiringLocationAndDirection = DecryptOffsetClear(GetFiringLocationAndDirection_enc);


	constexpr uint64_t firing_state_component = 0x1228;
	constexpr uint64_t displayname = 0x5c8;

	constexpr uint64_t DefuseTimer = 0x5D0;
	constexpr uint64_t Timer = 0x05A8;

	constexpr uint64_t get_charm_level_data_asset = 0x70;
	constexpr uint64_t get_charm_data_asset = 0x68;
	constexpr uint64_t get_skin_chroma_data_asset = 0x108;
	constexpr uint64_t get_skin_data_asset = 0x108;
	constexpr uint64_t get_skin_levels = 0x88;

	constexpr uint64_t super_class = 0x48;
	constexpr uint64_t objectclass = 0x10;

	constexpr uint64_t relative_rotation = 0x170;

	constexpr uint64_t portrait_map = 0x14F0;
	constexpr uint64_t character_map = 0x14F8;


	constexpr uint64_t poraitshit = 0x659;
	constexpr uint64_t Character = 0x698;

	constexpr uint64_t cameramaneger = 0x0528;
	constexpr uint64_t mesh = 0x438;





	constexpr uintptr_t LeftHandFarBoneName = 0xfbc;
	constexpr uintptr_t RightHandWeaponAttachName = 0xfc8;
	constexpr uintptr_t bIsLeftHanded = 0xfc8;
	constexpr uintptr_t bSupportsLeftHandedMode = 0xf1c;
	std::uintptr_t death_reaction_component_offset = 0x0CA8; //0x10
	std::uintptr_t montage_effect_override_offset = 0x100;
	std::uintptr_t montage_effect_override_context_offset = 0x108;

	//actor -> Username
	constexpr uint64_t PlayerState = 0x488;
	constexpr uint64_t PlatformPlayer = 0x6A0;
	constexpr uint64_t RiotName = 0x480;

	//camera 
	constexpr uint64_t camerapos = 0x590;
	constexpr uint64_t camerafov = 0x580;
	constexpr uint64_t camerarot = 0x59C;

	//sumshit
	constexpr uint64_t game_instance = 0x01d8;
	constexpr uint64_t local_players = 0x40;
	constexpr uint64_t viewport_client = 0x80;
	constexpr uint64_t was_invisible = 0xc8b;
	constexpr uint64_t inventory_icon = 0x0EB0;
	constexpr uintptr_t bone_array = 0x730;

	constexpr uint64_t bone_cout = bone_array + 0x8;
	constexpr uint64_t font = 0x88;
	constexpr uint64_t WireFrame = 0x8fe;
	constexpr uint64_t WireFrame2 = 0xc0;
	constexpr uint64_t WireFrame3 = 0xff;

	constexpr uint64_t skin_pointer = 0x3a8;
	constexpr uint64_t skin_pointer_2 = 0xB0;
	constexpr uint64_t skin_pointer_3 = 0x80;

	constexpr uint64_t ThirdpersonCosmestic3p = 0x0F00;
	constexpr uint64_t ControlRotation = 0x4e0;


	constexpr uint64_t ScreenSize1 = 0x48;
	constexpr uint64_t ScreenSize2 = 0x4c;

	constexpr uint64_t EquippableModels = 0xe8;
	constexpr uint64_t PossibleSkins = 0x150;
	constexpr uint64_t PossibleLevels = 0x138;
	constexpr uint64_t bIsUnlockedByConfig = 0xfe;
	constexpr uint64_t bIsOwned = 0xf2;
	constexpr uint64_t bIsFavorite = 0xf3;
	constexpr uint64_t PossibleChromas = 0x128;


	constexpr uint64_t viewport_world = 0x80;

	constexpr uint64_t AspectRatio = 0x428;

	constexpr uint64_t vmthook = 0x68;

	constexpr uint64_t Engine = 0x28;

	constexpr uint64_t IsDormant = 0x101;

	constexpr uint64_t SetCameraPOVHook = 0xD7;

	constexpr uint64_t viewport_gameinstance = 0x88;


	constexpr uintptr_t Mesh1P_Offset = 0xf30;
	constexpr uintptr_t Mesh3P_Offset = 0xf40;
	constexpr uintptr_t MeshOverlay1P_Offset = 0xf38;

	constexpr uintptr_t Mesh1POverlayMIDs = 0x0FA0;
	constexpr uintptr_t Mesh1PMIDs = 0x0F90;
	constexpr uintptr_t Mesh3PMIDs = 0x0F80;
	constexpr uintptr_t fmemory_needed = 0x10;


	constexpr uintptr_t NoSpreadNeed = 0xD8;


}

namespace globals
{
	namespace misc {
		inline bool hide_watermark = false;
		inline bool hide_lubov_evgenievna = true;

		inline int MenuKey = VK_INSERT;
		inline bool skinchangor = false;
		inline bool skiptutorial = false;
		inline float glow_float = 1.0f;
		inline bool finisher = false;
		inline bool onlylastkill = false;
		inline bool skin_changer = false;
	}
	namespace buddy {
		inline bool enabled = false;
		inline int index = 0;
	}
	namespace il {
		static bool init = false;

		inline bool enable = false;
		inline bool random_agent = false;
		inline int lock_agent = 0;
	}
}