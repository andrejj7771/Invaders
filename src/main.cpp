#include <iostream>

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"

#include "Level.h"
#include "LevelManager.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	Scene & scene = Scene::instance();
	
	LevelManagerPtr level_manager = std::make_shared<LevelManager>();
	
	LevelPtr level = std::make_shared<Level>("");
	level->load_from_file("/home/andrey/Invaders/data/levels/level1.lvl");
	level_manager->add_level(level);
	
	level = std::make_shared<Level>("");
	level->load_from_file("/home/andrey/Invaders/data/levels/level2.lvl");
	level_manager->add_level(level);
	
	sf::Clock clock;
	
	while(window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		
		time /= 800;
		
		level_manager->update();
		if (level_manager->is_end() == false) {
			scene.update(time);
		}
		
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		scene.draw(window);
	}
	
	level_manager->destroy();
	scene.destroy();
	
	return 0;
}
