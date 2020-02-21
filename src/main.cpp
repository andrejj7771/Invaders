#include <iostream>

#include "Scene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"

#include "GUIObjects/Label.h"
#include "GUIObjects/Button.h"

#include "Components/AnimationComponent.h"

#include "Level.h"
#include "LevelManager.h"

void button_click_callback(sf::Mouse::Button) {
	static int counter = 0;
	printf("click %d\n", counter++);
}

int main() {
	ComponentFactory::register_component<AnimationManager>(component_t::animation);
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	Scene & scene = Scene::instance();
	
	LevelManagerPtr level_manager = std::make_shared<LevelManager>();
	level_manager->load_levels_from_files("../data/levels");
	
	sf::Clock clock;
	
	sf::Font font;
	font.loadFromFile("../data/fonts/tnr.ttf");
	
	GUI::LabelPtr label = std::make_shared<GUI::Label>("Label", font, sf::Vector2f(10, 10));
	label->set_text_color(sf::Color::Red);
	label->set_fill_color(sf::Color::Green);
	
	GUI::ButtonPtr button = std::make_shared<GUI::Button>("Button", font, sf::Vector2f(10, 50));
	button->set_text_color(sf::Color::Blue);
	button->set_fill_color(sf::Color::Green);
	
	button->set_mouse_click_callback(std::bind(&::button_click_callback, std::placeholders::_1));
	
	scene.append_object(label);
	scene.append_object(button);
	
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
			
			if (event.type == sf::Event::MouseButtonPressed) {
				printf("pressed\n");
			}
			
			if (event.type == sf::Event::MouseButtonReleased) {
				printf("released\n");
			}
		}
		
		scene.draw(window);
	}
	
	level_manager->destroy();
	scene.destroy();
	
	return 0;
}
