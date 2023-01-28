#pragma once

#include "TimeUtil.h"

#if defined(_DEBUG)
#define LOG(format, ...)\
		do{\
			char _buffer[256];\
			int _res = snprintf(_buffer, std::size(_buffer), "{%.3f}: "##format##"\n", BTEngine::Core::TimeUtil::GetTime(), __VA_ARGS__);\
			OutputDebugStringA(_buffer);\
		}while(false)\

#define ASSERT(condition, format, ...)\
	do{\
		if(!(condition), format, ...)\
			{\
				LOG("ASSERT! %s(%d)\n"##format##, __FILE__, __LINE__, __VA__ARGS__);\
			}\
	}while(false)
#else
#define LOG(format, ...)
#define ASSET(condition, format, ...) do{(void)sizeof(condition);}while(false)
#endif