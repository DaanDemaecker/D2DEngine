#include "Collider.h"

bool D2D::Collider::TriggerContainsCollider(const Collider* pCollider)
{
    return (std::find(m_pCollidersInTrigger.begin(), m_pCollidersInTrigger.end(), pCollider) != m_pCollidersInTrigger.end());
}

void D2D::Collider::AddCollider(Collider* pCollider)
{
    if (pCollider != nullptr && !TriggerContainsCollider(pCollider))
    {
        m_pCollidersInTrigger.push_back(pCollider);
    }
}

void D2D::Collider::RemoveCollider(const Collider* pCollider)
{
    if (m_pCollidersInTrigger.size() == 0)
        return;

    m_pCollidersInTrigger.erase(std::remove(m_pCollidersInTrigger.begin(), m_pCollidersInTrigger.end(), pCollider), m_pCollidersInTrigger.end());
}