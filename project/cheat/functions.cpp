#include "functions.hpp"
#include "../sdk/offsets.hpp"
#include "../sdk/ret_spoof.h"


uclass* uobject::object_class() {
	
	return memory::read<uclass*>(class_ptr + 0x10);
}





tarray<int> equippable_skin_data_asset::get_skin_levels() {
	
	return memory::read2<tarray<int>>(std::uintptr_t(this) + 0x88);
}


equippable_skin_data_asset* equippable_skin_inventory_model::get_skin_data_asset() {
	
	return memory::read2<equippable_skin_data_asset*>(std::uintptr_t(this) + 0x108);
}

uobject* equippable_skin_chroma_inventory_model::get_skin_chroma_data_asset() {
	
	return memory::read2<uobject*>(std::uintptr_t(this) + 0x108);
}

uobject* equippable_charm_instance_inventory_model::get_charm_data_asset() {
	
	return memory::read2<uobject*>(std::uintptr_t(this) + 0x68);
}

equippable_charm_level_data_asset* equippable_charm_instance_inventory_model::get_charm_level_data_asset() {
	
	return memory::read2<equippable_charm_level_data_asset*>(std::uintptr_t(this) + 0x70);
}

int equippable_charm_level_data_asset::get_charm_level() {
	
	return memory::read2<int>(std::uintptr_t(this) + 0xe0);
}

void uobject::ProcessEvent(void* function, void* params) {

	SPOOF_FUNC

		reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(
			spoofcall_stub
			)(this, static_cast<uobject*>(function), params, offsets::MagicOffsets,
				reinterpret_cast<void*>(memory::module_base + offsets::process_event)
				);
}


void uobject::ProcessEvent_(uobject* function, void* params) {
	void** vtable = *reinterpret_cast<void***>(this);
	if (!vtable)
		return;

	void* fProcessEvent = vtable[offsets::vtable];
	if (!fProcessEvent)
		return;

	reinterpret_cast<void(*)(void*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(
		this, function, params, offsets::MagicOffsets, fProcessEvent
		);
}


void uobject::ProcessEvent_2(uobject* function, void* params) {
	static uintptr_t negritas = memory::module_base + offsets::process_event;
	reinterpret_cast<void (*)(uobject*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(this, function, params, offsets::MagicOffsets, (void*)negritas);

}



void uobject::ProcessEvent(void* class_, uobject* function, void* params) {
	void** vtable = *reinterpret_cast<void***>(this);
	if (!vtable)
		return;
		
	void* fProcessEvent = vtable[offsets::vtable];
	if (!fProcessEvent)
		return;

	reinterpret_cast<void(*)(void*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(
		class_, function, params, offsets::MagicOffsets, fProcessEvent
		);
}

void uobject::process_event_2(uobject* function, void* args) {

	SPOOF_FUNC

		return reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(this, function, args, offsets::MagicOffsets, (void*)(memory::module_base + offsets::process_event));
}


void uobject::process_event(uobject* function, void* args) {

	SPOOF_FUNC

		reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(
			spoofcall_stub
			)(this, static_cast<uobject*>(function), args, offsets::MagicOffsets,
				reinterpret_cast<void*>(memory::module_base + offsets::process_event)
				);

}

void uobject::process_event35(uobject* function, void* args) {

	return reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(this, function, args, 0x46C4660, (void*)(memory::module_base + offsets::process_event));

}



uobject* uobject::StaticLoadObject(const wchar_t* Name)
{

	

	if (!Name)
		return nullptr;


	static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
	return reinterpret_cast<uobject* (__fastcall*)(uobject*, uobject*, const wchar_t*, const wchar_t*, uint32_t, uint32_t, void*, uintptr_t, void*)>(spoofcall_stub)(nullptr, nullptr, Name, nullptr, 0, 0, nullptr, offsets::MagicOffsets, (void*)StaticLoadObjectAddress);
}

static uobject* StaticLoadObject(const wchar_t* ObjectPath) {

	if (!ObjectPath)
		return nullptr;


	static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
	return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, const wchar_t*, uint32_t, uint32_t, void*, uintptr_t, void*)>(spoofcall_stub)(nullptr, nullptr, ObjectPath, nullptr, 0, 0, nullptr, offsets::MagicOffsets, (void*)StaticLoadObjectAddress);


}



uobject* uobject::StaticFindObject(uobject* Class, uobject* InOuter, const wchar_t* Name, bool ExactClass)
{
	
	static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;
	return reinterpret_cast<uobject * (*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(Class, InOuter, Name, ExactClass, offsets::MagicOffsets, (void*)StaticFindObjectAddress);
}	





uint64_t fmemory::malloc(int32_t size, uint32_t aligment) {
	
	auto niga = memory::module_base + offsets::fmemory_malloc;
	return reinterpret_cast<uint64_t(__cdecl*)(uint64_t, int, uintptr_t, void*)>(spoofcall_stub)(size, aligment, offsets::MagicOffsets, (void*)niga);
}

uint64_t fmemory2::malloc2(int32_t size, uint32_t alignment) {
	
	auto niga = memory::module_base + offsets::fmemory_malloc;
	return reinterpret_cast<uint64_t(__cdecl*)(uint64_t, int, uintptr_t, void*)>(
		spoofcall_stub
		)(size, alignment, offsets::MagicOffsets, (void*)niga);
}

uint64_t fmemory3::malloc3(int32_t size, uint32_t aligment) {
	
	auto niga = memory::module_base + offsets::fmemory_malloc;
	return reinterpret_cast<uint64_t(__cdecl*)(uint64_t, int, uintptr_t, void*)>(
		spoofcall_stub
		)(size, aligment, offsets::MagicOffsets, (void*)niga);
}


void UPrimitiveComponent::set_material(int32_t element_index, uobject* material)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetMaterial").decrypt());

	struct {
		int32_t element_index;
		uobject* material;
	} params = { element_index, material };

	this->process_event(function, &params);
}


uobject* UPrimitiveComponent::CreateAndSetMaterialInstanceDynamicFromMaterial(int32_t element_index, uobject* parent)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial").decrypt());

	struct {
		int32_t element_index;
		uobject* parent;
		uobject* return_value;
	} params = { element_index, parent };

	this->process_event(function, &params);
	return params.return_value;

}

void aplayercontroller::ServerSay(fstring Msg, int32 ChatMode) {

	static uobject* function;
	if (!function)
		function = this->StaticFindObject(0, 0, crypt(L"AresPlayerController.ServerSay").decrypt(), false);

	struct { fstring a1; int32 a2; } params;
	params.a1 = Msg;
	params.a2 = ChatMode;

	this->process_event(function, &params);
	return;
}
void UPrimitiveComponent::SetRenderCustomDepth(bool bValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetRenderCustomDepth").decrypt());

	struct {
		bool bValue;
	} params = { bValue };

	this->process_event(function, &params);
}




UMaterialInstanceDynamic* UPrimitiveComponent::get_material(int32_t element_index)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.GetMaterial").decrypt());

	struct {
		int32_t element_index;
		UMaterialInstanceDynamic* return_value;
	} params = { element_index };

	this->process_event(function, &params);

	return params.return_value;
}
int32_t UPrimitiveComponent::GetNumMaterials()
{

	static uobject* Function = 0;
	if (!Function) Function = this->StaticFindObject(nullptr, nullptr, crypt(L"Engine.PrimitiveComponent.GetNumMaterials").decrypt(), false);

	struct {
		int32_t ReturnValue;
	} Params = { };

	this->ProcessEvent(this, Function, &Params);

	return Params.ReturnValue;
}
tarray<fname> USceneComponent::GetAllSocketNames() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"Engine.SceneComponent.GetAllSocketNames").decrypt()
		);

	struct
	{
		tarray<fname> ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;

}
tarray<fname> uskeletalmeshcomponent::GetAllSocketNames() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(
			L"Engine.SceneComponent.GetAllSocketNames"
		);

	struct
	{
		tarray<fname> ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;

}
void USceneComponent::GetChildrenComponents(
	bool bIncludeAllDescendants,
	tarray<USceneComponent*>* OutChildren
)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"Engine.SceneComponent.GetChildrenComponents").decrypt()
		);

	struct
	{
		bool bIncludeAllDescendants;
		tarray<USceneComponent*> Children;
	} params;

	params.bIncludeAllDescendants = bIncludeAllDescendants;

	this->process_event(function, &params);

	if (OutChildren)
		*OutChildren = params.Children;
}

void UPrimitiveComponent::SetCastShadow(bool NewCastShadow)
{
	

	uobject* function = uobject::find_object<uobject*>(
		crypt(L"Engine.PrimitiveComponent.SetCastShadow").decrypt()
	);
	if (!function)
		return;

	struct
	{
		bool NewCastShadow;
	} Parameters;

	Parameters.NewCastShadow = NewCastShadow;

	this->process_event(function, &Parameters);
}


int32_t UPrimitiveComponent::get_num_materials()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.GetNumMaterials").decrypt());

	struct {
		int32_t return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}
int32_t uskeletalmeshcomponent::get_num_materials()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.GetNumMaterials").decrypt());

	struct {
		int32_t return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}

uinventory* ashootercharacter::get_inventory_() {
	return (uinventory*)memory::read<uintptr_t>(uintptr_t(this) + 0x9a8);
}

currentequippable* uinventory::get_current_equippable_() {
	return (currentequippable*)memory::read<uintptr_t>(uintptr_t(this) + 0x248);
}



fstring get_object_namemaw(uobject* obj)
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetObjectName").decrypt());

	struct
	{
		uobject* obj;
		fstring output;
	} params;

	params.obj = { obj };

	variables.kismet_system->process_event(function, &params);
	return params.output;
}


fstring system::get_object_name(uobject* object) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetObjectName").decrypt());

	struct
	{
		uobject* object;
		fstring output;
	} params;

	params.object = { object };

	variables.kismet_system->process_event(function, &params);
	return params.output;
}


FString system::get_object_name2(uobject* object) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetObjectName").decrypt());

	struct
	{
		uobject* object;
		FString output;
	} params;

	params.object = { object };

	variables.kismet_system->process_event(function, &params);
	return params.output;
}

bool system::contains_string(const wchar_t* search_in, const wchar_t* sub_string, bool use_case, bool search_from_end) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Contains").decrypt());

	struct {
		fstring search_in;
		fstring sub_string;
		bool use_case;
		bool search_from_end;
		bool return_value;
	} params = { search_in, sub_string, use_case , search_from_end };

	variables.kismet_string->process_event(function, &params);
	return params.return_value;
}

bool system::starts_with(const wchar_t* source, const wchar_t* prefix, const enum_as_byte<search_case>& search_case) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.StartsWith").decrypt());

	struct {
		fstring source;
		fstring prefix;
		std::uint8_t search_case;
		bool return_value;
	} params = { source, prefix, search_case.get() };

	variables.kismet_string->process_event(function, &params);

	return params.return_value;
}

bool system::LineTraceSingle(
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
		function = uobject::find_object<uobject*>(L"Engine.KismetSystemLibrary.LineTraceSingle");

	struct
	{
		UWorld2* WorldContextObject;
		fvector Start;
		fvector End;
		ETraceTypeQuery TraceChannel;
		bool bTraceComplex;
		tarray<AActor*> ActorsToIgnore;
		EDrawDebugTrace  DrawDebugType;
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


	variables.kismet_system->ProcessEvent_2(function, &params);

	OutHit = params.OutHit;
	
	return params.ReturnValue;
}

bool system::LineTraceSingle2(
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
)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.KismetSystemLibrary.LineTraceSingle");

	struct
	{
		UWorld2* WorldContextObject;
		FVector Start;
		FVector End;
		ETraceTypeQuery TraceChannel;
		bool bTraceComplex;
		TArray<AActor*> ActorsToIgnore;
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

	variables.kismet_system->ProcessEvent_(function, &params);

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

uobject* system::get_outer_object(uobject* object) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetOuterObject").decrypt());

	struct
	{
		uobject* object;
		uobject* output;
	} params;

	variables.kismet_system->process_event(function, &params);

	return params.output;
}

fname string::string_to_name(fstring string) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_StringToName").decrypt());

	struct
	{
		fstring string;
		fname output;
	} params;

	params.string = string;

	variables.kismet_string->process_event(function, &params);

	return params.output;
}


fstring string::Conv_NameToString(fname string) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_NameToString").decrypt());

	struct
	{
		fname string;
		fstring output;
	} params;

	params.string = string;

	variables.kismet_string->process_event(function, &params);

	return params.output;
}


fstring string::buildstring_int(fstring append_to, fstring prefix, int32_t value, fstring suffix) {
	static uobject* function = 0; 
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.BuildString_Int"));

	if (function == nullptr)
		return fstring(L"NONE");

	struct
	{
		fstring append_to;
		fstring prefix;
		int32_t value;
		fstring suffix;
		fstring return_value;
	} params;

	params.append_to = append_to;
	params.prefix = prefix;
	params.value = value;
	params.suffix = suffix;

	variables.kismet_string->process_event(function, &params);

	return params.return_value;
}
 fstring string::int_to_string(int32_t value) {
	static uobject* function = 0; 
	if (!function) 
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_IntToString"));

	if (function == nullptr)
		return {};

	struct
	{
		int32_t value;
		fstring return_value;
	} params;

	params.value = value;

	variables.kismet_string->process_event(function, &params);

	return params.return_value;
}
 ftext text::string_to_text(const fstring& InString)
 {
	 static uobject* function = nullptr;
	 if (!function)
		 function = uobject::find_object<uobject*>(crypt(L"Engine.KismetTextLibrary.Conv_StringToText"));


	 if (!variables.kismet_text || !function)
		 return ftext();


	 struct
	 {
		 fstring InString;
		 ftext ReturnValue;
	 } params;

	 params.InString = InString;

	 variables.kismet_text->process_event(function, &params);

	 return params.ReturnValue;
 }
 
fstring text::text_to_string(ftext string) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetTextLibrary.Conv_TextToString").decrypt());

	struct
	{
		ftext text;
		fstring output;
	} params;

	params.text = string;

	variables.kismet_text->process_event(function, &params);

	return params.output;
}


ugameinstance* uworld::game_instance() {
	
	return memory::read<ugameinstance*>(class_ptr + offsets::game_instance);
}

tarray<ulocalplayer*> ugameinstance::local_players() {
	
	return memory::read<tarray<ulocalplayer*>>(class_ptr + offsets::local_players);
}

ugameviewportclient* ulocalplayer::viewport_client() {
	
	return memory::read<ugameviewportclient*>(class_ptr + offsets::viewport_client);
}

uworld* ugameviewportclient::get_world() {
	
	return memory::read<uworld*>(class_ptr + offsets::viewport_world);
}

ugameinstance* ugameviewportclient::get_gameinstance() {
	
	return memory::read<ugameinstance*>(class_ptr + offsets::viewport_gameinstance);
}


void uskeletalmeshcomponent::SetRelativeScale3D(fvector newscale) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.SetRelativeScale3D"));

	struct
	{
		fvector newscale;
	}Parameters;
	Parameters.newscale = newscale;
	this->process_event(function, &Parameters);
}


void USceneComponent::SetRelativeScale3D(fvector newscale) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.SetRelativeScale3D"));

	struct
	{
		fvector newscale;
	}Parameters;
	Parameters.newscale = newscale;
	this->process_event(function, &Parameters);
}


void USceneComponent::SetWorldScale3D(fvector newscale) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.SetWorldScale3D"));

	struct
	{
		fvector newscale;
	}Parameters;
	Parameters.newscale = newscale;
	this->process_event(function, &Parameters);
}

void UProceduralMeshComponent::CreateMeshSection(
	int32 SectionIndex,
	const tarray<fvector>& Vertices,
	const tarray<int32>& Triangles,
	const tarray<fvector>& Normals,
	const tarray<fvector2d>& UV0,
	const tarray<FColor>& VertexColors,
	const tarray<FProcMeshTangent>& Tangents,
	bool bCreateCollision
)
{
	

	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(
			Encrypt(L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection")
		);

	if (!function)
		return;

	// MUST MATCH SDK PARAMS EXACTLY
	struct
	{
		int32 SectionIndex;
		tarray<fvector> Vertices;
		tarray<int32> Triangles;
		tarray<fvector> Normals;
		tarray<fvector2d> UV0;
		tarray<FColor> VertexColors;
		tarray<FProcMeshTangent> Tangents;
		bool bCreateCollision;
	} params;

	params.SectionIndex = SectionIndex;
	params.Vertices = Vertices;        // ? COPY (NO std::move)
	params.Triangles = Triangles;
	params.Normals = Normals;
	params.UV0 = UV0;
	params.VertexColors = VertexColors;
	params.Tangents = Tangents;
	params.bCreateCollision = bCreateCollision;

	this->process_event(function, &params);
}
void blueprints::GetWallPenetrationSpans(uobject* nigga, fvector StartLocation, fvector EndLocation,
	tarray<AActor*> IgnoreActors, ECollisionChannel Channel,
	float MinimumPlayableSpan, FWallSpanList& Spans)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetWallPenetrationSpans"));

	struct {
		uobject* WorldContextObject;    // 0x00
		fvector StartLocation;          // 0x08
		fvector EndLocation;            // 0x14
		tarray<AActor*> IgnoreActors;   // 0x20 (assuming tarray is 16 bytes: data + size + max)
		ECollisionChannel Channel;      // 0x30 (4 bytes)
		// Compiler will add 4 bytes padding here automatically to align next member
		float MinimumPlayableSpan;      // 0x38 (4 bytes)
		FWallSpanList Spans;            // 0x40 (starts at 0x40)
	} params;

	params.WorldContextObject = nigga;
	params.StartLocation = StartLocation;
	params.EndLocation = EndLocation;
	params.IgnoreActors = IgnoreActors;
	params.Channel = Channel;
	params.MinimumPlayableSpan = MinimumPlayableSpan;



	variables.blueprints->ProcessEvent_2(function, &params);

	Spans = params.Spans;
}
void UProceduralMeshComponent::K2_DestroyComponent() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.ActorComponent.K2_DestroyComponent"));

	struct
	{
		uobject* newscale;
	}Parameters;
	Parameters.newscale = this;
	this->process_event(function, &Parameters);
}
void UProceduralMeshComponent::SetRelativeScale3D1(fvector newscale) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.SetRelativeScale3D"));

	struct
	{
		fvector newscale;
	}Parameters;
	Parameters.newscale = newscale;
	this->process_event(function, &Parameters);
}

void uskeletalmeshcomponent::SetWorldScale3D(fvector newscale) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.SetWorldScale3D"));

	struct
	{
		fvector newscale;
	}Parameters;
	Parameters.newscale = newscale;
	this->process_event(function, &Parameters);



}
fvector uskeletalmeshcomponent::K2_GetComponentLocation() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.K2_GetComponentLocation"));

	struct
	{
		fvector returnvalue;
	}Parameters;

	this->process_event(function, &Parameters);

	return Parameters.returnvalue;

}

fvector uskeletalmeshcomponent::K2_GetComponentScale() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.K2_GetComponentScale"));

	struct
	{
		fvector returnvalue;
	}Parameters;

	this->process_event(function, &Parameters);

	return Parameters.returnvalue;

}



frotator uskeletalmeshcomponent::K2_GetComponentRotation() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"Engine.SceneComponent.K2_GetComponentRotation"));

	struct
	{
		frotator returnvalue;
	}Parameters;

	this->process_event(function, &Parameters);

	return Parameters.returnvalue;

}


uskeletalmeshcomponent* acknowledgedpawn::GetCoreMesh3P1()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"ShooterGame.ShooterCharacter.GetCoreMesh3P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;

}


uskeletalmeshcomponent* acknowledgedpawn::GetCoremesh1pOverlay()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(Encrypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;

}

uskeletalmeshcomponent* ashootercharacter::GetCosmesticMesh3P()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCosmeticMesh3P").decrypt());

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;

}

uskeletalmeshcomponent* ashootercharacter::GetCoreMesh3P()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCoreMesh3P").decrypt());

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;

}
void ashootercharacter::Set3pMeshVisible(bool value) {
	static uobject* function;
	if (!function)
		function = this->find_object<uobject*>(crypt(L"ShooterCharacter.Set3PMeshVisible").decrypt());

	struct { bool a1; } params;
	params.a1 = value;

	this->ProcessEvent(function, &params);
	return;
}

tarray<ashootercharacter*> blueprints::find_all_shooters_with_alliance(uobject* context, ashootercharacter* viewer, earesalliance alliance, bool only_player, bool only_alive) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.FindAllShooterCharactersWithAlliance"));

	struct
	{
		uobject* context;
		ashootercharacter* viewer;
		earesalliance alliance;
		bool only_player;
		bool only_alive;
		tarray<ashootercharacter*> output;
	} params;

	params.context = context;
	params.viewer = viewer;
	params.alliance = alliance;
	params.only_player = only_player;
	params.only_alive = only_alive;

	variables.blueprints->process_event(function, &params);

	return params.output;
}

double blueprints::GetTimeSeconds(uobject* world_context)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"Engine.GameplayStatics.GetTimeSeconds")  // Changed from GetRealTimeSeconds
		);

	struct
	{
		uobject* world_context_object;
		double Return;
	} params{};

	params.world_context_object = world_context;

	variables.blueprints->process_event(function, &params);

	return params.Return;
}

inline bool blueprints::ares_line_trace_single_by_channel(
	uobject* world_context,
	const fvector& start,
	const fvector& end,
	const tarray<uobject*>& actors_to_ignore,
	FHitResult* out_hit,
	ECollisionChannel trace_channel,
	bool trace_complex,
	bool include_moving_objects
)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"ShooterGame.ShooterBlueprintLibrary.AresLineTraceSingleByChannel")
		);

	struct
	{
		uobject* world_context_object;
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

	if (function)
		variables.blueprints->process_event(function, &params);

	if (out_hit)
		*out_hit = params.out_hit;

	return params.return_value;
}





pregame_view_model* pregame_view_controller::get_pregame_view_model() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewController.GetViewModel"));

	if (function == nullptr)
		return nullptr;

	struct 
	{
		pregame_view_model* return_value;
	} params ;

	this->process_event(function, &params);

	return params.return_value;
}

void pregame_view_controller::lock_character(uobject* agent) {
	if (agent == nullptr) return;

	uobject* function = uobject::StaticFindObject(nullptr, nullptr, crypt(L"ShooterGame.PregameViewController.LockCharacter").decrypt(), false);
	if (function == nullptr) return;

	struct {
		uobject* agent;
	} params;
	
	params.agent = agent;

	this->process_event(function, &params);
}


bool pregame_view_model::is_local_player_locked_in()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewModel.IsLocalPlayerLockedIn"));

	struct {
		bool return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;


}
void pregame_view_controller::select_character(uobject* agent) {
	if (agent == nullptr) return;
	


	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewController.SelectCharacter"));

	struct {
		uobject* agent;
	} params = { agent };

	this->process_event(function, &params);

}

void blueprints::GetWallPenetrationSpans2(UWorld2* WorldContextObject, FVector StartLocation, FVector EndLocation, TArray<AActor*>& IgnoreActors, ECollisionChannel Channel, float MinimumPlayableSpan, FWallSpanList& Spans)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetWallPenetrationSpans"));

	struct {
		UWorld2* WorldContextObject;
		FVector StartLocation;
		FVector EndLocation;
		TArray<AActor*> IgnoreActors;
		ECollisionChannel Channel;
		float MinimumPlayableSpan;
		FWallSpanList Spans;

	} params;

	params.WorldContextObject = WorldContextObject;
	params.StartLocation = StartLocation;
	params.EndLocation = EndLocation;
	params.IgnoreActors = IgnoreActors;
	params.Channel = Channel;

	params.MinimumPlayableSpan = MinimumPlayableSpan;

	variables.blueprints->ProcessEvent_(function, &params);

	Spans = params.Spans;
}







aplayercontroller* aplayercontroller::ClientForceSetControlRotation(fvector NewRotation) {
	
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ClientForceSetControlRotation").decrypt());

	struct
	{
		aplayercontroller* context;
	} params;
	
	
	this->process_event(function, &params);

	return params.context;
}


aplayercontroller* blueprints::get_local_controller(uobject* context) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetLocalController").decrypt());

	struct {
		uobject* world_context;
		aplayercontroller* return_value;
	} params = { context };

	variables.blueprints->process_event(function, &params);

	return params.return_value;
}

aplayercontroller* blueprints::get_player_controller(uobject* context)
{
	
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetFirstLocalPlayerController").decrypt());

	struct
	{
		uobject* context;
		aplayercontroller* output;
	} params;

	params.context = context;

	variables.blueprints->process_event(function, &params);

	return params.output;
}

void game_statics::get_all_actors_of_class(uobject* context, uobject* _class, tarray<gameobject*>* output) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetAllActorsOfClass").decrypt());

	struct
	{
		uobject* context;
		uobject* _class;
		tarray<gameobject*> output;
	} params;

	params.context = context;
	params._class = _class;

	variables.gameplay_statics->process_event(function, &params);

	*output = params.output;
}

bool currentequippable::HasMuzzle()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.HasMuzzle"));

	struct
	{
		bool output;
	} params;

	this->process_event(function, &params);

	return params.output;
}
ftransform currentequippable::GetMuzzleTransform()
{
	

	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMuzzleTransform"));

	struct
	{
		ftransform ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

void content_library::apply_skin(currentequippable* equippable, uobject* skin_asset, uobject* chroma_asset, int level, uobject* charm_data, int buddie_level) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ContentLibrary.ApplySkin").decrypt());

	struct
	{
		currentequippable* equippable;
		uobject* skin_asset;
		uobject* chroma_asset;
		int level;
		uobject* charm_data;
		int buddie_level;
	} params;

	params.equippable = equippable;
	params.skin_asset = skin_asset;
	params.chroma_asset = chroma_asset;
	params.level = level;
	params.charm_data = charm_data;
	params.buddie_level = buddie_level;

	variables.content_library->process_event(function, &params);
}

void content_library::clear_weapon_components(currentequippable* equippable) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ContentLibrary.ClearWeaponComponents").decrypt());

	struct
	{
		currentequippable* equippable;
	} params;

	params.equippable = equippable;

	variables.content_library->process_event(function, &params);
}

void ashootercharacter::GetActorEyesViewPoint(fvector* OutLocation, frotator* OutRotation)

{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorEyesViewPoint").decrypt());

	struct
	{
		fvector OutLocation;
		frotator OutRotation;
	} params;

	this->ProcessEvent_(function, &params);

	if (OutLocation)
		*OutLocation = params.OutLocation;
	if (OutRotation)
		*OutRotation = params.OutRotation;

}
fvector ashootercharacter::GetActorForwardVector()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorForwardVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->ProcessEvent_(function, &params);

	return params.ReturnValue;
}


void ashootercharacter::DisableInput(aplayercontroller12* PlayerController) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.DisableInput"));

	struct {
		aplayercontroller12* PlayerController;
	} params;

	params.PlayerController = PlayerController;

	this->process_event(function, &params);
}

void ashootercharacter::EnableInput(aplayercontroller12* PlayerController) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.EnableInput"));

	struct {
		aplayercontroller12* PlayerController;
	} params;

	params.PlayerController = PlayerController;

	this->process_event(function, &params);
}

FVector ashootercharacter::GetActorForwardVector2()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorForwardVector"));

	struct
	{
		FVector ReturnValue;
	} params;

	this->ProcessEvent_(function, &params);

	return params.ReturnValue;
}
fvector ashootercharacter::GetActorUpVector()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorUpVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->ProcessEvent_(function, &params);

	return params.ReturnValue;
}
void ashootercharacter::ResetCharacterMaterials_Internal(uskeletalmeshcomponent* MeshToReset)
{
	
	static uobject* Function = nullptr;

	if (!Function)
	{
		auto function_name = crypt(L"ShooterGame.ShooterCharacter.ResetCharacterMaterials").decrypt();
		Function = uobject::StaticFindObject(nullptr, nullptr, function_name, false);
	}

	if (!Function)
		return;

	struct
	{
		uskeletalmeshcomponent* MeshToReset;
	} Args;

	Args.MeshToReset = MeshToReset;
	Function->ProcessEvent(this, Function, &Args);
}


void aplayercontroller::simulate_input_key(fkey key, bool bpressed) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"AresPlayerController.SimulateInputKey").decrypt());

	struct { fkey a1; bool a2; } params{};

	params.a1 = key;
	params.a2 = bpressed;

	this->process_event(function, &params);
}

bool aplayercontroller::is_input_key_down(fkey key)
{
	
	if (!this) { return false; }

	static uobject* function;

	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"PlayerController.IsInputKeyDown").decrypt());

	struct
	{
		fkey key;
		bool return_value;
	} params = { key };

	this->process_event(function, &params);

	return params.return_value;
}

void UMaterialInstanceDynamic::set_vector_parameter_value(fname parameter_name, flinearcolor value)
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetVectorParameterValue").decrypt());

	struct {
		fname parameter_name;
		flinearcolor value;
	} params = { parameter_name , value };

	this->process_event(function, &params);
}


void UMaterialInstanceDynamic::set_vector_parameter_value2(fname parameter_name, flinearcolor value)
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetVectorParameterValue").decrypt());

	struct {
		fname parameter_name;
		int shift;
		flinearcolor value;
	} params = { parameter_name,0 , value };

	this->process_event(function, &params);
}


void uobject::set_vector_parameter_value2(fname parameter_name, flinearcolor value)
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetVectorParameterValue").decrypt());

	struct {
		fname parameter_name;
		int shift;
		flinearcolor value;
	} params = { parameter_name,0 , value };

	variables.flxxdzjosh1->process_event(function, &params);
}


void ashootercharacter::get_firing_location_and_direction(fvector* Loc, fvector* Rot, bool bApplyRecoil) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection").decrypt());

	struct
	{
		fvector location;
		fvector rotation;
		bool bapplyrecoil;
	} params;

	params.bapplyrecoil = bApplyRecoil;

	this->process_event(function, &params);

	*Loc = params.location;
	*Rot = params.rotation;
}


void ashootercharacter::get_firing_location_and_direction2(fvector* Loc, frotator* Rot, bool bApplyRecoil)
{
	

	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection").decrypt());

	struct
	{
		fvector location;
		frotator direction;  // MUST BE FRotator
		bool bapplyrecoil;
	} params;

	params.bapplyrecoil = bApplyRecoil;

	this->process_event(function, &params);

	*Loc = params.location;
	*Rot = params.direction; // correct type now
}

void UMaterialInstanceDynamic::set_scalar_parameter_value(fname parameter_name, float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetScalarParameterValue");

	struct {
		fname parameter_name;
		float value;
	} params = { parameter_name, value };

	this->process_event(function, &params);
}

void UMaterialInstanceDynamic::set_scalar_parameter_value2(fname parameter_name, float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetScalarParameterValue").decrypt());

	struct {
		fname parameter_name;
		int shift;
		float value;
	} params = { parameter_name,0,  value };

	this->process_event(function ,&params);
}


void uobject::set_scalar_parameter_value2(fname parameter_name, float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetScalarParameterValue").decrypt());

	struct {
		fname parameter_name;
		int shift;
		float value;
	} params = { parameter_name,0,  value };

	variables.flxxdzjosh1->process_event(function, &params);

}

void UMaterialInstanceDynamic::set_texture_parameter_value(fname parameter_name, uobject* texture)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetTextureParameterValue").decrypt());

	struct {
		fname parameter_name;
		uobject* value;
	} params = { parameter_name, texture };

	this->process_event(function, &params);
}


void UMaterialInstanceDynamic::set_texture_parameter_value2(fname parameter_name, uobject* texture)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetTextureParameterValue").decrypt());

	struct {
		fname parameter_name;
		int shift;
		uobject* value;
	} params = { parameter_name,0, texture };

	this->process_event(function, &params);
}

ashootercharacter* aplayercontroller::get_shooter_character() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetShooterCharacter").decrypt());

	struct
	{
		ashootercharacter* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

bool aplayercontroller::dormant_server(ashootercharacter* actor) {
	
	return memory::read<bool>(reinterpret_cast<uintptr_t>(actor) + offsets::IsDormant);
}





void aplayercontroller::disconnect_server() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.DisconnectFromServer").decrypt());

	this->process_event(function, nullptr);
}
bool aplayercontroller::line_of_sight(ashootercharacter* enemy) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.LineOfSightTo").decrypt());

	struct {
		ashootercharacter* Enemy;
		fvector ViewPoint;
		bool bAlternateCheck;
		bool ReturnValue;
	} params;
	params.Enemy = enemy;
	params.ViewPoint = fvector(0, 0, 0);
	params.bAlternateCheck = false;

	this->process_event(function, &params);
	return params.ReturnValue;
}
bool aplayercontroller::line_of_sight2(ashootercharacter* enemy, fvector target_location, aplayercameramanager* camera) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.LineOfSightTo").decrypt());

	// Get camera location - this is where we're looking FROM
	fvector camera_location = camera->get_camera_location(); // You need to access your camera

	struct {
		ashootercharacter* Enemy;
		fvector ViewPoint;      // This is the STARTING location (where to look FROM)
		bool bAlternateCheck;
		bool ReturnValue;
	} params;

	params.Enemy = enemy;
	params.ViewPoint = camera_location;  // Look FROM camera TO the enemy
	params.bAlternateCheck = false;

	this->process_event(function, &params);
	return params.ReturnValue;
}
uskeletalmeshcomponent* ashootercharacter::GetMesh1P()
{
	SPOOF_FUNC;

	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMesh1P").decrypt());

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;

	this->process_event(function, &Parameters);

	return Parameters.Out;
}

void uskeletalmeshcomponent::SetRelativeLocation(
	const fvector& NewLocation,
	bool bSweep,
	bool bTeleport
)
{
	static uobject* fn =
		uobject::find_object<uobject*>(
			crypt(L"Engine.SceneComponent.K2_SetRelativeLocation").decrypt()
		);

	if (!fn)
		return;

	struct
	{
		fvector NewLocation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.NewLocation = NewLocation;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;

	memset(&params.SweepHitResult, 0, sizeof(USceneComponentHelpers::FHitResult));

	this->process_event(fn, &params);
}

 fvector USceneComponent::GetSocketLocation(fname InSocketName) {
	


	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.GetSocketLocation").decrypt());


	struct {
		fname InSocketName;
		fvector Return;
	} Parameters;

	Parameters.InSocketName = InSocketName;

	this->ProcessEvent(function, &Parameters);

	return Parameters.Return;

}
void USceneComponent::SetRelativeLocation(
	const fvector& NewLocation,
	bool bSweep,
	bool bTeleport
)
{
	static uobject* fn =
		uobject::find_object<uobject*>(
			crypt(L"Engine.SceneComponent.K2_SetRelativeLocation").decrypt()
		);

	if (!fn)
		return;

	struct
	{
		fvector NewLocation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.NewLocation = NewLocation;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;

	memset(&params.SweepHitResult, 0, sizeof(USceneComponentHelpers::FHitResult));

	this->process_event(fn, &params);
}


void uskeletalmeshcomponent::SetRelativeRotation(frotator Target, bool bSweep, bool bTeleport)
{
	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation").decrypt());

	struct
	{
		frotator NewRotation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.NewRotation = Target;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	memset(&params.SweepHitResult, 0, sizeof(USceneComponentHelpers::FHitResult));

	if (fn)
		this->process_event(fn, &params);
}


void USceneComponent::SetRelativeRotation(frotator Target, bool bSweep, bool bTeleport)
{
	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation").decrypt());

	struct
	{
		frotator NewRotation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.NewRotation = Target;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	memset(&params.SweepHitResult, 0, sizeof(USceneComponentHelpers::FHitResult));

	if (fn)
		this->process_event(fn, &params);
}

void UProceduralMeshComponent::SetRelativeRotation1(frotator Target, bool bSweep, bool bTeleport)
{
	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation").decrypt());

	struct
	{
		frotator NewRotation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.NewRotation = Target;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	memset(&params.SweepHitResult, 0, sizeof(USceneComponentHelpers::FHitResult));

	if (fn)
		this->process_event(fn, &params);
}

void uskeletalmeshcomponent::K2_AddLocalOffset(const fvector& Location, bool bSweep , bool bTeleport )
{
	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_AddLocalOffset").decrypt());

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


	if (fn)
		this->process_event(fn, &params);
}

void uskeletalmeshcomponent::K2_AddRelativeLocation(fvector DeltaLocation, bool bSweep, bool bTeleport)
{
	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_AddRelativeLocation").decrypt());

	struct
	{
		fvector DeltaLocation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.DeltaLocation = DeltaLocation;  // <-- correct naming
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	memset(&params.SweepHitResult, 0, sizeof(USceneComponentHelpers::FHitResult));

	if (fn)
		this->process_event(fn, &params);
}


void UProceduralMeshComponent::K2_AddRelativeLocation(fvector DeltaLocation, bool bSweep, bool bTeleport)
{
	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_AddRelativeLocation").decrypt());

	struct
	{
		fvector DeltaLocation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;
		bool bTeleport;
	} params;

	params.DeltaLocation = DeltaLocation;  // <-- correct naming
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	memset(&params.SweepHitResult, 0, sizeof(USceneComponentHelpers::FHitResult));

	if (fn)
		this->process_event(fn, &params);
}

fvector uskeletalmeshcomponent::GetSocketLocation(fname InSocketName) {
	


	static uobject* function = nullptr;
	if (!function) 
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.GetSocketLocation").decrypt());


	struct {
		fname InSocketName;
		fvector Return;
	} Parameters;

	Parameters.InSocketName = InSocketName;
	
	this->ProcessEvent(function, &Parameters);

	return Parameters.Return;

	
}

uskeletalmeshcomponent* currentequippable::GetEquippableMesh() {
	

	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetEquippableMesh").decrypt());

	struct {
		uskeletalmeshcomponent* ReturnValue;
	} Parameters;
	Parameters.ReturnValue == nullptr;
	this->ProcessEvent(function, &Parameters);

	return Parameters.ReturnValue;
}
uskeletalmeshcomponent* currentequippable::GetMesh1P()
{
	

	static uobject* function = nullptr;
	if (!function) {
		// Silah meshi için dogru Unreal yolu budur
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh1P").decrypt());
	}

	if (!function || !this) return nullptr;

	struct {
		uskeletalmeshcomponent* ReturnValue;
	} Parameters;

	Parameters.ReturnValue = nullptr;

	// 'this' silahin kendisi oldugu için ProcessEvent artik crash atmayacak
	this->process_event(function, &Parameters);

	return Parameters.ReturnValue;
}


void aplayercontroller::AddPitchInput(float Val)
{
	

	static uobject* Function = nullptr;
	if (!Function)
	{
		Function = uobject::StaticFindObject(
			nullptr,
			nullptr,
			crypt(L"Engine.PlayerController.AddPitchInput").decrypt(),
			false
		);
	}

	if (!Function)
		return;

	struct
	{
		float Val;
	} Parameters;

	Parameters.Val = Val;

	this->process_event(Function, &Parameters);
}

void aplayercontroller::AddYawInput(float Val)
{
	

	static uobject* Function = nullptr;
	if (!Function)
	{
		Function = uobject::StaticFindObject(
			nullptr,
			nullptr,
			crypt(L"Engine.PlayerController.AddYawInput").decrypt(),
			false
		);
	}

	if (!Function)
		return;

	struct
	{
		float Val;
	} Parameters;

	Parameters.Val = Val;

	this->process_event(Function, &Parameters);
}


void aplayercontroller::GetInputMouseDelta(float& DeltaX, float& DeltaY)
{
	
	uobject* Function = uobject::StaticFindObject(nullptr, nullptr, crypt(L"Engine.PlayerController.GetInputMouseDelta").decrypt(), false);

	if (!Function)
	{
		return;
	}
	struct
	{
		float DeltaX;
		float DeltaY;
	}Parameters;
	Function->ProcessEvent(this, Function, &Parameters);
	DeltaX = Parameters.DeltaX;
	DeltaY = Parameters.DeltaY;
}
void aplayercontroller::UnlockFOV() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.UnlockFOV").decrypt());

	if (function)
		this->process_event(function, nullptr);
}

bool aplayercontroller::get_mouse_position(float* locationx, float* locationy)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.GetMousePosition").decrypt());

	struct { float a1; float a2; bool ret; } params{};
	this->process_event(function, &params);

	*locationx = params.a1;
	*locationy = params.a2;
	return params.ret;
}




void uskeletalmeshcomponent::set_world_rotation(fvector NewRotation, bool bsweep, bool bteleport)
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetWorldRotation").decrypt());

	struct {
		fvector NewRotation;
		bool bsweep;
		uintptr_t FHitResult;
		bool bTeleport;
	} params = { NewRotation, bsweep, 0, bteleport };

	this->ProcessEvent(function, &params);
}



void ashootercharacter::relative_rotation(fvector NewRelativeRotation, bool bSweep, bool bTeleport)
{
	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRelativeRotation").decrypt());

	if (function == nullptr)
		return;

	struct
	{
		fvector NewRelativeRotation;
		bool bSweep;
		char* gay;
		bool bTeleport;

	} params;



	params.NewRelativeRotation = NewRelativeRotation;
	params.bSweep = bSweep;
	char buf[500];
	params.gay = buf;
	params.bTeleport = bTeleport;

	this->process_event(function, &params);
}

void ashootercharacter::K2_SetActorRelativeRotationnigger(FRotator NewRelativeRotation, bool bSweep, bool bTeleport)
{
	
	static uobject* Function;
	if (!Function) 
			Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRelativeRotation").decrypt());

	struct
	{
	    FRotator NewRelativeRotation;
		bool bSweep;
		USceneComponentHelpers::FHitResult SweepHitResult;

		bool bTeleport;
	}Parameters;

	Parameters.NewRelativeRotation = NewRelativeRotation;
	Parameters.bSweep = bSweep;
	Parameters.bTeleport = bTeleport;

	this->process_event(Function, &Parameters);
}


bool ashootercharacter::GetTrueDisplayName()
{
	
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PlatformPlayer.GetTrueDisplayName").decrypt());

	struct
	{
		fstring* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}


 bool uskeletalmeshcomponent::AttachTo( uskeletalmeshcomponent* Parent, fname SocketName,
	int LocationRule, int RotationRule, int ScaleRule, bool bWeldSimulatedBodies)
{
	static uobject* Function = uobject::find_object< uobject* >(crypt(L"Engine.SceneComponent.K2_AttachToComponent").decrypt());

	struct
	{
		uskeletalmeshcomponent* Parent;
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

	if (Function )
		this->process_event(Function, &params);

	return params.ReturnValue;
}

void uskeletalmeshcomponent::set_relative_rotation(FRotator NewRotation)
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation").decrypt());

	struct {
		FRotator NewRotation;
		bool bSweep;
		bool bTeleport;
	}Args;
	Args.NewRotation = NewRotation;
	Args.bSweep = true;
	Args.bTeleport = false;
	this->process_event(function, &Args);
}


void uskeletalmeshcomponent::SetSkinnedAssetAndUpdate(uobject* NewMesh, bool bReinitPose)
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.SkinnedMeshComponent.SetSkinnedAssetAndUpdate").decrypt());

	struct {
		uobject* newmesh;
		bool bReinitPose;
	
	}Args;
	
	Args.newmesh = NewMesh;
	Args.bReinitPose = bReinitPose;
	this->process_event(function, &Args);

}

void uskeletalmeshcomponent::set_relative_rotation1(frotator NewRotation, bool bSweep, bool bTeleport)
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation").decrypt());

	struct {
		frotator NewRotation;
		bool bSweep;
		bool bTeleport;
	} Args;

	Args.NewRotation = NewRotation;
	Args.bSweep = bSweep;
	Args.bTeleport = bTeleport;

	this->process_event(function, &Args);
}

uskeletalmeshcomponent* currentequippable::GetMesh3P()
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh3P").decrypt());

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	function->ProcessEvent(this, function, &Parameters);
	return Parameters.Out;
}


fvector2d aplayercontroller::project_world_to_screen(fvector world) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen").decrypt());

	struct
	{
		fvector world;
		fvector2d screen;
		bool relative_viewport;
	} params;

	params.world = world;
	params.relative_viewport = true;

	this->process_event(function, &params);
	return params.screen;
}


bool aplayercontroller12::project_world_location_to_screen12(fvector world_location, fvector2d& screen_location, bool player_viewport_relative) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen"));

	struct {
		fvector world_location;
		fvector2d screen_location;
		bool player_viewport_relativee;
		bool return_value;
	} params;
	params.world_location = world_location;
	params.player_viewport_relativee = player_viewport_relative;

	this->process_event(function, &params);
	screen_location = params.screen_location;

	return params.return_value;
}

bool aplayercontroller::project_world_location_to_screen(fvector world_location, fvector2d& screen_location, bool player_viewport_relative) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen").decrypt());

	struct {
		fvector world_location;
		fvector2d screen_location;
		bool player_viewport_relativee;
		bool return_value;
	} params;
	params.world_location = world_location;
	params.player_viewport_relativee = player_viewport_relative;

	this->process_event(function, &params);
	screen_location = params.screen_location;

	return params.return_value;
}
bool aplayercontroller::project_world_location_to_screen2(FVector world_location, FVector2D& screen_location, bool player_viewport_relative) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen").decrypt());

	struct {
		FVector world_location;
		FVector2D screen_location;
		bool player_viewport_relativee;
		bool return_value;
	} params;
	params.world_location = world_location;
	params.player_viewport_relativee = player_viewport_relative;

	this->process_event(function, &params);
	screen_location = params.screen_location;

	return params.return_value;
}


void aplayercontroller::SetClientRotation(frotator Rotation)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.ClientSetRotation").decrypt());

	struct
	{
		frotator newRotation;
		bool bResetCamera;
	}Parameters;

	Parameters.newRotation = Rotation;
	Parameters.bResetCamera = false;


	this->process_event(function, &Parameters);
}


void aplayercontroller::GetPlayerViewPoint(fvector Location, frotator Rotation)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetPlayerViewPoint").decrypt());

	struct
	{
		fvector newRotation;
		frotator bResetCamera;
	}Parameters;

	Parameters.newRotation = Location;
	Parameters.bResetCamera = Rotation;


	this->process_event(function, &Parameters);
}

fvector aplayercontroller::get_control_rotation()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation").decrypt());

	struct
	{
		fvector Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

frotator aplayercontroller::get_control_rotation2()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation").decrypt());

	struct
	{
		frotator Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

fvector acknowledgedpawn::GetControlRotation()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Pawn.GetControlRotation").decrypt());

	struct
	{
		fvector Out;
	}Args;
	function->ProcessEvent(this, &Args);
	return Args.Out;

}
fvector acknowledgedpawn::get_control_rotation_meow() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlLotation").decrypt());

	struct
	{
		fvector Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

float aplayercontroller::GetMouseSensitivity()
{
	
	uobject* Function = uobject::StaticFindObject(nullptr, nullptr, crypt(L"ShooterGame.ShooterPlayerController.GetMouseSensitivity").decrypt(), false);

	if (!Function)
	{
		return 0;
	}
	struct
	{
		float Out;
	}Parameters;
	Function->ProcessEvent(this, Function, &Parameters);
	return Parameters.Out;
}


void aplayercontroller::set_control_rotation(fvector angle) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetControlRotation").decrypt());

	struct
	{
		fvector angle;
	} params;

	params.angle = angle;

	this->process_event(function, &params);
}


void aplayercontroller::set_control_rotationfrotator(frotator angle) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetControlRotation").decrypt());

	struct
	{
		frotator angle;
	} params;

	params.angle = angle;

	this->process_event(function, &params);
}

ashootercharacter* aplayercontroller::GetFirstPersonCharacter() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetControlRotation").decrypt());

	struct
	{
		ashootercharacter* angle;
	} params;


	this->process_event(function, &params);
	return params.angle;
}



fvector AGameObject::GetObjectLocation()
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorLocation").decrypt());

	struct {
		fvector Out;
	}Args;

	this->process_event(function, &Args);

	return Args.Out;
}

float AGameObject::GetObjectHealh()
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject.GetHealth").decrypt());

	struct {
		float Out;
	}Args;
	this->process_event(function, &Args);

	return Args.Out;
}


uobject* Class::ShooterGameObject()
{
	
	return  uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject"));
}

uobject* GameplayStatics::GameplayStatics()
{
	
	return  uobject::find_object<uobject*>(crypt(L"Engine.Default__GameplayStatics"));
}

uobject* GameplayStatics::get_game_instancee(uworld* world_context)
{
	
	static uobject* function;
	if( !function )
		function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetGameInstance"));

	struct {
		uworld* world_context;
		uobject* return_value;
	} params = { world_context };

	variables.gameplay_statics->process_event(function, &params);
	return params.return_value;
}

static inline uobject* GameplayStatics::get_game_instance(uworld* world_context)
{
	
	auto function_name = crypt(L"Engine.GameplayStatics.GetGameInstance");
	static uobject* Function = nullptr;

	if (!Function)
		Function = uobject::StaticFindObject(nullptr, nullptr, function_name.decrypt(), false);

	struct {
		uworld* world_context;
		uobject* return_value;
	} params = { world_context };

	Function->ProcessEvent(GameplayStatics(), &params);
	return params.return_value;
}

uskeletalmeshcomponent* ashootercharacter::get_mesh() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetPawnMesh"));

	struct
	{
		uskeletalmeshcomponent* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}


uinventory* ashootercharacter::get_inventory() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetInventory"));

	struct
	{
		uinventory* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}


UPhysicalMaterial* UMaterialInterface::GetPhysicalMaterial() {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"MaterialInterface.GetPhysicalMaterial").decrypt());

	struct {
		UPhysicalMaterial* ReturnValue;
	} Params = {  };

	this->process_event(function, &Params);

	return Params.ReturnValue;
}



e_blend_mode UMaterialInterface::GetBlendMode() {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"MaterialInterface.GetBlendMode").decrypt());

	struct {
		e_blend_mode ReturnValue;
	} Params = {  };

	this->process_event(function, &Params);

	return Params.ReturnValue;
}
int32_t ashootercharacter::GetLocalRole()
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetLocalRole").decrypt());

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(Function, &params);

	return params.ReturnValue;
}

USceneComponent* ashootercharacter::K2_GetRootComponent()
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetRootComponent"));
	if (!Function)
	{
		return nullptr;
	}
	struct
	{
		USceneComponent* ReturnValue;
	} Parameters;
	Parameters.ReturnValue = nullptr;
	this->process_event35(Function, &Parameters);
	return Parameters.ReturnValue;
}


fvector ashootercharacter::GetActorRightVector()
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorRightVector").decrypt());

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(Function, &params);

	return params.ReturnValue;
}

frotator ashootercharacter::K2_GetActorRotation()
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorRotation").decrypt());
	struct
	{
		frotator Out;
	}Parameters;

	this->process_event(function, &Parameters);
	return Parameters.Out;
}

FRotator ashootercharacter::K2_SetActorRotation(FRotator negrito, bool bTeleportPhysics)
{
	
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRotation").decrypt());
	struct
	{
		FRotator Out;
		bool bTeleportPhysics;
	}Parameters;

	this->process_event(function, &Parameters);
	return Parameters.Out;
}





void UMaterialInstanceDynamic::SetVectorParameterValue(fname ParameterName, flinearcolor Value) {
	uobject* Function = uobject::find_object<uobject*>(crypt(L"MaterialInstanceDynamic.SetVectorParameterValue").decrypt());

	struct {
		fname ParameterName;
		flinearcolor Value;
	} Params = { ParameterName, Value };

	this->ProcessEvent(Function, &Params);
}

currentequippable* uinventory::get_current_equippable()
{
	
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresInventory.GetCurrentEquippable").decrypt());

	struct
	{
		currentequippable* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

fvector ashootercharacter::k2_get_actor_location()
{
	
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorLocation").decrypt());

	struct
	{
		fvector Out;
	} params;
	this->process_event(function, &params);

	return params.Out;
}



EAresItemSlot acknowledgedpawn::GetItemSlot() {
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresItem.GetItemSlot"));

	if (!function || !memory::is_valid((uintptr_t)function) || !memory::is_valid((uintptr_t)function))
		return EAresItemSlot::EAresItemSlot_MAX;

	struct
	{
		EAresItemSlot output;
	} params;


	this->process_event(function, &params);


	return params.output;
}
fvector acknowledgedpawn::k2_get_pawn_location()
{
	


	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Pawn.K2_GetActorLocation").decrypt());

	struct
	{
		fvector Out;
	} params;
	this->process_event(function, &params);

	return params.Out;
}

frotator ashootercharacter::get_view_rotation_with_full_recoil() {
	frotator return_value;
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetViewRotationFullRecoil").decrypt());
	this->process_event(function, &return_value);

	return return_value;
}
uobject* ashootercharacter::get_character_icon()
{
	
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCharacterIcon").decrypt());

	struct
	{
		uobject* Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}

bool ashootercharacter::is_alive() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsAlive").decrypt());

	struct
	{
		bool output;
	} params;

	this->process_event(function, &params);

	return params.output;
}



bool ashootercharacter::is3pEnabled() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.Is3PCameraEnabled").decrypt());

	struct
	{
		bool output;
	} params;

	this->process_event(function, &params);

	return params.output;
}




bool ashootercharacter::IsPlayerCharacter() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsPlayerCharacter").decrypt());

	struct
	{
		bool output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

bool ashootercharacter::IsZoomed() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsZoomed").decrypt());

	struct
	{
		bool returnvalue;
	} params;

	this->process_event(function, &params);

	return params.returnvalue;
}

bool ashootercharacter::is_dead_and_settled() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsDeadAndSettled").decrypt());

	struct
	{
		bool Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}

bool ashootercharacter::was_invisible() {
	
	return memory::read<bool>(class_ptr + offsets::was_invisible);
}

float ashootercharacter::health() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetHealth").decrypt());

	struct
	{
		float output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

float ashootercharacter::shield() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetShield").decrypt());

	struct
	{
		float output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

player_state* ashootercharacter::get_player_state() {
	
	return memory::read<player_state*>(class_ptr + offsets::PlayerState);
}

int32_t PlatformPlayer::GetCompetitiveTier() {
	static uobject* functon;
	if (!functon)
		functon = uobject::find_object<uobject*>(crypt(L"ShooterGame.PlatformPlayer.GetCompetitiveTier").decrypt());

	struct
	{
		int32_t output;
	} params;

	this->process_event(functon, &params);
	return params.output;
}

PlatformPlayer* player_state::getplayerformplayer() {
	
	return memory::read<PlatformPlayer*>(class_ptr + offsets::PlatformPlayer);
}


tarray<player_state*> player_state::get_players_spectating() {
	if (!this) return {};

	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.GetPlayersSpectating").decrypt());

	struct {
		bool omit_coaches;
		tarray<player_state*> return_value;
	} params = { false };

	this->process_event(fn, &params);
	return params.return_value;
}

fvector uskeletalmeshcomponent::get_bone_location(int32_t index) {
	
	fmatrix matrix;
	auto negritas = memory::module_base + offsets::bone_matrix;
	reinterpret_cast<fmatrix* (__fastcall*)(void*, fmatrix*, int, uintptr_t, void*)>(spoofcall_stub)(this, &matrix, index, offsets::MagicOffsets, (void*)negritas);
	return { matrix.wplane.x, matrix.wplane.y, matrix.wplane.z };
}


FVector uskeletalmeshcomponent::get_bone_location35(int32_t index) {
	
	FMatrix2 matrix;

	auto negritas = memory::module_base + offsets::bone_matrix;
	reinterpret_cast<FMatrix2* (__fastcall*)(void*, FMatrix2*, int, uintptr_t, void*)>(spoofcall_stub)(this, &matrix, index, offsets::MagicOffsets, (void*)negritas);
	return { matrix.WPlane.X, matrix.WPlane.Y, matrix.WPlane.Z };
}



int32_t uskeletalmeshcomponent::GetBoneIndex(fname BoneName) {

	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"Engine.SkinnedMeshComponent.GetBoneIndex").decrypt()
		);

	struct
	{
		fname BoneName;
		int32_t ReturnValue;
	} params;

	params.BoneName = BoneName;


	this->process_event(function, &params);


	return params.ReturnValue;
	
}

fname uskeletalmeshcomponent::GetBoneName(int32_t BoneName) {

	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"Engine.SkinnedMeshComponent.GetBoneName").decrypt()
		);

	struct
	{
		int32_t BoneName;
		fname ReturnValue;
	} params;

	params.BoneName = BoneName;


	this->process_event(function, &params);


	return params.ReturnValue;
	
}


uobject* uengine::font() {
	
	return memory::read<ugameinstance*>(class_ptr + offsets::font);
}

uengine* ugameinstance::get_uengine() {
	
	return memory::read<uengine*>(class_ptr + offsets::Engine);
}
UAresClientGameInstance* UAresClientGameInstance::GetAresClientGameInstance(uobject* WorldContextObject)
{
	

	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"ShooterGame.AresClientGameInstance.GetAresClientGameInstance").decrypt()
		);

	struct
	{
		uobject* WorldContextObject;
		UAresClientGameInstance* ReturnValue;
	} params;

	params.WorldContextObject = WorldContextObject;

	// Call ProcessEvent on the default object (CDO)
	variables.AresClient->process_event(function, &params);

	return params.ReturnValue;
}



UThreadedChatManager* ares_client_game_instace::GetThreadedChatManager()
{
	

	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(
			crypt(L"ShooterGame.AresClientGameInstance.GetThreadedChatManager").decrypt()
		);


	struct
	{
		UThreadedChatManager* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}



UThreadedChatManager* UThreadedChatManager::GetThreadedChatManager(uobject* world_context) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ThreadedChatManager.GetThreadedChatManager").decrypt());

	struct {
		uobject* world_context;
		UThreadedChatManager* return_value;
	} params;

	params.world_context = world_context;

	GetDefaultObj()->process_event(function, &params);

	return params.return_value;
}

void UThreadedChatManager::send_chat_message_v2(EChatRoomType room_type, ftext message) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ThreadedChatManager.SendChatMessageV2").decrypt());

	struct {
		EChatRoomType room_type;
		ftext message;
	} params;

	params.room_type = room_type;
	params.message = message;

	this->process_event(function, &params);
}


inline float math::vector_size(const fvector& value) {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.VSize").decrypt());

	struct {
		fvector value;
		double return_value;
	} params = { value };

	variables.math_system->process_event(function, &params);

	return params.return_value;
}

double math::distance_2d(fvector2d v1, fvector2d v2)
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Distance2D").decrypt());

	struct
	{
		fvector2d v1;
		fvector2d v2;
		double output;
	} params;

	params.v1 = v1;
	params.v2 = v2;

	variables.math_system->process_event(function, &params);
	return params.output;
}



uobject* KismetMathLibrary::KismetMathLibrary() {
	
	return uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetMathLibrary").decrypt());
}
fvector KismetMathLibrary::FindLookAtRotation(fvector start, fvector target) {
	
	uobject* function_name;
	if (!function_name)
		function_name = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetMathLibrary").decrypt());

	struct {
		fvector start;
		fvector target;
		fvector out;
	} Args;

	Args.start = start;
	Args.target = target;
	variables.math_system->process_event(function_name, &Args);
	return Args.out;
}
fvector math::mirror_vector_by_normal(fvector in_vect, fvector in_normal)
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.MirrorVectorByNormal").decrypt());

	struct {
		fvector in_vect;
		fvector in_normal;
		fvector return_value;
	} params = { in_vect, in_normal };

	variables.math_system->process_event(function, &params);

	return params.return_value;
}
frotator math::find_look_at_rotation(const fvector& start, const fvector& end)
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.FindLookAtRotation").decrypt());

	struct
	{
		fvector start;
		fvector end;
		frotator output;
	} params;

	params.start = start;
	params.end = end;

	variables.math_system->process_event(function, &params);
	return params.output;
}



fvector aplayercameramanager::get_camera_location()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraLocation").decrypt());

	struct
	{
		fvector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}


FVector aplayercameramanager::get_camera_location2()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraLocation").decrypt());

	struct
	{
		FVector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}


uobject* AresOutlineRendering::Static_Class()
{
	
	
	return uobject::find_object<uobject*>(crypt(L"Renderer.Default__AresOutlineRendering").decrypt());
}

void AresOutlineRendering::SetOutlineColorsForRender(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor)
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender").decrypt());

	struct {
		uobject* WorldContextObject;
		flinearcolor AllyColor;
		flinearcolor EnemyColor;
	}Parameters;
	Parameters.WorldContextObject = WorldContextObject;
	Parameters.AllyColor = AllyColor;
	Parameters.EnemyColor = EnemyColor;
	function->ProcessEvent(Static_Class(), function, &Parameters);

}

struct USkeletalMeshComponentRE
{


};


fvector aplayercameramanager::get_camera_rotation()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraRotation").decrypt());

	struct
	{
		fvector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}


frotator aplayercameramanager::get_camera_rotation3()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraRotation").decrypt());

	struct
	{
		frotator output;
	} params;

	this->process_event(function, &params);
	return params.output;
}




FVector aplayercameramanager::get_camera_rotation2()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraRotation").decrypt());

	struct
	{
		FVector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

float aplayercameramanager::GetFOVAngle1P() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetFOVAngle1P").decrypt());

	struct
	{
		float output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

aplayercameramanager* aplayercontroller::get_camera_manager() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetPlayerCameraManager").decrypt());

	struct
	{
		aplayercameramanager* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

void aplayercontroller::HandleThreadedChatManagerSentInGameMessage(fstring Msg, EChatMode ChatMode) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.HandleThreadedChatManagerSentInGameMessage").decrypt());

	struct
	{
		fstring Msg;
		EChatMode ChatMode;
	} params;

	params.Msg = Msg;
	params.ChatMode = ChatMode;
	this->process_event(function, &params);

}

uobject* IhateNigger::Static_Class()
{
	
	return uobject::StaticFindObject(nullptr, nullptr, crypt(L"ShooterGame.Default__BaseTeamComponent").decrypt(), false);
}
void ucameracomponent::SetFieldOfView(float fov) {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.CameraComponent.SetFieldOfView").decrypt());

	struct {
		float fov;
	}Args;
	Args.fov = fov;
	this->process_event(function, &Args);
}

void aplayercontroller::set_fov(float fov) {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.SetFOV").decrypt());

	struct {
		float fov;
	}Args;
	Args.fov = fov;
	this->process_event(function, &Args);
}
acknowledgedpawn* aplayercontroller::get_acknowledged_pawn() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.K2_GetPawn").decrypt());

	struct
	{
		acknowledgedpawn* output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

ashootercharacter* aplayercontroller::K2_GetPawn_Local()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.K2_GetPawn").decrypt());

	if (!function) { return nullptr; }

	struct {
		ashootercharacter* Out;
	} Args;
	this->process_event(function, &Args);
	return Args.Out;
}



fstring player_state::get_player_name() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerState.GetPlayerName").decrypt());

	struct
	{
		fstring output;
	} params;

	this->process_event(function, &params);

	return params.output;
}



void ashootercharacter::SetCrouchTimeOverride(float Override) {
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.SetCrouchTimeOverride").decrypt());

	struct {
		float Override;
	}Args;
	Args.Override = Override;
	function->ProcessEvent(this, function, &Args);
}




bool ashootercharacter::CanJump()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Character.CanJump").decrypt());

	struct { bool ret; } params;

	this->process_event(function, &params);
	return params.ret;
}



currentequippable* inventorymanager::get_current_weapon() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresInventory.GetCurrentEquippable").decrypt());

	struct
	{
		currentequippable* out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

equippable_skin_data_asset* currentequippable::get_skin_data_asset() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetEquippableSkinDataAsset").decrypt());

	struct {
		equippable_skin_data_asset* Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}
bool math::ClassIsChildOf(uobject* TestClass, uobject* ParentClass)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.ClassIsChildOf").decrypt());

	struct
	{
		uobject* min;
		uobject* max;
		bool output;
	} params = { TestClass, ParentClass };


	variables.math_system->process_event(function, &params);
	return params.output;


	
}

int32_t math::random_int(int32_t min, int32_t max) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.RandomIntegerInRange").decrypt());

	struct
	{
		int32_t min;
		int32_t max;
		int32_t output;
	} params = { min, max };


	variables.math_system->process_event(function, &params);
	return params.output;
}
double math::random_float(double min, double max) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.RandomFloatInRange").decrypt());

	struct
	{
		double min;
		double max;
		double output;
	} params = { min, max };

	variables.math_system->process_event(function, &params);
	return params.output;
}
frotator math::RInterpTo_Constant(frotator Current, frotator Target, float DeltaTime, float InterpSpeed)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.RInterpTo_Constant").decrypt());

	struct
	{
		frotator Current;
		frotator Target;
		float DeltaTime;
		float InterpSpeed;
		frotator out;
	}Args = { Current, Target, DeltaTime, InterpSpeed };

	variables.math_system->process_event(function, &Args);

	return Args.out;

}

fvector2d ucanvas::get_screen_size() {
	
	return fvector2d(memory::read<int32_t>(class_ptr + offsets::ScreenSize1), memory::read<int32_t>(class_ptr + offsets::ScreenSize2));
}


fvector2d ucanvas::get_screen_size2() {
	
	return fvector2d(memory::read<int32_t>(class_ptr + offsets::ScreenSize1), memory::read<int32_t>(class_ptr + offsets::ScreenSize2));

}
fvector ucanvas::k2_project(fvector WorldLocation)
{
	

	static uobject* fn = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_Project").decrypt());

	struct {
		fvector WorldLocation;
		fvector return_value;
	} params;

	params.WorldLocation = WorldLocation;

	static uintptr_t process_event_addr = memory::module_base + offsets::process_event;

	reinterpret_cast<void(*)(void*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(
		this, fn, &params, offsets::MagicOffsets, (void*)process_event_addr
		);

	return params.return_value;
}
void ucanvas::k2_drawline(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color) {
	
	static uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawLine").decrypt());
	struct
	{
		fvector2d screenpos_a;
		fvector2d screenpos_b;
		float thickness;
		flinearcolor color;
	} params;

	params.screenpos_a = screenpos_a;
	params.screenpos_b = screenpos_b;
	params.thickness = thickness;
	params.color = color;

	this->process_event(function, &params);
}
void ucanvas::k2_drawtransparentline(const fvector2d& screen_position_a, const fvector2d& screen_position_b, float thickness, const flinearcolor& render_color) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawTransparentLine"));

	struct {
		fvector2d ScreenPositionA;
		fvector2d ScreenPositionB;
		float Thickness;
		flinearcolor RenderColor;
	} params;

	params.ScreenPositionA = screen_position_a;
	params.ScreenPositionB = screen_position_b;
	params.Thickness = thickness;
	params.RenderColor = render_color;

	this->process_event(function, &params);
}
void ucanvas::k2_drawline3(FVector2D screenpos_a, FVector2D screenpos_b, float thickness, flinearcolor color) {
	
	static uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawLine").decrypt());
	struct
	{
		FVector2D screenpos_a;
		FVector2D screenpos_b;
		float thickness;
		flinearcolor color;
	} params;

	params.screenpos_a = screenpos_a;
	params.screenpos_b = screenpos_b;
	params.thickness = thickness;
	params.color = color;

	this->process_event(function, &params);

}
void ucanvas::k2_drawtexture(uobject* texture, fvector2d screen_position, fvector2d screen_size, fvector2d coordinate_position, fvector2d coordinate_size, flinearcolor render_color, e_blend_mode blend_mode, float rotation, fvector2d pivot_point)
{
	

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawTexture").decrypt());

	struct {
		uobject* texture;
		fvector2d screen_position;
		fvector2d screen_size;
		fvector2d coordinate_position;
		fvector2d coordinate_size;
		flinearcolor render_color;
		e_blend_mode blend_mode;
		float rotation;
		fvector2d pivot_point;
	} params;
	params.texture = texture;
	params.screen_position = screen_position;
	params.screen_size = screen_size;
	params.coordinate_position = coordinate_position;
	params.coordinate_size = coordinate_size;
	params.render_color = render_color;
	params.blend_mode = blend_mode;
	params.rotation = rotation;
	params.pivot_point = pivot_point;

	this->process_event(function, &params);
}
void ucanvas::k2_drawline2(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color)
{
	

	static uintptr_t fn_address = memory::module_base + 0x396D2A9;

	return reinterpret_cast<void(*)(fvector2d, fvector2d, float, flinearcolor, uintptr_t, void*)>(spoofcall_stub)(
		screenpos_a, screenpos_b, thickness, color, offsets::MagicOffsets, (void*)(fn_address)
		);

}





void ucanvas::k2_drawtext(uobject* font, fstring text, fvector2d screenposition, fvector2d scale, flinearcolor color, float kerning, flinearcolor shadowcolor, fvector2d shadowoffset, bool centrex, bool centrey, bool outline, flinearcolor outlinecolor)
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawText").decrypt());

	struct
	{
		uobject* font;
		fstring text;
		fvector2d screenposition;
		fvector2d scale;
		flinearcolor color;
		float kerning;
		flinearcolor shadowcolor;
		fvector2d shadowoffset;
		bool centrex;
		bool centrey;
		bool outline;
		flinearcolor outlinecolor;
	} params;

	params.font = font;
	params.text = text;
	params.screenposition = screenposition;
	params.scale = scale;
	params.color = color;
	params.kerning = kerning;
	params.shadowcolor = shadowcolor;
	params.shadowoffset = shadowoffset;
	params.centrex = centrex;
	params.centrey = centrey;
	params.outline = outline;
	params.outlinecolor = outlinecolor;

	this->process_event(function, &params);
}


ares_client_game_instace* ares_instance::get_ares_client_game_instance(uobject* world_context) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetAresClientGameInstance").decrypt());

	struct {
		uobject* uworld;
		ares_client_game_instace* return_value;
	} params = { world_context };

	variables.ares_instance->process_event(function, &params);

	return params.return_value;
}
inventorymanager* ares_client_game_instace::get_inventory_manager() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetInventoryManager").decrypt());

	struct {
		inventorymanager* out;
	} result;


	this->process_event(function, &result);
	return result.out;
}

arsenal_view_controller* ares_client_game_instace::get_aresnal_view_controller() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetArsenalViewController").decrypt());

	struct {
		arsenal_view_controller* out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

equippable_skin_inventory_model* equippable_inventory_model::get_equipped_skin_model() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableInventoryModel.GetEquippedSkin").decrypt());

	struct {
		equippable_skin_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;

}

equippable_charm_instance_inventory_model* equippable_inventory_model::get_equipped_charm_instance() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableInventoryModel.GetEquippedCharmInstance").decrypt());

	struct {
		equippable_charm_instance_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

tarray<equippable_inventory_model*> arsenal_view_model::get_gun_models() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewModel.GetGunModels").decrypt());

	struct {
		tarray<equippable_inventory_model*> out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

arsenal_view_model* arsenal_view_controller::get_view_model() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.GetViewModel").decrypt());

	struct {
		arsenal_view_model* out;
	} params;
	this->process_event(function, &params);
	return params.out;
}

equippable_skin_chroma_inventory_model* equippable_skin_inventory_model::get_skin_inventory_chroma_asset() {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableSkinInventoryModel.GetEquippedChroma").decrypt());

	struct {
		equippable_skin_chroma_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}


bool IhateNigger::IsAlly(ashootercharacter* Enemy, ashootercharacter* Self)
{
	

	uobject* Function = uobject::StaticFindObject(nullptr, nullptr, crypt(L"ShooterGame.BaseTeamComponent.IsAlly").decrypt(), false);
	struct {
		ashootercharacter* Enemy;
		ashootercharacter* Self;
		bool ReturnValue;
	}Parameters;
	Parameters.Enemy = Enemy;
	Parameters.Self = Self;
	Function->ProcessEvent(Static_Class(), Function, &Parameters);
	return Parameters.ReturnValue;
}

bool basecomponent::is_ally(ashootercharacter* enemy, ashootercharacter* self) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.BaseTeamComponent.IsAlly").decrypt());

	struct {
		ashootercharacter* enemy;
		ashootercharacter* self;
		bool return_value;
	} params;

	variables.base_component->process_event(function, &params);
	return params.return_value;
}


void skin_changer::unlock_all_apply(uobject* world, currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset) {
	
	auto ares_client_game_instance = ares_instance::get_ares_client_game_instance(world);
	auto a1 = memory::read2<uintptr_t>((uintptr_t)ares_client_game_instance + offsets::skin_pointer);
	inventorymanager* manager = ares_instance::get_ares_client_game_instance(world)->get_inventory_manager();

	if (a1) {

		a1 = memory::read2<uintptr_t>(a1 + offsets::skin_pointer_2);
		if (a1) {
		


			auto old_value = memory::read2<int>(a1 + offsets::skin_pointer_3);
			memory::write<int>(a1 + offsets::skin_pointer_3, 2);


			if (globals::buddy::enabled) {
				inventorymanager* manager = SPOOF_CALL(ares_instance::get_ares_client_game_instance)(world)->get_inventory_manager();
				auto charm_instances = memory::read2<tarray<tmap<uobject*, uobject*>>>(std::uintptr_t(manager) + 0x430);
				buddy = charm_instances[globals::buddy::index].Key;
				BuddyName = system::get_object_name(buddy);
				BuddyNameYAY = BuddyName.wide();

				content_library::clear_weapon_components(current_equippable);
				content_library::apply_skin(current_equippable, skin_data_asset, skin_chroma_asset, max_level, buddy, 1);
				memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
			}
			else {
				content_library::clear_weapon_components(current_equippable);
				content_library::apply_skin(current_equippable, skin_data_asset, skin_chroma_asset, max_level, nullptr, -1);
				memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
			}
		
		}
	}
}



void skin_changer::unlock_all_skins(uobject* world) {
	

	if (inventorymanager* manager = ares_instance::get_ares_client_game_instance(world)->get_inventory_manager()) {
		tarray<uobject*> equippable_models = memory::read2<tarray<uobject*>>(std::uintptr_t(manager) + offsets::EquippableModels);

		if (globals::misc::skin_changer) {
			for (int i = 0; i < equippable_models.size(); i++) {
				if (auto model = equippable_models[i]) {
					tarray<uobject*> skins = memory::read2<tarray<uobject*>>(std::uintptr_t(model) + offsets::PossibleSkins);

					if (skins.size() > 0) {
						for (int a = 0; a < skins.size(); a++) {
							if (auto skin = skins[a]) {
							
								tarray<uobject*> possible_levels = memory::read2<tarray<uobject*>>(
									std::uintptr_t(skin) + offsets::PossibleLevels
								);
								for (int b = 0; b < possible_levels.size(); b++) {
									if (uobject* xyz = possible_levels[b]) {
										memory::write<bool>(std::uintptr_t(xyz) + offsets::bIsUnlockedByConfig, true);
										memory::write<bool>(std::uintptr_t(xyz) + offsets::bIsOwned, true);
									}
								}

								tarray<uobject*> possible_chromas = memory::read2<tarray<uobject*>>(
									std::uintptr_t(skin) + offsets::PossibleChromas
								);
								for (int c = 0; c < possible_chromas.size(); c++) {
									if (uobject* xyz = possible_chromas[c]) {
										memory::write<bool>(std::uintptr_t(xyz) + offsets::bIsUnlockedByConfig, true);
										memory::write<bool>(std::uintptr_t(xyz) + offsets::bIsOwned, true);
									}
								}

								memory::write<bool>(std::uintptr_t(skin) + offsets::bIsUnlockedByConfig, true);
								memory::write<bool>(std::uintptr_t(skin) + offsets::bIsOwned, true);
							}
						}
					}
				}
			}
		}
	}
}



void uskeletalmeshcomponent::set_outline_mode(EAresOutlineMode mode) {
	

	auto fn_address = memory::module_base + offsets::SetAresOutlineMode;

	using set_outline_fn_t = void(*)(uskeletalmeshcomponent*, EAresOutlineMode, bool, uintptr_t, void*);

	reinterpret_cast<set_outline_fn_t>(spoofcall_stub)(
		this,
		mode,
		true,
		offsets::MagicOffsets,
		reinterpret_cast<void*>(fn_address)
		);
}

void uskeletalmeshcomponent::SetOutlineMode(EAresOutlineMode Mode)
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresOutlineComponent.SetOutlineMode").decrypt());
	struct
	{
		EAresOutlineMode Mode;
	}Parameters;
	Parameters.Mode = Mode;

	function->ProcessEvent(this, function, &Parameters);
}


void UAresOutlineComponent::SetOutlineMode(EAresOutlineMode Mode)
{
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresOutlineComponent.SetOutlineMode").decrypt());
	struct
	{
		EAresOutlineMode Mode;
	}Parameters;
	Parameters.Mode = Mode;

	function->ProcessEvent(this, function, &Parameters);

}


UEquippableSkinDataAsset* currentequippable::GetEquippableSkinDataAsset() {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetEquippableSkinDataAsset").decrypt());
	if (!function) {
		return nullptr;
	}
	struct {
		UEquippableSkinDataAsset* Out;
	} Parameters;

	function->ProcessEvent(this, function, &Parameters);
	return Parameters.Out;
}
UMaterialInterface* uskeletalmeshcomponent::GetMaterial(int32_t ElementIndex) {
	
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

std::int32_t uskeletalmeshcomponent::GetNumBones() {	
	static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.SkinnedMeshComponent.GetNumBones"));

	struct {
		int32_t return_value;
	} Parameters;

	this->process_event(Function, &Parameters);

	return Parameters.return_value;
}




void uskeletalmeshcomponent::SetMaterial(int32_t ElementIndex, uobject* Material) {
	
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetMaterial").decrypt());
	if (!function) {
		return;
	}

	struct {
		int32_t ElementIndex;
		uobject* Material;
	} Parameters;

	Parameters.ElementIndex = ElementIndex;
	Parameters.Material = Material;
	this->process_event(function, &Parameters);
}

void ashootercharacter::ClientFly()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.ClientFly").decrypt());

	struct
	{
	}Parameters;
	function->process_event(function, &Parameters);
	return;
}

fvector ashootercharacter::get_velocity() {
	static uobject* fn = nullptr;
	if (!fn) fn = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetVelocity").decrypt());

	fvector result{};
	this->ProcessEvent(fn, &result);
	return result;
}
void ashootercharacter::GetActorBounds(bool bOnlyCollidingComponents, fvector* Origin, fvector* BoxExtent, bool bIncludeFromChildActors)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorBounds").decrypt());

	struct
	{
		bool bOnlyCollidingComponents;
		fvector Origin;
		fvector BoxExtent;
		bool bIncludeFromChildActors;
	}Parameters;

	Parameters.bOnlyCollidingComponents = bOnlyCollidingComponents;
	Parameters.bIncludeFromChildActors = bIncludeFromChildActors;

	function->ProcessEvent(this, function, &Parameters);

	*Origin = Parameters.Origin;
	*BoxExtent = Parameters.BoxExtent;

}
uskeletalmeshcomponent* ashootercharacter::GetOverlayMesh1P()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P").decrypt());

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;

	this->ProcessEvent(function, &Parameters);
	return Parameters.Out;
}
UPrimitiveComponent* ashootercharacter::GetOverlayMesh1P2()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P").decrypt());

	struct
	{
		UPrimitiveComponent* Out;
	}Parameters;

	this->process_event(function, &Parameters);
	return Parameters.Out;
}


UPrimitiveComponent* ashootercharacter::GetMesh1P2()
{
	

	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh1P").decrypt());

	struct
	{
		UPrimitiveComponent* Out;
	}Parameters;
	function->ProcessEvent(this, function, &Parameters);
	return Parameters.Out;
}


uskeletalmeshcomponent* ashootercharacter::GetOverlayMesh3P()
{
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh3P").decrypt());

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;

	this->process_event(function, &Parameters);
	return Parameters.Out;
}



bool string::contains(fstring SearchIn, fstring Substring, bool bUseCase, bool bSearchFromEnd) {
	
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Contains").decrypt());

	struct {
		fstring SearchIn;
		fstring Substring;
		bool bUseCase;
		bool bSearchFromEnd;
		bool ReturnValue;
	}params;
	params.SearchIn = SearchIn;
	params.Substring = Substring;
	params.bUseCase = bUseCase;
	params.bSearchFromEnd = bSearchFromEnd;

	variables.kismet_string->ProcessEvent(function, &params);

	return params.ReturnValue;
}

