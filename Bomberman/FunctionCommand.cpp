#include "pch.h"
#include "FunctionCommand.h"

//D2D::FunctionCommand::~FunctionCommand()
//{
//	std::cout << "fok\n";
//}

void D2D::FunctionCommand::Execute()
{
	m_Function();
}
