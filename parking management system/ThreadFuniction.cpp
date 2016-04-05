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
#include "parking management system.h"
#include "parking management systemDlg.h"
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

using namespace std;

extern struct serverset serverinfo;

extern HANDLE hCom;  //ȫ�ֱ��������ھ��

extern CCarbarnInfo* garage;

extern int* idtoindex;

extern int sumgarage;

extern int link;

extern CParkingmanagementsystemDlg *dlg;

void OnSend(char* str,int length) 
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
	char strtmp[COMLEN];

	for(;;)
	{
		char str[]="12345";
		if(!link)
		{
			Sleep(1000);
			continue;
		}

		garage[index].getcommand(strtmp);
		if(strtmp[0]=='\0')//����Ϊ��
		{
			str[0]=garage[index].getcarbarnid();
			str[1]=GETSTATE;
			str[2]=0;
			str[3]=0;
			str[4]=(str[0]+str[1]+str[2]+str[3])%CHECKMOD;
			OnSend(str,6);
		}
		else
		{
			str[0]=garage[index].getcarbarnid();
			//tmp=garage[index].getcommand();
			str[1]=strtmp[0];
			str[2]=strtmp[1];
			str[3]=strtmp[2];
			str[4]=(str[0]+str[1]+str[2]+str[3])%CHECKMOD;
			OnSend(str,6);
			garage[index].setcommand("");
		}

		char recstr[COMLEN]="12";

		OnReceive(recstr,2);
		recstr[2]='\0';

		if(recstr[0]<=0)continue;
		if(recstr[0]>sumgarage)continue;
		/////////////////////////////////////////////////////////////////////////////
		int index=idtoindex[recstr[0]];
		char strtmp[COMLEN]="";
		garage[index].getsqlcommand(strtmp);
		garage[index].setnowstatus(recstr[1]);
		if(strtmp[0]!='\0'&&garage[index].getnowstatus()==STATEFREE)
		{
			mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
			garage[index].getsqlcommand(strtmp);
			if(mysql_query(&serverinfo.mysql,strtmp)!=NULL)
			{
				AfxMessageBox("���ݿ�����ʧ��");
				exit(1);
			}
			garage[index].setsqlcommand("");
		}
		/////////////////////////////////////////////////////////////////////////////

		index=(index+1)%sumgarage;
		//Sleep(200);
	}
	
	return 0;
}