#pragma once

#include <cstddef>
#include <utility>
#include <new>  

namespace Lumeda
{

    enum class MemTag : unsigned char
    {
        General,
        Assets,
        Renderer,
        Scene,
    };

    void* EngineAllocRaw(std::size_t size,
        std::size_t alignment,
        MemTag tag,
        const char* file,
        int line);

    void EngineFreeRaw(void* p);

    template <class T>
    T* Alloc(MemTag tag, const char* file, int line)
    {
        return static_cast<T*>(EngineAllocRaw(sizeof(T), alignof(T), tag, file, line));
    }

    template <class T, class... Args>
    T* New(MemTag tag, const char* file, int line, Args&&... args)
    {
        void* mem = EngineAllocRaw(sizeof(T), alignof(T), tag, file, line);
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

    template <class T>
    void Delete(T* p)
    {
        if (!p) return;
        p->~T();
        EngineFreeRaw(p);
    }


    #define LUMEDA_ALLOC(T, tag) Alloc<T>(tag, __FILE__, __LINE__)
    #define LUMEDA_NEW(T, tag, ...) New<T>(tag, __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__)

}