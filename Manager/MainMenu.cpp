#include "MainMenu.h"

MainMenu::MainMenu() : IScreen()
{
}
MainMenu::MainMenu(sf::RenderWindow *window) : IScreen(window)
{
    loadWidgets();
}
MainMenu::MainMenu(sf::RenderWindow *window, SoundManager *&sound) : IScreen(window)
{
    sf::Font *font = new sf::Font();
    sf::Texture *tex = new sf::Texture();
    font->loadFromFile(fontPath);
    this->sound = sound;
    loadWidgets();
}
void MainMenu::loadWidgets()
{
    tgui::Theme::Ptr theme = tgui::Theme::create({"theme/kenney.txt"});

    tgui::Button::Ptr button1 = tgui::Button::create("PLAY");
    button1->setPosition(dictPos.x, dictPos.y);
    button1->setSize(dictSize.x, dictSize.y);
    button1->setRenderer(theme->getRenderer("Button"));
    button1->setWidgetName("PLAY");
    button1->onClick(&IScreen::setState, this, AppState::IN_GAME);

    tgui::Button::Ptr button2 = tgui::Button::create("SETTINGS");
    button2->setSize(favSize.x, favSize.y);
    button2->setPosition(favPos.x, favPos.y);
    button2->setRenderer(theme->getRenderer("Button"));
    button2->setWidgetName("SETTINGS");
    button2->onClick(&IScreen::setState, this, AppState::SETTINGS);

    tgui::Button::Ptr button3 = tgui::Button::create("HighScore");
    button3->setSize(quizSize.x, quizSize.y);
    button3->setPosition(quizPos.x, quizPos.y);
    button3->setRenderer(theme->getRenderer("Button"));
    button3->setWidgetName("HighScore");

    tgui::Button::Ptr button4 = tgui::Button::create("Exit");
    button4->setSize(aboutSize.x, aboutSize.y);
    button4->setPosition(aboutPos.x, aboutPos.y);
    button4->setRenderer(theme->getRenderer("Button"));
    button4->setWidgetName("Exit");
    button4->onClick(&MainMenu::handleExit, this);

    widgets->add(button1);
    widgets->add(button2);
    widgets->add(button3);
    widgets->add(button4);

    widgets->setVisible(true);
    gui.add(widgets);
}

tgui::Group::Ptr MainMenu::getWidgets()
{
    return widgets;
}

std::vector<Button> MainMenu::getButton()
{
    return button;
}

void MainMenu::handleExit()
{
    std::cout << "Handle Exit" << std::endl;
    CloseGame = true;
}

void MainMenu::Update(sf::RenderWindow *window, bool HasExitGame)
{
    widgets->setVisible(true);
    SoundManager::getInstance().setMusicState(MusicState::PLAY);
    BackGround background = BackGround::getinstance();
    while (window->isOpen())
    {
        if (StateManager::getInstance().getState() != AppState::MAIN_MENU)
        {
            SoundManager::getInstance().setMusicState(MusicState::STOP);
            break;
        }
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (CloseGame)
                window->close();
            if (event.type == sf::Event::Closed)
                window->close();
            window->clear();
            background.DrawBackGround(window);
            background.DrawLogo(window);
            Draw(window);
            gui.handleEvent(event);
        }
    }
}