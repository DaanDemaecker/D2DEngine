#pragma once
#include <vector>

namespace dae
{
	struct Event;
	class Observer;

	class Subject
	{
	public:
		Subject() = default;
		virtual ~Subject() = default;

		void NotifyObservers(const Event& event);

		void AddObserver(Observer* observer);
		void RemoveObserver(const Observer* observer);

	private:
		std::vector<Observer*> m_pObservers{};
	};
}

