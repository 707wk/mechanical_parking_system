/**************************************
 *FILE          :C:\Users\707wk\Desktop\CWayFinding.cpp
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/3/26 ���� 10:49:09
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

#include "StdAfx.h"
#include "CWayFinding.h"
#include "DataStructure.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

extern struct serverset serverinfo;

/* double **data;

data = new double*[m]; //������ ��ֱ��double **data=new double*[m]; һ��ָ��ָ��һ��ָ�����顣

for(int j=0;j<m;j++)
{
data[j] = new double[n];        //���ָ�������ÿ��ָ��Ԫ����ָ��һ�����顣
}

for (int i=0;i<m;i++)

{
   for (int j=0;j<n;j++)
   {
    data[i][j]=i*n+j;//��ʼ������Ԫ��
   }

}

for (i=0;i<m;i++)
{
 delete[] data[i]; //�ȳ���ָ��Ԫ����ָ�������
}                     
delete[] data; */

CWayFinding::CWayFinding()
{
	MYSQL_RES *res;                    //��ѯ�����
	MYSQL_ROW column;                  //�����е���
	CString str;
	
	initmap();

	//////////////////////////////////////////////////////////////////////////
	str="select max(x) from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result
		column=mysql_fetch_row(res);//��ȡ���������
		
		if(column)
		{
			map_x=atoi(column[0]);
		}
		else
		{
			AfxMessageBox("map:δ�ҵ�����");
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox("���ݿ�����ʧ��");
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	str="select max(y) from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result
		column=mysql_fetch_row(res);//��ȡ���������
		
		if(column)
		{
			map_y=atoi(column[0]);
		}
		else
		{
			AfxMessageBox("map:δ�ҵ�����");
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox("���ݿ�����ʧ��");
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	str="select x,y,type,type_id from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result

		int tmpx;
		int tmpy;
		
		while(column=mysql_fetch_row(res))        //��ȡ���������
		{
			tmpx    =atoi(column[0]);
			tmpy    =atoi(column[1]);

			maplocation[tmpx][tmpy].type=atoi(column[2]);
			maplocation[tmpx][tmpy].id  =atoi(column[3]);
		}
	}
	else
	{
		AfxMessageBox("���ݿ�����ʧ��");
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////
}

CWayFinding::~CWayFinding()
{
}

void CWayFinding::initmap()
{
	for(int i=0;i<map_y;i++)
	{
		for(int j=0;j<map_x;j++)
		{
			maplocation[i][j].flage=0;
		}
	}
}

int CWayFinding::nearestcarport(struct mapway start)
{
	queue<mapway> pathanalysis;        //Ѱ·����
	return -1;
}

int CWayFinding::nearestexit(struct mapway start)
{
	queue<mapway> pathanalysis;        //Ѱ·����
	return -1;
}
