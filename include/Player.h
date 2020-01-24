#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
	
	ObjectPtr bullet;
	
public:
	
	Player(const sf::Vector2f & pos = {0, 0});
	~Player() override = default;
	
	void on_draw(sf::RenderWindow & window) override;
	void on_destroy() override;
	void on_collision(obj_t type) override;
	void on_update() override;
	
};

#endif //PLAYER_H
