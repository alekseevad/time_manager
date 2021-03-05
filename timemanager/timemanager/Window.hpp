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

	//edit window
	void OnSize(HWND hwnd, UINT flag, int width, int height);

	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();


	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

