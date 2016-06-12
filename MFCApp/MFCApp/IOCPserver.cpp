#include "StdAfx.h"
#include "IOCPserver.h"
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "DataStructure.h"
#include "ControlCode.h"
#include "ThreadFuniction.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;

extern struct serverset serverinfo;

extern HANDLE hCom;  //全局变量，串口句柄

extern DCB dcb;

extern CCarbarnInfo* garage;

extern CWayFinding* mapinfo;

extern int reservation;

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

extern int link;

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
	HANDLE CompletionPort = (HANDLE) CompletionPortID;
	DWORD BytesTransferred;
// LPOVERLAPPED Overlapped;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	DWORD SendBytes, RecvBytes;
	DWORD Flags;

	while(TRUE)
	{
			  
		if (GetQueuedCompletionStatus(CompletionPort, &BytesTransferred,
			(LPDWORD)&PerHandleData, (LPOVERLAPPED *) &PerIoData, INFINITE) == 0)
		{
/*			printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());
			return 0;
			continue;
			printf(">%d<end\n",index);//*/
		}

		/* First check to see if an error has occured on the socket and if so
		   then close the socket and cleanup the SOCKET_INFORMATION structure
		   associated with the socket.	//*/

		if (BytesTransferred == 0)
		{
			printf("[%s:%u] is closed!!\n",PerIoData->ip,PerIoData->port);	 
			if (closesocket(PerHandleData->Socket) == SOCKET_ERROR)
			{
				printf("closesocket() failed with error %d\n", WSAGetLastError());
				return 0;
			}

			GlobalFree(PerHandleData);
			GlobalFree(PerIoData);
			continue;
		}

		/* Check to see if the BytesRECV field equals zero. If this is so, then
		   this means a WSARecv call just completed so update the BytesRECV field
		   with the BytesTransferred value from the completed WSARecv() call.	//*/

		if (PerIoData->BytesRECV == 0)
		{
			PerIoData->BytesRECV = BytesTransferred;
			PerIoData->BytesSEND = 0;
		}
		else
		{
			PerIoData->BytesSEND += BytesTransferred;
		}

		if (PerIoData->BytesRECV > PerIoData->BytesSEND)
		{

			/* Post another WSASend() request.
			   Since WSASend() is not gauranteed to send all of the bytes requested,
			   continue posting WSASend() calls until all received bytes are sent.	//*/

			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));

			PerIoData->DataBuf.buf = PerIoData->Buffer + PerIoData->BytesSEND;
			PerIoData->DataBuf.len = PerIoData->BytesRECV - PerIoData->BytesSEND;

			printf("[%s:%u]->%s\n",PerIoData->ip,PerIoData->port,PerIoData->DataBuf.buf);
		
	WSABUF DataBuf;
	char sendstr[]="hello world client";
	DataBuf.buf=sendstr;
	DataBuf.len=strlen(sendstr)+1;

			if (WSASend(PerHandleData->Socket, &(DataBuf), 1, &SendBytes, 0,
				&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSASend() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
			ZeroMemory(PerIoData->DataBuf.buf,PerIoData->DataBuf.len);			  
		}
		else
		{
			printf("*");
			PerIoData->BytesRECV = 0;

			// Now that there are no more bytes to send post another WSARecv() request.

			Flags = 0;
			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));

			PerIoData->DataBuf.len = DATA_BUFSIZE;
			PerIoData->DataBuf.buf = PerIoData->Buffer;

			if (WSARecv(PerHandleData->Socket, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
				&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					printf("WSARecv() failed with error %d\n", WSAGetLastError());
					return 0;
				}
			}
		}
	}
}  

DWORD WINAPI iocpstartserver(LPVOID pParam)
{
	SOCKADDR_IN InternetAddr;
	SOCKET Listen;
	SOCKET Accept;
	HANDLE CompletionPort;
	SYSTEM_INFO SystemInfo;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;

	DWORD RecvBytes;
	DWORD Flags;
	DWORD ThreadID;
	WSADATA wsaData;
	DWORD Ret;

	unsigned int i = 0;

	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		printf("WSAStartup failed with error %d\n", Ret);
		return -1;
	}
	printf("WSAStartup\n");
	// Setup an I/O completion port.

	if ((CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		printf( "CreateIoCompletionPort failed with error: %d\n", GetLastError());
		return -1;
	}
	printf("CreateIoCompletionPort\n");

	// Determine how many processors are on the system.

	GetSystemInfo(&SystemInfo);

	// Create worker threads based on the number of processors available on the
	// system. Create two worker threads for each processor.

	for(i = 0; i < SystemInfo.dwNumberOfProcessors * 2; i++)
	{
		HANDLE ThreadHandle;

		// Create a server worker thread and pass the completion port to the thread.

		if ((ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, CompletionPort,
			0, &ThreadID)) == NULL)
		{
			printf("CreateThread() failed with error %d\n", GetLastError());
			return -1;
		}
		// Close the thread handle
		CloseHandle(ThreadHandle);
	}
	printf("创建%2d个工作线程\n",i);

	// Create a listening socket

	if ((Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		return -1;
	}
	printf("WSASocket()\n"); 

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(serverinfo.iocpport);

	if (bind(Listen, (PSOCKADDR) &InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return -1;
	}
	printf("bind()\n");

	// Prepare socket for listening

	if (listen(Listen, 5) == SOCKET_ERROR)
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return -1;
	}
	printf("listen()\n");

	// Accept connections and assign to the completion port.
	sockaddr_in client;
	int len=sizeof(client);
	while(TRUE)
	{
		ZeroMemory(&client,sizeof(sockaddr_in));
		if ((Accept = WSAAccept(Listen, PSOCKADDR(&client), &len, NULL, 0)) == SOCKET_ERROR)
		{
			printf("WSAAccept() failed with error %d\n", WSAGetLastError());
//			getchar();
			return -1;
		}

		// Create a socket information structure to associate with the socket
		if ((PerHandleData = (LPPER_HANDLE_DATA) GlobalAlloc(GPTR,	 
			sizeof(PER_HANDLE_DATA))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
//			getchar();
			return -1;
		}

		// Associate the accepted socket with the original completion port.
		
		PerHandleData->Socket = Accept;

		if (CreateIoCompletionPort((HANDLE) Accept, CompletionPort, (DWORD) PerHandleData,
			0) == NULL)
		{
			printf("CreateIoCompletionPort failed with error %d\n", GetLastError());
//			getchar();
			return -1;
		}

		// Create per I/O socket information structure to associate with the	 
		// WSARecv call below.

		if ((PerIoData = (LPPER_IO_OPERATION_DATA) GlobalAlloc(GPTR,
			sizeof(PER_IO_OPERATION_DATA))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
//			getchar();
			return -1;
		}

		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
//		strncpy_s(PerIoData->ip, 20, inet_ntoa(client.sin_addr), 20);
		inet_ntop(AF_INET, (void*)&client.sin_addr, PerIoData->ip, 20);
		PerIoData->port=ntohs(client.sin_port);
		PerIoData->BytesSEND = 0;
		PerIoData->BytesRECV = 0;
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;

		printf("[%s:%u] has established!!\n",PerIoData->ip,PerIoData->port);

		Flags = 0;
		if (WSARecv(Accept, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
			&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				printf("WSARecv() failed with error %d\n", WSAGetLastError());
//				getchar();
				return -1;
			}
		}//*/
	}
}


