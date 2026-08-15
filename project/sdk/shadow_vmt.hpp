#pragma once
#include "memory.hpp"

class shadow_vmt
{
public:

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

		*(std::uintptr_t**)address = fake_vtable;

		return hook_type(original_virtual_function);
	}

	void VMT(void* Addr, void* PDes, int Index, void** Ret)
	{
		


		auto VTable = *static_cast<std::uintptr_t**>(Addr);
		int Methods = 0;

		do
		{
			++Methods;
		} while (*reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(VTable) + (static_cast<unsigned long long>(Methods) * 0x8)));

		auto VTableBuf = new std::uint64_t[Methods * 0x8];

		for (auto Count = 0; Count < Methods; ++Count)
		{
			VTableBuf[Count] = *reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(VTable) + (static_cast<unsigned long long>(Count) * 0x8));
		}

		*Ret = reinterpret_cast<void*>(VTable[Index]);

		VTableBuf[Index] = reinterpret_cast<std::uintptr_t>(PDes);
		*reinterpret_cast<std::uint64_t**>(Addr) = VTableBuf;
	}






	void vhook(void* addr, void* pDes, int index, void** ret) {
		auto vtable = memory::read<uintptr_t*>(std::uintptr_t(addr));
		int methods = 0;

		for (int i = 0; memory::read<uintptr_t>((uintptr_t)vtable + (i * 0x8)); i++) methods++;

		auto vtable_buf = new uint64_t[methods * 0x8];
		for (int count = 0; count < methods; ++count) {
			vtable_buf[count] = memory::read<uintptr_t>((uintptr_t)vtable + (count * 0x8));

			*ret = (void*)vtable[index];

			vtable_buf[index] = (uintptr_t)(pDes);
			*(uint64_t**)(std::uintptr_t(addr)) = vtable_buf;

		}
	}




	template <typename type>
	bool hook(uint64_t module_base, uint64_t address, int index, void* function, type* original)
	{
		this->virtual_table = *(uintptr_t**)(address);
		if (reinterpret_cast<void*>(this->virtual_table[index]) != function)
		{
			while (this->virtual_table[this->vtable_size])
			{
				this->vtable_size++;
			}
			if (index < this->vtable_size)
			{
				this->allocated_vtable = reinterpret_cast<uintptr_t*>(
					fmemory::malloc(this->vtable_size * sizeof(uintptr_t), PAGE_EXECUTE_READWRITE)
					);

				for (int i = 0; i < this->vtable_size; i++)
				{
					this->allocated_vtable[i] = this->virtual_table[i];
				}
				*original = reinterpret_cast<type>(this->virtual_table[index]);
				this->allocated_vtable[index] = reinterpret_cast<uintptr_t>(function);
				*(uintptr_t**)(address) = this->allocated_vtable;
				return true;
			}
		}
		return false;
	}
private:
	uintptr_t* virtual_table;
	uintptr_t* allocated_vtable;
	int vtable_size;
};