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
	
	inline void add_level(const LevelPtr & level) {
		assert(level != nullptr);
		
		if (m_need_update == false) {
			m_need_update = true;
		}
		
		auto iter = std::find(m_level_list.begin(), m_level_list.end(), level);
		if (iter != m_level_list.end()) {
			printf("%s -> this level is already in the list\n", __FUNCTION__);
			return;
		}
		
		m_level_list.push_back(level);
	}
	
	inline void update() {
		if (m_need_destroy == true ||
				m_need_update == false)
		{
			return;
		}
		
		for (auto it = m_level_list.begin(); it != m_level_list.end(); ++it) {
			if ((*it)->is_destroyed() == true) {
				if (*it == m_current_level) {
					m_current_level = nullptr;
				}
				
				m_level_list.erase(it--);
			}
		}
		
		if (m_current_level == nullptr) {
			m_current_level = *m_level_list.begin();
			m_current_level->set_enable(true);
		}
		
		m_current_level->update();
		
		if (m_current_level->is_won() == true) {
			load_next_level();
		}
		
		if (m_current_level->is_failed() == true) {
			// game over
			destroy();
			return;
		}
	}
	
	inline const LevelPtr & get_current_level() const {
		return m_current_level;
	}
	
	inline void load_next_level() {
		auto iterator = std::find(m_level_list.begin(), m_level_list.end(), m_current_level);
		if (iterator == m_level_list.end() - 1) {
			// congratulations
			m_need_update = false;
			printf("You win!!!\n");
		} else {
			m_current_level->set_enable(false);
			m_current_level = *(iterator + 1);
			m_current_level->set_enable(true);
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
		m_need_update = false;
		
		for (auto lvl : m_level_list) {
			lvl->destroy();
			lvl = nullptr;
		}
		
		m_level_list.clear();
	}
	
	inline bool is_end() const {
		return !m_need_update;
	}
	
};


#endif //LEVEL_MANAGER
