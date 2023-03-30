#include "TrashTheCacheComponent.h"
#include <chrono>
#include <algorithm>
#include <numeric>


void dae::TrashTheCacheComponent::OnGUI()
{
	RenderExercise1();

	RenderExercise2();
}

void dae::TrashTheCacheComponent::RenderPlot(const std::vector<float>& samples, size_t verticalLineIndex, const ImColor& color)
{
    ImGui::PlotConfig::Values plotValues{ nullptr, samples.data(), static_cast<int>(samples.size()), 0, color };

    const float maxElement{ *std::max_element(samples.begin(), samples.end()) };

    ImGui::PlotConfig plot{};
    plot.frame_size = ImVec2{ 200, 100 };
    plot.values = plotValues;
    plot.scale = ImGui::PlotConfig::Scale(0, maxElement);

    plot.v_lines = ImGui::PlotConfig::VerticalLines{ true, &verticalLineIndex, 1 };

    plot.grid_y = ImGui::PlotConfig::Grid{ true, maxElement / 10 };

    ImGui::Plot("plotter", plot);
}

void dae::TrashTheCacheComponent::RenderDoublePlot()
{
    const float* doubleValues[2]{ m_Ex2Samples.data(), m_Ex2AltSamples.data() };
    ImU32 colors[2]{ ImColor{ 1.0f, 0.0f, 0.0f }, ImColor{ 0.0f, 1.0f, 0.0f } };

    ImGui::PlotConfig::Values plotValues{ nullptr, nullptr, static_cast<int>(m_Ex2Samples.size()), 0, 0, doubleValues, 2, colors };

    const float maxElement{ *std::max_element(m_Ex2Samples.begin(), m_Ex2Samples.end()) };

    ImGui::PlotConfig plot{};
    plot.frame_size = ImVec2{ 200, 100 };
    plot.values = plotValues;
    plot.scale = ImGui::PlotConfig::Scale{ 0, maxElement };

    plot.grid_y = ImGui::PlotConfig::Grid{ true, maxElement / 10 };

    ImGui::Plot("doubleplotter", plot);
}

void dae::TrashTheCacheComponent::RenderExercise1()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 20, main_viewport->WorkPos.y + 20));
    ImGui::SetNextWindowSize(ImVec2(280, 450));

    // Main body of the Demo window starts here.
    if (!ImGui::Begin("Exercise 1"))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    ImGui::InputInt("samples", &m_Ex1SampleAmount);

    if (ImGui::Button("Trash the cache"))
    {
        Excercise1();
    }

    if (!m_Ex1Samples.empty())
    {
        RenderPlot(m_Ex1Samples, 4, ImColor{ 1.0f, 0.0f, 0.0f });
    }

    ImGui::End();
}

void dae::TrashTheCacheComponent::RenderExercise2()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 320, main_viewport->WorkPos.y + 20));
    ImGui::SetNextWindowSize(ImVec2(300, 450));

    // Main body of the Demo window starts here.
    if (!ImGui::Begin("Exercise 2"))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    ImGui::InputInt("samples", &m_Ex2SampleAmount);

    if (ImGui::Button("Trash the cache with GameObject3D"))
    {
        Excercise2();
    }

    if (!m_Ex2Samples.empty())
    {
        RenderPlot(m_Ex2Samples, 3, ImColor{ 1.0f, 0.0f, 0.0f });
    }

    if (ImGui::Button("Trash the cache with GameObject3DAlt"))
    {
        Excercise2alt();
    }

    if (!m_Ex2AltSamples.empty())
    {
        RenderPlot(m_Ex2AltSamples, 3, ImColor{ 0.0f, 1.0f, 0.0f });
    }

    if (!m_Ex2Samples.empty() && !m_Ex2AltSamples.empty())
    {
        RenderDoublePlot();
    }

    ImGui::End();
}

void dae::TrashTheCacheComponent::Excercise1()
{
    m_Ex1Samples.clear();

    const unsigned int length{ 100'000'000 };
    std::vector<int> pBuffer{};
    pBuffer.resize(length);

    for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        std::vector<float> stepTimer{};

        for (int sample{}; sample < m_Ex1SampleAmount; sample++)
        {

            auto start = std::chrono::high_resolution_clock::now();

            for (int i{ 0 }; i < length; i += stepsize)
            {
                pBuffer[i] *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();

            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            stepTimer.push_back(static_cast<float>(elapsedTime));
        }

        std::sort(stepTimer.begin(), stepTimer.end());

        const float average{ std::accumulate(stepTimer.begin() + 1, stepTimer.end() - 1, 0.0f) / (stepTimer.size() - 2) };

        m_Ex1Samples.push_back(average);
    }
}

void dae::TrashTheCacheComponent::Excercise2()
{
    m_Ex2Samples.clear();

    const unsigned int length{ 10'000'000 };
    std::vector<GameObject3D> pBuffer{};
    pBuffer.resize(length);

    for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        std::vector<float> stepTimer{};

        for (int sample{}; sample < m_Ex2SampleAmount; sample++)
        {

            auto start = std::chrono::high_resolution_clock::now();

            for (int i{ 0 }; i < length; i += stepsize)
            {
                pBuffer[i].ID *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();

            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            stepTimer.push_back(static_cast<float>(elapsedTime));
        }

        std::sort(stepTimer.begin(), stepTimer.end());

        const float average{ std::accumulate(stepTimer.begin() + 1, stepTimer.end() - 1, 0.0f) / (stepTimer.size() - 2) };

        m_Ex2Samples.push_back(average);
    }
}

void dae::TrashTheCacheComponent::Excercise2alt()
{
    m_Ex2AltSamples.clear();

    const unsigned int length{ 1'000'000 };
    std::vector<GameObject3DAlt> pBuffer{};
    pBuffer.resize(length);

    for (auto stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        std::vector<float> stepTimer{};

        for (int sample{}; sample < m_Ex2SampleAmount; sample++)
        {

            auto start = std::chrono::high_resolution_clock::now();

            for (int i{ 0 }; i < length; i += stepsize)
            {
                pBuffer[i].ID *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();

            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            stepTimer.push_back(static_cast<float>(elapsedTime));
        }

        std::sort(stepTimer.begin(), stepTimer.end());

        const float average{ std::accumulate(stepTimer.begin() + 1, stepTimer.end() - 1, 0.0f) / (stepTimer.size() - 2) };

        m_Ex2AltSamples.push_back(average);
    }
}
