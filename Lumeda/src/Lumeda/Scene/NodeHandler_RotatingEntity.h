#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/NodeHandler.h>
#include <Lumeda/Scene/RotatingEntity.h>

namespace Lumeda
{
class RotatingEntityDefinition : public iLeafNodeDescription
{
public:
  RotatingEntityDefinition(const tString& name,
      const glm::vec3& position,
      const glm::quat& rotation,
      const glm::vec3& scale,
      const glm::vec3& rotating) :
      iLeafNodeDescription(RotatingEntity::TypeId, name, position, rotation, scale), m_Rotating(rotating)
  {
  }

  const glm::vec3& GetRotating() const { return m_Rotating; }

private:
  glm::vec3 m_Rotating;
};

class RotatingEntityHandler : public iNodeHandler
{
public:
  RotatingEntityHandler() : iNodeHandler("RotatingEntityHandler") {}
  ~RotatingEntityHandler() = default;

  tString GetHandlerTypeId() const { return RotatingEntity::TypeId; }

  std::unique_ptr<iLeafNodeDescription> Read(tinyxml2::XMLElement& element) override;
  tinyxml2::XMLElement* Write(tinyxml2::XMLDocument& document, LeafNode& node) override;

private:
  inline static const tString RotatingElementName = "Rotating";
};
} // namespace Lumeda