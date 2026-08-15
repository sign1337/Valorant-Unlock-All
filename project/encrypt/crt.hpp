#pragma once
#define contains_record( address, type, field ) ( ( type* )( ( char* )( address ) - ( uint64_t )( & ( (type* ) 0 ) -> field ) ) )
#define loword(l) ((std::uint16_t)(((uint64_t)(l)) & 0xffff))

namespace crt 
{
    void* custom_memset(void* dst0, register int c0, unsigned int len)
    {

        unsigned int i;
        unsigned int fill;
        unsigned int chunks = len / sizeof(fill);
        char* char_dest = (char*)dst0;
        unsigned int* uint_dest = (unsigned int*)dst0;
        fill = (c0 << 24) + (c0 << 16) + (c0 << 8) + c0;

        for (i = len; i > chunks * sizeof(fill); i--) {
            char_dest[i - 1] = c0;
        }

        for (i = chunks; i > 0; i--) {
            uint_dest[i - 1] = fill;
        }

        return dst0;

    }

    void* custom_memcpy(void* dest, const void* src, size_t count)
    {
        char* char_dest = static_cast<char*>(dest);
        const char* char_src = static_cast<const char*>(src);

        if (char_dest < char_src) {
            for (size_t i = 0; i < count; i++) {
                char_dest[i] = char_src[i];
            }
        }
        else if (char_dest > char_src) {
            for (size_t i = count; i > 0; i--) {
                char_dest[i - 1] = char_src[i - 1];
            }
        }
        return dest;
    }

    inline size_t strlen(const char* str) {
        if (str == nullptr) {
            return 0;
        }

        const char* s = str;
        while (*s != '\0') {
            ++s;
        }
        return s - str;
    }

    inline int wcslen(const wchar_t* str) {
        int counter = 0;
        if (!str)
            return 0;
        for (; *str != '\0'; ++str)
            ++counter;
        return counter;
    }
    // Case-insensitive wide string compare (undetected variant)
    inline bool wcsicmp_insensitive(const wchar_t* a, const wchar_t* b)
    {
        if (!a || !b)
            return false;

        // manual length check without wcslen
        const wchar_t* p = a;
        const wchar_t* q = b;
        size_t lenA = 0, lenB = 0;

        while (*p++) ++lenA;
        while (*q++) ++lenB;

        if (lenA != lenB)
            return false;

        for (size_t i = 0; i < lenA; ++i)
        {
            wchar_t ca = a[i];
            wchar_t cb = b[i];

            // normalize to lowercase using bit trick only for ASCII
            if (ca >= L'A' && ca <= L'Z') ca |= 0x20;
            if (cb >= L'A' && cb <= L'Z') cb |= 0x20;

            if (ca != cb)
                return false;
        }
        return true;
    }


    __forceinline bool contains(std::string firstString, std::string secondString) {
        if (secondString.size() > firstString.size())
            return false;

        for (int i = 0; i < firstString.size(); i++) {
            int j = 0;
            if (firstString[i] == secondString[j]) {
                int k = i;
                while (firstString[i] == secondString[j] && j < secondString.size()) {
                    j++;
                    i++;
                }
                if (j == secondString.size())
                    return true;
                else 
                    i = k;
            }
        }
        return false;
    }
}