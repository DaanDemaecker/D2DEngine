#pragma once
#include "Component.h"
#include "imgui.h"
#include "imgui_plot.h"
#include <vector>

namespace D2D
{
	class TrashTheCacheComponent final : public Component
	{
	public:
		TrashTheCacheComponent() = default;
		virtual ~TrashTheCacheComponent() = default;

		TrashTheCacheComponent(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent(TrashTheCacheComponent&& other) = delete;
		TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other) = delete;

		virtual void OnGUI() override;
	private:
        struct Transform
        {
            float matrix[16] = {
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1
            };
        };

        struct GameObject3D
        {
        public:
            Transform transform{ Transform{} };
            int ID{ 1 };
        };

        struct GameObject3DAlt
        {
        public:
            ~GameObject3DAlt() { delete transform; };
            Transform* transform{ new Transform{} };
            int ID{ 1 };
        };

        void RenderPlot(const std::vector<float>& samples, size_t verticalLineIndex, const ImColor& color);
        void RenderDoublePlot();

        void RenderExercise1();
        void RenderExercise2();

        void Excercise1();
        void Excercise2();
        void Excercise2alt();

        int m_Ex1SampleAmount{ 10 };
        std::vector<float> m_Ex1Samples{};

        int m_Ex2SampleAmount{ 10 };
        std::vector<float> m_Ex2Samples{};
        std::vector<float> m_Ex2AltSamples{};
	};
}
