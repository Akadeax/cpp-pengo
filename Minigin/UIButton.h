#pragma once
#include <functional>
#include <glm/vec2.hpp>

#include "Component.h"
#include "Signal.h"

namespace dae
{
	class UIButton final : public Component
	{
	public:
		Signal<> Hover{};
		Signal<> MouseDown{};
		Signal<> MouseUp{};

		explicit UIButton(GameObject* pParent, glm::vec2 buttonClickRect);

		void Ready() override;
		void Update() override;

		void Render() const override;

	private:
		glm::vec2 m_ButtonClickSize;

		void CheckHover() const;
		void CheckMouseDown(glm::vec2 pos) const;
		void CheckMouseUp(glm::vec2 pos) const;

		bool IsInBounds(glm::vec2 clickPos) const;
	};


}
