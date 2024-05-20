#pragma once
#include <memory>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureRenderer : public Component
	{
	public:
		explicit TextureRenderer(GameObject* pParent, std::shared_ptr<Texture2D> pTexture, int vframes = 1, int hframes = 1);

		void Render() const override;

		int GetVFrames() const { return m_VFrames; }
		int GetHFrames() const { return m_HFrames; }

		uint16_t frame{ 0 };

	protected:
		std::shared_ptr<Texture2D> m_pTexture;

		int m_VFrames;
		int m_HFrames;
	};
}
