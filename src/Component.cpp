#include "Component.h"

Component::Component(Object * target,
					 const std::string & name,
					 component_t type) :
	m_target(target),
	m_name(name)
{
	m_type = type;
}

Component::~Component() {
	m_target = nullptr;
}
