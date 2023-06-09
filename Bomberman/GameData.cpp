#include "pch.h"
#include "GameData.h"

void D2D::GameData::AddPowerup(PowerupType type)
{
	m_Powerups.push_back(type);
}

void D2D::GameData::ResetPowerups()
{
	m_Powerups.clear();
}

std::vector<D2D::PowerupType>& D2D::GameData::GetPowerups()
{
	return m_Powerups;
}
