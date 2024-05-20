#include "AnimatedTextureRenderer.h"

#include <iostream>
#include <glm/common.hpp>

#include "GameTime.h"

dae::AnimatedTextureRenderer::AnimatedTextureRenderer(
	GameObject* pParent,
	std::shared_ptr<Texture2D> pTexture,
	int vframes, int hframes
)
	: TextureRenderer(pParent, std::move(pTexture), vframes, hframes)
{
}

void dae::AnimatedTextureRenderer::Update()
{

	const Animation& current{ m_Animations[m_CurrentAnimation] };

	const float delta{ GameTime::GetInstance().GetDeltaTime() };
	if (m_TimeSinceAnimEnter + delta >= current.duration)
	{
		m_TimeSinceAnimEnter = 0.f;
	}
	else
	{
		m_TimeSinceAnimEnter += delta;
	}

	const float singleFrameDuration{ current.duration / static_cast<float>(current.frames.size()) };
	const uint16_t frameIndex{ static_cast<uint16_t>(m_TimeSinceAnimEnter / singleFrameDuration) };
	frame = current.frames[frameIndex];
}

/**
 * \brief add an animation to this handler
 * \return the ID this animation can be referenced by
 */
dae::AnimationID dae::AnimatedTextureRenderer::AddAnimation(Animation&& animation)
{
	m_Animations.push_back(std::move(animation));
	return m_Animations.size() - 1;
}

void dae::AnimatedTextureRenderer::SetAnimation(AnimationID id)
{
	m_CurrentAnimation = id;
	m_TimeSinceAnimEnter = 0.f;
}

void dae::AnimatedTextureRenderer::SetDirectionalAnimation(glm::ivec2 dir, AnimationID up, AnimationID right,
	AnimationID down, AnimationID left)
{
	if (dir.y == -1)      SetAnimation(up);
	else if (dir.x == 1)  SetAnimation(right);
	else if (dir.y == 1)  SetAnimation(down);
	else if (dir.x == -1) SetAnimation(left);
}
