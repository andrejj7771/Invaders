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
	
	///
	/// \brief m_owner - an instance of the component owner
	///
	Object * m_owner;
	
	///
	/// \brief m_name - the component's name
	///
	std::string m_name;
	
	///
	/// \brief m_type - the component's type
	///
	component_t m_type;
	
	///
	/// \brief m_need_destroy - the boolean flag means
	///  that component will be destroyed or won't be
	///
	bool m_need_destroy;
	
public:
	
	Component(Object * target,
			  const std::string & name,
			  component_t type);
	virtual ~Component();
	
	///
	/// \brief get_name - getter of the component name
	/// \return string value of the component name
	///
	inline const std::string get_name() const {
		return m_name;
	}
	
	///
	/// \brief get_owner - getter of the component owner
	/// \return the owner instance
	///
	inline Object * get_owner() const {
		return m_owner;
	}
	
	///
	/// \brief get_type - getter of the component type
	/// \return enum value of the component type
	///
	inline component_t get_type() const {
		return m_type;
	}
	
	///
	/// \brief update - component updater, invokes every frame
	/// \param time - elapsed time from last frame
	///
	inline void update(float time) {
		assert(m_owner != nullptr);
		on_update(time);
	}
	
	///
	/// \brief destroy - component destroyer
	///
	inline void destroy() {
		if (m_need_destroy == true) {
			return;
		}
		
		m_need_destroy = true;
		on_destroy();
	}
	
protected:
	
	///
	/// \brief on_update - updater of the concrete component
	/// \param time - elapsed time from last frame
	///
	virtual void on_update(float time) = 0;
	
	///
	/// \brief on_destroy - destroyer of the concrete component
	///
	virtual void on_destroy() = 0;
	
};

#endif //COMPONENT_H
