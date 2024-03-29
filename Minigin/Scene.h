#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const std::shared_ptr<GameObject>& object);
		void RemoveAll();

		void Ready() const;
		void Update() const;
		void LateUpdate() const;
		void FixedUpdate() const;
		void Render() const;
		void OnImGui() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend Scene& SceneManager::CreateScene(const std::string& name);
		explicit Scene(std::string name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};
}
