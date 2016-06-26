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
			AfxMessageBox(_T("WSAStartupʧ��"));
			exit(1);
		}

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			AfxMessageBox(_T("SOCKET�汾����"));
			WSACleanup();
			exit(1);
		}

		SOCKET sockClient;
		struct sockaddr_in addrServer;
		sockClient = socket(AF_INET, SOCK_STREAM, 0);
		if (sockClient == INVALID_SOCKET)
		{
			cout << "socket ʧ��" << endl;
			WSACleanup();
			return FALSE;
		}
		memset(&addrServer, 0, sizeof(sockaddr_in));

		addrServer.sin_family = AF_INET;
		addrServer.sin_addr.s_addr = inet_addr(serverinfo.ip);
		addrServer.sin_port = htons(serverinfo.iocpport);

		if (connect(sockClient, (const struct sockaddr*)&addrServer, sizeof(sockaddr)) != 0)
		{
			cout << "connect ʧ��" << endl;
			continue;
			WSACleanup();
		}
		if (send(sockClient, sendstr, strlen(sendstr)+1, 0) <= 0)
		{
			cout << "sendʧ��,�������ӶϿ�" << endl;
			continue;
		}
		//���շ����Ӧ��
		memset(recstr, '\0', COMLEN);
		if (recv(sockClient, recstr, COMLEN, 0) <= 0)
		{
			cout << "recvʧ��,�������ӶϿ�" << endl;
			continue;
		}
		serverinfo.overtime = 0;
		//cout << "rec��";
		//printf("rec[%d %d]\n", recstr[0], recstr[1]);

		switch (recstr[0])
		{
		case TASKSUCCEED:
			//printf("����ɹ�");
			switch (tmp.IOCTL)
			{
			case INPUTSAVE:
				printf("�����ģ������:%2d\n", atoi(recstr+2));
				break;
			case OUTPUTDELE:
				double times;
				double spend;
				sscanf(recstr + 1, "%lf %lf", &times, &spend);
				printf("�Ѵ� %.0f���� ÿ�����շ� %.1fԪ �շ� %.fԪ\n", times, spend,times*spend);
				break;
			case OUTPUTGARAGE:
				printf("����ĳ��ڱ����:%2d\n", atoi(recstr + 2));
				break;
			case PANTBAG:
				sscanf(recstr + 1, "%d %d", &serverinfo.sumCar, &serverinfo.freeCar);
				//printf("�ܳ�λ %3d ���г�λ %3d\n", serverinfo.sumCar, serverinfo.freeCar);
				break;
			default:
				printf("δ����\n");
			}
			break;
		case NOCAR:
			printf("��λ����\n");
			break;
		case GARAGEBUSY:
			printf("�޿���ģ��\n");
			break;
		case NOTFOUND:
			printf("δ�ҵ�����\n");
			break;
		case PLATEREPEAT:
			printf("�����ظ�\n");
			break;
		case NOTOUTPUT:
			printf("δ�ҵ�����\n");
			break;
		case NOTDEFINE:
			printf("δ���������\n");
			break;
		case TASKFAIL:
			printf("����ʧ��\n");
			break;
		default:
			printf("δ֪\n");
		}

		serverinfo.command.pop();
		closesocket(sockClient);
		WSACleanup();
	}

	return 0;
}
