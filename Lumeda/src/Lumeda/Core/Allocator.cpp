#include <Lumeda/Core/Allocator.h>

using namespace Lumeda;

#include <Lumeda/Core/Base.h>

#include <cstdlib>
#include <new>

#ifdef _MSC_VER
#include <malloc.h>
#endif

void* Lumeda::EngineAllocRaw(std::size_t size,
    std::size_t alignment,
    MemTag,
    const char*,
    int)
{
#ifdef _MSC_VER
    void* ptr = _aligned_malloc(size, alignment);
#else
    void* ptr = std::aligned_alloc(alignment, ((size + alignment - 1) / alignment) * alignment);
#endif
    LUMEDA_PROFILE_MEMORY_ALLOC(ptr, size);
    return ptr;
}

void Lumeda::EngineFreeRaw(void* p)
{

#ifdef _MSC_VER
    _aligned_free(p);
#else
    free(p);
#endif
    LUMEDA_PROFILE_MEMORY_FREE(p);
}