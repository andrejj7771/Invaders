#include <iostream>

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	Scene & scene = Scene::instance();
	scene.add_object(std::make_shared<Player>());
	
	ObjectPtr enemy = std::make_shared<Enemy>(sf::Vector2f(375, 0));
	
	scene.add_object(enemy);
	
	while(window.isOpen()) {
		scene.update();
		
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		scene.draw(window);
	}
	
	scene.destroy();
	
	return 0;
}
