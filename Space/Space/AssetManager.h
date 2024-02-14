#pragma once
#include "Graphics.h"
#include <map> // Allows storing elements in key-value pairs

class AssetManager {

public:
	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(std::string filename); // Get a texture based on the filename

private:

	static AssetManager* singletonInstance;

	// Map to store texture assets
	// Enabling efficient lookup and retrieval of texture assets
	std::map<std::string, SDL_Texture*>assetTextures;

	AssetManager();
	~AssetManager();


};
