#include "pch.h"
#include "CameraComponent.h"
#include "Transform.h"
#include <SDL.h>
#include <algorithm>

extern SDL_Window* g_window;

D2D::CameraComponent::CameraComponent()
{
	SDL_GetWindowSize(g_window, &m_WindowWidth, &m_WindowHeight);

}

void D2D::CameraComponent::SetPlayer(Transform* playerTransform, Transform* player2Transform)
{
	m_pPlayerTransforms.clear();
	m_pPlayerTransforms.push_back(playerTransform);
	if (player2Transform != nullptr)
	{
		m_pPlayerTransforms.push_back(player2Transform);;
	}
}

void D2D::CameraComponent::SetLevelBounds(float min, float max)
{
	m_CameraMax = min;
	m_CameraMax = -max + m_WindowWidth;
}

void D2D::CameraComponent::LateUpdate()
{
	if (m_pPlayerTransforms.size() <= 0)
		return;

	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
	}

	if (m_pTransform != nullptr)
	{
		glm::vec2 playerPos{};

		for (auto& player : m_pPlayerTransforms)
		{
			playerPos += player->GetLocalPosition();
		}
		playerPos /= m_pPlayerTransforms.size();


		float cameraX = m_WindowWidth / 2 - playerPos.x;

		cameraX = std::min(cameraX, m_CameraMin);
		cameraX = std::max(cameraX, m_CameraMax);


		m_pTransform->SetWorldPosition(cameraX, m_pTransform->GetWorldPosition().y);
	}

}
