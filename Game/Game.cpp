#define SDL_MAIN_HANDLED
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "CacheThrasher.h"
#include "ControllerInputDevice.h"
#include "InputManager.h"
#include "MoveCommand.h"
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
		// Scene tree:
		// pCenterParent (rotates) -> pPengo (rotates) -> pSnobee
		std::unique_ptr pCenterParent{ std::make_unique<dae::GameObject>() };
		pCenterParent->GetTransform().SetLocalPosition(glm::vec2(250, 250));
		//pCenterParent->AddComponent(std::make_unique<dae::Rotator>(pCenterParent.get(), 2.f));

		std::unique_ptr pPengo{ std::make_unique<dae::GameObject>() };
		pPengo->GetTransform().SetLocalPosition(glm::vec2(50, 0));
		pPengo->AddComponent(std::make_unique<dae::TextureRenderer>(pPengo.get(), dae::ResourceManager::GetInstance().LoadTexture("pengo.png")));
		//pPengo->AddComponent(std::make_unique<dae::Rotator>(pPengo.get(), 2.f));

		std::unique_ptr pSnobee{ std::make_unique<dae::GameObject>() };
		pSnobee->GetTransform().SetLocalPosition(glm::vec2(50, 0));
		pSnobee->AddComponent(std::make_unique<dae::TextureRenderer>(pSnobee.get(), dae::ResourceManager::GetInstance().LoadTexture("snobee.png")));

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
		dae::InputManager::GetInstance().RegisterInputDevice(std::move(keyboard));


		// Add Controller Input
		std::unique_ptr controller{ std::make_unique<dae::ControllerInputDevice>(0) };
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadUp,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ 0.f, -1.f }, speed)
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadRight,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ 1.f, 0.f }, speed)
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadDown,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ 0.f, 1.f }, speed)
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadLeft,
			dae::InputDevice::InputState::press,
			std::make_unique<MoveCommand>(pSnobee.get(), glm::vec2{ -1.f, 0.f }, speed)
		);

		dae::InputManager::GetInstance().RegisterInputDevice(std::move(controller));



		pPengo->AttachChild(std::move(pSnobee));
		pCenterParent->AttachChild(std::move(pPengo));
		scene.Add(std::move(pCenterParent));
	}





}

int main(int, char* [])
{
	SDL_SetMainReady();

	dae::Minigin engine("Data/");
	engine.Run(Load);
	return 0;
}
