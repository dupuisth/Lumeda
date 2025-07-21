#include <Lumeda/Renderer/Mesh.h>

namespace Lumeda
{
	class MeshOpenGL : public Mesh
	{
	public:
		MeshOpenGL(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs);
		virtual ~MeshOpenGL();

		void Draw() override;

		const std::string& GetName() const override;

	private:
		std::string m_Name;

		unsigned int m_Vao;
		unsigned int m_Vbo; 
		unsigned int m_Ebo;

		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<MeshAttrib> m_Attribs;
	};
}