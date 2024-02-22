#include "SceneManager.h"
#include "Scene.h"
#include <iostream>

void dae::SceneManager::Update()
{
	for(const auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene{ std::shared_ptr<Scene>(new Scene(name)) };
	m_Scenes.push_back(scene);
	return *scene;
}
