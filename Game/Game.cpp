#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin/GameObject.h"
#include "Minigin/Minigin.h"
#include "Minigin/SceneManager.h"
#include "Minigin/ResourceManager.h"
#include "Minigin/Scene.h"
#include "Minigin/TextRenderer.h"

void Load()
{
	auto& scene{ dae::SceneManager::GetInstance().CreateScene("Demo") };

	{
		const std::shared_ptr pBackground{ std::make_shared<dae::GameObject>() };

		std::shared_ptr<dae::Texture2D> pBackgroundTexture{ dae::ResourceManager::GetInstance().LoadTexture("background.tga") };
		pBackground->AddComponent(std::make_unique<dae::TextureRenderer>(pBackground.get(), pBackgroundTexture));

		scene.Add(pBackground);
	}

	{
		const std::shared_ptr pLogo{ std::make_shared<dae::GameObject>() };

		pLogo->GetTransform().SetPosition(216, 180);

		std::shared_ptr<dae::Texture2D> pLogoTexture{ dae::ResourceManager::GetInstance().LoadTexture("logo.tga") };
		pLogo->AddComponent(std::make_unique<dae::TextureRenderer>(pLogo.get(), pLogoTexture));

		scene.Add(pLogo);
	}

	{
		std::shared_ptr<dae::Font> pFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

		const std::shared_ptr pTitleText{ std::make_shared<dae::GameObject>() };

		pTitleText->GetTransform().SetPosition(80, 20);
		pTitleText->AddComponent(std::make_unique<dae::TextRenderer>(pTitleText.get(), "Programming 4 Assignment :)", pFont, SDL_Color{ 255, 255, 255, 255 }));
		
		scene.Add(pTitleText);
	}
}

int main(int, char* [])
{
	dae::Minigin engine("Data/");
	engine.Run(Load);
	return 0;
}
