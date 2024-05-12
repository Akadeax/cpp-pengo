#include "PlayerController.h"

#include <glm/gtx/norm.inl>


#include "GameObject.h"
#include "GameTime.h"

PlayerController::PlayerController(dae::GameObject* pParent)
	: Component(pParent)
{
}

void PlayerController::Kill()
{
 	--m_Lives;
	OnDeath.Emit();

	if (m_Lives <= 0)
	{
		OnGameOver.Emit();
	}
}

void PlayerController::IncreaseScore(int amount)
{
	m_Score += amount;
	OnScoreChanged.Emit();
}

bool PlayerController::IsMoving() const
{
	return m_IsMoving;
}

void PlayerController::Update()
{
	if (length2(m_MoveDir) == 0.f)
	{
		m_IsMoving = false;
		return;
	}

	m_IsMoving = true;
	GetParent()->GetTransform().Translate(
		m_MoveDir * m_MoveSpeed * dae::GameTime::GetInstance().GetDeltaTime()
	);

	m_MoveDir = glm::vec2{ 0, 0 };
}
