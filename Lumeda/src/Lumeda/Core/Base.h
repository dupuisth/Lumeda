#pragma once

#ifdef LUMEDA_PLATFORM_WINDOWS
	#ifdef LUMEDA_BUILD_DLL
		#define LUMEDA_API __declspec(dllexport)
	#else
		#define LUMEDA_API __declspec(dllimport)
	#endif
#else
	#error Windows only for now
#endif

