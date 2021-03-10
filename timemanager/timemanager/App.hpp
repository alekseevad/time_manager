#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <time.h>
#include <stdexcept>
#include <string>

#include <Windows.h>

class App
{
	enum class CTL_ID
	{
		CREATE_TASK,
		DELETE_TASK
	};

public:
	explicit App();
	~App();
	
	int run();

private:
	void init_native_window_obj();

	static LRESULT CALLBACK application_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void create_native_controls();

private:
	const std::wstring m_szAppName{ L"Bin-VV" }, m_szClassname{ L"Bin-VV_Window_class_nostyles" };
	HWND m_hWnd{}, m_hWndButton{}, m_hWndEdit{};
	const int m_AppWidth{ 350 }, m_AppHeight{ 250 };

};