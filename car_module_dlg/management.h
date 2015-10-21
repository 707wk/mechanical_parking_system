/**************************************
 *FILE    :D:\c\car\car_module\car_module.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:13
 *TEXT    :��ȡ��ģ��
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

#if !defined(_MANAGEMENT_)
#define _MANAGEMENT_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class management
{
private:
	int findmac;                       //��ʱmac
	int index;                         //��ʱ���
	int rows;                          //��ʱ������
	int cols;                          //��ʱ������
	MYSQL mysql;                       //mysql���ݿ�
	MYSQL_RES *res;                    //��ѯ�����
	MYSQL_ROW column;                  //�����е���

public:
	management();
	~management();

	void setfindmac(int mac);          //����mac
	int getmac();                      //����mac
	int getindex();                    //�������
	int getrows();                     //����rows
	int getcols();                     //����cols

	//////////////////////////////////////////////////////////////////////////
	/*�泵
	{
		��ȡcarid
			int mac=���������ͣ����
			int index=����mac��������ͣ����
			��index�������������
			�洢�����ݿ�
	}
	
	ȡ��
	{
		��ȡcarid
			int mac=carid.mac
			int index=(carid.rows-1)*cols+carid.cols;
		ɾ��������¼
	}
	*/////////////////////////////////////////////////////////////////////////
	int savecar(char* str);            //�泵,δ�ҵ�����-1
	int deletecar(char* str);          //ȡ��,δ�ҵ�����-1
	double countmoney(char* str);      //ͳ�Ʒ���

	//void AfxMessageBox(char* str);
};
#endif

/*////////////////////////////////////////////////////////////////////////
id    	int
mac	    int
index	int
rows	int
cols	int
*/////////////////////////////////////////////////////////////////////////
