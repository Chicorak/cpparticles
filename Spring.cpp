// Contains member functions of the Spring class.
// Handles the movement and forces acting upon the spring.
#include "../include/Spring.hpp"


// Spring constructor.
Spring::Spring(Joint *p1, Joint *p2, float restlength, float strength):
p1(p1), p2(p2), length(restlength), strength(strength) {
}


// Updates the spring.
void Spring::update() {
	float dx = p1->getX() - p2->getX();
	float dy = p1->getY() - p2->getY();
	float distance = hypot(dx, dy) - length;
	float theta = atan2(dy, dx);
	float force = (length - distance) * strength;
	p1->accelerate(Vector{static_cast<float>(theta + 0.5*M_PI), force / p1->getMass()});
	p2->accelerate(Vector{static_cast<float>(theta - 0.5*M_PI), force / p2->getMass()});
}
