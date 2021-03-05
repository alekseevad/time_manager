

#include "../Header/AppWindow.hpp"



int main()
{
	AppWindow app;
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}


	return 0;
}