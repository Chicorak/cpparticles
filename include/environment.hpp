// Header for the Environment class.
#ifndef environment_hpp
#define environment_hpp
#define _USE_MATH_DEFINES

#include <math.h>
#include <random>
#include "Joint.hpp"
#include "Spring.hpp"


// Handles all interaction between Joints, springs and attributes within the environment.
class Environment {
public:
	Environment(int width, int height);
	~Environment();
	int getHeight() { return height; }
	int getWidth() { return width; }
	Joint * addJoint();
	Joint * addJoint(float x, float y, float size=10, float mass=100, float speed=0, float angle=0, float elasticity=0.9);
	Joint * getJoint(float x, float y);
	Spring * addSpring(Joint *p1, Joint *p2, float length=50, float strength=0.5);
	std::vector<Joint* > getJoints() { return Joints; }
	std::vector<Spring* > getSprings() { return springs; }
	void bounce(Joint *Joint);
	void removeJoint(Joint *Joint);
	void removeSpring(Spring *spring);
	void setAirMass(float a) { airMass = a; }
	void setAllowAccelerate(bool setting) { allowAccelerate = setting; }
	void setAllowAttract(bool setting) { allowAttract = setting; }
	void setAllowBounce(bool setting) { allowBounce = setting; }
	void setAllowCollide(bool setting) { allowCollide = setting; }
	void setAllowCombine(bool setting) { allowCombine = setting; }
	void setAllowDrag(bool setting) { allowDrag = setting; }
	void setAllowMove(bool setting) { allowMove = setting; }
	void setElasticity(float e) { elasticity = e; }
	void update();
	
protected:
	const int height;
	const int width;
	bool allowAccelerate = true;
	bool allowAttract = false;
	bool allowBounce = true;
	bool allowCollide = true;
	bool allowCombine = false;
	bool allowDrag = true;
	bool allowMove = true;
	float airMass = 0.2;
	float elasticity = 0.75;
	std::vector<Joint *> Joints;
	std::vector<Spring *> springs;
	Vector acceleration = {M_PI, 0.2};
};

#endif // environment_hpp
