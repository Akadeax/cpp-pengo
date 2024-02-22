#pragma once
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	class Font;

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& dataPath);
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

	private:
		friend class Singleton;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
