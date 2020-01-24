#include "Object.h"

Object::Object(obj_t type) {
	m_type = type;
	m_visible = true;
	m_need_destroy = false;
}
