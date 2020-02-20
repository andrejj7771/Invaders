#ifndef LEVEL_H
#define LEVEL_H

#include "Objects/Player.h"
#include "Objects/Enemy.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <memory>
#include <vector>

#include <fstream>
#include <sstream>

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Level {
	
	std::vector<ObjectPtr> m_enemies;
	ObjectPtr m_player;
	
	bool m_need_destroy;
	bool m_is_won;
	bool m_is_failed;
	bool m_is_loaded;
	
	
	std::string m_level_name;
	
public:
	
	Level(const std::string & level_name = "");
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
	
	inline bool is_loaded() const {
		return m_is_loaded;
	}
	
	void create_player(const sf::Vector2f & pos);
	
	inline const ObjectPtr & get_player() const {
		return m_player;
	}
	
	void add_enemy(const sf::Vector2f & pos);
	
	void load_level();
	
	void load_out_level();
	
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
	
	inline bool load_from_file(const std::string & path) {
		assert(path.empty() == false);
		
		std::ifstream file_stream(path);
		if (file_stream.is_open() == false) {
			printf("%s -> can't open file.\n", __FUNCTION__);
			return false;
		}
		
		std::string line;
		std::getline(file_stream, m_level_name); // first string is always a level name
		
		while (std::getline(file_stream, line)) {
			if (line.empty() == true) {
				continue;
			}
			
			std::string type;
			std::string x;
			std::string y;
			
			std::istringstream iss(line);
			std::getline(iss, type, ' ');
			std::getline(iss, x, ' ');
			std::getline(iss, y, ' ');
			
			char c_type = *type.begin();
			float c_x = std::stof(x);
			float c_y = std::stof(y);
			
			if (c_type == '1') {
				create_player(sf::Vector2f(c_x, c_y));
			} else if(c_type == '2') {
				add_enemy(sf::Vector2f(c_x, c_y));
			} else {
				continue;
			}
		}
		
		file_stream.close();
		return true;
	}
	
	inline const std::string & get_level_name() const {
		return m_level_name;
	}
};


#endif //LEVEL_H
