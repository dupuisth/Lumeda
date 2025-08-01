#include <Lumeda/Renderer/ModelLoader.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Renderer/Renderer.h>
#include <Lumeda/Renderer/Mesh.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <queue>

using namespace Lumeda;

std::shared_ptr<Mesh> ProcessMesh(const std::string& name, aiMesh* aiMesh)
{
	LUMEDA_PROFILE;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		vertices.push_back(aiMesh->mVertices[i].x);
		vertices.push_back(aiMesh->mVertices[i].y);
		vertices.push_back(aiMesh->mVertices[i].z);
		vertices.push_back(aiMesh->mTextureCoords[0][i].x);
		vertices.push_back(aiMesh->mTextureCoords[0][i].y);
		vertices.push_back(aiMesh->mNormals[i].x);
		vertices.push_back(aiMesh->mNormals[i].y);
		vertices.push_back(aiMesh->mNormals[i].z);
	}

	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		aiFace face = aiMesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	std::shared_ptr<Mesh> mesh = Engine::Get().GetRenderer().CreateMesh(
		name,
		vertices,
		indices,
		{
			{ 0, 3, MeshAttribType::FLOAT },
			{ 1, 2, MeshAttribType::FLOAT },
			{ 2, 3, MeshAttribType::FLOAT },
		}
	);
	return mesh;
}

void ModelLoader::LoadModelFromFile(std::shared_ptr<Model> model, const std::string& path)
{
	LUMEDA_PROFILE;
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LUMEDA_CORE_ERROR("[ModelLoader]: Assimp error {0}", importer.GetErrorString());
		return;
	}

	std::shared_ptr<Material> material = Engine::Get().GetRenderer().CreateMaterial(model->GetName());
	
	int numModelsItem = 0;
	std::queue<aiNode*> nodes;
	nodes.push(scene->mRootNode);
	while (!nodes.empty())
	{
		aiNode* node = nodes.front();

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
			
			std::string name = model->GetName() + "_" + std::to_string(numModelsItem++);
			std::shared_ptr<Mesh> mesh = ProcessMesh(name, aiMesh);
			model->AttachItem({ mesh,  material });
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			nodes.push(node->mChildren[i]);
		}

		nodes.pop();
	}
}