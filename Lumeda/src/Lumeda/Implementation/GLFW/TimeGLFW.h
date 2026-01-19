#include <Lumeda/Core/Base.h>

#include <Lumeda/Core/Time.h>

#include <GLFW/glfw3.h>

namespace Lumeda
{
    class TimeGLFW : public Time
    {
    public:
        TimeGLFW();
        virtual ~TimeGLFW();

        void Tick() override;
        float GetTime() override;
        float GetPreciseTime() override;
        float GetDeltaTime() override;
        size_t GetFrameCount() override;

    private:
        float m_PreviousTime;
        size_t m_FrameCount;
        float m_DeltaTime;
        float m_time;
    };
}