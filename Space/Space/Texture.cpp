#include "Texture.h"

Texture::Texture(std::string path)
{
	textureGraphics = GameGraphics::Instance();
	mainTexture = textureGraphics->LoadTexture(path); // Load the texture
}
Texture::~Texture()
{
	SDL_DestroyTexture(mainTexture); // Release the texture
	mainTexture = NULL;
	textureGraphics = NULL;
}

// Render function: Draw the loaded texture using the GameGraphics instance
void Texture::Render()
{
	textureGraphics->DrawTexture(mainTexture); //It calls the DrawTexture function from the textureGraphics instance to render the mainTexture
}