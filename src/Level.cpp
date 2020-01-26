#include "Level.h"
#include "Scene.h"

Level::Level(const std::string & level_name) :
	m_player(nullptr),
	m_level_name(level_name)
{
	m_need_destroy = false;
	m_is_won = false;
	m_is_failed = false;
	m_is_loaded = false;
}

void Level::create_player(const sf::Vector2f & pos) {
	if (m_player != nullptr) {
		return;
	}
	
	m_player = std::make_shared<Player>(pos);
}

void Level::add_enemy(const sf::Vector2f & pos) {
	ObjectPtr enemy = std::make_shared<Enemy>(pos);
	m_enemies.push_back(enemy);
}

void Level::load_level() {
	if (m_is_loaded) {
		printf("%s -> level \"%s\" is already loaded\n",
			   __FUNCTION__,
			   m_level_name.data());
		return;
	}
	
	Scene & scene = Scene::instance();
	scene.add_object(m_player);
	
	for (const ObjectPtr & enemy : m_enemies) {
		scene.add_object(enemy);
	}
	
	m_is_loaded = true;
}

void Level::load_out_level() {
	if (m_is_loaded == false) {
		return;
	}
	
	Scene & scene = Scene::instance();
	scene.rem_object(m_player);
	
	for (const ObjectPtr & enemy : m_enemies) {
		scene.rem_object(enemy);
	}
	
	m_is_loaded = false;
}

