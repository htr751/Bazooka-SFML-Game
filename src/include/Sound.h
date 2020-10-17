#include <string>

#include <SFML/Audio.hpp>

#include "class_utils.hpp"

class Sound {
public:
    Sound(const std::string& soundFilePath);

    DEFAULT_MOVE_OPERATIONS(Sound);
    DISALLOW_COPY_OPERATIONS(Sound);

    void playSound();
    ~Sound() = default;
private:
    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;
};