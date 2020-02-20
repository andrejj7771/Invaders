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
	
	///
	/// \brief m_frame_texture - frame texture variable
	///
	sf::Texture m_frame_texture;
	
public:
	
	///
	/// \brief Frame - constructor of the frame object
	/// \param texture - frame texture
	///
	Frame(const sf::Texture & texture);
	
	///
	/// \brief Frame - constructor of the frame object
	/// \param image - the source image from which the texture will be cut
	/// \param tex_rect - the cutout area
	///
	Frame(const sf::Image & image,
		  const sf::IntRect & tex_rect);
	
	~Frame() = default;
	
	///
	/// \brief set_texture - set a new texture to frame
	/// \param texture - frame texture
	///
	void set_texture(const sf::Texture & texture);
	
	///
	/// \brief set_texture - set a new texture by image and cutout area
	/// \param image - the course image
	/// \param tex_rect - the cutout area
	///
	void set_texture(const sf::Image & image,
					 const sf::IntRect & tex_rect);
	
	///
	/// \brief get_texture - getter of the frame texture
	/// \return texture value
	///
	inline const sf::Texture & get_texture() const {
		return m_frame_texture;
	}
	
};

typedef std::shared_ptr<Frame> FramePtr;

class Animation {
	
	///
	/// \brief m_name - the name of the animation
	///
	std::string m_name;
	
	///
	/// \brief m_frames - the frames that form the animation
	///
	std::vector<FramePtr> m_frames;
	
	///
	/// \brief m_current_frame - the current frame that rendered now
	///
	FramePtr m_current_frame;
	
	///
	/// \brief m_current_index - the position index of the current frame
	///
	size_t m_current_index;
	
	///
	/// \brief m_is_playing - the flag that switches playing state of the animation
	///
	bool m_is_playing;
	
	///
	/// \brief m_is_reversed - the flag that switches direction of animation playing
	///
	bool m_is_reversed;
	
	///
	/// \brief m_is_looped - the animation can be looped and this flag switches loop state of the animation
	///
	bool m_is_looped;
	
	///
	/// \brief m_is_interruptible - the animation can be interrupted by another animation and this flag switches interruption state of the animation
	///
	bool m_is_interruptible;
	
	///
	/// \brief m_delay - delay between current and next frame
	///
	float m_delay;
	
	///
	/// \brief m_current_time - frame changing timer
	///
	float m_current_time;
	
	///
	/// \brief m_direction - direction of animation player state
	///
	dir_type m_direction;
	
public:
	
	///
	/// \brief Animation - constructor of animation object
	/// \param name - animation name
	/// \param delay - delay between frames
	///
	Animation(const std::string & name,
			  float delay = 250);
	
	///
	/// \brief Animation - copy constructor of animation object
	/// \param animation - source animation that will be copied
	///
	Animation(const Animation & animation);
	
	~Animation();
	
	///
	/// \brief rename - rename animation
	/// \param name - new name
	///
	inline void rename(const std::string & name) {
		m_name = name;
	}
	
	///
	/// \brief get_name - getter on animation name
	/// \return - string value of name variable
	///
	inline const std::string & get_name() const {
		return m_name;
	}
	
	///
	/// \brief get_num_frames - getter of frames number that form the animation
	/// \return size of frames vector
	///
	inline size_t get_num_frames() const {
		return m_frames.size();
	}
	
	///
	/// \brief is_playing - flag which indicates that animation is playing or it's not
	/// \return true if animation is playing, otherwise - false
	///
	inline bool is_playing() const {
		return m_is_playing;
	}
	
	///
	/// \brief reverse - change playing direction of the animation
	/// \param reverse - true is reversed/ false - it's not
	///
	inline void reverse(bool reverse) {
		m_is_reversed = reverse;
	}
	
	///
	/// \brief is_reversed - getter of reversion state of the animation
	/// \return true if animation is reversed, otherwise - false
	///
	inline bool is_reversed() const {
		return m_is_reversed;
	}
	
	///
	/// \brief loop - setter of loop state of the animation
	/// \param looped - true is reversed/ false - it's not
	///
	inline void loop(bool looped) {
		m_is_looped = looped;
	}
	
	///
	/// \brief is_looped getter of loop state of the animation
	/// \return true if animation is looped, otherwise - false
	///
	inline bool is_looped() const {
		return m_is_looped;
	}
	
	///
	/// \brief set_interruptible - setter of interruption state of the animation
	/// \param interruptible true if animation can be interrupted, false it can't
	///
	inline void set_interruptible(bool interruptible) {
		m_is_interruptible = interruptible;
	}
	
	///
	/// \brief is_inerruptible - getter of interruption state of the animation
	/// \return true if animation can be interrupted, false it can't
	///
	inline bool is_inerruptible() const {
		return m_is_interruptible;
	}
	
	///
	/// \brief set_delay - set delay timer to change frames
	/// \param delay - timer value
	///
	inline void set_delay(int delay) {
		m_delay = delay;
	}
	
	///
	/// \brief get_delay - getter of value of delay timer
	/// \return timer value
	///
	inline int get_delay() const {
		return m_delay;
	}
	
	///
	/// \brief change_direction - setter of direction value
	/// \param diretion - dir_type value of direction
	///
	inline void change_direction(dir_type diretion) {
		m_direction = diretion;
	}
	
	///
	/// \brief get_direction - getter of current direction
	/// \return dir_type value of direction
	///
	inline dir_type get_direction() const {
		return m_direction;
	}
	
	///
	/// \brief get_current_frame - getter of current animation frame
	/// \return current frame
	///
	inline const sf::Texture & get_current_frame() const {
		return m_current_frame->get_texture();
	}
	
	///
	/// \brief append_frame - append new animation frame
	/// \param frame - pointer on the frame that will be appended
	///
	void append_frame(const FramePtr & frame);
	
	///
	/// \brief remove_frame - remove animation by index
	/// \param index - index of frame that will be removed
	///
	void remove_frame(size_t index);
	
	///
	/// \brief play - play the animation
	///
	void play();
	
	///
	/// \brief stop - stop animation playing
	///
	void stop();
	
	///
	/// \brief update - aimation updater, changes current frame by time
	/// \param time - elapsed time from last frame
	///
	void update(float time);
	
private:
	
	///
	/// \brief next - set next frame
	///
	void next();
	
	///
	/// \brief prev - set previous frame
	///
	void prev();
	
};

typedef std::shared_ptr<Animation> AnimationPtr;

class AnimationManager : public Component {
	
	///
	/// \brief m_animations - animation list
	///
	std::vector<AnimationPtr> m_animations;
	
	///
	/// \brief m_current_animation - current animation that is playing now
	///
	AnimationPtr m_current_animation;
	
public:
	
	///
	/// \brief AnimationManager - component constructor
	/// \param owner - object instance of component owner
	///
	AnimationManager(Object * owner);
	
	~AnimationManager() override;
	
	///
	/// \brief append_animation - appent new animation to list
	/// \param anim - instance of new animation
	///
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
	
	///
	/// \brief remove_animation - remove animation from list by instance
	/// \param anim - instance of animation that will be removed
	///
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
	
	///
	/// \brief remove_animation - remove animation from list by index
	/// \param index - index of animation that will be removed
	///
	inline void remove_animation(size_t index) {
		assert(index < m_animations.size());
		
		auto a_iterator = m_animations.begin() + static_cast<unsigned>(index);
		m_animations.erase(a_iterator);
		*a_iterator = nullptr;
	}
	
	///
	/// \brief get_num_animations - get number of the animations
	/// \return 
	///
	inline size_t get_num_animations() const {
		return m_animations.size();
	}
	
	///
	/// \brief get_animation - get animation by name
	/// \param name - name of the animation
	/// \return instance of the animation if animation exists, otherwise - nullptr
	///
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
	
	///
	/// \brief get_animation - get animation by index
	/// \param index - index of the animation
	/// \return instance of the animation if it exists, otherwise - false
	///
	inline const AnimationPtr & get_animation(size_t index) {
		assert(index < m_animations.size());
		
		auto a_iterator = m_animations.begin() + static_cast<unsigned>(index);
		return *a_iterator;
	}
	
	///
	/// \brief set_current_animation - set current animation by index
	/// \param index - index of the animation
	///
	inline void set_current_animation(size_t index) {
		assert(index < m_animations.size());
		
		m_current_animation = m_animations.at(index);
	}
	
	///
	/// \brief set_current_animation - set current animation by name
	/// \param name - name of the animation
	///
	inline void set_current_animation(const std::string & name) {
		const AnimationPtr & animation = get_animation(name);
		
		if (animation != nullptr) {
			m_current_animation = animation;
		}
	}
	
	///
	/// \brief get_anim_list - get animation list
	/// \return std::vector of animations
	///
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
