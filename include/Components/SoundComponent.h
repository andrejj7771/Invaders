#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include "Component.h"

#include <SFML/Audio.hpp>

#include <vector>

class Object;

typedef std::shared_ptr<sf::Sound> SoundPtr;

class SoundComponent : public Component {
	
	///
	/// \brief m_sound - sound source
	///
	SoundPtr m_sound;
	
	///
	/// \brief m_use_owner_pos - use position of owner object
	///
	bool m_use_owner_pos;
	
public:
	
	///
	/// \brief SoundComponent - SoundComponent object constructor
	/// \param owner - instance of component's owner
	/// \param sound - instance of sound source
	/// \param owner_pos - use position of owner object
	///
	SoundComponent(Object * owner,
				   const SoundPtr & sound,
				   bool owner_pos = true);
	
	///
	/// \brief SoundComponent - SoundComponent object constructor
	/// \param owner - instance of component's owner
	/// \param sound - instance of source buffer
	/// \param owner_pos - use position of owner object
	///
	SoundComponent(Object * owner,
				   const sf::SoundBuffer & sound,
				   bool owner_pos = true);
	
	~SoundComponent() override = default;
	
	///
	/// \brief get_sound - getter of sound source object
	/// \return instance of sound object
	///
	inline const SoundPtr & get_sound() const {
		return m_sound;
	}
	
	///
	/// \brief set_volume - set volume of source
	/// \param volume - float value
	///
	inline void set_volume(float volume) {
		m_sound->setVolume(volume);
	}
	
	///
	/// \brief get_colume - 
	/// \return 
	///
	inline float get_colume() const {
		return m_sound->getVolume();
	}
	
	inline void set_position(const sf::Vector2f & pos) {
		if (m_use_owner_pos == true) {
			return;
		}
		
		m_sound->setPosition(pos.x, pos.y, 0);
	}
	
	inline sf::Vector2f get_position() const {
		sf::Vector3f pos = m_sound->getPosition();
		return sf::Vector2f(pos.x, pos.y);
	}
	
	inline void play() {
		m_sound->play();
	}
	
	inline void stop() {
		m_sound->stop();
	}
	
	inline void set_looped(bool looped) {
		m_sound->setLoop(looped);
	}
	
	inline bool is_looped() const {
		return m_sound->getLoop();
	}
	
	inline void set_using_target_pos(bool value) {
		m_use_owner_pos = value;
	}
	
	inline bool is_target_pos_using() const {
		return m_use_owner_pos;
	}
	
protected:
	
	void on_update(float time) override;
	void on_destroy() override;
	
};

#endif //SOUNDCOMPONENT_H
