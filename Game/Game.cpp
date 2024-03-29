#define SDL_MAIN_HANDLED
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <sstream>

#include "ControllerInputDevice.h"
#include "IncreaseScoreCommand.h"
#include "InputManager.h"
#include "LivesDisplay.h"
#include "MoveCommand.h"
#include "PlayerController.h"
#include "RemoveLifeCommand.h"
#include "ScoreDisplay.h"
#include "Minigin/FPSDisplay.h"
#include "Minigin/GameObject.h"
#include "Minigin/Minigin.h"
#include "Minigin/SceneManager.h"
#include "Minigin/ResourceManager.h"
#include "Minigin/Rotator.h"
#include "Minigin/Scene.h"
#include "Minigin/TextRenderer.h"

void Load()
{
	auto& scene{ dae::SceneManager::GetInstance().CreateScene("Demo") };

	std::shared_ptr<dae::Font> pFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	std::shared_ptr<dae::Font> pFontSmall{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 14) };

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
		pFPSDisplay->AddComponent(std::make_unique<dae::Rotator>(pFPSDisplay.get(), 2.f));
		scene.Add(std::move(pFPSDisplay));
	}

	{
		std::unique_ptr pInfo{ std::make_unique<dae::GameObject>() };
		pInfo->GetTransform().SetLocalPosition({ 20, 80 });
		pInfo->AddComponent(std::make_unique<dae::TextRenderer>(
			pInfo.get(), "WASD to move pengo, R to damage, T to increase score", pFontSmall, SDL_Color{ 255, 255, 255, 255 })
		);

		std::unique_ptr pInfo2{ std::make_unique<dae::GameObject>() };
		pInfo2->GetTransform().SetLocalPosition({ 20, 95 });
		pInfo2->AddComponent(std::make_unique<dae::TextRenderer>(
			pInfo2.get(), "D-Pad to move snobee, A to damage, B to increase score", pFontSmall, SDL_Color{ 255, 255, 255, 255 })
		);

		scene.Add(std::move(pInfo));
		scene.Add(std::move(pInfo2));

		// Pengo and its UI
		std::unique_ptr pPengo{ std::make_unique<dae::GameObject>() };
		pPengo->GetTransform().SetLocalPosition(glm::vec2(150, 200));
		pPengo->AddComponent(std::make_unique<dae::TextureRenderer>(pPengo.get(), dae::ResourceManager::GetInstance().LoadTexture("pengo.png")));
		pPengo->AddComponent(std::make_unique<PlayerController>(pPengo.get()));

		std::unique_ptr pPengoLivesDisplay{ std::make_unique<dae::GameObject>() };
		pPengoLivesDisplay->GetTransform().SetLocalPosition({ 20, 120 });
		pPengoLivesDisplay->AddComponent(std::make_unique<dae::TextRenderer>(
			pPengoLivesDisplay.get(), "", pFont, SDL_Color{ 255, 255, 255, 255 })
		);
		pPengoLivesDisplay->AddComponent(std::make_unique<LivesDisplay>(
			pPengoLivesDisplay.get(),
			pPengo->GetComponent<PlayerController>()
		));

		std::unique_ptr pPengoScoreDisplay{ std::make_unique<dae::GameObject>() };
		pPengoScoreDisplay->GetTransform().SetLocalPosition({ 220, 120 });
		pPengoScoreDisplay->AddComponent(std::make_unique<dae::TextRenderer>(
			pPengoScoreDisplay.get(), "", pFont, SDL_Color{ 255, 255, 255, 255 })
		);
		pPengoScoreDisplay->AddComponent(std::make_unique<ScoreDisplay>(
			pPengoScoreDisplay.get(),
			pPengo->GetComponent<PlayerController>()
		));

		scene.Add(std::move(pPengoLivesDisplay));
		scene.Add(std::move(pPengoScoreDisplay));



		// Snobee and its UI
		std::unique_ptr pSnobee{ std::make_unique<dae::GameObject>() };
		pSnobee->GetTransform().SetLocalPosition(glm::vec2(250, 200));
		pSnobee->AddComponent(std::make_unique<dae::TextureRenderer>(pSnobee.get(), dae::ResourceManager::GetInstance().LoadTexture("snobee.png")));
		pSnobee->AddComponent(std::make_unique<PlayerController>(pSnobee.get()));

		std::unique_ptr pSnobeeLivesDisplay{ std::make_unique<dae::GameObject>() };
		pSnobeeLivesDisplay->GetTransform().SetLocalPosition({ 20, 150 });
		pSnobeeLivesDisplay->AddComponent(std::make_unique<dae::TextRenderer>(
			pSnobeeLivesDisplay.get(), "", pFont, SDL_Color{ 255, 255, 255, 255 })
		);
		pSnobeeLivesDisplay->AddComponent(std::make_unique<LivesDisplay>(
			pSnobeeLivesDisplay.get(),
			pSnobee->GetComponent<PlayerController>()
			));

		std::unique_ptr pSnobeeScoreDisplay{ std::make_unique<dae::GameObject>() };
		pSnobeeScoreDisplay->GetTransform().SetLocalPosition({ 220, 150 });
		pSnobeeScoreDisplay->AddComponent(std::make_unique<dae::TextRenderer>(
			pSnobeeScoreDisplay.get(), "", pFont, SDL_Color{ 255, 255, 255, 255 })
		);
		pSnobeeScoreDisplay->AddComponent(std::make_unique<ScoreDisplay>(
			pSnobeeScoreDisplay.get(),
			pSnobee->GetComponent<PlayerController>()
		));

		scene.Add(std::move(pSnobeeLivesDisplay));
		scene.Add(std::move(pSnobeeScoreDisplay));


		constexpr float speed{ 100.f };

		// Add Keyboard Input
		std::unique_ptr keyboard{ std::make_unique<dae::KeyboardInputDevice>() };
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_W,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pPengo.get(), glm::vec2{0.f, -1.f}, speed)
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_D,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pPengo.get(), glm::vec2{ 1.f, 0.f }, speed)
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_S,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pPengo.get(), glm::vec2{ 0.f, 1.f }, speed)
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_A,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pPengo.get(), glm::vec2{ -1.f, 0.f }, speed)
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_R,
			dae::InputDevice::InputState::up,
			std::make_unique<RemoveLifeCommand>(pPengo.get())
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_T,
			dae::InputDevice::InputState::up,
			std::make_unique<IncreaseScoreCommand>(pPengo.get())
		);
		dae::InputManager::GetInstance().RegisterInputDevice(std::move(keyboard));


		// Add Controller Input
		std::unique_ptr controller{ std::make_unique<dae::ControllerInputDevice>(0) };
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadUp,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ 0.f, -1.f }, speed * 2)
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadRight,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ 1.f, 0.f }, speed * 2)
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadDown,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ 0.f, 1.f }, speed * 2)
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadLeft,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ -1.f, 0.f }, speed * 2)
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::a,
			dae::InputDevice::InputState::up,
			std::make_unique<RemoveLifeCommand>(pSnobee.get())
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::b,
			dae::InputDevice::InputState::up,
			std::make_unique<IncreaseScoreCommand>(pSnobee.get())
		);
		dae::InputManager::GetInstance().RegisterInputDevice(std::move(controller));



		scene.Add(std::move(pPengo));
		scene.Add(std::move(pSnobee));
	}





}

int main(int, char* [])
{
	SDL_SetMainReady();

	dae::Minigin engine("Data/");
	engine.Run(Load);
	return 0;
}
