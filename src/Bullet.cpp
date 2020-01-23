#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f & pos) :
    Object(obj_t::bullet)
{
	set_size(sf::Vector2f(8, 15));
	set_position(pos);
	set_fill_color(sf::Color::Red);
}

void Bullet::on_draw(sf::RenderWindow & render) {
	render.draw(m_shape);
}

void Bullet::on_collision(ObjectPtr & obj) {
	if (obj->get_type() == obj_t::enemy) {
		obj->destroy();
		destroy();
	}
}

void Bullet::on_update() {
	if (is_visible() == false) {
		return;
	}
	
	if (is_destroyed() == true) {
		return;
	}
	
	const sf::Vector2f & pos = get_position();
	
	if (pos.y < 0) {
		destroy();
		return;
	}
	
	const sf::Vector2f new_pos(pos.x, pos.y - 0.15f);
	set_position(new_pos);
}
