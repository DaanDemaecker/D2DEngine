#pragma once
#include "Singleton.h"
#include <glm/glm.hpp>
#include <vector>

namespace D2D
{
	class BoxCollider;
	class CapsuleCollider;
	struct Rect;
	struct Capsule;

	class PhysicsManager final : public Singleton<PhysicsManager>
	{
	public:
		void AddCollider(BoxCollider* pCollider);
		void AddCollider(CapsuleCollider* pCollider);
		void RemoveCollider(BoxCollider* pCollider);
		void RemoveCollider(CapsuleCollider* pCollider);

		void AddTrigger(BoxCollider* pTrigger);
		void RemoveTrigger(BoxCollider* pTrigger);

		bool CanMove(BoxCollider* pCollider, glm::vec2& direction, bool secondCheck = false);
		bool CanMove(CapsuleCollider* pCollider, glm::vec2& direction, bool secondCheck = false);

		bool Raycast(const Rect& rect, const glm::vec2 startPos, const glm::vec2 endPos);

		bool IsOverlapping(const Rect& r1, const Rect& r2);
		bool IsPointInCircle(const glm::vec2& point, const glm::vec2& center, float radius);

		bool IsOverlapping(Capsule& capsule, const Rect& rect);
		bool IsRectangleCircleOverlap(const Rect& rect, const glm::vec2& circleCenter, float circleRadius);

		bool IsOverlapping(const glm::vec2& c1, float r1, const glm::vec2& c2, float r2);


		void CheckTrigger(BoxCollider* pTrigger);
		void CheckColliderForTrigger(BoxCollider* pCollider);
		void CheckColliderForTrigger(CapsuleCollider* pCollider);

	private:
		friend class Singleton<PhysicsManager>;
		PhysicsManager() = default;

		std::vector<BoxCollider*> m_pBoxColliders{};
		std::vector<CapsuleCollider*> m_pCapsuleColliders{};

		std::vector<BoxCollider*> m_pBoxTriggers{};

		void GetPenetrationDepth(const glm::vec2& point, const glm::vec2& center, float radius, glm::vec2& depth);
	};
}