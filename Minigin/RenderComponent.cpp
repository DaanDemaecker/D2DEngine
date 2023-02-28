#include "RenderComponent.h"
#include "Renderer.h"
#include "Transform.h"

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void dae::RenderComponent::Render() const
{
	const auto tranform = GetComponent<Transform>();

	if (!tranform || !m_pTexture)
		return;

	glm::vec2 pos{ tranform->GetPosition() };

	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
