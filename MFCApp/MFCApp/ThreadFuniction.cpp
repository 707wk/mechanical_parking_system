/**************************************
 *FILE          :C:\Users\707wk\Desktop\CWayFinding.cpp
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/3/26 ���� 10:49:09
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
#include "MFCApp.h"
#include "MFCAppDlg.h"
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "DataStructure.h"
#include "ControlCode.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <time.h>

using namespace std;

extern struct serverset serverinfo;

extern HANDLE hCom;  //ȫ�ֱ��������ھ��

extern DCB dcb;

extern CCarbarnInfo* garage;

extern int reservation;

extern int* idtoindex;

extern int maxindex;

extern int sumgarage;

extern int link;

extern CMFCAppDlg *dlg;

void OnSendBit(char* str,int length) 
{
	// TODO: Add your control notification handler code here
	OVERLAPPED m_osWrite;
	memset(&m_osWrite,0,sizeof(OVERLAPPED));
	m_osWrite.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	
	DWORD dwBytesWrite=length;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	BOOL bWriteStat;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	bWriteStat=WriteFile(hCom,str,
		dwBytesWrite,& dwBytesWrite,&m_osWrite);
	
	if(!bWriteStat)
	{
		if(GetLastError()==ERROR_IO_PENDING)
		{
			WaitForSingleObject(m_osWrite.hEvent,1000);
		}
	}
	else
	{
		AfxMessageBox(_T("OnSend:�����ѶϿ�"));
		exit(1);
	}
}

void OnSend(char* str,int length) 
{
	// TODO: Add your control notification handler code here

	//char qwe1[255];
	//sprintf(qwe1,"send:%2d %2d %2d %2d %2d",str[0],str[1],str[2],str[3],str[4]);
	//dlg->setinfo(qwe1);

	//GetCommState(hCom,&dcb);
	//dcb.Parity  =SPACEPARITY;   //��żλΪ0
	//SetCommState(hCom,&dcb);

	//OnSendBit(str,1);
	//PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);

	//GetCommState(hCom,&dcb);
	//dcb.Parity  =MARKPARITY;   //��żλΪ1
	//SetCommState(hCom,&dcb);
	
	//OnSendBit(str+1,length-1);
	//PurgeComm(hCom,PURGE_TXCLEAR|PURGE_RXCLEAR);

	//dcb.Parity  =NOPARITY;   //��żλ
	//SetCommState(hCom,&dcb);
	
	printf("send:%02X-%02X-%02X-%02X-%02X-%02X-%02X\n", 
		(unsigned char)str[0], 
		(unsigned char)str[1], 
		(unsigned char)str[2], 
		(unsigned char)str[3], 
		(unsigned char)str[4], 
		(unsigned char)str[5], 
		(unsigned char)str[6]);

	OnSendBit(str,length);
}

void OnReceive(char (&str)[COMLEN],int length) 
{
	// TODO: Add your control notification handler code here
	OVERLAPPED m_osRead;
	memset(&m_osRead,0,sizeof(OVERLAPPED));
	m_osRead.hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
	
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	
	memset(str,'\0',COMLEN);
	DWORD dwBytesRead=length;//��ȡ���ֽ���
	BOOL bReadStat;
	
	ClearCommError(hCom,&dwErrorFlags,&ComStat);

	if(!ComStat.cbInQue)// ������������
	{
		//strcpy(str,"\0\0\0");
        return ;
	}

	dwBytesRead=min(dwBytesRead, (DWORD)ComStat.cbInQue);
	bReadStat=ReadFile(hCom,str,
		dwBytesRead,&dwBytesRead,&m_osRead);
	if(!bReadStat)
	{
		if(GetLastError()==ERROR_IO_PENDING)
			//GetLastError()��������ERROR_IO_PENDING,�����������ڽ��ж�����
		{
			WaitForSingleObject(m_osRead.hEvent,2000);
			//ʹ��WaitForSingleObject�����ȴ���ֱ����������ɻ���ʱ�Ѵﵽ2����
			//�����ڶ�����������Ϻ�m_osRead��hEvent�¼����Ϊ���ź�
		}
	}
	
	PurgeComm(hCom, PURGE_TXABORT|
		PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
}

DWORD WINAPI ThreadPoll(LPVOID pParam)
{
	int index=0;
	int command_flage=0;
	char strtmp[COMLEN];

	time_t nowtime;
	struct tm local;
//	char qwe1[255];

	for(;link!=-1;index=(index+1)%sumgarage)
	{
		char str[]="1234567";

		str[0] = ADDFIRST;
		str[2] = ADDEND;

		if(!link)
		{
			Sleep(1000);
			continue;
		}

		garage[index].getcommand(strtmp);
		if(strtmp[0]=='\0')//����Ϊ��
		{
			str[1]=garage[index].getcarbarnid();
			str[3]=GETSTATE;
			str[4]=0;
			str[5]=0;
			str[6]=(str[1]+str[3]+str[4]+str[5])%CHECKMOD;
			OnSend(str,7);

			command_flage=0;
		}
		else
		{
			str[1]=garage[index].getcarbarnid();
			str[3]=strtmp[0];
			str[4]=strtmp[1];
			str[5]=strtmp[2];
			str[6]=(str[1]+str[3]+str[4]+str[5])%CHECKMOD;
			OnSend(str,7);
			//garage[index].setcommand("");

			nowtime = time(NULL);  
			localtime_s(&local,&nowtime);
			
			printf("[%02d:%02d:%02d] sen:%02X-%02X-%02X-%02X-%02X\n",
				local.tm_hour,local.tm_min,local.tm_sec,str[1],str[3],str[4],str[5],str[6]);
//			dlg->setinfo(qwe1);

			command_flage=1;
		}

		Sleep(100);
		char recstr[COMLEN];
		memset(recstr,'\0',COMLEN);
		
		OnReceive(recstr,4);
		//recstr[2]='\0';

		//////////////////////////////////////////////////////////////////////////
		//�жϽ����Ƿ�Ϸ�
		if(recstr[0]==0)
		{
			continue;
		}

		nowtime = time(NULL);  
		localtime_s(&local,&nowtime);
		
		printf("[%02d:%02d:%02d] rev:%02X-%02X-%02X-%02X\n",
			local.tm_hour,local.tm_min,local.tm_sec,recstr[0],recstr[1],recstr[2],recstr[3]);//*/
//		dlg->setinfo(qwe1);

		if(command_flage&&recstr[1]==ACCEPTED)
		{
			garage[index].setcommand("");
		}
		
		if(recstr[0]<0)
		{
			continue;
		}

		if(recstr[0]>maxindex)
		{
			continue;
		}

		if(idtoindex[recstr[0]]==-1)
		{
			continue;
		}
		//////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////
		//int index=idtoindex[recstr[0]];
		char strtmp[COMLEN]="";
		garage[idtoindex[recstr[0]]].getsqlcommand(strtmp);
		garage[idtoindex[recstr[0]]].setnowstatus(recstr[1]);

		if(strtmp[0]!='\0'&&garage[idtoindex[recstr[0]]].getnowstatus()==STATEFREE)
		{
			mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
			garage[idtoindex[recstr[0]]].getsqlcommand(strtmp);
			if(mysql_query(&serverinfo.mysql,strtmp)!=NULL)
			{
				AfxMessageBox(_T("ThreadPoll:���ݿ�����ʧ��"));
				exit(1);
			}
			garage[idtoindex[recstr[0]]].setsqlcommand("");
		}
		/////////////////////////////////////////////////////////////////////////////
		Sleep(serverinfo.intervaltime);

		//index=(index+1)%sumgarage;
		//Sleep(200);
	}
	
	return 0;
}