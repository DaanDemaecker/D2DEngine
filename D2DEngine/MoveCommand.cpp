#include "MoveCommand.h"
#include "RigidBodyComponent.h"

void D2D::MoveCommand::Execute()
{
	if (m_pRigidBody != nullptr)
	{
		m_pRigidBody->AddForce(m_Direction * m_pRigidBody->GetMoveSpeed());
	}
}
