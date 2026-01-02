#include <Lumeda/Renderer/Material.h>

using namespace Lumeda;

Material::Material(const std::string& name) : m_Name(name), m_Shader(), m_UniformsMap()
{
	LUMEDA_PROFILE;
}


Material::~Material()
{
	LUMEDA_PROFILE;
}

void Material::Use()
{
	LUMEDA_PROFILE;

	if (m_Shader == nullptr)
	{
		LUMEDA_CORE_WARN("[Material] Trying to use a material with no shader assigned");
		return;
	}

	m_Shader->Bind();
	m_UniformsMap.Send(m_Shader);
}

void Material::Use(sUniformsMap& uniformsMap)
{
	LUMEDA_PROFILE;

	if (m_Shader == nullptr)
	{
		LUMEDA_CORE_WARN("[Material] Trying to use a material with no shader assigned");
		return;
	}

	m_Shader->Bind();
	m_UniformsMap.Send(m_Shader);
	uniformsMap.Send(m_Shader);
}


void Material::SetShader(Shader* shader)
{
	LUMEDA_PROFILE;
	m_Shader = shader;
}

sUniformsMap& Material::GetUniformsMap()
{
	LUMEDA_PROFILE;
	return m_UniformsMap;
}

const std::string& Material::GetName()
{
	LUMEDA_PROFILE;
	return m_Name;
}