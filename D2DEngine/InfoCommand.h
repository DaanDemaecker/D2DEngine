#pragma once
#include <glm/glm.hpp>
#include "Command.h"

namespace D2D
{
	class ImGuiInfoComponent;

	class InfoCommand final : public Command
	{
	public:
		InfoCommand(ImGuiInfoComponent* pInfoComponent) : m_pInfoComponent{pInfoComponent} {}
		virtual ~InfoCommand() = default;
		InfoCommand(const InfoCommand& other) = delete;
		InfoCommand(InfoCommand&& other) = delete;
		InfoCommand& operator=(const InfoCommand& other) = delete;
		InfoCommand& operator=(InfoCommand&& other) = delete;

		virtual void Execute() override;

	private:
		ImGuiInfoComponent* m_pInfoComponent;
	};
}