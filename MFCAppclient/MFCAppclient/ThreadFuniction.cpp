/**************************************
 *FILE          :T:\car\MFCAppclient\MFCAppclient\ThreadFuniction.cpp
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/6/24 13:53:44
 *TARGET        :C/C++
 *EMAIL         :gtsoft_wk@foxmail.com
 *LOGO          :
               #########                       
              ############                     
              #############                    
             ##  ###########                   
            ###  ###### #####                  
            ### #######   ####                 
           ###  ########## ####                
          ####  ########### ####               
        #####   ###########  #####             
       ######   ### ########   #####           
       #####   ###   ########   ######         
      ######   ###  ###########   ######       
     ######   #### ##############  ######      
    #######  ##################### #######     
    #######  ##############################    
   #######  ###### ################# #######   
   #######  ###### ###### #########   ######   
   #######    ##  ######   ######     ######   
   #######        ######    #####     #####    
    ######        #####     #####     ####     
     #####        ####      #####     ###      
      #####       ###        ###      #        
        ##       ####        ####              
***************************************/

#include "StdAfx.h"
#include "MFCAppclient.h"
#include "MFCAppclientDlg.h"
#include "DataStructure.h"
#include "ControlCode.h"

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <queue>
#include <time.h>

using namespace std;

#pragma warning(disable: 4996)  

extern struct serverset serverinfo;

DWORD WINAPI ThreadPoll(LPVOID pParam)
{
	char sendstr[COMLEN];
	char recstr[COMLEN];
	struct comNode tmp;
	printf("start\n");
	for (;;Sleep(1000))
	{
//		printf("!");
		if (serverinfo.command.empty() == TRUE)
			continue;

		memset(&tmp, '\0', sizeof(struct comNode));
		tmp = serverinfo.command.front();
		sendstr[0] = tmp.IOCTL;
		sprintf_s(sendstr + 1, COMLEN, " %s", tmp.strplate);

		switch (tmp.IOCTL)
		{
		case INPUTSAVE:
			sprintf_s(sendstr + 1, COMLEN, " %s %d", tmp.strplate, tmp.ioputid);
			break;
		case OUTPUTDELE:
			sprintf_s(sendstr + 1, COMLEN, " %s", tmp.strplate);
			break;
		case OUTPUTGARAGE:
			sprintf_s(sendstr + 1, COMLEN, " %s", tmp.strplate);
			break;
		default:;
		}

//		printf("send[con=%d str=%s len=%d]", sendstr[0], sendstr + 2, strlen(sendstr));

		/*if(tmp.IOCTL== PANTBAG)
			sprintf_s(sendstr + 1, COMLEN, " %d", tmp.ioputid);
		else sprintf_s(sendstr + 1, COMLEN, " %s %d", tmp.strplate, tmp.ioputid);//*/

		WSAData wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			AfxMessageBox(_T("WSAStartup失败"));
			exit(1);
		}

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			AfxMessageBox(_T("SOCKET版本不对"));
			WSACleanup();
			exit(1);
		}

		SOCKET sockClient;
		struct sockaddr_in addrServer;
		sockClient = socket(AF_INET, SOCK_STREAM, 0);
		if (sockClient == INVALID_SOCKET)
		{
			cout << "socket 失败" << endl;
			WSACleanup();
			return FALSE;
		}
		memset(&addrServer, 0, sizeof(sockaddr_in));

		addrServer.sin_family = AF_INET;
		addrServer.sin_addr.s_addr = inet_addr(serverinfo.ip);
		addrServer.sin_port = htons(serverinfo.iocpport);

		if (connect(sockClient, (const struct sockaddr*)&addrServer, sizeof(sockaddr)) != 0)
		{
			cout << "connect 失败" << endl;
			continue;
			WSACleanup();
		}
		if (send(sockClient, sendstr, strlen(sendstr)+1, 0) <= 0)
		{
			cout << "send失败,可能连接断开" << endl;
			continue;
		}
		//接收服务端应答
		memset(recstr, '\0', COMLEN);
		if (recv(sockClient, recstr, COMLEN, 0) <= 0)
		{
			cout << "recv失败,可能连接断开" << endl;
			continue;
		}
		serverinfo.overtime = 0;
		//cout << "rec：";
		//printf("rec[%d %d]\n", recstr[0], recstr[1]);

		switch (recstr[0])
		{
		case TASKSUCCEED:
			//printf("请求成功");
			switch (tmp.IOCTL)
			{
			case INPUTSAVE:
				printf("最近的模块编号是:%2d\n", atoi(recstr+2));
				break;
			case OUTPUTDELE:
				double times;
				double spend;
				sscanf(recstr + 1, "%lf %lf", &times, &spend);
				printf("已存 %.0f分钟 每分钟收费 %.1f元 收费 %.f元\n", times, spend,times*spend);
				break;
			case OUTPUTGARAGE:
				printf("最近的出口编号是:%2d\n", atoi(recstr + 2));
				break;
			case PANTBAG:
				sscanf(recstr + 1, "%d %d", &serverinfo.sumCar, &serverinfo.freeCar);
				//printf("总车位 %3d 空闲车位 %3d\n", serverinfo.sumCar, serverinfo.freeCar);
				break;
			default:
				printf("未定义\n");
			}
			break;
		case NOCAR:
			printf("车位已满\n");
			break;
		case GARAGEBUSY:
			printf("无空闲模块\n");
			break;
		case NOTFOUND:
			printf("未找到车辆\n");
			break;
		case PLATEREPEAT:
			printf("车牌重复\n");
			break;
		case NOTOUTPUT:
			printf("未找到出口\n");
			break;
		case NOTDEFINE:
			printf("未定义的请求\n");
			break;
		case TASKFAIL:
			printf("请求失败\n");
			break;
		default:
			printf("未知\n");
		}

		serverinfo.command.pop();
		closesocket(sockClient);
		WSACleanup();
	}

	return 0;
}
