#pragma once

#include <tinyxml2.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/ResourceLoader.h>

namespace Lumeda
{
class Resources;

struct sMaterialUniformDefinition
{
  tString name;
  eShaderUniformType type;
  tString value;
  std::unordered_map<tString, tString> valueAttributes;
};

struct sMaterialDefinition
{
public:
  twString descriptorPath;

  tString name;
  tString gpuProgramName;

  std::vector<sMaterialUniformDefinition> uniforms;

public:
  static sMaterialDefinition FromMaterial(Material& material, Resources& resources);
};

class MaterialDefinitionXml
{
public:
  static sMaterialDefinition Read(const twString& path);
  static void Write(const sMaterialDefinition& definition, const twString& path);

private:
  inline static const char* ElementName = "Material";
  inline static const char* NameField = "Name";
  inline static const char* GpuProgramField = "GpuProgram";
  inline static const char* UniformElement = "Uniform";
  inline static const char* UniformNameField = "Name";
  inline static const char* UniformValueElement = "Value";
  inline static const char* UniformTypeField = "Type";
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