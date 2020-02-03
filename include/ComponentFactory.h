#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include <functional>
#include <map>
#include <memory>

#include "Component.h"

class Object;

typedef std::shared_ptr<Component> ComponentPtr;

class ComponentFactory {
	
	static std::map<component_t, std::function<ComponentPtr(Object*)>> m_factory;
	
public:
	
	ComponentFactory() = default;
	~ComponentFactory() = default;
	
	template<typename T>
	static void register_component(component_t type) {
		auto factory_func = [](Object * owner) -> ComponentPtr
		{
			return std::make_shared<T>(owner);
		};
		
		m_factory[type] = factory_func;
	}
	
	static ComponentPtr create(component_t type, Object * owner) {
		auto iterator = m_factory.find(type);
		if (iterator == m_factory.end()) {
			printf("%s -> component unregistered.\n", __FUNCTION__);
			return nullptr;
		}
		
		return iterator->second(owner);
	}
};

#endif //COMPONENT_FACTORY
