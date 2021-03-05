#pragma once
#include <Windows.h>



class Window
{
public:
	Window();

	//Initialize the window
	bool init();
	bool broadcast();

	//Release the window
	bool release();
	bool isRun();

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();


	~Window();
protected:
	HWND hwnd;
	bool isRunning;
};

