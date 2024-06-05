#include "SnobeeChaseState.h"

#include <algorithm>
#include <random>

#include "AnimatedTextureRenderer.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Scene.h"
#include "GridManager.h"
#include "SceneManager.h"
#include "SnobeeController.h"
#include "SnobeeStateMachine.h"

SnobeeChaseState::SnobeeChaseState(
	SnobeeController* pSnobeeController,
	SnobeeStateMachine* pStateMachine,
	dae::AnimatedTextureRenderer* pRenderer
)
	: SnobeeState(pSnobeeController, pStateMachine, pRenderer)
{
	const dae::Scene* pScene{ dae::SceneManager::GetInstance().GetCurrentScene() };
	m_pGridManager = pScene->GetGameObjectByTag("GridManager")->GetComponent<GridManager>();

	m_ChaseUp = GetRenderer()->   AddAnimation({ .3f, { 12, 13 } });
	m_ChaseRight = GetRenderer()->AddAnimation({ .3f, { 14, 15 } });
	m_ChaseDown = GetRenderer()-> AddAnimation({ .3f, { 8, 9 } });
	m_ChaseLeft = GetRenderer()-> AddAnimation({ .3f, { 10, 11 } });
}

void SnobeeChaseState::OnEnter()
{
	m_MoveStartPos = GetSnobeeController()->GetParent()->GetTransform().GetLocalPosition();
	m_MoveTargetPos = m_MoveStartPos;
	m_MoveDir = glm::ivec2{ 0, -1 };
}

void SnobeeChaseState::Update()
{
	if (m_TimeUntilNextMove <= 0.f)
	{
		GetSnobeeController()->GetParent()->GetTransform().SetLocalPosition(m_MoveTargetPos);
		m_MoveStartPos = m_MoveTargetPos;

		// convert all our positions into grid coordinates so we can check for blocks
		const glm::vec2 startAsGrid{ m_pGridManager->LocalToGrid(m_MoveStartPos, false) };

		std::vector<glm::ivec2> directions{ { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

		std::random_device rd;
		std::mt19937 g(rd());
		std::ranges::shuffle(directions, g);

		for (const glm::ivec2& dir : directions)
		{
			const glm::vec2 target{ startAsGrid + glm::vec2{ dir.x, dir.y } };
			if (!m_pGridManager->IsGridPositionValid(target)) continue;
			if (m_pGridManager->HasBlock(target))
			{
				// 50/50 whether it continues or destroys the block
				if (g() % 2 == 0)
				{
					continue;
				}
				const bool destroySuccess{ m_pGridManager->GetBlock(target)->Destroy(false) };
				if (!destroySuccess) continue;
			}

			m_MoveDir = dir;
			break;
		}

		const glm::vec2 targetAsGrid{ startAsGrid + glm::vec2{ m_MoveDir.x, m_MoveDir.y } };
		m_MoveTargetPos = m_pGridManager->GridToLocal(targetAsGrid, false);

		m_TimeUntilNextMove = m_MoveTime;
		GetRenderer()->SetDirectionalAnimation(
			m_MoveDir,
			m_ChaseUp,
			m_ChaseRight,
			m_ChaseDown,
			m_ChaseLeft
		);

		return;
	}

	m_TimeUntilNextMove -= dae::GameTime::GetInstance().GetDeltaTime();

	const float lerpFactor{ (m_MoveTime - m_TimeUntilNextMove) / m_MoveTime };
	GetSnobeeController()->GetParent()->GetTransform().SetLocalPosition(
		mix(m_MoveStartPos, m_MoveTargetPos, lerpFactor)
	);
}

void SnobeeChaseState::OnExit()
{
	GetSnobeeController()->GetParent()->GetTransform().SetLocalPosition(m_MoveTargetPos);
}
