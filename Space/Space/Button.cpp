#include "Button.h"
#include <SDL_ttf.h>

Button::Button(const char* text, int x, int y, int width, int height, SDL_Renderer* renderer) {
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    this->renderer = renderer;

    // Render text on the button
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, { 255, 255, 255 });
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

Button::~Button() {
    SDL_DestroyTexture(texture);
}

void Button::Render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Button::IsClicked(int mouseX, int mouseY) {
    return mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y && mouseY <= rect.y + rect.h;
}