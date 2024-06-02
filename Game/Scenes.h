#pragma once
#include <string>

#include "SceneManager.h"

std::unique_ptr<dae::Scene> CreateMenuScene();
std::unique_ptr<dae::Scene> CreateGameScene(const std::string& levelFilePath, int id);
std::unique_ptr<dae::Scene> CreateFirstGameScene();
