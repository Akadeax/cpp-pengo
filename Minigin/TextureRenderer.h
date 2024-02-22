#pragma once
#include <memory>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureRenderer : public Component
	{
	public:
		explicit TextureRenderer(GameObject* pParent, std::shared_ptr<Texture2D> pTexture);

		void Render() const override;

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}
