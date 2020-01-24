#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f & pos) :
    Object(obj_t::bullet, pos)
{
	set_size(sf::Vector2f(8, 15));
	set_fill_color(sf::Color::Red);
}

void Bullet::on_draw(sf::RenderWindow & render) {
	render.draw(shape());
}

void Bullet::on_collision(obj_t type) {
	if (type == obj_t::enemy) {
		destroy();
	}
}

void Bullet::on_update(float time) {
	const sf::Vector2f & pos = get_position();
	
	if (pos.y < 0) {
		destroy();
		return;
	}
	
	const sf::Vector2f new_pos(pos.x, pos.y - 0.4f * time);
	set_position(new_pos);
}
