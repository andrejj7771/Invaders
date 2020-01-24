#include "Scene.h"

Scene::Scene() {
	m_need_destroy = false;
}

Scene & Scene::instance() {
	static Scene _instance;
	return _instance;
}
