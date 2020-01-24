#include "Level.h"

Level::Level(const std::string & level_name) :
	m_player(nullptr),
	m_level_name(level_name)
{
	m_need_destroy = false;
	m_is_won = false;
	m_is_failed = false;
}

