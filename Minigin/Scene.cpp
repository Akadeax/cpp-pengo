#include "Scene.h"
#include "GameObject.h"

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

void Scene::Remove(const std::shared_ptr<GameObject>& object)
{
	std::erase(m_Objects, object);
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

