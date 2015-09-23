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
	int rows;                          //��
	int cols;                          //��
	double speed_rows;                 //���ٶ�
	double speed_cols;                 //���ٶ�
	vector <speed_location> map_queue; //λ���б�

public:
	int readdate();

	int judgeposition(int num);        //��ȡ����״̬
	int getid(int num);                //��ȡid
	int getmac();                      //��ȡģ���ַ
	void setmac(int mac);              //����ģ���ַ
	int getrows();                     //��ȡ������
	void setrows(int rows);            //���ó�����
	int getcols();                     //��ȡ������
	void setcols(int cols);            //���ó�����
	double getspeedrows();             //��ȡ���ƶ��ٶ�
	void setspeesrows(double rows);    //�������ƶ��ٶ�
	double getspeedcols();             //��ȡ���ƶ��ٶ�
	void setspeedcols(double cols);    //�������ƶ��ٶ�
	int getrows(int location);         //��ȡlocation����
	int getcols(int location);         //��ȡlocation����
	int countqueue();                  //������ʱ���С��������
	int findemptycarport();            //��������ĳ�λ,δ�ҵ�����-1
	int savecar();                     //�泵
	void savedatetomysql();            //�������ݵ�mysql

	void putinfo();
};
#endif
