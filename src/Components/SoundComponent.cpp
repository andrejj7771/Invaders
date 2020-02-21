#include "Components/SoundComponent.h"
#include "Object.h"

SoundComponent::SoundComponent(Object * owner,
							   const SoundPtr & sound,
							   bool target_pos) :
	Component(owner, "SoundComponent", component_t::sound),
	m_sound(sound)
{
	m_use_owner_pos = target_pos;
}

SoundComponent::SoundComponent(Object * owner,
							   const sf::SoundBuffer & buffer,
							   bool target_pos) :
	Component(owner, "SoundComponent", component_t::sound),
	m_sound(std::make_shared<sf::Sound>(buffer))
{
	m_use_owner_pos = target_pos;
}

void SoundComponent::on_update(float) {
	if (m_use_owner_pos == false) {
		return;
	}
	
	const sf::Vector2f & pos = get_owner()->get_position();
	set_position(pos);
}

void SoundComponent::on_destroy() {
	m_sound = nullptr;
}

