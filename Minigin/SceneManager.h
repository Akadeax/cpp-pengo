#pragma once
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
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render() const;

	private:
		friend class Singleton;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
