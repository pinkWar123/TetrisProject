#pragma once
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <map>
#include "Login.h"
#include "SearchBoxConstants.h"


using json = nlohmann::json;

class Favorite
{
private:
	
	static tgui::Group::Ptr widgets;
	
	
public:
	static std::vector<std::string> favWords;
	void Load(tgui::Gui& gui);
	static void AddFavoriteWords(std::string word);
	tgui::Group::Ptr getWidgets();
	static void LoadFavoriteWords();
};