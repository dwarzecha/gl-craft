#include "Application/Application.hpp"

int main()
{
	Application* app = new Application("GL-Craft");
	app->RunLoop();

	delete app;

	return 0;
}
