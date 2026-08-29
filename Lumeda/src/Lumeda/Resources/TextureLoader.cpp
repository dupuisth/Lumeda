#include <tinyxml2.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Resources/Resources.h>
#include <Lumeda/Resources/TextureLoader.h>
#include <Lumeda/Resources/TextureManager.h>

using namespace Lumeda;
using namespace tinyxml2;

sTextureDefinition TextureDefinitionXml::Read(const twString& path)
{
  XMLDocument xml;
  xml.LoadFile(path.c_str());

  // Get the main object
  XMLElement* node = xml.FirstChildElement();

  // Parse
  const char* name = node->FirstChildElement(NameField)->GetText();
  const char* file = node->FirstChildElement(FileField)->GetText();
  int filtering = node->FirstChildElement(FilteringField)->IntText();
  int wrapping = node->FirstChildElement(WrappingField)->IntText();

  eTextureFiltering filteringCasted = (eTextureFiltering)filtering;
  eTextureWrapping wrappingCasted = (eTextureWrapping)wrapping;

  sTextureDefinition definition = {.descriptorPath = path, .name = name, .file = file, .filtering = filteringCasted, .wrapping = wrappingCasted};

  return definition;
}

void TextureDefinitionXml::Write(const sTextureDefinition& definition, const twString& path)
{
  XMLDocument doc;

  XMLNode* root = doc.NewElement(ElementName);

  XMLElement* name = doc.NewElement(NameField);
  name->SetText(definition.name.c_str());
  root->InsertEndChild(name);

  XMLElement* file = doc.NewElement(FileField);
  file->SetText(definition.file.c_str());
  root->InsertEndChild(file);

  XMLElement* filtering = doc.NewElement(FilteringField);
  filtering->SetText((int)definition.filtering);
  root->InsertEndChild(filtering);

  XMLElement* wrapping = doc.NewElement(WrappingField);
  wrapping->SetText((int)definition.wrapping);
  root->InsertEndChild(wrapping);

  doc.InsertFirstChild(root);

  doc.SaveFile(path.c_str());
}

void TextureLoader::PreLoad(const twString& path)
{
  // Load the definition
  sTextureDefinition definition = TextureDefinitionXml::Read(path);

  // Store it
  m_Pendings.push_back(definition);
}

void TextureLoader::LoadPending()
{
  for (const auto& definition : m_Pendings)
  {
    // Keep only Texture2D for now.
    iTexture* texture = m_Resources.GetTextureManager().CreateTexture(definition.name, eTextureType_2D);
    texture->CreateFromFile(definition.file);
    texture->SetFiltering(definition.filtering);
    texture->SetWrapping(definition.wrapping);
  }
  m_Pendings.clear();
}