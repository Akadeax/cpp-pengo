#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject* object);
		void RemoveAll();

		void Ready() const;
		void Update() const;
		void LateUpdate() const;
		void HandleDeletion();
		void FixedUpdate() const;
		void Render() const;
		void OnImGui() const;

		GameObject* GetGameObjectByTag(const std::string& tag);

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend Scene& SceneManager::CreateScene(const std::string& name, SceneManager::SceneID sceneIndex);
		explicit Scene(std::string name);

		std::string m_Name;
		std::vector <std::unique_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};
}
