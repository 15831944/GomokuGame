#pragma once

#include "resource.h"
bool WindowCreate(HWND hWnd);
bool WindowClose(HWND hWnd);
bool ShowInterface(HWND hWnd, HDC hDC);
bool Key_Down(HWND hWnd, WPARAM wParam);
bool DropFiles(HWND hWnd, WPARAM wParam);
bool Save_MouseDown(HWND hWnd);
bool Mode_MouseDown(HWND hWnd);
bool Return_MouseDown(HWND hWnd);
bool Restart_MouseDown(HWND hWnd);
bool LoadFile_MouseDown(HWND hWnd);
bool DeleteFile_MouseDown(HWND hWnd);
bool Historical_MouseDown(HWND hWnd);
bool MouseLeft_Dowm(HWND hWnd, LPARAM lParam); 
bool MouseRight_Dowm(HWND hWnd, LPARAM lParam);