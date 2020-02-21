#include "Components/Component.h"

Component::Component(Object * target,
		  const std::string & name,
		  component_t type) :
	m_owner(target),
	m_name(name)
{
	m_type = type;
	m_need_destroy = false;
}

Component::~Component() {
	m_owner = nullptr;
}
