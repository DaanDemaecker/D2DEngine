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

void D2D::CameraComponent::SetPlayer(Transform* playerTransform)
{
	m_pPlayerTransform = playerTransform;
}

void D2D::CameraComponent::SetLevelBounds(float min, float max)
{
	m_CameraMax = min;
	m_CameraMax = -max + m_WindowWidth;
}

void D2D::CameraComponent::LateUpdate()
{
	if (m_pPlayerTransform == nullptr)
		return;

	if (m_pTransform == nullptr)
	{
		m_pTransform = GetOwner()->GetTransform().get();
	}

	if (m_pTransform != nullptr)
	{
		const auto playerPos = m_pPlayerTransform->GetLocalPosition();

		float cameraX = m_WindowWidth / 2 - playerPos.x;

		cameraX = std::min(cameraX, m_CameraMin);
		cameraX = std::max(cameraX, m_CameraMax);


		m_pTransform->SetWorldPosition(cameraX, m_pTransform->GetWorldPosition().y);
	}

}
