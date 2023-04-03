#pragma once
#include <glm/glm.hpp>
#include "Command.h"

namespace dae
{
	class GameObject;

	class InfoCommand final : public Command
	{
	public:
		InfoCommand() = default;
		virtual ~InfoCommand() = default;
		InfoCommand(const InfoCommand& other) = delete;
		InfoCommand(InfoCommand&& other) = delete;
		InfoCommand& operator=(const InfoCommand& other) = delete;
		InfoCommand& operator=(InfoCommand&& other) = delete;

		virtual void Execute(const GameObject* Object) override;
	};
}