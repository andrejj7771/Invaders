#include "GameObjects/Enemy.h"

namespace Game {
	
	Enemy::Enemy(Scene & scene,
				 const sf::Vector2f & pos) :
		GameObject(gObj_t::enemy, scene, pos),
		m_target_pos(pos),
		m_offset(sf::Vector2f(-100, 50))
	{
		m_direction = true;
		set_size(sf::Vector2f(33, 24));
	}
	
	void Enemy::on_collision(gObj_t type) {
		if (type == gObj_t::bullet) {
			destroy();
		}
	}
	
	void Enemy::on_draw(sf::RenderWindow & render) {
		render.draw(shape());
	}
	
	void Enemy::on_update(float time) {
		sf::Vector2f pos = get_position();
		
		if ((pos.x <= m_target_pos.x + m_offset.x && m_direction == true) ||
				(pos.x >= m_target_pos.x + m_offset.x && m_direction == false))
		{
			m_direction = !m_direction;
			m_offset.x *= (-1);
			pos.y += m_offset.y;
		} else {
			pos.x += time * (m_direction == true ? -0.1f : 0.1f);
		}
		
		set_position(pos);
	}
	
}
