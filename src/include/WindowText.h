#include <string>

#include <SFML/Graphics.hpp>

class WindowText {
public:
    WindowText(const std::string& fontFilePath, const std::string& textContents, sf::Vector2f textPosition, unsigned int fontSize);
    WindowText(const WindowText& other);
    WindowText(WindowText&& other);

    WindowText& operator=(const WindowText& other);
    WindowText& operator=(WindowText&& other);

    const sf::Text& getText() const noexcept;
    ~WindowText() = default;
private:
    sf::Font m_font;
    sf::Text m_text;
};