#include <Windows.h>

HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
            if (kbdStruct.vkCode == VK_F1) {
                MessageBoxA(NULL, "F1 is pressed!", "key pressed", MB_ICONINFORMATION);
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