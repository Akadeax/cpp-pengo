#include "Scenes.h"

#include <glm/vec2.hpp>

#include "AnimatedTextureRenderer.h"
#include "ControllerInputDevice.h"
#include "Font.h"
#include "GameManager.h"
#include "GameObject.h"
#include "GridManager.h"
#include "InputManager.h"
#include "KeyboardInputDevice.h"
#include "LivesDisplay.h"
#include "Minigin.h"
#include "PlayerController.h"
#include "PlayerInteractCommand.h"
#include "PlayerMoveCommand.h"
#include "PlayerStateMachine.h"
#include "ResourceSystem.h"
#include "SaveData.h"
#include "Scene.h"
#include "ScoreDisplay.h"
#include "ServiceLocator.h"
#include "SkipLevelCommand.h"
#include "TextRenderer.h"
#include "TextureRenderer.h"
#include "UIAnchor.h"
#include "UIButton.h"
#include "UITextColorButton.h"

using std::shared_ptr, std::unique_ptr, std::make_unique;
using dae::GameObject;

unique_ptr<dae::Scene> CreateMenuScene()
{
	unique_ptr pScene{ make_unique<dae::Scene>(0) };


	shared_ptr<dae::Font> pFont{
	dae::ServiceLocator::GetResourceSystem().LoadFont("Data/pixelFont.otf", 12)
	};

	unique_ptr pTitleAnchor{ make_unique<GameObject>() };
	unique_ptr pTitleAnchorComp{ make_unique<dae::UIAnchor>(pTitleAnchor.get(), dae::UIAnchorPoint::center) };

	unique_ptr pTitle{ make_unique<GameObject>() };
	unique_ptr pTitleText{ make_unique<dae::TextRenderer>(
		pTitleAnchor.get(),
		"Start Game", pFont,
		SDL_Color{ 255, 255, 255, 255 },
		dae::TextAlign::center, dae::TextAlign::center,
		pTitleAnchorComp.get()
	) };

	unique_ptr pTitleButton{ make_unique<dae::UITextColorButton>(pTitle.get(), glm::vec2{ 130, 15 }) };

	pTitleButton->MouseUp.Connect([]
		{
			dae::SceneManager::GetInstance().QueueSceneLoadForEndOfFrame(CreateFirstGameScene);
		});

	pTitleAnchor->AddComponent(std::move(pTitleAnchorComp));
	pTitle->AddComponent(std::move(pTitleText));
	pTitle->AddComponent(std::move(pTitleButton));

	pTitleAnchor->AttachChild(std::move(pTitle));
	pScene->Add(std::move(pTitleAnchor));

	return std::move(pScene);
}


unique_ptr<dae::Scene> CreateGameScene(const std::string& levelFilePath, int id)
{
	unique_ptr pScene{ make_unique<dae::Scene>(id) };

	shared_ptr<dae::Font> pFont{
		dae::ServiceLocator::GetResourceSystem().LoadFont("Data/pixelFont.otf", 14)
	};

	const glm::vec2 centerScreen{ dae::Minigin::WINDOW_WIDTH / 2.f, dae::Minigin::WINDOW_HEIGHT / 2.f };

#pragma region main setup (world, etc)
	{
		unique_ptr pGridManager{ make_unique<GameObject>("GridManager") };
		pGridManager->GetTransform().SetLocalPosition(centerScreen);
		pGridManager->GetTransform().SetLocalScale({ 1.5f, 1.5f });

		pGridManager->AddComponent(make_unique<GridManager>(pGridManager.get(), levelFilePath));

		unique_ptr pArena{ make_unique<GameObject>() };
		pArena->GetTransform().SetLocalScale({ 1.5f, 1.5f });
		const glm::vec2 offset{
			static_cast<float>(GridManager::BLOCK_SQUARE_SIZE) * (glm::vec2{ GridManager::GRID_WIDTH, GridManager::GRID_HEIGHT } / 2.f * 1.5f)
		};
		pArena->GetTransform().SetLocalPosition(centerScreen - offset);
		pArena->AddComponent(make_unique<dae::TextureRenderer>(
			pArena.get(),
			dae::ServiceLocator::GetResourceSystem().LoadTexture("Data/arena.png")
		));


		pScene->Add(std::move(pArena));
		pScene->Add(std::move(pGridManager));
	}

	{
		unique_ptr pGameManager{ make_unique<GameObject>("GameManager") };
		pGameManager->GetTransform().SetLocalPosition(centerScreen);
		pGameManager->GetTransform().SetLocalScale({ 1.5f, 1.5f });

		pGameManager->AddComponent(make_unique<GameManager>(pGameManager.get()));
		pScene->Add(std::move(pGameManager));
	}
#pragma endregion
#pragma region player
	{
		// Pengo and its UI
		unique_ptr pPengo{ make_unique<GameObject>("Player") };
		pPengo->GetTransform().SetLocalPosition(centerScreen);
		pPengo->GetTransform().SetLocalScale({ 1.5f, 1.5f });
		pPengo->AddComponent(make_unique<dae::AnimatedTextureRenderer>(
			pPengo.get(),
			dae::ServiceLocator::GetResourceSystem().LoadTexture("Data/pengo_red.png"),
			4, 8
		));
		pPengo->AddComponent(make_unique<PlayerController>(pPengo.get()));

		// State machine
		auto stateMachine{ make_unique<PlayerStateMachine>(pPengo.get()) };

		pPengo->AddComponent(std::move(stateMachine));


		// Add Keyboard Input
		unique_ptr keyboard{ make_unique<dae::KeyboardInputDevice>() };
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_W,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 0.f, -1.f })
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_D,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 1.f, 0.f })
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_S,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 0.f, 1.f })
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_A,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ -1.f, 0.f })
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_R,
			dae::InputDevice::InputState::up,
			make_unique<PlayerInteractCommand>(pPengo.get())
		);
		keyboard->BindKeyboardButton(
			SDL_SCANCODE_F1,
			dae::InputDevice::InputState::up,
			make_unique<SkipLevelCommand>(pScene->GetGameObjectByTag("GameManager"))
		);
		dae::InputManager::GetInstance().RegisterInputDevice(std::move(keyboard));


		// Add Controller Input
		unique_ptr controller{ make_unique<dae::ControllerInputDevice>(0) };
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadUp,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 0.f, -1.f })
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadRight,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 1.f, 0.f })
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadDown,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ 0.f, 1.f })
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::dpadLeft,
			dae::InputDevice::InputState::press,
			make_unique<PlayerMoveCommand>(pPengo.get(), glm::vec2{ -1.f, 0.f })
		);
		controller->BindControllerButton(
			dae::ControllerInputDevice::ControllerButton::a,
			dae::InputDevice::InputState::up,
			make_unique<PlayerInteractCommand>(pPengo.get())
		);
		dae::InputManager::GetInstance().RegisterInputDevice(std::move(controller));



		{
			unique_ptr pLivesAnchor{ make_unique<GameObject>() };
			unique_ptr pLivesAnchorComp{ make_unique<dae::UIAnchor>(pLivesAnchor.get(), dae::UIAnchorPoint::topLeft) };
			pLivesAnchorComp->offset = glm::vec2{ 10, 10 };
			pLivesAnchor->AddComponent(std::move(pLivesAnchorComp));

			unique_ptr pLivesDisplay{ make_unique<GameObject>() };
			pLivesDisplay->AddComponent(make_unique<dae::TextRenderer>(
				pLivesDisplay.get(),
				"Lives: x", pFont,
				SDL_Color{ 255, 255, 255, 255 }
			));
			pLivesDisplay->AddComponent(make_unique<LivesDisplay>(
				pLivesDisplay.get(),
				pPengo->GetComponent<PlayerController>()
			));

			pLivesAnchor->AttachChild(std::move(pLivesDisplay));
			pScene->Add(std::move(pLivesAnchor));
		}
		{
			unique_ptr pScoreAnchor{ make_unique<GameObject>() };
			unique_ptr pScoreAnchorComp{ make_unique<dae::UIAnchor>(pScoreAnchor.get(), dae::UIAnchorPoint::topRight) };
			pScoreAnchorComp->offset = glm::vec2{ -10, 10 };
			pScoreAnchor->AddComponent(std::move(pScoreAnchorComp));

			unique_ptr pScoreDisplay{ make_unique<GameObject>() };
			pScoreDisplay->AddComponent(make_unique<dae::TextRenderer>(
				pScoreDisplay.get(),
				"Score: x", pFont,
				SDL_Color{ 255, 255, 255, 255 },
				dae::TextAlign::end
			));
			pScoreDisplay->AddComponent(make_unique<ScoreDisplay>(
				pScoreDisplay.get(),
				pPengo->GetComponent<PlayerController>()
			));

			pScoreAnchor->AttachChild(std::move(pScoreDisplay));
			pScene->Add(std::move(pScoreAnchor));
		}

		pScene->Add(std::move(pPengo));
	}
#pragma endregion

	if (id > 1)
	{
		SaveData::GetInstance().LoadCrossLevelData(pScene.get());
	}

	return std::move(pScene);
}


unique_ptr<dae::Scene> CreateFirstGameScene()
{
	return CreateGameScene("Data/Levels/1.json", 1);
}
