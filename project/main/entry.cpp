#include "../cheat/hooks.hpp"
#include <filesystem>
#include "../sdk/spoof2.h"
#include <process.h>
#include <windows.h>
#include "../cheat/hooks.hpp"
#include <filesystem>
#include "../sdk/spoof2.h"
#include <process.h>
#include <windows.h>
#include <winternl.h>
#include "../protection.h"
#include <iostream>
#include <string>
#include <winhttp.h>
#include <thread>
#include <chrono>
#include <cstring>
#include <random>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include <string>
#include <winhttp.h>
#include <thread>
#include <chrono>
std::string g_authToken = "";
HMODULE g_hModule = NULL;
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "winhttp.lib")
typedef struct _LDR_MODULE {
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID BaseAddress;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    SHORT LoadCount;
    SHORT TlsIndex;
    LIST_ENTRY HashTableEntry;
    ULONG TimeDateStamp;
} LDR_MODULE, * PLDR_MODULE;

// NtCreateThreadEx definition
typedef NTSTATUS(NTAPI* pNtCreateThreadEx)(
    PHANDLE ThreadHandle,
    ACCESS_MASK DesiredAccess,
    PVOID ObjectAttributes,
    HANDLE ProcessHandle,
    PVOID StartRoutine,
    PVOID Argument,
    ULONG CreateFlags,
    SIZE_T ZeroBits,
    SIZE_T StackSize,
    SIZE_T MaximumStackSize,
    PVOID AttributeList
    );

// Simple JSON extractor for the response
std::string get_json_val(const std::string& json, const std::string& key) {
    std::string search = OBF("\"") + key + OBF("\":\"");
    size_t start = json.find(search);
    if (start == std::string::npos) return "";
    start += search.length();
    size_t end = json.find(OBF("\""), start);
    return json.substr(start, end - start);
}

// Random sleep with jitter
void RandomSleep(int baseMs = 500) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(baseMs - 100, baseMs + 100);
    int sleepTime = dist(rng);

    // Use various sleep methods to avoid pattern
    switch (sleepTime % 3) {
    case 0: Sleep(sleepTime); break;
    case 1: std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime)); break;
    case 2: {
        HMODULE ntdll = GetModuleHandleA("ntdll.dll");
        if (ntdll) {
            auto NtDelayExecution = (NTSTATUS(NTAPI*)(BOOL, PLARGE_INTEGER))GetProcAddress(ntdll, "NtDelayExecution");
            if (NtDelayExecution) {
                LARGE_INTEGER li;
                li.QuadPart = -10000 * sleepTime;
                NtDelayExecution(FALSE, &li);
            }
        }
        break;
    }
    }
}


void SecurityMonitorThread() {
    while (true) {
        check_window_titles();
        ANTI_DUMP_PE;
        anti_apc_injection();
        anti_api_hook();
        anti_attach();
        anti_code_patch();
        anti_debug();
        anti_dll_injection();
        anti_dump_and_seh();
        anti_dump_pe();
        anti_iat_hook();
        anti_instrumentation();
        anti_network_analysis();
        anti_pause_thread();
        anti_reverse_files();
        anti_terminate_thread();

        KILL_PYQT_APPS;
        ANTI_DUMP_PE;
        ADD_FAKE_AUTH_STRINGS;

        START_DEBUG_REG_PROTECTION;
        START_IDT_PROTECTION;
        START_PAGE_PROTECTION;
        START_KERNEL_CALLBACK_PROTECTION;
        JUNK_SHIP_SPACIAL;
        START_INTEGRITY_CHECK;
        START_ANTI_ATTACH;
        START_ANTI_WINDOW_TITLE;
        START_ANTI_PAUSE_THREAD;
        START_ANTI_TERMINATE_THREAD;
        START_ANTI_CODE_PATCH;
        START_ANTI_API_HOOK;
        START_ANTI_IAT_HOOK;
        START_ANTI_DEBUG;
        START_ANTI_DUMP_AND_SEH;
        START_ANTI_VM;
        START_ANTI_VM_ADVANCED;
        START_ANTI_INSTRUMENTATION;
        START_ANTI_NETWORK_ANALYSIS;
        START_ANTI_REVERSE_FILES;
        START_MEMORY_PROTECTION;
        START_SYSCALL_PROTECTION;
        START_ANTI_APC;
        START_GDT_PROTECTION;
        START_DEBUG_REG_PROTECTION;
        START_IDT_PROTECTION;
        START_PAGE_PROTECTION;
        START_KERNEL_CALLBACK_PROTECTION;
        START_JUNK_THREADS;

        JUNK_VAR;
        JUNK_FUCK_IDA;
        BUG_IDA;
        ZIGZAG_JUNK;
        PYRAMID_JUNK;
        JUNK_SHIP_SPACIAL;
        COOL_JUNK;
        CALL_RANDOM_JUNK;
        ULTRA_MEGA_JUNK(0);
        Junkyyyyyyy(0);
        START_PAGE_PROTECTION;

        RandomSleep(500);
    }
}

void UnlinkFromPeb() {
    PPEB peb = reinterpret_cast<PPEB>(__readgsqword(0x60));
    if (!peb || !peb->Ldr) return;

    PLIST_ENTRY head = &peb->Ldr->InMemoryOrderModuleList;
    PLIST_ENTRY current = head->Flink;

    while (current != head) {
        PLDR_MODULE module = CONTAINING_RECORD(current, LDR_MODULE, InMemoryOrderModuleList);

        if (module->BaseAddress == g_hModule) {
            module->InLoadOrderModuleList.Blink->Flink = module->InLoadOrderModuleList.Flink;
            module->InLoadOrderModuleList.Flink->Blink = module->InLoadOrderModuleList.Blink;
            module->InMemoryOrderModuleList.Blink->Flink = module->InMemoryOrderModuleList.Flink;
            module->InMemoryOrderModuleList.Flink->Blink = module->InMemoryOrderModuleList.Blink;
            module->InInitializationOrderModuleList.Blink->Flink = module->InInitializationOrderModuleList.Flink;
            module->InInitializationOrderModuleList.Flink->Blink = module->InInitializationOrderModuleList.Blink;

            module->InLoadOrderModuleList.Flink = module->InLoadOrderModuleList.Blink = nullptr;
            module->InMemoryOrderModuleList.Flink = module->InMemoryOrderModuleList.Blink = nullptr;
            module->InInitializationOrderModuleList.Flink = module->InInitializationOrderModuleList.Blink = nullptr;
            break;
        }
        current = current->Flink;
    }
}
void CleanKdmapperLogs() {
    wchar_t cmdline[512];
    swprintf(cmdline, 512, OBF(L"wevtutil cl \"Microsoft-Windows-Kernel-PnP/Configuration\" /q"));
    _wsystem(cmdline);

    swprintf(cmdline, 512, OBF(L"wevtutil cl \"System\" /q"));
    _wsystem(cmdline);

    RandomSleep(100);
}
void WipeSecurityDirectory() {
    if (!g_hModule) return;

    PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)g_hModule;
    if (pDos->e_magic != IMAGE_DOS_SIGNATURE) return;

    PIMAGE_NT_HEADERS pNt = (PIMAGE_NT_HEADERS)((BYTE*)g_hModule + pDos->e_lfanew);
    if (pNt->Signature != IMAGE_NT_SIGNATURE) return;

    DWORD secDir = pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress;
    if (secDir) {
        DWORD old;
        VirtualProtect((BYTE*)g_hModule + secDir, 0x1000, PAGE_READWRITE, &old);
        memset((BYTE*)g_hModule + secDir, 0, 0x1000);
        pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress = 0;
        pNt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size = 0;
        VirtualProtect((BYTE*)g_hModule + secDir, 0x1000, old, &old);
    }
}

void WipePeHeaders() {
    if (!g_hModule) return;

    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)g_hModule;
    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((uintptr_t)g_hModule + pDosHeader->e_lfanew);

    DWORD oldProtect;
    SIZE_T headersSize = pNtHeaders->OptionalHeader.SizeOfHeaders;

    VirtualProtect(g_hModule, headersSize, PAGE_READWRITE, &oldProtect);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    uint8_t* pHeaders = (uint8_t*)g_hModule;
    for (SIZE_T i = 0; i < headersSize; i++) {
        if (i < 2) {
            if (i == 0) pHeaders[i] = 'M';
            else if (i == 1) pHeaders[i] = 'Z';
        }
        else {
            pHeaders[i] = (uint8_t)dis(gen);
        }
    }

    VirtualProtect(g_hModule, headersSize, oldProtect, &oldProtect);
}

extern "C" __declspec(dllexport) LRESULT unlock_all(int code, WPARAM wParam, LPARAM lParam) {
    return CallNextHookEx(nullptr, code, wParam, lParam);
}

void bypass_pak_signing();
void mount_custom_pak(const wchar_t* path, int priority);

__int64 get_fpak_platform_file()
{
    auto delegate = *(__int64*)((uintptr_t)GetModuleHandleA(nullptr) + offsets::get_fpak_platform_file);
    if (!delegate) return 0;
    return *(__int64*)(delegate + 24);
}

void bypass_pak_signing()
{
    auto delegate = (uint8_t*)((uintptr_t)GetModuleHandleA(nullptr) + offsets::bypass_pak_signing);
    DWORD old_protect;
    VirtualProtect(delegate, 0x20, PAGE_READWRITE, &old_protect);
    memset(delegate, 0, 0x20);
    VirtualProtect(delegate, 0x20, old_protect, &old_protect);

    auto fpak = get_fpak_platform_file();
    if (fpak) {
        auto bsigned_ptr = (uint8_t*)(fpak + 48);
        VirtualProtect(bsigned_ptr, 1, PAGE_READWRITE, &old_protect);
        *bsigned_ptr = 0;
        VirtualProtect(bsigned_ptr, 1, old_protect, &old_protect);
    }
}

void mount_custom_pak(const wchar_t* path, int priority)
{
    auto fpak = get_fpak_platform_file();
    if (!fpak) return;

    typedef bool(__fastcall* fn_mount)(__int64, const wchar_t*, int, const wchar_t*, bool, bool);
    auto mount = (fn_mount)((uintptr_t)GetModuleHandleA(nullptr) + offsets::mount_custom_pak);
    mount(fpak, path, priority, nullptr, true, false);
}

void StartInitialization() {

    RandomSleep(1000);

    std::thread security_worker(SecurityMonitorThread);
    security_worker.detach();
    RandomSleep(1000);
    uintptr_t base = 0;
    while (!base) {
        base = (uintptr_t)GetModuleHandleA(OBF("VALORANT-Win64-Shipping.exe"));
        Sleep(500);
    }

    memory::module_base = base;
    (initialize_spoofcall)((uint8_t*)memory::module_base);

    bypass_pak_signing();
    mount_custom_pak(OBF(L"C:\\mods\\pakchunk1-Windows_P.pak"), 10000);
    RandomSleep(1000);
    mount_custom_pak(OBF(L"C:\\mods\\pakchunk2-Windows_P.pak"), 10001);
    RandomSleep(1000);
    mount_custom_pak(OBF(L"C:\\mods\\pakchunk3-Windows_P.pak"), 10002);
    CleanKdmapperLogs();
    // WipeSecurityDirectory();
    WipePeHeaders();
    UnlinkFromPeb();
    hooks::q9F_init();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_hModule = hModule;
        DisableThreadLibraryCalls(hModule);

        // Use NtCreateThreadEx for stealth
        pNtCreateThreadEx NtCreateThreadEx = (pNtCreateThreadEx)GetProcAddress(
            GetModuleHandleA(OBF("ntdll.dll")), OBF("NtCreateThreadEx"));

        if (NtCreateThreadEx) {
            HANDLE hThread;
            NtCreateThreadEx(&hThread, THREAD_ALL_ACCESS, NULL, GetCurrentProcess(),
                (LPTHREAD_START_ROUTINE)StartInitialization, NULL,
                0x8, 0, 0, 0, NULL);
            if (hThread) CloseHandle(hThread);
        }
        else {
            // Fallback for compatibility
            CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)StartInitialization, nullptr, 0, nullptr));
        }
    }
    return TRUE;
}