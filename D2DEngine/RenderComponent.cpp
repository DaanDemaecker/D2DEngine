#include "RenderComponent.h"
#include "Renderer.h"
#include "Transform.h"

void D2D::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
	
	auto size = pTexture->GetSize();

	m_SrcRect = Rect{0, 0, static_cast<float>(size.x), static_cast<float>(size.y)};
}

void D2D::RenderComponent::SetSourceRect(const Rect& srcRect)
{
	m_SrcRect = srcRect;
}

void D2D::RenderComponent::SetOffset(float offsetX, float offSetY)
{
	m_OffsetX = offsetX;
	m_OffsetY = offSetY;
}

void D2D::RenderComponent::SetDestRectBounds(float width, float height)
{
	m_DestRectWidth = width;
	m_DestRectHeight = height;
}

void D2D::RenderComponent::Render() const
{
	const auto tranform = GetOwner()->GetTransform();

	if (!tranform || !m_pTexture)
		return;

	glm::vec2 pos{ tranform->GetWorldPosition() };

	if (m_DestRectWidth == 0 || m_DestRectHeight == 0)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x + m_OffsetX , pos.y + m_OffsetY, m_SrcRect);
	}
	else
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x + m_OffsetX, pos.y + m_OffsetY, m_DestRectWidth, m_DestRectHeight, m_SrcRect);
	}
}
