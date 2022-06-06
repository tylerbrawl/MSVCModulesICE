module;
#include <string_view>

export module Constants;

export
{
	// It breaks regardless of whether the value is a std::wstring_view...
	constexpr std::wstring_view TEST_FILE_NAME{ L"Baka.txt" };

	// ...or a raw C-string.
	constexpr const wchar_t* OTHER_TEST_FILE_NAME{ L"Idiot.txt" };

	// NOTE: The program will compile if these are *NOT* made constexpr, even when
	// "Whole Program Optimization" is enabled. However, in that scenario, you will
	// get a runtime error caused by accessing a null value. This issue was already
	// reported at https://developercommunity.visualstudio.com/t/modules:-global-consts-are-zero-ed/10057491.
}