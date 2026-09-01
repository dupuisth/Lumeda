#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Resources/NodeHandler.h>
#include <Lumeda/Scene/World.h>

namespace Lumeda
{

class WorldHandler : public iUpdateable
{
public:
  WorldHandler() : iUpdateable("WorldHandler") {}
  ~WorldHandler() = default;

  ///////////////////////////////////////////
  // Handlers
  ///////////////////////////////////////////
  void PushHandler(std::unique_ptr<iNodeHandler> nodeHandler) { m_NodeHandlers.push_back(std::move(nodeHandler)); }
  const std::vector<std::unique_ptr<iNodeHandler>>& GetHandlers() { return m_NodeHandlers; }

  void WriteWorld(World& world, const tString& path);

private:
  std::vector<std::unique_ptr<iNodeHandler>> m_NodeHandlers;
};
} // namespace Lumeda