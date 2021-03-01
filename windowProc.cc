#include <Windows.h>
#include <stdio.h>
#include "SearchEngine.h"

LRESULT CALLBACK windProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
switch (msg)
    {
        case WM_DESTROY:
        {
            printf("destroy\n");
            PostQuitMessage(0);
            return 0;
        }
        case WM_COMMAND:
        {
            switch (HIWORD(wParam))
            {
                case LBN_DBLCLK:
                {
                    int pos = SendMessage((HWND) lParam, LB_GETCURSEL, 0, 0);
                    if (pos == 0)
                    {
                        MainEngine.upperDir();
                        showFiles((HWND) lParam);
                    } else {
                        int tempFolder = 1;
                        if (MainEngine.fileList.at(pos).cType == tempFolder )
                        {
                            MainEngine.changeDir(pos);
                            showFiles((HWND) lParam);
                        }
                    }
                    break;
                }
            }
            break;
        }
        case WM_PARENTNOTIFY:
        {
            puts("notify");
            break;
        }
        case WM_CREATE:
        {
            puts("create");
            break;
        }
        default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

    return 0;
}