// Demonstrates Joint physics in a 'regular' environment with gravity.
#include <SFML/Graphics.hpp>
#include "../include/cpparticles.hpp"

int main() {
	
	// Set up the environment.
	Environment *env = new Environment(800, 600);
	Joint *selectedJoint = nullptr;
	
	// Create the main window.
	sf::RenderWindow window(sf::VideoMode(env->getWidth(), env->getHeight()), "Collision Simulation");
	window.setFramerateLimit(60);
	
	// Add random Joints to the environment.
	for (int i = 0; i < 10; i++) {
		env->addJoint();
	}
	
	while (window.isOpen()) {
		
		// Process events.
		sf::Event event;
		while (window.pollEvent(event)) {
			
			// Close window: Exit.
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			// Escape: Exit.
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
			
			// Hold left mouse button: Select and drag a Joint.
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					float mouseX = event.mouseButton.x;
					float mouseY = event.mouseButton.y;
					selectedJoint = env->getJoint(mouseX, mouseY);
				}
			}
			
			// Release left mouse button: Release a Joint.
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					selectedJoint = nullptr;
				}
			}
		}
		
		// Clear the window.
		window.clear();
		
		// Update the environment.
		env->update();
		
		// Move the selected Joint to the cursor's position.
		if (selectedJoint) {
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;
			selectedJoint->moveTo(mouseX, mouseY);
		}
		
		// Draw Joints.
		for (int i = 0; i < env->getJoints().size(); i++) {
			Joint *Joint = env->getJoints()[i];
			sf::CircleShape circle(Joint->getSize());
			circle.setOrigin(Joint->getSize(), Joint->getSize());
			circle.setPosition(Joint->getX(), Joint->getY());
			window.draw(circle);
		}
		
		// Update the window.
		window.display();
	}
	
	return EXIT_SUCCESS;
}
