#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

// The colon followed by public indicates that Texture inherits public members and functions from the GameEntity class
class Texture{

public:

	Texture(std::string path); // The constructor is used to create a Texture object and loads the texture from the provided path
	Texture(std::string path, int x, int y, int width, int height);
	~Texture();

	void RenderDestination();
	void Render();

private:

	SDL_Texture* mainTexture; // SDL_Texture pointer to store the loaded texture
	GameGraphics* textureGraphics;  // Pointer to the graphics subsystem for rendering
	SDL_Rect destinationRect;

	int visualWidth;
	int visualHeight;
};