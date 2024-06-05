#pragma once
#include <string>

#include "SceneManager.h"

namespace dae
{
	class Font;
}

std::unique_ptr<dae::Scene> CreateMenuScene();
std::unique_ptr<dae::Scene> CreateGameScene(const std::string& levelFilePath, int id);
std::unique_ptr<dae::Scene> CreateFirstGameScene();

std::unique_ptr<dae::Scene> CreateCoOpScene(const std::string& levelFilePath, int id);
std::unique_ptr<dae::Scene> CreateFirstCoOpScene();

std::unique_ptr<dae::Scene> GameOverScene();

std::unique_ptr<dae::GameObject> MenuButtonBuilder(
	std::string text,
	std::shared_ptr<dae::Font> pFont,
	float yOffset,
	std::function<void()> onClick,
	float rectWidth = 130
);