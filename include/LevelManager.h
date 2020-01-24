#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Level.h"

class Level;
typedef std::shared_ptr<Level> LevelPtr;

class LevelManager {
	
	std::vector<LevelPtr> m_level_list;
	LevelPtr m_current_level;
	
	bool m_need_update;
	bool m_need_destroy;
	
public:
	
	LevelManager();
	~LevelManager() = default;
	
	inline void update() {
		if (m_need_destroy == true ||
				m_need_update == false)
		{
			return;
		}
		
		if (m_current_level->is_won() == true) {
			load_next_level();
		}
		
		if (m_current_level->is_failed() == true) {
			// game over
			destroy();
			return;
		}
		
		m_current_level->update();
	}
	
	inline const LevelPtr & get_current_level() const {
		return m_current_level;
	}
	
	inline void load_next_level() {
		auto iterator = std::find(m_level_list.begin(), m_level_list.end(), m_current_level);
		if (iterator == m_level_list.end() - 1) {
			// congratulations
			m_need_update = false;
		} else {
			m_current_level = *(iterator + 1);
		}
	}
	
	inline std::vector<std::string> get_name_list() {
		std::vector<std::string> names;
		
		for (const LevelPtr & lvl : m_level_list) {
			names.push_back(lvl->get_level_name());
		}
		
		return names;
	}
	
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		m_need_destroy = true;
		
		for (auto lvl : m_level_list) {
			lvl->destroy();
			lvl = nullptr;
		}
		
		m_level_list.clear();
	}
	
};


#endif //LEVEL_MANAGER
