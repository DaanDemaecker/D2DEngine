#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "Powerup.h"

namespace D2D
{
	class GameData final : public Singleton<GameData>
	{
	public:
		GameData() = default;
		virtual ~GameData() = default;

		void SetLives(int lives) { m_LivesAmount = lives; }
		int GetLivesAmount() const { return m_LivesAmount; }

		void SetScore(int score) { m_Score = score; }
		int GetScore() const { return m_Score; }

		void AddPowerup(PowerupType type);
		void ResetPowerups();
		std::vector<PowerupType>& GetPowerups();

		void SetName(const std::string& name) { m_Name = name; }
		const std::string& GetName() const { return m_Name; }

		void SetCurrentLevel(int level) { m_CurrentLevel = level; }
		int GetCurrentLevel() const { return m_CurrentLevel; }
		int GetMaxLevel() const { return m_MaxLevel; }
		

	private:
		int m_LivesAmount{};

		int m_Score{};
		std::string m_Name{};

		int m_CurrentLevel{ 1 };
		const int m_MaxLevel{ 3 };

		std::vector<PowerupType> m_Powerups{};
	};
}