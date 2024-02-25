#pragma once
#include <string>
#include <map>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Graphics.h"
class TextManager
{
private:
	TTF_Font* font;
	SDL_Color textColor = { 255, 255, 255 };
	std::vector<std::pair<SDL_Texture*, SDL_Rect>> texts;
public:
	TextManager(int fontSize)
	{
		if (TTF_Init() < 0) {
			// Handle TTF initialization error
			std::cerr << "SDL_ttf could not initialize: " << TTF_GetError() << std::endl;
			return;
		}
		std::string path = SDL_GetBasePath();
		path += "Assets/Peanut Butter.ttf";
		font = TTF_OpenFont(path.c_str(), fontSize);
		if (!font) {
			// Handle font loading error
			std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
		}
	}

	TextManager()
	{
	}

	void AddText(std::string text, int x, int y, int width, int height)
	{
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
		SDL_Rect destRect = { x, y, width, height };

		texts.push_back(std::pair<SDL_Texture*, SDL_Rect>(SDL_CreateTextureFromSurface(GameGraphics::Instance()->renderer, textSurface), destRect));
	}

	void Render()
	{
		for (size_t i = 0; i < texts.size(); i++)
		{
			SDL_RenderCopy(GameGraphics::Instance()->renderer, texts[i].first, nullptr, &texts[i].second);
		}
	}

	void ResetText()
	{
		texts.clear();
	}
};