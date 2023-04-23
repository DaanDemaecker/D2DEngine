#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace D2D
{
	class BoxCollider;

	class Transform final : public Component
	{
	public:
		void SetCollider(BoxCollider* pCollider);

		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; }
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& pos);

		glm::vec2 GetWorldPosition();
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(const glm::vec2& pos);

		void MoveLocalPosition(float x, float y);
		void MoveLocalPosition(const glm::vec2& dir);

		void SetDirtyFlag();

		virtual void Render() const override;

	private:
		glm::vec2 m_LocalPosition{};
		glm::vec2 m_ParentWorldPosition{};

		bool m_HasChanged{ true };

		BoxCollider* m_pCollider{ nullptr };
	};
}
