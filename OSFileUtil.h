#pragma once
#ifndef BOUNTIVE_OSFILEUTIL
#define BOUNTIVE_OSFILEUTIL

#ifdef _WIN32
#include "WindowsFileUtil.h"
#ifdef _WIN64
#include "WindowsFileUtil.h"
#else
#endif
#elif __APPLE__
#if TARGET_OS_MAC
#include "MacFileUtil.h"
#else
#endif
#elif __linux__
#include "LinuxFileUtil.h"
#elif __unix__
#include "LinuxFileUtil.h"
#elif defined(_POST_VERSION)
#else
#endif

#endif