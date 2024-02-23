#include "FPSDisplay.h"

#include "Time.h"
#include <sstream>
#include <iomanip>

dae::FPSDisplay::FPSDisplay(GameObject* pParent, float updateIntervalSecs, std::shared_ptr<Font> font, SDL_Color color)
	: TextRenderer(pParent, "0.0", std::move(font), color)
	, m_UpdateIntervalSecs{ updateIntervalSecs }
{
}

void dae::FPSDisplay::Update()
{
	TextRenderer::Update();

	m_CurrentUpdateTime += Time::GetInstance().GetDeltaTime();
	if (m_CurrentUpdateTime > m_UpdateIntervalSecs)
	{
		m_CurrentUpdateTime = 0.f;

		std::stringstream ss{};
		ss << std::fixed << std::setprecision(1);
		ss << (1.f / Time::GetInstance().GetDeltaTime());

		SetText(ss.str());
	}
}
