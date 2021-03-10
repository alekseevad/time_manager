#include "App.hpp"

int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	App app{};
	return app.run();
}
