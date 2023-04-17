#pragma once
#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class PlayerComponent final : public Component
	{
	public:
		PlayerComponent() = default;
		virtual ~PlayerComponent() override = default;


		void CreateBomb();

	private:

	};
}

