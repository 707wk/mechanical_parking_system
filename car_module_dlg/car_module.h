/**************************************
 *FILE    :D:\c\car\car_module\car_module.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:13
 *TEXT    :NULL
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

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct speed_location
{
	double time;                       //����ʱ��
	int idle;                          //����״̬
	int id;                            //���
};

class car_module
{
private:
	int mac;                           //����ģ���ַ
	int sumcar;                        //�ܴ泵��
	int spendcar;                      //�Ѵ泵��
	int condition;                     //״̬
	int rows;                          //��
	int cols;                          //��
	double speed_rows;                 //���ٶ�
	double speed_cols;                 //���ٶ�
	vector <speed_location> map_queue; //λ���б�

public:
	int readdate();
	int readdate(int mac);             //��mysql��ȡ������Ϣ

	int judgeposition(int num);        //��ȡ����״̬
	                                   //0:����
	                                   //1:ռ��
	                                   //2:���
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
	int savecar();                     //�泵
	int deletecar(int index);          //ȡ��
	int savedatetomysql();             //�������ݵ�mysql
	int clear();                       //��տ������

	void putinfo();
};
#endif
