#include <Lumeda/Renderer/Material.h>

using namespace Lumeda;

Material::Material(const std::string& name) : m_Name(name), m_Shader()
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

	// Simple macro to assign basics uniforms (int, float, vec, mat)
	#define BASIC_ASSIGNATION(map) 	for (const auto& [uniform, value] : map) m_Shader->SetUniform(uniform, value);
	BASIC_ASSIGNATION(m_IntMap);
	BASIC_ASSIGNATION(m_FloatMap);
	BASIC_ASSIGNATION(m_Vec2Map);
	BASIC_ASSIGNATION(m_Vec3Map);
	BASIC_ASSIGNATION(m_Vec4Map);
	BASIC_ASSIGNATION(m_Mat2Map);
	BASIC_ASSIGNATION(m_Mat3Map);
	BASIC_ASSIGNATION(m_Mat4Map);

	// Assign textures
	int textureSlot = 0;
	for (const auto& [uniform, value] : m_TextureMap)
	{
		value->Bind(textureSlot);
		m_Shader->SetUniform(uniform, textureSlot);
		textureSlot += 1;
	}
}

void Material::SetShader(std::shared_ptr<Shader> shader)
{
	LUMEDA_PROFILE;
	m_Shader = shader;
}

void Material::SetUniform(const std::string& uniform, int value)
{
	LUMEDA_PROFILE;
	m_IntMap[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, float value)
{
	LUMEDA_PROFILE;
	m_FloatMap[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, const glm::vec2& value)
{
	LUMEDA_PROFILE;
	m_Vec2Map[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, const glm::vec3& value)
{
	LUMEDA_PROFILE;
	m_Vec3Map[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, const glm::vec4& value)
{
	LUMEDA_PROFILE;
	m_Vec4Map[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, const glm::mat2& value)
{
	LUMEDA_PROFILE;
	m_Mat2Map[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, const glm::mat3& value)
{
	LUMEDA_PROFILE;
	m_Mat3Map[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, const glm::mat4& value)
{
	LUMEDA_PROFILE;
	m_Mat4Map[uniform] = value;
}

void Material::SetUniform(const std::string& uniform, std::shared_ptr<Texture2D> value)
{
	LUMEDA_PROFILE;
	m_TextureMap[uniform] = value;
}

const std::string& Material::GetName()
{
	LUMEDA_PROFILE;
	return m_Name;
}