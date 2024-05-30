#pragma once
#include "Component.h"
#include "Signal.h"

namespace dae
{
	class Timer final : public Component
	{
	public:
		Signal<> Timeout{};

		explicit Timer(GameObject* pParent, float duration, bool startOnReady = false);
		void Update() override;

		void Start();
		bool IsRunning() const { return m_IsRunning; }

	private:
		bool m_IsRunning{ false };

		float m_Duration{};
		float m_CurrentDuration{};
	};
}

