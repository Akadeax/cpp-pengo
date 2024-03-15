#include "MoveCommand.h"


#include "GameObject.h"
#include "GameTime.h"

MoveCommand::MoveCommand(dae::GameObject* pObject, glm::vec2 dir, float speed)
	: Command(pObject)
	, m_Dir{ dir }
	, m_Speed{ speed }
{
}

void MoveCommand::Execute()
{
	m_pGameObject->GetTransform().Translate(m_Dir * m_Speed * dae::GameTime::GetInstance().GetDeltaTime());
}
