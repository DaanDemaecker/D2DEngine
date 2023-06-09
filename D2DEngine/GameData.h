#pragma once
#include "Singleton.h"
#include "GameObject.h"

namespace D2D
{
	class GameData final : public Singleton<GameData>
	{
	public:

		void SetLives(int lives) { m_LivesAmount = lives; }
		int GetLivesAmount() const { return m_LivesAmount; }

	private:
		int m_LivesAmount{};
	};
}