#include <filesystem>
#include <iostream>

import Constants;

/*
Problem Description: An internal compiler error (ICE) is triggered when initializing a static const
std::filesystem::path instance with a constexpr value exported by another module. This occurs regardless
of where the std::filesystem::path instance is being created.

The scariest part of this ICE is that it doesn't always print out the correct name of the file which triggers
it. In a much larger project, it was printing out the name of a completely unrelated file. (You can imagine
how much of a nightmare debugging that was.) In this small re-production repository, however, it seems to
identify line #714 of the MSVC STL's <filesystem> header as being the cause of the bug in the Release mode,
but it identifies Constants.ixx in the Debug mode.

Reproduction Steps:
	1. Ensure that the "Whole Program Optimization" setting is enabled for the project. This is on by default
	   for Release builds, but for this re-production repository, I also enabled it for Debug builds.

	2. Build the project as usual. The ICE should occur.

Workaround: To "workaround" this issue, one must disable Whole Program Optimizations. Simply making the
exported values will result in zeroed values, as described in the bug report at
https://developercommunity.visualstudio.com/t/modules:-global-consts-are-zero-ed/10057491.
*/

namespace
{
	static const std::filesystem::path testFilePath{ TEST_FILE_NAME };  // < This line breaks it.
}

int main(const int argc, const char* const argv[])
{
	static const std::filesystem::path otherFilePath{ OTHER_TEST_FILE_NAME };  // < This line also breaks it.
	
	if (std::filesystem::exists(testFilePath) || std::filesystem::exists(otherFilePath)) [[unlikely]]
		std::cout << "You came prepared, didn't you?" << std::endl;

	return 0;
}