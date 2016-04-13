/**************************************
 *FILE    :D:\c\car\parking management\CCarbarnInfo.h
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

#if !defined(_CCARBARNINFO_)
#define _CCARBARNINFO_

#include "StdAfx.h"
#include "DataStructure.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

//��λ��Ϣ
struct speed_location
{
	double time;                       //����ʱ��
	int    idle;                       //����״̬
		                               //0:����
	                                   //1:ռ��
	                                   //2:���
	int    id;                         //���
};

class CCarbarnInfo
{
private:
	int    carbarnid;                  //������
	string name;                       //������
	int    nowstatus;                  //��״̬
	char   command[COMLEN];            //������� ��/ȡ1�ֽ� ����2�ֽ� 
	char   sqlcommand[COMLEN];         //sql����
	/*1.��ӣ���q.push(x):��xԪ�ؽӵ����е�ĩ�ˣ�
	2.���ӣ���q.pop() �������еĵ�һ��Ԫ�أ������᷵��Ԫ�ص�ֵ��
	3,���ʶ���Ԫ�أ���q.front()
	4,���ʶ�βԪ�أ���q.back();
	5,���ʶ��е�Ԫ�ظ�������q.size();
	*/
	int    spendtime;                  //�����ʱ
	int    sumcar;                     //�ܴ泵��
	int    spendcar;                   //�Ѵ泵��
	int    map_rows;                   //�ڼ���
	int    map_cols;                   //�ڼ���
	int    rows;                       //��
	int    cols;                       //��
	double speed_rows;                 //�����ƶ��ٶ�
	double speed_cols;                 //�����ƶ��ٶ�
	vector <speed_location> map_queue; //λ���б�

public:
	CCarbarnInfo();
	~CCarbarnInfo();
	//////////////////////////////////////////////////////////////////////////
	//��������ͦ���۵�
	//int checkfist();                 //����Ƿ��ʼ��
	//int readdate();                  //���ļ���ȡ����
	//////////////////////////////////////////////////////////////////////////
	int    readdate(int carbarnid);    //��mysql��ȡ������Ϣ
	int    judgeposition(int num);     //��ȡ����״̬
	                                   //0:����
	                                   //1:ռ��
	                                   //2:���
	int    getid(int num);             //��ȡid
	int    combine(int id,int idle);   //�ϲ�id�Ϳ���״̬
	int    getcarbarnid();             //��ȡ���
	void   setcarbarnid(int carbarnid);//���ñ��
	string getname();                  //��ȡģ����
	void   setname(string name);       //����ģ����
	int    getnowstatus();             //��ȡ��ǰ״̬
	void   setnowstatus(int status);   //���õ�ǰ״̬
	void   setoffline();               //��Ϊ����״̬
	//int    getoldstatus();           //��ȡ��һ״̬
	//void   setoldstatus(int status); //������һ״̬
	void   getcommand(char* str);              //��ȡ����
	void   setcommand(const char str[]);       //��������
	void   setsqlcommand(const char str[]);    //����sql����
	void   getsqlcommand(char* str);           //��ȡsql����
	int    getusernum();               //��ȡ�ȴ��û���
	int    getspendtime();             //��ȡ����ʱ��
	void   accspendtime();             //�ۼ�ʱ��
	void   setzerospendtime();         //����
	int    getsumcar();                //��ȡ����
	int    getspendcar();              //��ȡ�Ѵ泵��
	int    getrows();                  //��ȡ������
	void   setrows(int rows);          //���ó�����
	int    getcols();                  //��ȡ������
	void   setcols(int cols);          //���ó�����
	double getspeedrows();             //��ȡ�����ƶ��ٶ�
	void   setspeedrows(double rows);  //���ú����ƶ��ٶ�
	double getspeedcols();             //��ȡ�����ƶ��ٶ�
	void   setspeedcols(double cols);  //���������ƶ��ٶ�
	int    getrows(int location);      //��ȡlocation����
	int    getcols(int location);      //��ȡlocation����
	int    countqueue();               //������ʱ���С��������
	int    findemptycarport();         //��������ĳ�λ,δ�ҵ�����-1
	int    findemptycarid();           //��������ĳ�λ��,δ�ҵ�����-1
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
	int    savecar();                  //�泵,δ�ҵ�����-1
	int    deletecar(int index);       //ȡ��,δ�ҵ�����-1
	//int  savedatetomysql();          //�������ݵ��ļ�
	int    savedatetomysql();          //�������ݵ�mysql
	int    clear();                    //��տ������[�ѷ���]
	void   deletedate();               //ɾ��ģ��[�ѷ���,��webģ��ʵ��]

	/*////////////////////////////////////////////////////////////////////////
	���� setentry(int index)��������ڣ� 
		 cancelentry(int index) ��ȡ����ڣ� 
		 newgarage() �۴��������
		 switchid() ���ⲿ����ת��Ϊ�ڲ������
	*/////////////////////////////////////////////////////////////////////////
	int    setentry(int index);        //�������[�ѷ���,��webģ��ʵ��]
	int    cancelentry(int index);     //ȡ�����[�ѷ���,��webģ��ʵ��]
	int    newgarage();                //����ģ��[�ѷ���,��webģ��ʵ��]
	int    switchid(int index);        //�ⲿ����ת��Ϊ�ڲ�����

	//void putinfo();                  //�����Ϣ[�ն���]
};
#endif

