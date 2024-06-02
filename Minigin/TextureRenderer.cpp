#include "TextureRenderer.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::TextureRenderer::TextureRenderer(GameObject* pParent, std::shared_ptr<Texture2D> pTexture, int vframes, int hframes)
	: Component(pParent)
	, m_pTexture{ std::move(pTexture) }
	, m_VFrames{ vframes }
	, m_HFrames{ hframes }
{
}

void dae::TextureRenderer::Render() const
{
	if (m_pTexture == nullptr) return;

	Transform& transform{ GetParent()->GetTransform() };

	const glm::ivec2 texSize{ m_pTexture->GetSize() };
	const int cellSizeX{ texSize.x / m_HFrames };
	const int cellSizeY{ texSize.y / m_VFrames };

	const SDL_Rect source{
		(frame % m_HFrames) * cellSizeX,
		(frame / m_HFrames) * cellSizeY,
		cellSizeX,
		cellSizeY
	};

	Renderer::GetInstance().RenderTexture(
		*m_pTexture,
		&source,
		{ cellSizeX, cellSizeY },
		transform.GetWorldPosition() + offset,
		transform.GetWorldRotation(),
		transform.GetWorldScale()
	);
}
