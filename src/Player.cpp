#include "Player.h"
#include "Bullet.h"
#include "Scene.h"

Player::Player() :
    Object (obj_t::player)
{
	set_size(sf::Vector2f(50, 50));
	set_position(sf::Vector2f(375, 525));
	set_fill_color(sf::Color::White);
}

void Player::on_draw(sf::RenderWindow & window) {
	window.draw(shape());
	
	if (bullet != nullptr) {
		bullet->draw(window);
	}
}

void Player::on_destroy() {
	if (bullet != nullptr) {
		bullet->destroy();
	}
}

void Player::on_collision(obj_t type) {
	if (type == obj_t::enemy) {
		printf("Game Over!!!\n");
	}
}

void Player::on_update() {
	if (bullet != nullptr) {
		bullet->update();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		const sf::Vector2f & pos = get_position();
		
		if (pos.x <= 0) {
			return;
		}
		
		set_position(sf::Vector2f(pos.x - 0.1f, pos.y));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		const sf::Vector2f & pos = get_position();
		
		if (pos.x >= 750) {
			return;
		}
		
		set_position(sf::Vector2f(pos.x + 0.1f, pos.y));
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		const sf::Vector2f & pos = get_position();
		const sf::Vector2f new_pos(pos.x + 21, pos.y - 25);
		
		if (bullet == nullptr || bullet->is_destroyed() == true) {
			bullet = std::make_shared<Bullet>(new_pos);
			Scene::instance().add_object(bullet);
			return;
		}
		
		if (bullet->is_destroyed() == true) {
			bullet->set_position(new_pos);
		}
	}
}
