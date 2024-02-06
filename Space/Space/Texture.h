#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameEntity.h"
#include "AssetManager.h"

class Texture: public GameEntity{
	 
private:
	SDL_Texture* mTex;
	GameGraphics* mGraphics;
	int mWidth;
	int mHeight;
	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;
public:
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	~Texture();
	virtual void Render();
};

#endif
