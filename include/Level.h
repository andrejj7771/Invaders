#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Enemy.h"
#include "Scene.h"

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
			m_is_won = true;
			return;
		}
		
		if (m_enemies.size() == 0) {
			// congratulations
			m_is_failed = true;
			return;
		}
	}
	
	inline bool is_won() const {
		return m_is_won;
	}
	
	inline bool is_failed() const {
		return m_is_failed;
	}
	
	inline void create_player(const sf::Vector2f & pos) {
		if (m_player != nullptr) {
			return;
		}
		
		m_player = std::make_shared<Player>(pos);
		Scene::instance().add_object(m_player);
	}
	
	inline void add_enemy(const sf::Vector2f & pos) {
		ObjectPtr enemy = std::make_shared<Enemy>(pos);
		m_enemies.push_back(enemy);
		Scene::instance().add_object(m_player);
	}
	
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
	
	inline bool load_from_file(const std::string & path) {
		assert(path.empty() == false);
		
		return false;
	}
	
	inline const std::string & get_level_name() const {
		return m_level_name;
	}
};


#endif //LEVEL_H
