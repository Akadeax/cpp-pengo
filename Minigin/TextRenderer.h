#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;
	class Font;

	class TextRenderer final : public Component
	{
		TextRenderer(const std::string& text, std::shared_ptr<Font> font, SDL_Color color);

		void Update() override;

		void SetText(const std::string& text);

	private:
		bool m_IsDirty{ true };
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
