#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "../Manager/Screen.h"
#include "../Manager/UserManager.h"
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
	//tgui::Group::Ptr widgets;
	static std::string userName;
	static std::string passWord;
	static int userIndex;
	
	void updateTextSize();
	
	void CreateNewAccount();
public:
	Login();
	Login(sf::RenderWindow* window);
	tgui::Button::Ptr loginButton;
	void Update(sf::RenderWindow* window, bool HasExitGame) override;
	void loadWidgets() override;
	void SignIn();
	bool isValidated();
	
	tgui::Group::Ptr getWidgets();
	static std::string getUserName();
	static std::string getPassWord();
	static int getUserIndex();
};

