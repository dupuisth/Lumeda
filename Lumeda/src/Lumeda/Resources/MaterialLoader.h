#pragma once

#include <tinyxml2.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/ResourceLoader.h>

namespace Lumeda
{
class Resources;

struct sMaterialDefinition
{
  twString descriptorPath;

  tString name;
};

class MaterialDefinitionXml
{
public:
  static sMaterialDefinition Read(const twString& path);
  static void Write(const sMaterialDefinition& definition, const twString& path);

private:
  inline static const char* ElementName = "Material";
  inline static const char* NameField = "Name";
};

// Load a texture from its definition (xml)
class MaterialLoader : public iResourceLoader
{
public:
  MaterialLoader(Resources& resources) : iResourceLoader("MaterialLoader"), m_Resources(resources) { AddSupportedExtensions(".material.xml"); }
  ~MaterialLoader() = default;

  void PreLoad(const twString& path) override;
  void LoadPending() override;

private:
  Resources& m_Resources;

  std::vector<sMaterialDefinition> m_Pendings;
};
} // namespace Lumeda