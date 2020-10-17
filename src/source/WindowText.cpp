#include <utility>

#include "WindowText.h"

WindowText::WindowText(const std::string& fontFilePath, const std::string& textContents,
        sf::Vector2f textPosition, unsigned int fontSize) {
    m_font.loadFromFile(fontFilePath);

    m_text.setFont(this->m_font);
    m_text.setString(textContents);
    m_text.setCharacterSize(fontSize);
    m_text.setFillColor(sf::Color::White);
    const auto& textBounds = m_text.getLocalBounds();
    m_text.setOrigin(sf::Vector2f(textBounds.width / 2, textBounds.height / 2));
    m_text.setPosition(textPosition);
}

WindowText::WindowText(const WindowText& other): m_font(other.m_font), m_text(other.m_text) {
    this->m_text.setFont(this->m_font);
}

WindowText::WindowText(WindowText&& other): m_font(std::move(other.m_font)), m_text(std::move(other.m_text)) {
    this->m_text.setFont(this->m_font);
}

WindowText& WindowText::operator=(const WindowText& other) {
    if (this == &other) {
        return *this;
    }

    this->m_text = other.m_text;
    this->m_font = other.m_font;

    this->m_text.setFont(this->m_font);
    return *this;
}

WindowText& WindowText::operator=(WindowText&& other) {
    if (this == &other) {
        return *this;
    }

    this->m_font = std::move(other.m_font);
    this->m_text = std::move(other.m_text);

    this->m_text.setFont(this->m_font);
    return *this;
}

const sf::Text& WindowText::getText() const noexcept {
    return this->m_text;
}