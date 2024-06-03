#pragma once
#include <SDL_pixels.h>

#include "ToggleButton.h"

namespace dae
{
	class TextRenderer;

	class TextColorToggleButton final : public ToggleButton
	{
	public:
		TextColorToggleButton(
			GameObject* pParent,
			const glm::vec2& buttonClickRect,
			bool startOn = true,
			SDL_Color on =      SDL_Color{ 0, 175, 0, 255 },
			SDL_Color off =     SDL_Color{ 175, 0, 0, 255 },
			SDL_Color hover =   SDL_Color{ 175, 175, 0, 255 },
			SDL_Color pressed = SDL_Color{ 100, 100, 0, 255 }
		);

		void Ready() override;

	private:
		SDL_Color m_OnColor;
		SDL_Color m_OffColor;
		SDL_Color m_HoverColor;
		SDL_Color m_PressedColor;

		TextRenderer* m_pTextRenderer{};
	};

}
