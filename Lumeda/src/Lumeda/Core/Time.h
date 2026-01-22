#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{
    class Time
    {
    public:
        virtual ~Time() = default;
        virtual void Tick() = 0;

        virtual float GetPreciseTime() = 0;
        virtual float GetTime() = 0;
        virtual float GetDeltaTime() = 0;
        virtual size_t GetFrameCount() = 0;

        static Time* Create();
    };
}