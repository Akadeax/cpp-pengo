#pragma once
#include <Component.h>


namespace dae
{
	class TextRenderer;
}

class PlayerController;

class LivesDisplay final : public dae::Component
{
public:
	explicit LivesDisplay(dae::GameObject* pParent, PlayerController* pPlayerController);

	void Ready() override;

private:
	PlayerController* m_pPlayerController{};
	dae::TextRenderer* m_pTextRenderer{};

	void UpdateLivesText() const;
};
