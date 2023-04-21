#include "Rotator.h"
#include "TimeManager.h"
#include "Transform.h"

void dae::Rotator::Update()
{
	auto pTransfom{GetOwner()->GetTransform()};

	if (!pTransfom)
		return;

	m_CurrentAngle += m_RotSpeed * TimeManager::GetInstance().GetDeltaTime();
	
	while (m_CurrentAngle > glm::radians(360.f))
	{
		m_CurrentAngle -= glm::radians(360.f);
	}

	while (m_CurrentAngle < glm::radians(360.f))
	{
		m_CurrentAngle += glm::radians(360.f);
	}

	const float x{cosf(m_CurrentAngle)*m_Distance};
	const float y{sinf(m_CurrentAngle)*m_Distance};

	pTransfom->SetLocalPosition(x, y);
}
