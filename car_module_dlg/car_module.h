/**************************************
 *FILE    :D:\c\car\car_module\car_module.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:13
 *TEXT    :����ģ��:ֻ���𳵿���Ϣ
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

#if !defined(_CAR_MODULE_)
#define _CAR_MODULE_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct speed_location
{
	double time;                       //����ʱ��
	int idle;                          //����״̬
		                               //0:����
	                                   //1:ռ��
	                                   //2:���
	int id;                            //���
};

class car_module
{
private:
	int mac;                           //����ģ���ַ
	int sumcar;                        //�ܴ泵��
	int spendcar;                      //�Ѵ泵��
	int compotr;                       //�˿ں�
	int condition;                     //״̬
	int rows;                          //��
	int cols;                          //��
	double speed_rows;                 //���ٶ�
	double speed_cols;                 //���ٶ�
	vector <speed_location> map_queue; //λ���б�
	int status;
	MYSQL mysql;                       //mysql���ݿ�
	MYSQL_RES *res;                    //��ѯ�����
	MYSQL_ROW column;                  //�����е���

public:
	car_module();
	~car_module();
	//////////////////////////////////////////////////////////////////////////
	//��������ͦ���۵�
	//int checkfist();                   //����Ƿ��ʼ��
	//int readdate();                    //���ļ���ȡ����
	//////////////////////////////////////////////////////////////////////////
	int readdate(int mac);             //��mysql��ȡ������Ϣ

	int getstatus();                   //��ȡ״̬
	int judgeposition(int num);        //��ȡ����״̬
	                                   //0:����
	                                   //1:ռ��
	                                   //2:���
	void setcompotr(int num);          //���ö˿ں�
	int getcompotr();                  //��ȡ�˿ں�
	int getid(int num);                //��ȡid
	int getcond(int num);              //��ȡ״̬
	int combine(int id,int idle);      //�ϲ�id�Ϳ���״̬
	int getmac();                      //��ȡģ���ַ
	void setmac(int mac);              //����ģ���ַ
	int getsumcar();                   //��ȡ����
	int getspendcar();                 //��ȡ�Ѵ泵��
	int getcondition();                //��ȡ��ǰ״̬
	void setconditopn(int num);        //����״̬
	int getrows();                     //��ȡ������
	void setrows(int rows);            //���ó�����
	int getcols();                     //��ȡ������
	void setcols(int cols);            //���ó�����
	double getspeedrows();             //��ȡ���ƶ��ٶ�
	void setspeedrows(double rows);    //�������ƶ��ٶ�
	double getspeedcols();             //��ȡ���ƶ��ٶ�
	void setspeedcols(double cols);    //�������ƶ��ٶ�
	int getrows(int location);         //��ȡlocation����
	int getcols(int location);         //��ȡlocation����
	int countqueue();                  //������ʱ���С��������
	int findemptycarport();            //��������ĳ�λ,δ�ҵ�����-1
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
	int savecar();                     //�泵,δ�ҵ�����-1
	int deletecar(int index);          //ȡ��,δ�ҵ�����-1
	//int savedatetomysql();           //�������ݵ��ļ�
	int savedatetomysql(int mac);      //�������ݵ�mysql
	int clear();                       //��տ������[�ѷ���]
	void deletedate();                 //ɾ��ģ��

	/*////////////////////////////////////////////////////////////////////////
	���� setentry(int index)��������ڣ� 
		 cancelentry(int index) ��ȡ����ڣ� 
		 newgarage() �۴��������
		 switchid() ���ⲿ����ת��Ϊ�ڲ������
	*/////////////////////////////////////////////////////////////////////////
	int setentry(int index);           //�������
	int cancelentry(int index);        //ȡ�����
	int newgarage();                   //��������
	int switchid(int index);           //�ⲿ����ת��Ϊ�ڲ�����

	//void putinfo();                    //�����Ϣ[�ն���]
};
#endif
