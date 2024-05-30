#define SDL_MAIN_HANDLED
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <sstream>
#include "AnimatedTextureRenderer.h"
#include "ControllerInputDevice.h"
#include "GameManager.h"
#include "GridManager.h"
#include "IncreaseScoreCommand.h"
#include "InputManager.h"
#include "PlayerMoveCommand.h"
#include "PlayerController.h"
#include "PlayerInteractCommand.h"
#include "PlayerStateMachine.h"
#include "SDLResourceSystem.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "Minigin/GameObject.h"
#include "Minigin/Minigin.h"
#include "Minigin/SceneManager.h"
#include "Minigin/Scene.h"

void Load()
{
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	dae::ServiceLocator::GetSoundSystem().RegisterSound(
		dae::SoundSystem::SoundType::sfx,
		"Data/Sound/act_start.mp3"
	);
	dae::ServiceLocator::RegisterResourceSystem(std::make_unique<dae::SDLResourceSystem>());

	auto& scene{ dae::SceneManager::GetInstance().CreateScene("Demo", 0) };

	std::shared_ptr<dae::Font> pFont{
		dae::ServiceLocator::GetResourceSystem().LoadFont("Data/Lingua.otf", 36)
	};
	std::shared_ptr<dae::Font> pFontSmall{
		dae::ServiceLocator::GetResourceSystem().LoadFont("Data/Lingua.otf", 14)
	};

	const glm::vec2 centerScreen{ dae::Minigin::WINDOW_WIDTH / 2.f, dae::Minigin::WINDOW_HEIGHT / 2.f };
	{
		std::unique_ptr pGridManager{ std::make_unique<dae::GameObject>("GridManager")};
		pGridManager->GetTransform().SetLocalPosition(centerScreen);
		pGridManager->GetTransform().SetLocalScale({ 1.5f, 1.5f });

		pGridManager->AddComponent(std::make_unique<GridManager>(pGridManager.get()));
		scene.Add(std::move(pGridManager));
	}

	{
		std::unique_ptr pGameManager{ std::make_unique<dae::GameObject>("GameManager") };
		pGameManager->GetTransform().SetLocalPosition(centerScreen);
		pGameManager->GetTransform().SetLocalScale({ 1.5f, 1.5f });

		pGameManager->AddComponent(std::make_unique<GameManager>(pGameManager.get()));
		scene.Add(std::move(pGameManager));
	}


	{
		//std::unique_ptr pInfo{ std::make_unique<dae::GameObject>() };
		//pInfo->GetTransform().SetLocalPosition({ 20, 80 });
		//pInfo->AddComponent(std::make_unique<dae::TextRenderer>(
		//	pInfo.get(), "WASD to move pengo, R to damage, T to increase score", pFontSmall, SDL_Color{ 255, 255, 255, 255 })
		//);

		//std::unique_ptr pInfo2{ std::make_unique<dae::GameObject>() };
		//pInfo2->GetTransform().SetLocalPosition({ 20, 95 });
		//pInfo2->AddComponent(std::make_unique<dae::TextRenderer>(
		//	pInfo2.get(), "D-Pad to move snobee, A to damage, B to increase score", pFontSmall, SDL_Color{ 255, 255, 255, 255 })
		//);

		//scene.Add(std::move(pInfo));
		//scene.Add(std::move(pInfo2));
	}

	{
		// Pengo and its UI
		std::unique_ptr pPengo{ std::make_unique<dae::GameObject>() };
		pPengo->GetTransform().SetLocalPosition(glm::vec2(150, 200));
		pPengo->GetTransform().SetLocalScale({ 1.5f, 1.5f });
		pPengo->AddComponent(std::make_unique<dae::AnimatedTextureRenderer>(
			pPengo.get(),
			dae::ServiceLocator::GetResourceSystem().LoadTexture("Data/pengo_red.png"),
			4, 8
		));
		pPengo->AddComponent(std::make_unique<PlayerController>(pPengo.get()));

		// State machine
		auto stateMachine{ std::make_unique<PlayerStateMachine>(pPengo.get()) };

		pPengo->AddComponent(std::move(stateMachine));

		//std::unique_ptr pPengoLivesDisplay{ std::make_unique<dae::GameObject>() };
		//pPengoLivesDisplay->GetTransform().SetLocalPosition({ 20, 120 });
		//pPengoLivesDisplay->AddComponent(std::make_unique<dae::TextRenderer>(
		//	pPengoLivesDisplay.get(), "", pFont, SDL_Color{ 255, 255, 255, 255 })
		//);
		//pPengoLivesDisplay->AddComponent(std::make_unique<LivesDisplay>(
		//	pPengoLivesDisplay.get(),
		//	pPengo->GetComponent<PlayerController>()
		//));

		//std::unique_ptr pPengoScoreDisplay{ std::make_unique<dae::GameObject>() };
		//pPengoScoreDisplay->GetTransform().SetLocalPosition({ 220, 120 });
		//pPengoScoreDisplay->AddComponent(std::make_unique<dae::TextRenderer>(
		//	pPengoScoreDisplay.get(), "", pFont, SDL_Color{ 255, 255, 255, 255 })
		//);
		//pPengoScoreDisplay->AddComponent(std::make_unique<ScoreDisplay>(
		//	pPengoScoreDisplay.get(),
		//	pPengo->GetComponent<PlayerController>()
		//));

		//scene.Add(std::move(pPengoLivesDisplay));
		//scene.Add(std::move(pPengoScoreDisplay));



		// Snobee and its UI
		/*std::unique_ptr pSnobee{ std::make_unique<dae::GameObject>() };
		pSnobee->GetTransform().SetLocalPosition(glm::vec2(250, 200));
		pSnobee->AddComponent(std::make_unique<dae::TextureRenderer>(pSnobee.get(), dae::ServiceLocator::GetResourceSystem().LoadTexture("snobee.png")));
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
		scene.Add(std::move(pSnobeeScoreDisplay));*/



		// Add Keyboard Input
		std::unique_ptr keyboard{ std::make_unique<dae::KeyboardInputDevice>() };
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_W,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{0.f, -1.f})
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_D,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 1.f, 0.f })
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_S,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 0.f, 1.f })
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_A,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ -1.f, 0.f })
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_R,
			dae::InputDevice::InputState::up,
			std::make_unique<PlayerInteractCommand>(pPengo.get())
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_T,
			dae::InputDevice::InputState::up,
			std::make_unique<IncreaseScoreCommand>(pPengo.get())
		);
		dae::InputManager::GetInstance().RegisterInputDevice(std::move(keyboard));


		// Add Controller Input
		/*std::unique_ptr controller{ std::make_unique<dae::ControllerInputDevice>(0) };
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadUp,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pSnobee.get(), glm::vec2{ 0.f, -1.f })
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadRight,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pSnobee.get(), glm::vec2{ 1.f, 0.f })
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadDown,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pSnobee.get(), glm::vec2{ 0.f, 1.f })
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadLeft,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pSnobee.get(), glm::vec2{ -1.f, 0.f })
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
		dae::InputManager::GetInstance().RegisterInputDevice(std::move(controller));*/



		scene.Add(std::move(pPengo));
		//scene.Add(std::move(pSnobee));

	}
}

int main(int, char* [])
{
	SDL_SetMainReady();

	dae::Minigin engine("Data/");
	engine.Run(Load);
	return 0;
}
