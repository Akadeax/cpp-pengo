#include "SDLResourceSystem.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdexcept>

#include "Renderer.h"

dae::SDLResourceSystem::SDLResourceSystem()
{
	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::SDLResourceSystem::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_DataPath + file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<dae::Font> dae::SDLResourceSystem::LoadFont(const std::string& file, unsigned size) const
{
	return std::make_shared<Font>(m_DataPath + file, size);
}
