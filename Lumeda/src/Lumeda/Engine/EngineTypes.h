#pragma once

#include <string>

namespace Lumeda
{
typedef std::string tString;
typedef std::wstring twString;

// Default flag type
typedef unsigned int tFlag;

///////////////////////////////////////////
// Engine backend
///////////////////////////////////////////
enum eLumedaBackend
{
    eLumedaBackend_OpenGL = 0
};

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

} // namespace Lumeda
