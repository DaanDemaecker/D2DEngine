#pragma once
#include <memory>

namespace D2D
{
	class State
	{
	public:
		State() = default;
		virtual ~State() = default;

		State(State& other) = delete;
		State(State&& other) = delete;

		State& operator=(State& other) = delete;
		State& operator=(State&& other) = delete;

		virtual void Update() = 0;

		virtual void OnStateEnter() = 0;
		virtual void OnStateLeave() = 0;
	};
}