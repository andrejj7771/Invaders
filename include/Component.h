#ifndef COMPONENT_H
#define COMPONENT_H

#include <cassert>
#include <memory>
#include <string>

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

enum class component_t : char {
	animation = 0,
	sound = 1
};

class Component {
	
	Object * m_target;
	std::string m_name;
	
	component_t m_type;
	
	bool m_need_destroy;
	
public:
	
	Component(Object * target,
			  const std::string & name,
			  component_t type);
	Component(const ObjectPtr & target,
			  const std::string & name,
			  component_t type);
	virtual ~Component();
	
	inline const std::string get_name() const {
		return m_name;
	}
	
	inline Object * getTarget() const {
		return m_target;
	}
	
	inline component_t get_type() const {
		return m_type;
	}
	
	inline Object * get_target() const {
		return m_target;
	}
	
	inline void update(float time) {
		assert(m_target != nullptr);
		on_update(time);
	}
	
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		m_need_destroy = true;
		on_destroy();
	}
	
	
protected:
	
	virtual void on_update(float time) = 0;
	virtual void on_destroy() = 0;
	
};

#endif //COMPONENT_H
