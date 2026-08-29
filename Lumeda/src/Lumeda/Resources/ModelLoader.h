#pragma once

#include <tinyxml2.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/ResourceLoader.h>

namespace Lumeda
{
class Resources;

struct sModelDefinition
{
  twString descriptorPath;

  tString name;
  tString geomtryFile;
  std::vector<tString> materialsName;
};

class ModelDefinitionXml
{
public:
  static sModelDefinition Read(const twString& path);
  static void Write(const sModelDefinition& definition, const twString& path);

private:
  inline static const char* ElementName = "Model";
  inline static const char* NameField = "Name";
  inline static const char* GeometryFileField = "Geometry";
  inline static const char* MaterialElement = "Material";
};

// Load a Model from its definition (xml)
class ModelLoader : public iResourceLoader
{
public:
  ModelLoader(Resources& resources) : iResourceLoader("ModelLoader"), m_Resources(resources) { AddSupportedExtensions(".model.xml"); }
  ~ModelLoader() = default;

  void PreLoad(const twString& path) override;
  void LoadPending() override;

private:
  Resources& m_Resources;

  std::vector<sModelDefinition> m_Pendings;
};
} // namespace Lumeda