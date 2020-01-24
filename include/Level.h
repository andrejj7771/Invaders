#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <memory>
#include <vector>

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Level {
	
	std::vector<ObjectPtr> m_enemies;
	ObjectPtr m_player;
	
	bool m_need_destroy;
	bool m_is_won;
	bool m_is_failed;
	
	bool m_is_disable;
	
	std::string m_level_name;
	
public:
	
	Level(const std::string & level_name);
	~Level() = default;
	
	inline void update() {
		if (m_need_destroy == true ||
				m_is_won == true ||
				m_is_failed == true)
		{
			return;
		}
		
		if (m_player->is_destroyed()) {
			// game over
			m_is_failed = true;
			return;
		}
		
		for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it) {
			if ((*it)->is_destroyed()) {
				m_enemies.erase(it--);
			}
		}
		
		if (m_enemies.size() == 0) {
			// congratulations
			m_is_won = true;
			return;
		}
	}
	
	inline bool is_won() const {
		return m_is_won;
	}
	
	inline bool is_failed() const {
		return m_is_failed;
	}
	
	void create_player(const sf::Vector2f & pos);
	
	inline const ObjectPtr & get_player() const {
		return m_player;
	}
	
	void add_enemy(const sf::Vector2f & pos);
	
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		m_need_destroy = true;
		
		for (auto enemy : m_enemies) {
			enemy->destroy();
			enemy = nullptr;
		}
		
		m_enemies.clear();
		m_player->destroy();
		m_player = nullptr;
	}
	
	inline bool is_destroyed() {
		return m_need_destroy;
	}
	
	inline void set_enable(bool value) {
		m_is_disable = !value;
		
		for (auto enemy : m_enemies) {
			enemy->set_visible(value);
		}
		
		m_player->set_visible(value);
	}
	
	inline bool is_enabled() const {
		return m_is_disable;
	}
	
	inline bool load_from_file(const std::string & path) {
		assert(path.empty() == false);
		
		return false;
	}
	
	inline const std::string & get_level_name() const {
		return m_level_name;
	}
};


#endif //LEVEL_H
