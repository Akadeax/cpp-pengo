#include "Scenes.h"

#include <glm/vec2.hpp>

#include "AnimatedTextureRenderer.h"
#include "Font.h"
#include "GameManager.h"
#include "GameObject.h"
#include "GridManager.h"
#include "IncreaseScoreCommand.h"
#include "InputManager.h"
#include "KeyboardInputDevice.h"
#include "Minigin.h"
#include "PlayerController.h"
#include "PlayerInteractCommand.h"
#include "PlayerMoveCommand.h"
#include "PlayerStateMachine.h"
#include "ResourceSystem.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "TextureRenderer.h"

void CreateMenuScene()
{
}

void CreateGameScene(const std::string& levelFilePath, uint16_t id)
{
	dae::Scene* pScene{ dae::SceneManager::GetInstance().MakeSceneForID(id) };

	std::shared_ptr<dae::Font> pFont{
		dae::ServiceLocator::GetResourceSystem().LoadFont("Data/Lingua.otf", 36)
	};
	std::shared_ptr<dae::Font> pFontSmall{
		dae::ServiceLocator::GetResourceSystem().LoadFont("Data/Lingua.otf", 14)
	};

	const glm::vec2 centerScreen{ dae::Minigin::WINDOW_WIDTH / 2.f, dae::Minigin::WINDOW_HEIGHT / 2.f };

	{
		std::unique_ptr pGridManager{ std::make_unique<dae::GameObject>("GridManager") };
		pGridManager->GetTransform().SetLocalPosition(centerScreen);
		pGridManager->GetTransform().SetLocalScale({ 1.5f, 1.5f });

		pGridManager->AddComponent(std::make_unique<GridManager>(pGridManager.get(), levelFilePath));

		std::unique_ptr pArena{ std::make_unique<dae::GameObject>() };
		pArena->GetTransform().SetLocalScale({ 1.5f, 1.5f });
		const glm::vec2 offset{
			static_cast<float>(GridManager::BLOCK_SQUARE_SIZE) * (glm::vec2{ GridManager::GRID_WIDTH, GridManager::GRID_HEIGHT } / 2.f * 1.5f)
		};
		pArena->GetTransform().SetLocalPosition(centerScreen - offset);
		pArena->AddComponent(std::make_unique<dae::TextureRenderer>(
			pArena.get(),
			dae::ServiceLocator::GetResourceSystem().LoadTexture("Data/arena.png")
		));


		pScene->Add(std::move(pArena));
		pScene->Add(std::move(pGridManager));
	}

	{
		std::unique_ptr pGameManager{ std::make_unique<dae::GameObject>("GameManager") };
		pGameManager->GetTransform().SetLocalPosition(centerScreen);
		pGameManager->GetTransform().SetLocalScale({ 1.5f, 1.5f });

		pGameManager->AddComponent(std::make_unique<GameManager>(pGameManager.get()));
		pScene->Add(std::move(pGameManager));
	}

	{
		// Pengo and its UI
		std::unique_ptr pPengo{ std::make_unique<dae::GameObject>() };
		pPengo->GetTransform().SetLocalPosition(centerScreen);
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


		// Add Keyboard Input
		std::unique_ptr keyboard{ std::make_unique<dae::KeyboardInputDevice>() };
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_W,
			dae::InputDevice::InputState::press,
			std::make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 0.f, -1.f })
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


		pScene->Add(std::move(pPengo));
	}
}
