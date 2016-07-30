/**************************************
 *FILE    :D:\c\car\parking management\DataStructure.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/4 21:12:25
 *TEXT    :�ṹͷ�ļ�
 *EMAIL   :gtsoft_wk@foxmail.com
 *CODE    :https://github.com/707wk
 *LOGO    :
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
      #####      ;###        ###      #        
        ##       ####        ####              
***************************************/

#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include "StdAfx.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define COMLEN 1024                    //����泤��

//ϵͳ����
struct serverset
{
	char   ip[100];                    //���ݿ�ip
	char   name[100];                  //���ݿ��û���
	char   password[100];              //���ݿ�����
	char   database[100];              //���ݿ���
	int    dataport;                   //���ݿ�˿�
	int    iocpport;                   //socket�˿�
	double cost;                       //����(Ԫ/Сʱ)(����)
	int    reservationtime;            //ԤԼʱ��

	char   mscomm[255];                //�˿ں�
	char   mscommini[100];             //���Ӳ���
	int    BaudRate;                   //������Ϊ9600
	int    ByteSize;                   //ÿ���ֽ���8λ
	int    Parity;                     //����żУ��λ
	int    StopBits;                   //����ֹͣλ

	int    intervaltime;               //��ѯ���

	int    sumcar;                     //�ܳ�λ
	int    spendcar;                   //�Ѵ泵����
	int    reservation;                //ԤԼ������

	int    Threadsum;                  //�����߳���
	DWORD  Threadwork;                 //�쳣�߳���
	DWORD  activeThreadtime;           //�߳�����ʱ��

	int    runstate;                   //����״̬
	//int  lockflage;                  //��д��
	char   locationip[40];             //����ip
	
	MYSQL  mysql;                      //mysql���ݿ�
};

//�û�����
//����
struct userdata
{
	char name[100];
	int jurisdiction;                  //Ȩ��
};

//����ģ��id���ұ�
struct idLUT
{
	int id;                            //����id
	int index;                         //�ڶ����е�λ��
};

#endif