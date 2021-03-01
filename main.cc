#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "resource.h"

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK windProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

std::string getCurrentPath()
{
    char buffer[MAX_PATH] = {0};
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\");
    std::string path = std::string(buffer).substr(0, pos + 1) + "*";
    return path;
}

void showFiles(HWND list)
{
    SendMessage(list, LB_RESETCONTENT, 0, 0);
    fileList.clear();

    WIN32_FIND_DATA fileData;

    HANDLE hFind = FindFirstFile(currentPath.c_str(), &fileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cout << "file not found " << std::endl;
    }

    while (FindNextFile(hFind, &fileData) != 0)
    {
        File f(fileData);
        fileList.push_back(f);
        SendMessage(list, LB_ADDSTRING, NULL,(LPARAM) fileData.cFileName);
    }

    FindClose(hFind);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR ncmdLine, int ncmdShow)
{
    std::string class_name = std::to_string(GetCurrentThreadId());

    WNDCLASSEX wndClass = {};
    
    wndClass.cbSize = sizeof(wndClass);
    wndClass.lpfnWndProc = windProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = class_name.c_str();
    wndClass.lpszMenuName = MAKEINTRESOURCE(MY_MAIN_MENU);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassEx(&wndClass);

    HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE | WS_MINIMIZEBOX, wndClass.lpszClassName, "main", WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
                                640, 480, NULL, NULL, hInstance, NULL);
    HWND files = CreateWindowEx(0 , "ListBox", "listbox", WS_CHILD | WS_VISIBLE | LBS_NOTIFY , 0, 0, 300, 400, hwnd, NULL, hInstance, NULL);

    currentPath = getCurrentPath();

    showFiles(files);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;

}