#include "Manager/Program.h"

tgui::Gui Program::gui;

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	Program* program = new Program();
	program->Run();
	delete program;
	return 0;
}

 