#include "SceneManager.h"

#include "InputManager.h"
#include "Scene.h"

void dae::SceneManager::SetCurrentScene(std::unique_ptr<Scene> pScene)
{
	m_pScene = std::move(pScene);
}

void dae::SceneManager::QueueSceneLoadForEndOfFrame(std::function<std::unique_ptr<Scene>()> sceneBuilder)
{
	m_QueuedSceneLoad = std::move(sceneBuilder);
}

void dae::SceneManager::Ready() const
{
	m_pScene->Ready();
}

void dae::SceneManager::Update() const
{
	m_pScene->Update();
}

void dae::SceneManager::LateUpdate() const
{
	m_pScene->LateUpdate();
}

void dae::SceneManager::HandleDeletion()
{
	m_pScene->HandleDeletion();

	if (m_QueuedSceneLoad != nullptr)
	{
		InputManager::GetInstance().ClearInputDevices();
		SetCurrentScene(m_QueuedSceneLoad());
		m_QueuedSceneLoad = nullptr;
	}
}

void dae::SceneManager::FixedUpdate() const
{
	m_pScene->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	m_pScene->Render();
}

void dae::SceneManager::OnImGui() const
{
	m_pScene->OnImGui();
}

dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	return m_pScene.get();
}
