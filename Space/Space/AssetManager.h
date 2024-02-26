#pragma once
#include "Graphics.h"
// Allows storing elements in key-value pairs
#include <map> 

class AssetManager {

private:

	static AssetManager* singletonInstance;

	// Map to store texture assets
	// Enabling efficient lookup and retrieval of texture assets
	std::map<std::string, SDL_Texture*>assetTextures;

	AssetManager();
	~AssetManager();

public:
	static AssetManager* Instance();
	static void release();

	// Get a texture based on the filename
	SDL_Texture* GetTexture(std::string filename); 
};
