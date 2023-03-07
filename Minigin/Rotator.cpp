#include "Rotator.h"
#include "Time.h"
#include "Transform.h"

void dae::Rotator::Update()
{
	auto pTransfom{m_pOwner.lock()->GetTransform()};

	if (!pTransfom)
		return;

	m_CurrentAngle += m_RotSpeed * Time::GetInstance().GetDeltaTime();
	
	if (m_CurrentAngle > glm::radians(360.f))
		m_CurrentAngle -= glm::radians(360.f);

	const float x{cosf(m_CurrentAngle)*m_Distance};
	const float y{ sinf(m_CurrentAngle) * m_Distance };

	pTransfom->SetLocalPosition(x, y);
}
