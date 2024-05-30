#pragma once
#include "ResourceSystem.h"

namespace dae
{
	class SDLResourceSystem final : public ResourceSystem
	{
	public:
		SDLResourceSystem();
		~SDLResourceSystem() override = default;

		std::shared_ptr<Texture2D> LoadTexture(const std::string&) const override;
		std::shared_ptr<Font> LoadFont(const std::string&, unsigned) const override;

	private:
		std::string m_DataPath{};
	};
}
