#include "Application.h"
#include "MainWindow.h"
#include <string>

// TODO? Не знаю, как при разработке для Android,
// но обычно очень желательно использовать precompiled headers


// Disable the warnings for deprecated functions (strtok and stricmp)
#pragma warning(disable:4996)

CApplication::CApplication(HINSTANCE hInstance)
  : m_hInstance(hInstance), m_bFullScreen(false)
{
}

CApplication::~CApplication()
{
}

void CApplication::ParseCmdLine(LPSTR lpCmdLine)
{
	LPSTR lpArgument = strtok(lpCmdLine," ");
	while (lpArgument)
	{
		if (stricmp(lpArgument,"-fullscreen") == 0)
			m_bFullScreen = true;
		lpArgument = strtok(NULL," ");
	}
}

void CApplication::Run()
{
	// Create the main window first
	CMainWindow mainWindow(800,600,m_bFullScreen);

	MSG Message;
	Message.message = (UINT)~WM_QUIT;

	// Нет, я считаю, это кривая конструкция, когда движок содержит функцию
	// Update c параметром int, который ещё и результат GetTickCount()
	// (хотя бы потому, что на самом деле GetTickCount возвращает время 
	// с точностью 10 мс).
	// Мне гораздо больше нравится следующая конструкция

	LARGE_INTEGER timerFreq, prevUpdateTime;

	QueryPerformanceFrequency(&timerFreq);
	QueryPerformanceCounter(&prevUpdateTime);
	// Loop until a WM_QUIT message is received
	while (Message.message != WM_QUIT)
	{
		LARGE_INTEGER frameStartTime, curTime;

		QueryPerformanceCounter(&frameStartTime);
		while (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			// If a message was waiting in the message queue, process it
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		QueryPerformanceCounter(&curTime);

		mainWindow.Update(double(curTime.QuadPart - prevUpdateTime.QuadPart) /
			double(timerFreq.QuadPart));
		prevUpdateTime = curTime;
		// Draw the main window
		mainWindow.Draw();
		QueryPerformanceCounter(&curTime);

		int sleepTime = int((1.0 / c_maxFrameRate - 
			double(curTime.QuadPart - frameStartTime.QuadPart) / double(timerFreq.QuadPart)) * 1000);

		if (sleepTime > 0)
			Sleep(sleepTime);
	}
}