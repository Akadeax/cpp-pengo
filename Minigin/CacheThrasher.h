#pragma once
#include <imgui_plot.h>
#include <vector>

#include "Component.h"
namespace dae
{
    class CacheThrasher final : public Component
    {
    public:
	    explicit CacheThrasher(GameObject* pParent);

        void OnImGui() override;

    private:
        struct StepResult
        {
            int stepSize;
            float averageTimeMs;
        };

        std::vector<float> m_Steps{};
        std::vector<float> m_Averages{};
        ImGui::PlotConfig m_Conf;
        bool m_ShowGraph{ false };

        std::vector<StepResult> AllocateIntegers();
        std::vector<StepResult> AllocateGameObjects();
        std::vector<StepResult> AllocateGameObjectsAlt();

        struct Transform
        {
            float matrix[16] = {
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1 };
        };

        struct GameObject3D
        {
            Transform transform;
            int ID;
        };
        struct GameObject3DAlt
        {
            Transform* transform;
            int ID;
        };
    };
}


