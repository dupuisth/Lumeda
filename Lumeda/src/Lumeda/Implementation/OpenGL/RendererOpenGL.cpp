#include <Lumeda/Implementation/OpenGL/RendererOpenGL.h>

#include <Lumeda/Core/Engine.h>
#include <Lumeda/Implementation/OpenGL/ShaderOpenGL.h>
#include <Lumeda/Implementation/OpenGL/TextureOpenGL.h>
#include <Lumeda/Implementation/OpenGL/MeshOpenGL.h>
#include <Lumeda/Implementation/OpenGL/FramebufferOpenGL.h>
#include <Lumeda/Implementation/OpenGL/RenderTargetOpenGL.h>
#include <Lumeda/Renderer/Material.h>
#include <Lumeda/Renderer/Model.h>
#include <Lumeda/Renderer/Camera.h>
#include <Lumeda/Renderer/ModelLoader.h>
#include <Lumeda/Renderer/Camera.h>

#include <glad/glad.h>

using namespace Lumeda;

const char* SCREEN_SHADER_VERT = "#version 460 core \n \
layout (location = 0) in vec3 a_Pos; \
layout (location = 1) in vec2 a_Uv; \
out vec2 f_Uv; \
void main() \
{ \
	f_Uv = a_Uv; \
	gl_Position = vec4(a_Pos, 1.0); \
}";

const char* SCREEN_SHADER_FRAG = "#version 460 core \n \
in vec2 f_Uv; \
out vec4 FragColor; \
uniform sampler2D u_ColorTexture; \
uniform sampler2D u_DepthStencilTexture; \
void main() \
{ \
    float ds = length(vec4(1.0) - texture(u_DepthStencilTexture, f_Uv)); \
    vec4 color = texture(u_ColorTexture, f_Uv); \
    FragColor = color; \
}";

RendererOpenGL::RendererOpenGL()
	: m_RenderCallsMesh()
{
	LUMEDA_PROFILE;
	if (!gladLoadGL())
	{
		LUMEDA_CORE_CRITICAL("Failed to initialize glad");
		throw std::runtime_error("Failed to initialize glad");
	}

	m_WindowResizeCallbackToken = Engine::Get().GetWindow().AddResizeCallback(
		std::bind(&RendererOpenGL::OnWindowResize, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
	);

	m_ScreenShader = CreateShaderFromSource("Renderer_ScreenShader", SCREEN_SHADER_VERT, SCREEN_SHADER_FRAG);
	m_ScreenMesh = CreateMesh(
		"Renderer_Quad",
		{
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Top Left
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // Bottom Left
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Top Right
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f     // Bottom Right
		},
			{
				0, 1, 2,
				1, 3, 2
			},
			{
				{ 0, 3, Lumeda::MeshAttribType::FLOAT },
				{ 1, 2, Lumeda::MeshAttribType::FLOAT }
			}
	);
}

RendererOpenGL::~RendererOpenGL()
{
	LUMEDA_PROFILE;

	// Force delete all materials
	for (auto& material : m_Materials)
	{
		Delete(material.second);
	}

	// Force delete all shaders
	for (auto& shader : m_Shaders)
	{
		Delete(shader.second);
	}

	// Force delete all textures
	for (auto& texture : m_Textures2D)
	{
		Delete(texture.second);
	}

	// Force delete all meshes
	for (auto& mesh : m_Meshes)
	{
		Delete(mesh.second);
	}

	// Force delete all framebuffers
	for (auto& framebuffer : m_Framebuffers)
	{
		Delete(framebuffer.second);
	}

	Engine::Get().GetWindow().RemoveResizeCallback(m_WindowResizeCallbackToken);
}

void RendererOpenGL::SetClearColor(float r, float g, float b, float a)
{
	LUMEDA_PROFILE;
	glClearColor(r, g, b, a);
}

void RendererOpenGL::Clear()
{
	LUMEDA_PROFILE;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOpenGL::SetViewport(int x, int y, int width, int height)
{
	LUMEDA_PROFILE;
	glViewport(x, y, width, height);
}

const std::unordered_map<std::string, Shader*>& Lumeda::RendererOpenGL::ListShaders()
{
	LUMEDA_PROFILE;
	return m_Shaders;
}

const std::unordered_map<std::string, Texture2D*>& Lumeda::RendererOpenGL::ListTextures2D()
{
	LUMEDA_PROFILE;
	return m_Textures2D;
}

const std::unordered_map<std::string, Mesh*>& Lumeda::RendererOpenGL::ListMeshes()
{
	LUMEDA_PROFILE;
	return m_Meshes;
}

const std::unordered_map<std::string, Material*>& Lumeda::RendererOpenGL::ListMaterials()
{
	LUMEDA_PROFILE;
	return m_Materials;
}

const std::unordered_map<std::string, Model*>& Lumeda::RendererOpenGL::ListModels()
{
	LUMEDA_PROFILE;
	return m_Models;
}

const std::unordered_map<std::string,Framebuffer*>& RendererOpenGL::ListFramebuffers()
{
	LUMEDA_PROFILE;
	return m_Framebuffers;
}

const std::unordered_map<std::string, RenderTarget*>& RendererOpenGL::ListRenderTargets()
{
	LUMEDA_PROFILE;
	return m_RenderTargets;
}


#define SAFE_RETURN_RESOURCE(map, resourceName) \
const auto& iterator = map.find(resourceName); \
if (iterator == map.end()) \
{ \
	LUMEDA_CORE_WARN("[RendererOpenGL] Did not find the resource {0} in the map {1}", resourceName, #map); \
	return nullptr; \
} \
return iterator->second;

Shader* RendererOpenGL::GetShader(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Shaders, name);
}

Texture2D* RendererOpenGL::GetTexture2D(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Textures2D, name);
}

Mesh* RendererOpenGL::GetMesh(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Meshes, name);
}

Material* RendererOpenGL::GetMaterial(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Materials, name);
}

Model* RendererOpenGL::GetModel(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Models, name);
}

Framebuffer* RendererOpenGL::GetFramebuffer(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_Framebuffers, name);
}

RenderTarget* RendererOpenGL::GetRenderTarget(const std::string& name)
{
	LUMEDA_PROFILE;
	SAFE_RETURN_RESOURCE(m_RenderTargets, name);
}

Shader* RendererOpenGL::CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
	LUMEDA_PROFILE;
	ShaderOpenGL* shader = LUMEDA_NEW(ShaderOpenGL, MemTag::Assets, name, vertexPath, fragmentPath);
	m_Shaders.insert({ name, shader });
	return shader;
}

Shader* RendererOpenGL::CreateShaderFromSource(const std::string& name, const char* vertexCode, const char* fragmentCode)
{
	LUMEDA_PROFILE;
	ShaderOpenGL* shader = LUMEDA_NEW(ShaderOpenGL, MemTag::Assets, name, vertexCode, fragmentCode, 0);
	m_Shaders.insert({ name, shader });
	return shader;
}

Texture2D* RendererOpenGL::CreateTexture2D(const std::string& name, const std::string& path)
{
	LUMEDA_PROFILE;
	Texture2DOpenGL* texture2D = LUMEDA_NEW(Texture2DOpenGL, MemTag::Assets, name, path);
	m_Textures2D.insert({ name, texture2D });
	return texture2D;
}

Texture2D* RendererOpenGL::CreateTexture2D(const std::string& name, unsigned int width, unsigned int height, eTextureFormat format)
{
	LUMEDA_PROFILE;
	Texture2DOpenGL* texture2D = LUMEDA_NEW(Texture2DOpenGL, MemTag::Assets, name, width, height, format);
	m_Textures2D.insert({ name, texture2D });
	return texture2D;
}

Mesh* RendererOpenGL::CreateMesh(const std::string& name, const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<MeshAttrib>& attribs)
{
	LUMEDA_PROFILE;
	MeshOpenGL* mesh = LUMEDA_NEW(MeshOpenGL, MemTag::Assets, name, vertices, indices, attribs);
	m_Meshes.insert({ name, mesh });
	return mesh;
}

Material* RendererOpenGL::CreateMaterial(const std::string& name)
{
	LUMEDA_PROFILE;
	Material* material = LUMEDA_NEW(Material, MemTag::Assets, name);
	m_Materials.insert({ name, material });
	return material;
}

Model* RendererOpenGL::CreateModel(const std::string& name)
{
	LUMEDA_PROFILE;
	Model* model = LUMEDA_NEW(Model, MemTag::Assets, name);
	m_Models.insert({ name, model });
	return model;
}

Model* RendererOpenGL::CreateModel(const std::string& name, const std::string& fromFile)
{
	LUMEDA_PROFILE;
	Model* model = CreateModel(name);
	ModelLoader::LoadModelFromFile(model, fromFile);
	return model;
}

Framebuffer* RendererOpenGL::CreateFramebuffer(const std::string& name)
{
	LUMEDA_PROFILE;
	Framebuffer* framebuffer = LUMEDA_NEW(FramebufferOpenGL, MemTag::Assets, name);
	m_Framebuffers.insert({ name, framebuffer });
	return framebuffer;
}

RenderTarget* RendererOpenGL::CreateRenderTarget(const std::string& name, int width, int height)
{
	LUMEDA_PROFILE;
	RenderTargetOpenGL* renderTarget = LUMEDA_NEW(RenderTargetOpenGL, MemTag::Assets, name, glm::ivec2(width, height));
	m_RenderTargets.insert({ name, renderTarget });
	return renderTarget;
}

void RendererOpenGL::BeginFrame()
{
	LUMEDA_PROFILE;
	m_RenderCallsMesh.clear();
	m_RenderCallsModel.clear();
}

void RendererOpenGL::Submit(Mesh* mesh, Material* material, sUniformsMap& uniforms)
{
	LUMEDA_PROFILE;
	sRenderCallMesh renderCall;
	renderCall.mesh = mesh;
	renderCall.material = material;
	renderCall.uniformMap = uniforms;

	m_RenderCallsMesh.push_back(renderCall);
}

void RendererOpenGL::Submit(Model* model, sUniformsMap& uniforms)
{
	LUMEDA_PROFILE;
	sRenderCallModel renderCall;
	renderCall.model = model;
	renderCall.uniformMap = uniforms;

	m_RenderCallsModel.push_back(renderCall);
}

void RendererOpenGL::Render(Camera* camera, RenderTarget* renderTarget)
{
	LUMEDA_PROFILE;
	glm::vec3 cameraPosition(0.0f);
	glm::vec3 cameraForward(0.0f, 0.0f, 1.0f);
	glm::mat4 cameraMatrix(1.0f);
	float time = 0.0f; // TODO : Fix this when there is a Timer

	if (camera != nullptr)
	{
		cameraPosition = camera->GetTransform().GetPosition();
		cameraForward = camera->GetTransform().GetForward();
		cameraMatrix = camera->GetProjectionView();
	}

	for (const auto& [name, shader] : m_Shaders)
	{
		shader->Bind();
		shader->Prepare(time, cameraPosition, cameraForward, cameraMatrix);
	}

	if (renderTarget != nullptr)
	{
		renderTarget->Bind();
		glViewport(0, 0, renderTarget->GetSize().x, renderTarget->GetSize().y);

	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& renderCall : m_RenderCallsModel)
	{
		renderCall.model->Draw(renderCall.uniformMap);
	}

	for (auto& renderCall : m_RenderCallsMesh)
	{
		renderCall.material->Use(renderCall.uniformMap);
		renderCall.mesh->Draw();
	}

	if (renderTarget != nullptr)
	{
		renderTarget->UnBind();
	}
}

void RendererOpenGL::PrepareRenderScreen()
{
	LUMEDA_PROFILE;
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}

void RendererOpenGL::RenderToScreen(RenderTarget* renderTarget, int x, int y, int width, int height)
{
	LUMEDA_PROFILE;
	glViewport(x, y, width, height);

	static_cast<RenderTargetOpenGL*>(renderTarget)->PrepareRender(m_ScreenShader);
	m_ScreenMesh->Draw();
}

void RendererOpenGL::RenderToScreen(RenderTarget* renderTarget)
{
	LUMEDA_PROFILE;
	glm::ivec2 size = Engine::Get().GetWindow().GetSize();
	RenderToScreen(renderTarget, 0, 0, size.x, size.y);
}

void RendererOpenGL::EndFrame()
{
	LUMEDA_PROFILE;
	m_RenderCallsMesh.clear();
	m_RenderCallsModel.clear();
}

void RendererOpenGL::OnWindowResize(Window& window, int width, int height)
{
	LUMEDA_PROFILE;
	SetViewport(0, 0, width, height);
}
