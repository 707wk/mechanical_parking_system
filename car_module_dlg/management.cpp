/**************************************
 *FILE    :D:\c\car\car_module\car_module.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:33
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
#include "StdAfx.h"
#include "management.h"
#include "DataStructure.h"
#include "md5.h"
#include "car_module.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

extern struct serverset serverinfo;

management::management()
{
	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		AfxMessageBox("数据库无法连接!");
		return ;
	}
}

management::~management()
{
	mysql_close(&mysql);
}

void management::setfindmac(int mac)
{
	this->findmac=mac;
}

//////////////////////////////////////////////////////////////////////////
//蛋蛋的忧伤
int management::getmac()
{
	return this->findmac;
}

int management::getindex()
{
	return this->index;
}

int management::getrows()
{
	return this->rows;
}

int management::getcols()
{
	return this->cols;
}
//////////////////////////////////////////////////////////////////////////

int management::savecar(char* str)
{
	string md5str;
	MD5 md5;
	md5.update(str);
	md5str=md5.toString();
	md5.reset();

	car_module garage;
	garage.readdate(findmac);
	index=garage.savecar();
	if(index==-1)
	{
		AfxMessageBox("未找到空闲车位:2");
		return -1;
	}
	rows=garage.getrows(index);
	cols=garage.getcols(index);

	CString insertstr;
	insertstr.Format("INSERT INTO t_carinfo (id,plate,mac,number,rows,cols) \
VALUES('%s','%s',%d,%d,%d,%d)",md5str.c_str(),str,findmac,index,rows,cols);

	//AfxMessageBox(insertstr);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,insertstr.GetBuffer(0))==NULL)
	{
	}
	else
	{
		AfxMessageBox("插入失败:2");
		return -1;
	}
	
	return index;
}

int management::deletecar(char* str)
{
	string md5str;
	MD5 md5;
	md5.update(str);
	md5str=md5.toString();
	md5.reset();
	
	CString insertstr;
	insertstr.Format("select * from t_carinfo where id='%s'",md5str.c_str());

	//AfxMessageBox(str);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,insertstr.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		if(column)
		{
			findmac=atoi(column[2]);
			index=atoi(column[3]);

			car_module garage;
			garage.readdate(findmac);
			garage.deletecar(index);

			CString deletestr;
			deletestr.Format("DELETE FROM t_carinfo where id='%s'",md5str.c_str());

			//AfxMessageBox(deletestr);
			if(mysql_query(&mysql,deletestr.GetBuffer(0))==NULL)
			{
			}
			else
			{
				AfxMessageBox("删除失败:1");
				return -1;
			}

			return index;
		}
		else
		{
			AfxMessageBox("readdate:未找到数据:3");
			return -1;
		}
	}
	else
	{
		AfxMessageBox("查找失败");
		return -1;
	}
}

