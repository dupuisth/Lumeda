#pragma once

#include <glm/glm.hpp>

#include <string>

namespace Lumeda
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Prepare(float time, const glm::vec3& cameraPosition, const glm::vec3& cameraForward, const glm::mat4 cameraMatrix) = 0;

		virtual void SetUniform(const std::string& uniform, int value) = 0;
		virtual void SetUniform(const std::string& uniform, float value) = 0;
		virtual void SetUniform(const std::string& uniform, const glm::vec2& value) = 0;
		virtual void SetUniform(const std::string& uniform, const glm::vec3& value) = 0;
		virtual void SetUniform(const std::string& uniform, const glm::vec4& value) = 0;
		virtual void SetUniform(const std::string& uniform, const glm::mat2& value) = 0;
		virtual void SetUniform(const std::string& uniform, const glm::mat3& value) = 0;
		virtual void SetUniform(const std::string& uniform, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;
	};
}