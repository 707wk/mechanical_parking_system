/**************************************
 *FILE    :D:\c\car\car_module\car_module.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:33
 *TEXT    :存取车模块
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
		AfxMessageBox("存取车模块:数据库无法连接!");
		return ;
	}
}

management::~management()
{
	mysql_close(&mysql);
}

void management::setfindname(string name)
{
	this->findname=name;
}

//////////////////////////////////////////////////////////////////////////
//蛋蛋的忧伤
string management::getname()
{
	return this->findname;
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

/*////////////////////////////////////////////////////////////////////////
time	timestamp
plate	char
id	int
mac	int
timestatus	int
balancestatus	double
money	double
balance	double
*////////////////////////////////////////////////////////////////////////
int management::savecar(char* str)
{
	string md5str;
	MD5 md5;
	md5.update(str);
	md5str=md5.toString();
	md5.reset();

	CString tmp;
	tmp.Format("select plate from t_carinfo where plate='%s'",str);
	mysql_query(&mysql,tmp.GetBuffer(0));
	res=mysql_store_result(&mysql);
	column=mysql_fetch_row(res);
	if(column)return -1;

	car_module garage;
	garage.readdate(findname);
	index=garage.savecar();
	if(index==-1)
	{
		AfxMessageBox("未找到空闲车位:2");
		return -1;
	}
	rows=garage.getrows(index);
	cols=garage.getcols(index);

	CString insertstr;
	insertstr.Format("INSERT INTO t_carinfo (id,plate,name,number,rows,cols,start) \
VALUES('%s','%s','%s',%d,%d,%d,now())",md5str.c_str(),str,findname.c_str(),index,rows,cols);

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

	//////////////////////////////////////////////////////////////////////////
	insertstr.Format("INSERT INTO t_history (time,plate,id,name,timestatus) \
		VALUES(now(),'%s','%s','%s',%d)",str,md5str.c_str(),findname.c_str(),1);
	
	//AfxMessageBox(insertstr);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,insertstr.GetBuffer(0))==NULL)
	{
	}
	else
	{
		AfxMessageBox("插入失败:3");
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	
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
			findname=column[2];
			index=atoi(column[3]);

			double cost=countmoney(str);

			car_module garage;
			garage.readdate(findname);
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

			//////////////////////////////////////////////////////////////////////////
			insertstr.Format("INSERT INTO t_history (time,plate,id,name,timestatus,balancestatus,money) \
				VALUES(now(),'%s','%s','%s',%d,%d,%lf)",str,md5str.c_str(),findname.c_str(),2,2,cost);
			
			//AfxMessageBox(insertstr);
			mysql_query(&mysql,"SET NAMES 'UTF-8'");
			
			if(mysql_query(&mysql,insertstr.GetBuffer(0))==NULL)
			{
			}
			else
			{
				AfxMessageBox("插入失败:4");
				return -1;
			}
			//////////////////////////////////////////////////////////////////////////

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

double management::countmoney(char* str)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);

	string md5str;
	MD5 md5;
	md5.update(str);
	md5str=md5.toString();
	md5.reset();

	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

/*////////////////////////////////////////////////////////////////////////
	1900+timeinfo->tm_year,
		1+timeinfo->tm_mon,
		timeinfo->tm_mday,
		timeinfo->tm_hour,
		timeinfo->tm_min,
		timeinfo->tm_sec;
*/////////////////////////////////////////////////////////////////////////

	CString selectstr;
	selectstr.Format("select start from t_carinfo where id='%s'",md5str.c_str());

	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,selectstr.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		if(column)
		{
			sscanf(column[0],"%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&min,&sec);
			time_t t1;
			struct tm timeptr1;
			timeptr1.tm_mday=day ;
			timeptr1.tm_mon=month-1;
			timeptr1.tm_year=year-1900;
			timeptr1.tm_sec=sec;
			timeptr1.tm_min=min;
			timeptr1.tm_hour=hour;
			//timeptr1.tm_wday=0;
			//timeptr1.tm_yday=0;
			//timeptr1.tm_isdst=0;

			t1=mktime(&timeptr1);

			return ((difftime(rawtime,t1)-1)/60+1)*serverinfo.cost;
		}
	}
	else
	{
		AfxMessageBox("插入失败:5");
		return -1;
	}

	return -1;
}

