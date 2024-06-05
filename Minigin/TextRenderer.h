#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <string>

#include "TextureRenderer.h"

namespace dae
{
	class UIAnchor;
}

namespace dae
{
	class Texture2D;
	class Font;

	enum class TextAlign
	{
		start, center, end
	};

	class TextRenderer : public TextureRenderer
	{
	public:
		TextRenderer(
			GameObject* pParent,
			std::string text,
			std::shared_ptr<Font> font,
			SDL_Color color = SDL_Color{ 255, 255, 255, 255 },
			TextAlign mainAxis = TextAlign::start,
			TextAlign crossAxis = TextAlign::start,
			UIAnchor* pAnchorToOffset = nullptr
		);

		void Update() override;

		std::string GetText() const { return m_Text; }
		void SetText(const std::string& text);
		void SetColor(SDL_Color color);

	private:
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		SDL_Color m_Color;

		bool m_IsDirty{ true };

		TextAlign m_MainAxis;
		TextAlign m_CrossAxis;

		UIAnchor* m_pAnchorToOffset{ nullptr };
	};
}
