#pragma once
#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, glm::vec2 pos, float rotation, glm::vec2 scale) const;
		void RenderTexture(
			const Texture2D& texture,
			const SDL_Rect* sourceRect,
			glm::ivec2 destSize,
			glm::vec2 pos,
			float rotation,
			glm::vec2 scale
		) const;

		void RenderRect(glm::vec2 pos, glm::vec2 size, glm::vec<4, Uint8> color) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

	private:
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
		SDL_Color m_ClearColor{};
	};
}

