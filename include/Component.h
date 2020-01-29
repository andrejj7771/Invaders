#ifndef COMPONENT_H
#define COMPONENT_H

#include <cassert>
#include <memory>
#include <string>

class Object;

enum class component_t : char {
	animation = 0,
	sound = 1
};

class Component {
	
	Object * m_target;
	std::string m_name;
	
	component_t m_type;
	
public:
	
	Component(Object * target,
			  const std::string & name,
			  component_t type);
	virtual ~Component();
	
	inline const std::string get_name() const {
		return m_name;
	}
	
	inline Object * getTarget() const {
		return m_target;
	}
	
	inline void update() {
		assert(m_target != nullptr);
		on_update();
	}
	
protected:
	
	virtual void on_update() = 0;
	
};

#endif //COMPONENT_H
