#include <tinyxml2.h>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Resources/MaterialLoader.h>
#include <Lumeda/Resources/MaterialManager.h>
#include <Lumeda/Resources/Resources.h>

using namespace Lumeda;
using namespace tinyxml2;

sMaterialDefinition MaterialDefinitionXml::Read(const twString& path)
{
  // Load the file
  XMLDocument xml;
  xml.LoadFile(path.c_str());

  // Get the main object
  XMLElement* node = xml.FirstChildElement();

  // Parse
  const char* name = node->FirstChildElement(NameField)->GetText();

  // Create the definition
  sMaterialDefinition definition = {.descriptorPath = path, .name = name};

  return definition;
}

void MaterialDefinitionXml::Write(const sMaterialDefinition& definition, const twString& path)
{
  XMLDocument doc;

  XMLNode* root = doc.NewElement(ElementName);

  XMLElement* name = doc.NewElement(NameField);
  name->SetText(definition.name.c_str());
  root->InsertEndChild(name);

  doc.InsertFirstChild(root);

  doc.SaveFile(path.c_str());
}

void MaterialLoader::PreLoad(const twString& path)
{
  // Load the definition
  sMaterialDefinition definition = MaterialDefinitionXml::Read(path);

  // Store it
  m_Pendings.push_back(definition);
}

void MaterialLoader::LoadPending()
{
  for (const auto& definition : m_Pendings)
  {
  }
  m_Pendings.clear();
}