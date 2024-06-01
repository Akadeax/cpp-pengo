#include "Scene.h"

#include <algorithm>
#include <iostream>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(uint16_t id)
	: m_ID{ id }
{
}

Scene::~Scene() = default;


void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject* object)
{
	std::erase_if(m_Objects, [object](const std::unique_ptr<GameObject>& pGo)
		{
			return pGo.get() == object;
		});
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Ready() const
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->Ready();
	}
}

void Scene::Update() const
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->Update();
	}
}

void Scene::LateUpdate() const
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->LateUpdate();
	}
}

void Scene::HandleDeletion()
{
	std::erase_if(m_Objects, [](const std::unique_ptr<GameObject>& pGo)
		{
			return pGo->IsMarkedForDeletion();
		});

	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->HandleDeletion();
	}
}

void Scene::FixedUpdate() const
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->Render();
	}
}

void Scene::OnImGui() const
{
	for (size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->OnImGui();
	}
}

GameObject* Scene::GetGameObjectByTag(const std::string& tag)
{
	const auto result{ std::ranges::find_if(
		m_Objects,
		[this, tag](auto& ptr) { return ptr->GetTag() == tag; }
	) };

	if (result == std::end(m_Objects))
	{
		return nullptr;
	}

	return result->get();
}

