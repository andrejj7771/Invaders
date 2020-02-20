#include "AnimationComponent.h"
#include "Object.h"

#include <algorithm>

Frame::Frame(const sf::Texture & texture) :
	m_frame_texture(texture)
{}

Frame::Frame(const sf::Image & texture,
	  const sf::IntRect & tex_rect)
{
	m_frame_texture.loadFromImage(texture, tex_rect);
}

void Frame::set_texture(const sf::Texture & texture) {
	m_frame_texture = texture;
}

void Frame::set_texture(const sf::Image & texture,
						const sf::IntRect & tex_rect)
{
	m_frame_texture.loadFromImage(texture, tex_rect);
}

Animation::Animation(const std::string & name,
					 float delay) :
	m_name(name),
	m_current_frame(nullptr)
{
	m_current_index = 0;
	
	m_is_playing = false;
	m_is_looped = false;
	m_is_reversed = false;
	m_is_interruptible = false;
	
	m_direction = dir_type::forward;
	
	m_delay = delay;
	m_current_time = 0;
}

Animation::Animation(const Animation & animation) {
	m_name = animation.m_name;
	m_frames = animation.m_frames;
	m_current_frame = *m_frames.begin();
	m_current_index = 0;
	
	m_is_playing = false;
	m_is_looped = animation.m_is_looped;
	m_is_reversed = animation.m_is_reversed;
	m_is_interruptible = animation.m_is_interruptible;
	
	m_direction = animation.m_direction;
	
	m_delay = animation.m_delay;
}

Animation::~Animation() {
	m_is_playing = false;
	
	for (auto & frame : m_frames) {
		frame = nullptr;
	}
	
	m_frames.clear();
	m_current_frame = nullptr;
}

void Animation::append_frame(const FramePtr & frame) {
	assert(frame != nullptr);
	
	auto f_it = std::find(m_frames.begin(), m_frames.end(), frame);
	if (f_it != m_frames.end()) {
		printf("%s -> animation(\"%s\") already contains this frame.\n",
			   __FUNCTION__, m_name.data());
		return;
	}
	
	if (m_current_frame == nullptr) {
		m_current_frame = frame;
	}
	
	m_frames.push_back(frame);
}

void Animation::remove_frame(size_t index) {
	assert(index < get_num_frames());
	
	const FramePtr & frame = m_frames.at(index);
	if (m_current_frame == frame) {
		size_t frames_num = get_num_frames();
		if (frames_num == 1) {
			stop();
			m_current_frame = nullptr;
		} else if (index == frames_num - 1) {
			m_current_frame = m_frames.at(0);
			m_current_index = 0;
		} else {
			m_current_frame = m_frames.at(index + 1);
			m_current_index = index + 1;
		}
	}
	
	m_frames.erase(m_frames.begin() + long(index));
}

void Animation::play() {
	if (m_is_playing == true) {
		return;
	}
	
	m_is_playing = true;
}

void Animation::stop() {
	if (m_is_playing == false) {
		return;
	}
	
	m_is_playing = false;
}

void Animation::update(float time) {
	if (m_is_playing == false) {
		return;
	}
	
	if (m_current_time >= m_delay) {
		if (m_is_reversed == false) {
			++m_current_index;
		} else {
			--m_current_index;
		}
		
		m_current_time = 0;
	}
	
	m_current_time += time;
	
	if (m_is_reversed == false) {
		if (m_current_index >= get_num_frames()) {
			m_current_index = 0;
		}
	} else {
		if (m_current_index == SIZE_MAX) { // m_current_index == -1
			m_current_index = get_num_frames() - 1;
		}
	}
	
	if (m_is_looped == false) {
		stop();
	}
	
	m_current_frame = m_frames.at(m_current_index);
}

void Animation::next() {
	++m_current_index;
		if (m_current_index >= m_frames.size()) {
			m_current_index = 0;
			if (!is_looped()) {
				stop();
			}
		}
		
		if (!is_playing()) {
			return;
		}
		
		m_current_frame = m_frames.at(m_current_index);
	
}

void Animation::prev() {
	--m_current_index;
		if (m_current_index == SIZE_MAX) {
			m_current_index = m_frames.size() - 1;
			if (!is_looped()) {
				stop();
			}
		}
		
		if (!is_playing()) {
			return;
		}
		
		m_current_frame = m_frames.at(m_current_index);
	
}

AnimationManager::AnimationManager(Object * object) :
	Component(object, "AnimationManager", component_t::animation),
	m_current_animation(nullptr)
{}

AnimationManager::~AnimationManager() {
	on_destroy();
}

void AnimationManager::on_update(float time) {
	if (m_current_animation == nullptr) {
		return;
	}
	
	m_current_animation->update(time);
	const auto & texture = m_current_animation->get_current_frame();
	get_owner()->set_texture(texture);
}

void AnimationManager::on_destroy() {
	m_current_animation = nullptr;
	for (auto & a : m_animations) {
		a = nullptr;
	}
	
	m_animations.clear();
}

