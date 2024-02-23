#pragma once
#include "Singleton.h"
namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		float GetDeltaTime() const { return m_DeltaTime; }
		void SetDeltaTime(float val) { m_DeltaTime = val; }

		static constexpr float FIXED_TIME_STEP{ 1.f / 50.f };

	private:
		friend class Singleton;
		Time() = default;

		float m_DeltaTime{ 0.f };
	};
}
