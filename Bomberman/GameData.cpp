#include "pch.h"
#include "GameData.h"

void D2D::GameData::AddPowerup(PowerupType type, int idx)
{
	if (idx == 0)
	{
		m_Powerups0.push_back(type);
	}
	else
	{
		m_Powerups1.push_back(type);
	}

}

void D2D::GameData::ResetPowerups()
{
	m_Powerups0.clear();
	m_Powerups1.clear();
}

std::vector<D2D::PowerupType>& D2D::GameData::GetPowerups(int idx)
{
	if (idx == 0)
	{
		return m_Powerups0;
	}
	else
	{
		return m_Powerups1;
	}
}
