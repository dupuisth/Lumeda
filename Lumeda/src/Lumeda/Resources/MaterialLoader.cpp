#include <tinyxml2.h>
#include <unordered_map>
#include <Lumeda/Graphics/Material.h>
#include <Lumeda/Graphics/Texture.h>
#include <Lumeda/Resources/GpuProgramManager.h>
#include <Lumeda/Resources/MaterialLoader.h>
#include <Lumeda/Resources/MaterialManager.h>
#include <Lumeda/Resources/Resources.h>
#include <Lumeda/Resources/TextureManager.h>

using namespace Lumeda;
using namespace tinyxml2;

sMaterialDefinition MaterialDefinitionXml::Read(const twString& path)
{
  sMaterialDefinition definition;
  definition.descriptorPath = path;

  // Load the file
  XMLDocument xml;
  xml.LoadFile(path.c_str());

  // Get the main object
  XMLElement* node = xml.FirstChildElement();

  // Parse
  const char* name = node->FirstChildElement(NameField)->GetText();
  definition.name = name;

  const char* gpuProgram = node->FirstChildElement(GpuProgramField)->GetText();
  definition.gpuProgramName = gpuProgram;

  XMLElement* uniformNode = node->FirstChildElement(UniformElement);
  while (uniformNode != nullptr)
  {
    sMaterialUniformDefinition uniDefinition;

    const char* uniformName = uniformNode->Attribute(UniformNameField);
    uniDefinition.name = uniformName;

    int type = uniformNode->IntAttribute(UniformTypeField);
    uniDefinition.type = (eShaderUniformType)type;

    XMLElement* uniformValueNode = uniformNode->FirstChildElement(UniformValueElement);
    for (const XMLAttribute* attr = uniformValueNode->FirstAttribute(); attr != nullptr; attr = attr->Next())
    {
      const char* name = attr->Name();
      const char* value = attr->Value();
      uniDefinition.valueAttributes.insert({name, value});
    }
    const char* uniformValue = uniformValueNode->GetText();
    if (uniformValue != nullptr)
    {
      uniDefinition.value = uniformValue;
    }
    definition.uniforms.push_back(uniDefinition);

    uniformNode = uniformNode->NextSiblingElement(UniformElement);
  }

  return definition;
}

void MaterialDefinitionXml::Write(const sMaterialDefinition& definition, const twString& path)
{
  XMLDocument doc;

  XMLNode* root = doc.NewElement(ElementName);

  XMLElement* name = doc.NewElement(NameField);
  name->SetText(definition.name.c_str());
  root->InsertEndChild(name);

  XMLElement* gpuProgramElement = doc.NewElement(GpuProgramField);
  gpuProgramElement->SetText(definition.gpuProgramName.c_str());
  root->InsertEndChild(gpuProgramElement);

  for (const auto& uniform : definition.uniforms)
  {
    XMLElement* uniformElement = doc.NewElement(UniformElement);
    uniformElement->SetAttribute(UniformNameField, uniform.name.c_str());
    uniformElement->SetAttribute(UniformTypeField, (int)uniform.type);

    XMLElement* uniformValueElement = doc.NewElement(UniformValueElement);
    for (const auto& attribute : uniform.valueAttributes)
    {
      uniformValueElement->SetAttribute(attribute.first.c_str(), attribute.second.c_str());
    }
    uniformValueElement->SetText(uniform.value.c_str());
    uniformElement->InsertEndChild(uniformValueElement);

    root->InsertEndChild(uniformElement);
  }

  doc.InsertFirstChild(root);

  doc.SaveFile(path.c_str());
}

sMaterialDefinition sMaterialDefinition::FromMaterial(Material& material, Resources& resources)
{
  sMaterialDefinition definition = {.name = material.GetName()};

  if (material.GetProgram() != nullptr)
  {
    definition.gpuProgramName = material.GetProgram()->GetName();
  }
  else
  {
    definition.gpuProgramName = "";
  }

  // mat3 and mat4 are not supported yet,
  // since for now there are no real use case of those.
  UniformMap& uniforms = material.GetUniformMap();
  for (const auto& floatUni : uniforms.GetUniformsFloat())
  {
    definition.uniforms.push_back({
        .name = floatUni.first,
        .type = eShaderUniformType_Float,
        .value = std::to_string(floatUni.second),
    });
  }
  for (const auto& vec2Uni : uniforms.GetUniformsVec2())
  {
    sMaterialUniformDefinition uniDefinition = {.name = vec2Uni.first,
        .type = eShaderUniformType_Vec2,
        .value = "",
        .valueAttributes = {{"x", std::to_string(vec2Uni.second.x)}, {"y", std::to_string(vec2Uni.second.y)}}};
    definition.uniforms.push_back(uniDefinition);
  }
  for (const auto& vec3Uni : uniforms.GetUniformsVec3())
  {
    sMaterialUniformDefinition uniDefinition = {.name = vec3Uni.first,
        .type = eShaderUniformType_Vec3,
        .value = "",
        .valueAttributes = {
            {"x", std::to_string(vec3Uni.second.x)}, {"y", std::to_string(vec3Uni.second.y)}, {"z", std::to_string(vec3Uni.second.z)}}};
    definition.uniforms.push_back(uniDefinition);
  }
  for (const auto& vec4Uni : uniforms.GetUniformsVec4())
  {
    sMaterialUniformDefinition uniDefinition = {.name = vec4Uni.first,
        .type = eShaderUniformType_Vec4,
        .value = "",
        .valueAttributes = {{"x", std::to_string(vec4Uni.second.x)},
            {"y", std::to_string(vec4Uni.second.y)},
            {"z", std::to_string(vec4Uni.second.z)},
            {"w", std::to_string(vec4Uni.second.w)}}};
    definition.uniforms.push_back(uniDefinition);
  }
  for (const auto& textureUni : uniforms.GetUniformsTexture())
  {
    iTexture* texture = textureUni.second;
    tString value = texture != nullptr ? texture->GetName() : "";

    definition.uniforms.push_back({
        .name = textureUni.first,
        .type = eShaderUniformType_Texture2D,
        .value = value,
    });
  }

  return definition;
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
    Material* material = m_Resources.GetMaterialManager().CreateMaterial(definition.name);
    material->SetPath(definition.descriptorPath);

    iGpuProgram* gpuProgram = m_Resources.GetGpuProgramManager().GetResourceByName(definition.gpuProgramName);
    material->SetProgram(gpuProgram);

    for (const auto& uni : definition.uniforms)
    {

      if (uni.type == eShaderUniformType_Texture2D)
      {
        iTexture* texture = m_Resources.GetTextureManager().GetResourceByName(uni.value);
        material->GetUniformMap().SetUniform(uni.name, texture);
      }
      else if (uni.type == eShaderUniformType_Float)
      {
        material->GetUniformMap().SetUniform(uni.name, std::stof(uni.value));
      }
      else if (uni.type == eShaderUniformType_Vec2)
      {
        material->GetUniformMap().SetUniform(uni.name, glm::vec2(std::stof(uni.valueAttributes.at("x")), std::stof(uni.valueAttributes.at("y"))));
      }
      else if (uni.type == eShaderUniformType_Vec3)
      {
        material->GetUniformMap().SetUniform(uni.name,
            glm::vec3(std::stof(uni.valueAttributes.at("x")), std::stof(uni.valueAttributes.at("y")), std::stof(uni.valueAttributes.at("z"))));
      }
      else if (uni.type == eShaderUniformType_Vec4)
      {
        material->GetUniformMap().SetUniform(uni.name,
            glm::vec4(std::stof(uni.valueAttributes.at("x")),
                std::stof(uni.valueAttributes.at("y")),
                std::stof(uni.valueAttributes.at("z")),
                std::stof(uni.valueAttributes.at("w"))));
      }
    }
  }
  m_Pendings.clear();
}