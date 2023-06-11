#include "pch.h"
#include "VersusPlayer.h"
#include "WorldEvents.h"
#include "InputManager.h"
#include "FunctionCommand.h"
#include "TimeManager.h"
#include "Transform.h"
#include "PhysicsManager.h"
#include "Collider.h"
#include "EnemyMovementStates.h"
#include "RenderComponent.h"
#include "BaseEnemyComponent.h"
#include "Subject.h"
#include <iostream>

void D2D::VersusPlayer::FixedUpdate()
{
	if (m_pControlledEnemy == nullptr)
	{
		MovePlayer();
	}
	else
	{
		MoveEnemy();
	}
}

void D2D::VersusPlayer::Setup(const std::string& sceneName, float speed, int controllerIdx, const glm::vec2& levelMin, const glm::vec2& levelMax)
{
	m_Speed = speed;

	m_LevelMin = levelMin;
	m_LevelMax = levelMax;

	auto& input = InputManager::GetInstance();

	input.AddGamepadCommand(controllerIdx, GamepadButton::DpadUp, D2D::keyState::pressed, std::make_unique<D2D::FunctionCommand>(std::bind(&VersusPlayer::Move, this,  glm::vec2{ 0, -1 })), sceneName);
	input.AddGamepadCommand(controllerIdx, GamepadButton::DpadLeft, D2D::keyState::pressed, std::make_unique<D2D::FunctionCommand>(std::bind(&VersusPlayer::Move, this, glm::vec2{ -1, 0 })), sceneName);
	input.AddGamepadCommand(controllerIdx, GamepadButton::DpadDown, D2D::keyState::pressed, std::make_unique<D2D::FunctionCommand>(std::bind(&VersusPlayer::Move, this, glm::vec2{ 0, 1 })), sceneName);
	input.AddGamepadCommand(controllerIdx, GamepadButton::DpadRight, D2D::keyState::pressed, std::make_unique<D2D::FunctionCommand>(std::bind(&VersusPlayer::Move, this, glm::vec2{ 1, 0 })), sceneName);

	input.AddGamepadCommand(controllerIdx, GamepadButton::ButtonSouth, D2D::keyState::Down, std::make_unique<D2D::FunctionCommand>(std::bind(&VersusPlayer::Pick, this)), sceneName);

}

void D2D::VersusPlayer::Move(const glm::vec2& direction)
{
	m_Direction = direction;
}

void D2D::VersusPlayer::Pick()
{
	if (m_pControlledEnemy != nullptr)
		return;

	auto pos{ GetTransform()->GetWorldPosition() };

	auto result{ PhysicsManager::GetInstance().Raycast(pos - glm::vec2{1, 1}, pos + glm::vec2{1, 1})};

	if (result != nullptr)
	{
		auto pEnemy{result->GetComponent<BaseEnemyComponent>()};

		if (pEnemy)
		{
			auto pEnemyController{ std::make_unique<ControlledState>() };
			m_pControlledEnemy = pEnemyController.get();

			pEnemy->SetMovementState(std::move(pEnemyController));
			pEnemy->AddObserver(this);

			GetComponent<RenderComponent>()->SetActive(false);
		}
	}
}

void D2D::VersusPlayer::Notify(const Event& event)
{
	if (const auto enemyDieEvent{ dynamic_cast<const EnemyDieEvent*>(&event) })
	{
		m_pControlledEnemy = nullptr;
		GetComponent<RenderComponent>()->SetActive(true);
	}
}

void D2D::VersusPlayer::MovePlayer()
{
	m_Direction = glm::normalize(m_Direction) * m_Speed * TimeManager::GetInstance().GetFixedTime();

	auto pos{ GetTransform()->GetWorldPosition()};

	if (pos.x  + m_Direction.x > m_LevelMin.x &&
		pos.x + m_Direction.x < m_LevelMax.x &&
		pos.y + m_Direction.y > m_LevelMin.y &&
		pos.y + m_Direction.y < m_LevelMax.y)
	{
		GetTransform()->MoveLocalPosition(m_Direction);
	}

	pos = GetTransform()->GetWorldPosition();

	GetTransform()->SetWorldPosition({std::max(pos.x, m_LevelMin.x), std::max(pos.y, m_LevelMin.y)});

	pos = GetTransform()->GetWorldPosition();

	GetTransform()->SetWorldPosition({ std::min(pos.x, m_LevelMax.x), std::min(pos.y, m_LevelMax.y) });

	m_Direction = glm::vec2{};
}

void D2D::VersusPlayer::MoveEnemy()
{
	m_pControlledEnemy->SetDirection(m_Direction);
	m_Direction = glm::vec2{};
}
