#include <tinyxml2.h>
#include <Lumeda/Graphics/Model.h>
#include <Lumeda/Resources/MaterialManager.h>
#include <Lumeda/Resources/ModelLoader.h>
#include <Lumeda/Resources/ModelManager.h>
#include <Lumeda/Resources/Resources.h>

using namespace Lumeda;
using namespace tinyxml2;

sModelDefinition ModelDefinitionXml::Read(const twString& path)
{
  sModelDefinition definition;
  definition.descriptorPath = path;

  XMLDocument xml;
  xml.LoadFile(path.c_str());

  // Get the main object
  XMLElement* node = xml.FirstChildElement();

  // Parse
  const char* name = node->FirstChildElement(NameField)->GetText();
  definition.name = name;

  const char* geometryfile = node->FirstChildElement(GeometryFileField)->GetText();
  definition.geomtryFile = geometryfile;

  XMLElement* materialElement = node->FirstChildElement(MaterialElement);
  while (materialElement != nullptr)
  {
    const char* materialName = materialElement->GetText();
    definition.materialsName.push_back(materialName);

    materialElement = materialElement->NextSiblingElement(MaterialElement);
  }

  return definition;
}

void ModelDefinitionXml::Write(const sModelDefinition& definition, const twString& path)
{
  XMLDocument doc;

  XMLNode* root = doc.NewElement(ElementName);

  XMLElement* name = doc.NewElement(NameField);
  name->SetText(definition.name.c_str());
  root->InsertEndChild(name);

  XMLElement* geometryFileElement = doc.NewElement(GeometryFileField);
  geometryFileElement->SetText(definition.geomtryFile.c_str());
  root->InsertEndChild(geometryFileElement);

  for (const auto& materialName : definition.materialsName)
  {
    XMLElement* materialElement = doc.NewElement(MaterialElement);
    materialElement->SetText(materialName.c_str());
    root->InsertEndChild(materialElement);
  }
  doc.InsertFirstChild(root);

  doc.SaveFile(path.c_str());
}

void ModelLoader::PreLoad(const twString& path)
{
  // Load the definition
  sModelDefinition definition = ModelDefinitionXml::Read(path);

  // Store it
  m_Pendings.push_back(definition);
}

void ModelLoader::LoadPending()
{
  for (const auto& definition : m_Pendings)
  {
    Model* model = m_Resources.GetModelManager().CreateModel(definition.name, definition.geomtryFile);
    // Update the path with the definition one (not the geometry)
    model->SetPath(definition.descriptorPath);

    for (int i = 0; i < definition.materialsName.size(); i++)
    {
      Material* material = m_Resources.GetMaterialManager().GetResourceByName(definition.materialsName[i]);
      if (i >= model->GetMaterials().size())
      {
        LUMEDA_CORE_WARN("[ModelLoader] Model definition have more materials than the loaded model");
        model->GetMaterials().push_back(material);
      }
      else
      {
        model->GetMaterials()[i] = material;
      }
    }
  }
  m_Pendings.clear();
}