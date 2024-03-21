#pragma once
#include <Component.h>


namespace dae
{
	class TextRenderer;
}

class PlayerController;

class ScoreDisplay final : public dae::Component
{
public:
	explicit ScoreDisplay(dae::GameObject* pParent, PlayerController* pPlayerController);

	void Ready() override;

private:
	PlayerController* m_pPlayerController;
	dae::TextRenderer* m_pTextRenderer;

	void UpdateScoreText() const;
};
