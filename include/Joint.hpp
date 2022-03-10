// Header for the Joint class and Vector struct.
#ifndef joint_hpp
#define joint_hpp
#define _USE_MATH_DEFINES

#include <math.h>


// Contains direction (angle) and magnitude (speed).
struct Vector {
	float angle;
	float speed;
};

Vector operator+(Vector const& v1, Vector const& v2);


// Handles the movement and forces acting upon the Joint and surrounding Joints.
class Joint {
public:
	Joint(float x, float y, float size, float mass, float speed, float angle, float elasticity, float drag);
	Joint *getCollideWith() { return collideWith; }
	float getAngle() { return angle; }
	float getDrag() { return drag; }
	float getElasticity() { return elasticity; }
	float getMass() { return mass; }
	float getSize() { return size; }
	float getSpeed() { return speed; }
	float getX() { return x; }
	float getY() { return y; }
	void accelerate(Vector vector);
	void attract(Joint *otherP);
	void checkCollide(Joint *otherP);
	void combine(Joint *otherP);
	void experienceDrag();
	void move();
	void moveTo(float moveX, float moveY);
	void setAngle(float a) { angle = a; }
	void setDrag(float d) { drag = d; }
	void setElasticity(float e) { elasticity = e; }
	void setMass(float m) { mass = m; }
	void setSize(float s) { size = s; }
	void setSpeed(float s) { speed = s; }
	void setX(float xCoord) { x = xCoord; }
	void setY(float yCoord) { y = yCoord; }
	
protected:
	float angle;
	float drag;
	float elasticity;
	float mass;
	float size;
	float speed;
	float x;
	float y;
	Joint *collideWith = NULL;
};

#endif // Joint_hpp
