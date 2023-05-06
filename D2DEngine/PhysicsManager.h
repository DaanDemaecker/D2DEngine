#pragma once
#include "Singleton.h"
#include <glm/glm.hpp>
#include <vector>

namespace D2D
{
	class BoxCollider;
	class CapsuleCollider;
	struct Rect;

	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		PhysicsManager();
		~PhysicsManager();

		void AddCollider(BoxCollider* pCollider);
		void AddCollider(CapsuleCollider* pCollider);
		void RemoveCollider(BoxCollider* pCollider);
		void RemoveCollider(CapsuleCollider* pCollider);

		bool CanMove(BoxCollider* pCollider, glm::vec2& direction, bool secondCheck = false);
		bool CanMove(CapsuleCollider* pCollider, glm::vec2& direction, bool secondCheck = false);

		bool Raycast(const Rect& rect, const glm::vec2 startPos, const glm::vec2 endPos);

		bool IsOverlapping(const Rect& r1, const Rect& r2);
		bool IsPointInCircle(const glm::vec2& point, const glm::vec2& center, float radius);

	private:
		std::vector<BoxCollider*> m_pBoxColliders{};
		std::vector<CapsuleCollider*> m_pCapsuleColliders{};

		void GetPenetrationDepth(const glm::vec2& point, const glm::vec2& center, float radius, glm::vec2& depth);
	};
}