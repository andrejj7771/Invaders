#include "Level.h"
#include "Scene.h"

Level::Level(const std::string & level_name) :
	m_player(nullptr),
	m_level_name(level_name)
{
	m_need_destroy = false;
	m_is_won = false;
	m_is_failed = false;
	m_is_disable = true;
}

void Level::create_player(const sf::Vector2f & pos) {
	if (m_player != nullptr) {
		return;
	}
	
	m_player = std::make_shared<Player>(pos);
	m_player->set_visible(!m_is_disable);
	Scene::instance().add_object(m_player);
}

void Level::add_enemy(const sf::Vector2f & pos) {
	ObjectPtr enemy = std::make_shared<Enemy>(pos);
	enemy->set_visible(!m_is_disable);
	m_enemies.push_back(enemy);
	Scene::instance().add_object(enemy);
}

