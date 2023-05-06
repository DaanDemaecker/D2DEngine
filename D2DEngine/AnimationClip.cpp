#include "AnimationClip.h"
#include "TimeManager.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Event.h"

D2D::AnimationClip::AnimationClip(RenderComponent* pRenderComponent)
{
	m_pRenderComponent = pRenderComponent;
}

void D2D::AnimationClip::SetClip(std::shared_ptr<Texture2D> pTexture, int cols, int rows, int frames)
{
	if (pTexture != nullptr)
	{
		m_pTexture = pTexture;

		auto size = pTexture->GetSize();

		m_SrcRect.w = static_cast<float>(size.x) / cols;
		m_SrcRect.h = static_cast<float>(size.y) / rows;
	}
	m_Cols = cols;
	m_Rows = rows;
	m_FrameAmount = frames;
}

void D2D::AnimationClip::AddAnimationEvent(int frame, std::unique_ptr<Event> event)
{
	//The given event will be notified after the given frame
	m_AnimationEvents.insert(std::make_pair(frame, std::move(event)));
}

void D2D::AnimationClip::SetCurrentSprite()
{
	if (m_pRenderComponent != nullptr)
	{
		m_pRenderComponent->SetTexture(m_pTexture);
		SetFrame();
	}
}

void D2D::AnimationClip::Update()
{
	m_FrameTimer += TimeManager::GetInstance().GetDeltaTime();

	if (m_FrameTimer >= m_FrameDuration)
	{
		m_FrameTimer -= m_FrameDuration;

		for (const auto& event : m_AnimationEvents)
		{
			if (event.first == m_CurrentFrame)
				NotifyObservers(*(event.second.get()));
		}

		++m_CurrentFrame %= m_FrameAmount;

		SetFrame();
	}
}

void D2D::AnimationClip::SetFrame()
{
	if (m_pRenderComponent != nullptr)
	{
		m_SrcRect.x = (m_CurrentFrame % m_Cols) * m_SrcRect.w;
		m_SrcRect.y = static_cast<int>(m_CurrentFrame/m_Cols) * m_SrcRect.y;

		m_pRenderComponent->SetSourceRect(m_SrcRect);
	}
}
