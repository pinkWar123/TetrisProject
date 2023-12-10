#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Screen.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
// This is the class defining the login screen
class Login : public IScreen
{
private:
	tgui::EditBox::Ptr userNameBox;
	tgui::EditBox::Ptr passWordBox;
	tgui::Button::Ptr signUpButton;
	tgui::Group::Ptr widgets;
	static std::string userName;
	static std::string passWord;
	static int userIndex;
	
	void updateTextSize(tgui::BackendGui& gui);
	
	void CreateNewAccount();
public:
	tgui::Button::Ptr loginButton;
	void Draw(sf::RenderWindow* window);
	void Update(sf::RenderWindow* window, sf::Event ev);
	virtual void Execute(sf::RenderWindow* window, sf::Event ev);
	void Load(tgui::Gui& gui);

	void SignIn();
	bool isValidated();
	
	tgui::Group::Ptr getWidgets();
	static std::string getUserName();
	static std::string getPassWord();
	static int getUserIndex();
};

