#include <math.h>

// PI value
const float PI = 3.14159265f; 
// Conversion factor from degrese to radians
const float DEG_TO_RAD = PI / 180.0F; 

// 2D Vector structure
struct Vector2 {

	float x;
	float y;

	// Constructor with default values
	// The constructor initializes the x and y components of the vector with the default values
	Vector2(float _x = 0.0f, float _y = 0.0f)
		// Initialized the x and y components to given values
		:x(_x), y(_y){} 
	
	// Calculate the square of the magnitude of the vector
	float magnitudeSqr()
	{
		return x * x + y * y;
	}
	// Calculate the magnitude of the vector
	float magnitude() {
		return (float)sqrt(x * x + y * y);
	}
	// Return a normalized version of the vector
	Vector2 normalized() {
		float mag = magnitude();
		return Vector2(x / mag, y / mag);
	}
};

inline Vector2 operator+(const Vector2& Ihs, const Vector2& rhs)
{
	return Vector2(Ihs.x + rhs.x, Ihs.y + rhs.y);
}
inline Vector2 operator-(const Vector2& Ihs, const Vector2& rhs) {
	return Vector2(Ihs.x - rhs.x, Ihs.y - rhs.y);
}

// Function to rotate a vector by a specified angle in degrees
inline Vector2 rotateVector(Vector2& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RAD); // Convert angle to radians
	// Returns a new Vector2 representing the input vector rotated by the specified angle
	// The rotation is achieved by applying the equations for rotating a vector in 2D space using cosine and sine functions
	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle))); // Rotate the vector using trigonometric function
}