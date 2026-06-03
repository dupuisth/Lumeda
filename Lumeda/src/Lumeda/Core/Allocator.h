#pragma once

#include <cstddef>
#include <new>
#include <utility>

namespace Lumeda
{

void* EngineAllocRaw(std::size_t size, const char* file, int line);

void* EngineReAllocRaw(void* ptr, std::size_t size, const char* file, int line);

void EngineFreeRaw(void* p);

template <class T> T* Alloc(const char* file, int line)
{
    return static_cast<T*>(EngineAllocRaw(sizeof(T), file, line));
}

template <class T, class... Args> T* New(const char* file, int line, Args&&... args)
{
    void* mem = EngineAllocRaw(sizeof(T), file, line);
    try
    {
        return new (mem) T(std::forward<Args>(args)...);
    }
    catch (...)
    {
        EngineFreeRaw(mem);
        throw;
    }
}

template <class T> void Delete(T* p, const char* file, int line)
{
    if (!p)
        return;
    p->~T();
    EngineFreeRaw(p);
}

#define LUMEDA_FREE(ptr) Lumeda::Delete(ptr, __FILE__, __LINE__)
#define LUMEDA_ALLOC_RAW(size) Lumeda::EngineAllocRaw(size, __FILE__, __LINE__)
#define LUMEDA_REALLOC_RAW(ptr, size) Lumeda::EngineReAllocRaw(ptr, size, __FILE__, __LINE__)
#define LUMEDA_NEW(T, ...) Lumeda::New<T>(__FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__)
} // namespace Lumeda