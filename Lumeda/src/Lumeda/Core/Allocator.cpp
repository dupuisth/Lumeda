#include <Lumeda/Core/Allocator.h>

using namespace Lumeda;

#include <Lumeda/Core/Base.h>

#include <cstdlib>
#include <new>

#ifdef _MSC_VER
#include <malloc.h>
#endif

void* Lumeda::EngineAllocRaw(std::size_t size,
    const char* file,
    int line)
{
    void* ptr = malloc(size);
    LUMEDA_PROFILE_MEMORY_ALLOC(ptr, size);
    return ptr;
}

void* Lumeda::EngineReAllocRaw(void* ptr, std::size_t size, const char* file, int line)
{
    // For now, lie to the profiler
    LUMEDA_PROFILE_MEMORY_FREE(ptr);
    ptr = realloc(ptr, size);
    LUMEDA_PROFILE_MEMORY_ALLOC(ptr, size);
    return ptr;
}

void Lumeda::EngineFreeRaw(void* p)
{
    free(p);
    LUMEDA_PROFILE_MEMORY_FREE(p);
}