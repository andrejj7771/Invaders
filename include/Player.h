#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object {
	
	ObjectPtr bullet;
	
public:
	
	Player();
	~Player() override = default;
	
	void on_draw(sf::RenderWindow & window) override;
	void on_destroy() override;
	void on_collision(ObjectPtr & obj) override;
	void on_update() override;
	
};

#endif //PLAYER_H
