#include "PhysicsManager.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "Renderer.h"
#include "Transform.h"

#include <cmath>
#include <algorithm>

#include <iostream>

void D2D::PhysicsManager::AddIgnoreLayers(const std::string& tag1, const std::string& tag2)
{
    m_IgnoreLayers[tag1].push_back(tag2);
}

void D2D::PhysicsManager::AddCollider(BoxCollider* pCollider)
{
	if ((pCollider != nullptr) && (std::find(m_pBoxColliders.begin(), m_pBoxColliders.end(), pCollider) == m_pBoxColliders.end()))
	{
		m_pBoxColliders.push_back(pCollider);
        CheckColliderForTrigger(pCollider);
	}
}

void D2D::PhysicsManager::AddCollider(CapsuleCollider* pCollider)
{
    if ((pCollider != nullptr) && (std::find(m_pCapsuleColliders.begin(), m_pCapsuleColliders.end(), pCollider) == m_pCapsuleColliders.end()))
    {
        m_pCapsuleColliders.push_back(pCollider);
        CheckColliderForTrigger(pCollider);
    }
}

void D2D::PhysicsManager::RemoveCollider(BoxCollider* pCollider)
{
    for (auto& trigger : m_pBoxTriggers)
    {
        trigger->RemoveCollider(pCollider);
    }

    if (m_pBoxColliders.size() == 0)
        return;

	m_pBoxColliders.erase(std::remove(m_pBoxColliders.begin(), m_pBoxColliders.end(), pCollider), m_pBoxColliders.end());
}

void D2D::PhysicsManager::RemoveCollider(CapsuleCollider* pCollider)
{
    for (auto& trigger : m_pBoxTriggers)
    {
        trigger->RemoveCollider(pCollider);
    }

    if (m_pCapsuleColliders.size() == 0)
        return;

    m_pCapsuleColliders.erase(std::remove(m_pCapsuleColliders.begin(), m_pCapsuleColliders.end(), pCollider), m_pCapsuleColliders.end());
}

void D2D::PhysicsManager::AddTrigger(BoxCollider* pTrigger)
{
    if ((pTrigger != nullptr) && (std::find(m_pBoxTriggers.begin(), m_pBoxTriggers.end(), pTrigger) == m_pBoxTriggers.end()))
    {
        m_pBoxTriggers.push_back(pTrigger);
        CheckTrigger(pTrigger);
    }
}

void D2D::PhysicsManager::RemoveTrigger(BoxCollider* pTrigger)
{
    if (m_pBoxTriggers.size() == 0)
        return;

    m_pBoxTriggers.erase(std::remove(m_pBoxTriggers.begin(), m_pBoxTriggers.end(), pTrigger), m_pBoxTriggers.end());
}

bool D2D::PhysicsManager::CanMove(BoxCollider* pCollider, glm::vec2& direction, bool /*secondCheck*/)
{
    const auto rect{ Rect{pCollider->GetBounds()} };

    const auto movedRect{ Rect{rect.x + direction.x, rect.y + direction.y, rect.w, rect.h} };

    auto tag{ pCollider->GetOwner()->GetTag() };

	for (const auto& otherCollider : m_pBoxColliders)
	{
		if (otherCollider == pCollider || !otherCollider->IsActive() ||
            ShouldIgnoreLayers(tag, otherCollider->GetOwner()->GetTag()))continue;
		
        auto otherRect = D2D::Rect{ otherCollider->GetBounds() };

        if(IsOverlapping(rect, otherRect))
            continue;

        if (IsOverlapping(movedRect, otherRect))
            return false;
	}

    for (const auto& otherCollider : m_pCapsuleColliders)
    {
        if (!otherCollider->IsActive() ||
            ShouldIgnoreLayers(tag, otherCollider->GetOwner()->GetTag()))
            continue;

        auto otherCapsule = otherCollider->GetBounds();
        
        if (IsOverlapping(otherCapsule, rect))
            continue;

        if (IsOverlapping(otherCapsule, movedRect))
            return false;
    }

    return true;
}

bool D2D::PhysicsManager::CanMove(CapsuleCollider* pCollider, glm::vec2& direction, bool secondCheck)
{
    //constexpr float epsilon{ 0.001f };

    //Capsule shape of collider
    auto capsule = pCollider->GetBounds();

    //Where capsule collider would be if moved
    auto movedCapsule = capsule;
    movedCapsule.center = movedCapsule.center + direction;

    //Get rect and circle centers of capsule
    const auto capsuleRect{ capsule.GetRect()};
    const auto C1{ capsule.GetTopCenter() };
    const auto C2{ capsule.GetBotCenter() };

    //Get rect and circle centers of moved capsule
    const auto movedCapsuleRect{ movedCapsule.GetRect()};
    const auto movedC1{ movedCapsule.GetTopCenter() };
    const auto movedC2{ movedCapsule.GetBotCenter() };


    std::string tag{ pCollider->GetOwner()->GetTag() };

    for (const auto& otherCollider : m_pBoxColliders)
    {
        if (!otherCollider->IsActive() ||
            ShouldIgnoreLayers(tag, otherCollider->GetOwner()->GetTag()))
            continue;

        auto otherRect = D2D::Rect{ otherCollider->GetBounds() };

        //---Initial overlap---
        //Get all points of the rect
        const glm::vec2 tl{ otherRect.x, otherRect.y }; //Top Left corner
        const glm::vec2 tr{ otherRect.x + otherRect.w, otherRect.y }; //Top Right corner
        const glm::vec2 bl{ otherRect.x, otherRect.y + otherRect.h }; //Bottom Left Corner
        const glm::vec2 br{ otherRect.x + otherRect.w, otherRect.y + otherRect.h }; //Bottom right corner

        //If objects are already overlapping, continue
        if (IsOverlapping(capsuleRect, otherRect) ||
            IsPointInCircle(tl, C1, capsule.radius) ||
            IsPointInCircle(tr, C1, capsule.radius) ||
            IsPointInCircle(bl, C2, capsule.radius) ||
            IsPointInCircle(br, C2, capsule.radius) ||
            otherRect.IsPointInBox({C1.x, C1.y - capsule.radius}) ||
            otherRect.IsPointInBox({C2.x, C2.y + capsule.radius}))
            continue;


        //---Rect overlap
        if (IsOverlapping(movedCapsuleRect, otherRect))
            return false;

        //---Circles overlap---
        glm::vec2 penetrationDepth{};
        //--Top circle overlap--
        //-Bottom left corner--
        if (IsPointInCircle(bl, movedC1, capsule.radius))
        {
            if (secondCheck)
            {
                return false;
            }
            else
            {
                GetPenetrationDepth(bl, movedC1, capsule.radius, penetrationDepth);

                // Calculate the new direction based on the penetration depth
                if (abs(direction.x) > abs(direction.y))
                {
                    direction.x += penetrationDepth.x;
                    direction.y += penetrationDepth.y;
                    direction.x = 0;
                }
                else if (abs(direction.y) > abs(direction.x))
                {
                    direction.x += penetrationDepth.x;
                    direction.y += penetrationDepth.y;
                    direction.y = 0;
                }

                bool test = CanMove(pCollider, direction, true);

                return test;
            }
        }
        
        //-Bottom right corner--
        if (IsPointInCircle(br, movedC1, capsule.radius))
        {
            if (secondCheck)
            {
                return false;
            }
            else
            {
                GetPenetrationDepth(br, movedC1, capsule.radius, penetrationDepth);

                // Calculate the new direction based on the penetration depth
                if (abs(direction.x) > abs(direction.y))
                {
                    direction.x += penetrationDepth.x;
                    direction.x = 0;
                    direction.y += penetrationDepth.y;
                }
                else if (abs(direction.y) > abs(direction.x))
                {
                    direction.x += penetrationDepth.x;
                    direction.y += penetrationDepth.y;
                    direction.y = 0;
                }

                return CanMove(pCollider, direction, true);
            }
        }


        //--Bottom circle overlap--
        //-Top left corner--
        if (IsPointInCircle(tl, movedC2, capsule.radius))
        {
            if (secondCheck)
            {
                return false;
            }
            else
            {
                GetPenetrationDepth(tl, movedC2, capsule.radius, penetrationDepth);

                // Calculate the new direction based on the penetration depth
                if (abs(direction.x) > abs(direction.y))
                {
                    direction.x += penetrationDepth.x;
                    direction.y += penetrationDepth.y;
                    direction.x = 0;
                }
                else if (abs(direction.y) > abs(direction.x))
                {
                    direction.x += penetrationDepth.x;
                    direction.y += penetrationDepth.y;
                    direction.y = 0;
                }

                return CanMove(pCollider, direction, true);
            }
        }

        //-Top right corner--
        if (IsPointInCircle(tr, movedC2, capsule.radius))
        {
            if (secondCheck)
            {
                return false;
            }
            else
            {
                GetPenetrationDepth(tr, movedC2, capsule.radius, penetrationDepth);

                // Calculate the new direction based on the penetration depth
                if (abs(direction.x) > abs(direction.y))
                {
                    direction.x += penetrationDepth.x;
                    direction.y += penetrationDepth.y;
                    direction.x = 0;
                }
                else if (abs(direction.y) > abs(direction.x))
                {
                    direction.x += penetrationDepth.x;
                    direction.y += penetrationDepth.y;
                    direction.y = 0;
                }

                return CanMove(pCollider, direction, true);
            }
        }

        //--Top and bottom point of capsule--
        if (otherRect.IsPointInBox({ movedC1.x, movedC1.y - capsule.radius }))
        {
            return false;
        }
        if (otherRect.IsPointInBox({ movedC2.x, movedC2.y + capsule.radius }))
        {
            return false;
        }

    }

    for (const auto& otherCollider : m_pCapsuleColliders)
    {
        if (otherCollider == pCollider || !otherCollider->IsActive() ||
            ShouldIgnoreLayers(tag, otherCollider->GetOwner()->GetTag()))continue;

        auto otherCapsule = otherCollider->GetBounds();
        auto otherRect = D2D::Rect{ otherCapsule.GetRect() };
        auto otherC1 = otherCapsule.GetTopCenter();
        auto otherC2 = otherCapsule.GetBotCenter();

        if (IsOverlapping(capsuleRect, otherRect) ||
            IsOverlapping(C1, capsule.radius, otherC2, otherCapsule.radius) ||
            IsOverlapping(C2, capsule.radius, otherC1, otherCapsule.radius))
            continue;

        if (IsOverlapping(movedCapsuleRect, otherRect) ||
            IsOverlapping(movedC1, capsule.radius, otherC2, otherCapsule.radius) ||
            IsOverlapping(movedC2, capsule.radius, otherC1, otherCapsule.radius))
            return false;
    }


    return true;
}

void D2D::PhysicsManager::GetPenetrationDepth(const glm::vec2& point, const glm::vec2& center, float radius, glm::vec2& depth)
{
    // Calculate the vector from the point to the center of the circle
    glm::vec2 diff = center - point;

    // Calculate the distance between the point and the center of the circle
    float distance = glm::length(diff);

    // Calculate the penetration depth
    float penetrationDepth = radius - distance;

    // Calculate the penetration direction
    glm::vec2 penetrationDirection = glm::normalize(diff);

    // Scale depth to decrease chances of getting stuck
    constexpr float scale = 5.f;

    // Calculate the penetration vector
    depth = penetrationDepth * scale * penetrationDirection;
}

void D2D::PhysicsManager::RaycastDirectional(const glm::vec2& p1, const glm::vec2& direction, float t, const Collider* toIgnore, std::vector<Collider*>& hits)
{
    for (auto& pBoxCollider : m_pBoxColliders)
    {
        if (pBoxCollider == toIgnore)
            continue;

        auto rect{ pBoxCollider->GetBounds() };
        if (RaycastDirectional(p1, direction, t, rect))
            hits.push_back(pBoxCollider);
    }

    for (auto& pCapsuleColliders : m_pCapsuleColliders)
    {
        if (pCapsuleColliders == toIgnore)
            continue;

        auto capsule{ pCapsuleColliders->GetBounds() };
        if (RaycastDirectional(p1, direction, t, capsule))
            hits.push_back(pCapsuleColliders);
    }
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

bool D2D::PhysicsManager::IsOverlapping(const Rect& r1, const Rect& r2)
{
    if (r1.x + r1.w < r2.x || r1.x > r2.x + r2.w) return false; // check x-axis overlap
    if (r1.y + r1.h < r2.y || r1.y > r2.y + r2.h) return false; // check y-axis overlap
    return true;
}

bool D2D::PhysicsManager::IsPointInCircle(const glm::vec2& point, const glm::vec2& center, float radius)
{
    glm::vec2 diff = center - point;
    const float distanceSqrd = (diff.x * diff.x) + (diff.y * diff.y);

    return distanceSqrd <= radius * radius;
}

bool D2D::PhysicsManager::IsOverlapping(Capsule& capsule, const Rect& rect)
{
    if (IsOverlapping(capsule.GetRect(), rect) ||
        IsRectangleCircleOverlap(rect, capsule.GetTopCenter(), capsule.radius) ||
        IsRectangleCircleOverlap(rect, capsule.GetBotCenter(), capsule.radius))
    {
        return true;
    }


    return false;
}

bool D2D::PhysicsManager::IsRectangleCircleOverlap(const Rect& rect, const glm::vec2& circleCenter, float circleRadius)
{
    // Find the closest point on the rectangle to the center of the circle
    float closestX = std::clamp(circleCenter.x, rect.x, rect.x + rect.w);
    float closestY = std::clamp(circleCenter.y, rect.y, rect.y + rect.h);

    // Calculate the distance between the closest point and the center of the circle
    float distanceX = circleCenter.x - closestX;
    float distanceY = circleCenter.y - closestY;
    float distanceSqrd = distanceX * distanceX + distanceY * distanceY;

    // Check if the distance is less than or equal to the circle's radius
    return distanceSqrd <= (circleRadius * circleRadius);
}

bool D2D::PhysicsManager::IsOverlapping(const glm::vec2& c1, float r1, const glm::vec2& c2, float r2)
{
    float sqrdDistance = (c2.x - c1.x) * (c2.x - c1.x) + (c2.y - c1.y) * (c2.y - c1.y);


    return sqrdDistance <= (r1 + r2) * (r1 + r2);
}

void D2D::PhysicsManager::CheckTrigger(BoxCollider* pTrigger)
{
    auto bounds{ pTrigger->GetBounds() };
    for (const auto& boxCollider : m_pBoxColliders)
    {
        if (!boxCollider->IsActive())
            continue;

        bool isOverlapping = IsOverlapping(bounds, boxCollider->GetBounds());

        if (pTrigger->TriggerContainsCollider(boxCollider))
        {
            if (!isOverlapping)
            {
                pTrigger->RemoveCollider(boxCollider);
                boxCollider->GetOwner()->OnTriggerExit(pTrigger);
                pTrigger->GetOwner()->OnTriggerExit(boxCollider);
            }
        }
        else
        {
            if (isOverlapping)
            {
                pTrigger->AddCollider(boxCollider);
                boxCollider->GetOwner()->OnTriggerEnter(pTrigger);
                pTrigger->GetOwner()->OnTriggerEnter(boxCollider);
            }
        }
    }

    for (const auto& boxTrigger : m_pBoxTriggers)
    {
        if (!boxTrigger->IsActive())
            continue;

        bool isOverlapping = IsOverlapping(bounds, boxTrigger->GetBounds());

        if (pTrigger->TriggerContainsCollider(boxTrigger))
        {
            if (!isOverlapping)
            {
                pTrigger->RemoveCollider(boxTrigger);
                boxTrigger->GetOwner()->OnTriggerExit(pTrigger);
                pTrigger->GetOwner()->OnTriggerExit(boxTrigger);
            }
        }
        else
        {
            if (isOverlapping)
            {
                pTrigger->AddCollider(boxTrigger);
                boxTrigger->GetOwner()->OnTriggerEnter(pTrigger);
                pTrigger->GetOwner()->OnTriggerEnter(boxTrigger);
            }
        }
    }

    for (const auto& capsuleCollider : m_pCapsuleColliders)
    {
        if (!capsuleCollider->IsActive())
            continue;

        bool isOverlapping = IsOverlapping(capsuleCollider->GetBounds(), bounds);

        if (pTrigger->TriggerContainsCollider(capsuleCollider))
        {
            if (!isOverlapping)
            {
                pTrigger->RemoveCollider(capsuleCollider);
                capsuleCollider->GetOwner()->OnTriggerExit(pTrigger);
                pTrigger->GetOwner()->OnTriggerExit(capsuleCollider);
            }
        }
        else
        {
            if (isOverlapping)
            {
                pTrigger->AddCollider(capsuleCollider);
                capsuleCollider->GetOwner()->OnTriggerEnter(pTrigger);
                pTrigger->GetOwner()->OnTriggerEnter(capsuleCollider);
            }
        }
    }
}

void D2D::PhysicsManager::CheckColliderForTrigger(BoxCollider* pCollider)
{
    const auto rect{ pCollider->GetBounds() };

    for (const auto& trigger : m_pBoxTriggers)
    {
        if (!trigger->IsActive())
            continue;

        bool isOverlapping = IsOverlapping(trigger->GetBounds(), rect);

        if (trigger->TriggerContainsCollider(pCollider))
        {
            if (!isOverlapping)
            {
                trigger->RemoveCollider(pCollider);
                pCollider->GetOwner()->OnTriggerExit(trigger);
                trigger->GetOwner()->OnTriggerExit(pCollider);
            }
        }
        else
        {
            if (isOverlapping)
            {
                trigger->AddCollider(pCollider);
                pCollider->GetOwner()->OnTriggerEnter(trigger);
                trigger->GetOwner()->OnTriggerEnter(pCollider);
            }
        }
    }
}

void D2D::PhysicsManager::CheckColliderForTrigger(CapsuleCollider* pCollider)
{
    auto capsule{ pCollider->GetBounds() };

    for (const auto& trigger : m_pBoxTriggers)
    {
        if (!trigger->IsActive())
            continue;

        bool isOverlapping = IsOverlapping(capsule, trigger->GetBounds());

        if (trigger->TriggerContainsCollider(pCollider))
        {
            if (!isOverlapping)
            {
                trigger->RemoveCollider(pCollider);
                pCollider->GetOwner()->OnTriggerExit(trigger);
                trigger->GetOwner()->OnTriggerExit(pCollider);
            }
        }
        else
        {
            if (isOverlapping)
            {
                trigger->AddCollider(pCollider);
                pCollider->GetOwner()->OnTriggerEnter(trigger);
                trigger->GetOwner()->OnTriggerEnter(pCollider);
            }
        }
    }
}

D2D::Collider* D2D::PhysicsManager::RaycastDirectional(const glm::vec2& p1, const glm::vec2& direction, float t, const D2D::Collider* toIgnore)
{
    std::vector<D2D::Collider*> hits{};

    RaycastDirectional(p1, direction, t, toIgnore, hits);

    float closestSquared{ FLT_MAX };
    int closestIndex{ -1 };


    for (int i{}; i < static_cast<int>(hits.size()); ++i)
    {
        auto p{ hits[i]->GetTransform()->GetWorldPosition() };
        float distanceSquared{ (p.x - p1.x) * (p.x - p1.x) + (p.y - p1.y) * (p.y - p1.y) };
        if (distanceSquared < closestSquared)
        {
            closestSquared = distanceSquared;
            closestIndex = i;
        }
    }


    if (closestIndex == -1)
        return nullptr;
    else
        return hits[closestIndex];
}

D2D::Collider* D2D::PhysicsManager::Raycast(const glm::vec2& p1, const glm::vec2& p2, const D2D::Collider* toIgnore)
{
    glm::vec2 direction{ p2 - p1 };

    float t{ static_cast<float>(direction.length()) };

    direction /= t;

    return RaycastDirectional(p1, direction, t, toIgnore);
}

bool D2D::PhysicsManager::RaycastDirectional(const glm::vec2& origin, const glm::vec2& direction, float t, const Rect& rectangle)
{
    float left = rectangle.x;
    float right = rectangle.x + rectangle.w;
    float top = rectangle.y;
    float bottom = rectangle.y + rectangle.h;

    float x1 = origin.x;
    float y1 = origin.y;
    float x2 = origin.x + direction.x * t;
    float y2 = origin.y + direction.y * t;

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

bool D2D::PhysicsManager::RaycastDirectional(const glm::vec2& origin, const glm::vec2& direction, float t, Capsule& capsule)
{
    if (RaycastDirectional(origin, direction, t, capsule.GetRect()) ||
        RaycastDirectional(origin, direction, t, capsule.GetTopCenter(), capsule.radius) ||
        RaycastDirectional(origin, direction, t, capsule.GetBotCenter(), capsule.radius))
    {
        return true;
    }

    return false;
}

bool D2D::PhysicsManager::RaycastDirectional(const glm::vec2& origin, const glm::vec2& direction, float t, const glm::vec2& c, float r)
{
    bool hit = false;

    glm::vec2 perpendicularDirection(-direction.y, direction.x);
    glm::vec2 oc = c - origin;
    float d = glm::dot(oc, perpendicularDirection);

    if (d > r) {
        return hit;
    }

    glm::vec2 intersection = origin + direction * t;
    glm::vec2 ic = c - intersection;
    float distanceToCenter = glm::length(ic);

    if (distanceToCenter > r) {
        return hit;
    }

    hit = true;

    return hit;
}

bool D2D::PhysicsManager::ShouldIgnoreLayers(const std::string& tag1, const std::string& tag2)
{
    auto& tags{ m_IgnoreLayers[tag1] };

    if (std::find(tags.begin(), tags.end(), tag2) == tags.end())
        return false;

    return true;
}
