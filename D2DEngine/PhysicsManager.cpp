#include "PhysicsManager.h"
#include "BoxCollider.h"

#include "Renderer.h"

void D2D::PhysicsManager::AddBoxCollider(BoxCollider* pCollider)
{
	if ((pCollider != nullptr) && (std::find(m_pBoxColliders.begin(), m_pBoxColliders.end(), pCollider) == m_pBoxColliders.end()))
	{
		m_pBoxColliders.push_back(pCollider);
	}
}

void D2D::PhysicsManager::RemoveCollider(BoxCollider* pCollider)
{
	m_pBoxColliders.erase(std::remove(m_pBoxColliders.begin(), m_pBoxColliders.end(), pCollider), m_pBoxColliders.end());
}

bool D2D::PhysicsManager::CanMove(BoxCollider* pCollider, const glm::vec2 direction)
{
    const auto rect{ Rect{pCollider->GetBounds()} };
    const auto halfWidth{ rect.w / 2.f };
    const auto halfHeight{ rect.h / 2.f };
    const auto middle{ glm::vec2{rect.x + halfWidth, rect.y + halfHeight} };

    constexpr float epsilon{ 0.001f };

	for (const auto& box : m_pBoxColliders)
	{
		if (box == pCollider)continue;
		
        auto otherRect = D2D::Rect{ box->GetBounds() };

		if (otherRect.IsPointInBounds(middle))continue;

        if (abs(direction.x) > epsilon)
        {
            float sign{ std::copysign(1.f, direction.x)};

            glm::vec2 startPos{middle.x + ((halfWidth - epsilon) * sign), middle.y};

            if (Raycast(otherRect, startPos, startPos + glm::vec2{ direction.x, 0 }))
                return false;

            if (Raycast(otherRect, startPos + +glm::vec2{ 0, halfHeight - epsilon }, startPos + glm::vec2{ direction.x, 0 }))
                return false;

            if (Raycast(otherRect, startPos + glm::vec2{ 0, -halfHeight + epsilon }, startPos + glm::vec2{ direction.x, 0 }))
                return false;
        }

        if (abs(direction.y) > epsilon)
        {
            float sign{ std::copysign(1.f, direction.y) };

            glm::vec2 startPos{ middle.x, middle.y + ((halfHeight - epsilon) * sign) };

            if (Raycast(otherRect, startPos, startPos + glm::vec2{ 0, direction.y}))
                return false;

            if (Raycast(otherRect, startPos + +glm::vec2{ halfWidth - epsilon, 0 }, startPos + glm::vec2{ 0, direction.y }))
                return false;

            if (Raycast(otherRect, startPos + glm::vec2{ -halfWidth + epsilon, 0 }, startPos + glm::vec2{ 0, direction.y }))
                return false;
        }
	}

	return true;
}

bool D2D::PhysicsManager::Raycast(const Rect& rect, const glm::vec2 startPos, const glm::vec2 endPos)
{
    float left = rect.x;
    float right = rect.x + rect.w;
    float top = rect.y;
    float bottom = rect.y + rect.h;

    float x1 = startPos.x;
    float y1 = startPos.y;
    float x2 = endPos.x;
    float y2 = endPos.y;

    // Check if the line is outside the bounding box of the rectangle
    if (x1 < left && x2 < left) return false;
    if (x1 > right && x2 > right) return false;
    if (y1 < top && y2 < top) return false;
    if (y1 > bottom && y2 > bottom) return false;

    // Check if the line intersects with any of the rectangle's edges
    float m = (y2 - y1) / (x2 - x1); // Slope of the line

    // Check left edge
    float y = m * (left - x1) + y1;
    if (y >= top && y <= bottom) return true;

    // Check right edge
    y = m * (right - x1) + y1;
    if (y >= top && y <= bottom) return true;

    // Check top edge
    float x = (top - y1) / m + x1;
    if (x >= left && x <= right) return true;

    // Check bottom edge
    x = (bottom - y1) / m + x1;
    if (x >= left && x <= right) return true;

    return false;
}
