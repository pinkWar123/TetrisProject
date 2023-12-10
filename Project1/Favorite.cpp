#include "Favorite.h"

void Favorite::Load(tgui::Gui& gui)
{
	LoadFavoriteWords();
	widgets = tgui::Group::create();
	tgui::Theme::Ptr theme = tgui::Theme::create({ "kenney.txt" });
	tgui::ListBox::Ptr listBox = tgui::ListBox::create();
	listBox->setAutoScroll(false);
	listBox->setSize({ "70%","60%" });
	listBox->setPosition({ "15%","20%" });
	listBox->setWidgetName("ListBox");
	
	
	listBox->setRenderer(theme->getRenderer("ListBox"));
	listBox->setItemHeight(40);
	listBox->setTextSize(10);
	for (auto it : Favorite::favWords)
	{
		listBox->addItem(it);
	}
	tgui::Button::Ptr button = tgui::Button::create();
	button->setWidgetName("BackButton");
	button->setPosition(backPos.x, backPos.y);
	button->setSize(backSize.x, backSize.y);
	//button->setText("BACK");
	//button->setTextSize
	button->setRenderer(theme->getRenderer("BButton"));
	

	widgets->add(listBox);
	widgets->add(button);
	widgets->setVisible(false);
	

	gui.add(widgets);
}

void Favorite::AddFavoriteWords(std::string word)
{
	favWords.push_back(word);
	std::ifstream is("user.json",std::ios::in);
	json object = json::parse(is);
	std::cout << object.at("user")[Login::getUserIndex()];
	object.at("user")[Login::getUserIndex()]["Favorite"] = favWords;
	
	std::ofstream os("user.json");
	os << object;
	os.close();
	is.close();
	widgets->get<tgui::ListBox>("ListBox")->addItem(word);
}

void Favorite::LoadFavoriteWords()
{
	Favorite::favWords.clear();
	std::ifstream is("user.json");
	json object = json::parse(is);
	std::cout << object << std::endl << std::to_string(Login::getUserIndex());
	favWords = object.at("user")[Login::getUserIndex()]["Favorite"];
	is.close();
}

tgui::Group::Ptr Favorite::getWidgets()
{
	return widgets;
}