#pragma once

namespace dae
{
	struct Event;
	class GameObject;

	class Observer
	{
	public:
		virtual void Notify(const Event& event) = 0;
	};
}