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

	m_CurrentDeltaSum += Time::GetInstance().GetDeltaTime();
	++m_CurrentDeltaCount;

	if (m_CurrentDeltaSum > m_UpdateIntervalSecs)
	{
		const float averageFPS{ 1.f / (m_CurrentDeltaSum / static_cast<float>(m_CurrentDeltaCount)) };
		m_CurrentDeltaSum = 0.f;
		m_CurrentDeltaCount = 0;

		std::stringstream ss{};
		ss << std::fixed << std::setprecision(1);
		ss << averageFPS;
		SetText(ss.str());
	}
}
