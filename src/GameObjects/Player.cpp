#include "GameObjects/Player.h"
#include "GameObjects/Bullet.h"

#include "Scene.h"

namespace Game {
	
	Player::Player(Scene & scene,
				   const sf::Vector2f & pos) :
	    GameObject (gObj_t::player, scene, pos)
	{
		set_size(sf::Vector2f(50, 50));
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
	
	void Player::on_collision(gObj_t type) {
		if (type == gObj_t::enemy) {
			printf("Game Over!!!\n");
			destroy();
		}
	}
	
	void Player::on_update(float time) {
		if (bullet != nullptr) {
			bullet->update(time);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			const sf::Vector2f & pos = get_position();
			
			if (pos.x <= 0) {
				return;
			}
			
			set_position(sf::Vector2f(pos.x - 0.5f * time, pos.y));
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			const sf::Vector2f & pos = get_position();
			
			if (pos.x >= 750) {
				return;
			}
			
			set_position(sf::Vector2f(pos.x + 0.5f * time, pos.y));
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			const sf::Vector2f & pos = get_position();
			const sf::Vector2f new_pos(pos.x + 21, pos.y - 25);
			
			if (bullet == nullptr || bullet->is_destroyed() == true) {
				bullet = std::make_shared<Bullet>(m_scene, new_pos);
				m_scene.append_object(bullet);
				return;
			}
			
			if (bullet->is_destroyed() == true) {
				bullet->set_position(new_pos);
			}
		}
	}
	
}
