#include "Setting.h"

Setting::Setting() : IScreen()
{

}

Setting::Setting(sf::RenderWindow* window) : IScreen(window)
{
	loadWidgets();
}

void Setting::Update(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		if (StateManager::getInstance().getState() != AppState::SETTINGS) break;
		sf::Event event;
		while (window->pollEvent(event))
		{
			window->clear();
			Draw(window);
			gui.handleEvent(event);

		}
	}
}

void Setting::loadWidgets()
{
	tgui::Theme::Ptr theme = tgui::Theme::create({ "kenney.txt" });
	volume = tgui::Slider::create();
	volume->setMinimum(100);
	volume->setMaximum(200);
	volume->setStep(5);
	volume->setValue(135);
	volume->setRenderer(theme->getRenderer("Slider"));

	volume->onValueChange([](float value) {
		std::cerr << "Slider value was changed to " << value << "\n";
		});

	difficulty = tgui::SpinControl::create();
	difficulty->setMinimum(10);
	difficulty->setMaximum(20);
	difficulty->setStep(1);
	difficulty->setValue(15);
	difficulty->setDecimalPlaces(1); // Display "15.0" instead of "15"
	difficulty->setPosition(tgui::Layout2d(100, 200));
	difficulty->setRenderer(theme->getRenderer("SpinControl"));
	difficulty->onValueChange([](float value) {
		std::cerr << "SpinControl value was changed to " << value << "\n";
		});

	widgets->add(volume);
	widgets->add(difficulty);
	widgets->setVisible(true);
	gui.add(widgets);

}