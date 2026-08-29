#pragma once

#include <tinyxml2.h>
#include <Lumeda/Core/Base.h>
#include <Lumeda/Resources/ResourceLoader.h>

namespace Lumeda
{
class Resources;

struct sTextureDefinition
{
  twString descriptorPath;

  tString name;
  tString file;
  eTextureFiltering filtering;
  eTextureWrapping wrapping;
};

class TextureDefinitionXml
{
public:
  static sTextureDefinition Read(const twString& path);
  static void Write(const sTextureDefinition& definition, const twString& path);

private:
  inline static const char* ElementName = "Texture";
  inline static const char* NameField = "Name";
  inline static const char* FileField = "File";
  inline static const char* FilteringField = "Filtering";
  inline static const char* WrappingField = "Wrapping";
};

// Load a texture from its definition (xml)
class TextureLoader : public iResourceLoader
{
public:
  TextureLoader(Resources& resources) : iResourceLoader("TextureLoader"), m_Resources(resources) { AddSupportedExtensions(".texture.xml"); }
  ~TextureLoader() = default;

  void PreLoad(const twString& path) override;
  void LoadPending() override;

private:
  Resources& m_Resources;

  std::vector<sTextureDefinition> m_Pendings;
};
} // namespace Lumeda