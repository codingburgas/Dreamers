#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

// The colon followed by public indicates that Texture inherits public members and functions from the GameEntity class
class Texture :public GameEntity {

public:

	Texture(std::string path); // The constructor is used to create a Texture object and loads the texture from the provided path
	~Texture();

	virtual void Render();

private:

	SDL_Texture* mainTexture; // SDL_Texture pointer to store the loaded texture
	GameGraphics* textureGraphics;  // Pointer to the graphics subsystem for rendering

	int visualWidth;
	int visualHeight;
};