#include <queue>
#include <set>
#include <Lumeda/Graphics/SimpleRenderer.h>
#include <Lumeda/Graphics/VertexBuffer.h>
#include <Lumeda/Scene/Node.h>
#include <Lumeda/Scene/Renderable.h>
#include <Lumeda/Scene/World.h>

using namespace Lumeda;

SimpleRenderer::SimpleRenderer(iLowLevelGraphics& lowLevelGraphics) : iRenderer("SimpleRenderer"), m_LowLevelGraphics(lowLevelGraphics)
{
  glm::ivec2 screenSize = glm::ivec2(m_LowLevelGraphics.GetWidth(), m_LowLevelGraphics.GetHeight());

  m_FrameBuffer = m_LowLevelGraphics.CreateFrameBuffer("SimpleRenderer_FrameBuffer");
  m_FrameBufferColor = m_LowLevelGraphics.CreateTexture("SimpleRenderer_ScreenColor", eTextureType_2D, eTextureUsage_Normal);
  m_FrameBufferColor->CreateFromRawData(glm::ivec3(screenSize, 0), ePixelFormat_RGB, nullptr);
  m_FrameBufferDepthStencil = m_LowLevelGraphics.CreateRenderBuffer("SimpleRenderer_ColorDepthStencil");
  m_FrameBufferDepthStencil->SetStorage(screenSize, ePixelFormat_Depth24Stencil8);
  m_FrameBuffer->AttachTexture2D(eFrameBufferAttachment_Color, *m_FrameBufferColor);
  m_FrameBuffer->AttachRenderBuffer(eFrameBufferAttachment_DepthStencil, *m_FrameBufferDepthStencil);

  m_OpaquePass = std::make_unique<OpaquePass>(m_FrameBuffer.get());
  m_ScreenPass = std::make_unique<ScreenPass>();

  m_RenderContext = std::make_unique<RenderContext>(lowLevelGraphics);
}

///////////////////////////////////////////
// Submits
///////////////////////////////////////////
void SimpleRenderer::Submit(const sRenderItem& item)
{
  m_OpaquePass->Submit(item);
  // Debugging, Also submit as an wireframe!
  if (!item.wireframe)
  {
    sRenderItem copy = item;
    copy.wireframe = true;
    m_OpaquePass->Submit(copy);
  }

  m_ScreenPass->Submit(item);
}

void SimpleRenderer::Submit(World& world)
{
  std::queue<LeafNode*> iterationQueue;
  iterationQueue.push(&world.GetRootNode());

  while (!iterationQueue.empty())
  {
    LeafNode* leafNode = iterationQueue.front();
    iterationQueue.pop();

    // Try to cast as renderable and submit if succeed
    iRenderable* renderable = dynamic_cast<iRenderable*>(leafNode);
    if (renderable != nullptr)
    {
      renderable->CollectRenderCommands(*this);
    }

    // If has childs, append them
    Node* node = dynamic_cast<Node*>(leafNode);
    if (node != nullptr)
    {
      for (auto& child : node->GetChilds())
      {
        iterationQueue.push(child.get());
      }
    }
  }
}

///////////////////////////////////////////
// Render
///////////////////////////////////////////
void SimpleRenderer::Flush(const UniformMap& globalUniforms)
{
  m_OpaquePass->Flush(*m_RenderContext, globalUniforms);
  m_ScreenPass->Flush(*m_RenderContext, globalUniforms);
}