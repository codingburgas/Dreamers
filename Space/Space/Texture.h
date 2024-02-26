#pragma once
#include "AssetManager.h"

// The colon followed by public indicates that Texture inherits public members and functions from the GameEntity class
class Texture{

public:

	// The constructor is used to create a Texture object and loads the texture from the provided path
	Texture(std::string path); 
	Texture(std::string path, int x, int y, int width, int height);
	~Texture();

	void renderDestination();
	void render();

private:

	// SDL_Texture pointer to store the loaded texture
	SDL_Texture* mainTexture; 
	// Pointer to the graphics subsystem for rendering
	GameGraphics* textureGraphics; 
	SDL_Rect destinationRect;

	int visualWidth;
	int visualHeight;
};