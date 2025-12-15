#pragma once

#include <Lumeda/Core/Base.h>
#include <Lumeda/Renderer/Texture.h>
#include <Lumeda/Renderer/Shader.h>
#include <Lumeda/Renderer/UniformsMap.h>

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
		virtual void Use(sUniformsMap& uniformsMap);

		void SetShader(std::shared_ptr<Shader> shader);
		sUniformsMap& GetUniformsMap();

		const std::string& GetName();

	protected:
		std::string m_Name;

		std::shared_ptr<Shader> m_Shader;
		sUniformsMap m_UniformsMap;
	};
}