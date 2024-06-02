#include "TextRenderer.h"

#include <SDL_ttf.h>
#include <stdexcept>
#include <utility>

#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameTime.h"
#include "UIAnchor.h"

dae::TextRenderer::TextRenderer(
	GameObject* pParent,
	std::string text,
	std::shared_ptr<Font> font,
	SDL_Color color,
	TextAlign mainAxis,
	TextAlign crossAxis,
	UIAnchor* pAnchorToOffset
)
	: TextureRenderer(pParent, nullptr)
	, m_Text{ std::move(text) }
	, m_pFont{ std::move(font) }
	, m_Color{ color }
	, m_MainAxis{ mainAxis }
	, m_CrossAxis{ crossAxis }
	, m_pAnchorToOffset{ pAnchorToOffset }
{
}

void dae::TextRenderer::Update()
{
	if (!m_IsDirty) return;

	SDL_Surface* surf{ TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color) };
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	SDL_Texture* texture{ SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf) };
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}

	SDL_FreeSurface(surf);
	m_pTexture = std::make_shared<Texture2D>(texture);

	const glm::vec2 size{ m_pTexture->GetSize() };
	glm::vec2 localOffset{};

	if (m_MainAxis == TextAlign::center) localOffset.x = -size.x / 2.f;
	else if (m_MainAxis == TextAlign::end) localOffset.x = -size.x;

	if (m_CrossAxis == TextAlign::center) localOffset.y = -size.y / 2.f;
	else if (m_CrossAxis == TextAlign::end) localOffset.y = -size.y;

	if (m_pAnchorToOffset)
	{
		m_pAnchorToOffset->offset = localOffset;
		m_pAnchorToOffset->UpdateAnchoredPosition();
	}
	else
	{
		offset = localOffset;
	}

	m_IsDirty = false;
}

void dae::TextRenderer::SetText(const std::string& text)
{
	m_IsDirty = true;
	m_Text = text;
}

void dae::TextRenderer::SetColor(SDL_Color color)
{
	m_IsDirty = true;
	m_Color = color;
}
