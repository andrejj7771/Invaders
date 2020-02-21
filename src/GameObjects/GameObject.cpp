#include "GameObjects/GameObject.h"

namespace Game {
	
	GameObject::GameObject(gObj_t obj_type, const sf::Vector2f & pos) :
		Object(obj_t::game_object, pos)
	{
		m_object_type = obj_type;
	}
	
	void GameObject::on_destroy() {}
}
