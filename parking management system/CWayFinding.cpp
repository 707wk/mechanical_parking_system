/**************************************
 *FILE          :C:\Users\707wk\Desktop\CWayFinding.cpp
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/3/26 下午 10:49:09
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

data = new double*[m]; //设置行 或直接double **data=new double*[m]; 一个指针指向一个指针数组。

for(int j=0;j<m;j++)
{
data[j] = new double[n];        //这个指针数组的每个指针元素又指向一个数组。
}

for (int i=0;i<m;i++)

{
   for (int j=0;j<n;j++)
   {
    data[i][j]=i*n+j;//初始化数组元素
   }

}

for (i=0;i<m;i++)
{
 delete[] data[i]; //先撤销指针元素所指向的数组
}                     
delete[] data; */

CWayFinding::CWayFinding()
{
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	CString str;
	
	initmap();

	//////////////////////////////////////////////////////////////////////////
	str="select max(x) from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		
		if(column)
		{
			map_x=atoi(column[0]);
		}
		else
		{
			AfxMessageBox("map:未找到数据");
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	str="select max(y) from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		
		if(column)
		{
			map_y=atoi(column[0]);
		}
		else
		{
			AfxMessageBox("map:未找到数据");
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	str="select x,y,type,type_id from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result

		int tmpx;
		int tmpy;
		
		while(column=mysql_fetch_row(res))        //获取具体的数据
		{
			tmpx    =atoi(column[0]);
			tmpy    =atoi(column[1]);

			maplocation[tmpx][tmpy].type=atoi(column[2]);
			maplocation[tmpx][tmpy].id  =atoi(column[3]);
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
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
	queue<mapway> pathanalysis;        //寻路变量
	return -1;
}

int CWayFinding::nearestexit(struct mapway start)
{
	queue<mapway> pathanalysis;        //寻路变量
	return -1;
}
