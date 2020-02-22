#include "Object.h"

Object::Object(obj_t type, Scene & scene,
			   const sf::Vector2f & pos) :
	m_scene(scene)
{
	static size_t id = 0;
	m_id = id++;
	
	m_type = type;
	m_visible = true;
	m_need_destroy = false;
	set_position(pos);
}
