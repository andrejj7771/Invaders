#ifndef SCENE_H
#define SCENE_H

#include "GUIObjects/GUIObject.h"
#include "GameObjects/GameObject.h"

class Scene {
	
	std::vector<Game::GameObjectPtr> m_game_objects;
	std::vector<GUI::GUIObjectPtr> m_gui_objects;
	
	bool m_need_destroy;
	
public:
	
	Scene();
	~Scene() = default;
	
	inline void update(float time) {
		update_gui(time);
		update_game_object(time);
	}
	
	inline void draw(sf::RenderWindow & render) {
		render.clear();
		for (auto object : m_game_objects) {
			object->draw(render);
		}
		
		for (auto object : m_gui_objects) {
			object->draw(render);
		}
		
		render.display();
	}
	
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		for (Game::GameObjectPtr & obj : m_game_objects) {
			obj->destroy();
		}
		
		for (GUI::GUIObjectPtr & obj : m_gui_objects) {
			obj->destroy();
		}
		
		m_game_objects.clear();
		m_gui_objects.clear();
		m_need_destroy = true;
	}
	
	inline bool is_destroy() const {
		return m_need_destroy;
	}
	
	inline void append_object(const Game::GameObjectPtr & obj) {
		assert(obj != nullptr);
		
		auto obj_iterator = std::find(m_game_objects.begin(), m_game_objects.end(), obj);
		if (obj_iterator != m_game_objects.end()) {
			printf("%s -> object is already on the scene.\n", __FUNCTION__);
			return;
		}
		
		m_game_objects.push_back(obj);
	}
	
	inline void append_object(const GUI::GUIObjectPtr & obj) {
		assert(obj != nullptr);
		
		auto obj_iterator = std::find(m_gui_objects.begin(), m_gui_objects.end(), obj);
		if (obj_iterator != m_gui_objects.end()) {
			printf("%s -> object is already on the scene.\n", __FUNCTION__);
			return;
		}
		
		m_gui_objects.push_back(obj);
	}
	
	inline void remove_object(const Game::GameObjectPtr & obj) {
		assert(obj != nullptr);
		
		auto obj_iterator = std::find(m_game_objects.begin(), m_game_objects.end(), obj);
		assert(obj_iterator != m_game_objects.end());
		
		m_game_objects.erase(obj_iterator);
		obj->destroy();
	}
	
	inline void remove_object(const GUI::GUIObjectPtr & obj) {
		assert(obj != nullptr);
		
		auto obj_iterator = std::find(m_gui_objects.begin(), m_gui_objects.end(), obj);
		assert(obj_iterator != m_gui_objects.end());
		
		m_gui_objects.erase(obj_iterator);
		obj->destroy();
	}
	
	void remove_object(size_t index, bool game_object = true) {
		long long _index = static_cast<long long>(index);
		
		if (game_object) {
			assert(index < m_game_objects.size());
			
			auto obj_iterator = m_game_objects.begin() + _index;
			m_game_objects.erase(obj_iterator);
			(*obj_iterator)->destroy();
		} else {
			assert(index < m_gui_objects.size());
			
			auto obj_iterator = m_gui_objects.begin() + _index;
			m_gui_objects.erase(obj_iterator);
			(*obj_iterator)->destroy();
		}
	}
	
	inline size_t get_num_objects() const {
		return m_game_objects.size();
	}
	
private:
	
	inline void update_gui(float time) {
		if (m_gui_objects.size() == 0) {
			return;
		}
		
		for (auto it = m_gui_objects.begin(); it != m_gui_objects.end(); ++it) {
			GUI::GUIObjectPtr & obj = *it;
			if (obj->is_destroyed() == true) {
				m_gui_objects.erase(it--);
				continue;
			}
			
			obj->update(time);
		}
	}
	
	inline void update_game_object(float time) {
		if (m_game_objects.size() == 0) {
			return;
		}
		
		for (size_t i = 0; i < m_game_objects.size(); ++i) {
			m_game_objects.at(i)->update(time);
		}
		
		//check collision and remove destroyed objects
		for (size_t i = 0; i < m_game_objects.size(); ++i) {
			const Game::GameObjectPtr & obj_i = m_game_objects.at(i);
			if (obj_i->is_visible() == false) {
				continue;
			}
			
			for (size_t j = 0; j < m_game_objects.size(); ++j) {
				if (i == j) {
					continue;
				}
				
				const Game::GameObjectPtr & obj_j = m_game_objects.at(j);
				if (obj_j->is_visible() == false) {
					continue;
				}
				
				obj_i->check_collision(obj_j);
			}
		}
		
		for (auto it = m_game_objects.begin(); it != m_game_objects.end(); ++it) {
			if ((*it)->is_destroyed() == true) {
				m_game_objects.erase(it--);
			}
		}
	}
	
};

#endif //SCENE_H
