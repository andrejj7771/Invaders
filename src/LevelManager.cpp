#include "LevelManager.h"

LevelManager::LevelManager() :
	m_current_level(nullptr)
{
	m_need_update = false;
	m_need_destroy = false;
}
