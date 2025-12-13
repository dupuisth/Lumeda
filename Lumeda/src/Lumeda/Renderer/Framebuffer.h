#pragma once

#include <Lumeda/Core/Base.h>

namespace Lumeda
{

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        virtual const std::string& GetName() const = 0;
    };
}