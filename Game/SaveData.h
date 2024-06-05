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

struct HighscoreData
{
	std::string name;
	int score;
};

class SaveData final : public dae::Singleton<SaveData>
{
public:
	void SaveCrossLevelData(const dae::Scene* pScene);
	void LoadCrossLevelData(const dae::Scene* pScene);

	std::vector<HighscoreData> GetHighscoreData();
	void SaveHighscore(HighscoreData highscore);

	int lastRunScore{};

private:
	friend class Singleton;
	SaveData() = default;

	std::vector<CrossLevelData> m_PlayerLevelSaveData;

	void CreateEmptyHighscoreFile() const;

	std::string m_HighscorePath{ "highscores.json" };
};
