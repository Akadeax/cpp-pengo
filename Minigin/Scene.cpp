#include "Scene.h"

#include <algorithm>
#include <iostream>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::~Scene() = default;


Scene::Scene(int id)
	: m_ID{ id }
{
}

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

GameObject* Scene::GetGameObjectByTag(const std::string& tag) const
{
	const auto result{ std::ranges::find_if(
		m_Objects,
		[this, &tag](auto& ptr) { return ptr->GetTag() == tag; }
	) };

	if (result == std::end(m_Objects))
	{
		return nullptr;
	}

	return result->get();
}

std::vector<GameObject*> Scene::GetGameObjectsByTag(const std::string& tag) const
{
	std::vector<GameObject*> results{};

	// copy_if does not want to project the unique ptr into a raw ptr here, so for_each it is
	std::ranges::for_each(m_Objects, [&tag, &results](const std::unique_ptr<GameObject>& pGo)
		{
			if (pGo->GetTag() == tag) results.emplace_back(pGo.get());
		});
	return results;
}

