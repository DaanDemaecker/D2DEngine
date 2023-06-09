#pragma once
#include "Singleton.h"
#include "GameObject.h"


namespace D2D
{

	class GameData final : public Singleton<GameData>
	{
	public:
		GameData() = default;
		virtual ~GameData() = default;

		void SetLives(int lives) { m_LivesAmount = lives; }
		int GetLivesAmount() const { return m_LivesAmount; }

		void AddPowerup(PowerupType type);
		void ResetPowerups();
		std::vector<PowerupType>

	private:
		int m_LivesAmount{};

		std::vector<PowerupType> m_Powerups{};
	};
}