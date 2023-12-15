#include "Login.h"

using object_t = std::map<std::string, std::string>;
using objects_t = std::vector<object_t>;

Login::Login() : IScreen()
{
}

Login::Login(sf::RenderWindow *window) : IScreen(window)
{
	loadWidgets();
}

void Login::loadWidgets()
{
	updateTextSize();
	tgui::Theme::Ptr theme = tgui::Theme::create({"theme/kenney.txt"});

	userNameBox = tgui::EditBox::create();
	userNameBox->setWidgetName("Username");
	userNameBox->setSize({"60%", "7.5%"});
	userNameBox->setPosition({"20%", "40%"});
	userNameBox->setDefaultText("Username");
	userNameBox->setRenderer(theme->getRenderer("EditBox"));

	passWordBox = tgui::EditBox::copy(userNameBox);
	passWordBox->setWidgetName("Password");
	passWordBox->setPosition({"20%", "52%"});
	passWordBox->setPasswordCharacter('*');
	passWordBox->setDefaultText("Password");
	passWordBox->setRenderer(theme->getRenderer("EditBox"));
	passWordBox->setTextSize(32);

	loginButton = tgui::Button::create("Login");
	loginButton->setWidgetName("Login");
	loginButton->setSize({"25%", "10%"});
	loginButton->setPosition({"50%", "70%"});
	loginButton->onClick(&Login::SignIn, this);
	loginButton->setRenderer(theme->getRenderer("Button"));
	passWordBox->setTextSize(32);

	signUpButton = tgui::Button::create("SignUp");
	signUpButton->setSize({"25%", "10%"});
	signUpButton->setPosition({"25%", "70%"});
	signUpButton->onClick(&Login::CreateNewAccount, this);
	signUpButton->setRenderer(theme->getRenderer("Button"));

	// widgets = tgui::Group::create();
	widgets->add(userNameBox);
	widgets->add(passWordBox);
	widgets->add(loginButton);
	widgets->add(signUpButton);

	widgets->setVisible(true);
	gui.add(widgets);
}

void Login::Update(sf::RenderWindow *window, bool HasExitGame)
{
	BackGround backround = BackGround::getinstance();
	while (window->isOpen())
	{
		if (StateManager::getInstance().getState() == AppState::MAIN_MENU)
			break;
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			window->clear();
			backround.DrawBackGround(window);
			backround.DrawLogo(window);
			Draw(window);
			gui.handleEvent(event);
		}
	}
}

void Login::updateTextSize()
{
	// Update the text size of all widgets in the gui, based on the current window height
	const float windowHeight = gui.getView().getRect().height;
	gui.setTextSize(static_cast<unsigned int>(0.07f * windowHeight)); // 7% of height
}

void Login::CreateNewAccount()
{
	std::string userName = static_cast<std::string>(userNameBox->getText());
	std::string passWord = static_cast<std::string>(passWordBox->getText());

	std::ifstream stream("Login/user.json", std::ios::in);
	json object = json::parse(stream);
	json newObject;
	newObject["Username"] = userName;
	newObject["Password"] = passWord;
	newObject["Favorite"] = json::array();
	object["user"].push_back(newObject);

	std::ofstream os("Login/user.json");

	os << object;
	stream.close();
	os.close();
}

bool Login::isValidated()
{
	std::string userName = static_cast<std::string>(userNameBox->getText());
	std::string passWord = static_cast<std::string>(passWordBox->getText());

	std::ifstream is("Login/user.json");
	json object = json::parse(is);

	for (auto it : object.at("user").items())
	{
		if (it.value().at("Username") == userName && it.value().at("Password") == passWord)
		{
			is.close();
			UserManager::getInstance().setPassword(passWord);
			UserManager::getInstance().setUserName(userName);

			return true;
		}
	}
	is.close();
	return false;
}

void Login::SignIn()
{
	bool isValidated = Login::isValidated();
	if (isValidated)
	{
		StateManager::getInstance().setState(AppState::MAIN_MENU);
		widgets->setVisible(false);
	}
}

tgui::Group::Ptr Login::getWidgets()
{
	return widgets;
}


