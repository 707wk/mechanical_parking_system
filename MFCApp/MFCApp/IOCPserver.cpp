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

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

int inputParking(char* strplate, int inputId)
{
	MYSQL_RES *res;                    //查询结果集
	//MYSQL_ROW column;                //数据行的列
	char strtmp[COMLEN];

	if (serverinfo.sumcar == serverinfo.spendcar + serverinfo.reservation)
	{
		//MessageBox(_T("车位已满"));
		return NOCAR;
	}

	sprintf_s(strtmp, COMLEN, "select plate from t_reservation where plate='%s'", strplate);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		if (mysql_num_rows(res))
		{
			sprintf_s(strtmp, COMLEN, "delete from t_reservation where plate='%s'", strplate);
			mysql_query(&serverinfo.mysql, strtmp);
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}

	sprintf_s(strtmp, COMLEN, "select plate from t_carinfo where plate='%s'", strplate);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		if (mysql_num_rows(res))
		{
			//MessageBox(_T("车牌重复"));
			return PLATEREPEAT;
		}
	}

	int garageid = mapinfo->nearestcarport(inputId);

	if (garageid == -1)
	{
		//MessageBox(_T("未找到空闲模块,请稍后再试!"));
		return GARAGEBUSY;
	}

	printf("最近的车库是第%d号车库\n", garageid);

	sprintf_s(strtmp, COMLEN, "insert into t_carinfo(plate,start) values('%s',now())", strplate);
	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}

	int index = idtoindex[garageid];

	garage[index].setnowstatus(BUSY);

	char sendstr[] = "123";
	sendstr[0] = SAVECAR;
	sendstr[1] = garage[index].getrows(garage[index].findemptycarid());
	sendstr[2] = garage[index].getcols(garage[index].findemptycarid());
	garage[index].setcommand(sendstr);

	sprintf_s(strtmp, COMLEN, "update t_carinfo set carbarnid=%d,num=%d where plate='%s'",
		garageid, garage[index].findemptycarid(), strplate);
	garage[index].setsqlcommand(strtmp);

	garage[index].savecar();

	serverinfo.spendcar++;

	memset(strplate, '\0', COMLEN);
	strplate[0] = TASKSUCCEED;
	sprintf_s(strplate + 1, COMLEN - 1, " %d", garageid);
	return TASKSUCCEED;
}

int outputDrawOut(char* strplate)
{
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	char strtmp[COMLEN];
	time_t start;
	time_t end;
	struct tm tmp;
	double cost;

	sprintf_s(strtmp, COMLEN, "select start from t_carinfo where plate='%s'", strplate);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) == NULL)
	{
		res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column = mysql_fetch_row(res);              //获取具体的数据
		if(column==NULL)
		{
			return NOTFOUND;
		}
		//2016-06-12 21:53:45
		sscanf_s(column[0], "%d-%d-%d %d:%d:%d", &tmp.tm_year, &tmp.tm_mon, &tmp.tm_mday, &tmp.tm_hour, &tmp.tm_min, &tmp.tm_sec);
		tmp.tm_mon--;
		tmp.tm_year -= 1900;
		start = mktime(&tmp);
		time(&end);
		cost = difftime(end, start);
		//printf("[%s]",column[0]);
	}
	/*struct tm{
	int tm_sec; // 秒: 0-59
	int tm_min; // 分: 0-59
	int tm_hour; // 时: 0-23
	int tm_mday; // 日: 1-31
	int tm_mon; // 月: 0-11
	int tm_year; // 年: 1900+
	int tm_wday; // 星期: 0-6
	int tm_yday; // 某年的第几天: 0-365
	int tm_isdst; // 夏令时标志: 0/1
	}
	下面以2010年9月12日为例：
	struct tm tm10912;
	time_t tt10912;
	tm10912.tm_mday = 12;
	tm10912.tm_mon = 9 - 1;
	tm10912.tm_year = 2010 - 1900;
	tt10912= mktime(&tm10912);*/

	sprintf_s(strtmp, COMLEN, "delete from t_carinfo where plate='%s'", strplate);

	serverinfo.spendcar--;

	memset(strplate, '\0', COMLEN);
	strplate[0] = TASKSUCCEED;
	sprintf_s(strplate + 1, COMLEN - 1, " %.0f %.1f", cost/60, serverinfo.cost);
	return TASKSUCCEED;
}

int carRetrieval(char* strplate)
{
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	char strtmp[COMLEN];

	sprintf_s(strtmp, COMLEN, "select carbarnid,num from t_carinfo where plate='%s'", strplate);

	mysql_query(&serverinfo.mysql, "SET NAMES 'GB2312'");

	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}
	res = mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

	if (mysql_num_rows(res) == 0)
	{
		//MessageBox(_T("未找到车辆"));
		return NOTFOUND;
	}

	column = mysql_fetch_row(res);

	int garageid = atoi(column[0]);
	int num = atoi(column[1]);

	int nearoutput = mapinfo->nearestexit(garageid);
	if (nearoutput == -1)
	{
		//MessageBox(_T("未找到出口,请检查地图设置!"));
		return NOTOUTPUT;
	}

	//	printf("最近的出口是第%d号出口\n", nearoutput);

	int index = idtoindex[garageid];

	garage[index].setnowstatus(BUSY);

	char sendstr[] = "123";
	sendstr[0] = DELETECAR;
	sendstr[1] = garage[index].getrows(num);
	sendstr[2] = garage[index].getcols(num);
	garage[index].setcommand(sendstr);

	sprintf_s(strtmp, COMLEN, "update t_carinfo set carbarnid=0,num=0 where plate='%s'", strplate);
	if (mysql_query(&serverinfo.mysql, strtmp) != NULL)
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1);
	}

	garage[index].setsqlcommand(strtmp);

	garage[index].deletecar(num);

	memset(strplate, '\0', COMLEN);
	strplate[0] = TASKSUCCEED;
	sprintf_s(strplate + 1, COMLEN - 1, " %d", nearoutput);
	return TASKSUCCEED;
}

DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID)
{
	HANDLE CompletionPort = (HANDLE) CompletionPortID;
	DWORD BytesTransferred;
// LPOVERLAPPED Overlapped;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	DWORD SendBytes, RecvBytes;
	DWORD Flags;
	DWORD start;
	DWORD stop;

	CString str;

	WSABUF DataBuf;
	char sendstr[COMLEN];
	char strplate[COMLEN];
	int  ioputId;
	int  result;

	DataBuf.buf = sendstr;

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
		start = GetTickCount();
		//InterlockedIncrement(&serverinfo.activeThread);
/*		if (stateflage == 0)
		{
			printf("Q");
			stateflage = 1;
			//++serverinfo.activeThread;
			InterlockedIncrement(&serverinfo.activeThread);
		}//*/
		/* First check to see if an error has occured on the socket and if so
		   then close the socket and cleanup the SOCKET_INFORMATION structure
		   associated with the socket.	//*/

		if (BytesTransferred == 0)
		{
//			printf("[%s:%u] is closed!!\n",PerIoData->ip,PerIoData->port);
			printf("[%s:%u] 已断开\n", PerIoData->ip, PerIoData->port);
			//printf("C");
			//stateflage = 0;
			//--serverinfo.activeThread;
			//InterlockedDecrement(&serverinfo.activeThread);
			
			if (closesocket(PerHandleData->Socket) == SOCKET_ERROR)
			{
				str.Format(_T("closesocket() failed with error %d"), WSAGetLastError());
				AfxMessageBox(str);
				exit(1);
			}

			GlobalFree(PerHandleData);
			GlobalFree(PerIoData);

			//InterlockedDecrement(&serverinfo.activeThread);
			stop = GetTickCount();
			serverinfo.activeThreadtime = serverinfo.activeThreadtime + stop - start;
			//printf(":%ld-%ld:", stop - start, serverinfo.activeThread);
			continue;
		}
/*		if (stateflage == 0)
		{
			printf("Q");
			stateflage = 1;
			//++serverinfo.activeThread;
			InterlockedIncrement(&serverinfo.activeThread);
		}//*/

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
/*			if (stateflage == 0)
			{
				printf("Q");
				stateflage = 1;
				//++serverinfo.activeThread;
				InterlockedIncrement(&serverinfo.activeThread);
			}//*/

			/* Post another WSASend() request.
			   Since WSASend() is not gauranteed to send all of the bytes requested,
			   continue posting WSASend() calls until all received bytes are sent.	//*/

			ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));

			PerIoData->DataBuf.buf = PerIoData->Buffer + PerIoData->BytesSEND;
			PerIoData->DataBuf.len = PerIoData->BytesRECV - PerIoData->BytesSEND;

//			printf("[%s:%u]->{%d %d %d}\n",PerIoData->ip,PerIoData->port, PerIoData->DataBuf.buf[0], PerIoData->DataBuf.buf[3], PerIoData->DataBuf.buf[2]);

			switch (PerIoData->DataBuf.buf[0])
			{
			case INPUTSAVE:
				printf("入口存车");
				sscanf_s(PerIoData->DataBuf.buf + 1, " %s %d", strplate, COMLEN, &ioputId);
				result = inputParking(strplate, ioputId);
				switch (result)
				{
				case TASKSUCCEED:
					strcpy_s(sendstr, COMLEN, strplate);
					serverinfo.spendcar++;
					break;
				default:
					sendstr[0] = result;
					sendstr[1] = sendstr[0] % CHECKMOD;
					sendstr[2] = '\0';
				}
				break;
			case OUTPUTDELE:
				printf("出口出车");
				sscanf_s(PerIoData->DataBuf.buf + 1, " %s", strplate, COMLEN);
				result = outputDrawOut(strplate);
				switch (result)
				{
				case TASKSUCCEED:
					strcpy_s(sendstr, COMLEN, strplate);
					serverinfo.spendcar--;
					break;
				default:
					sendstr[0] = result;
					sendstr[1] = sendstr[0] % CHECKMOD;
					sendstr[2] = '\0';
				}
				break;
			case OUTPUTGARAGE:
				printf("模块取车");
				sscanf_s(PerIoData->DataBuf.buf + 1, " %s", strplate, COMLEN);
				result = carRetrieval(strplate);
				switch (result)
				{
				case TASKSUCCEED:
					strcpy_s(sendstr, COMLEN, strplate);
					break;
				default:
					sendstr[0] = result;
					sendstr[1] = sendstr[0] % CHECKMOD;
					sendstr[2] = '\0';
				}
				break;
			case RESERVATION:
//				printf("预约");
				if (serverinfo.sumcar - serverinfo.spendcar - serverinfo.reservation < 1)
				{
					sendstr[0] = (unsigned char) NOCAR;
				}
				else
				{
					sendstr[0] = TASKSUCCEED;
					serverinfo.reservation++;
				}
				sendstr[1] = sendstr[0] % CHECKMOD;
				sendstr[2] = '\0';
				break;
			case UNRESERVATION:
//				printf("取消");
				serverinfo.reservation--;
				sendstr[0] = TASKSUCCEED;
				sendstr[1] = sendstr[0] % CHECKMOD;
				sendstr[2] = '\0';
				break;
			case GETGARAGEINFO:
//				printf("获取信息");
				memset(sendstr, '\0', COMLEN);
				sendstr[0] = TASKSUCCEED;
				sprintf_s(sendstr + 1, COMLEN-1, " %d %d", serverinfo.sumcar - serverinfo.spendcar -serverinfo.reservation,serverinfo.reservationtime);
				break;
			case PANTBAG:
				sendstr[0] = PANTBAG;
				sendstr[1] = sendstr[0] % CHECKMOD;
				sendstr[2] = '\0';
				break;
			default:
				printf("未定义");
				sendstr[0] = NOTDEFINE;
				sendstr[1] = sendstr[0] % CHECKMOD;
				sendstr[2] = '\0';
			}
			printf("<%d>", DataBuf.buf[0]);
			DataBuf.len=strlen(sendstr)+1;

			if (WSASend(PerHandleData->Socket, &(DataBuf), 1, &SendBytes, 0,
				&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
			{
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					str.Format(_T("WSASend() failed with error %d"), WSAGetLastError());
					AfxMessageBox(str);
					exit(1);
				}
			}
			ZeroMemory(PerIoData->DataBuf.buf,PerIoData->DataBuf.len);
		}
		else
		{
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
					str.Format(_T("WSARecv() failed with error %d"), WSAGetLastError());
					AfxMessageBox(str);
					exit(1);
				}
			}
		}
		//InterlockedDecrement(&serverinfo.activeThread);
		stop = GetTickCount();
		serverinfo.activeThreadtime = serverinfo.activeThreadtime + stop - start;
	}
}  

DWORD WINAPI iocpstartserver(LPVOID pParam)
{
	SOCKADDR_IN InternetAddr;
	SOCKET Listen;
	SOCKET Accept;
	HANDLE CompletionPort;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;

	DWORD RecvBytes;
	DWORD Flags;
	DWORD ThreadID;
	WSADATA wsaData;
	DWORD Ret;

	CString str;

	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		str.Format(_T("WSAStartup failed with error %d"), Ret);
		AfxMessageBox(str);
		exit(1);
	}

	// Setup an I/O completion port.
	if ((CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL)
	{
		str.Format(_T("CreateIoCompletionPort failed with error: %d"), GetLastError());
		AfxMessageBox(str);
		exit(1);
	}

	// Determine how many processors are on the system.
	// Create worker threads based on the number of processors available on the
	// system. Create two worker threads for each processor.
	
	for(int i = 0; i < serverinfo.Threadsum; i++)
	{
		HANDLE ThreadHandle;

		// Create a server worker thread and pass the completion port to the thread.
		if ((ThreadHandle = CreateThread(NULL, 0, ServerWorkerThread, CompletionPort,
			0, &ThreadID)) == NULL)
		{
			str.Format(_T("CreateThread() failed with error %d"), GetLastError());
			AfxMessageBox(str);
			exit(1);
		}
		// Close the thread handle
		CloseHandle(ThreadHandle);
	}

	// Create a listening socket
	if ((Listen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		str.Format(_T("WSASocket() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		exit(1);
	}

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InternetAddr.sin_port = htons(serverinfo.iocpport);

	if (bind(Listen, (PSOCKADDR) &InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		str.Format(_T("bind() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		exit(1);
	}

	// Prepare socket for listening
	if (listen(Listen, 5) == SOCKET_ERROR)
	{
		str.Format(_T("listen() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		exit(1);
	}

	// Accept connections and assign to the completion port.
	sockaddr_in client;
	int len=sizeof(client);
	while(TRUE)
	{
		ZeroMemory(&client,sizeof(sockaddr_in));
		if ((Accept = WSAAccept(Listen, PSOCKADDR(&client), &len, NULL, 0)) == SOCKET_ERROR)
		{
			str.Format(_T("WSAAccept() failed with error %d"), WSAGetLastError());
			AfxMessageBox(str);
			exit(1);
		}

		// Create a socket information structure to associate with the socket
		if ((PerHandleData = (LPPER_HANDLE_DATA) GlobalAlloc(GPTR,	 
			sizeof(PER_HANDLE_DATA))) == NULL)
		{
			str.Format(_T("GlobalAlloc() failed with error %d"), GetLastError());
			AfxMessageBox(str);
			exit(1);
		}

		// Associate the accepted socket with the original completion port.
		PerHandleData->Socket = Accept;

		if (CreateIoCompletionPort((HANDLE) Accept, CompletionPort, (DWORD) PerHandleData,
			0) == NULL)
		{
			str.Format(_T("CreateIoCompletionPort failed with error %d"), GetLastError());
			AfxMessageBox(str);
			exit(1);
		}

		// Create per I/O socket information structure to associate with the	 
		// WSARecv call below.

		if ((PerIoData = (LPPER_IO_OPERATION_DATA) GlobalAlloc(GPTR,
			sizeof(PER_IO_OPERATION_DATA))) == NULL)
		{
			str.Format(_T("GlobalAlloc() failed with error %d"), GetLastError());
			AfxMessageBox(str);
			exit(1);
		}

		ZeroMemory(&(PerIoData->Overlapped), sizeof(OVERLAPPED));
		inet_ntop(AF_INET, (void*)&client.sin_addr, PerIoData->ip, 20);
		PerIoData->port=ntohs(client.sin_port);
		PerIoData->BytesSEND = 0;
		PerIoData->BytesRECV = 0;
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		PerIoData->DataBuf.buf = PerIoData->Buffer;

//		printf("[%s:%u] has established!!\n",PerIoData->ip,PerIoData->port);
		printf("[%s:%u] 已连接\n", PerIoData->ip, PerIoData->port);

		Flags = 0;
		if (WSARecv(Accept, &(PerIoData->DataBuf), 1, &RecvBytes, &Flags,
			&(PerIoData->Overlapped), NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				//printf
				str.Format(_T("WSARecv() failed with error %d"), WSAGetLastError());
				AfxMessageBox(str);
				exit(1);
			}
		}//*/
	}
}


