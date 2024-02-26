#include "Graphics.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
	// Create an instance of the GameManager to manage the game
	GameManager* game = GameManager::Instance(); 
	game->run();
	// Release recources held by the GameManager
	GameManager::release(); 
	game = NULL;

	// Indicate a successful program execution
	return 0; 
}