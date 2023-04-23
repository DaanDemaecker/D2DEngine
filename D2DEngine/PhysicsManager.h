#pragma once
#include "Singleton.h"
#include <glm/glm.hpp>
#include <vector>

namespace D2D
{
	class BoxCollider;
	struct Rect;

	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:

		void AddBoxCollider(BoxCollider* pCollider);
		void RemoveCollider(BoxCollider* pCollider);

		bool CanMove(BoxCollider* pCollider, const glm::vec2 direction);

		bool Raycast(const Rect& rect, const glm::vec2 startPos, const glm::vec2 endPos);

	private:
		std::vector<BoxCollider*> m_pBoxColliders{};
	};
}