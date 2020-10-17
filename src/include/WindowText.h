#include <string>

#include <SFML/Graphics.hpp>

class WindowText {
public:
    static sf::Text createTextObj(const std::string& fontFilePath, const std::string& textContents,
        sf::Vector2f textPosition);
};