/**************************************
 *FILE          :C:\Users\707wk\Desktop\CWayFinding.h
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/3/26 ���� 10:49:16
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


#if !defined(_CWAYFINDING_)
#define _CWAYFINDING_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

//��ͼ����
struct maptype
{
	int type;                          //����
                                       //"0">ǽ��
                                       //"1">���
                                       //"2">����
                                       //"3">����ģ��
                                       //"4">��·
	int id;                            //���
	int flage;                         //�Ƿ��Ѿ���
};

//��ͼ·��
struct mapway
{
	int x;                             //������
	int y;                             //������
};

class CWayFinding
{
private:
	int map_x;                         //��ͼ��
	int map_y;                         //��ͼ��
	struct maptype** maplocation;      //��ͼ��¼

public:
	CWayFinding();
	~CWayFinding();

	void initmap();                    //��ʼ��ͼ����
	int nearestcarport(int id);        //�����������
	int nearestexit(int id);           //�����������
	void putinfo();                    //�����ͼ
	void clearflage();                 //��ձ�־λ
};
#endif

