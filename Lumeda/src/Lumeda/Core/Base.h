#pragma once

#include <memory>
#include <Lumeda/Core/Assert.h>
#include <Lumeda/Core/Log.h>
#include <Lumeda/Engine/EngineTypes.h>
#include <Lumeda/Profiling/Profiling.h>

#define LUMEDA_RANDINT(a, b) ((a) + (int)((double)rand() / (RAND_MAX + 1.0) * ((b) - (a))))
#define LUMEDA_RANDFLOAT(a, b) (((float)rand() / (float)(RAND_MAX)) * (b - a) + a)
