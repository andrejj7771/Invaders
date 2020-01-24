#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f & pos) :
	Object(obj_t::enemy),
	m_target_pos(pos),
	m_offset(sf::Vector2f(-100, 50))
{
	m_direction = true;
	set_position(pos);
	set_size(sf::Vector2f(50, 50));
	set_fill_color(sf::Color::Blue);
}

void Enemy::on_collision(obj_t type) {
	if (type == obj_t::bullet) {
		destroy();
	}
}

void Enemy::on_draw(sf::RenderWindow & render) {
	render.draw(shape());
}

void Enemy::on_update() {
	sf::Vector2f pos = get_position();
	
	if ((pos.x <= m_target_pos.x + m_offset.x && m_direction == true) ||
			(pos.x >= m_target_pos.x + m_offset.x && m_direction == false))
	{
		m_direction = !m_direction;
		m_offset.x *= (-1);
		pos.y += m_offset.y;
	} else {
		pos.x += m_direction == true ? -0.05f : 0.05f;
	}
	
	set_position(pos);
}
