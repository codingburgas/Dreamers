#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	// Set the initial position coordinates of the entity
	position.x = x;
	position.y = y;

	rotationAngle = 0.0f;
	isActive = true;
	parentEntity = NULL; // Initialize the parentEntity pointer to NULL as there is no parent entity initially
}
GameEntity::~GameEntity()
{
	parentEntity = NULL;
}

// Set the position of the entity
void GameEntity::Pos(Vector2 pos)
{
	position = pos;
}

// Method to retrieve the position of the entity in the specified coordinate space
Vector2 GameEntity::Pos(SPACE space)
{

	// Return the local position if the space is local or if there is no parent entity
	if (space == local || parentEntity == NULL)
		return position;

	/* This line of code calculates the world position of the entity
	 based on the parent entity's position and rotation*/
	return parentEntity->Pos(world) + RotateVector(position, parentEntity->Rotation(local));
}

// Method to set the rotation angle of the entity
void GameEntity::Rotation(float r)
{
	rotationAngle = r;

	// Check if the rotation angle exceeds 360 degrees and adjust it to fit within the valid
	if (rotationAngle > 360.0f)
		rotationAngle -= 360.0f;

	// Check if the rotation angle is negative and adjust it to fit within the valid range
	if (rotationAngle < 0.0f)
		rotationAngle += 360.0f;
}