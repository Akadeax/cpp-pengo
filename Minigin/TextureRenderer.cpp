#include "TextureRenderer.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::TextureRenderer::TextureRenderer(GameObject* pParent, std::shared_ptr<Texture2D> pTexture)
	: Component(pParent), m_pTexture{ std::move(pTexture) }
{
}

void dae::TextureRenderer::Render() const
{
	if (m_pTexture == nullptr) return;

	const auto& pos = GetParent()->GetTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
