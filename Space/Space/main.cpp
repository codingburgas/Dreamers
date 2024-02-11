#include "Graphics.h"
#include "GameManager.h"

int main(int argc, char* argv[])
{
	GameManager* game = GameManager::Instance(); // Create an instance of the GameManager to manage the game
	game->Run();
	GameManager::Release(); // Release recources held by the GameManager
	game = NULL;

	return 0; // Indicate a successful program execution
}