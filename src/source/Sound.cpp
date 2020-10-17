#include "Sound.h"

Sound::Sound(const std::string& soundFilePath): m_sound(m_soundBuffer) {
    m_soundBuffer.loadFromFile(soundFilePath);
}

void Sound::playSound() {
    this->m_sound.play();
}