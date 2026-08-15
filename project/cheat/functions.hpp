#pragma once
#include "../sdk/offsets.hpp"
#include "../sdk/memory.hpp"
#include "../sdk/math.hpp"
#include "../sdk/structs.hpp"
#include "../encrypt/xor.hpp"
#include <Windows.h>
#include <chrono>
#include "../sdk/spoof.h"
#include "../sdk/ret_spoof.h"
#include <algorithm>



enum class EAresOutlineMode
{
	None = 0,
	Outline = 1,
	Block = 2,
	Enemy = 3,
	AlwaysOutline = 4,
	AlwaysEnemy = 5,
	EAresOutlineMode_MAX = 6,
};

class fmemory {
public:
	static uint64_t malloc(int32_t size, uint32_t aligment);
};

namespace fmemory2 {
	uint64_t malloc2(int32_t size, uint32_t alignment);
}

class fmemory3 {
public:
	static uint64_t malloc3(int32_t size, uint32_t aligment);
};

class UObject
{
public:


	char padding_01[0x18];
	int32_t ComparisonIndex;

	static UObject* StaticFindObject(const wchar_t* Name)
	{

		static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;
		return reinterpret_cast<UObject * (__fastcall*)(UObject*, UObject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(nullptr, reinterpret_cast<UObject*>(-1), Name, false, offsets::MagicOffsets, (void*)StaticFindObjectAddress);
	}
	static UObject* StaticFindObject(UObject* Class, UObject* InOuter, const wchar_t* Name, bool ExactClass)
	{

		static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;
		return reinterpret_cast<UObject * (__fastcall*)(UObject*, UObject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(Class, InOuter, Name, ExactClass, offsets::MagicOffsets, (void*)StaticFindObjectAddress);
	}

	template<typename type = UObject> static inline type find_object2(const wchar_t* name, UObject* outer = nullptr, bool exact = false) {

		return reinterpret_cast<type>(UObject::StaticFindObject(nullptr, outer, name, exact));
	}
	template<typename type = UObject> static inline type* find_object1(const wchar_t* name, UObject* outer = reinterpret_cast<UObject*>(-1), bool exact = false) {

		return reinterpret_cast<type*>(UObject::StaticFindObject(nullptr, outer, name, exact));
	}
	template<typename type = UObject> static inline type* find_object(const wchar_t* name, UObject* outer = nullptr, bool exact = false) {

		return reinterpret_cast<type*>(UObject::StaticFindObject(nullptr, outer, name, exact));
	}

	static void ProcessEvent(void* class_, UObject* function, void* params)
	{

		static uintptr_t negritas = memory::module_base + offsets::process_event;
		reinterpret_cast<void (*)(void*, UObject*, void*, uintptr_t, void*)>(spoofcall_stub)(class_, function, params, offsets::MagicOffsets, (void*)negritas);
	}
	void ProcessEvent(void* class_, void* params)
	{

		static uintptr_t negritas = memory::module_base + offsets::process_event;
		reinterpret_cast<void (*)(void*, UObject*, void*, uintptr_t, void*)>(spoofcall_stub)(class_, this, params, offsets::MagicOffsets, (void*)negritas);
	}

	void ProcessEvent_(UObject* function, void* params) {

		static uintptr_t negritas = memory::module_base + offsets::process_event;
		reinterpret_cast<void (*)(UObject*, UObject*, void*, uintptr_t, void*)>(spoofcall_stub)(this, function, params, offsets::MagicOffsets, (void*)negritas);

	}


	void ProcessEventx(UObject* Function, void* args, void* out_args = nullptr, void* stack = nullptr) {

		if (!Function || !this)
			return;

		static void(__fastcall * process_event_func)(UObject*, UObject*, void*, void*, void*, uintptr_t, void*);
		if (!process_event_func) {
			process_event_func = reinterpret_cast<decltype(process_event_func)>(spoofcall_stub);
		}
		return process_event_func(this, Function, args, out_args, stack, offsets::MagicOffsets, (void*)(memory::module_base + offsets::process_event));
	}

	static UObject* StaticLoadObject(const wchar_t* ObjectPath) {

		if (!ObjectPath)
			return nullptr;


		static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
		return reinterpret_cast<UObject * (__fastcall*)(UObject*, UObject*, const wchar_t*, const wchar_t*, uint32_t, uint32_t, void*, uintptr_t, void*)>(spoofcall_stub)(nullptr, nullptr, ObjectPath, nullptr, 0, 0, nullptr, offsets::MagicOffsets, (void*)StaticLoadObjectAddress);


	}


	template <typename type = UObject>
	type* cast() {
		return reinterpret_cast<type*>(this);
	}


};



//class TUObjectArrayWrapper
//{
//private:
//	friend class UObject;
//
//private:
//	void* GObjectsAddress = nullptr;
//
//private:
//	TUObjectArrayWrapper() = default;
//
//public:
//	TUObjectArrayWrapper(TUObjectArrayWrapper&&) = delete;
//	TUObjectArrayWrapper(const TUObjectArrayWrapper&) = delete;
//
//	TUObjectArrayWrapper& operator=(TUObjectArrayWrapper&&) = delete;
//	TUObjectArrayWrapper& operator=(const TUObjectArrayWrapper&) = delete;
//
//private:
//	inline void InitGObjects()
//	{
//		GObjectsAddress = reinterpret_cast<void*>(InSDKUtils::GetImageBase() + Offsets::GObjects);
//	}
//
//public:
//	inline void InitManually(void* GObjectsAddressParameter)
//	{
//		GObjectsAddress = GObjectsAddressParameter;
//	}
//
//	inline class TUObjectArray* operator->()
//	{
//		if (!GObjectsAddress) [[unlikely]]
//			InitGObjects();
//
//		return reinterpret_cast<class TUObjectArray*>(GObjectsAddress);
//	}
//
//	inline TUObjectArray& operator*() const
//	{
//		return *reinterpret_cast<class TUObjectArray*>(GObjectsAddress);
//	}
//
//	inline operator const void* ()
//	{
//		if (!GObjectsAddress) [[unlikely]]
//			InitGObjects();
//
//		return GObjectsAddress;
//	}
//
//	inline class TUObjectArray* GetTypedPtr()
//	{
//		if (!GObjectsAddress) [[unlikely]]
//			InitGObjects();
//
//		return reinterpret_cast<class TUObjectArray*>(GObjectsAddress);
//	}
//};

class uclass;
class uobject {
public:
	void* VTable;
	int32_t   ObjectFlags;
	int32_t   InternalIndex;
	uclass* ClassPrivate;
	fname   NamePrivate;
	UObject* OuterPrivate;


	uclass* object_class();

	template <typename t>
	static t static_find_object(uobject* klass, uobject* outer, const wchar_t* name) {

		auto fn_addr = memory::module_base + offsets::static_find_object;
		return reinterpret_cast<t(*)(uobject*, uobject*, const wchar_t*, uintptr_t, void*)>(spoofcall_stub)(klass, outer, name, offsets::MagicOffsets, (void*)fn_addr);
	}

	template<typename type = UObject> static inline type find_object2(const wchar_t* name, UObject* outer = nullptr, bool exact = false) {

		return reinterpret_cast<type>(UObject::StaticFindObject(nullptr, outer, name, exact));
	}

	template <typename t>
	static t find_object(const wchar_t* name, uobject* outer = nullptr) {
		return uobject::static_find_object<t>(nullptr, outer, name);
	}



	static inline void* static_find_object3(uclass* klass, uobject* outer, const wchar_t* name, bool exact) {
		static void* (__fastcall * find_obj_func)(uclass*, uobject*, const wchar_t*, bool);
		if (!find_obj_func) {
			find_obj_func = reinterpret_cast<decltype(find_obj_func)>(memory::module_base + offsets::static_find_object);
		}
		return SPOOF_CALL(find_obj_func)(klass, outer, name, exact);
	}


	template<typename type = uobject> static inline type* find_object13(const wchar_t* name, uobject* outer = nullptr, bool exact1 = false) {
		return reinterpret_cast<type*>(uobject::static_find_object3 (nullptr, outer, name, exact1));
	}



	static uobject* StaticLoadObject(const wchar_t* Name);

	void set_vector_parameter_value2(fname parameter_name, flinearcolor value);
	void set_scalar_parameter_value2(fname parameter_name, float value);
	static uobject* StaticFindObject(uobject* Class, uobject* InOuter, const wchar_t* Name, bool ExactClass);

	void process_event(uobject* function, void* args);
	void ProcessEvent(void* class_, uobject* function, void* params);
	void ProcessEvent(void* class_, void* params);
	void ProcessEvent_(uobject* function, void* params);
	void process_event35(uobject* function, void* args);
	void ProcessEvent_2(uobject* function, void* params);
	bool is_child_of(uclass* parent);

	void process_event_2(uobject* function, void* args);


	template <typename type = uobject>
	type* cast() {
		return reinterpret_cast<type*>(this);
	}
};

template<class type> class enum_as_byte {
public:
	enum_as_byte() {}
	enum_as_byte(type value) : value(static_cast<std::uint8_t>(value)) {}

	explicit enum_as_byte(std::int32_t value) : value(static_cast<std::uint8_t>(value)) {}
	explicit enum_as_byte(std::uint8_t value) : value(value) {}

	operator type() const { return type(value); }
	type get() const { return type(value); }

private:
	std::uint8_t value;
};

class ufield : public uobject
{
public:
	ufield* next;
};

class ustruct : public ufield
{
public:
	ustruct* super_field;
	ufield* children;
	std::int32_t property_size;
	std::int32_t min_alignment;
};

class uclass : public ustruct
{

};

static enum search_case : std::uint8_t {
	case_sensitive, ignore_case
};

struct FDisplayName : uobject
{
public:
	fstring FullName;
	fstring GameName;
	fstring TagLine;
};



class BlindManagerComponent : public uobject
{
public:
	bool IsBlinded() {
		uobject* function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.IsBlinded");

		if (function == nullptr) {
			return false;
		}

		struct {
			bool return_value;
		} params;

		this->process_event(function, &params);

		return params.return_value;
	}

	void SetBlind(bool value) {
		uobject* function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.SetBlinded");

		if (function == nullptr) {
			return;
		}

		struct {
			bool blinded_value;
		} params = { value };

		this->process_event(function, &params);
	}

	void ClientCleanseBlinds()
	{
		uobject* function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.ClientCleanseBlinds");

		if (function == nullptr) {
			return;
		}

		this->process_event(function, nullptr);
	}

	static void use_blind_manager_component(uobject* target_object) {


		auto* blind_manager = static_cast<BlindManagerComponent*>(target_object);

		if (blind_manager == nullptr) {
			return;
		}
		bool blinded = blind_manager->IsBlinded();

		if (blinded)
		{
			blind_manager->SetBlind(false);

			blind_manager->ClientCleanseBlinds();
		}

	}
};


struct FSoftObjectPath {
	fname AssetPathName; // 0x00(0x0c)
	char pad_C[0x4]; // 0x0c(0x04)
	fstring SubPathString; // 0x10(0x10)
};

enum class EChatRoomType : uint8_t
{
	Party = 0,
	Pregame = 1,
	All = 2,
	Team = 3,
	InGameSystem = 4,
	System = 5,
	Whisper = 6,
	Count = 7,
	EChatRoomType_MAX = 8,
};
struct EquippableGroundPickup_C : uobject {

};


struct UEngine : uobject {
	char pad_30[0x8]; // 0x30(0x08)
	uobject* TinyFont; // 0x38(0x08)
	FSoftObjectPath TinyFontName; // 0x40(0x20)
	uobject* SmallFont; // 0x60(0x08)
	FSoftObjectPath SmallFontName; // 0x68(0x20)
	uobject* MediumFont; // 0x88(0x08)
	FSoftObjectPath MediumFontName; // 0x90(0x20)
	uobject* LargeFont; // 0xb0(0x08)
	FSoftObjectPath LargeFontName; // 0xb8(0x20)
	uobject* SubtitleFont; // 0xd8(0x08)
	FSoftObjectPath SubtitleFontName; // 0xe0(0x20)
	tarray< uobject*> AdditionalFonts; // 0x100(0x10)
	tarray< fstring> AdditionalFontNames; // 0x110(0x10)
};




// Unreal Engine's EDrawDebugTrace (simplified)
enum EDrawDebugTrace : uint8_t
{
	None = 0,
	ForOneFrame = 1,
	ForDuration = 2,
	Persistent = 3,
	EDrawDebugTrace_MAX = 4
};

fstring get_object_namemaw(uobject* obj);

class ugameviewportclient : public uobject {
public:
	struct uworld* get_world();
	struct ugameinstance* get_gameinstance();
};

class ulocalplayer : public uobject {
public:
	ugameviewportclient* viewport_client();
};

class uengine : public uobject
{
public:
	uobject* font();
};

class UAresClientGameInstance : public uobject
{
public:


	static UAresClientGameInstance* GetAresClientGameInstance(uobject* WorldContextObject);
};

class ugameinstance : public uobject {
public:
	uengine* get_uengine();
	tarray<ulocalplayer*> local_players();

};

class uworld : public uobject
{
public:
	ugameinstance* game_instance();
};


enum class EPhysicalSurface  {
	SurfaceType_Default = 0,
	SurfaceType1 = 1,
	SurfaceType2 = 2,
	SurfaceType3 = 3,
	SurfaceType4 = 4,
	SurfaceType5 = 5,
	SurfaceType6 = 6,
	SurfaceType7 = 7,
	SurfaceType8 = 8,
	SurfaceType9 = 9,
	SurfaceType10 = 10,
	SurfaceType11 = 11,
	SurfaceType12 = 12,
	SurfaceType13 = 13,
	SurfaceType14 = 14,
	SurfaceType15 = 15,
	SurfaceType16 = 16,
	SurfaceType17 = 17,
	SurfaceType18 = 18,
	SurfaceType19 = 19,
	SurfaceType20 = 20,
	SurfaceType21 = 21,
	SurfaceType22 = 22,
	SurfaceType23 = 23,
	SurfaceType24 = 24,
	SurfaceType25 = 25,
	SurfaceType26 = 26,
	SurfaceType27 = 27,
	SurfaceType28 = 28,
	SurfaceType29 = 29,
	SurfaceType30 = 30,
	SurfaceType31 = 31,
	SurfaceType32 = 32,
	SurfaceType33 = 33,
	SurfaceType34 = 34,
	SurfaceType35 = 35,
	SurfaceType36 = 36,
	SurfaceType37 = 37,
	SurfaceType38 = 38,
	SurfaceType39 = 39,
	SurfaceType40 = 40,
	SurfaceType41 = 41,
	SurfaceType42 = 42,
	SurfaceType43 = 43,
	SurfaceType44 = 44,
	SurfaceType45 = 45,
	SurfaceType46 = 46,
	SurfaceType47 = 47,
	SurfaceType48 = 48,
	SurfaceType49 = 49,
	SurfaceType50 = 50,
	SurfaceType51 = 51,
	SurfaceType52 = 52,
	SurfaceType53 = 53,
	SurfaceType54 = 54,
	SurfaceType55 = 55,
	SurfaceType56 = 56,
	SurfaceType57 = 57,
	SurfaceType58 = 58,
	SurfaceType59 = 59,
	SurfaceType60 = 60,
	SurfaceType61 = 61,
	SurfaceType62 = 62,
	SurfaceType_Max = 63,
	EPhysicalSurface_MAX = 64
};
enum class EFrictionCombineMode
{
	Average = 0,
	Min = 1,
	Multiply = 2,
	Max = 3,
	EFrictionCombineMode_MAX = 4,
};


struct UPhysicalMaterial : uobject {
	float Friction; // 0x30(0x04)
	float StaticFriction; // 0x34(0x04)
	EFrictionCombineMode FrictionCombineMode; // 0x38(0x01)
	bool bOverrideFrictionCombineMode; // 0x39(0x01)
	char pad_3A[0x2]; // 0x3a(0x02)
	float Restitution; // 0x3c(0x04)
	EFrictionCombineMode RestitutionCombineMode; // 0x40(0x01)
	bool bOverrideRestitutionCombineMode; // 0x41(0x01)
	char pad_42[0x2]; // 0x42(0x02)
	float Density; // 0x44(0x04)
	float SleepLinearVelocityThreshold; // 0x48(0x04)
	float SleepAngularVelocityThreshold; // 0x4c(0x04)
	int32_t SleepCounterThreshold; // 0x50(0x04)
	float RaiseMassToPower; // 0x54(0x04)
	float DestructibleDamageThresholdScale; // 0x58(0x04)
	char pad_5C[0x4]; // 0x5c(0x04)
	uobject* PhysicalMaterialProperty; // 0x60(0x08)
	EPhysicalSurface SurfaceType; // 0x68(0x01)
	char pad_69[0x3]; // 0x69(0x03)
	uobject* Strength; // 0x6c(0x0c)
	EPhysicalSurface AudioSurfaceType; // 0x78(0x01)
	char pad_79[0x1f]; // 0x79(0x1f)
};

class UMaterialInterface : public uobject
{
public:

	char pad_30[0x10]; // 0x30(0x10)
	uobject* SubsurfaceProfile; // 0x40(0x08)
	tarray<uobject*> SpecularProfiles; // 0x48(0x10)
	char bIncludedInBaseGame : 1; // 0x58(0x01)
	char pad_58_1 : 7; // 0x58(0x01)
	char pad_59[0x17]; // 0x59(0x17)
	uobject* LightmassSettings; // 0x70(0x24)
	char pad_94[0x4]; // 0x94(0x04)
	struct tarray<struct FMaterialTextureInfo> TextureStreamingData; // 0x98(0x10)
	struct tarray<struct UAssetUserData*> AssetUserData; // 0xa8(0x10)
	char pad_B8[0x18]; // 0xb8(0x18)

	e_blend_mode GetBlendMode();
	UPhysicalMaterial* GetPhysicalMaterial();

};

class UMaterialInstanceDynamic : public UMaterialInterface {
public:
	void SetVectorParameterValue(fname ParameterName, flinearcolor Value);

	void set_vector_parameter_value(fname parameter_name, flinearcolor value);
	void set_vector_parameter_value2(fname parameter_name, flinearcolor value);

	void set_scalar_parameter_value(fname parameter_name, float value);
	void set_scalar_parameter_value2(fname parameter_name, float value);

	void set_texture_parameter_value(fname parameter_name, uobject* texture);
	void set_texture_parameter_value2(fname parameter_name, uobject* texture);


};

enum class ETraceTypeQuery : uint8_t
{
	TraceTypeQuery1 = 0,
	TraceTypeQuery2 = 1,
	TraceTypeQuery3 = 2,
	TraceTypeQuery4 = 3,
	TraceTypeQuery5 = 4,
	TraceTypeQuery6 = 5,
	TraceTypeQuery7 = 6,
	TraceTypeQuery8 = 7,
	TraceTypeQuery9 = 8,
	TraceTypeQuery10 = 9,
	TraceTypeQuery11 = 10,
	TraceTypeQuery12 = 11,
	TraceTypeQuery13 = 12,
	TraceTypeQuery14 = 13,
	TraceTypeQuery15 = 14,
	TraceTypeQuery16 = 15,
	TraceTypeQuery17 = 16,
	TraceTypeQuery18 = 17,
	TraceTypeQuery19 = 18,
	TraceTypeQuery20 = 19,
	TraceTypeQuery21 = 20,
	TraceTypeQuery22 = 21,
	TraceTypeQuery23 = 22,
	TraceTypeQuery24 = 23,
	TraceTypeQuery25 = 24,
	TraceTypeQuery26 = 25,
	TraceTypeQuery27 = 26,
	TraceTypeQuery28 = 27,
	TraceTypeQuery29 = 28,
	TraceTypeQuery30 = 29,
	TraceTypeQuery31 = 30,
	TraceTypeQuery32 = 31,
	TraceTypeQuery_MAX = 32,
	ETraceTypeQuery_MAX = 33,
};


struct AActor : public uobject {
	
	AActor* GetOwner() {  // <- mark const
		static uobject* Function = uobject::find_object<uobject*>(L"Engine.Actor.GetOwner");
		if (!Function) return nullptr;  // <- must return a value

		struct Params {
			AActor* ReturnValue;
		} args;

		Function->ProcessEvent(this, Function, &args);
		return args.ReturnValue;
	}

	fvector K2_GetActorLocation() {
		auto function_name = crypt(L"Engine.Actor.K2_GetActorLocation").decrypt();
		static uobject* Function = nullptr;

		if (!Function)
			Function = uobject::StaticFindObject(nullptr, nullptr, function_name, false);

		if (!Function)
			return { 0, 0, 0 };

		struct {
			fvector Out;
		} Parameters;

		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}

	void GetAllChildActors(tarray<AActor*>& OutChildren, bool bIncludeDescendants) {
		static uobject* Function = uobject::find_object<uobject*>(L"Engine.Actor.GetAllChildActors");
		if (!Function) return;

		struct Params {
			tarray<AActor*> OutChildren;
			bool bIncludeDescendants;
		} args;

		args.bIncludeDescendants = bIncludeDescendants;
		Function->ProcessEvent(this, Function, &args);

		OutChildren = args.OutChildren;
	}

};

enum class EEffectAttachType : uint8_t {
	NotAttached = 0,
	RootComponent = 1,
	Attach1P = 2,
	Attach3P = 3,
	Count = 4,
	EEffectAttachType_MAX = 5
};

enum class EMovementSyncType : uint8_t {
	Always = 0,
	Never = 1,
	SpectatorOnly = 2,
	Count = 3,
	EMovementSyncType_MAX = 4
};



struct AEffectContainer : AActor {
	char pad_460[0x10]; // 0x460(0x10)
	uobject* Pool; // 0x470(0x08)
	uobject* EffectID; // 0x478(0x20)
	uobject* EffectData; // 0x498(0x58)
	uobject* OnStartEffect; // 0x4f0(0x10)
	uobject* OnUpdateEffectPerspective; // 0x500(0x10)
	uobject* OnEffectDataUpdated; // 0x510(0x10)
	uobject* OnStopEffect; // 0x520(0x10)
	uobject* OnResetEffect; // 0x530(0x10)
	EEffectAttachType AttachType; // 0x540(0x01)
	bool bObeyOwnerHidden; // 0x541(0x01)
	EMovementSyncType MovementSyncType; // 0x542(0x01)
	bool bPureEffect; // 0x543(0x01)
	uobject* SpawnType; // 0x544(0x01)
	bool bCosmeticEffect; // 0x545(0x01)
	bool bForceOneShotEffect; // 0x546(0x01)
	char pad_547[0x1]; // 0x547(0x01)
	float ReplayEffectOffsetTime; // 0x548(0x04)
	char pad_54C[0x1]; // 0x54c(0x01)
	bool bCurrentPerspectiveIsFirstPerson; // 0x54d(0x01)
	char pad_54E[0x2]; // 0x54e(0x02)
	float EffectTailTime; // 0x550(0x04)
	char pad_554[0x8]; // 0x554(0x08)
	float CumulativeTotalLifeSpan; // 0x55c(0x04)
	char pad_560[0x78]; // 0x560(0x78)
	uobject* PureEffectInstance; // 0x5d8(0x08)
	char pad_5E0[0x8]; // 0x5e0(0x08)
	uobject* OwningManager; // 0x5e8(0x08)
	AActor* OriginalTarget; // 0x5f0(0x08)
	char pad_5F8[0x8]; // 0x5f8(0x08)
};

struct UPrimitiveComponent : uobject {
public:

	char pad_330[0x18]; // 0x330(0x18)
	uobject* UmbraCullingMode; // 0x348(0x01)
	uobject* PrepassCullMode; // 0x349(0x01)
	char pad_34A[0x2]; // 0x34a(0x02)
	float MinDrawDistance; // 0x34c(0x04)
	float LDMaxDrawDistance; // 0x350(0x04)
	float CachedMaxDrawDistance; // 0x354(0x04)
	float CachedVertexFogIntensityFromVolumes; // 0x358(0x04)
	uobject* DepthPriorityGroup; // 0x35c(0x01)
	uobject* ViewOwnerDepthPriorityGroup; // 0x35d(0x01)
	uobject* IndirectLightingCacheQuality; // 0x35e(0x01)
	uobject* LightmapType; // 0x35f(0x01)
	uobject* HLODBatchingPolicy; // 0x360(0x01)
	char bEnableAutoLODGeneration : 1; // 0x361(0x01)
	char bIsActorTextureStreamingBuiltData : 1; // 0x361(0x01)
	char bIsValidTextureStreamingBuiltData : 1; // 0x361(0x01)
	char pad_361_3 : 5; // 0x361(0x01)
	char pad_362[0x2]; // 0x362(0x02)
	char bIsFirstPerson : 1; // 0x364(0x01)
	char bIgnoreFOVChanges : 1; // 0x364(0x01)
	char pad_364_2 : 6; // 0x364(0x01)
	char pad_365[0x3]; // 0x365(0x03)
	char bNeverDistanceCull : 1; // 0x368(0x01)
	char pad_368_1 : 7; // 0x368(0x01)
	char pad_369[0x17]; // 0x369(0x17)
	char pad_380_0 : 2; // 0x380(0x01)
	char bAlwaysCreatePhysicsState : 1; // 0x380(0x01)
	char bGenerateOverlapEvents : 1; // 0x380(0x01)
	char bMultiBodyOverlap : 1; // 0x380(0x01)
	char bTraceComplexOnMove : 1; // 0x380(0x01)
	char bReturnMaterialOnMove : 1; // 0x380(0x01)
	char bUseViewOwnerDepthPriorityGroup : 1; // 0x380(0x01)
	char bAllowCullDistanceVolume : 1; // 0x381(0x01)
	char bVisibleInReflectionCaptures : 1; // 0x381(0x01)
	char bVisibleInRealTimeSkyCaptures : 1; // 0x381(0x01)
	char bVisibleInRayTracing : 1; // 0x381(0x01)
	char bRenderInMainPass : 1; // 0x381(0x01)
	char bRenderInDepthPass : 1; // 0x381(0x01)
	char bReceivesDecals : 1; // 0x381(0x01)
	char bReceivesFloorOnlyDecals : 1; // 0x381(0x01)
	char bDisableRGBAWrite : 1; // 0x382(0x01)
	char bHoldout : 1; // 0x382(0x01)
	char bOwnerNoSee : 1; // 0x382(0x01)
	char bOnlyOwnerSee : 1; // 0x382(0x01)

	void SetRenderCustomDepth(bool bValue);
	void set_material(int32_t element_index, uobject* material);
	void set_is_first_person(bool value) {
		if (!this) return;

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetIsFirstPerson"));

		this->process_event(fn, &value);
	}

	uobject* CreateAndSetMaterialInstanceDynamicFromMaterial(int32_t element_index, uobject* material);
	UMaterialInterface* GetMaterial(int32_t ElementIndex) {
		
		uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.GetMaterial").decrypt());
		if (!function) {
			return nullptr;
		}

		struct {
			int32_t ElementIndex;
			UMaterialInterface* ReturnValue;
		} Parameters;

		Parameters.ElementIndex = ElementIndex;
		Parameters.ReturnValue = nullptr;
		this->process_event(function, &Parameters);
		return Parameters.ReturnValue;
	}


	int32_t GetNumMaterials();

	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
		if (!this || !parent) return nullptr;

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial").decrypt());

		struct {
			int32_t element_index;
			uobject* parent;
			uobject* return_value;
		} params = { element_index, parent };

		this->ProcessEvent_(fn, &params);
		return params.return_value;
	}


	UMaterialInstanceDynamic* get_material(int32_t element_index);

	int32_t get_num_materials();
	void SetCastShadow(bool NewCastShadow);



};

typedef          int    int32;
typedef unsigned char   uint8;

class AActor;
class UPrimitiveComponent;
enum class ECollisionChannel : uint8 {
	ECC_WorldStatic = 0,
	ECC_WorldDynamic = 1,
	ECC_Pawn = 2,
	ECC_Visibility = 3,
	ECC_Camera = 4,
	ECC_PhysicsBody = 5,
	ECC_Vehicle = 6,
	ECC_Destructible = 7,
	ECC_EngineTraceChannel1 = 8,
	ECC_EngineTraceChannel2 = 9,
	ECC_EngineTraceChannel3 = 10,
	ECC_EngineTraceChannel4 = 11,
	ECC_EngineTraceChannel5 = 12,
	ECC_EngineTraceChannel6 = 13,
	ECC_GameTraceChannel1 = 14,
	ECC_GameTraceChannel2 = 15,
	ECC_GameTraceChannel3 = 16,
	ECC_GameTraceChannel4 = 17,
	ECC_GameTraceChannel5 = 18,
	ECC_GameTraceChannel6 = 19,
	ECC_GameTraceChannel7 = 20,
	ECC_GameTraceChannel8 = 21,
	ECC_GameTraceChannel9 = 22,
	ECC_GameTraceChannel10 = 23,
	ECC_GameTraceChannel11 = 24,
	ECC_GameTraceChannel12 = 25,
	ECC_GameTraceChannel13 = 26,
	ECC_GameTraceChannel14 = 27,
	ECC_GameTraceChannel15 = 28,
	ECC_GameTraceChannel16 = 29,
	ECC_GameTraceChannel17 = 30,
	ECC_GameTraceChannel18 = 31,
	ECC_OverlapAll_Deprecated = 32,
	ECC_MAX = 33
};


struct FPhysicalMaterialStrength
{
public:
	float                                         TensileStrength;                                   // 0x0000(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CompressionStrength;                               // 0x0004(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ShearStrength;                                     // 0x0008(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};


struct FHitResult2
{
	int32 FaceIndex; // 0x0
	float Time; // 0x4
	float Distance; // 0x8
	fvector Location; // 0x10
	fvector ImpactPoint; // 0x28
	fvector Normal; // 0x40
	fvector ImpactNormal; // 0x58
	fvector TraceStart; // 0x70	
	fvector TraceEnd; // 0x88
	float PenetrationDepth; // 0xa0
	int32 MyItem; // 0xa4
	int32 Item; // 0xa8
	uint8 ElementIndex; // 0xac
	uint8 bBlockingHit : 1; // 0xad
	uint8 bStartPenetrating : 1; // 0xad
	uint8 PadFlags : 6; // padding bits
	uint8 Pad_AE[0x2]; // padding to align next member (0xb0)
	UPhysicalMaterial* PhysMaterial; // 0xb0 (8 bytes)
	AActor* Actor; // 0xb8  ? (8 bytes)
	UPrimitiveComponent* Component; // 0xc0
	uint8 Pad_C8[0x10]; // 0xc8 (padding to 0xd8)
	fname BoneName; // 0xd8
	fname MyBoneName; // 0xe4
};



class FWeakObjectPtr
{
public:
	int32                                         ObjectIndex;                                       // 0x0000(0x0004)(NOT AUTO-GENERATED PROPERTY)
	int32                                         ObjectSerialNumber;                                // 0x0004(0x0004)(NOT AUTO-GENERATED PROPERTY)

public:
	class UObject* Get() const; // Function: 0xFFFF80093C7F000F
	class UObject* operator->() const; // Function: 0xFFFF80093C7F000F
	bool operator==(const FWeakObjectPtr& Other) const; // Function: 0xFFFF80093C7F000F
	bool operator!=(const FWeakObjectPtr& Other) const; // Function: 0xFFFF80093C7F000F
	bool operator==(const class UObject* Other) const; // Function: 0xFFFF80093C7F000F
	bool operator!=(const class UObject* Other) const; // Function: 0x9FFF8C0A0526A667

};


template<typename UEType>
class TWeakObjectPtr : public FWeakObjectPtr
{
public:
	UEType* Get() const
	{
		return static_cast<UEType*>(FWeakObjectPtr::Get());
	}

	UEType* operator->() const
	{
		return static_cast<UEType*>(FWeakObjectPtr::Get());
	}
};

struct FActorInstanceHandle : AActor {
	struct TWeakObjectPtr<AActor> Actor; // 0x00(0x08)
	char pad_8[0x10]; // 0x08(0x10)
};

class AActor;
class UPrimitiveComponent;
class UPhysicalMaterial;

struct FHitResult
{
	int32 FaceIndex;                    // 0x00(0x04)
	float Time;                         // 0x04(0x04)
	float Distance;                     // 0x08(0x04)
	char pad_0C[0x4];                   // 0x0C(0x04)
	fvector Location;                   // 0x10(0x18)
	fvector ImpactPoint;                // 0x28(0x18)
	fvector Normal;                     // 0x40(0x18)
	fvector ImpactNormal;               // 0x58(0x18)
	fvector TraceStart;                 // 0x70(0x18)
	fvector TraceEnd;                   // 0x88(0x18)
	float PenetrationDepth;             // 0xA0(0x04)
	int32 MyItem;                       // 0xA4(0x04)
	int32 Item;                         // 0xA8(0x04)
	uint8 ElementIndex;                 // 0xAC(0x01)
	uint8 bBlockingHit : 1;             // 0xAD
	uint8 bStartPenetrating : 1;
	uint8 pad_AD_bits : 6;
	char pad_AE[0x2];                   // 0xAE(0x02)
	UPhysicalMaterial* PhysMaterial;    // 0xB0(0x08)
	AActor* Actor;                      // 0xB8(0x08) - keep your pointer
	char pad_ActorHandle[0x10];         // 0xC0(0x10) - pad remaining 16 bytes
	UPrimitiveComponent* Component;     // 0xD0(0x08)
	fname BoneName;                     // 0xD8
	fname MyBoneName;                   // 0xE4
	char pad_END[0x8];                  // padding to 0xF0
};

struct FWallSpanInfo {
	FHitResult Entrance;    // 0x00(0xf0)
	FHitResult Exit;        // 0xf0(0xf0)
};


struct FWallSpanList {
	tarray<FWallSpanInfo> Spans;        // 0x00(0x10)
	bool bLastPointInWall;              // 0x10(0x01)
	char pad_11[0x7];                   // 0x11(0x07)
	FHitResult EntranceToLastPoint;     // 0x18(0xf0)
};




struct FStaticMaterial {
	UMaterialInterface* MaterialInterface; // 0x00(0x08)
    fname MaterialSlotName; // 0x08(0x0c)
	fname ImportedMaterialSlotName; // 0x14(0x0c)
	uobject* UVChannelData; // 0x20(0x14)
	char pad_34[0x4]; // 0x34(0x04)

};
enum class EAresSurfaceType : uint8 {
	Default = 0,
	Concrete = 1,
	Dirt = 2,
	Gravel = 3,
	Water = 4,
	Metal = 5,
	Wood = 6,
	Grass = 7,
	Glass = 8,
	Flesh = 9,
	Snow = 10,
	MetalThin = 11,
	BrokenGlass = 12,
	Impenetrable = 13,
	Linoleum = 14,
	BubbleCage = 15,
	MetalNonResonant = 16,
	CarpetOnWood = 17,
	MetalPipe = 18,
	ConcretePuddle = 19,
	GarbageBag = 20,
	Thorns = 21,
	Sand = 22,
	Mud = 23,
	Tree = 24,
	Ice = 25,
	ShootinRangeTarget = 26,
	Cloth = 27,
	CobbleStone = 28,
	CeramicTile = 29,
	CarpetOnConcrete = 30,
	EtherGlass = 31,
	CosmicFabric = 32,
	GoldenRipple = 33,
	PlasticHollow = 34,
	Shield = 35,
	Count = 36,
	EAresSurfaceType_MAX = 37
};



struct UWorld2 : public uobject
{
	static UWorld2* GetWorld()
	{
		uintptr_t* UWorldRead_SECOND = memory::read<uintptr_t*>(memory::module_base + offsets::State2); // wrong
		auto UWorld_RESULT_SECOND = memory::read<UWorld2*>(uintptr_t(UWorldRead_SECOND));
		return UWorld_RESULT_SECOND;

	
	}
};



class system : public uobject
{
public:
	
	static fstring get_object_name(uobject* object);
	static FString get_object_name2(uobject* object);
	static bool contains_string(const wchar_t* search_in, const wchar_t* sub_string, bool use_case = false, bool search_from_end = false);
	static bool starts_with(const wchar_t* source, const wchar_t* prefix, const enum_as_byte<search_case>& search_case = ignore_case);
	uobject* get_outer_object(uobject* object);

	static bool LineTraceSingle2(
		UWorld2* WorldContextObject,
		FVector Start,
		FVector End,
		ETraceTypeQuery TraceChannel,
		bool bTraceComplex,
		TArray<AActor*> ActorsToIgnore,
		EDrawDebugTrace DrawDebugType,
		FHitResult& OutHit,
		bool bIgnoreSelf,
		flinearcolor TraceColor,
		flinearcolor TraceHitColor,
		float DrawTime
	);

	static bool LineTraceSingle(
		UWorld2* WorldContextObject,
		fvector Start,
		fvector End,
		ETraceTypeQuery TraceChannel,
		bool bTraceComplex,
		tarray<AActor*> ActorsToIgnore,
		EDrawDebugTrace DrawDebugType,
		FHitResult& OutHit,
		bool bIgnoreSelf,
		flinearcolor TraceColor,
		flinearcolor TraceHitColor,
		float DrawTime
	);

	static inline __int64 decrypt_parent(uobject* parent) {

		static __int64(__fastcall * decrypt_function)(__int64);
		if (!decrypt_function) {
			auto niga = memory::module_base + offsets::skin_decrypt;
			return reinterpret_cast<__int64(*)(__int64, uintptr_t, void*)>(spoofcall_stub)((__int64)parent, offsets::MagicOffsets, (void*)niga);
			//decrypt_function = reinterpret_cast<decltype(decrypt_function)>(offsets::skin_decrypt + memory::module_base);
		}

		if (!decrypt_function) return 0x0;

		return decrypt_function((__int64)parent);
	}
};

class string : public uobject
{
public:

	static fstring Conv_NameToString(fname string);

	static fname string_to_name(fstring string);
	static bool contains(fstring SearchIn, fstring Substring, bool bUseCase = false, bool bSearchFromEnd = false);
	static fstring int_to_string(int32_t value);
	static fstring buildstring_int(fstring append_to, fstring prefix, int32_t value, fstring suffix);

};

class equippable_skin_data_asset : public uobject
{
public:
	int32_t get_type() {

		fstring name = system::get_object_name(this);

		if (string::contains(name, L"Default__BasePistol", true, false)) {
			return 1;
		}
		else if (string::contains(name, L"Default__SawedOffShotgun", true, false) || string::contains(name, L"Default__Slim", true, false)) {
			return 2;
		}
		else if (string::contains(name, L"Default__AutoPistol", true, false) || string::contains(name, L"Default__AutomaticPistol", true, false)) {
			return 3;
		}
		else if (string::contains(name, L"Default__Luger", true, false)) {
			return 4;
		}
		else if (string::contains(name, L"Default__Revolver", true, false)) {
			return 5;
		}
		else if (string::contains(name, L"Default__Vector", true, false)) {
			return 6;
		}
		else if (string::contains(name, L"Default__MP5", true, false) || string::contains(name, L"Default__SubMachineGun_MP5", true, false)) {
			return 7;
		}
		else if (string::contains(name, L"Default__PumpShotgun", true, false)) {
			return 8;
		}
		else if (string::contains(name, L"Default__AutomaticShotgun", true, false) || string::contains(name, L"Default__AutoShotgun", true, false)) {
			return 9;
		}
		else if (string::contains(name, L"Default__Burst", true, false) || string::contains(name, L"Default__AssaultRifle_Burst", true, false)) {
			return 10;
		}
		else if (string::contains(name, L"Default__DMR", true, false)) {
			return 11;
		}
		else if (string::contains(name, L"Default__AssaultRifle_ACR", true, false) || string::contains(name, L"Default__Carbine", true, false)) {
			return 12;
		}
		else if (string::contains(name, L"Default__AK", true, false) || string::contains(name, L"Default__AssaultRifle_AK", true, false)) {
			return 13;
		}
		else if (string::contains(name, L"Default__LeverSniperRifle", true, false) || string::contains(name, L"Default__LeverSniper", true, false)) {
			return 14;
		}
		else if (string::contains(name, L"Default__BoltSniper", true, false)) {
			return 15;
		}
		else if (string::contains(name, L"Default__LMG", true, false) || string::contains(name, L"Default__LightMachineGun", true, false)) {
			return 16;
		}
		else if (string::contains(name, L"Default__HMG", true, false) || string::contains(name, L"Default__HeavyMachineGun", true, false)) {
			return 17;
		}
		else if (string::contains(name, L"Default__Melee", true, false)) {
			return 18;
		}
		else if (string::contains(name, L"Default__DS_Gun", true, false)) {
			return 19;
		}
		return 0;
	}

	tarray<int> get_skin_levels();
};

class equippable_skin_chroma_inventory_model : public uobject
{
public:
	uobject* get_skin_chroma_data_asset();
};

class equippable_skin_inventory_model : public uobject
{
public:
	equippable_skin_data_asset* get_skin_data_asset();
	equippable_skin_chroma_inventory_model* get_skin_inventory_chroma_asset();
};

class equippable_charm_level_data_asset : public uobject
{
public:
	int get_charm_level();
};

class equippable_charm_instance_inventory_model : public uobject
{
public:
	uobject* get_charm_data_asset();
	equippable_charm_level_data_asset* get_charm_level_data_asset();

};

class equippable_inventory_model : public uobject
{
public:
	equippable_skin_inventory_model* get_equipped_skin_model();
	equippable_charm_instance_inventory_model* get_equipped_charm_instance();
};

struct USceneComponent3 : uobject {
	char pad_D8[0x8]; // 0xd8(0x08)
	uobject* PhysicsVolume; // 0xe0(0x08)
	USceneComponent3* AttachParent; // 0xe8(0x08)
	fname AttachSocketName; // 0xf0(0x0c)
	char pad_FC[0x4]; // 0xfc(0x04)
	USceneComponent3* AttachChildren; // 0x100(0x10)
	USceneComponent3* ClientAttachedChildren; // 0x110(0x10)
	char pad_120[0x50]; // 0x120(0x50)
	fvector RelativeLocation; // 0x170(0x18)
	frotator RelativeRotation; // 0x188(0x18)
	fvector RelativeScale3D; // 0x1a0(0x18)
	fvector ComponentVelocity; // 0x1b8(0x18)
	char bComponentToWorldUpdated : 1; // 0x1d0(0x01)
	char pad_1D0_1 : 1; // 0x1d0(0x01)
	char bAbsoluteLocation : 1; // 0x1d0(0x01)
	char bAbsoluteRotation : 1; // 0x1d0(0x01)
	char bAbsoluteScale : 1; // 0x1d0(0x01)
	char bVisible : 1; // 0x1d0(0x01)
	char pad_1D0_6 : 2; // 0x1d0(0x01)
	char pad_1D1[0x4f]; // 0x1d1(0x4f)
	char bRenderInTargetViewMode : 1; // 0x220(0x01)
	char bShouldBeAttached : 1; // 0x220(0x01)
	char bShouldSnapLocationWhenAttached : 1; // 0x220(0x01)
	char bShouldSnapRotationWhenAttached : 1; // 0x220(0x01)
	char bShouldSnapScaleWhenAttached : 1; // 0x220(0x01)
	char bShouldUpdatePhysicsVolume : 1; // 0x220(0x01)
	char bSkipChildTransformPropagation : 1; // 0x220(0x01)
	char bForceSkipUpdateOverlaps : 1; // 0x220(0x01)
	char bIgnoreTransformUpdatesFromParent : 1; // 0x221(0x01)
	char bHiddenInGame : 1; // 0x221(0x01)
	char bBoundsChangeTriggersStreamingDataRebuild : 1; // 0x221(0x01)
	char bUseAttachParentBound : 1; // 0x221(0x01)
	char bComputeFastLocalBounds : 1; // 0x221(0x01)
	char bComputeBoundsOnceForGame : 1; // 0x221(0x01)
	char bComputedBoundsOnceForGame : 1; // 0x221(0x01)
	char bIsNotRenderAttachmentRoot : 1; // 0x221(0x01)
	char pad_222[0x1]; // 0x222(0x01)
	uobject* Mobility; // 0x223(0x01)
	uobject* DetailMode; // 0x224(0x01)
	uobject* PhysicsVolumeChangedDelegate; // 0x225(0x01)
	char pad_226[0x10a]; // 0x226(0x10a)
};

struct USceneComponent : uobject {
	char pad_D8[0x8]; // 0xd8(0x08)
	uobject* PhysicsVolume; // 0xe0(0x08)
	USceneComponent* AttachParent; // 0xe8(0x08)
	fname AttachSocketName; // 0xf0(0x0c)
	char pad_FC[0x4]; // 0xfc(0x04)
	USceneComponent* AttachChildren; // 0x100(0x10)
	USceneComponent* ClientAttachedChildren; // 0x110(0x10)
	char pad_120[0x50]; // 0x120(0x50)
	fvector RelativeLocation; // 0x170(0x18)
	frotator RelativeRotation; // 0x188(0x18)
	fvector RelativeScale3D; // 0x1a0(0x18)
	fvector ComponentVelocity; // 0x1b8(0x18)
	char bComponentToWorldUpdated : 1; // 0x1d0(0x01)
	char pad_1D0_1 : 1; // 0x1d0(0x01)
	char bAbsoluteLocation : 1; // 0x1d0(0x01)
	char bAbsoluteRotation : 1; // 0x1d0(0x01)
	char bAbsoluteScale : 1; // 0x1d0(0x01)
	char bVisible : 1; // 0x1d0(0x01)
	char pad_1D0_6 : 2; // 0x1d0(0x01)
	char pad_1D1[0x4f]; // 0x1d1(0x4f)
	char bRenderInTargetViewMode : 1; // 0x220(0x01)
	char bShouldBeAttached : 1; // 0x220(0x01)
	char bShouldSnapLocationWhenAttached : 1; // 0x220(0x01)
	char bShouldSnapRotationWhenAttached : 1; // 0x220(0x01)
	char bShouldSnapScaleWhenAttached : 1; // 0x220(0x01)
	char bShouldUpdatePhysicsVolume : 1; // 0x220(0x01)
	char bSkipChildTransformPropagation : 1; // 0x220(0x01)
	char bForceSkipUpdateOverlaps : 1; // 0x220(0x01)
	char bIgnoreTransformUpdatesFromParent : 1; // 0x221(0x01)
	char bHiddenInGame : 1; // 0x221(0x01)
	char bBoundsChangeTriggersStreamingDataRebuild : 1; // 0x221(0x01)
	char bUseAttachParentBound : 1; // 0x221(0x01)
	char bComputeFastLocalBounds : 1; // 0x221(0x01)
	char bComputeBoundsOnceForGame : 1; // 0x221(0x01)
	char bComputedBoundsOnceForGame : 1; // 0x221(0x01)
	char bIsNotRenderAttachmentRoot : 1; // 0x221(0x01)
	char pad_222[0x1]; // 0x222(0x01)
	uobject* Mobility; // 0x223(0x01)
	uobject* DetailMode; // 0x224(0x01)
	uobject* PhysicsVolumeChangedDelegate; // 0x225(0x01)
	char pad_226[0x10a]; // 0x226(0x10a)
	void SetRelativeScale3D(fvector newscale);
	void SetWorldScale3D(fvector newscale);
	tarray<fname> GetAllSocketNames();
	void GetChildrenComponents(bool bIncludeAllDescendants, tarray<USceneComponent*>* Children);
	void SetRelativeRotation(frotator Target, bool bSweep = false, bool bTeleport = true);
	void SetRelativeLocation(
		const fvector& NewLocation,
		bool bSweep = false,
		bool bTeleport = true
	);

	
	fvector GetSocketLocation(fname InSocketName);
};

struct UAresOutlineComponent : USceneComponent {
	uobject* LastLocalPlayerState; // 0x330(0x08)
	uobject* ShooterCharacterOwner; // 0x338(0x08)
	char pad_340[0x10]; // 0x340(0x10)
	EAresOutlineMode AllyOutline; // 0x350(0x01)
	EAresOutlineMode EnemyOutline; // 0x351(0x01)
	EAresOutlineMode NeutralOutline; // 0x352(0x01)
	EAresOutlineMode DeadAllyOutline; // 0x353(0x01)
	EAresOutlineMode DeadEnemyOutline; // 0x354(0x01)
	char pad_355[0x3]; // 0x355(0x03)
	float DeathFadeDuration; // 0x358(0x04)
	bool bAffectChildren; // 0x35c(0x01)
	char pad_35D[0x3]; // 0x35d(0x03)
	// 0x0365 - 0x0368 (alignment)


	void SetOutlineMode(EAresOutlineMode OutlineMode);

}; // Size: 0x368
struct UPrimitiveComponent2 : USceneComponent {
	char pad_330[0x18]; // 0x330(0x18)
	uobject* UmbraCullingMode; // 0x348(0x01)
	uobject* PrepassCullMode; // 0x349(0x01)
	char pad_34A[0x2]; // 0x34a(0x02)
	float MinDrawDistance; // 0x34c(0x04)
	float LDMaxDrawDistance; // 0x350(0x04)
	float CachedMaxDrawDistance; // 0x354(0x04)
	float CachedVertexFogIntensityFromVolumes; // 0x358(0x04)
	uobject* DepthPriorityGroup; // 0x35c(0x01)
	uobject* ViewOwnerDepthPriorityGroup; // 0x35d(0x01)
	uobject* IndirectLightingCacheQuality; // 0x35e(0x01)
	uobject* LightmapType; // 0x35f(0x01)
	uobject* HLODBatchingPolicy; // 0x360(0x01)
	char bEnableAutoLODGeneration : 1; // 0x361(0x01)
	char bIsActorTextureStreamingBuiltData : 1; // 0x361(0x01)
	char bIsValidTextureStreamingBuiltData : 1; // 0x361(0x01)
	char pad_361_3 : 5; // 0x361(0x01)
	char pad_362[0x2]; // 0x362(0x02)
	char bIsFirstPerson : 1; // 0x364(0x01)
	char bIgnoreFOVChanges : 1; // 0x364(0x01)
	char pad_364_2 : 6; // 0x364(0x01)
	char pad_365[0x3]; // 0x365(0x03)
	char bNeverDistanceCull : 1; // 0x368(0x01)
	char pad_368_1 : 7; // 0x368(0x01)
	char pad_369[0x17]; // 0x369(0x17)
	char pad_380_0 : 2; // 0x380(0x01)
	char bAlwaysCreatePhysicsState : 1; // 0x380(0x01)
	char bGenerateOverlapEvents : 1; // 0x380(0x01)
	char bMultiBodyOverlap : 1; // 0x380(0x01)
	char bTraceComplexOnMove : 1; // 0x380(0x01)
	char bReturnMaterialOnMove : 1; // 0x380(0x01)
	char bUseViewOwnerDepthPriorityGroup : 1; // 0x380(0x01)
	char bAllowCullDistanceVolume : 1; // 0x381(0x01)
	char bVisibleInReflectionCaptures : 1; // 0x381(0x01)
	char bVisibleInRealTimeSkyCaptures : 1; // 0x381(0x01)
	char bVisibleInRayTracing : 1; // 0x381(0x01)
	char bRenderInMainPass : 1; // 0x381(0x01)
	char bRenderInDepthPass : 1; // 0x381(0x01)
	char bReceivesDecals : 1; // 0x381(0x01)
	char bReceivesFloorOnlyDecals : 1; // 0x381(0x01)
	char bDisableRGBAWrite : 1; // 0x382(0x01)
	char bHoldout : 1; // 0x382(0x01)
	char bOwnerNoSee : 1; // 0x382(0x01)
	char bOnlyOwnerSee : 1; // 0x382(0x01)
};



struct UActorComponent : uobject {
	char pad_30[0x18]; // 0x30(0x18)
	tarray<struct fname> ComponentTags; // 0x78(0x10)
	struct tarray<struct uobject*> AssetUserData; // 0x88(0x10)
	char pad_98[0x4]; // 0x98(0x04)
	int32_t UCSSerializationIndex; // 0x9c(0x04)
	char pad_A0_0 : 3; // 0xa0(0x01)
	char bNetAddressable : 1; // 0xa0(0x01)
	char bReplicates : 1; // 0xa0(0x01)
	char pad_A0_5 : 3; // 0xa0(0x01)
	char pad_A1[0x7]; // 0xa1(0x07)
	uint64_t TickTimingsAccumulatedTotal; // 0xa8(0x08)
	uint64_t TickTimingsAccumulatedBP; // 0xb0(0x08)
	uint64_t TickTimingsStart; // 0xb8(0x08)
	char pad_C0[0x1]; // 0xc0(0x01)
	char pad_C1_0 : 3; // 0xc1(0x01)
	char bAutoActivate : 1; // 0xc1(0x01)
	char bIsActive : 1; // 0xc1(0x01)
	char bEditableWhenInherited : 1; // 0xc1(0x01)
	char pad_C1_6 : 1; // 0xc1(0x01)
	char bCanEverAffectNavigation : 1; // 0xc1(0x01)
	char pad_C2_0 : 1; // 0xc2(0x01)
	char bIsEditorOnly : 1; // 0xc2(0x01)
	char pad_C2_2 : 6; // 0xc2(0x01)
	char pad_C3[0x1]; // 0xc3(0x01)
	char pad_C7[0x1]; // 0xc7(0x01)
	tarray<struct uobject*> UCSModifiedProperties; // 0xc8(0x10)
	char pad_D8[0x10]; // 0xd8(0x10)
};


struct alignas(0x04) FColor final
{
public:
	uint8_t B;
	uint8_t G;
	uint8_t R;
	uint8_t A;

	FColor() : B(0), G(0), R(0), A(255) {} // default constructor

	FColor(uint8_t InR, uint8_t InG, uint8_t InB, uint8_t InA = 255)
		: R(InR), G(InG), B(InB), A(InA)
	{
	}
};

struct FProcMeshTangent final
{
public:
	fvector                                       TangentX;                                          // 0x0000(0x0018)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bFlipTangentY;                                     // 0x0018(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                       Pad_19[0x7];                                       // 0x0019(0x0007)(Fixing Struct Size After Last Property [ Dumper-7 ])
};


struct UProceduralMeshComponent : uobject {
	char pad_6D0[0x8]; // 0x6d0(0x08)
	bool bUseComplexAsSimpleCollision; // 0x6d8(0x01)
	bool bUseAsyncCooking; // 0x6d9(0x01)
	char pad_6DA[0x6]; // 0x6da(0x06)
	struct uobject* ProcMeshBodySetup; // 0x6e0(0x08)
	struct tarray<struct FKBoxElem> CollisionBoxElems; // 0x6e8(0x10)
	char pad_6F8[0x8]; // 0x6f8(0x08)
	struct tarray<struct FProcMeshSection> ProcMeshSections; // 0x700(0x10)
	struct tarray<struct FKConvexElem> CollisionConvexElems; // 0x710(0x10)
	struct uobject* LocalBounds; // 0x720(0x38)
	struct tarray<struct uobject*> AsyncBodySetupQueue; // 0x758(0x10)
	char pad_768[0x8]; // 0x768(0x08)

	void CreateMeshSection(int32 SectionIndex,
		const tarray<struct fvector>&Vertices,
		const tarray<int32>& Triangles, const tarray<struct fvector>& Normals,
		const tarray<struct fvector2d>& UV0, const tarray<struct FColor>& VertexColors,
		const tarray<struct FProcMeshTangent>& Tangents,
		bool bCreateCollision); // Function: 0x53B4C90
	void SetRelativeScale3D1(fvector newscale);
	void K2_DestroyComponent();
	void SetRelativeRotation1(frotator Target, bool bSweep = false, bool bTeleport = true);
	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
		if (!this || !parent) return nullptr;

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial");

		struct {
			int32_t element_index;
			uobject* parent;
			uobject* return_value;
		} params = { element_index, parent };

		this->process_event(fn, &params);
		return params.return_value;
	}

	void K2_AddRelativeLocation(fvector DeltaLocation, bool bSweep, bool bTeleport);


};

enum class EPhysicsTransformUpdateMode {
	SimulationUpatesComponentTransform = 0,
	ComponentTransformIsKinematic = 1,
	EPhysicsTransformUpdateMode_MAX = 2
};


class uskeletalmeshcomponent : public uobject
{
public:

	struct FHitResult233 {
		int32 FaceIndex; // 0x00(0x04)
		float Time; // 0x04(0x04)
		float Distance; // 0x08(0x04)
		uint8 pad_C[0x4]; // 0x0c(0x04)
		fvector Location; // 0x10(0x18)
		fvector ImpactPoint; // 0x28(0x18)
		fvector Normal; // 0x40(0x18)
		fvector ImpactNormal; // 0x58(0x18)
		fvector TraceStart; // 0x70(0x18)
		fvector TraceEnd; // 0x88(0x18)
		float PenetrationDepth; // 0xa0(0x04)
		int32 MyItem; // 0xa4(0x04)
		int32 Item; // 0xa8(0x04)
		uint8 ElementIndex; // 0xac(0x01)
		uint8 bBlockingHit : 1; // 0xad(0x01)
		uint8 bStartPenetrating : 1; // 0xad(0x01)
		uint8 pad_AD_2 : 6; // 0xad(0x01)
		uint8 pad_AE[0x2]; // 0xae(0x02)
		UPhysicalMaterial* PhysMaterial; // 0xb0(0x08)
		AActor* Actor; // 0xb8(0x18)
		UPrimitiveComponent* Component; // 0xd0(0x08)
		fname BoneName; // 0xd8(0x0c)
		fname MyBoneName; // 0xe4(0x0c)
	};


	char pad_A20[0x8]; // 0xa20(0x08)
	uobject* SkeletalMeshAsset; // 0xa28(0x08)
	uobject* AnimBlueprintGeneratedClass; // 0xa30(0x08)
	uobject* AnimClass; // 0xa38(0x08)
	uobject* AnimScriptInstance; // 0xa40(0x08)
	uobject* PostProcessAnimInstance; // 0xa48(0x08)
	uobject* AnimationData; // 0xa50(0x18)
	char pad_A68[0x10]; // 0xa68(0x10)
	 fvector RootBoneTranslation; // 0xa78(0x18)
	 fvector LineCheckBoundsScale; // 0xa90(0x18)
	char pad_AA8[0x20]; // 0xaa8(0x20)
	 tarray<struct uobject**> LinkedInstances; // 0xac8(0x10)
	char pad_AD8[0x10]; // 0xad8(0x10)
	 tarray<struct uobject*> CachedBoneSpaceTransforms; // 0xae8(0x10)
	 tarray<struct uobject*> CachedComponentSpaceTransforms; // 0xaf8(0x10)
	char pad_B08[0xa0]; // 0xb08(0xa0)
	float GlobalAnimRateScale; // 0xba8(0x04)
	 uobject* KinematicBonesUpdateType; // 0xbac(0x01)
	uobject* PhysicsTransformUpdateMode; // 0xbad(0x01)
	char pad_BAE[0x1]; // 0xbae(0x01)
	uobject* AnimationMode; // 0xbaf(0x01)
	char pad_BB0[0x1]; // 0xbb0(0x01)
	char bDisablePostProcessBlueprint : 1; // 0xbb1(0x01)
	char bOmitFromParticleModuleLocationSkelVertSurface : 1; // 0xbb1(0x01)
	char pad_BB1_2 : 1; // 0xbb1(0x01)
	char bUpdateOverlapsOnAnimationFinalize : 1; // 0xbb1(0x01)
	char pad_BB1_4 : 1; // 0xbb1(0x01)
	char bHasValidBodies : 1; // 0xbb1(0x01)
	char bBlendPhysics : 1; // 0xbb1(0x01)
	char bEnablePhysicsOnDedicatedServer : 1; // 0xbb1(0x01)
	char bUpdateMeshWhenKinematic : 1; // 0xbb2(0x01)
	char bUpdateJointsFromAnimation : 1; // 0xbb2(0x01)
	char bAllowClothActors : 1; // 0xbb2(0x01)
	char bDisableClothSimulation : 1; // 0xbb2(0x01)
	char pad_BB2_4 : 4; // 0xbb2(0x01)
	char pad_BB3[0x5]; // 0xbb3(0x05)
	char bDisableRigidBodyAnimNode : 1; // 0xbb8(0x01)
	char bAllowAnimCurveEvaluation : 1; // 0xbb8(0x01)
	char pad_BB8_2 : 3; // 0xbb8(0x01)
	char bCollideWithEnvironment : 1; // 0xbb8(0x01)
	char bCollideWithAttachedChildren : 1; // 0xbb8(0x01)
	char bForceCollisionUpdate : 1; // 0xbb8(0x01)
	char bLocalSpaceSimulation : 1; // 0xbb9(0x01)
	char bResetAfterTeleport : 1; // 0xbb9(0x01)
	char pad_BB9_2 : 1; // 0xbb9(0x01)
	char bDeferKinematicBoneUpdate : 1; // 0xbb9(0x01)
	char bNoSkeletonUpdate : 1; // 0xbb9(0x01)
	char bPauseAnims : 1; // 0xbb9(0x01)
	char bUseRefPoseOnInitAnim : 1; // 0xbb9(0x01)
	char bEnablePerPolyCollision : 1; // 0xbb9(0x01)
	char bForceRefpose : 1; // 0xbba(0x01)
	char bOnlyAllowAutonomousTickPose : 1; // 0xbba(0x01)
	char bIsAutonomousTickPose : 1; // 0xbba(0x01)
	char bOldForceRefPose : 1; // 0xbba(0x01)
	char bShowPrePhysBones : 1; // 0xbba(0x01)
	char bRequiredBonesUpToDate : 1; // 0xbba(0x01)
	char bAnimTreeInitialised : 1; // 0xbba(0x01)
	char bIncludeComponentLocationIntoBounds : 1; // 0xbba(0x01)
	char bEnableLineCheckWithBounds : 1; // 0xbbb(0x01)
	char bPropagateCurvesToFollowers : 1; // 0xbbb(0x01)
	char bSkipKinematicUpdateWhenInterpolating : 1; // 0xbbb(0x01)
	char bSkipBoundsUpdateWhenInterpolating : 1; // 0xbbb(0x01)
	char bForceEvaluateAnimation : 1; // 0xbbb(0x01)
	char bForceUpdateAnimation : 1; // 0xbbb(0x01)
	char pad_BBB_6 : 1; // 0xbbb(0x01)
	char bReplicated : 1; // 0xbbb(0x01)
	char pad_BBC_0 : 2; // 0xbbc(0x01)
	char bNeedsQueuedAnimEventsDispatched : 1; // 0xbbc(0x01)
	char pad_BBC_3 : 5; // 0xbbc(0x01)
	char pad_BBD[0x1]; // 0xbbd(0x01)
	uint16_t CachedAnimCurveUidVersion; // 0xbbe(0x02)
	float ClothBlendWeight; // 0xbc0(0x04)
	bool bWaitForParallelClothTask; // 0xbc4(0x01)
	bool bFilteredAnimCurvesIsAllowList; // 0xbc5(0x01)
	uint16_t CachedMeshCurveMetaDataVersion; // 0xbc6(0x02)
	tarray<struct fname> FilteredAnimCurves; // 0xbc8(0x10)
	uobject* BodySetup; // 0xbd8(0x08)
	char pad_BE0[0x4]; // 0xbe0(0x04)
	float ClothMaxDistanceScale; // 0xbe4(0x04)
	uobject* OnConstraintBroken; // 0xbe8(0x10)
	uobject* OnPlasticDeformation; // 0xbf8(0x10)
	uobject* ClothingSimulationFactory; // 0xc08(0x08)
	char pad_C10[0xf8]; // 0xc10(0xf8)
	float TeleportDistanceThreshold; // 0xd08(0x04)
	float TeleportRotationThreshold; // 0xd0c(0x04)
	char pad_D10[0x8]; // 0xd10(0x08)
	uint32_t LastPoseTickFrame; // 0xd18(0x04)
	char pad_D1C[0x94]; // 0xd1c(0x94)
	uobject* ClothingInteractor; // 0xdb0(0x08)
	char pad_DB8[0xd8]; // 0xdb8(0xd8)
	uobject* OnAnimInitialized; // 0xe90(0x10)
	char pad_EA0[0x250]; // 0xea0(0x250)


	UMaterialInterface* GetMaterial(int32_t ElementIndex);
	void SetMaterial(int32_t ElementIndex, uobject* Material);
	std::int32_t GetNumBones();
	void SetSkinnedAssetAndUpdate(uobject* NewMesh, bool bReinitPose);
	bool AttachTo(uskeletalmeshcomponent* Parent, fname SocketName, int LocationRule, int RotationRule, int ScaleRule, bool bWeldSimulatedBodies);
	void SetRelativeScale3D(fvector newscale);
	
	void SetWorldScale3D(fvector newscale);
	fvector GetSocketLocation(fname InSocketName);
	tarray<fname> GetAllSocketNames();
	fvector K2_GetComponentLocation();
	fvector K2_GetComponentScale();
	frotator K2_GetComponentRotation();
	void set_world_rotation(fvector NewRotation, bool bsweep, bool bteleport);
	void set_relative_rotation(FRotator NewRotation);
	void set_relative_rotation1(frotator NewRotation, bool bSweep = false, bool bTeleport = true);
	void SetRelativeRotation(frotator Target, bool bSweep = false, bool bTeleport = true);
	void SetRelativeLocation(
		const fvector& NewLocation,
		bool bSweep = false,
		bool bTeleport = true
	);
	void K2_SetWorldLocationAndRotation(fvector newlocation, frotator NewRelativeRotation, bool bSweep, bool bTeleport)
	{
		
		static uobject* Function;
		if (!Function)
			Function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetWorldLocationAndRotation").decrypt());

		struct
		{
			fvector newlocation;
			frotator NewRelativeRotation;
			bool bSweep;
			FHitResult233 SweepHitResult;
			bool bTeleport;
		}Parameters;
		Parameters.newlocation = newlocation;
		Parameters.NewRelativeRotation = NewRelativeRotation;
		Parameters.bSweep = bSweep;
		Parameters.bTeleport = bTeleport;
		memset(&Parameters.SweepHitResult, 0, sizeof(FHitResult233));


		this->process_event(Function, &Parameters);
	}


	void K2_AddRelativeLocation(fvector Target, bool bSweep = false, bool bTeleport = true);
	void SetOutlineMode(EAresOutlineMode Mode);
	fvector get_bone_location(int32_t index);
	FVector get_bone_location35(int32_t index);

	int32_t GetBoneIndex(fname BoneName); 
	fname GetBoneName(int32_t BoneName);
	int32_t get_num_materials();

    void K2_AddLocalOffset(const fvector& Location, bool bSweep = false, bool bTeleport = true);

	void SetOnlyOwnerSee(bool bNewOnlyOwnerSee) {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetOnlyOwnerSee");

		struct {
			bool bValue;
		} params = { bNewOnlyOwnerSee };

		this->process_event(function, &params);
	}

	void SetRenderInTargetViewMode(bool bValue) {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.SceneComponent.SetRenderInTargetViewMode");

		struct {
			bool bValue;
		} params = { bValue };

		this->process_event(function, &params);
	}

	
	
	void SetRenderCustomDepth(bool bValue) {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetRenderCustomDepth");

		struct {
			bool bValue;
		} params = { bValue };

		this->process_event(function, &params);
		
	}
	void SetAbsolute(bool bNewAbsoluteLocation, bool bNewAbsoluteRotation, bool bNewAbsoluteScale) {

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.SetAbsolute");

		struct {
			bool bNewAbsoluteLocation;
			bool bNewAbsoluteRotation;
			bool bNewAbsoluteScale;	
		} params = { bNewAbsoluteLocation, bNewAbsoluteRotation, bNewAbsoluteScale };

		this->process_event(fn, &params);
		
	}
	uobject* GetAttachParent() {
		if (!this) return nullptr;

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.GetAttachParent");

		struct {

			uobject* return_value;
		} params;

		this->process_event(fn, &params);
		return params.return_value;
	}
	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
		if (!this || !parent) return nullptr;

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial");

		struct {
			int32_t element_index;
			uobject* parent;
			uobject* return_value;
		} params = { element_index, parent };

		this->process_event(fn, &params);
		return params.return_value;
	}


	void set_outline_mode(EAresOutlineMode mode);


};

struct UEquippableSkinDataAsset
{

};

class stability_component : public uobject {
public:
};

enum class ECanFireCooldownCheckOption : uint8_t
{
	CheckCooldown = 0,
	SkipCooldownCheck = 1,
	ECanFireCooldownCheckOption_MAX = 2,
};
struct firing_state : public uobject {
public:
	float cooldown() {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FiringStateComponent.GetCooldownTimeRemaining").decrypt());

		if (!function || this == nullptr) {
			return false;
		}

		struct
		{
			float ret;
		} params;


		this->process_event(function, &params);
		return params.ret;
	}

	bool CanFire(ECanFireCooldownCheckOption zainexdad) {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FiringStateComponent.CanFire").decrypt());

		
		struct
		{
			ECanFireCooldownCheckOption zainexdad;
			bool ret;
		} params;
		params.zainexdad = zainexdad;


		this->process_event(function, &params);
		return params.ret;
	}

	uint64_t GetStabilityComponent() {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FiringStateComponent.GetStabilityComponent").decrypt());


		struct
		{
			uint64_t zainexdad;
		} params;



		this->process_event(function, &params);
		return params.zainexdad;
	}
};

class currentequippable : public uobject
{
public:
	struct type {
		const wchar_t* search = nullptr;
		const char* config = nullptr;
		std::int32_t index = 0;

		const bool is_valid() const noexcept {
			return this->search != nullptr || this->config != nullptr;
		}
	};

	ftransform GetMuzzleTransform();
	bool HasMuzzle();

	uskeletalmeshcomponent* GetEquippableMesh();
	firing_state* get_firing_state()
	{
		return memory::read<firing_state*>(uintptr_t(this) + offsets::firing_state_component);
	}

	uskeletalmeshcomponent* GetMesh1P();
	uskeletalmeshcomponent* GetMesh3P();
	UEquippableSkinDataAsset* GetEquippableSkinDataAsset();
	static inline currentequippable::type types[] = {
			{ L"basepistol", "classic" },
			{ L"sawedoffshotgun", "shorty" },
			{ L"automaticpistol", "frenzy" },
			{ L"lugerpistol", "ghost" },

			{ L"revolverpistol", "sheriff" },

			{ L"vector", "stinger" },
			{ L"submachinegun_mp5", "spectre" },

			{ L"pumpshotgun", "bucky" },
			{ L"automaticshotgun", "judge" },

			{ L"assaultrifle_burst", "bulldog" },
			{ L"dmr", "guardian" },
			{ L"assaultrifle_acr", "phantom" },
			{ L"assaultrifle_ak", "vandal" },

			{ L"leversniperrifle", "marshal" },
			{ L"boltsniper", "operator" },

			{ L"lightmachinegun", "ares" },
			{ L"heavymachinegun", "odin" },

			{ L"ability_melee_base", "knife" },

			{ L"gun_sprinter_x_heavylightninggun_production", "neon_x" },
			{ L"ability_wushu_x_dagger_production", "jett_dagger" }
	};

	currentequippable::type get_type() {

		const fstring& name = system::get_object_name(this);

		for (std::int32_t index = 0; index < sizeof(currentequippable::types) / sizeof(currentequippable::type); index++) {
			currentequippable::type type = currentequippable::types[index];

			if (type.index == 0)
				type.index = index;

			if (system::starts_with(name.c_str(), type.search))
				return { type.search, type.config, type.index };
		}

		return {};
	}




	equippable_skin_data_asset* get_skin_data_asset();
};
class uinventory : public uobject
{
public:
	currentequippable* get_current_equippable();
	currentequippable* get_current_equippable_();
};

class arsenal_view_model : public uobject
{
public:
	tarray<equippable_inventory_model*> get_gun_models();
};

class arsenal_view_controller : public uobject
{
public:
	arsenal_view_model* get_view_model();
};



class UMaterial : public uobject
{
public:

};



class ThreadMessage : public uobject
{
public:
	static void SendMessageAfterKill(EChatRoomType nigger, ftext Message);
};




class inventorymanager : public uobject
{
public:
	currentequippable* get_current_weapon();
};

struct UThreadedChatManager : public uobject {
	uobject* ChatService; // 0xe0(0x08)
	uobject* Messages; // 0xe8(0x10)
	uobject* PartyRoom; // 0x148(0x08)
	uobject* PregameRoom; // 0x150(0x08)
	uobject* AllRoom; // 0x158(0x08)
	uobject* TeamRoom; // 0x160(0x08)
	struct UPartyManager* PartyManager; // 0x168(0x08)
	struct UCoreGameManager* CoreGameManager; // 0x170(0x08)
	struct UPregameManager* PregameManager; // 0x178(0x08)
	struct UWhisperChatManager* WhisperChatManager; // 0x180(0x08)
	struct UMutedPatternsManager* MutedPatternsManager; // 0x188(0x08)
	struct UTextChatManagerV2* TextChatManager; // 0x190(0x08)
	struct UEmojiMapping* EmojiMapping; // 0x198(0x08)
	struct URSOManager* RSOManager; // 0x1a0(0x08)
	char pad_1A8[0x8];
public:

	void SendChatMessageV2(EChatRoomType RoomType, const ftext& Message)
	{
		

		static uobject* function = nullptr;
		if (!function)

			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ThreadedChatManager.SendChatMessageV2").decrypt());

		struct
		{
			EChatRoomType RoomType;
			ftext Message;
		} params = { RoomType , Message };

		this->process_event(function, &params);

	}

	static UThreadedChatManager* GetThreadedChatManager(uobject* world_context);
	void send_chat_message_v2(EChatRoomType room_type, ftext message);

	static uobject* GetDefaultObj() {
		static uobject* default_obj = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ThreadedChatManager").decrypt());
		return default_obj;
	}
	// 0x1a8(0x08)
};

struct AresClientGameInstance_GetThreadedChatManager
{
	class UThreadedChatManager* ReturnValue; // 0x0000(0x0008)
};

class ares_client_game_instace : public uobject
{
public:
	arsenal_view_controller* get_aresnal_view_controller();
	inventorymanager* get_inventory_manager();

	UThreadedChatManager* GetThreadedChatManager();

};

class ares_instance : public uobject
{
public:
	static ares_client_game_instace* get_ares_client_game_instance(uobject* world_context);
};

void SetAspectRatio(float InAspectRatio)
{
	static uobject* function = 0;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CameraComponent.SetAspectRatio").decrypt());

	struct
	{
		float InAspectRatio;
	} params;

	params.InAspectRatio = InAspectRatio;

	function->process_event(function, &params);
}
struct FPostProcessSettings
{
	// SceneColorTint
	bool bOverride_SceneColorTint = false;
	flinearcolor SceneColorTint = flinearcolor(1.0f, 1.0f, 1.0f, 1.0f);

	// Auto Exposure
	bool bOverride_AutoExposureMinBrightness = false;
	float AutoExposureMinBrightness = 1.0f;

	bool bOverride_AutoExposureMaxBrightness = false;
	float AutoExposureMaxBrightness = 1.0f;

	// Film
	bool bOverride_FilmContrast = false;
	float FilmContrast = 1.0f;

	bool bOverride_FilmSaturation = false;
	float FilmSaturation = 1.0f;

	// Bloom
	bool bOverride_BloomIntensity = false;
	float BloomIntensity = 1.0f;

	// Grain
	bool bOverride_GrainIntensity = false;
	float GrainIntensity = 0.0f;

	// Vignette
	bool bOverride_VignetteIntensity = false;
	float VignetteIntensity = 0.4f;

	// Chromatic Aberration (Fringe)
	bool bOverride_SceneFringeIntensity = false;
	float SceneFringeIntensity = 0.0f;

	// Ambient Occlusion
	bool bOverride_AmbientOcclusionIntensity = false;
	float AmbientOcclusionIntensity = 1.0f;

	bool bOverride_AmbientOcclusionDistance = false;
	float AmbientOcclusionDistance = 150.0f;

	bool bOverride_AmbientOcclusionFadeDistance = false;
	float AmbientOcclusionFadeDistance = 500.0f;

	// Padding to roughly align with Unreal's original size (if needed)
	uint8 Padding[1440]; // adjust based on actual struct size (~1552 total)
};


struct FMinimalViewInfo
{
public:
	fvector                                       Location;                                          // 0x0000(0x0018)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector                                       Rotation;                                          // 0x0018(0x0018)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	float                                         FOV;                                               // 0x0030(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DesiredFOV;                                        // 0x0034(0x0004)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         OrthoWidth;                                        // 0x0038(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         OrthoNearClipPlane;                                // 0x003C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         OrthoFarClipPlane;                                 // 0x0040(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         PerspectiveNearClipPlane;                          // 0x0044(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AspectRatio;                                       // 0x0048(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_4C[0x8];                                       // 0x004C(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	uint8                                         bConstrainAspectRatio : 1;                         // 0x0054(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         bUseFieldOfViewForLOD : 1;                         // 0x0054(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8                                         Pad_55[0x3];                                       // 0x0055(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uobject* ProjectionMode;                                    // 0x0058(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_59[0x3];                                       // 0x0059(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         PostProcessBlendWeight;                            // 0x005C(0x0004)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	FPostProcessSettings                          PostProcessSettings;                               // 0x0060(0x0800)(BlueprintVisible, NativeAccessSpecifierPublic)
	fvector2d                                     OffCenterProjectionOffset;                         // 0x0860(0x0010)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, Transient, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8                                         Pad_870[0x70];                                     // 0x0870(0x0070)(Fixing Struct Size After Last Property [ Dumper-7 ])
};
// ScriptStruct Engine.CameraCacheEntry
// Size: 0x8f0 (Inherited: 0x00)
struct FCameraCacheEntry {
	float Timestamp; // 0x00(0x04)
	char pad_4[0xc]; // 0x04(0x0c)
	FMinimalViewInfo Egg; // 0x10(0x8e0)
};


class aplayercameramanager : public uobject
{
public:

	uobject* PCOwner; // 0x460(0x08)
	USceneComponent* TransformComponent; // 0x468(0x08)
	char pad_470[0xc]; // 0x470(0x0c)
	float DefaultFOV; // 0x47c(0x04)
	char pad_480[0x90]; // 0x480(0x90)
	float DefaultOrthoWidth; // 0x510(0x04)
	char pad_514[0x4]; // 0x514(0x04)
	float DefaultAspectRatio; // 0x518(0x04)
	char pad_51C[0x64]; // 0x51c(0x64)
	uobject* ViewTarget; // 0x580(0x900)
	uobject* PendingViewTarget; // 0xe80(0x900)
	char pad_1780[0x30]; // 0x1780(0x30)
	FCameraCacheEntry CameraCachePrivate; // 0x17b0(0x8f0)
    FCameraCacheEntry LastFrameCameraCachePrivate; // 0x20a0(0x8f0)
	struct tarray<struct uobject**> ModifierList; // 0x2990(0x10)
	struct tarray<struct uobject**> DefaultModifiers; // 0x29a0(0x10)
	float FreeCamDistance; // 0x29b0(0x04)
	char pad_29B4[0x4]; // 0x29b4(0x04)
	 fvector FreeCamOffset; // 0x29b8(0x18)
	 FVector FreeCamAdditiveRotation; // 0x29d0(0x18)
	 fvector ViewTargetOffset; // 0x29e8(0x18)
	 uobject* OnAudioFadeChangeEvent; // 0x2a00(0x10)
	char pad_2A10[0x18]; // 0x2a10(0x18)
	uobject* CameraLensEffects; // 0x2a28(0x10)
	uobject* CachedCameraShakeMod; // 0x2a38(0x08)
	uobject* PostProcessBlendCache; // 0x2a40(0x10)
	char pad_2A50[0x20]; // 0x2a50(0x20)
	uobject* AnimCameraActor; // 0x2a70(0x08)
	char bIsOrthographic : 1; // 0x2a78(0x01)
	char bDefaultConstrainAspectRatio : 1; // 0x2a78(0x01)
	char pad_2A78_2 : 4; // 0x2a78(0x01)
	char bClientSimulatingViewTarget : 1; // 0x2a78(0x01)
	char bUseClientSideCameraUpdates : 1; // 0x2a78(0x01)
	char pad_2A79_0 : 2; // 0x2a79(0x01)
	char bGameCameraCutThisFrame : 1; // 0x2a79(0x01)
	char pad_2A79_3 : 5; // 0x2a79(0x01)
	char pad_2A7A[0x2]; // 0x2a7a(0x02)
	float ViewPitchMin; // 0x2a7c(0x04)
	float ViewPitchMax; // 0x2a80(0x04)
	float ViewYawMin; // 0x2a84(0x04)
	float ViewYawMax; // 0x2a88(0x04)
	float ViewRollMin; // 0x2a8c(0x04)
	float ViewRollMax; // 0x2a90(0x04)
	char pad_2A94[0x4]; // 0x2a94(0x04)
	float ServerUpdateCameraTimeout; // 0x2a98(0x04)
	char pad_2A9C[0x14]; // 0x2a9c(0x14)

	fvector get_camera_location();
	fvector get_camera_rotation();

	frotator get_camera_rotation3();
	FVector get_camera_location2();
	FVector get_camera_rotation2();
	float GetFOVAngle1P();

};

class aplayerstate : public uobject
{
public:
};



enum class EAresItemSlot : unsigned char
{
	Primary = 0,
	Secondary = 1,
	Melee = 2,
	GrenadeAbility = 3,
	Ability1 = 4,
	Ability2 = 5,
	Passive = 6,
	Level = 7,
	Invisible = 8,
	Ultimate = 9,
	Unarmed = 10,
	Armor = 11,
	Backpack = 12,
	Totem = 13,
	PrimaryStorage = 14,
	SecondaryStorage = 15,
	Count = 16,
	Any = 253,
	Invalid = 254,
	EAresItemSlot_MAX = 255,
};

class acknowledgedpawn : public uobject
{
public:

	EAresItemSlot GetItemSlot();
	fvector k2_get_pawn_location();
	fvector GetControlRotation();
	fvector get_control_rotation_meow();
	void set_relative_rotation(frotator NewRotation);

	uskeletalmeshcomponent* GetCoreMesh3P1();
	uskeletalmeshcomponent* GetCoremesh1pOverlay();

	bool canjump();
};



class UDamageResponse : public uobject {

public:
	struct acknowledgedpawn* GetDamageCauser() {

		uobject* function = (uobject*)uobject::find_object<uobject*>(crypt(L"ShooterGame.DamageResponse.GetEventInstigatorPawn").decrypt());
		struct
		{
			acknowledgedpawn* output;
		} params;

		this->process_event(function, &params);
		return params.output;
	}
	struct acknowledgedpawn* GetEquippableUsed() {
		uobject* function = (uobject*)uobject::find_object<uobject*>(crypt(L"ShooterGame.DamageResponse.GetEquippableUsed").decrypt());


		struct
		{
			acknowledgedpawn* output;
		} params;



		this->process_event(function, &params);


		return params.output;
	}

};


class gameobject : public uobject
{
public:
};

class PlatformPlayer : public uobject
{
public:
	int32_t GetCompetitiveTier();

};
class player_state : public uobject
{
public:
	fstring get_player_name();
	PlatformPlayer* getplayerformplayer();


	tarray<player_state*> get_players_spectating();
	bool IsSpectator() {

		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerState.IsSpectator").decrypt());

		struct
		{
			bool output;
		} params;

		this->process_event(function, &params);

		return params.output;
	}
};



class character_minimap_component : public uobject {
public:
	void set_observer_status(bool status) {
		if (memory::read<bool>(std::uintptr_t(this) + offsets::minimap_component::observer_status) != status)
			memory::write<bool>(std::uintptr_t(this) + offsets::minimap_component::observer_status, status);
	}

	void set_visible_status(bool status) {
		if (memory::read<bool>(std::uintptr_t(this) + offsets::minimap_component::visible_status) != status)
			memory::write<bool>(std::uintptr_t(this) + offsets::minimap_component::visible_status, status);
	}
};

class aplayercontroller12 : public uobject
{
public:

	bool project_world_location_to_screen12(fvector world_location, fvector2d& screen_location, bool player_viewport_relative);
};

class ashootercharacter : public uobject
{
public:

	void GetActorBounds(bool bOnlyCollidingComponents, fvector* Origin, fvector* BoxExtent, bool bIncludeFromChildActors);
	fvector get_velocity();

	void GetActorEyesViewPoint(fvector* OutLocation, frotator* OutRotation);
	fvector GetActorForwardVector();
	FVector GetActorForwardVector2();
	fvector GetActorUpVector();


	bool GetTrueDisplayName();
	void ResetCharacterMaterials_Internal(uskeletalmeshcomponent* MeshToReset);
	void ClientFly();
	bool CanJump();

	void K2_SetActorRelativeRotationnigger(FRotator NewRelativeRotation, bool bSweep, bool bTeleport);
	frotator K2_GetActorRotation();
	FRotator  K2_SetActorRotation(FRotator negrito, bool bTeleportPhysics);
	void get_firing_location_and_direction(fvector* loc, fvector* Rot, bool bApplyRecoil = false);
	void get_firing_location_and_direction2(fvector* loc, frotator* Rot, bool bApplyRecoil);
	uskeletalmeshcomponent* get_mesh();
	uinventory* get_inventory_();
	uskeletalmeshcomponent* GetOverlayMesh1P();
	UPrimitiveComponent* GetOverlayMesh1P2();
	UPrimitiveComponent* GetMesh1P2();
	uskeletalmeshcomponent* GetOverlayMesh3P();
	uinventory* get_inventory();
	fvector k2_get_actor_location();
	uskeletalmeshcomponent* GetMesh1P();
	void SetCrouchTimeOverride(float Override);
	void Set3pMeshVisible(bool value);
	int32_t GetLocalRole();
	void relative_rotation(fvector NewRelativeRotation, bool bSweep, bool bTeleport);

	frotator get_view_rotation_with_full_recoil();

	character_minimap_component* get_portrait_minimap_component() {
		return memory::read<character_minimap_component*>(std::uintptr_t(this) + offsets::radar::portrait_minimap);
	}

	character_minimap_component* get_character_minimap_component() {
		return memory::read<character_minimap_component*>(std::uintptr_t(this) + offsets::radar::character_minimap);
	}
	uobject* get_character_icon();
	bool is3pEnabled();
	bool IsPlayerCharacter();

	bool is_alive();
	bool was_invisible();
	float health();
	float shield();
	bool is_dead_and_settled();
	uskeletalmeshcomponent* GetCosmesticMesh3P();
	uskeletalmeshcomponent* GetCoreMesh3P();
	player_state* get_player_state();
	fvector GetActorRightVector();

	USceneComponent* K2_GetRootComponent();
	bool IsZoomed();

	class aplayercontroller;
	void DisableInput(aplayercontroller12* PlayerController);

	void EnableInput(aplayercontroller12* PlayerController);
};



namespace IhateNigger
{
	uobject* Static_Class();
	bool IsAlly(ashootercharacter* Enemy, ashootercharacter* Self);
}





enum class EChatMode
{
	None = 0,
	Team = 1,
	All = 2,
	Ping = 3,
	Count = 4,
	EChatMode_MAX = 5,
};

class pregame_view_model : public uobject {
public:
	bool is_local_player_locked_in();
};
class pregame_view_controller : public uobject {
public:
	pregame_view_model* get_pregame_view_model();

	void lock_character(uobject* agent);

	void select_character(uobject* agent);
};

typedef          int    int32;

class ucameracomponent : public USceneComponent {
public:

	bool bOverrideFov; // 0x330(0x01)
	bool bOverrideCameraRenderSettings; // 0x331(0x01)
	char pad_332[0x2]; // 0x332(0x02)
	float fieldOfView; // 0x334(0x04)
	float OrthoWidth; // 0x338(0x04)
	float OrthoNearClipPlane; // 0x33c(0x04)
	float OrthoFarClipPlane; // 0x340(0x04)
	float AspectRatio; // 0x344(0x04)
	uobject* AspectRatioAxisConstraint; // 0x348(0x01)
	char bConstrainAspectRatio : 1; // 0x349(0x01)
	char bOverrideAspectRatioAxisConstraint : 1; // 0x349(0x01)
	char bUseFieldOfViewForLOD : 1; // 0x349(0x01)
	char bLockToHmd : 1; // 0x349(0x01)
	char bUsePawnControlRotation : 1; // 0x349(0x01)
	char pad_349_5 : 3; // 0x349(0x01)
	uobject* ProjectionMode; // 0x34a(0x01)
	char pad_34B[0x65]; // 0x34b(0x65)
	float PostProcessBlendWeight; // 0x3b0(0x04)
	char pad_3B4[0x2c]; // 0x3b4(0x2c)
	uobject* PostProcessSettings; // 0x3e0(0x800)

	void SetFieldOfView(float InFieldOfView);


};


class aplayercontroller : public uobject
{
public:

	aplayercontroller* ClientForceSetControlRotation(fvector NewRotation);
	bool is_input_key_down(fkey key);
	void ServerSay(fstring Msg, int32 ChatMode);
	void HandleThreadedChatManagerSentInGameMessage(fstring Msg, EChatMode ChatMode);
	bool get_mouse_position(float* locationx, float* locationy);
	void AddYawInput(float Val);
	void AddPitchInput(float Val);

	void GetInputMouseDelta(float& DeltaX, float& DeltaY);
	void UnlockFOV();
	float GetMouseSensitivity();
	ashootercharacter* K2_GetPawn_Local();
	void simulate_input_key(fkey key, bool bpressed);

	bool dormant_server(ashootercharacter* actor);
	ashootercharacter* get_shooter_character();
	void set_fov(float fov);
	bool line_of_sight(ashootercharacter* other);

	bool line_of_sight2(ashootercharacter* enemy, fvector target_location, aplayercameramanager* camera);

	fvector2d project_world_to_screen(fvector world);
	fvector get_control_rotation();
	frotator get_control_rotation2();

	bool project_world_location_to_screen(fvector world_location, fvector2d& screen_location, bool player_viewport_relative);

	bool project_world_location_to_screen2(FVector world_location, FVector2D& screen_location, bool player_viewport_relative);

	void set_control_rotation(fvector angle);
	void set_control_rotationfrotator(frotator angle);
	aplayercameramanager* get_camera_manager();

	ashootercharacter* GetFirstPersonCharacter();

	acknowledgedpawn* get_acknowledged_pawn();
	void disconnect_server();
	void SetClientRotation(frotator Rotation);
	void GetPlayerViewPoint(fvector Location, frotator Rotation);

	pregame_view_controller* get_pregame_view_controller() {
		return memory::read<pregame_view_controller*>(std::uintptr_t(this) + 0xD40);
	}

};



std::wstring BuddyNameYAY;
fstring BuddyName;
uobject* buddy;
namespace skin_changer {
	void unlock_all_skins(uobject* world);
	void unlock_all_apply(uobject* world,
		currentequippable* current_equippable,
		uobject* skin_data_asset,
		uobject* skin_chroma_asset,
		int max_level,
		uobject* skin_charm_data_asset,
		int skin_charm_level_data_asset);
}




namespace AresOutlineRendering {
	uobject* Static_Class();
	void SetOutlineColorsForRender(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor);
}




class ucanvas : public uobject {
public:
#define M_PI 3.14159265358979323846

	fvector2d get_screen_size();
	fvector2d get_screen_size2();
	void k2_drawline(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color);
	void k2_drawtransparentline(const fvector2d& screen_position_a, const fvector2d& screen_position_b, float thickness, const flinearcolor& render_color);

	void k2_drawline3(FVector2D screenpos_a, FVector2D screenpos_b, float thickness, flinearcolor color);
	void k2_drawline2(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color);
	void k2_drawtexture(uobject* texture, fvector2d screen_position, fvector2d screen_size, fvector2d coordinate_position, fvector2d coordinate_size, flinearcolor render_color, e_blend_mode blend_mode, float rotation, fvector2d pivot_point);
	void k2_drawtext(uobject* font, fstring text, fvector2d screenposition, fvector2d scale, flinearcolor color, float kerning, flinearcolor shadowcolor, fvector2d shadowoffset, bool centrex, bool centrey, bool outline, flinearcolor outlinecolor);
	fvector k2_project(fvector WorldLocation);

	void draw_circle(int x, int y, int radius, int numsides, flinearcolor color) {
		float step = M_PI * 2.0 / numsides;
		int count = 0;

		fvector2d v[128];

		for (float a = 0; a < M_PI * 2.0; a += step) {
			float x1 = radius * cosf(a) + x;
			float y1 = radius * sinf(a) + y;
			float x2 = radius * cosf(a + step) + x;
			float y2 = radius * sinf(a + step) + y;

			v[count].x = x1;
			v[count].y = y1;
			v[count + 1].x = x2;
			v[count + 1].y = y2;

			this->k2_drawline(fvector2d({ v[count].x, v[count].y }), fvector2d({ x2, y2 }), 1.0f, color);
		}
	}



};


class text : public uobject
{
public:
	static fstring text_to_string(ftext string);
    static ftext string_to_text(const fstring& InString);
	
};
typedef unsigned char   uint82;





class blueprints : public uobject
{
public:

	static uobject* GetDefaultObj() {
		static uobject* default_obj = uobject::find_object<uobject*>(L"ShooterGame.Default__ShooterBlueprintLibrary");
		return default_obj;
	}

	static aplayercontroller* get_player_controller(uobject* context);
	static aplayercontroller* get_local_controller(uobject* context);
	static tarray<ashootercharacter*> find_all_shooters_with_alliance(uobject* context, ashootercharacter* viewer, earesalliance alliance, bool only_player, bool only_alive);
	static void GetWallPenetrationSpans(uobject* nigga, fvector StartLocation, fvector EndLocation, tarray<AActor*> IgnoreActors, ECollisionChannel Channel, float MinimumPlayableSpan, FWallSpanList& Spans);

	

	static double GetTimeSeconds(uobject* WorldContextObject);
	static inline bool ares_line_trace_single_by_channel(
		uobject* world_context,
		const fvector& start,
		const fvector& end,
		const tarray<uobject*>& actors_to_ignore,
		FHitResult* out_hit,
		ECollisionChannel trace_channel,
		bool trace_complex,
		bool include_moving_objects
	);



	static void GetWallPenetrationSpans2(UWorld2* WorldContextObject, FVector StartLocation, FVector EndLocation, TArray<AActor*>& IgnoreActors, ECollisionChannel Channel, float MinimumPlayableSpan, FWallSpanList& Spans);


	/*bool IsOtherActorVisible(AActor* viewer,ashootercharacter* Target, ETraceTypeQuery TraceChannel, tarray<AActor*> IgnoreActors, bool TraceBothDirections, uobject world, bool HasVisibility, fvector FocusPoint)
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Ares_Characters_FunctionLibrary.Ares_Characters_FunctionLibrary_C.HasLineOfSightToCharacter"));

		struct {
			AActor* viewer;
			ashootercharacter* Target;
			ETraceTypeQuery TraceChannel;
			tarray<AActor*> IgnoreActors;
			bool TraceBothDirections;
			uobject world;
			bool HasVisibility;
			fvector FocusPoint;
		} params;

		params.viewer = viewer;
		params.Target = Target;
		params.TraceChannel = TraceChannel;
		params.IgnoreActors = IgnoreActors;
		params.TraceBothDirections = TraceBothDirections;
		params.world = world;

		

		variables.flxxdzjosh->process_event(function, &params);

		Spans = params.Spans;
	}*/
};


namespace kismentsystemlibrary
{
	UObject* static_class()
	{

		auto class_name = crypt(L"Engine.Default__KismetSystemLibrary").decrypt();
		return UObject::StaticFindObject(nullptr, nullptr, class_name, false);
	}


	static bool line_trace_single(
		uworld* world_context_object,
		fvector start,
		fvector end,
		ETraceTypeQuery trace_channel,
		bool b_trace_complex,
		tarray<AActor*> actors_to_ignore,
		EDrawDebugTrace draw_debug_type,
		FHitResult& out_hit,
		bool b_ignore_self,
		flinearcolor trace_color,
		flinearcolor trace_hit_color,
		float draw_time)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.KismetSystemLibrary.LineTraceSingle");
		if (!function) return false;

		struct {
			uworld* world_context_object;
			fvector start;
			fvector end;
			ETraceTypeQuery trace_channel;
			bool b_trace_complex;
			tarray<AActor*> actors_to_ignore;
			char draw_debug_type;
			FHitResult out_hit;
			bool b_ignore_self;
			flinearcolor trace_color;
			flinearcolor trace_hit_color;
			float draw_time;
			bool return_value;
		} params;

		params.world_context_object = world_context_object;
		params.start = start;
		params.end = end;
		params.trace_channel = trace_channel;
		params.b_trace_complex = b_trace_complex;
		params.actors_to_ignore = actors_to_ignore;
		params.draw_debug_type = draw_debug_type;
		params.b_ignore_self = b_ignore_self;
		params.trace_color = trace_color;
		params.trace_hit_color = trace_hit_color;
		params.draw_time = draw_time;

		world_context_object->process_event(function, &params);
		out_hit = params.out_hit;

		return params.return_value;

	}
	static inline void DrawDebugSphere(
		UObject* WorldContextObject,
		FVector Center,
		float Radius,
		int32_t Segments,
		flinearcolor LineColor,
		float Duration,
		float Thickness
	) {
		auto function_name = crypt(L"Engine.KismetSystemLibrary.DrawDebugSphere").decrypt();
		static UObject* Function = nullptr;
		if (!Function)
			Function = UObject::StaticFindObject(nullptr, nullptr, function_name, false);

		struct Params {
			UObject* WorldContextObject;
			FVector Center;
			float Radius;
			int32_t Segments;
			flinearcolor LineColor;
			float Duration;
			float Thickness;
		} Args;

		Args.WorldContextObject = WorldContextObject;
		Args.Center = Center;
		Args.Radius = Radius;
		Args.Segments = Segments;
		Args.LineColor = LineColor;
		Args.Duration = Duration;
		Args.Thickness = Thickness;

		if (Function && static_class())
			Function->ProcessEvent(static_class(), Function, &Args);
	}

	// DrawDebugLine fonksiyonu
	static inline void DrawDebugLine(
		UObject* WorldContextObject,
		FVector LineStart,
		FVector LineEnd,
		flinearcolor LineColor,
		float Duration,
		float Thickness
	) {
		auto function_name = crypt(L"Engine.KismetSystemLibrary.DrawDebugLine").decrypt();
		static UObject* Function = nullptr;
		if (!Function)
			Function = UObject::StaticFindObject(nullptr, nullptr, function_name, false);

		struct Params {
			UObject* WorldContextObject;
			FVector LineStart;
			FVector LineEnd;
			flinearcolor LineColor;
			float Duration;
			float Thickness;
		} Args;

		Args.WorldContextObject = WorldContextObject;
		Args.LineStart = LineStart;
		Args.LineEnd = LineEnd;
		Args.LineColor = LineColor;
		Args.Duration = Duration;
		Args.Thickness = Thickness;

		if (Function && static_class())
			Function->ProcessEvent(static_class(), Function, &Args);
	}


	static inline void DrawDebugCapsule(
		UObject* WorldContextObject,
		FVector Center,
		float HalfHeight,
		float Radius,
		FRotator Rotation,
		flinearcolor LineColor,
		float Duration,
		float Thickness
	) {
		auto function_name = crypt(L"Engine.KismetSystemLibrary.DrawDebugCapsule").decrypt();
		static UObject* Function = nullptr;
		if (!Function)
			Function = UObject::StaticFindObject(nullptr, nullptr, function_name, false);

		struct Params {
			UObject* WorldContextObject;
			FVector Center;
			float HalfHeight;
			float Radius;
			FRotator Rotation;
			flinearcolor LineColor;
			float Duration;
			float Thickness;
		} Args;

		Args.WorldContextObject = WorldContextObject;
		Args.Center = Center;
		Args.HalfHeight = HalfHeight;
		Args.Radius = Radius;
		Args.Rotation = Rotation;
		Args.LineColor = LineColor;
		Args.Duration = Duration;
		Args.Thickness = Thickness;

		if (Function && static_class())
			Function->ProcessEvent(static_class(), Function, &Args);
	}




	bool LineTraceSingle(
		UWorld2* WorldContextObject,
		fvector Start,
		fvector End,
		ETraceTypeQuery TraceChannel,
		bool bTraceComplex,
		tarray<AActor*> ActorsToIgnore,
		EDrawDebugTrace DrawDebugType,
		FHitResult& OutHit,
		bool bIgnoreSelf,
		flinearcolor TraceColor,
		flinearcolor TraceHitColor,
		float DrawTime
	)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object2<uobject*>(crypt(L"Engine.KismetSystemLibrary.LineTraceSingle").decrypt());

		struct
		{
			UWorld2* WorldContextObject;
			fvector Start;
			fvector End;
			ETraceTypeQuery TraceChannel;
			bool bTraceComplex;
			tarray<AActor*> ActorsToIgnore;
			char  DrawDebugType;
			FHitResult OutHit;
			bool bIgnoreSelf;
			flinearcolor TraceColor;
			flinearcolor TraceHitColor;
			float DrawTime;
			bool ReturnValue; // must match UE function return
		} params;

		params.WorldContextObject = WorldContextObject;
		params.Start = Start;
		params.End = End;
		params.TraceChannel = TraceChannel;
		params.bTraceComplex = bTraceComplex;
		params.ActorsToIgnore = ActorsToIgnore;
		params.DrawDebugType = DrawDebugType;
		params.bIgnoreSelf = bIgnoreSelf;
		params.TraceColor = TraceColor;
		params.TraceHitColor = TraceHitColor;
		params.DrawTime = DrawTime;
		/*    if (!WorldContextObject)
			{
				printf("[ERROR] WorldContextObject is NULL!\n");
			}
			else
			{
				printf("[DEBUG] World is valid: %p\n", WorldContextObject);
			}*/

		static_class()->ProcessEvent(function, &params);

		OutHit = params.OutHit;
		//// ? Debug prints
		//printf("=== LineTraceSingle ===\n");
		//printf("Start: [%.2f, %.2f, %.2f]\n", Start.X, Start.Y, Start.Z);
		//printf("End:   [%.2f, %.2f, %.2f]\n", End.X, End.Y, End.Z);
		//printf("Hit:   %s\n", params.OutHit.bBlockingHit ? "true" : "false");
		//printf("ImpactPoint: [%.2f, %.2f, %.2f]\n", params.OutHit.ImpactPoint.X, params.OutHit.ImpactPoint.Y, params.OutHit.ImpactPoint.Z);
		////printf("HitActor: %p\n", params.OutHit.Actor);
		//printf("ReturnValue: %s\n", params.ReturnValue ? "true" : "false");
		return params.ReturnValue;
	}

}


class math : public uobject
{
public:
	static bool ClassIsChildOf(uobject* TestClass, uobject* ParentClass);

	static inline float vector_size(const fvector& value);

	static frotator RInterpTo_Constant(frotator Current, frotator Target, float DeltaTime, float InterpSpeed);

	static int32_t random_int(int32_t min, int32_t max);
	static double random_float(double min, double max);

	static double distance_2d(fvector2d v1, fvector2d v2);
	static inline frotator find_look_at_rotation(const fvector& start, const fvector& end);

	static fvector mirror_vector_by_normal(fvector in_vect, fvector in_normal);




};

class game_statics : public uobject
{
public:
	static void get_all_actors_of_class(uobject* context, uobject* _class, tarray<gameobject*>* output);
};

class content_library
{
public:
	static void apply_skin(currentequippable* equippable, uobject* skin_asset, uobject* chroma_asset, int level, uobject* charm_data, int buddie_level);
	static void clear_weapon_components(currentequippable* equippable);
};

namespace basecomponent {
	bool is_ally(ashootercharacter* enemy, ashootercharacter* self);
}


void SecurelyClearBuffer(volatile char* buffer, size_t size) {

	if (buffer) SecureZeroMemory((void*)buffer, size);
}
bool verifyChallengeTimestamp(const std::string& challenge, int allowedWindowSec = 30) {

	size_t pos = challenge.find(':');
	if (pos == std::string::npos)
		return false;

	std::string timestampStr = challenge.substr(0, pos);
	time_t challengeTime = std::stoll(timestampStr);

	auto now = std::chrono::system_clock::now();
	auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

	return std::abs(now_seconds - challengeTime) <= allowedWindowSec;
}
std::string computeHandshakeResponse(const std::string& challenge, const std::string& sharedSecret) {

	return std::to_string(std::hash<std::string>{}(challenge + sharedSecret));
}
std::string xorEncryptDecrypt(const std::string& input, const std::string& key) {

	std::string output = input;
	for (size_t i = 0; i < input.size(); i++) {
		output[i] = input[i] ^ key[i % key.size()];
	}
	return output;
}


class variables_construct
{
public:
	uobject* blueprints;
	UObject* blueprints2;
	uobject* gameplay_statics;
	uobject* kismet_system;
	uobject* kismet_string;
	uobject* kismet_text;
	uobject* math_system;
	uobject* bobber;
	uobject* rendering_library;
	uobject* content_library;
	uobject* ares_outline_rendering;
	uobject* ares_equippable;
	uobject* ares_instance;
	uobject* base_component;
	uobject* Ngigga;
	uobject* AresClient;
	uobject* ThreadedChatManager;
	uobject* SceneComponent;
	uobject* flxxdzjosh;
	uobject* flxxdzjosh1;
	fkey f1;
	fkey spacebar;
	fkey leftmousebutton;
	fkey n_key;

	uobject* ucameracomponent;


	void init_variables() {
		


		base_component = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__BaseTeamComponent").decrypt());
		blueprints = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ShooterBlueprintLibrary").decrypt());
		ucameracomponent = uobject::find_object<uobject*>(crypt(L"Engine.Default__CameraComponent").decrypt());
		blueprints2 = UObject::find_object2<UObject*>(crypt(L"ShooterGame.Default__ShooterBlueprintLibrary").decrypt());
		flxxdzjosh = uobject::find_object<uobject*>(crypt(L"Ares_Characters_FunctionLibrary.Ares_Characters_FunctionLibrary_C").decrypt());
		flxxdzjosh1 = uobject::find_object<uobject*>(crypt(L"Engine.Default__MaterialInstanceDynamic").decrypt());
		

		gameplay_statics = uobject::find_object<uobject*>(crypt(L"Engine.Default__GameplayStatics").decrypt());
		kismet_system = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetSystemLibrary").decrypt());
		kismet_string = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetStringLibrary").decrypt());
		rendering_library = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetRenderingLibrary").decrypt());
		kismet_text = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetTextLibrary").decrypt());
		math_system = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetMathLibrary").decrypt());
		bobber = uobject::find_object<uobject*>(crypt(L"Engine.MeshComponent.SetAresOutlineMode").decrypt());
		content_library = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ContentLibrary").decrypt());
		ares_outline_rendering = uobject::find_object<uobject*>(crypt(L"Renderer.Default__AresOutlineRendering").decrypt());
		ares_equippable = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__AresEquippable").decrypt());
		ares_instance = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__AresClientGameInstance").decrypt());
		Ngigga = uobject::find_object<uobject*>(crypt(L"Engine.Default__PrimitiveComponent").decrypt());
		AresClient = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__AresClientGameInstance").decrypt());
		ThreadedChatManager = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ThreadedChatManager").decrypt());
		SceneComponent = uobject::find_object<uobject*>(crypt(L"Engine.Default__SceneComponent").decrypt());
	}
};

class MAWGAGO {
public:
	uobject* gameobject = uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject"));
	uobject* Fog = uobject::find_object<uobject*>(crypt(L"Engine.ExponentialHeightFogComponent"));

	uobject* engineactor = uobject::find_object<uobject*>(crypt(L"Engine.Actor"));
	uobject* pawn = uobject::find_object<uobject*>(crypt(L"ShooterGame.Pawn"));
	uobject* patch = uobject::find_object<uobject*>(crypt(L"ShooterGame.PatchManager"));
	uobject* projectile = uobject::find_object<uobject*>(crypt(L"ShooterGame.Projectile"));
	

};


inline variables_construct variables;


struct USceneComponentHelpers
{

	struct FHitResult {
		int32 FaceIndex; // 0x00(0x04)
		float Time; // 0x04(0x04)
		float Distance; // 0x08(0x04)
		uint8 pad_C[0x4]; // 0x0c(0x04)
		fvector Location; // 0x10(0x18)
		fvector ImpactPoint; // 0x28(0x18)
		fvector Normal; // 0x40(0x18)
		fvector ImpactNormal; // 0x58(0x18)
		fvector TraceStart; // 0x70(0x18)
		fvector TraceEnd; // 0x88(0x18)
		float PenetrationDepth; // 0xa0(0x04)
		int32 MyItem; // 0xa4(0x04)
		int32 Item; // 0xa8(0x04)
		uint8 ElementIndex; // 0xac(0x01)
		uint8 bBlockingHit : 1; // 0xad(0x01)
		uint8 bStartPenetrating : 1; // 0xad(0x01)
		uint8 pad_AD_2 : 6; // 0xad(0x01)
		uint8 pad_AE[0x2]; // 0xae(0x02)
		UPhysicalMaterial* PhysMaterial; // 0xb0(0x08)
		AActor* Actor; // 0xb8(0x18)
		UPrimitiveComponent* Component; // 0xd0(0x08)
		fname BoneName; // 0xd8(0x0c)
		fname MyBoneName; // 0xe4(0x0c)
	};

	static void Detach(void* Target)
	{
		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_DetachFromComponent");

		if (!fn || !Target) return;

		struct
		{
			int LocationRule;
			int RotationRule;
			int ScaleRule;
			bool bCallModify;
		} params;

		params.LocationRule = 0;
		params.RotationRule = 0;
		params.ScaleRule = 0;
		params.bCallModify = true;

		((uobject*)Target)->process_event(fn, &params);
	}

	static uobject* GetChildComponent(int32_t index)
	{


		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.GetChildComponent");

		if (!fn) return nullptr;

		struct
		{
			int32_t Index;
			uobject* ReturnValue;
		} params;

		params.Index = index;

		variables.SceneComponent->process_event(fn, &params);

		return params.ReturnValue;
	}


	static int32_t GetNumChildrenComponents()
	{

		static uobject* fn = nullptr;
		if (!fn)
			fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.GetNumChildrenComponents");

		if (!fn) return 0;

		struct
		{
			int32_t ReturnValue;
		} params;

		variables.SceneComponent->process_event(fn, &params);

		return params.ReturnValue;
	}



	static bool AttachTo(uskeletalmeshcomponent* Target, uskeletalmeshcomponent* Parent, fname SocketName,
		int LocationRule, int RotationRule, int ScaleRule, bool bWeldSimulatedBodies)
	{
		static uobject* Function = uobject::find_object< uobject*>(crypt(L"Engine.SceneComponent.K2_AttachToComponent").decrypt());

		struct
		{
			void* Parent;
			fname SocketName;
			int LocationRule;
			int RotationRule;
			int ScaleRule;
			bool bWeldSimulatedBodies;
			bool ReturnValue;
		} params;

		params.Parent = Parent;
		params.SocketName = SocketName;
		params.LocationRule = LocationRule;
		params.RotationRule = RotationRule;
		params.ScaleRule = ScaleRule;
		params.bWeldSimulatedBodies = bWeldSimulatedBodies;

		if (Function && Target)
			Function->ProcessEvent(Target, Function, &params);

		return params.ReturnValue;
	}
	static void SetRelativeLocation(void* Target, const fvector& Location, bool bSweep = false, bool bTeleport = true)
	{
		static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeLocation").decrypt());

		struct
		{
			fvector NewLocation;
			bool bSweep;
			FHitResult SweepHitResult;  // output param
			bool bTeleport;
		} params;

		params.NewLocation = Location;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;
		memset(&params.SweepHitResult, 0, sizeof(FHitResult)); // safe zero init

		if (Target && fn)
			fn->ProcessEvent(Target, fn, &params);
	}
	
	static void SetRelativeRotation(void* Target, const frotator& Location, bool bSweep = false, bool bTeleport = true)
	{
		static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation").decrypt());

		struct
		{
			frotator NewLocation;
			bool bSweep;
			FHitResult SweepHitResult;  // output param
			bool bTeleport;
		} params;

		params.NewLocation = Location;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;
		memset(&params.SweepHitResult, 0, sizeof(FHitResult)); // safe zero init

		if (Target && fn)
			fn->ProcessEvent(Target, fn, &params);
	}

	static void K2_SetWorldLocation(void* Target, const frotator& Location, bool bSweep = false, bool bTeleport = true)
	{
		static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetWorldLocation").decrypt());

		struct
		{
			frotator NewLocation;
			bool bSweep;
			FHitResult SweepHitResult;  // output param
			bool bTeleport;
		} params;

		params.NewLocation = Location;
		params.bSweep = bSweep;
		params.bTeleport = bTeleport;
		memset(&params.SweepHitResult, 0, sizeof(FHitResult)); // safe zero init

		if (Target && fn)
			fn->ProcessEvent(Target, fn, &params);
	}






};

namespace KismetMathLibrary {
	uobject* KismetMathLibrary();
	fvector FindLookAtRotation(fvector start, fvector target);


	
}



struct AGameObject : public uobject{
	uint8                                         Pad_460[0x8];                                      // 0x0460(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	uobject* Mesh;                                              // 0x0468(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* Persistence;                                       // 0x0470(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          Invulnerable;                                      // 0x0478(0x0001)(BlueprintVisible, Net, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bIgnoreFriendlyFireModifiers;                      // 0x0479(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bIgnoreFriendlyFireModifiersForInstigator;         // 0x047A(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bPlayImpactEffects;                                // 0x047B(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         PostDeathLifespan;                                 // 0x047C(0x0004)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* CanBeTeleportedFilter;                             // 0x0480(0x0001)(Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uint8                                         Pad_481[0x7];                                      // 0x0481(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	uobject* DamageHandler;                                     // 0x0488(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uobject* HealthSection;                                     // 0x0490(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uobject* DestructionComponent;                              // 0x0498(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uobject* AIPerceptionStimuliSourceComponent;         // 0x04A0(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uobject* PlayspaceVisibility;                               // 0x04A8(0x0008)(Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, InstancedReference, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)

	fvector GetObjectLocation();
	ftext GetDisplayName();
	float GetObjectHealh();

	void SetActorHiddenInGame(bool bNewHidden) {

		
	
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorHiddenInGame").decrypt());
		if (!Function)
			return;

		struct {
			bool bNewHidden;
		} Parameters;

		Parameters.bNewHidden = bNewHidden;

		this->process_event(Function, &Parameters);
	}

	void SetActorEnableCollision(bool bNewActorEnableCollision) {


		
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorEnableCollision").decrypt());
		if (!Function)
			return;

		struct {
			bool bNewActorEnableCollision;
		} Parameters;

		Parameters.bNewActorEnableCollision = bNewActorEnableCollision;

		this->process_event(Function, &Parameters);
	}


};

struct UParticleSystemComponent : uobject {
	void K2_DestroyComponent(uobject* object) {
		
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(Encrypt(L"Engine.ActorComponent.K2_DestroyComponent"));

		struct
		{
			uobject* newscale;
		}Parameters;
		Parameters.newscale = this;
		this->ProcessEvent(function, &Parameters);
	}

	void Deactivate() {
		
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(Encrypt(L"Engine.ActorComponent.Deactivate"));

		this->ProcessEvent(function, nullptr);
	}
	
};
struct UParticleSystem : uobject {

};


enum class EAttachLocation : uint8_t
{
	KeepRelativeOffset = 0,
	KeepWorldPosition = 1,
	SnapToTarget = 2,
	SnapToTargetIncludingScale = 3,
	EAttachLocation_MAX = 4,
};


// Enum Engine.EAttachmentRule
// NumValues: 0x0004
enum class EAttachmentRule : uint8_t
{
	KeepRelative = 0,
	KeepWorld = 1,
	SnapToTarget = 2,
	EAttachmentRule_MAX = 3,
};

enum class EAresParticleVariantColor : uint8_t
{
	AresVariantBaseColor = 0,
	AresVariant1Color = 1,
	AresVariant2Color = 2,
	AresVariant3Color = 3,
	AresVariantRadiantColor = 4,
	EAresParticleVariantColor_MAX = 5,
};

enum class EPSCPoolMethod : uint8_t
{
	None = 0,
	AutoRelease = 1,
	ManualRelease = 2,
	ManualRelease_OnComplete = 3,
	FreeInPool = 4,
	EPSCPoolMethod_MAX = 5,
};
namespace GameplayStatics {

	struct predict_projectile_path_params {
		fvector start_location;
		fvector launch_velocity;
		bool trace_with_collision = true;
		char pad_19[0x3];
		float projectile_radius = 10;
		float max_sim_time = 2;
		bool trace_with_channel = true;
		ECollisionChannel trace_channel = ECollisionChannel::ECC_WorldDynamic;
		char pad_26[0x2];
		char adssad[0x10];
		tarray<ashootercharacter*> actors_to_ignore;
		float sim_frequency = 40;
		float override_gravity_z = 0;
		EDrawDebugTrace draw_debug_type = EDrawDebugTrace::None;
		char pad_51[0x3];
		float draw_debugt_time = 1;
		bool trace_complex = false;
		char pad_59[0x7];
	};

	struct point_data {
		struct fvector location; // 0x00(0x0c)
		struct fvector velocity; // 0x0c(0x0c)
		float time; // 0x18(0x04)
	};

	struct path_result {
		tarray<point_data> path_data; // 0x00(0x10)
		point_data LastTraceDestination; // 0x10(0x1c)
		FHitResult hit_result; // Hitresult
	};

	uobject* GameplayStatics();
	uobject* get_game_instancee(uworld* world_context);

	double GetTimeSeconds(uobject* world_context)
	{
		
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetTimeSeconds"));

		struct {
			uobject* world_context;
			double return_value;
		} params = { world_context };

		params.world_context = world_context;


		variables.gameplay_statics->process_event(function, &params);
		return params.return_value;
	}

	UParticleSystemComponent* SpawnEmitterAtLocationWithWorld(
		uobject* WorldContextObject,
		UParticleSystem* EmitterTemplate,
		fvector Location,
		frotator Rotation,
		fvector Scale,
		bool bAutoDestroy,
		EPSCPoolMethod PoolingMethod,
		bool bAutoActivateSystem,
		bool bIsFirstPerson,
		float WarmupTime)
	{
		static UObject* Function = nullptr;
		if (!Function)
			Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.GameplayStatics.SpawnEmitterAtLocationWithWorld", false);

		struct {
			uobject* WorldContextObject;
			UParticleSystem* EmitterTemplate;
			fvector Location;
			frotator Rotation;
			fvector Scale;
			bool bAutoDestroy;
			EPSCPoolMethod PoolingMethod;
			bool bAutoActivateSystem;
			bool bIsFirstPerson;
			float WarmupTime;
			UParticleSystemComponent* Out;
		} Args;

		Args.WorldContextObject = WorldContextObject;
		Args.EmitterTemplate = EmitterTemplate;
		Args.Location = Location;
		Args.Rotation = Rotation;
		Args.Scale = Scale;
		Args.bAutoDestroy = bAutoDestroy;
		Args.PoolingMethod = PoolingMethod;
		Args.bAutoActivateSystem = bAutoActivateSystem;
		Args.bIsFirstPerson = bIsFirstPerson;
		Args.WarmupTime = WarmupTime;

		Function->ProcessEvent(GameplayStatics(), Function, &Args);
		return Args.Out;
	}

	static inline UParticleSystemComponent* SpawnEmitterAttached(
		UParticleSystem* EmitterTemplate,
		USceneComponent* AttachToComponent,
		fname AttachPointName,
		fvector Location,
		FRotator Rotation,
		fvector Scale,
		EAttachLocation LocationType,
		bool bAutoDestroy,
		EPSCPoolMethod PoolingMethod,
		bool bAutoActivate,
		bool bIsFirstPerson,
		float WarmupTime,
		EAresParticleVariantColor ParticleVariantColor, uworld* World)
	{
		static uobject* Function = nullptr;
		if (!Function)
			Function = uobject::find_object<uobject*>(L"Engine.GameplayStatics.SpawnEmitterAttached");
		if (!Function) return nullptr;

		struct {
			UParticleSystem* EmitterTemplate;
			USceneComponent* AttachToComponent;
			fname AttachPointName;
			fvector Location;
			FRotator Rotation;
			fvector Scale;
			EAttachLocation LocationType;
			bool bAutoDestroy;
			EPSCPoolMethod PoolingMethod;
			bool bAutoActivate;
			bool bIsFirstPerson;
			float WarmupTime;
			EAresParticleVariantColor ParticleVariantColor;
			UParticleSystemComponent* Out;
		} Args;

		Args.EmitterTemplate = EmitterTemplate;
		Args.AttachToComponent = AttachToComponent;
		Args.AttachPointName = AttachPointName;
		Args.Location = Location;
		Args.Rotation = Rotation;
		Args.Scale = Scale;
		Args.LocationType = LocationType;
		Args.bAutoDestroy = bAutoDestroy;
		Args.PoolingMethod = PoolingMethod;
		Args.bAutoActivate = bAutoActivate;
		Args.bIsFirstPerson = bIsFirstPerson;
		Args.WarmupTime = WarmupTime;
		Args.ParticleVariantColor = ParticleVariantColor;
		Args.Out = nullptr;

		World->process_event(Function, &Args);
		return Args.Out;
	}


	inline static uobject* get_game_instance(uworld* world_context);
	template<typename type>
	static inline tarray<type*> GetAllActorsOfClass(uworld* world_context, uobject* actor_class) {

		uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetAllActorsOfClass"));
		struct {
			uworld* world_context;
			uobject* actor_class;
			tarray<type*> return_value;
		} params = { world_context, actor_class };

		GameplayStatics()->ProcessEvent(function, &params);
		return params.return_value;
	}

	static inline void GetAllActorsOfClass2(uworld* WorldContextObject, uobject* ActorClass, tarray<AGameObject*>* OutActors)
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.GameplayStatics.GetAllActorsOfClass");

		struct
		{
			uworld* WorldContextObject;
			uobject* ActorClass;
			tarray<AGameObject*> OutActors;
		} params;

		params.WorldContextObject = WorldContextObject;
		params.ActorClass = ActorClass;

		GameplayStatics()->ProcessEvent(function, &params);

		if (OutActors)
			*OutActors = params.OutActors;
	}

	static inline bool predict_projectile_path(uobject* world_context, fvector start_location, fvector start_direction, tarray<ashootercharacter*> actors_to_ignore, float override_graivity_z, path_result* result)
	{
		auto function = uobject::find_object<uobject*>(L"Engine.GameplayStatics.Blueprint_PredictProjectilePath_Advanced");

		GameplayStatics::predict_projectile_path_params predict_params = GameplayStatics::predict_projectile_path_params();
		predict_params.start_location = start_location;
		predict_params.launch_velocity = start_direction;
		predict_params.projectile_radius = 5;
		predict_params.trace_channel = ECollisionChannel::ECC_WorldDynamic;
		predict_params.trace_complex = false;
		predict_params.trace_with_collision = true;
		predict_params.trace_with_channel = true;
		predict_params.actors_to_ignore = actors_to_ignore;
		predict_params.draw_debug_type = EDrawDebugTrace::None;
		predict_params.draw_debugt_time = 1;
		predict_params.sim_frequency = 40;
		predict_params.max_sim_time = 2;
		predict_params.override_gravity_z = override_graivity_z;

		struct {
			uobject* world_context;
			predict_projectile_path_params predict_params;
			path_result path_result;
			bool return_value;
		} params = { world_context, predict_params };

		GameplayStatics()->process_event(function, &params);

		if (result) {
			*result = params.path_result;
		}

		return params.return_value;
	}



}
struct UCameraComponent : uobject {
	bool bOverrideFov; // 0x330(0x01)
	bool bOverrideCameraRenderSettings; // 0x331(0x01)
	char pad_332[0x2]; // 0x332(0x02)
	float fieldOfView; // 0x334(0x04)
	float OrthoWidth; // 0x338(0x04)
	float OrthoNearClipPlane; // 0x33c(0x04)
	float OrthoFarClipPlane; // 0x340(0x04)
	float AspectRatio; // 0x344(0x04)
	uobject* AspectRatioAxisConstraint; // 0x348(0x01)
	char bConstrainAspectRatio : 1; // 0x349(0x01)
	char bOverrideAspectRatioAxisConstraint : 1; // 0x349(0x01)
	char bUseFieldOfViewForLOD : 1; // 0x349(0x01)
	char bLockToHmd : 1; // 0x349(0x01)
	char bUsePawnControlRotation : 1; // 0x349(0x01)
	char pad_349_5 : 3; // 0x349(0x01)
    uobject* ProjectionMode; // 0x34a(0x01)
	char pad_34B[0x65]; // 0x34b(0x65)
	float PostProcessBlendWeight; // 0x3b0(0x04)
	char pad_3B4[0x2c]; // 0x3b4(0x2c)
     uobject* PostProcessSettings; // 0x3e0(0x800)

};


namespace ShooterGameBlueprints
{
	uobject* Static_Class()
	{

		auto class_name = crypt(L"ShooterGame.Default__ShooterBlueprintLibrary").decrypt();
		return uobject::StaticFindObject(nullptr, nullptr, class_name, false);
	}



	static inline bool ares_line_trace_single_by_channel(
		UWorld2* world_context,
		const fvector& start,
		const fvector& end,
		const tarray<uobject*>& actors_to_ignore,
		FHitResult* out_hit,
		ECollisionChannel trace_channel,
		bool trace_complex,
		bool include_moving_objects)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object2<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.AresLineTraceSingleByChannel"));

		struct
		{
			UWorld2* world_context_object;
			fvector start;
			fvector end;
			tarray<uobject*> actors_to_ignore;
			FHitResult out_hit;
			ECollisionChannel trace_channel;
			bool trace_complex;
			bool include_moving_objects;
			bool return_value;
		} params{};

		params.world_context_object = world_context;
		params.start = start;
		params.end = end;
		params.actors_to_ignore = actors_to_ignore;
		params.trace_channel = trace_channel;
		params.trace_complex = trace_complex;
		params.include_moving_objects = include_moving_objects;

		// Call safely
		if (function)
			Static_Class()->ProcessEvent_2(function, &params);

		// Copy result
		if (out_hit)
			*out_hit = params.out_hit;

		return params.return_value;
	}


	static inline fstring GetValVersion() {
		auto function = uobject::find_object<uobject*>(L"ShooterGame.ShooterBlueprintLibrary.GetFullBuildVersionString");

		if (function == nullptr)
			return nullptr;

		fstring return_value;

		function->ProcessEvent(Static_Class(), function, &return_value);

		return return_value;
	}

	static void GetWallPenetrationSpans(
		uworld* World,
		const fvector& Start,
		const fvector& End,
		const tarray<AActor*>& IgnoreActors,
		ECollisionChannel TraceChannel,
		float IgnoreGapTolerance,
		FWallSpanList& OutWallSpans)
	{
		static uobject* Function = nullptr;
		if (!Function) {
			Function = uobject::find_object<uobject*>(L"ShooterGame.ShooterBlueprintLibrary.GetWallPenetrationSpans");
		}

		if (!Function || !World) {
			return;
		}

		struct {
			uworld* World;
			fvector Start;
			fvector End;
			tarray<AActor*> IgnoreActors;
			ECollisionChannel TraceChannel;
			float IgnoreGapTolerance;
			FWallSpanList OutWallSpans;
		} params;

		params.World = World;
		params.Start = Start;
		params.End = End;
		params.IgnoreActors = IgnoreActors;
		params.TraceChannel = TraceChannel;
		params.IgnoreGapTolerance = IgnoreGapTolerance;

		World->process_event(Function, &params);
		OutWallSpans = params.OutWallSpans;
	}
}

namespace Class {
	uobject* ShooterGameObject();

	static inline uobject* ExponentialHeightFog()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.ExponentialHeightFog");

		return function;

	}

	static inline uobject* Light()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.Light");

		return function;

	}


	static inline uobject* Actors()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.Actor");

		return function;

	}
}
namespace keys
{
	static fkey space;
	static fkey left_mouse;
	static fkey w;
	static fkey a;
	static fkey s;
	static fkey d;
	static fkey left_alt;
}
ftext MakeSafeFText(const fstring& input)
{
	ftextdata* data = new ftextdata();
	data->TextSource = input;

	ftext out;
	out.TextData = data;

	return out;
}
struct AAresOnGroundEquippable : AGameObject {
	char pad_4B0[0x8]; // 0x4b0(0x08)
	uobject* Collision; // 0x4b8(0x08)
	uobject* NearbyCollision; // 0x4c0(0x08)
	uobject* AuthNearbyCharacters; // 0x4c8(0x50)
	currentequippable* MyEquippable; // 0x518(0x08)
	ashootercharacter LastOwner; // 0x520(0x08)
	bool bIsSilentDrop; // 0x528(0x01)
	char pad_529[0x7]; // 0x529(0x07)

};


namespace AGameModeBase
{

	class fstring                                 OptionsString;                                     // 0x0460(0x0010)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* GameSessionClass;                                  // 0x0470(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* GameStateClass;                                    // 0x0478(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* PlayerControllerClass;                             // 0x0480(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* PlayerStateClass;                                  // 0x0488(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* HUDClass;                                          // 0x0490(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* DefaultPawnClass;                                  // 0x0498(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* SpectatorClass;                                    // 0x04A0(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* ReplaySpectatorPlayerControllerClass;              // 0x04A8(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* ServerStatReplicatorClass;                         // 0x04B0(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* SpectatorPlayerControllerClass;                    // 0x04B8(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* SpectatorPlayerStateClass;                         // 0x04C0(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoClear, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* GameSession;                                       // 0x04C8(0x0008)(ZeroConstructor, Transient, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* GameState;                                         // 0x04D0(0x0008)(ZeroConstructor, Transient, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uobject* ServerStatReplicator;                              // 0x04D8(0x0008)(ZeroConstructor, Transient, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)

	static uobject* GetDefaultObj() {
		static uobject* default_obj = uobject::find_object<uobject*>(L"Engine.Default__GameModeBase");
		return default_obj;
	}

	static int32 GetNumSpectators()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.GameModeBase.GetNumSpectators");

		struct {
			int32 ReturnValue;
		} params;

		GetDefaultObj()->ProcessEvent_2(function, &params);
		return params.ReturnValue;

	}
};

ftext string_to_text(const fstring& input)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetTextLibrary.Conv_StringToText").decrypt());

	if (!variables.kismet_text || !function)
		return ftext();

	struct
	{
		fstring in_string;
		ftext   return_value;
	} params;

	params.in_string = input;

	variables.kismet_text->ProcessEvent(function, &params);

	return params.return_value;
}





