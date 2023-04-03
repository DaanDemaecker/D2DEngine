#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; }
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& pos);

		glm::vec2 GetWorldPosition();
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(const glm::vec2& pos);

		void MoveLocalPosition(float x, float y);
		void MoveLocalPosition(const glm::vec2& pos);

		void SetDirtyFlag();

	private:
		glm::vec2 m_LocalPosition{};
		glm::vec2 m_ParentWorldPosition{};

		bool m_HasChanged{ true };
	};
}
