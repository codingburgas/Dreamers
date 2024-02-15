#include "Texture.h"

Texture::Texture(std::string filename)
{
	textureGraphics = GameGraphics::Instance();
	mainTexture = AssetManager::Instance()->GetTexture(filename); // Load the texture

	// Querying the dimensions of the 'mainTexture' to retrieve its width and height
	SDL_QueryTexture(mainTexture, NULL, NULL, &visualWidth, &visualHeight);
}

Texture::~Texture()
{
	mainTexture = NULL;
	textureGraphics = NULL;
}

// Render function: Draw the loaded texture using the GameGraphics instance
void Texture::Render()
{
	textureGraphics->DrawTexture(mainTexture); //It calls the DrawTexture function from the textureGraphics instance to render the mainTexture
}