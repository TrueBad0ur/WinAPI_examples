#include <Windows.h>
#include <iostream>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <psapi.h>

void listFiles() {
    HANDLE hFind = INVALID_HANDLE_VALUE;
    TCHAR szDir[MAX_PATH] = TEXT(".\\*");
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;

    hFind = FindFirstFile(szDir, &ffd);

    do {
        // check if it's a directory
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            //wcslen(ffd.cFileName
            _tprintf(TEXT("  %*s      <DIR>\n"), 30, ffd.cFileName);
        } else {
        // else it's a file
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

void dynamicDLLImport() {
    typedef int(WINAPI* MessageBeepProc)(UINT);

    HMODULE hModule1 = LoadLibrary(TEXT("USER32.dll"));
    MessageBeepProc MessageBeepF = (MessageBeepProc)GetProcAddress(hModule1, "MessageBeep");
    MessageBeepF(0xFFFFFFFF);
}

// function helper for EnumSystemProcesses()
void PrintProcessNameAndID(DWORD processID) {
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    if (NULL != hProcess) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
            GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        }
    }
    _tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);
    CloseHandle(hProcess);
}

int EnumSystemProcesses() {
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
        return 1;
    }

    cProcesses = cbNeeded / sizeof(DWORD);
    for (i = 0; i < cProcesses; i++) {
        if (aProcesses[i] != 0) {
            PrintProcessNameAndID(aProcesses[i]);
        }
    }
}

int main() {
	listFiles();
    showWindow();
    infoAboutSystem();
    notepadExample();
    dynamicDLLImport();
    // need higher rights
    EnumSystemProcesses();
	return 0;
}