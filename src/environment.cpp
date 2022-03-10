// Contains member functions of the Environment class.
// Handles all interaction between Joints, springs and attributes within the environment.
#include "../include/environment.hpp"


// Environment constructor.
Environment::Environment(int width, int height):
width(width), height(height) {
}


// Environment destructor. Destroys all Joints and springs in the environment.
Environment::~Environment() {
	for (int i = 0; i < springs.size(); i++) {
		delete springs[i];
	}
	for (int i = 0; i < Joints.size(); i++) {
		delete Joints[i];
	}
}


// Adds a Joint with randomly generated attributes to the environment and returns a pointer to the Joint.
Joint * Environment::addJoint() {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<int> sizeDist(10,20);
	float size = sizeDist(rd);
	std::uniform_int_distribution<int> massDist(100, 10000);
	float mass = massDist(rd);
	std::uniform_int_distribution<int> xDist(size, width - size);
	float x = xDist(rd);
	std::uniform_int_distribution<int> yDist(size, height - size);
	float y = yDist(rd);
	std::uniform_real_distribution<float> speedDist (0, 1);
	float speed = speedDist(rd);
	std::uniform_real_distribution<float> angleDist (0, 2 * M_PI);
	float angle = angleDist(rd);
	std::uniform_real_distribution<float> elasticityDist (0.8, 1);
	float elasticity = elasticityDist(rd);
	return addJoint(x, y, size, mass, speed, angle, elasticity);
}


// Adds a Joint with parameter-specified attributes to the environment and returns a pointer to the Joint.
Joint * Environment::addJoint(float x, float y, float size, float mass, float speed, float angle, float elasticity) {
	// Equation for drag [source]: http://www.petercollingridge.co.uk/tutorials/pygame-physics-simulation/mass/
	float drag = pow((mass / (mass + airMass)), size);
	Joint *johnt = new Joint(x, y, size, mass, speed, angle, elasticity, drag);
	Joints.push_back(johnt);
	return johnt;
}


// Returns a pointer to the Joint from the environment at the coordinates (x, y), otherwise nullptr.
Joint * Environment::getJoint(float x, float y){
	for (int i = 0; i < Joints.size(); i++) {
		if (hypot(Joints[i]->getX() - x, Joints[i]->getY() - y) <= Joints[i]->getSize()) {
			return Joints[i];
		}
	}
	return nullptr;
}


// Adds a spring connecting two Joints in the environment and returns a pointer to the spring.
Spring * Environment::addSpring(Joint *p1, Joint *p2, float length, float strength) {
	Spring *spring = new Spring(p1, p2, length, strength);
	springs.push_back(spring);
	return spring;
}


// Bounces a Joint if in contact with boundary of the environment.
void Environment::bounce(Joint *Joint) {
	// Joint hits the right boundary:
	if (Joint->getX() > (width - Joint->getSize())) {
		Joint->setX(2 * (width - Joint->getSize()) - Joint->getX());
		Joint->setAngle(-Joint->getAngle());
		Joint->setSpeed(Joint->getSpeed() * Joint->getElasticity());
	// Joint hits the left boundary:
	} else if (Joint->getX() < Joint->getSize()) {
		Joint->setX(2 * Joint->getSize() - Joint->getX());
		Joint->setAngle(-Joint->getAngle());
		Joint->setSpeed(Joint->getSpeed() * Joint->getElasticity());
	}
	// Joint hits the bottom boundary:
	if (Joint->getY() > (height - Joint->getSize())) {
		Joint->setY(2 * (height - Joint->getSize()) - Joint->getY());
		Joint->setAngle(M_PI - Joint->getAngle());
		Joint->setSpeed(Joint->getSpeed() * Joint->getElasticity());
	// Joint hits the top boundary:
	} else if (Joint->getY() < Joint->getSize()) {
		Joint->setY(2 * Joint->getSize() - Joint->getY());
		Joint->setAngle(M_PI - Joint->getAngle());
		Joint->setSpeed(Joint->getSpeed() * Joint->getElasticity());
	}
}


// Removes a Joint from the environment.
void Environment::removeJoint(Joint *Joint) {
	for (int i = 0; i < Joints.size(); i++) {
		if (Joint == Joints[i]) {
			delete Joints[i];
			Joints.erase(Joints.begin() + i);
		}
	}
}


// Removes a spring from the environment.
void Environment::removeSpring(Spring *spring) {
	for (int i = 0; i < springs.size(); i++) {
		if (spring == springs[i]) {
			delete springs[i];
			springs.erase(springs.begin() + i);
		}
	}
}


// Updates all Joints and springs in the environment.
void Environment::update() {
	for (int i = 0; i < Joints.size(); i++) {
		Joint *Joint = Joints[i];
		if (allowAccelerate) {
			Joint->accelerate(acceleration);
		}
		if (allowMove) {
			Joint->move();
		}
		if (allowDrag) {
			Joint->experienceDrag();
		}
		if (allowBounce) {
			bounce(Joint);
		}
		// Allows interaction with other Joints.
		for (int x = i + 1; x < Joints.size(); x++) {
			Joint *otherJohnt = Joints[x];
			if (allowCollide) {
				Joint->checkCollide(otherJohnt);
			}
			if (allowAttract) {
				Joint->attract(otherJohnt);
			}
			if (allowCombine) {
				Joint->combine(otherJohnt);
			}
		}
	}
	for (int i = 0; i < springs.size(); i++) {
		Spring *spring = springs[i];
		spring->update();
	}
}
