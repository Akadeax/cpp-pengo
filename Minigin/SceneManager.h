#pragma once
#include <memory>

#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void SetCurrentScene(std::unique_ptr<Scene> pScene);
		void QueueSceneLoadForEndOfFrame(std::function<std::unique_ptr<Scene>()> sceneBuilder);

		void Ready() const;
		void Update() const;
		void LateUpdate() const;
		void HandleDeletion();
		void FixedUpdate() const;
		void Render() const;
		void OnImGui() const;

		Scene* GetCurrentScene() const;

	private:
		friend class Singleton;
		SceneManager() = default;

		std::unique_ptr<Scene> m_pScene;
		std::function<std::unique_ptr<Scene>()> m_QueuedSceneLoad{};
	};
}
