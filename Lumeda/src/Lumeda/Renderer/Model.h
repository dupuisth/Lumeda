#pragma once

#include <Lumeda/Core/Base.h>

#include <glm/glm.hpp>

#include <vector>

namespace Lumeda
{
	class Material;
	class Mesh;

	struct ModelItem
	{
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;
	};

	class Model
	{
	public:
		Model(const std::string& name);
		virtual ~Model();

		virtual void Draw();
		virtual void Draw(const glm::mat4 world);

		virtual const std::vector<ModelItem>& ListItems() const;
		virtual void AttachItem(const ModelItem& modelItem);
		virtual void SetItem(int index, const ModelItem& modelItem);
		virtual void RemoveItem(int index);

		const std::string& GetName();

	private:
		const std::string& m_Name;

		std::vector<ModelItem> m_ModelItems;
	};
}