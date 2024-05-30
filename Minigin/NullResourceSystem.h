#pragma once
#include "ResourceSystem.h"

namespace dae
{
	class NullResourceSystem final : public ResourceSystem
	{
	public:
		NullResourceSystem() = default;
		~NullResourceSystem() override = default;

		std::shared_ptr<Texture2D> LoadTexture(const std::string&) const override { return nullptr; }
		std::shared_ptr<Font> LoadFont(const std::string&, unsigned) const override { return nullptr; }

	private:
		std::string m_DataPath{};
	};
}
