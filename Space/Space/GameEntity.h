#pragma once
#include "MathHelper.h"
class GameEntity {

public:
	// Defines an enumeration
	enum SPACE{local=0, world=1};

	GameEntity(float x = 0.0f, float y = 0.0f);
	~GameEntity();

	void Pos(Vector2 pos); // Get the position of the entity
	Vector2 Pos(SPACE space = world); // Allows specifying the coordinate space
	void Rotation(float rotation); // Get the rotation of the entity
	float Rotation(SPACE space = world); // Allows specifying the coordinate space

	void Active(bool active); // Active or deactive the entity
	bool Active();
	void Parent(GameEntity* parent);
	GameEntity* Parent();

	virtual void Update();
	virtual void Render();

private:

	Vector2 mPos;
	float mRotation; // The rotation angle of the entity
	bool mActive;
	GameEntity* mParent;
};