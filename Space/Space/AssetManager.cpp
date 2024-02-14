#include "AssetManager.h"

AssetManager* AssetManager::singletonInstance = NULL;

AssetManager* AssetManager::Instance() {

	// It ensures only one instance is created
	if (singletonInstance == nullptr)
		singletonInstance = new AssetManager();

	return singletonInstance;
}
void AssetManager::Release() {
	delete singletonInstance;
	singletonInstance = NULL;
}
AssetManager::AssetManager()
{

}