#include "WindowText.h"

sf::Text WindowText::createTextObj(const std::string& fontFilePath, const std::string& textContents,
        sf::Vector2f textPosition) {
    sf::Font font;
    font.loadFromFile(fontFilePath);

    sf::Text text;
    text.setFont(font);
    text.setString(textContents);
    text.setCharacterSize(84);
    text.setFillColor(sf::Color::Red);

    const auto textBounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textBounds.width / 2, textBounds.height / 2));
    text.setPosition(textPosition);

    return text;
}