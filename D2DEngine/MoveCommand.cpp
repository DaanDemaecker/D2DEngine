#include "MoveCommand.h"
#include "Transform.h"
#include "TimeManager.h"

void D2D::MoveCommand::Execute()
{
	if (m_pTransform != nullptr)
	{
		m_pTransform->MoveLocalPosition(m_Direction * m_Speed * TimeManager::GetInstance().GetDeltaTime());
	}
}
