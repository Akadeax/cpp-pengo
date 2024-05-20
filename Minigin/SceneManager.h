#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		using SceneID = uint8_t;

		Scene& CreateScene(const std::string& name, SceneID sceneIndex);

		void Ready() const;
		void Update() const;
		void LateUpdate() const;
		void HandleDeletion() const;
		void FixedUpdate() const;
		void Render() const;
		void OnImGui() const;

		Scene* GetCurrentScene();
		void SetCurrentScene(SceneID id);

	private:
		friend class Singleton;
		SceneManager() = default;

		std::map<SceneID, std::shared_ptr<Scene>> m_Scenes;
		SceneID m_CurrentSceneId{ 0 };
	};
}
