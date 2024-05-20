#include "PlayerController.h"

#include <iostream>
#include <glm/gtx/norm.inl>

#pragma warning(push, 0)
#include <glm/gtx/string_cast.hpp>
#pragma warning(pop)

#include "GridManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

PlayerController::PlayerController(dae::GameObject* pParent)
	: Component(pParent)
{
}

void PlayerController::Ready()
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	const GridManager* pGridManager{ pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>() };

	const glm::vec2 startPos{ pGridManager->GridToWorld({ 0, 0 }) };
	GetParent()->GetTransform().SetLocalPosition(startPos);
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
