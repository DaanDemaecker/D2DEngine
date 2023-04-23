#include "RenderComponent.h"
#include "Renderer.h"
#include "Transform.h"

void D2D::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void D2D::RenderComponent::SetOffset(float offsetX, float offSetY)
{
	m_OffsetX = offsetX;
	m_Offsety = offSetY;
}

void D2D::RenderComponent::Render() const
{
	const auto tranform = GetComponent<Transform>();

	if (!tranform || !m_pTexture)
		return;

	glm::vec2 pos{ tranform->GetWorldPosition() };

	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x + m_OffsetX, pos.y + m_OffsetX);
	tranform->Render();
}
