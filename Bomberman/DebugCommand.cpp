#include "pch.h"
#include "DebugCommand.h"

void D2D::DebugCommand::Execute()
{
	m_pDebugFunction();
}
