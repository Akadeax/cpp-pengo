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
#include "Scenes.h"
#include "ServiceLocator.h"
#include "SoundEffects.h"

PlayerController::PlayerController(dae::GameObject* pParent)
	: Component(pParent)
{
}

void PlayerController::Ready()
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	const GridManager* pGridManager{ pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>() };

	const glm::vec2 startPos{ pGridManager->GridToWorld({ 0, 0 }) };
	m_StartPos = startPos;

	GetParent()->GetTransform().SetLocalPosition(m_StartPos);
}

void PlayerController::SetLives(int lives)
{
	m_Lives = lives;
}

void PlayerController::Kill()
{
	if (m_Lives == 0)
	{
		OnGameOver.Emit();
		dae::SceneManager::GetInstance().QueueSceneLoadForEndOfFrame(CreateMenuScene);
		dae::ServiceLocator::GetSoundSystem().StopMusic();
		dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundSystem::SoundType::sfx, soundEffects::PLAYER_LOSE, 255);

	}
	else
	{
		--m_Lives;
		OnDeath.Emit();

		GetParent()->GetTransform().SetLocalPosition(m_StartPos);
		dae::ServiceLocator::GetSoundSystem().PlaySound(dae::SoundSystem::SoundType::sfx, soundEffects::PLAYER_DEATH, 255);
	}
}

void PlayerController::SetScore(int score)
{
	m_Score = score;
	OnScoreChanged.Emit();
}

void PlayerController::IncreaseScore(int amount)
{
	m_Score += amount;
	OnScoreChanged.Emit();
}
