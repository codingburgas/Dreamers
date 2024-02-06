#ifndef Game_Graphics
#define Game_Graphics
#include <SDL.h>

class GameGraphics {

public:

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

private:
	static GameGraphics* sInstance;
	static bool sInitialized;
	SDL_Window* mWindow;
	SDL_Surface* mBackBuffer;

	SDL_Renderer* mRenderer;
public:
	static GameGraphics* Instance();
	static void Release();
	static bool Initialized();
	SDL_Texture* LoadTexture(std::string path);
	void ClearBackBuffer();
	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL);
	void Render();

private:
	GameGraphics();
	~GameGraphics();

	bool Init();
};

#endif