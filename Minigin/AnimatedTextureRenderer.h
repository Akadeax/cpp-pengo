#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "TextureRenderer.h"

namespace dae
{
	using AnimationID = size_t;

	struct Animation
	{
		float duration{ 1.f };
		std::vector<uint16_t> frames{};
	};

	class AnimatedTextureRenderer final : public TextureRenderer
	{
	public:
		explicit AnimatedTextureRenderer(
			GameObject* pParent,
			std::shared_ptr<Texture2D> pTexture,
			int vframes = 1,
			int hframes = 1
		);

		void Update() override;

		AnimationID AddAnimation(Animation&& animation);

		void SetAnimation(AnimationID id);
		void SetDirectionalAnimation(glm::ivec2 dir, AnimationID up, AnimationID right, AnimationID down, AnimationID left);

	private:
		std::vector<Animation> m_Animations{};
		AnimationID m_CurrentAnimation{ 0 };

		float m_TimeSinceAnimEnter{ 0.f };
	};
}

