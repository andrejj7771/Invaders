#include <iostream>

#include "Scene.h"
#include "Player.h"
#include "Enemy.h"

#include "AnimationComponent.h"

#include "Level.h"
#include "LevelManager.h"

int main() {
	ComponentFactory::register_component<AnimationManager>(component_t::animation);
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Invaders");
	
	Scene & scene = Scene::instance();
	
//	LevelManagerPtr level_manager = std::make_shared<LevelManager>();
//	level_manager->load_levels_from_files("../data/levels");
	
	sf::Clock clock;
	
	sf::Image img;
	if (img.loadFromFile("/home/nag/Pictures/54.png") == false) {
		return -1;
	}
	
	unsigned int x = 83;
	unsigned int y = 14;
	unsigned int w = 11;
	unsigned int h = 8;
	
	sf::Texture texture;
	texture.create(w, h);
	
	texture.loadFromImage(img, sf::IntRect(static_cast<int>(x),
										   static_cast<int>(y),
										   static_cast<int>(w),
										   static_cast<int>(h)));
	
	ObjectPtr e = std::make_shared<Enemy>(sf::Vector2f(100, 0));
	auto anim_manager = std::static_pointer_cast<AnimationManager>(e->add_component(component_t::animation));
	
	FramePtr frame_1 = std::make_shared<Frame>(img, sf::IntRect(83, 14, 11, 8));
	FramePtr frame_2 = std::make_shared<Frame>(img, sf::IntRect(99, 14, 11, 8));
	
	AnimationPtr anim = std::make_shared<Animation>("idle");
	anim->append_frame(frame_1);
	anim->append_frame(frame_2);
	anim->loop(true);
	anim->set_delay(500);
	
	anim_manager->append_animation(anim);
	anim_manager->set_current_animation("idle");
	anim->play();
	
	scene.add_object(e);
	
	while(window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		
		time /= 800;
		
//		level_manager->update();
//		if (level_manager->is_end() == false) {
			scene.update(time);
//		}
		
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		scene.draw(window);
	}
	
//	level_manager->destroy();
	scene.destroy();
	
	return 0;
}
