#include "AssetManager.h"

AssetManager* AssetManager::singletonInstance = NULL;

AssetManager* AssetManager::Instance() {

	// It ensures only one instance is created
	if (singletonInstance == nullptr)
		singletonInstance = new AssetManager();

	return singletonInstance;
}
void AssetManager::release() {
	delete singletonInstance;
	singletonInstance = NULL;
}
AssetManager::AssetManager()
{

}
AssetManager::~AssetManager()
{
	// Iterates through the assetTextures map, which stores texture assets as key-value pairs
	for (std::pair<std::string, SDL_Texture*> texture : assetTextures)
	{
		// Checks if the texture pointer is not nullptr, then destroys the SDL_Texture
		if (texture.second != nullptr) 
		{
			SDL_DestroyTexture(texture.second);
		}
	}
	// Clears the assetTextures map
	assetTextures.clear();  
}

// Loading and returning a texture based on filename
SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	// Constructs the full path by appending the filename to the base path obtained from SDL_GetBasePath
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	// Load the texture using and store it in the assetTextures map
	if (assetTextures[fullPath] == nullptr)
		assetTextures[fullPath] = GameGraphics::Instance()->loadTexture(fullPath);

	// Return the texture associated with the fullPath key in the assetTextures map
	return assetTextures[fullPath]; 
}