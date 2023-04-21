#include "MoveCommand.h"
#include "MoveComponent.h"

void D2D::MoveCommand::Execute()
{
		m_pMoveComponent->AddMovement(m_Direction);
}
