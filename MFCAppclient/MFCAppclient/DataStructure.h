/**************************************
 *FILE          :T:\car\MFCAppclient\MFCAppclient\DataStructure.h
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/6/18 19:40:21
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

#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include "StdAfx.h"
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define COMLEN 1024                    //����泤��

struct comNode
{
	int  IOCTL;                        //������
	char strplate[COMLEN];             //���ƺ�
	int  ioputid;                      //�����id
};

//ϵͳ����
struct serverset
{
	int    ioId;                       //id
	char   ip[100];                    //������ip
	int    iocpport;                   //socket�˿�
	int    intervaltime;               //��ѯ���

	int    overtime;                   //��ʱʱ��
	int    maxovertime;                //���ʱʱ��

	queue<struct comNode> command;     //�ȴ�����
	char   iobuf[COMLEN];              //���շ����ַ���
};

//�û�����
//����
struct userdata
{
	char name[100];
	int jurisdiction;                  //Ȩ��
};

#endif