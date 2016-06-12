/* Module Name: iocmplt.cpp
//
// Description:
//
//	 This sample illustrates how to develop a simple echo server Winsock
//	 application using the completeion port I/O model. This	 
//	 sample is implemented as a console-style application and simply prints
//	 messages when connections are established and removed from the server.
//	 The application listens for TCP connections on port 5150 and accepts them
//	 as they arrive. When this application receives data from a client, it
//	 simply echos (this is why we call it an echo server) the data back in
//	 it's original form until the client closes the connection.
//
// Compile:
//
//	 cl -o iocmplt iocmplt.cpp ws2_32.lib
//
// Command Line Options:
//
//	 iocmplt.exe	 
//
//	 Note: There are no command line options for this sample.	//*/

#if !defined(_IOCPSERVER_)
#define _IOCPSERVER_

#include "StdAfx.h"
#include "DataStructure.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

#define PORT 5555
#define DATA_BUFSIZE 8192

typedef struct
{
	OVERLAPPED Overlapped;
	WSABUF DataBuf;
	CHAR Buffer[DATA_BUFSIZE];
	CHAR ip[20];
	UINT port;
	DWORD BytesSEND;
	DWORD BytesRECV;
} PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;

typedef struct	 
{
	SOCKET Socket;
} PER_HANDLE_DATA, * LPPER_HANDLE_DATA;

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);

DWORD WINAPI iocpstartserver(LPVOID pParam);

#endif