#include "Texture.h"

Texture::Texture(std::string path)
{
	textureGraphics = GameGraphics::Instance();
	mainTexture = AssetManager::Instance()->GetTexture(path); // Load the texture

	// Querying the dimensions of the 'mainTexture' to retrieve its width and height
	SDL_QueryTexture(mainTexture, NULL, NULL, &visualWidth, &visualHeight);
}

Texture::Texture(std::string path, int x, int y, int width, int height)
{
	textureGraphics = GameGraphics::Instance();
	mainTexture = AssetManager::Instance()->GetTexture(path);
	destinationRect = { x, y, width, height };
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

// Render function: Draw the loaded texture using the GameGraphics instance
void Texture::RenderDestination()
{
	textureGraphics->DrawTexture(mainTexture, &destinationRect); //It calls the DrawTexture function from the textureGraphics instance to render the mainTexture
}