#include "SaveData.h"

#include <fstream>

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

std::vector<HighscoreData> SaveData::GetHighscoreData()
{
	if (!std::filesystem::exists(m_HighscorePath))
	{
		CreateEmptyHighscoreFile();
	}

	const std::ifstream file{ m_HighscorePath };
	assert(file.is_open() && "File failed to open");

	std::stringstream buffer;
	buffer << file.rdbuf();

	const nlohmann::json json{ nlohmann::json::parse(buffer.str()) };

	std::vector<HighscoreData> out{};
	for (auto& highscore : json["highscores"])
	{
		out.emplace_back(highscore["name"], highscore["score"]);
	}

	return out;
}

void SaveData::SaveHighscore(HighscoreData highscore)
{
	std::vector<HighscoreData> data{ GetHighscoreData() };
	data.push_back(std::move(highscore));

	std::ranges::sort(data, std::greater{}, &HighscoreData::score);

	nlohmann::json outJson;
	for (size_t i{}; i < data.size(); ++i)
	{
		outJson["highscores"][i]["name"] = data[i].name;
		outJson["highscores"][i]["score"] = data[i].score;
	}

	std::ofstream outFile{ m_HighscorePath };
	outFile << nlohmann::to_string(outJson);
}

void SaveData::CreateEmptyHighscoreFile() const
{
	std::ofstream out{ m_HighscorePath };
	out << "{\"highscores\":[]}";
}
