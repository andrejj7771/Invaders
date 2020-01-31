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
	
	float m_delay;
	float m_current_time;
	
	dir_type m_direction;
	
public:
	
	Animation(const std::string & name,
			  float delay = 250);
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
	
	inline const sf::Texture & get_current_frame() const {
		return m_current_frame->get_texture();
	}
	
	void append_frame(const FramePtr & frame);
	void remove_frame(size_t index);
	
	void play();
	void stop();
	void update(float time);
	
private:
	
	void next();
	void prev();
	
};

typedef std::shared_ptr<Animation> AnimationPtr;

class AnimationManager : public Component {
	
	std::vector<AnimationPtr> m_animations;
	AnimationPtr m_current_animation;
	
public:
	
	AnimationManager(Object * object);
	AnimationManager(const ObjectPtr & object);
	~AnimationManager() override;
	
	inline void append_animation(const AnimationPtr & anim) {
		assert(anim != nullptr);
		
		auto a_iterator = std::find(m_animations.begin(),
									m_animations.end(),
									anim);
		
		if (a_iterator != m_animations.end()) {
			printf("%s -> the component already contains this animation",
				   __FUNCTION__);
			
			return;
		}
		
		m_animations.push_back(anim);
	}
	
	inline void remove_animation(const AnimationPtr & anim) {
		assert(anim != nullptr);
		
		auto a_iterator = std::find(m_animations.begin(),
									m_animations.end(),
									anim);
		
		if (a_iterator == m_animations.end()) {
			return;
		}
		
		m_animations.erase(a_iterator);
		*a_iterator = nullptr;
	}
	
	inline void remove_animation(size_t index) {
		assert(index < m_animations.size());
		
		auto a_iterator = m_animations.begin() + static_cast<unsigned>(index);
		m_animations.erase(a_iterator);
		*a_iterator = nullptr;
	}
	
	inline size_t get_num_animations() const {
		return m_animations.size();
	}
	
	inline AnimationPtr get_animation(const std::string & name) {
		assert(name.empty() == false);
		
		auto predicate = [name](const AnimationPtr & anim)
		{
			return anim->get_name() == name;
		};
		
		auto a_iterator = std::find_if(m_animations.begin(), m_animations.end(), predicate);
		if (a_iterator == m_animations.end()) {
			return nullptr;
		}
		
		return *a_iterator;
	}
	
	inline const AnimationPtr & get_animation(size_t index) {
		assert(index < m_animations.size());
		
		auto a_iterator = m_animations.begin() + static_cast<unsigned>(index);
		return *a_iterator;
	}
	
	inline void set_current_animation(size_t index) {
		assert(index < m_animations.size());
		
		m_current_animation = m_animations.at(index);
	}
	
	inline void set_current_animation(const std::string & name) {
		const AnimationPtr & animation = get_animation(name);
		
		if (animation != nullptr) {
			m_current_animation = animation;
		}
	}
	
	inline std::vector<std::string> get_anim_list() const {
		std::vector<std::string> names;
		
		for (auto anim : m_animations) {
			names.push_back(anim->get_name());
		}
		
		return names;
	}
	
protected:
	
	void on_update(float time) override;
	void on_destroy() override;
	
};

#endif //ANIMATION_COMPONENT_H
