// Server.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "List.h"
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")
#define NUMBER_OF_PEOPLE 2
enum RecvMsg{
	FORWARD,
	CLIENT_CLOSE
};
enum SendMsg{
	GAME_START,
	CLIENT_CLOSE_,
	CLOSE_SERVER,
	PLAYER_ID
};
SOCKET Socket;
LIST_HEAD ListHead;
BOOL InitalSocket(SOCKET *Socket);
BOOL WINAPI Routine(DWORD dwCtrlType);
bool SendContent(const char *Content);
DWORD WINAPI Respond(LPVOID Parameter);
void ShowError(DWORD dwErrNo, const TCHAR *lpszFunction);
bool Forward_Message(CLIENT_DATA * ptrNode, char *Content);
bool ClientClose_Message(CLIENT_DATA * ptrNode, char *Content);
bool(*Recv[])(CLIENT_DATA * ptrNode, char *Content) = {
	Forward_Message,
	ClientClose_Message
};
int main(){
	CLIENT_DATA CData = { 0 };
	char Content[MAXBYTE] = { 0 };
	SOCKADDR_IN ClientAddr = { 0 };
	int ClientAddrLen = sizeof(ClientAddr);
	SetConsoleCtrlHandler(Routine, TRUE);
	if (FALSE == InitalSocket(&Socket)) {
		printf("初始化Socket出错\n");
		system("pause");
		return -1;
	}
	while (true){
		if (INVALID_SOCKET == (CData.Socket = accept(Socket, (SOCKADDR *)&ClientAddr, &ClientAddrLen))) {
			ShowError(WSAGetLastError(), L"等待客户端连接时:");
			return -1;
		}
		printf("第%d个客户端连接进来了...\n", CData.Pos);
		printf("客户端IP = %d.%d.%d.%d\n", ClientAddr.sin_addr.S_un.S_un_b.s_b1, ClientAddr.sin_addr.S_un.S_un_b.s_b2, ClientAddr.sin_addr.S_un.S_un_b.s_b3, ClientAddr.sin_addr.S_un.S_un_b.s_b4);
		HANDLE hThread = CreateThread(NULL, NULL, Respond, InsertNode(&ListHead.DataHead, &CData, GetNodeCount(ListHead.DataHead)), NULL, NULL);
		if (!hThread) {
			ShowError(GetLastError(), L"创建消息线程时:");
			return FALSE;
		}
		memset(Content, 0, sizeof(Content));
		sprintf(Content, "%d\n%d\n", PLAYER_ID, CData.Pos++);
		send(CData.Socket, Content, strlen(Content), 0);
		if (NUMBER_OF_PEOPLE == GetNodeCount(ListHead.DataHead)) {
			memset(Content, 0, sizeof(Content));
			sprintf(Content, "%d\n", GAME_START);
			Sleep(500);
			SendContent(Content);//向所有玩家发送游戏开始消息
		}
	}
    return 0;
}
char *Analysis(char *Buff, char ch) {
	if (!Buff)return nullptr;
	char *lpEnd = strchr(Buff, ch);
	if (lpEnd) {
		char *lpStart = Buff;
		char *Buf = (char *)malloc(strlen(Buff) + 1);
		memset(Buf, 0, strlen(Buff) + 1);
		*lpEnd = 0;
		strcpy(Buf, lpStart);
		lpEnd++;
		strcat(strcat(strcpy(Buff, lpEnd), "\\"), Buf);
		//到这里说明已经将我们需要的字符串放到最后面了
		lpStart = strchr(Buff, '\\');
		*lpStart = 0;
		free(Buf);
		return ++lpStart;
	}
	return Buff;
}
bool Process(CLIENT_DATA * ptrNode, char *Content) {
	return Recv[atoi(Analysis(Content, '\n'))](ptrNode, Content);
}
bool SendContent(const char *Content) {
	for (CLIENT_DATA *ptrHead = ListHead.DataHead; ptrHead; ptrHead = ptrHead->Next) {
		send(ptrHead->Socket, Content, strlen(Content), 0);
	}
	return true;
}
DWORD WINAPI Respond(LPVOID Parameter) {
	//int Error = 0;
	//srand((unsigned int)time(NULL));
	char Content[MAXWORD] = { 0 };
	CLIENT_DATA *ptrNode = (CLIENT_DATA *)Parameter;
	while (recv(ptrNode->Socket, Content, sizeof(Content), 0) > 0) {
		Process(ptrNode, Content);
		_strset(Content, 0);
	}
	ShowError(WSAGetLastError(), L"接收客户端数据时:");
	return TRUE;
}
bool Forward_Message(CLIENT_DATA * ptrNode, char * Content){
	return SendContent(Content);
}
bool ClientClose_Message(CLIENT_DATA * ptrNode, char * Content){
	char Content_[MAXBYTE] = { 0 };
	sprintf(Content_, "%d\n%d", CLIENT_CLOSE_, ptrNode->Pos);
	closesocket(ptrNode->Socket);
	SendContent(Content_);
	return false;
}
BOOL WINAPI Routine(DWORD dwCtrlType) {
	if (CTRL_CLOSE_EVENT == dwCtrlType) {
		// 控制台将要被关闭，这里添加你的处理代码 ...
		char Buff[10] = { 0 };
		sprintf(Buff, "%d\n", CLOSE_SERVER);
		SendContent(Buff);
		closesocket(Socket);
		for (CLIENT_DATA *ptrHead = ListHead.DataHead; ptrHead; ptrHead = ptrHead->Next) {
			closesocket(ptrHead->Socket);
		}
		WSACleanup();
	}
	return TRUE;
}
void ShowError(DWORD dwErrNo, const TCHAR *lpszFunction) {
	LPVOID lpMsgBuf;
	//	memset(lpMsgBuf, 0, sizeof(lpMsgBuf));
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErrNo,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   //   Default   language   
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	wchar_t Message[500] = { 0 };
	memset(Message, 0, sizeof(Message));
	wcscat(wcscat(Message, lpszFunction), (LPTSTR)lpMsgBuf);
	MessageBox(NULL, Message, L"Error", MB_OK);
}
BOOL InitalSocket(SOCKET *Socket) {
	WSADATA WSAData;
	int SockError = 0;
	SOCKADDR_IN ServerAddr = { 0 };
	if ((SockError = WSAStartup(MAKEWORD(2, 2), &WSAData))) {
		ShowError(SockError, L"初始化Socket时:");
		return FALSE;
	}
	*Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(10086);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (SOCKET_ERROR == bind(*Socket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr))) {
		ShowError(WSAGetLastError(), _TEXT("绑定Socket时:"));
		return FALSE;
	}
	if (SOCKET_ERROR == listen(*Socket, NUMBER_OF_PEOPLE)) {
		ShowError(WSAGetLastError(), _TEXT("监听Socket时:"));
		return FALSE;
	}
	return TRUE;
}
