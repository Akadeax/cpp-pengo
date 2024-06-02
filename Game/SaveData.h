#pragma once
#include <json.hpp>

#include "Singleton.h"

namespace dae
{
	class Scene;
}

struct CrossLevelData
{
	int lives;
	int score;
};

class SaveData final : public dae::Singleton<SaveData>
{
public:
	void SaveCrossLevelData(const dae::Scene* pScene);
	void LoadCrossLevelData(const dae::Scene* pScene);

	//void SaveCrossGameData();
	//void LoadCrossGameData();

private:
	friend class Singleton;
	SaveData() = default;

	std::vector<CrossLevelData> m_PlayerLevelSaveData;
};

