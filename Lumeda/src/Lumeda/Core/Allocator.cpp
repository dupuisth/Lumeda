#include <Lumeda/Core/Allocator.h>

using namespace Lumeda;

#include <Lumeda/Core/Base.h>
#include <cstdlib>
#include <new>

#ifdef _MSC_VER
#include <malloc.h>
#endif

void* Lumeda::EngineAllocRaw(std::size_t size, const char* file, int line)
{
    void* ptr = malloc(size);
    if (ptr == nullptr)
    {
        // Failed to allocate the given ammount
        LUMEDA_CORE_ERROR("[Allocator] allocation failed for size={0}", size);
        return ptr;
    }
    // Allocation success
    LUMEDA_PROFILE_MEMORY_ALLOC(ptr, size);
    return ptr;
}

void* Lumeda::EngineReAllocRaw(void* ptr, std::size_t size, const char* file, int line)
{
    void* newPtr = realloc(ptr, size);
    if (newPtr != nullptr)
    {
        LUMEDA_PROFILE_MEMORY_FREE(ptr);
        LUMEDA_PROFILE_MEMORY_ALLOC(newPtr, size);
        return newPtr;
    }

    // Failed to reallocate, the old pointer still exists
    LUMEDA_CORE_ERROR("[Allocator] realloc failed for size={0}", size);
    return nullptr;
}

void Lumeda::EngineFreeRaw(void* p)
{
    LUMEDA_PROFILE_MEMORY_FREE(p);
    free(p);
}