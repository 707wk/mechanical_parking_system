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

#ifndef _DataStructure_h_
#define _DataStructure_h_

#include "StdAfx.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ϵͳ����
struct serverset
{
	char   ip[20];                     //���ݿ�ip
	char   name[100];                  //���ݿ��û���
	char   password[100];              //���ݿ�����
	char   database[100];              //���ݿ���
	int    port;                       //���ݿ�˿�
	double cost;                       //����(Ԫ/Сʱ)(����)
	int    mscomm;                     //�˿ں�

	MYSQL  mysql;                      //mysql���ݿ�
};

struct speed_location
{
	double time;                       //����ʱ��
	int idle;                          //����״̬
		                               //0:����
	                                   //1:ռ��
	                                   //2:���
	int id;                            //���
};

struct carbarninfo
{
	int    id;                         //������
	string name;                       //������
	int    nowstatus;                  //��״̬
	int    oldstatus;                  //��һ״̬
	int    sumtotal;                   //��������
	int    spendtotal;                 //�Ѵ泵����
	int    rows;                       //��
	int    cols;                       //��
	double speedrows;                  //���ٶ�
	double speedcols;                  //���ٶ�
	vector <speed_location> map_queue; //λ���б�
};

//�û�����
//����
struct userdata
{
	char name[100];
	int jurisdiction;//Ȩ��
};

#endif