#include <iostream>

#include "Scene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"

#include "GUIObjects/Label.h"
#include "GUIObjects/Button.h"

#include "Components/AnimationComponent.h"

#include "Level.h"
#include "LevelManager.h"

#include "Events.h"

int main() {
	MouseEvent & mouse_event = MouseEvent::instance();
	Scene & scene = Scene::instance();
	
	ComponentFactory::register_component<AnimationManager>(component_t::animation);
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	LevelManagerPtr level_manager = std::make_shared<LevelManager>();
	level_manager->load_levels_from_files("../data/levels");
	
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
			
			mouse_event.update(window, event);
		}
		
		scene.draw(window);
	}
	
	level_manager->destroy();
	scene.destroy();
	
	return 0;
}
