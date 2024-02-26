#include "Texture.h"

Texture::Texture(std::string path)
{
	textureGraphics = GameGraphics::Instance();
	// Load the texture
	mainTexture = AssetManager::Instance()->GetTexture(path); 

	// Querying the dimensions of the 'mainTexture' to retrieve its width and height
	SDL_QueryTexture(mainTexture, NULL, NULL, &visualWidth, &visualHeight);
}

// It gets the main texture from the AssetManager using the provided path.
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
void Texture::render()
{
	// It calls the DrawTexture function from the textureGraphics instance to render the mainTexture
	textureGraphics->drawTexture(mainTexture); 
}

// Render function: Draw the loaded texture using the GameGraphics instance
void Texture::renderDestination()
{
	// It calls the DrawTexture function from the textureGraphics instance to render the mainTexture
	textureGraphics->drawTexture(mainTexture, &destinationRect); 
}