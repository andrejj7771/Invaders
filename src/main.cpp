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
	
	LevelPtr level = std::make_shared<Level>("test_level_1");
	level->create_player(sf::Vector2f(375, 0));
	
	level->add_enemy(sf::Vector2f(625, 0));
	level->add_enemy(sf::Vector2f(375, 0));
	level->add_enemy(sf::Vector2f(125, 0));
	
	level_manager->add_level(level);
	
	level = std::make_shared<Level>("test_level_2");
	level->create_player(sf::Vector2f(375, 0));
	
	level->add_enemy(sf::Vector2f(625, 0));
	level->add_enemy(sf::Vector2f(500, 0));
	level->add_enemy(sf::Vector2f(375, 0));
	level->add_enemy(sf::Vector2f(250, 0));
	level->add_enemy(sf::Vector2f(125, 0));
	
	level->add_enemy(sf::Vector2f(500, 100));
	level->add_enemy(sf::Vector2f(375, 100));
	level->add_enemy(sf::Vector2f(250, 100));
	
	level_manager->add_level(level);
	
	while(window.isOpen()) {
		level_manager->update();
		if (level_manager->is_end() == false) {
			scene.update();
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
