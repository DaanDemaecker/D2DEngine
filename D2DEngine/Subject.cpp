#include "Subject.h"
#include "Observer.h"
#include <algorithm>

void D2D::Subject::NotifyObservers(const Event& event)
{
	for (const auto& observer : m_pObservers)
	{
		observer->Notify(event);
	}
}

void D2D::Subject::AddObserver(Observer* observer)
{
	if (std::find(m_pObservers.begin(), m_pObservers.end(), observer) == m_pObservers.end())
	{
		m_pObservers.push_back(observer);
	}
}

void D2D::Subject::RemoveObserver(const Observer* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}
