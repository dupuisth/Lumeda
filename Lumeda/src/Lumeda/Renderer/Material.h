#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/Texture.h>
#include <Lumeda/Renderer/Shader.h>

#include <glm/glm.hpp>

#include <memory>
#include <unordered_map>

namespace Lumeda
{
	class Material
	{
	public:
		Material(const std::string& name);
		virtual ~Material();

		virtual void Use();

		void SetShader(std::shared_ptr<Shader> shader);
		void SetUniform(const std::string& uniform, int value);
		void SetUniform(const std::string& uniform, float value);
		void SetUniform(const std::string& uniform, const glm::vec2& value);
		void SetUniform(const std::string& uniform, const glm::vec3& value);
		void SetUniform(const std::string& uniform, const glm::vec4& value);
		void SetUniform(const std::string& uniform, const glm::mat2& value);
		void SetUniform(const std::string& uniform, const glm::mat3& value);
		void SetUniform(const std::string& uniform, const glm::mat4& value);
		void SetUniform(const std::string& uniform, std::shared_ptr<Texture2D> value);

		const std::string& GetName();

	protected:
		std::string m_Name;

		std::shared_ptr<Shader> m_Shader;

		// Uniforms
		std::unordered_map<std::string, int> m_IntMap;
		std::unordered_map<std::string, float> m_FloatMap;
		std::unordered_map<std::string, glm::vec2> m_Vec2Map;
		std::unordered_map<std::string, glm::vec3> m_Vec3Map;
		std::unordered_map<std::string, glm::vec4> m_Vec4Map;
		std::unordered_map<std::string, glm::mat2> m_Mat2Map;
		std::unordered_map<std::string, glm::mat3> m_Mat3Map;
		std::unordered_map<std::string, glm::mat4> m_Mat4Map;
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureMap;
	};
}