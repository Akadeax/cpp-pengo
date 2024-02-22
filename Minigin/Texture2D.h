#pragma once
#include <glm/vec2.hpp>

struct SDL_Texture;
namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final
	{
	public:
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		SDL_Texture* GetSDLTexture() const { return m_pTexture; }
		glm::ivec2 GetSize() const;

		Texture2D(Texture2D&& rhs) = delete;
		Texture2D(const Texture2D& rhs) = delete;
		Texture2D& operator=(Texture2D&& rhs) = delete;
		Texture2D& operator=(const Texture2D& rhs) = delete;

	private:
		SDL_Texture* m_pTexture;
	};
}
