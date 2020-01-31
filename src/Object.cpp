#include "Object.h"
#include "AnimationComponent.h"

Object::Object(obj_t type, const sf::Vector2f & pos) {
	m_type = type;
	m_visible = true;
	m_need_destroy = false;
	set_position(pos);
}

ComponentPtr Object::add_component(component_t type) {
	const ComponentPtr & compoent = get_component(type);
	if (compoent != nullptr) {
		return compoent;
	}
	
	ComponentPtr result = nullptr;
	
	switch (type) {
		case component_t::animation:
			result = std::make_shared<AnimationManager>(this);
			break;
		case component_t::sound:
//			return std::make_shared<SoundManager>(this); //TODO: impliment sound manager
			return nullptr;
	}
	
	m_components.push_back(result);
	return result;
}
