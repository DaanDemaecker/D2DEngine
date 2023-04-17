#include "MoveCommand.h"
#include "MoveComponent.h"

void dae::MoveCommand::Execute()
{
		m_pMoveComponent->AddMovement(m_Direction);
}
