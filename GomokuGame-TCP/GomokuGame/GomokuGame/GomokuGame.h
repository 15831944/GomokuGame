#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include "resource.h"
#pragma comment(lib,"ws2_32.lib")
enum RecvMsg {
	FORWARD,
	CLIENT_CLOSE
};
enum SendMsg {
	GAME_START,
	CLIENT_CLOSE_,
	CLOSE_SERVER,
	PLAYER_ID
};
typedef struct Client_Data {
	int Pos;
	SOCKET Socket;
	struct Client_Data *Next;
}CLIENT_DATA;
bool Menu();
bool WindowCreate(HWND hWnd);
bool WindowClose(HWND hWnd);
char *Analysis(char *Buff, char ch);
int GetFileLen(const char *FileName);
bool Process(HWND hWnd, char *Content);
bool ShowInterface(HWND hWnd, HDC hDC);
bool Key_Down(HWND hWnd, WPARAM wParam);
bool DropFiles(HWND hWnd, WPARAM wParam);
bool Save_MouseDown(HWND hWnd);
bool Mode_MouseDown(HWND hWnd);
bool Return_MouseDown(HWND hWnd);
bool Restart_MouseDown(HWND hWnd);
bool LoadFile_MouseDown(HWND hWnd);
bool ConnectServer_MouseDown(HWND hWnd);
bool DeleteFile_MouseDown(HWND hWnd);
bool Historical_MouseDown(HWND hWnd);
DWORD WINAPI Respond(LPVOID Parameter);
char *GetLine(char *FileContent, int Line);
bool MouseLeft_Dowm(HWND hWnd, LPARAM lParam); 
bool MouseRight_Dowm(HWND hWnd, LPARAM lParam);
BOOL MovePointer_Char(char **lpStart, char ch, BOOL df);
const char *GetFileContent(char *Content, const char *FileName);
void ShowError(HWND hWnd, DWORD dwErrNo, const TCHAR *lpszFunction);
