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

	void renderUIelements();

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
	sf::RectangleShape optionsPanel;
	sf::Texture logo;
	sf::Sprite logoSprite;
	sf::Image icon;

	//Events
	sf::Event eventAction;

	//User input panel
	sf::RectangleShape userPanel;
	std::string userInputString;
	sf::Text userText;

	//Output panel
	sf::RectangleShape outputPanel;
	sf::Text outputText;

	//Buttons
	sf::RectangleShape ConvertButton;
	sf::Text Convert_UI;
	sf::RectangleShape ResetButton;
	sf::Text Reset_UI;

	//Font
	sf::Font binaryFont;
	sf::Font UIfont;

	//UI
	sf::Text DescriptionUI;
	sf::Text UserInputUI;
	sf::Text UserOutputUI;

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

	void initOptionsPanel();
	void initButtons();

	void initUIelements();
	void initMyBinaryLogo();
};
#endif // !MY_BINARY_ENGINE