#include <iostream>

#include "Scene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"

#include "GUIObjects/Label.h"

#include "Components/AnimationComponent.h"

#include "Level.h"
#include "LevelManager.h"

int main() {
	ComponentFactory::register_component<AnimationManager>(component_t::animation);
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	Scene & scene = Scene::instance();
	
	LevelManagerPtr level_manager = std::make_shared<LevelManager>();
	level_manager->load_levels_from_files("../data/levels");
	
	sf::Clock clock;
	
	sf::Image img;
	if (img.loadFromFile("/home/nag/Pictures/54.png") == false) {
		return -1;
	}
	
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
