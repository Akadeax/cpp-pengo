#include "SaveData.h"

#include "GameObject.h"
#include "PlayerController.h"
#include "Scene.h"

void SaveData::SaveCrossLevelData(const dae::Scene* pScene)
{
	for (const dae::GameObject* pGo : pScene->GetGameObjectsByTag("Player"))
	{
		const PlayerController* pPlayer{ pGo->GetComponent<PlayerController>() };
		m_PlayerLevelSaveData.emplace_back(pPlayer->GetLives(), pPlayer->GetScore());
	}
}

void SaveData::LoadCrossLevelData(const dae::Scene* pScene)
{
	const std::vector pPlayerObjects{ pScene->GetGameObjectsByTag("Player") };
	for (size_t i{}; i < pPlayerObjects.size(); ++i)
	{
		PlayerController* pPlayer{ pPlayerObjects[i]->GetComponent<PlayerController>() };
		pPlayer->SetLives(m_PlayerLevelSaveData[i].lives);
		pPlayer->SetScore(m_PlayerLevelSaveData[i].score);
	}

	m_PlayerLevelSaveData.clear();
}
