#pragma once
#include <map>
#include <memory>
#include <optional>

#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* MakeSceneForID(uint16_t id);

		void QueueSceneLoadForEndOfFrame(uint16_t id);

		void Ready() const;
		void Update() const;
		void LateUpdate() const;
		void HandleDeletion();
		void FixedUpdate() const;
		void Render() const;
		void OnImGui() const;

		Scene* GetCurrentScene();
		uint16_t GetCurrentSceneID();
		void SetCurrentScene(uint16_t id);

	private:
		friend class Singleton;
		SceneManager() = default;

		std::map<uint16_t, std::unique_ptr<Scene>> m_Scenes;
		uint16_t m_CurrentSceneId{ 0 };

		std::optional<uint16_t> m_QueuedSceneLoad{ std::nullopt };
	};
}
