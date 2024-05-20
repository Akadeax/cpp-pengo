#include "Scene.h"

#include <algorithm>
#include <iostream>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(std::string name) : m_Name(std::move(name)) {}

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
	for (const auto& object : m_Objects)
	{
		object->Ready();
	}
}

void Scene::Update() const
{
	for(const auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::LateUpdate() const
{
	for (const auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}

void Scene::HandleDeletion()
{
	std::erase_if(m_Objects, [](const std::unique_ptr<GameObject>& pGo)
		{
			return pGo->IsMarkedForDeletion();
		});

	for (const auto& object : m_Objects)
	{
		object->HandleDeletion();
	}
}

void Scene::FixedUpdate() const
{
	for (const auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::OnImGui() const
{
	for (const auto& object : m_Objects)
	{
		object->OnImGui();
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

	return (*result).get();
}

