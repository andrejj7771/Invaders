#ifndef ENEMY_H
#define ENEMY_H

#include "Object.h"

class Enemy : public Object {
	
	sf::Vector2f m_target_pos;
	sf::Vector2f m_offset;
	
	bool m_direction;							// true - left / false - right
	
public:
	
	Enemy(const sf::Vector2f & pos);
	~Enemy() override = default;
	
protected:
	
	void on_collision(obj_t type) override;
	void on_draw(sf::RenderWindow & render) override;
	void on_update(float time) override;
	
};

#endif //ENEMY_H
