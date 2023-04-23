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

    const auto movedRect{ Rect{rect.x + direction.x, rect.y + direction.y, rect.w, rect.h} };

	for (const auto& box : m_pBoxColliders)
	{
		if (box == pCollider)continue;
		
        auto otherRect = D2D::Rect{ box->GetBounds() };

        if(RectOverlap(rect, otherRect))
            continue;

        if (RectOverlap(movedRect, otherRect))
            return false;
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

bool D2D::PhysicsManager::RectOverlap(const Rect& r1, const Rect& r2)
{
    if (r1.x + r1.w < r2.x || r1.x > r2.x + r2.w) return false; // check x-axis overlap
    if (r1.y + r1.h < r2.y || r1.y > r2.y + r2.h) return false; // check y-axis overlap
    return true;
}
