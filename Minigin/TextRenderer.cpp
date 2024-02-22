#include "TextRenderer.h"

#include <SDL_ttf.h>
#include <stdexcept>
#include <utility>

#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::TextRenderer::TextRenderer(GameObject* pParent, std::string text, std::shared_ptr<Font> font, SDL_Color color)
	: TextureRenderer(pParent, nullptr), m_Text{ std::move(text) }, m_pFont{ std::move(font) }, m_Color{ color }
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
	m_IsDirty = false;
}

void dae::TextRenderer::SetText(const std::string& text)
{
	m_IsDirty = true;
	m_Text = text;
}
