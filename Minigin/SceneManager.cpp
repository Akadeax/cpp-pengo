#include "SceneManager.h"

#include <cassert>

#include "Scene.h"
#include <iostream>

void dae::SceneManager::Ready() const
{
	m_Scenes.at(m_CurrentSceneId)->Ready();
}

void dae::SceneManager::Update() const
{
	m_Scenes.at(m_CurrentSceneId)->Update();
}

void dae::SceneManager::LateUpdate() const
{
	m_Scenes.at(m_CurrentSceneId)->LateUpdate();
}

void dae::SceneManager::HandleDeletion() const
{
	m_Scenes.at(m_CurrentSceneId)->HandleDeletion();
}

void dae::SceneManager::FixedUpdate() const
{
	m_Scenes.at(m_CurrentSceneId)->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	m_Scenes.at(m_CurrentSceneId)->Render();
}

void dae::SceneManager::OnImGui() const
{
	m_Scenes.at(m_CurrentSceneId)->OnImGui();
}

dae::Scene* dae::SceneManager::GetCurrentScene()
{
	return m_Scenes[m_CurrentSceneId].get();
}

void dae::SceneManager::SetCurrentScene(SceneID id)
{
	m_CurrentSceneId = id;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name, SceneID sceneIndex)
{
	const auto& scene{ std::shared_ptr<Scene>(new Scene(name)) };
	m_Scenes[sceneIndex] = scene;
	return *scene;
}


