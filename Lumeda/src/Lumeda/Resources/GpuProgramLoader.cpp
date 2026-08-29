#include <tinyxml2.h>
#include <Lumeda/Graphics/GpuProgram.h>
#include <Lumeda/Graphics/GpuShader.h>
#include <Lumeda/Resources/GpuProgramLoader.h>
#include <Lumeda/Resources/GpuProgramManager.h>
#include <Lumeda/Resources/GpuShaderManager.h>
#include <Lumeda/Resources/Resources.h>

using namespace Lumeda;
using namespace tinyxml2;

sGpuProgramDefinition GpuProgramDefinitionXml::Read(const twString& path)
{
  // Load the file
  XMLDocument xml;
  xml.LoadFile(path.c_str());

  // Get the main object
  XMLElement* node = xml.FirstChildElement();

  // Parse
  const char* name = node->FirstChildElement(NameField)->GetText();
  const char* vertex = node->FirstChildElement(VertexFileField)->GetText();
  const char* fragment = node->FirstChildElement(FragFileField)->GetText();

  // Create the definition
  sGpuProgramDefinition definition = {.descriptorPath = path, .name = name, .vertexFilePath = vertex, .fragmentFilePath = fragment};

  return definition;
}

void GpuProgramDefinitionXml::Write(const sGpuProgramDefinition& definition, const twString& path)
{
  XMLDocument doc;

  XMLNode* root = doc.NewElement(ElementName);

  XMLElement* name = doc.NewElement(NameField);
  name->SetText(definition.name.c_str());
  root->InsertEndChild(name);

  XMLElement* vertex = doc.NewElement(VertexFileField);
  vertex->SetText(definition.vertexFilePath.c_str());
  root->InsertEndChild(vertex);

  XMLElement* fragment = doc.NewElement(FragFileField);
  fragment->SetText(definition.fragmentFilePath.c_str());
  root->InsertEndChild(fragment);

  doc.InsertFirstChild(root);

  doc.SaveFile(path.c_str());
}

void GpuProgramLoader::PreLoad(const twString& path)
{
  // Load the definition
  sGpuProgramDefinition definition = GpuProgramDefinitionXml::Read(path);

  // Store it
  m_Pendings.push_back(definition);
}

void GpuProgramLoader::LoadPending()
{
  // First pass, load all the shaders
  for (const auto& definition : m_Pendings)
  {
    tString vertexName = definition.vertexFilePath;
    iGpuShader* vertexShader = m_Resources.GetGpuShaderManager().CreateShader(vertexName, definition.vertexFilePath, eShaderType_Vertex);
    vertexShader->CreateFromFile(definition.vertexFilePath);

    tString fragmentName = definition.fragmentFilePath;
    iGpuShader* fragmentShader = m_Resources.GetGpuShaderManager().CreateShader(fragmentName, definition.fragmentFilePath, eShaderType_Fragment);
    fragmentShader->CreateFromFile(definition.fragmentFilePath);
  }

  // Second pass, load the programs
  for (const auto& definition : m_Pendings)
  {
    tString vertexName = definition.vertexFilePath;
    iGpuShader* vertexShader = m_Resources.GetGpuShaderManager().GetResourceByName(vertexName);

    tString fragmentName = definition.fragmentFilePath;
    iGpuShader* fragmentShader = m_Resources.GetGpuShaderManager().GetResourceByName(fragmentName);

    iGpuProgram* program = m_Resources.GetGpuProgramManager().CreateProgram(definition.name);
    program->AttachShader(vertexShader);
    program->AttachShader(fragmentShader);
    program->Link();
  }
  m_Pendings.clear();
}