#pragma once

#include <string>

namespace Lumeda
{
typedef std::string tString;

#ifdef LUMEDA_USE_WIDE_STRING
typedef std::wstring twString;
#define _W(t) L##t
#else
typedef std::string twString;
#define _W(t) t
#endif

// Default flag type
typedef unsigned int tFlag;

///////////////////////////////////////////
// Engine backend
///////////////////////////////////////////
enum eLumedaBackend
{
  eLumedaBackend_OpenGL = 0
};
//---------------------------------------//

///////////////////////////////////////////
// Updateable
///////////////////////////////////////////
enum eUpdateableMessage
{
  eUpdateableMessage_OnStart,

  eUpdateableMessage_OnPreDraw,
  eUpdateableMessage_OnDraw,
  eUpdateableMessage_OnPostDraw,

  eUpdateableMessage_PreUpdate,
  eUpdateableMessage_Update,
  eUpdateableMessage_PostUpdate,

  eUpdateableMessage_Reset,
};
//---------------------------------------//

///////////////////////////////////////////
// Events
///////////////////////////////////////////

typedef unsigned int tEventCategory;
typedef unsigned int tEventType;

// All the categories of events
enum eEventCategory
{
  eEventCategory_Engine = 0,
  eEventCategory_System = 1000,
  eEventCategory_Graphics = 2000,
  eEventCategory_User = 10000,
};

// Events for the Engine category
enum eEngineEvent
{
  eEngineEvent_FirstEnum = eEventCategory_Engine,
  // { ... }
  eEngineEvent_LastEnum,
};

class iEvent
{
public:
  virtual ~iEvent() = default;

  virtual tEventType GetType() = 0;

  virtual tString ToString() { return ""; };

  bool Handled;
};
//---------------------------------------//

} // namespace Lumeda
