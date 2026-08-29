#pragma once

#include <tinyxml2.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/ResourceLoader.h>

namespace Lumeda
{
class Resources;

struct sGpuProgramDefinition
{
  twString descriptorPath;

  tString name;
  tString vertexFilePath;
  tString fragmentFilePath;
};

class GpuProgramDefinitionXml
{
public:
  static sGpuProgramDefinition Read(const twString& path);
  static void Write(const sGpuProgramDefinition& definition, const twString& path);

private:
  inline static const char* ElementName = "GpuProgram";
  inline static const char* NameField = "Name";
  inline static const char* VertexFileField = "Vertex";
  inline static const char* FragFileField = "Fragment";
};

// Load a texture from its definition (xml)
class GpuProgramLoader : public iResourceLoader
{
public:
  GpuProgramLoader(Resources& resources) : iResourceLoader("GpuProgramLoader"), m_Resources(resources) { AddSupportedExtensions(".gpuprogram.xml"); }
  ~GpuProgramLoader() = default;

  void PreLoad(const twString& path) override;
  void LoadPending() override;

private:
  tString GetNameFromGpuShader(const twString& path) { return path; }

private:
  Resources& m_Resources;

  std::vector<sGpuProgramDefinition> m_Pendings;
};
} // namespace Lumeda