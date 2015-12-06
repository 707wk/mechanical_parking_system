/**************************************
 *FILE    :D:\c\car\parking management\carbarninfo.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/5 19:48:19
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

#if !defined(_CARBARNINFO_)
#define _CARBARNINFO_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <string>
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

class carbarninfo
{
private:
	int    id;                         //������
	string name;                       //������
	int    nowstatus;                  //��״̬
	int    oldstatus;                  //��һ״̬
	string command;                    //����ִ�е�����
	int    sumcar;                     //�ܴ泵��
	int    spendcar;                   //�Ѵ泵��
	int    map_rows;                   //�ڼ���
	int    map_cols;                   //�ڼ���
	int    rows;                       //��
	int    cols;                       //��
	double speed_rows;                 //�����ƶ��ٶ�
	double speed_cols;                 //�����ƶ��ٶ�
	vector <speed_location> map_queue; //λ���б�
	//MYSQL  mysql;                      //mysql���ݿ�
	//MYSQL_RES *res;                  //��ѯ�����
	//MYSQL_ROW column;                //�����е���

public:
	carbarninfo();
	~carbarninfo();
	//////////////////////////////////////////////////////////////////////////
	//��������ͦ���۵�
	//int checkfist();                 //����Ƿ��ʼ��
	//int readdate();                  //���ļ���ȡ����
	//////////////////////////////////////////////////////////////////////////
	int readdate(string name);         //��mysql��ȡ������Ϣ
	int judgeposition(int num);        //��ȡ����״̬
	                                   //0:����
	                                   //1:ռ��
	                                   //2:���
	void setcompotr(int num);          //���ö˿ں�
	int getcompotr();                  //��ȡ�˿ں�
	int getid(int num);                //��ȡid
	int getcond(int num);              //��ȡ״̬
	int combine(int id,int idle);      //�ϲ�id�Ϳ���״̬
	string getname();                  //��ȡģ����
	void setname(string name);         //����ģ����
	int getsumcar();                   //��ȡ����
	int getspendcar();                 //��ȡ�Ѵ泵��
	int getcondition();                //��ȡ״̬
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
	int savedatetomysql(string name);  //�������ݵ�mysql
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

	//void putinfo();                  //�����Ϣ[�ն���]
};
#endif
