#include "Subject.h"
#include "Observer.h"
#include <algorithm>

void dae::Subject::NotifyObservers(const Event& event)
{
	for (const auto& observer : m_pObservers)
	{
		observer->Notify(event);
	}
}

void dae::Subject::AddObserver(Observer* observer)
{
	if (std::find(m_pObservers.begin(), m_pObservers.end(), observer) == m_pObservers.end())
	{
		m_pObservers.push_back(observer);
	}
}

void dae::Subject::RemoveObserver(const Observer* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}
