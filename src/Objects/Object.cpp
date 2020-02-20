#include "Objects/Object.h"

Object::Object(obj_t type, const sf::Vector2f & pos) {
	m_type = type;
	m_visible = true;
	m_need_destroy = false;
	set_position(pos);
}
