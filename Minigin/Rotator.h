#pragma once
#include "Component.h"

namespace dae
{
	class Rotator final : public Component
	{
	public:
		explicit Rotator(GameObject* pParent, float radiansPerSecond);
		void Update() override;

	private:
		float m_RadiansPerSecond;
	};
}

