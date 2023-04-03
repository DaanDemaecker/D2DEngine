#include "MoveCommand.h"
#include "GameObject.h"
#include "MoveComponent.h"
#include <iostream>

void dae::MoveCommand::Execute(const GameObject* Object)
{
	auto moveComponent = Object->GetComponent<MoveComponent>();

	if (moveComponent != nullptr)
	{
		moveComponent->AddMovement(m_Direction);
	}
}
