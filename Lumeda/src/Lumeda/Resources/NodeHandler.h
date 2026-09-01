#pragma once

#include <tinyxml2.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Engine/Updateable.h>
#include <Lumeda/Scene/LeafNode.h>

namespace Lumeda
{
class iLeafNodeDescription
{
public:
  iLeafNodeDescription(const tString& typeId, const tString& name, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) :
      m_TypeId(typeId), m_Name(name), m_LocalPosition(position), m_LocalRotation(rotation), m_LocalScale(scale)
  {
  }

  const tString& GetName() const { return m_Name; }

  const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
  const glm::quat& GetLocalRotation() const { return m_LocalRotation; }
  const glm::vec3& GetLocalScale() const { return m_LocalScale; }

  const tString& GetTypeId() const { return m_TypeId; }

private:
  tString m_TypeId;
  tString m_Name;

  glm::vec3 m_LocalPosition;
  glm::quat m_LocalRotation;
  glm::vec3 m_LocalScale;
};

class iNodeHandler : public iUpdateable
{
public:
  iNodeHandler(const tString& name) : iUpdateable(name) {}
  virtual ~iNodeHandler() = default;

  virtual bool CanHandleType(const tString& type) { return type == GetHandlerTypeId(); }
  virtual tString GetHandlerTypeId() const = 0;

  /// @brief Returns a unique_ptr to the parsed node
  virtual std::unique_ptr<iLeafNodeDescription> Read(tinyxml2::XMLElement& element) = 0;

  /// @brief Returns the serialized node (not added to the document)
  virtual tinyxml2::XMLElement* Write(tinyxml2::XMLDocument& document, LeafNode& node) = 0;

protected:
  virtual tinyxml2::XMLElement* CreateDefaultElement(tinyxml2::XMLDocument& document, LeafNode& node);

protected:
  inline static const tString TypeAttributeName = "Type";
  inline static const tString NameAttributeName = "Name";
  inline static const tString LocalPositionElementName = "LocalPosition";
  inline static const tString LocalRotationElementName = "LocalRotation";
  inline static const tString LocalScaleElementName = "LocalScale";
};
} // namespace Lumeda