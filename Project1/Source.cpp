#include "Program.h"

std::vector<std::string> Favorite::favWords;
std::string Login::passWord;
std::string Login::userName;
tgui::Group::Ptr Favorite::widgets;
int Login::userIndex;
tgui::Gui Program::gui;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	Program* program = new Program();
	program->Run();
	return 0;
}

