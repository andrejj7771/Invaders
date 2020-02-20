#include "ComponentFactory.h"

std::map<component_t, std::function<ComponentPtr(Object*)>> ComponentFactory::m_factory;

ComponentPtr ComponentFactory::create(component_t type, Object * owner) {
	auto it = m_factory.find(type);
	if (it == m_factory.end()) {
		printf("%s -> component not registered.\n", __FUNCTION__);
		return nullptr;
	}
	
	return it->second(owner);
}
