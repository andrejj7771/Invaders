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

typedef std::shared_ptr<LevelManager> LevelManagerPtr;

int main() {
	MouseEvent & mouse_event = MouseEvent::instance();
	
	ComponentFactory::register_component<AnimationManager>(component_t::animation);
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	LevelManagerPtr level_manager = std::make_shared<LevelManager>();
	level_manager->load_levels_from_files("../data/levels");
	
	sf::Clock clock;
	
	while(window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		
		time /= 800;
		
		level_manager->update(time);
		
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			mouse_event.update(window, event);
		}
		
		level_manager->draw(window);
	}
	
	level_manager->destroy();
	return 0;
}
