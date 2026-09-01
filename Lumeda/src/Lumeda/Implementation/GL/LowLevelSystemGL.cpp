#include <GLFW/glfw3.h>
#include <Lumeda/Implementation/GL/LowLevelSystemGL.h>

using namespace Lumeda;

///////////////////////////////////////////
// Entry point
///////////////////////////////////////////
extern int lumedaMain();

#ifdef WIN32
int main(int argc, char* argv[])
{
  return lumedaMain();
}
#else
int main(int argc, char* argv[])
{
  return lumedaMain();
}
#endif
//---------------------------------------//

float LowLevelSystemGL::GetElapsedTime()
{
  return static_cast<float>(glfwGetTime());
}
