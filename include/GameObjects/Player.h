#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

namespace Game {
	
	class Player : public GameObject {
		
		GameObjectPtr bullet;
		
	public:
		
		Player(Scene & scene,
			   const sf::Vector2f & pos = {0, 0});
		~Player() override = default;
		
		void on_draw(sf::RenderWindow & window) override;
		void on_destroy() override;
		void on_collision(gObj_t type) override;
		void on_update(float time) override;
		
	};
	
}

#endif //PLAYER_H
