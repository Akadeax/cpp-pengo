#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		explicit Scene(int id);

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

		GameObject* GetGameObjectByTag(const std::string& tag) const;
		std::vector<GameObject*> GetGameObjectsByTag(const std::string& tag) const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		int GetID() const { return m_ID; }

	private:
		std::vector <std::unique_ptr<GameObject>> m_Objects{};
		int m_ID{};

		static unsigned int m_IdCounter;
	};
}
