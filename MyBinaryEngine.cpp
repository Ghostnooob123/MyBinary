#include "MyBinaryEngine.h"

//Constructor & Destructor
MyBinaryEngine::MyBinaryEngine()
{
	//Initialize member variables
	this->initVariables();
	//Initialize the window
	this->initWindow();
	//Initialize the font
	this->initFont();
	//Initialize the user input panel
	this->initUserPanel();
	//Initialize the user text
	this->initUserText();
	//Initialize the user output panel
	this->initOutputPanel();
	//Initialize the output user text
	this->initOutputText();
	//Initialize the options panel
	this->initOptionsPanel();
	//Initialize the UI elements
	this->initUIelements();

}
MyBinaryEngine::~MyBinaryEngine()
{
	//Destructor implementation if needed

}

//Accessors
const bool MyBinaryEngine::isAppRunning() const
{
	/*
	  @return const bool
	  - Check if the application is still running.
	*/
	return this->window->isOpen();
}

//Public Engine functions
void MyBinaryEngine::update()
{
	/*
	  @return void
	  - Poll events.
	  - Update mouse position.
	*/
	this->pollEvents();
	this->updateMousePos();

	this->updateBinaryCode();

}
void MyBinaryEngine::render()
{
	/*
	  @return void
	  - Clear old frames.
	  - Display frame in the window.
	*/

	//Clear the window
	this->window->clear(sf::Color::White);

	this->renderBinaryCode();

	this->renderUIelements();

	//Display the updated frame
	this->window->display();
}

//Private Engine functions
void MyBinaryEngine::pollEvents()
{
	while (this->window->pollEvent(this->eventAction))
	{
		switch (this->eventAction.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				this->window->close();
			}
			break;
		case sf::Event::TextEntered:
			if (this->userRequest)
			{
				if (this->eventAction.text.unicode < 128)
				{
					if (this->eventAction.text.unicode == '\b' && !this->userInputString.empty())
					{
						//Handle backspace (remove last character)
						this->userInputString.pop_back();
						this->binaryCode_Storage.clear();
					}
					else if (this->eventAction.text.unicode == '\r')
					{
						// Enter key pressed
						//Clear the input string for new input when Enter is pressed
						std::string tempStr;
						tempStr = this->binaryCode_Storage.back().getString();
						if (tempStr.back() == ' ')
						{
							tempStr.pop_back();
						}

						std::istringstream r(tempStr);
						char c;
						size_t power{ tempStr.size() - 1 };
						unsigned long long num{ 0 };
						while (r >> c)
						{
							if (c != '0')
							{
								num += static_cast<unsigned long long>(c - '0') * (pow(2, power));
							}
							--power;
						}

						this->outputText.setString(std::to_string(num));
						this->outputText.setPosition(this->outputPanel.getPosition().x + 5.0f, this->outputPanel.getPosition().y + 5.0f);

						this->userOutputRequest = true;
						this->userRequest = false;
						this->binaryCode_Storage.clear();
					}
					else
					{
						//Check if the char is backspace
						if (this->eventAction.text.unicode != '0' && this->eventAction.text.unicode != '1')
						{
							continue;
						}
						if (this->eventAction.text.unicode == '\b')
						{
							continue;
						}
						if (this->userInputString.length() >= this->maxChars)
						{
							continue;
						}
						//Append the entered character to the input string
						this->userInputString += static_cast<char>(this->eventAction.text.unicode);
						this->binaryCode_Storage.clear();
					}
					//Update the text in the GUI
					sf::Text userInputText = this->userText;
					userInputText.setString(this->userInputString);
					this->binaryCode_Storage.push_back(userInputText);
				}
			}
			break;
		}
	}
}
void MyBinaryEngine::updateMousePos()
{
	/*
	  @return void

	  - Update mouse postitions:
	  - Mouse position relative to window.
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void MyBinaryEngine::updateBinaryCode()
{
	if (this->userPanel.getGlobalBounds().contains(this->mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->userRequest = true;
		this->userOutputRequest = false;
		this->userInputString.clear();
		this->outputText.setString("");
		this->binaryCode_Storage.clear();
	}

	if (!this->userPanel.getGlobalBounds().contains(this->mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->userRequest = false;
	}
}
void MyBinaryEngine::renderBinaryCode()
{
	this->window->draw(this->userPanel);

	this->window->draw(this->outputPanel);
	this->window->draw(this->outputText);

	this->window->draw(this->optionsPanel);

	for (auto& part : this->binaryCode_Storage)
	{
		part.setPosition(sf::Vector2f(this->userPanel.getPosition().x + 5.0f, this->userPanel.getPosition().y + 5.0f));
		this->window->draw(part);
	}
}

void MyBinaryEngine::renderUIelements()
{
	this->window->draw(this->DescriptionUI);
	this->window->draw(this->UserInputUI);
	this->window->draw(this->UserOutputUI);
}

//Init Engine functions
void MyBinaryEngine::initVariables()
{
	/*
	  @return void
	  - Initialize the variables/members.
	*/

	this->userInputString = "";
	this->maxChars = 30;
	this->userRequest = false;

	this->letters = " abcdefghijklmnopqrstuvwxyz";
}
void MyBinaryEngine::initWindow()
{
	/*
	  @return void
	  - Initialize the render window.
	*/
	this->videoMode.height = 200;
	this->videoMode.width = 500;

	this->window = std::make_unique<sf::RenderWindow> (sf::VideoMode(this->videoMode.width, this->videoMode.height), "MyBinary", sf::Style::Titlebar | sf::Style::Close);
	this->window->setPosition(sf::Vector2i(700, 400));
	this->window->setFramerateLimit(165);

	//Centers of the screen
	this->centerX = this->window->getSize().x / 2.0f;
	this->centerY = this->window->getSize().y / 2.0f;
}
void MyBinaryEngine::initFont()
{
	/*
	  @return void
	  - Initialize the font.
	*/

	if (!this->binaryFont.loadFromFile("Source/Font/BinaryFont.ttf"))
	{
		std::cerr << "[ERROR] can't load BinaryFont.ttf\n";
	}

	if (!this->UIfont.loadFromFile("Source/Font/BinaryFont_Bold.otf"))
	{
		std::cerr << "[ERROR] can't load BinaryFont_Bold.ttf\n";
	}
}

void MyBinaryEngine::initUserPanel()
{
	/*
	  @return void
	  - Initialize the input user panel.
	*/

	this->userPanel.setPosition(this->centerX - 150.0f, this->centerY - 30.0f);
	this->userPanel.setSize(sf::Vector2f(370.0f, 25.0f));
	this->userPanel.setOutlineColor(sf::Color::Black);
	this->userPanel.setOutlineThickness(1.0f);
}
void MyBinaryEngine::initUserText()
{
	/*
	  @return void
	  - Initialize the user input text.
	*/

	//userInputText by default
	this->userText.setFont(this->binaryFont); // Set the font you want to use
	this->userText.setCharacterSize(16); // Set the font size
	this->userText.setFillColor(sf::Color::Black); // Set the text color
	this->userText.setString("NONE");
}

void MyBinaryEngine::initOutputPanel()
{
	/*
	  @return void
	  - Initialize the output panel.
	*/

	this->outputPanel.setPosition(this->centerX - 150.0f, this->centerY + 15.0f);
	this->outputPanel.setSize(sf::Vector2f(150.0f, 25.0f));
	this->outputPanel.setOutlineColor(sf::Color::Black);
	this->outputPanel.setOutlineThickness(1.0f);
}
void MyBinaryEngine::initOutputText()
{
	/*
	  @return void
	  - Initialize the output user text.
	*/

	//userInputText by default
	this->outputText.setFont(this->binaryFont); // Set the font you want to use
	this->outputText.setCharacterSize(16); // Set the font size
	this->outputText.setFillColor(sf::Color::Black); // Set the text color
	this->outputText.setString("NONE");
	this->outputText.setPosition(sf::Vector2f(this->centerX, this->centerY + 100000.0f));
}

void MyBinaryEngine::initOptionsPanel()
{
	/*
	  @return void
	  - Initialize the options panel.
	*/

	this->optionsPanel.setPosition(this->centerX - 250.0f, this->centerY + 55.0f);
	this->optionsPanel.setFillColor(sf::Color(238, 238, 238));
	this->optionsPanel.setSize(sf::Vector2f(500.0f, 70.0f));
	this->optionsPanel.setOutlineColor(sf::Color::Black);
}

void MyBinaryEngine::initUIelements()
{
	/*
	  @return void
	  - Initialize the UI elements.
	*/

	//Description UI
	this->DescriptionUI.setFont(this->UIfont);
	this->DescriptionUI.setCharacterSize(13);
	this->DescriptionUI.setFillColor(sf::Color::Black);
	this->DescriptionUI.setString("Type the binary code or paste it,\nand the software will convert it to decimal for you.");
	this->DescriptionUI.setPosition(sf::Vector2f(this->centerX - 154.0f, this->centerY - 85.0f));

	//User input UI
	this->UserInputUI.setFont(this->UIfont);
	this->UserInputUI.setCharacterSize(13);
	this->UserInputUI.setFillColor(sf::Color::Black);
	this->UserInputUI.setString("Binary Code:");
	this->UserInputUI.setPosition(sf::Vector2f(this->centerX - 245.0f, this->centerY - 25.0f));

	//User output UI
	this->UserOutputUI.setFont(this->UIfont);
	this->UserOutputUI.setCharacterSize(13);
	this->UserOutputUI.setFillColor(sf::Color::Black);
	this->UserOutputUI.setString("To Decimal:");
	this->UserOutputUI.setPosition(sf::Vector2f(this->centerX - 243.0f, this->centerY + 20.0f));
}
