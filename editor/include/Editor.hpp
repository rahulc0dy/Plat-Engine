#include <Engine.hpp>

class Editor {
public:
	Editor();
	~Editor();

	void run();

private:
	sf::RenderWindow m_window;
	sf::View m_view;
	sf::Font m_font;
};