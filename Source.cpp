#include <Windows.h>
#include <iostream>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>

void listFiles() {
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH] = TEXT(".\\*");
	WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;

	hFind = FindFirstFile(szDir, &ffd);

    do
    {
        // check if it's a directory
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            //wcslen(ffd.cFileName
            _tprintf(TEXT("  %*s      <DIR>\n"), 30, ffd.cFileName);
        }
        else
        // else it's a file
        {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            _tprintf(TEXT("  %*s      %ld bytes\n"), 30, ffd.cFileName, filesize.QuadPart);
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    getchar();
}

void showWindow() {
    MessageBoxW(NULL, TEXT("Text inside the window"), TEXT("Title of the window"), MB_OK);
}

void infoAboutSystem() {
    ShellAbout(NULL, TEXT("hello"), TEXT("world"), NULL);
}

void notepadExample() {
    HWND hWndCalc, hEditWnd;
    hWndCalc = FindWindowA("Notepad", NULL);
    if (hWndCalc) {
        // Set title of notepad to TEST
        SetWindowTextA(hWndCalc, "TEST");
        hEditWnd = FindWindowEx(hWndCalc, NULL, TEXT("Edit"), NULL);
        if (hEditWnd) {
            SendMessageA(hEditWnd, WM_SETTEXT, 0, (LPARAM)"TEST");
        }
    }
}

int main() {
	listFiles();
    showWindow();
    infoAboutSystem();
    notepadExample();
	return 0;
}