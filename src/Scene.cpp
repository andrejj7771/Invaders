#include "Scene.h"

Scene::Scene() :
	m_level_manager(std::make_shared<LevelManager>())
{
	m_need_destroy = false;
}

Scene & Scene::instance() {
	static Scene _instance;
	return _instance;
}
