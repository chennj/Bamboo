#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "bamboo/core/Log.h"

#include "bamboo/debug/Instrumentor.h"

#ifdef BB_PLATFORM_WINDOWS
#include <Windows.h>
#endif