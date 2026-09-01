#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>

namespace Lumeda
{
struct sWorldDefinition
{
};

class WorldDefinitionXml
{
public:
  static sWorldDefinition Read(const twString& path);
  static void Write(const sWorldDefinition& definition, const twString& path);
};

class WorldHandler : public iUpdateable
{
public:
  WorldHandler() : iUpdateable("WorldHandler") {}
  ~WorldHandler() = default;
};
} // namespace Lumeda