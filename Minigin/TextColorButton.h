#pragma once
#include <SDL_pixels.h>

#include "UIButton.h"

namespace dae
{
	class TextRenderer;

	class TextColorButton final : public UIButton
	{
	public:
		TextColorButton(
			GameObject* pParent,
			const glm::vec2& buttonClickRect,
			SDL_Color normal =  SDL_Color{ 255, 255, 255, 255 },
			SDL_Color hover =   SDL_Color{ 0, 175, 0, 255 },
			SDL_Color pressed = SDL_Color{ 0, 100, 0, 255 }
		);

		void Ready() override;

	private:
		SDL_Color m_NormalColor;
		SDL_Color m_HoverColor;
		SDL_Color m_PressedColor;

		TextRenderer* m_pTextRenderer{};
	};

}
