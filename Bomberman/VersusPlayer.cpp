#include "pch.h"
#include "VersusPlayer.h"
#include "WorldEvents.h"
#include "InputManager.h"
#include "FunctionCommand.h"
#include "TimeManager.h"
#include "Transform.h"

void D2D::VersusPlayer::Update()
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

}

void D2D::VersusPlayer::Move(const glm::vec2& direction)
{
	m_Direction = direction;
}

void D2D::VersusPlayer::Notify(const Event& event)
{
	if (const auto enemyDieEvent{ dynamic_cast<const EnemyDieEvent*>(&event) })
	{
		m_pControlledEnemy = nullptr;
	}
}

void D2D::VersusPlayer::MovePlayer()
{
	m_Direction = glm::normalize(m_Direction) * m_Speed * TimeManager::GetInstance().GetDeltaTime();

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
}
