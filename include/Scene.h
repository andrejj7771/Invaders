#ifndef SCENE_H
#define SCENE_H

#include "Object.h"

class Scene {
	
	std::vector<ObjectPtr> m_objects;
	
	bool m_need_destroy;
	
private:
	
	Scene();
	
	Scene(Scene & scene) = delete;
	Scene & operator=(const Scene & scene) = delete;
	
public:
	
	static Scene & instance();
	
	~Scene() = default;
	
	inline void update() {
		if (m_objects.size() == 0) {
			return;
		}
		
		for (size_t i = 0; i < m_objects.size(); ++i) {
			m_objects.at(i)->update();
		}
		
		//check collision and remove destroyed objects
		for (size_t i = 0; i < m_objects.size() - 1; ++i) {
			const ObjectPtr & obj_i = m_objects.at(i);
			if (obj_i->is_destroyed() == true) {
				rem_object(i--);
				continue;
			}
			
			if (obj_i->is_visible() == false) {
				continue;
			}
			
			for (size_t j = i + 1; j < m_objects.size(); ++j) {
				const ObjectPtr & obj_j = m_objects.at(j);
				if (obj_j->is_destroyed() == true) {
					rem_object(j--);
					continue;
				}
				
				if (obj_j->is_visible() == false) {
					continue;
				}
				
				obj_i->check_collision(obj_j);
			}
		}
	}
	
	inline void draw(sf::RenderWindow & render) {
		render.clear();
		for (auto object : m_objects) {
			object->draw(render);
		}
		render.display();
	}
	
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		for (ObjectPtr & obj : m_objects) {
			obj->destroy();
		}
		
		m_objects.clear();
		m_need_destroy = true;
	}
	
	inline bool is_destroy() const {
		return m_need_destroy;
	}
	
	inline void add_object(const ObjectPtr & obj) {
		assert(obj != nullptr);
		
		auto obj_iterator = std::find(m_objects.begin(), m_objects.end(), obj);
		if (obj_iterator != m_objects.end()) {
			printf("%s -> object is already on the scene.\n", __FUNCTION__);
			return;
		}
		
		m_objects.push_back(obj);
	}
	
	inline void rem_object(const ObjectPtr & obj) {
		assert(obj != nullptr);
		
		auto obj_iterator = std::find(m_objects.begin(), m_objects.end(), obj);
		assert(obj_iterator == m_objects.end());
		
		m_objects.erase(obj_iterator);
		obj->destroy();
	}
	
	void rem_object(size_t index) {
		assert(index < m_objects.size());
		
		auto obj_iterator = m_objects.begin() + static_cast<long long>(index);
		m_objects.erase(obj_iterator);
		(*obj_iterator)->destroy();
	}
	
	inline size_t get_num_objects() const {
		return m_objects.size();
	}
	
};

#endif //SCENE_H
