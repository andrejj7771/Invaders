#include <iostream>

#include "Scene.h"
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	ScenePtr scene = std::make_shared<Scene>();
	scene->add_object(std::make_shared<Player>());
	
	while(window.isOpen()) {
		
		scene->update();
		
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		scene->draw(window);
	}
	
	scene->destroy();
	scene = nullptr;
	
	return 0;
}
