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

void dae::SceneManager::HandleDeletion()
{
	m_Scenes.at(m_CurrentSceneId)->HandleDeletion();

	if (m_QueuedSceneLoad.has_value())
	{
		SetCurrentScene(m_QueuedSceneLoad.value());
	}
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

uint16_t dae::SceneManager::GetCurrentSceneID()
{
	return m_CurrentSceneId;
}

void dae::SceneManager::SetCurrentScene(uint16_t id)
{
	m_CurrentSceneId = id;
}

dae::Scene* dae::SceneManager::MakeSceneForID(uint16_t id)
{
	std::unique_ptr scene{std::make_unique<Scene>(id)};
	m_Scenes[id] = std::move(scene);
	return m_Scenes[id].get();
}

void dae::SceneManager::QueueSceneLoadForEndOfFrame(uint16_t id)
{
	m_QueuedSceneLoad = id;
}


