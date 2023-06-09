#pragma once
#include "Component.h"
#include "Observer.h"
#include "Subject.h"

namespace D2D
{
	class BaseEnemyComponent;

	class EnemyManager final : public Component, public Observer, public Subject
	{
	public:
		EnemyManager() = default;
		virtual ~EnemyManager() override = default;
		
		virtual void Notify(const Event& event);

		void AddSubject(Subject* subject);
		void RemoveSubjects();

	private:
		std::vector<BaseEnemyComponent*> m_pEnemies{};

		std::vector<Subject*> m_pSubjects;
	};
}