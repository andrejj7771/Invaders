#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "Component.h"

#include <vector>

#include <SFML/Graphics.hpp>

enum class dir_type : char {
	forward = 0,
	backward = 1
};

class Frame {
	
	sf::Texture m_frame_texture;
	
public:
	
	Frame(const sf::Texture & texture);
	Frame(const sf::Image & texture,
		  const sf::IntRect & tex_rect);
	~Frame() = default;
	
	void set_texture(const sf::Texture & texture);
	void set_texture(const sf::Image & texture,
					 const sf::IntRect & tex_rect);
	
	inline const sf::Texture & get_texture() const {
		return m_frame_texture;
	}
	
};

typedef std::shared_ptr<Frame> FramePtr;

class Animation {
	
	std::string m_name;
	std::vector<FramePtr> m_frames;
	FramePtr m_current_frame;
	size_t m_current_index;
	
	bool m_is_playing;
	bool m_is_reversed;
	bool m_is_looped;
	bool m_is_interruptible;
	
	int m_delay;
	int m_current_time;
	
	dir_type m_direction;
	
public:
	
	Animation(const std::string & name,
			  int delay = 5);
	Animation(const Animation & animation);
	~Animation();
	
	inline void rename(const std::string & name) {
		m_name = name;
	}
	
	inline const std::string & get_name() const {
		return m_name;
	}
	
	inline size_t get_num_frames() const {
		return m_frames.size();
	}
	
	inline bool is_playing() const {
		return m_is_playing;
	}
	
	inline void reverse(bool reverse) {
		m_is_reversed = reverse;
	}
	
	inline bool is_reversed() const {
		return m_is_reversed;
	}
	
	inline void loop(bool looped) {
		m_is_looped = looped;
	}
	
	inline bool is_looped() const {
		return m_is_looped;
	}
	
	inline void set_interruptible(bool interruptible) {
		m_is_interruptible = interruptible;
	}
	
	inline bool is_inerruptible() const {
		return m_is_interruptible;
	}
	
	inline void set_delay(int delay) {
		m_delay = delay;
	}
	
	inline int get_delay() const {
		return m_delay;
	}
	
	inline void change_direction(dir_type diretion) {
		m_direction = diretion;
	}
	
	inline dir_type get_direction() const {
		return m_direction;
	}
	
	void append_frame(const FramePtr & frame);
	void remove_frame(size_t index);
	
	void play();
	void stop();
	void update();
	
private:
	
	void next();
	void prev();
	
};

class AnimationManager : public Component {
	
	
	
};

#endif //ANIMATION_COMPONENT_H
