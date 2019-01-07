#pragma once
#include <iostream>
#include <fstream>
#define WHITE	1
#define BLACK	2
#define MAP_WIDE	15
#define MAP_HIGH	15
#define EDGE_WIDE	20
#define EDGE_HIGH	20
#define CURSOR_MOVE	20//���һ���ƶ�������
#define CHESSBOX_RECT_WIDE	20
#define CHESSBOX_RECT_HIGH	20
enum Direction{
	 UP,
	 DOWN,
	 LEFT,
	 RIGHT,
	 LEFT_UP,
	 RIGHT_UP,
	 LEFT_DOWN,
	 RIGHT_DOWN
};
typedef struct Chess {
	int iChessCount;
	COORD pChessPos;
}CHESS;
class Gomoku{
	RECT Rect;
	int Later;//������
	HDC hBlackDC;//����dc
	HDC hWhiteDC;
	int iFileCount;
	HDC hChessBoxDC;//����dc
	int iChessCount;//��¼�˶�������ʤ��
	bool bHistorical;
	int iChessBoxWide;
	int iChessBoxHigh;
	TCHAR Cursor[MAXBYTE];
	int iChessCount_Black;//113
	int iChessCount_White;//112
	TCHAR tcResult[MAXBYTE];
	TCHAR FileName_[MAXBYTE];//�ñ�����Ϊ���򽫴浵���浽���ļ�
	int iMap[MAP_HIGH][MAP_WIDE];
	bool RetPos(CHESS *Pos, Direction df);
	Direction SetContraries(Direction df);
public:
	Gomoku(HWND hWnd);
	~Gomoku();
	bool init();
	int Mode();
	int ChessCount();
	bool Save(HWND hWnd);
	bool Result(CHESS Pos);
	inline int FileCount();
	BOOL Show(HDC hLoadBmpDC);
	bool Move_Later(HWND hWnd);
	bool MoveCursor(Direction DF);
	bool CanMoveCursor(Direction DF);
	bool DeleFile(HWND hWnd, int Index);
	bool ShowHistorical(HDC hLoadBmpDC);
	inline bool Historical(bool Visible);
	bool ReadFile(HWND hWnd, TCHAR *FileName);
	bool Move_Later(HWND hWnd, LPARAM lParam);
	bool Move_Later(HWND hWnd, int Pos, int X, int Y);
};
inline bool Gomoku::Historical(bool Visible) {
	return bHistorical = Visible;
}
inline int Gomoku::FileCount(){
	return iFileCount;
}