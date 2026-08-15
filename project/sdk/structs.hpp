#pragma once
#include <string>
#include <cstdint>

#include "../encrypt/crt.hpp"




template <class type>
struct tarray {
public:
    tarray() { this->data = nullptr; this->count = this->max = 0; };
    tarray(type* dataPtr, int count, int max) {
        this->data = dataPtr;
        this->count = count;
        this->max = max;
    }

    type* data;
    std::int32_t count, max;

    type& operator[](int i) {
        return this->data[i];
    };

    int size() {
        return this->count;
    }


    int Num() const
    {
        return this->count;
    }



    bool IsValidIndex(std::int32_t index) const
    {
        return index < Num();
    }

    bool valid(int i) {
        return bool(i < this->count);
    }

    void add(const type& item) {
        if (count >= max) {
            std::int32_t new_max = (max == 0) ? 1 : max * 2;
            type* new_data = (type*)::operator new[](new_max * sizeof(type));
            if (data) {
                memcpy(new_data, data, count * sizeof(type));
                ::operator delete[](data);
            }
            data = new_data;
            max = new_max;
        }
        data[count++] = item;
    }


    void Add(const type& value)
    {
        if (count >= max) // Expand
        {
            std::int32_t newMax = (max == 0) ? 1 : max * 2;
            type* newData = new type[newMax];
            for (std::int32_t i = 0; i < count; i++)
                newData[i] = data[i];
            delete[] data;
            data = newData;
            max = newMax;
        }
        data[count++] = value;
    }


    void Remove(const type& item) {
        for (int i = 0; i < count; i++) {
            if (data[i] == item) {
                for (int j = i; j < count - 1; j++)
                    data[j] = data[j + 1];
                count--;
                return;
            }
        }
    }

    void Empty() {
        delete[] data;
        data = nullptr;
        count = 0;
        max = 0;
    }


    type* begin() const { return data; }
    type* end() const { return data + count; }
};
class fname {
public:

    std::string ToString(tarray<const char*>* GNames) const
    {
        if (!GNames) return "None";
        if (comparison_index >= static_cast<uint32_t>(GNames->Num())) return "Invalid";

        std::string result = (*GNames)[comparison_index];
        if (number > 0) {
            result += "_" + std::to_string(number);
        }
        return result;
    }

    fname() : comparison_index(std::uint32_t()), number(std::int32_t()) {};
    fname(std::uint32_t index) : comparison_index(index), number(std::int32_t()) {};

public:
    std::uint32_t comparison_index;
    std::int32_t number;
};

class fkey {
public:
    fkey() : name() {}
    fkey(fname name) : name(name) {}

public:
    fname name;
    std::uint8_t details[24] = {};
};

template<class TEnum>
class TEnumAsByte
{
public:
    inline TEnumAsByte()
    {
    }

    inline TEnumAsByte(TEnum _value)
        : value(static_cast<uint8_t>(_value))
    {
    }

    explicit inline TEnumAsByte(int32_t _value)
        : value(static_cast<uint8_t>(_value))
    {
    }

    explicit inline TEnumAsByte(uint8_t _value)
        : value(_value)
    {
    }

    inline operator TEnum() const
    {
        return (TEnum)value;
    }

    inline TEnum GetValue() const
    {
        return (TEnum)value;
    }

private:
    uint8_t value;
};

template<class type> class TArray {
public:
    TArray() : Data(nullptr), Count(std::int32_t()), Max(std::int32_t()) {}
    TArray(type* Data, std::int32_t Count, std::int32_t maxx) : Data(Data), Count(Count), Max(maxx) {}

    const bool is_valid() const noexcept
    {
        return !(this->Data == nullptr);
    }

    const std::int32_t size() const noexcept
    {
        return this->Count;
    }

    type& operator[](std::int32_t index) noexcept
    {
        return this->Data[index];
    }

    const type& operator[](std::int32_t index) const noexcept
    {
        return this->Data[index];
    }

    bool is_valid_index(std::int32_t index) const noexcept
    {
        return index < this->size();
    }
    int Num() const
    {
        return Count;
    }

    type* GetData() noexcept
    {
        return Data;
    }

    void Add(const type& value)
    {
        if (Count >= Max) // Expand
        {
            std::int32_t newMax = (Max == 0) ? 1 : Max * 2;
            type* newData = new type[newMax];
            for (std::int32_t i = 0; i < Count; i++)
                newData[i] = Data[i];
            delete[] Data;
            Data = newData;
            Max = newMax;
        }
        Data[Count++] = value;
    }

protected:
    type* Data;
    std::int32_t Count;
    std::int32_t Max;
};
class fstring : public tarray<wchar_t>
{
public:
    inline fstring()
    {
    };



    fstring(const wchar_t* other)
    {
        max = count = *other ? static_cast<int>(crt::wcslen(other)) + 1 : 0;

        if (count)
        {
            data = const_cast<wchar_t*>(other);
        }
    };

    fstring(const wchar_t* other, int count)
    {
        data = const_cast<wchar_t*>(other);;
        max = count = count;
    };

    bool is_valid() const
    {
        return data != nullptr;
    }

    const wchar_t* wide() const
    {
        return data;
    }

    const wchar_t* c_str() const
    {
        return this->data;
    }

    bool empty() const
    {
        return data == nullptr || count == 0 || data[0] == L'\0';
    }


    std::string to_str() const
    {
        auto length = crt::wcslen(data);

        std::string str(length, '\0');

        for (size_t i = 0; i < length; ++i) {
            wchar_t wc = data[i];

            if (wc >= 0 && wc < 128) {
                str[i] = static_cast<char>(wc);
            }
            else {
                str[i] = '?';
            }
        }

        return str;
    }

    std::wstring ToWString() const
    {
        wchar_t* buffer = new wchar_t[max + 1];
        *(uintptr_t*)(data, (uintptr_t*)buffer, max * sizeof(wchar_t));
        buffer[max] = L'\0';
        std::wstring ws(buffer);
        delete[] buffer;
        return ws;
    }

    std::string ToString2() const
    {
        std::wstring ws = ToWString();
        return std::string(ws.begin(), ws.end());
    }


    std::string ToString() const
    {
        auto length = std::wcslen(data);

        std::string str(length, '\0');

        std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(data, data + length, '?', &str[0]);

        return str;
    }


};

class FString : public TArray<wchar_t>
{
public:
    inline FString()
    {
    };
    inline int Len() const
    {
        return IsValid() ? static_cast<int>(std::wcslen(Data)) : 0;
    }


    FString(const wchar_t* other)
    {
        Max = Count = *other ? static_cast<int>(std::wcslen(other)) + 1 : 0;

        if (Count)
        {
            Data = const_cast<wchar_t*>(other);
        }
    };
    FString(const wchar_t* other, int count)
    {
        Data = const_cast<wchar_t*>(other);;
        Max = Count = count;
    };

    inline bool IsValid() const
    {
        return Data != nullptr;
    }

    inline const wchar_t* wide() const
    {
        return Data;
    }
    const wchar_t* c_str() const
    {
        return this->Data;
    }
    int multi(char* name, int size) const
    {
        return WideCharToMultiByte(CP_UTF8, 0, Data, Count, name, size, nullptr, nullptr) - 1;
    }

    std::string ToString() const
    {
        auto length = std::wcslen(Data);

        std::string str(length, '\0');

        std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

        return str;
    }
};

class ftextdata
{
public:

    fstring TextSource;
};


class ftext
{
public:
    ftextdata* TextData;   // 0x00
    char pad_0[0x18];

    const wchar_t* c_str() const
    {
        if (!TextData)
            return L"";

        return TextData->TextSource.c_str();
    }
};

struct flinearcolor
{
	float r, g, b, a;
	flinearcolor() : r(0), g(0), b(0), a(0) { }
	flinearcolor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) { }
	flinearcolor(float r, float g, float b) : r(r), g(g), b(b), a(1.f) {}
};

enum class earesalliance : uint8_t {
	ally = 0,
	enemy = 1,
	neutral = 2,
	any = 3,
	count = 4
};

enum class e_blend_mode : uint8_t
{
	opaque = 0,
	masked = 1,
	translucent = 2,
	additive = 3,
	modulate = 4,
	alpha_composite = 5,
	max = 6,
};