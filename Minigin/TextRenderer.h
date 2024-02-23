#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <string>

#include "TextureRenderer.h"

namespace dae
{
	class Texture2D;
	class Font;

	class TextRenderer : public TextureRenderer
	{
	public:
		TextRenderer(GameObject* pParent, std::string text, std::shared_ptr<Font> font, SDL_Color color);

		void Update() override;

		void SetText(const std::string& text);

	private:
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		SDL_Color m_Color;

		bool m_IsDirty{ true };
	};
}
