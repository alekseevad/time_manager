#include "App.hpp"

App::App()
{
	using std::wstring;
	using std::string;
	try
	{
		this->init_native_window_obj();
		this->create_native_controls();
	}
	catch(const std::exception& e)
	{
		const string except_data = e.what();

		MessageBox(nullptr, wstring(begin(except_data), end(except_data)).c_str(),
				L"Îøèáêà", MB_ICONERROR | ERROR);
		ExitProcess(EXIT_FAILURE);
	}
}

int App::run()
{
	MSG _msg{};
	ShowWindow(this->m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(this->m_hWnd);
	while (GetMessage(&_msg, nullptr, 0, 0))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
	return static_cast<int>(_msg.wParam);
}

LRESULT application_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	App* pApp;
	if (uMsg == WM_NCCREATE)
	{
		pApp = static_cast<App*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp)))
		{
			if (GetLastError() != 0)
				return false;
		}
	}
	else
	{
		pApp = reinterpret_cast<App*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (pApp)
	{
		pApp->m_hWnd = hWnd;
		return pApp->window_proc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void App::init_native_window_obj()
{
	WNDCLASSEX __wc{ sizeof(WNDCLASSEX) };
	_wc.cbClsExtra = 0;
	_wc.cbWndExtra = 0;
	_wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	_wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	_wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	_wc.hInstance = GetModuleHandle(nullptr);
	_wc.lpfnWndProc = App::application_proc();
	_wc.lpszClassName = this->m_szClassname.c_str();
	_wc.lpszMenuName = nullptr;
	_wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&_wc))
		throw std::runtime_error("Error, cannot register main window class!");

	RECT _windowRC{ 0, 0, this->m_AppWidth, this->m_AppHeight };
	AdjustWindowRect(&_windowRC, WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE, false);

	if (this->m_hWnd = CreateWindowEx(
		0,
		this->m_szClassname.c_str(),
		this->m_szAppName.c_str(),
		WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE,
		(GetSystemMetrics(SM_CXSCREEN) - _windowRC.right) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - _windowRC.right) / 2,
		_windowRC.right, _windowRC.bottom, nullptr, nullptr, nullptr, this
	); !this->m_hWnd)
		throw std::runtime_error("Cannot Create main window!");

}

void App::create_native_controls()
{
	if(this->m_hWndButton = CreateWindowEx(
		0,
		L"BUTTON",
		L"Add record",
		WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		56, 108, 238, 37,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::CREATE_TASK), nullptr, nullptr
	); !this->m_hWndButton)
		throw std::runtime_error("Cannot Create main window!");

	if (this->m_hWndButton = CreateWindowEx(
		0,
		L"Edit",
		L"Delete record",
		WS_CHILD | ES_AUTOHSCROLL | WS_VISIBLE,
		56, 66, 238, 24,
		this->m_hWnd, reinterpret_cast<HMENU>(App::CTL_ID::DELETE_TASK), nullptr, nullptr
	); !this->m_hWndEdit)
		throw std::runtime_error("Cannot Create main window!");

	HFONT hFont = CreateFont(18, 0, 0, 0, FW_REGULAR, 0, 0, 0, DEFAULT_CHARSET, OUT_DEVICE_PRECIS, 
	CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Roboto");
	SendMessage(this->m_hWndButton, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessage(this->m_hWndEdit, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
}
