#pragma once
#include <thread>     // for std::thread and std::this_thread::sleep_for
#include <chrono>

#ifdef _KERNEL_MODE
namespace std
{
	// STRUCT TEMPLATE remove_reference
	template <class _Ty>
	struct remove_reference {
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&> {
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&&> {
		using type = _Ty;
	};

	template <class _Ty>
	using remove_reference_t = typename remove_reference<_Ty>::type;

	// STRUCT TEMPLATE remove_const
	template <class _Ty>
	struct remove_const { // remove top-level const qualifier
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_const<const _Ty> {
		using type = _Ty;
	};

	template <class _Ty>
	using remove_const_t = typename remove_const<_Ty>::type;
}
#else
#include <type_traits>
#endif

namespace skc
{
	template<class _Ty>
	using clean_type = typename std::remove_const_t<std::remove_reference_t<_Ty>>;

	template <int _size, char _key1, char _key2, typename T>
	class skCrypter
	{
	public:
		__forceinline constexpr skCrypter(T* data)
		{
			crypt(data);
		}

		__forceinline T* get()
		{
			return _storage;
		}

		__forceinline int size() // (w)char count
		{
			return _size;
		}

		__forceinline  char key()
		{
			return _key1;
		}

		__forceinline  T* encrypt()
		{
			if (!isEncrypted())
				crypt(_storage);

			return _storage;
		}

		__forceinline  T* decrypt()
		{
			if (isEncrypted())
				crypt(_storage);

			return _storage;
		}

		__forceinline bool isEncrypted()
		{
			return _storage[_size - 1] != 0;
		}

		__forceinline std::string decrypt_and_wipe()
		{
			// Decrypt internal storage if still encrypted
			if (isEncrypted())
				crypt(_storage);

			// Copy decrypted string (excluding null terminator)
			std::string result(_storage, _storage + _size - 1);

			// Wipe internal buffer immediately after copying
#if defined(_WIN32) || defined(_WIN64)
			SecureZeroMemory(_storage, sizeof(_storage));
#else
			volatile T* ptr = _storage;
			for (int i = 0; i < _size; i++)
				ptr[i] = 0;
#endif

			// 🔁 Defer wiping the result using a background thread
			std::thread([copy = result]() mutable {
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // adjust delay if needed
#if defined(_WIN32) || defined(_WIN64)
				SecureZeroMemory(copy.data(), copy.size());
#else
				volatile char* ptr = copy.data();
				for (size_t i = 0; i < copy.size(); i++)
					ptr[i] = 0;
#endif
				}).detach(); // fire and forget

			return result; // decrypted for ~50ms, then wiped
		}

		__forceinline std::string decrypt_and_wipe2()
		{
			// Decrypt internal storage if still encrypted
			if (isEncrypted())
				crypt(_storage);

			// Copy decrypted string (excluding null terminator)
			std::string result(_storage, _storage + _size - 1);

			// Wipe internal buffer immediately after copying
#if defined(_WIN32) || defined(_WIN64)
			SecureZeroMemory(_storage, sizeof(_storage));
#else
			volatile T* ptr = _storage;
			for (int i = 0; i < _size; i++)
				ptr[i] = 0;
#endif

			// 🔁 Defer wiping the result using a background thread
			std::thread([copy = result]() mutable {
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // adjust delay if needed
#if defined(_WIN32) || defined(_WIN64)
				SecureZeroMemory(copy.data(), copy.size());
#else
				volatile char* ptr = copy.data();
				for (size_t i = 0; i < copy.size(); i++)
					ptr[i] = 0;
#endif
				}).detach(); // fire and forget

			return result; // decrypted for ~50ms, then wiped
		}

		__forceinline const char* decrypt_and_wipe_cstr()
		{
			static char decryptedBuffer[512]; // adjust size based on your needs

			// Decrypt internal storage if still encrypted
			if (isEncrypted())
				crypt(_storage);

			// Copy decrypted string into static buffer (excluding null terminator)
			memcpy(decryptedBuffer, _storage, _size - 1);
			decryptedBuffer[_size - 1] = '\0';

			// Wipe internal buffer immediately
#if defined(_WIN32) || defined(_WIN64)
			SecureZeroMemory(_storage, sizeof(_storage));
#else
			volatile T* ptr = _storage;
			for (int i = 0; i < _size; i++)
				ptr[i] = 0;
#endif

			// Optionally wipe decryptedBuffer after delay (unsafe if reused concurrently)
			std::thread([]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
#if defined(_WIN32) || defined(_WIN64)
				SecureZeroMemory(decryptedBuffer, sizeof(decryptedBuffer));
#else
				volatile char* ptr = decryptedBuffer;
				for (size_t i = 0; i < sizeof(decryptedBuffer); i++)
					ptr[i] = 0;
#endif
				}).detach();

			return decryptedBuffer; // 🔓 valid as long as not overwritten
		}

		__forceinline std::wstring decrypt_and_wipe_w()
		{
			// Decrypt internal storage if still encrypted
			if (isEncrypted())
				crypt(_storage);  // assumes _storage is wchar_t* or T*

			// Copy decrypted string (excluding null terminator)
			std::wstring result(_storage, _storage + _size - 1);

			// Wipe internal buffer immediately
#if defined(_WIN32) || defined(_WIN64)
			SecureZeroMemory(_storage, sizeof(wchar_t) * _size);
#else
			volatile wchar_t* ptr = _storage;
			for (int i = 0; i < _size; i++)
				ptr[i] = 0;
#endif

			// 🔁 Defer wiping the result using a background thread
			std::thread([copy = result]() mutable {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
#if defined(_WIN32) || defined(_WIN64)
				SecureZeroMemory(copy.data(), copy.size() * sizeof(wchar_t));
#else
				volatile wchar_t* ptr = copy.data();
				for (size_t i = 0; i < copy.size(); i++)
					ptr[i] = 0;
#endif
				}).detach();

			return result;
		}

		__forceinline std::wstring decrypt_and_wipe_z()
		{
			// Decrypt _storage in-place if still encrypted
			if (isEncrypted())
				crypt(_storage);  // assume this decrypts wchar_t* _storage in-place

			// Copy decrypted string (excluding null terminator)
			std::wstring result(_storage, _storage + _size - 1);

			// Immediate secure wipe of internal buffer
#if defined(_WIN32) || defined(_WIN64)
			SecureZeroMemory(_storage, sizeof(wchar_t) * _size);
#else
			volatile wchar_t* ptr = _storage;
			for (int i = 0; i < _size; ++i)
				ptr[i] = 0;
#endif

			// Background secure wipe of returned result (after 50ms)
			std::thread([copy = result]() mutable {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
#if defined(_WIN32) || defined(_WIN64)
				SecureZeroMemory(copy.data(), copy.size() * sizeof(wchar_t));
#else
				volatile wchar_t* ptr = copy.data();
				for (size_t i = 0; i < copy.size(); ++i)
					ptr[i] = 0;
#endif
				}).detach();

			return result;
		}

		__forceinline void clear() // set full storage to 0
		{
			for (int i = 0; i < _size; i++)
			{
				_storage[i] = 0;
			}
		}

		__forceinline operator T* ()
		{
			decrypt();

			return _storage;
		}

	private:
		__forceinline constexpr void crypt(T* data)
		{
			for (int i = 0; i < _size; i++)
			{
				_storage[i] = data[i] ^ (_key1 + i % (1 + _key2));
			}
		}

		T _storage[_size]{};
	};
}

#define EncryptString(chararr) std::string(Encrypt(chararr)).c_str()
#define DecryptOffset(value) [&](){ auto val = value; int retval = strtol(val.decrypt(), NULL, 16); val.encrypt(); return retval; }()
#define DecryptOffsetClear(value) [&](){ auto val = value; int retval = strtol(val.decrypt(), NULL, 16); val.clear(); return retval; }()
#define EncryptString(chararr) std::string(Encrypt(chararr)).c_str()
#define Encrypt(str) skCrypt_key(str, __TIME__[7] + 1, __TIME__[4] + 9)
#define crypt(str) skCrypt_key(str, __TIME__[2], __TIME__[4])
#define skCrypt_key(str, key1, key2) []() { \
			constexpr static auto crypted = skc::skCrypter \
				<sizeof(str) / sizeof(str[0]), key1, key2, skc::clean_type<decltype(str[0])>>((skc::clean_type<decltype(str[0])>*)str); \
					return crypted; }()

//#define DecryptOffset(value) [&](){ auto val = value; int retval = strtol(val.decrypt(), NULL, 16); val.encrypt(); return retval; }()
//#define DecryptOffsetClear(value) [&](){ auto val = value; int retval = strtol(val.decrypt(), NULL, 16); val.clear(); return retval; }()
#define EncryptGet(value) [&](){ auto val = Encrypt(value); std::string return_value = val.decrypt(); val.encrypt(); return return_value; }()
#define EncryptGetL(value) [&](){ auto val = Encrypt(value); auto return_value = val.decrypt(); val.encrypt(); return return_value; }()