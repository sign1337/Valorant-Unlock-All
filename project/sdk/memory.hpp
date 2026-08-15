#pragma once
#include <windows.h>
#include <cstdint>
#include <array>
#include <vector>
#include <string>  
#include <chrono>
#include "definitions.hpp"
#include "spoof.h"
#include "ret_spoof.h"
#include <set>
#include <TlHelp32.h>
#define null NULL
#define class_ptr uint64_t(this)


typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;

extern "C" NTSTATUS __query_virtual_memory(
    HANDLE p_handle,
    void* base_addr,
    MEMORY_INFORMATION_CLASS memory_info_class,
    void* mbi,
    std::size_t mbi_length,
    std::size_t* mbi_out_length
);

static uint64_t MockedRdtsc() {
    static uint64_t rdtscValue = __rdtsc();
    return rdtscValue;
}

inline uint64_t Fake_rdtsc() {
    static uint64_t lastTSC = __rdtsc();
    return lastTSC;
}



namespace memory
{

   

    extern "C" long nt_read_virtual_memory(HANDLE process, void* address, void* buffer, std::size_t number_of_bytes_to_read, std::size_t* number_of_bytes_readed);
    extern "C" long nt_write_virtual_memory(HANDLE process, void* address, void* buffer, std::size_t number_of_bytes_to_write, std::size_t* number_of_bytes_written);

    extern "C" uintptr_t __asm_get_peb();

    static bool read_virtual_memory(std::uintptr_t address, uint8_t* buffer, size_t size) {
        std::size_t number_of_bytes_readed = {};
        return nt_read_virtual_memory(HANDLE(-1), reinterpret_cast<void*>(address), buffer, size, &number_of_bytes_readed) == 0;
    }

    static bool write_virtual_memory(std::uintptr_t address, uint8_t* buffer, size_t size) {
        std::size_t number_of_bytes_written = {};
        return nt_write_virtual_memory(HANDLE(-1), reinterpret_cast<void*>(address), buffer, size, &number_of_bytes_written) == 0;
    }
   
    static uintptr_t get_module_base()
    {
        
        return *(uintptr_t*)(__asm_get_peb() + 0x10);
    }


    inline uintptr_t resolve_api(const char* module, const char* func) {
        
        auto hMod = SPOOF_CALL(LoadLibraryA)(module);
        return reinterpret_cast<uintptr_t>(SPOOF_CALL(GetProcAddress)(hMod, func));
    }

    bool isvalidniggersorwhat(void* retaddr, void* expectedFunc)
    {
        
        if (*((BYTE*)retaddr - 5) == 0xE8)
        {
            if ((char*)retaddr + *((int*)retaddr - 1) != (char*)expectedFunc)
                return false;
        }
        else
        {
            if (*(uint16_t*)((uintptr_t)retaddr - 3) != 0x15FF)
                return false;
        }
        return true;
    }


    inline uint64_t module_base = null;

    inline bool is_bad_write_ptr(LPVOID ptr, uint64_t size)
    {
        
        volatile uintptr_t check = (uintptr_t)ptr;
        return check == 0;
    }

    inline bool valid_pointer(uint64_t address)
    {
        
        return !is_bad_write_ptr((LPVOID)address, 8);
    }
    bool IsValidPointer2(void* ptr) {
        
        uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
        return addr > 0x10000 && addr < 0x00007FFFFFFFFFFF; 
    }

    inline bool IsValidPointer(uintptr_t address) {
        
        if (!address)
            return false;

        constexpr uintptr_t zero_filter = 0xFFFF0000FFFFFF00;
        constexpr uintptr_t extras_filter = 0xFFFF000000000000;

        uintptr_t zero_result = address & zero_filter;
        uintptr_t extras_result = address & extras_filter;

        return zero_result != 0 && extras_result == 0;
    }
   
    bool is_valid(uintptr_t pointer)
    {
        
        if (!pointer)
            return false;

        constexpr uintptr_t zero_filter = 0xFFFF0000FFFFFF00;
        constexpr uintptr_t extras_filter = 0xFFFF000000000000;

        uintptr_t zero_result = pointer & zero_filter;
        uintptr_t extras_result = pointer & extras_filter;

        return zero_result != 0 && extras_result == 0;
    }
//
//#define OBF_INLINE __forceinline
//#define OBF_JUNK(x) if((uintptr_t)(x) & 1) { __nop(); }
//
//    template<typename T>
//    OBF_INLINE T read(uintptr_t addr, const T& def = T{})
//    {
//        volatile uintptr_t p = addr ^ 0xDEADBEEFCAFEBABE;
//        p ^= 0xDEADBEEFCAFEBABE;
//
//        if (!is_valid(p))
//            return def;
//
//        
//        OBF_JUNK(p);
//
//        T out{};
//        __movsb(
//            reinterpret_cast<unsigned char*>(&out),
//            reinterpret_cast<const unsigned char*>(p),
//            sizeof(T)
//        );
//
//        return out;
//    }
//
//    template<typename T>
//    OBF_INLINE bool write(uintptr_t addr, const T& val)
//    {
//        volatile uintptr_t p = addr + 0x1337;
//        p -= 0x1337;
//
//        if (!is_valid(p))
//            return false;
//
//        
//        OBF_JUNK(p);
//
//        __movsb(
//            reinterpret_cast<unsigned char*>(p),
//            reinterpret_cast<const unsigned char*>(&val),
//            sizeof(T)
//        );
//
//        return true;
//    }



    template<typename t>
    inline t read(DWORD_PTR address, const t& def = t())
    {
        if (!address || address < 0x10000)  
            return def;

        if (!is_valid(address)) 
            return def;

        return reinterpret_cast<t(*)(std::uintptr_t)>(memory::module_base + offsets::TriggerVEH)(address - offsets::RandomShit);
        
     
    }


    template<typename t>
    inline t read2(DWORD_PTR address, const t& def = t())
    {
        if (!address || address < 0x10000)
            return def;

        if (!is_valid(address))
            return def;

        
        return *reinterpret_cast<t*>(address);

    }


    template<typename t>
    inline bool write(DWORD_PTR address, const t& value)
    {
        // Validate WITHOUT stack manipulation first
        if (!address || address < 0x10000)
            return false;

        // Make sure is_valid() has NO SPOOF_FUNC inside it
        if (!is_valid(address))
            return false;

        // Only now use SPOOF_FUNC for the actual write
        
        *reinterpret_cast<t*>(address) = value;
        return true;
    }

    inline uint64_t get_module(wchar_t* name) {
        
        const ntos::peb* peb = reinterpret_cast<ntos::peb*>(__readgsqword(0x60));
        if (!peb) return uint64_t(0);

        const ntos::list_entry head = peb->Ldr->InMemoryOrderModuleList;

        for (auto curr = head; curr.Flink != &peb->Ldr->InMemoryOrderModuleList; curr = *curr.Flink) {
            ntos::ldr_data_table_entry* mod = reinterpret_cast<ntos::ldr_data_table_entry*>(contains_record(curr.Flink, ntos::ldr_data_table_entry, InMemoryOrderLinks));

            if (mod->BaseDllName.Buffer)
                if (crt::wcsicmp_insensitive(mod->BaseDllName.Buffer, name))
                {
                    return uint64_t(mod->DllBase);
                }
        }

        return uint64_t(0);
    }

    inline void clear_pe_header(HMODULE hModule) {
        DWORD old;
        SPOOF_CALL(VirtualProtect)(hModule, 0x1000, PAGE_EXECUTE_READWRITE, &old);
        SPOOF_CALL(crt::custom_memset)(hModule, 0, 0x1000);
        SPOOF_CALL(VirtualProtect)(hModule, 0x1000, old, &old);
    }

    void EraseIATAndRelocs(HMODULE hModule) {
        if (!hModule) return;

        auto* dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
        auto* ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>((uintptr_t)hModule + dosHeader->e_lfanew);
        auto& optionalHeader = ntHeaders->OptionalHeader;

        // 1. Erase Import Directory (IAT)
        if (optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size) {
            DWORD oldProtect = 0;
            auto* importDir = reinterpret_cast<void*>(
                (uintptr_t)hModule + optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
            SIZE_T size = optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;

            if (SPOOF_CALL(VirtualProtect)(importDir, size, PAGE_READWRITE, &oldProtect)) {
                SecureZeroMemory(importDir, size);
                SPOOF_CALL(VirtualProtect)(importDir, size, oldProtect, &oldProtect);
            }
            optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = 0;
            optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = 0;
        }

        // 2. Erase Relocation Table
        if (optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size) {
            DWORD oldProtect = 0;
            auto* relocDir = reinterpret_cast<void*>(
                (uintptr_t)hModule + optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
            SIZE_T size = optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size;

            if (SPOOF_CALL(VirtualProtect)(relocDir, size, PAGE_READWRITE, &oldProtect)) {
                SecureZeroMemory(relocDir, size);
                SPOOF_CALL(VirtualProtect)(relocDir, size, oldProtect, &oldProtect);
            }
            optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress = 0;
            optionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size = 0;
        }
    }

}

uint64_t malloc_spoofed(int32_t size, uint32_t aligment) {
    
    auto niga = memory::module_base + offsets::fmemory_malloc;
    return reinterpret_cast<uint64_t(__cdecl*)(uint64_t, int, uintptr_t, void*)>(spoofcall_stub)(size, aligment, offsets::MagicOffsets, (void*)niga);
}
namespace SLIGHTS {
    namespace vmt {
        class shadow {
        public:

            shadow() {}

            shadow(void* object) { this->initialize(object); }

            template <typename hook_type>
            _declspec(noinline) hook_type vmt(std::uintptr_t address, std::uintptr_t hook_function, int index) {
                
                auto vtable = *(std::uintptr_t**)address;

                int vtable_size = 0;
                do vtable_size += 1;
                while (*(std::uintptr_t*)(std::uintptr_t(vtable) + (vtable_size * 8)));

                auto original_virtual_function = (void*)vtable[index];

                std::uintptr_t* fake_vtable = new std::uintptr_t[vtable_size * 8];

                for (int i = 0; i < vtable_size; i++) {
                    if (i == index) continue;
                    fake_vtable[i] = *(std::uintptr_t*)(std::uintptr_t(vtable) + (i * 8));
                } fake_vtable[index] = hook_function;

                memory::write<uintptr_t*>(address, fake_vtable);
      

                return hook_type(original_virtual_function);
            }

            bool initialize(void* object, std::size_t size = 0) {
                
                this->object = object;
                if (this->object == nullptr) return false;

                this->object_vtable = memory::read<uintptr_t*>((uintptr_t)this->object);
                if (this->object_vtable == nullptr) return false;
                if (this->object_vtable == this->object_fake_vtable) return false;

                if (size == 0) {
                    while (is_valid_ptr_value(this->object_vtable[size])) ++size;
                    size *= sizeof(std::uintptr_t);
                }

                this->object_fake_vtable = reinterpret_cast<std::uintptr_t*>(malloc_spoofed(size, PAGE_EXECUTE_READWRITE));
                if (this->object_fake_vtable == nullptr) return false;

                crt::custom_memcpy(
                    reinterpret_cast<void*>(this->object_fake_vtable),
                    reinterpret_cast<const void*>(this->object_vtable),
                    static_cast<std::size_t>(size)
                );


                memory::write<uintptr_t*>((uintptr_t)this->object, this->object_fake_vtable);
                return true;
            }

            void restore_table() {
                
                if (this->object == nullptr) return;
                if (this->object_vtable == nullptr) return;
                memory::write<uintptr_t*>((uintptr_t)this->object, this->object_vtable);
            }

            void virtual_hook(void* addr, void* pDes, int index, void** ret) {
                auto vtable = memory::read<uintptr_t*>(std::uintptr_t(addr));
                int methods = 0;

                for (int i = 0; memory::read<uintptr_t>((uintptr_t)vtable + (i * offsets::RandomShit)); i++) methods++;

                auto vtable_buf = new uint64_t[methods * offsets::RandomShit];
                for (int count = 0; count < methods; ++count) {
                    vtable_buf[count] = memory::read<uintptr_t>((uintptr_t)vtable + (count * offsets::RandomShit));

                    *ret = (void*)vtable[index];

                    vtable_buf[index] = (uintptr_t)(pDes);

                    memory::write <uint64_t*>(std::uintptr_t(addr), vtable_buf);
                }

            }
            void VMT(void* addr, void* pDes, int index, void** ret)
            {
                auto vtable = *(uintptr_t**)addr;
                int methods = 0;
                do {
                    ++methods;
                } while (*(uintptr_t*)((uintptr_t)vtable + (methods * 0x8)));
                auto vtable_buf = new uint64_t[methods * 0x8];
                for (auto count = 0; count < methods; ++count) {
                    vtable_buf[count] = *(uintptr_t*)((uintptr_t)vtable + (count * 0x8));

                    *ret = (void*)vtable[index];

                    vtable_buf[index] = (uintptr_t)(pDes);
                    *(uint64_t**)addr = vtable_buf;
                }
            }

            template <typename function> function apply(std::uintptr_t address, std::size_t index) {
                
                if (!address)
                    return function();

                if (const std::uintptr_t original = this->object_fake_vtable[index])
                    if (this->object_fake_vtable[index] = address)
                        return reinterpret_cast<function>(original);

                return function();
            }


            uint64_t get_address_from_index(std::size_t index) {
                
                return this->object_fake_vtable[index];
            }

        private:
            void* object = nullptr;
            std::uintptr_t* object_vtable = nullptr;
            std::uintptr_t* object_fake_vtable = nullptr;

        public:
            static inline std::uintptr_t rwx_cave = std::uintptr_t();
            static inline std::int32_t total_function = std::int32_t();

            bool is_valid_ptr_value(std::uintptr_t pointer) {
                
                return pointer && (pointer >= 0x10000) && (pointer < 0xF000000000000);
            }

          	static std::uintptr_t bind_function_to_rwx_cave(void* function) {
				if (shadow::rwx_cave == 0)
					return std::uintptr_t();

				std::array<std::uint8_t, 15> stub = { 0xFF, 0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xC3 };
				*reinterpret_cast<void**>(&stub[6]) = function;

				const std::uintptr_t address = (shadow::rwx_cave + 0x80) + (shadow::total_function * stub.size());

				__movsb(reinterpret_cast<std::uint8_t*>(address), stub.data(), stub.size());

				++shadow::total_function;

				return address;
			}

            static void unbind_all_functions()
            {
                
                if (shadow::total_function == 0 || shadow::rwx_cave == 0)
                    return;

                std::array<std::uint8_t, 15> stub = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

                for (int x = 0; x != shadow::total_function; x++)
                {
                    const std::uintptr_t address = (shadow::rwx_cave + 0x80) + (x * stub.size());
                    crt::custom_memcpy(
                        reinterpret_cast<void*>(address),                 // destination
                        reinterpret_cast<const void*>(stub.data()),       // source
                        static_cast<std::size_t>(stub.size())            // number of bytes
                    );

                }
            }

            static std::uintptr_t find_whitelisted_rwx_cave() {
                
                MEMORY_BASIC_INFORMATION mbi = {};
                std::uintptr_t address = std::uintptr_t();

                while (__query_virtual_memory(HANDLE(-1), reinterpret_cast<void*>(address), MemoryBasicInformation, &mbi, sizeof(mbi), nullptr) == 0) {
                    if (address && mbi.Protect == PAGE_EXECUTE_READWRITE && mbi.AllocationProtect == PAGE_EXECUTE_READWRITE && mbi.Type == MEM_PRIVATE && mbi.State == MEM_COMMIT) {
                        std::uint8_t* pattern_address = reinterpret_cast<std::uint8_t*>(address);

                        bool is_empty_end = true;
                        for (std::size_t index = 100; index < mbi.RegionSize; index++)
                            if (!(pattern_address[index] == 0ui8))
                                if (is_empty_end = !is_empty_end; is_empty_end == false)
                                    break;

                        if (is_empty_end && pattern_address[0] == 0x48 && pattern_address[1] == 0x89 && pattern_address[2] == 0x5C && pattern_address[3] == 0x24)
                            return address;
                    }
                    address += mbi.RegionSize;
                }
                return address;
            }
        };
    }
}
