#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "Minigin/FPSDisplay.h"
#include "Minigin/GameObject.h"
#include "Minigin/Minigin.h"
#include "Minigin/SceneManager.h"
#include "Minigin/ResourceManager.h"
#include "Minigin/Scene.h"
#include "Minigin/TextRenderer.h"

void Load()
{
	auto& scene{ dae::SceneManager::GetInstance().CreateScene("Demo") };

	std::shared_ptr<dae::Font> pFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	{
		std::unique_ptr pBackground{ std::make_unique<dae::GameObject>() };

		std::shared_ptr<dae::Texture2D> pBackgroundTexture{ dae::ResourceManager::GetInstance().LoadTexture("background.tga") };
		pBackground->AddComponent(std::make_unique<dae::TextureRenderer>(pBackground.get(), pBackgroundTexture));

		scene.Add(std::move(pBackground));
	}

	{
		std::unique_ptr pLogo{ std::make_unique<dae::GameObject>() };

		pLogo->GetTransform().SetLocalPosition(glm::vec2(216, 180));

		std::shared_ptr<dae::Texture2D> pLogoTexture{ dae::ResourceManager::GetInstance().LoadTexture("logo.tga") };
		pLogo->AddComponent(std::make_unique<dae::TextureRenderer>(pLogo.get(), pLogoTexture));

		scene.Add(std::move(pLogo));
	}

	{
		std::unique_ptr pTitleText{ std::make_unique<dae::GameObject>() };

		pTitleText->GetTransform().SetLocalPosition(glm::vec2(80, 20));
		pTitleText->AddComponent(std::make_unique<dae::TextRenderer>(pTitleText.get(), "Programming 4 Assignment :)", pFont, SDL_Color{ 255, 255, 255, 255 }));
		
		scene.Add(std::move(pTitleText));
	}

	{
		std::unique_ptr pFPSDisplay{ std::make_unique<dae::GameObject>() };

		pFPSDisplay->GetTransform().SetLocalPosition(glm::vec2(10, 10));
		pFPSDisplay->AddComponent(std::make_unique<dae::FPSDisplay>(pFPSDisplay.get(), 0.2f, pFont, SDL_Color{ 255, 255, 255, 255 }));

		scene.Add(std::move(pFPSDisplay));
	}

	{
		std::unique_ptr pParent{ std::make_unique<dae::GameObject>() };

		pParent->GetTransform().SetLocalPosition(glm::vec2(250, 250));
		pParent->AddComponent(std::make_unique<dae::TextRenderer>(pParent.get(), "P", pFont, SDL_Color{ 255, 255, 255, 255 }));


		std::unique_ptr pChild{ std::make_unique<dae::GameObject>() };

		pChild->GetTransform().SetLocalPosition(glm::vec2(50, 50));
		pChild->AddComponent(std::make_unique<dae::TextRenderer>(pChild.get(), "C", pFont, SDL_Color{ 255, 255, 255, 255 }));

		pParent->AttachChild(std::move(pChild));

		scene.Add(std::move(pParent));
	}
}

int main(int, char* [])
{
	dae::Minigin engine("Data/");
	engine.Run(Load);
	return 0;
}
