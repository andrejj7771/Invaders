#include "Component.h"

Component::Component(Object * target,
		  const std::string & name,
		  component_t type) :
	m_target(target),
	m_name(name)
{
	m_type = type;
	m_need_destroy = false;
}

Component::Component(const ObjectPtr & target,
					 const std::string & name,
					 component_t type) :
	m_target(target.get()),
	m_name(name)
{
	m_type = type;
	m_need_destroy = false;
}

Component::~Component() {
	m_target = nullptr;
}
