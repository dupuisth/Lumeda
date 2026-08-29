#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <queue>
#include <Lumeda/Resources/MaterialManager.h>
#include <Lumeda/Utils/AssimpModelLoader.h>

using namespace Lumeda;

std::unique_ptr<iVertexBuffer> ProcessMesh(const std::string& name, aiMesh* aiMesh, Graphics& graphics, Resources& resources)
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

  std::unique_ptr<iVertexBuffer> vertexBuffer = graphics.GetLowLevelGraphics().CreateVertexBuffer();
  vertexBuffer->SetData(vertices,
      indices,
      {
          {0, 3, eVertexAttribType_Float},
          {1, 2, eVertexAttribType_Float},
          {2, 3, eVertexAttribType_Float},
      });
  return std::move(vertexBuffer);
}

void AssimpModelLoader::Load(Model* model, const twString& path, Graphics& graphics, Resources& resources)
{
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    LUMEDA_CORE_ERROR("[ModelLoader]: Assimp error {0}", importer.GetErrorString());
    return;
  }

  // Prepare the material slots
  for (int i = 0; i < scene->mNumMaterials; i++)
  {
    model->GetMaterials().push_back(nullptr);
  }

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
      std::unique_ptr<iVertexBuffer> mesh = ProcessMesh(name, aiMesh, graphics, resources);
      model->AddItem(std::move(mesh), aiMesh->mMaterialIndex);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
      nodes.push(node->mChildren[i]);
    }

    nodes.pop();
  }
}