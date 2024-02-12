#pragma once
#include <SDL.h>

class Button {
public:
    Button(const char* text, int x, int y, int width, int height, SDL_Renderer* renderer);
    ~Button();

    void Render();
    bool IsClicked(int mouseX, int mouseY);

private:
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
};