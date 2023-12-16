#include "Setting.h"

Setting::Setting() : IScreen()
{
	loadWidgets();
}

Setting::Setting(sf::RenderWindow *window) : IScreen(window)
{
	loadWidgets();
}
void Setting::Update(sf::RenderWindow *window, bool HasExitGame)
{
	BackGround background = BackGround::getinstance();
	while (window->isOpen())
	{
		if (StateManager::getInstance().getState() != AppState::SETTINGS)
			break;
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
			gui.handleEvent(event);
			if (StateManager::getInstance().getState() != AppState::SETTINGS)
				return;

			window->clear();
			background.DrawBackGround(window);
			gui.draw();
			window->draw(SettingText);
			window->draw(VolumeText);
			window->draw(DifficultyText);

			window->display();
		}
		if (HasExitGame)
			break;
	}
}

void Setting::loadWidgets()
{
	tgui::Theme::Ptr theme = tgui::Theme::create({"theme/kenney.txt"});
	//  volume here==========================================
	volume = tgui::Slider::create();
	volume->setMinimum(0);
	volume->setMaximum(100);
	volume->setStep(1);
	volume->setValue(50);
	volume->setSize(600, 40);
	volume->setPosition(tgui::Layout2d(500, 300));

	volume->onValueChange([](float value)
						  { SoundManager::getInstance().ChangeBackGroundMusicVolume(value);
							  SoundManager::getInstance().ChangeSoundEffectVolum(value); });
	//================================================================================================
	difficulty = tgui::RadioButtonGroup::create();
	// dificulty here
	easyRadioButton = tgui::RadioButton::create();
	easyRadioButton->setText("Easy");
	easyRadioButton->setPosition(500, 400);
	easyRadioButton->setSize(150, 30);
	easyRadioButton->setTextSize(20);
	easyRadioButton->getRenderer()->setTextColor(tgui::Color::White);
	easyRadioButton->getRenderer()->setTextColorHover(tgui::Color::Red);
	easyRadioButton->getRenderer()->setTextColorChecked(tgui::Color::Red);
	difficulty->add(easyRadioButton);

	hardRadioButton = tgui::RadioButton::create();
	hardRadioButton->setText("Hard");
	hardRadioButton->setPosition(500, 440);
	hardRadioButton->setSize(150, 30);
	hardRadioButton->setTextSize(20);
	hardRadioButton->getRenderer()->setTextColor(tgui::Color::White);
	hardRadioButton->getRenderer()->setTextColorHover(tgui::Color::Red);
	hardRadioButton->getRenderer()->setTextColorChecked(tgui::Color::Red);
	difficulty->add(hardRadioButton);

	veryHardRadioButton = tgui::RadioButton::create();
	veryHardRadioButton->setText("Very Hard");
	veryHardRadioButton->setPosition(500, 480);
	veryHardRadioButton->setSize(150, 30);
	veryHardRadioButton->setTextSize(20);
	veryHardRadioButton->getRenderer()->setTextColor(tgui::Color::White);
	veryHardRadioButton->getRenderer()->setTextColorHover(tgui::Color::Red);
	veryHardRadioButton->getRenderer()->setTextColorChecked(tgui::Color::Red);
	difficulty->add(veryHardRadioButton);

	easyRadioButton->setChecked(true);
	easyRadioButton->onCheck([]
							 {
        Game::Speed = 0.25;
        std::cout << "Selected difficulty: Easy " << std::endl; });

	hardRadioButton->onCheck([]
							 {
         Game::Speed = 0.15;
        std::cout << "Selected difficulty: Hard" << std::endl; });

	veryHardRadioButton->onCheck([]
								 {
         Game::Speed = 0.1;
        std::cout << "Selected difficulty: Very Hard" << std::endl; });
	//================================================================================================
	BackButton = tgui::Button::create();
	BackButton->setPosition(30, 30);
	BackButton->setSize(100, 100);
	BackButton->setText("Back");
	BackButton->setRenderer(theme->getRenderer("Button"));
	BackButton->getRenderer()->setTextSize(25);
	BackButton->getRenderer()->setTextColorDownHover(tgui::Color::Red);
	BackButton->onPress([](const tgui::String &text)
						{
		StateManager::getInstance().setState(AppState::MAIN_MENU);
		std::cout << "Change to Main Menu" << std::endl; });
	//================================================================================================
	// Add RadioButtons to the GUI
	widgets->add(easyRadioButton);
	widgets->add(veryHardRadioButton);
	widgets->add(hardRadioButton);
	widgets->add(volume);
	widgets->add(difficulty);
	widgets->add(BackButton);
	widgets->setVisible(true);
	gui.add(widgets);

	if (!font.loadFromFile("Font/GameFont.ttf"))
	{
		std ::cout << "Failed to load Font";
	}

	SettingText.setFont(font);
	SettingText.setString("SETTING GAME");
	SettingText.setPosition(300, 100);
	SettingText.setCharacterSize(80);
	SettingText.setFillColor(sf::Color::White);

	VolumeText.setFont(font);
	VolumeText.setString("Volume: ");
	VolumeText.setPosition(250, 300);
	VolumeText.setCharacterSize(30);
	VolumeText.setFillColor(sf::Color::White);

	DifficultyText.setFont(font);
	DifficultyText.setString("Difficulty: ");
	DifficultyText.setPosition(250, 400);
	DifficultyText.setCharacterSize(30);
	DifficultyText.setFillColor(sf::Color::White);
	//================================================================================================
}