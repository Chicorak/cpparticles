// Header for the Spring class.
#ifndef Spring_hpp
#define Spring_hpp
#define _USE_MATH_DEFINES

#include <math.h>
#include "Joint.hpp"


// Handles the movement and forces acting upon the spring.
class Spring {
public:
	Spring(Joint *p1, Joint *p2, float restlength=50, float strength=0.5);
	Joint *getP1() { return p1; }
	Joint *getP2() { return p2; }
	void update();
	
protected:
	float length;
	float strength;
	Joint *p1;
	Joint *p2;
};

#endif // spring_hpp
