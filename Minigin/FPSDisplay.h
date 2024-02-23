#pragma once
#include "TextRenderer.h"

namespace dae
{
	class FPSDisplay final : public TextRenderer
	{
	public:
		FPSDisplay(GameObject* pParent, float updateIntervalSecs, std::shared_ptr<Font> font, SDL_Color color);

		void Update() override;

	private:
		float m_UpdateIntervalSecs;

		float m_CurrentUpdateTime{ 0.f };
	};
}

