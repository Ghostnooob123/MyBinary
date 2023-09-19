#ifndef MY_BINARY_ENGINE
#define MY_BINARY_ENGINE

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class MyBinaryEngine final
{
public:
	//Constructor & Destructor
	MyBinaryEngine();
	~MyBinaryEngine();

	//Accessors
	const bool isAppRunning() const;

	//Public Engine functions
	void update();
	void render();
private:
	//Private Engine functions
	void pollEvents();
	void updateMousePos();

	void updateBinaryCode();
	void renderBinaryCode();

	//Variables
	float centerX; //Center of the screen by X
	float centerY; //Center of the screen by Y

	size_t maxChars;

	bool userRequest;
	bool userOutputRequest;

	std::string letters;

	//Window
	std::unique_ptr< sf::RenderWindow> window;
	sf::VideoMode videoMode;

	//Events
	sf::Event eventAction;

	//User input panel
	sf::RectangleShape userPanel;
	std::string userInputString;
	sf::Text userText;

	//Output panel
	sf::RectangleShape outputPanel;
	sf::Text outputText;

	//Font
	sf::Font binaryFont;

	//Storage
	std::vector<sf::Text> binaryCode_Storage;

	//Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Init Engine functions
	void initVariables();
	void initWindow();
	void initFont();

	void initUserPanel();
	void initUserText();

	void initOutputPanel();
	void initOutputText();
};
#endif // !MY_BINARY_ENGINE