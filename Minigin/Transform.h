#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		explicit Transform();
		explicit Transform(glm::vec2 pos);

		const glm::vec2& GetPosition() const { return m_Position; }

		void SetPosition(glm::vec2 vec);
		void SetPosition(float x, float y);

	private:
		glm::vec2 m_Position;
	};
}
