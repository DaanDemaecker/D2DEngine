#pragma once
#include <string>
#include <functional>

namespace D2D
{
	class D2DEngine
	{
	public:
		explicit D2DEngine(const std::string& dataPath);
		~D2DEngine();
		void Run(const std::function<void()>& load);

		D2DEngine(const D2DEngine& other) = delete;
		D2DEngine(D2DEngine&& other) = delete;
		D2DEngine& operator=(const D2DEngine& other) = delete;
		D2DEngine& operator=(D2DEngine&& other) = delete;
	};
}