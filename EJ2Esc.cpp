#include <windows.h>

#define WND_CLASS_NAME "EJ2Esc"

#define HKID_OEM_AUTO 0x10
#define HKID_OEM_ENLW 0x20
#define TMID_CAPITAL  2

#ifdef __cplusplus
extern "C" int WinMainCRTStartup();
#endif

void SendKey(UINT vk) {
    INPUT input[2] = {0};
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = vk;
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = vk;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, input, sizeof(INPUT));
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    static HANDLE hmutex;

    switch (msg) {
        case WM_CREATE:
            // Prevent multiple running
            hmutex = CreateMutex(NULL, TRUE, WND_CLASS_NAME);
            if (hmutex != NULL) {
                if(GetLastError() == ERROR_ALREADY_EXISTS){
                    ReleaseMutex(hmutex);
                    CloseHandle(hmutex);
                    PostQuitMessage(0);
                    break;
                }
            }
            else {
                PostQuitMessage(0);
                break;
            }
            // Set Hotkey for Zenkaku/Hankaku
            // `Alt + Zenkaku/Hankaku` cannot be replaced
            // MOD_SHIFT: 0x2, MOD_CONTROL: 0x4, MOD_WIN: 0x8
            for (int m = 0; m <= (MOD_SHIFT | MOD_CONTROL | MOD_WIN); m++) {
                RegisterHotKey(hwnd, HKID_OEM_AUTO | m, m, VK_OEM_AUTO);
                RegisterHotKey(hwnd, HKID_OEM_ENLW | m, m, VK_OEM_ENLW);
            }
            // Set Timer for disable CapsLock
            SetTimer(hwnd, TMID_CAPITAL, 1000, NULL);
            break;

        case WM_TIMER:
            switch (wparam) {
                case TMID_CAPITAL:
                    if (GetKeyState(VK_CAPITAL) & 0x0001) {
                        SendKey(VK_CAPITAL);
                    }
                    break;
            }
            break;

        case WM_HOTKEY:
            switch (wparam & 0xF0) {
                case HKID_OEM_AUTO:
                case HKID_OEM_ENLW:
                    SendKey(VK_ESCAPE);
                    break;
            }
            break;

        default:
            return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0;
}

int WinMainCRTStartup() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.hInstance = hInstance;
    wc.lpszClassName = WND_CLASS_NAME;
    wc.lpfnWndProc = WindowProc;
    if (!RegisterClass(&wc)) {
        return 0;
    }

    HWND hWnd = CreateWindow(
            WND_CLASS_NAME,
            NULL,
            0,
            0, 0,
            0, 0,
            HWND_MESSAGE,
            NULL,
            hInstance,
            NULL
            );
    if (hWnd == NULL) {
        return 0;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
