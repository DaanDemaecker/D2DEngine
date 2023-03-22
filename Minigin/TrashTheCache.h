#pragma once
#include "imgui.h"
#include "imgui_plot.h"
#include <vector>


namespace dae
{
	class TrashTheCache final
	{


	public:
        TrashTheCache() = default;
        ~TrashTheCache() = default;
        TrashTheCache(const TrashTheCache& other) = delete;
        TrashTheCache(TrashTheCache&& other) = delete;
        TrashTheCache& operator=(const TrashTheCache& other) = delete;
        TrashTheCache& operator=(TrashTheCache&& other) = delete;



		void Render();

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

