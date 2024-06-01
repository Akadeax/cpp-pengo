#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		explicit Scene(uint16_t id);

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
		uint16_t m_ID;
		std::vector <std::unique_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};
}
