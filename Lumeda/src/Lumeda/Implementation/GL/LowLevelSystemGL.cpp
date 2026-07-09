#include <Lumeda/Implementation/GL/LowLevelSystemGL.h>

using namespace Lumeda;

///////////////////////////////////////////
// Entry point
///////////////////////////////////////////
extern int lumedaMain();

#ifdef WIN32
#error "Not ready for this!"
#else
int main(int argc, char* argv[])
{
  return lumedaMain();
}
#endif
//---------------------------------------//
