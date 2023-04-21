#include "pch.h"
#include "DebugCommand.h"

void dae::DebugCommand::Execute()
{
	m_pDebugFunction();
}
