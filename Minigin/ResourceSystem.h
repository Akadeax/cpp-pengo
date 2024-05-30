#pragma once
#include <memory>
#include <string>

#include "Font.h"
#include "Texture2D.h"


namespace dae
{
	class ResourceSystem
	{
	public:
		virtual ~ResourceSystem() = default;

		virtual std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const = 0;
		virtual std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const = 0;
	};
}
