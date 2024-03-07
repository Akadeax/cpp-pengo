#include "CacheThrasher.h"

#include <chrono>
#include <SDL_syswm.h>
#include <vector>
#include <algorithm>

dae::CacheThrasher::CacheThrasher(GameObject* pParent)
	: Component(pParent)
{
}

void dae::CacheThrasher::OnImGui()
{
	m_Conf.scale.min = 0;
	m_Conf.tooltip.show = true;
	m_Conf.tooltip.format = "x=%.2f, y=%.2f";
	m_Conf.grid_x.show = true;
	m_Conf.grid_y.show = true;
	m_Conf.frame_size = ImVec2(200, 200);
	m_Conf.line_thickness = 2.f;

	ImGui::Begin("Exercises");
	if (ImGui::SmallButton("Thrash the Cache with ints"))
	{
		m_Steps.clear();
		m_Averages.clear();

		m_ShowGraph = true;

		std::vector<StepResult> results{ AllocateIntegers() };
		
		std::ranges::for_each(results, [&](const auto& result)
		{
			m_Steps.push_back(static_cast<float>(result.stepSize));
			m_Averages.push_back(result.averageTimeMs);
		});

		m_Conf.scale.max = *std::ranges::max_element(m_Averages);
		m_Conf.values.xs = m_Steps.data();
		m_Conf.values.ys = m_Averages.data();
		m_Conf.values.count = static_cast<int>(m_Averages.size());
	}

	if (ImGui::SmallButton("Thrash the Cache with GameObject3D"))
	{
		m_Steps.clear();
		m_Averages.clear();

		m_ShowGraph = true;

		std::vector<StepResult> results{ AllocateGameObjects() };

		std::ranges::for_each(results, [&](const auto& result)
			{
				m_Steps.push_back(static_cast<float>(result.stepSize));
				m_Averages.push_back(result.averageTimeMs);
			});

		m_Conf.scale.max = *std::ranges::max_element(m_Averages);
		m_Conf.values.xs = m_Steps.data();
		m_Conf.values.ys = m_Averages.data();
		m_Conf.values.count = static_cast<int>(m_Averages.size());
	}

	if (ImGui::SmallButton("Thrash the Cache with GameObject3DAlt"))
	{
		m_Steps.clear();
		m_Averages.clear();

		m_ShowGraph = true;

		std::vector<StepResult> results{ AllocateGameObjectsAlt() };

		std::ranges::for_each(results, [&](const auto& result)
			{
				m_Steps.push_back(static_cast<float>(result.stepSize));
				m_Averages.push_back(result.averageTimeMs);
			});

		m_Conf.scale.max = *std::ranges::max_element(m_Averages);
		m_Conf.values.xs = m_Steps.data();
		m_Conf.values.ys = m_Averages.data();
		m_Conf.values.count = static_cast<int>(m_Averages.size());
	}

	if (m_ShowGraph)
	{
		ImGui::Plot("plot", m_Conf);
	}
	ImGui::End();
}

std::vector<dae::CacheThrasher::StepResult> dae::CacheThrasher::AllocateIntegers()
{
	std::vector<int> values(50'108'000);

	std::vector<StepResult> results{};

	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		std::vector<long long> samples{};
		for (size_t sampleIndex{ 0 }; sampleIndex < 10; ++sampleIndex)
		{
			auto start{ std::chrono::high_resolution_clock::now() };
			for (size_t i{ 0 }; i < values.size(); i += stepSize)
			{
				values[i] *= 2;
			}
			auto end{ std::chrono::high_resolution_clock::now() };

			long long elapsed{ std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() };
			samples.push_back(elapsed);
		}

		std::sort(std::begin(samples), std::end(samples));

		long long sum{};
		for (size_t i{ 1 }; i < samples.size() - 1; ++i)
		{
			sum += samples[i];
		}

		float average{ static_cast<float>(sum) / static_cast<float>(samples.size()) };
		results.push_back({ stepSize, average });
	}

	return results;
}

std::vector<dae::CacheThrasher::StepResult> dae::CacheThrasher::AllocateGameObjects()
{
	std::vector<GameObject3D> values(500'000);

	std::vector<StepResult> results{};

	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		std::vector<long long> samples{};
		for (size_t sampleIndex{ 0 }; sampleIndex < 100; ++sampleIndex)
		{
			auto start{ std::chrono::high_resolution_clock::now() };
			for (size_t i{ 0 }; i < values.size(); i += stepSize)
			{
				values[i].ID *= 2;
			}
			auto end{ std::chrono::high_resolution_clock::now() };
			long long elapsed{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
			samples.push_back(elapsed);
		}

		std::sort(std::begin(samples), std::end(samples));

		long long sum{};
		for (size_t i{ 10 }; i < samples.size() - 10; ++i)
		{
			sum += samples[i];
		}

		float average{ static_cast<float>(sum) / static_cast<float>(samples.size()) };
		results.push_back({ stepSize, average });
	}

	return results;
}

std::vector<dae::CacheThrasher::StepResult> dae::CacheThrasher::AllocateGameObjectsAlt()
{
	std::vector<GameObject3DAlt> values(500'000);

	std::vector<StepResult> results{};

	for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		std::vector<long long> samples{};
		for (size_t sampleIndex{ 0 }; sampleIndex < 100; ++sampleIndex)
		{
			auto start{ std::chrono::high_resolution_clock::now() };
			for (size_t i{ 0 }; i < values.size(); i += stepSize)
			{
				values[i].ID *= 2;
			}
			auto end{ std::chrono::high_resolution_clock::now() };
			long long elapsed{ std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() };
			samples.push_back(elapsed);
		}

		std::sort(std::begin(samples), std::end(samples));

		long long sum{};
		for (size_t i{ 10 }; i < samples.size() - 10; ++i)
		{
			sum += samples[i];
		}

		float average{ static_cast<float>(sum) / static_cast<float>(samples.size()) };
		results.push_back({ stepSize, average });
	}

	return results;
}
