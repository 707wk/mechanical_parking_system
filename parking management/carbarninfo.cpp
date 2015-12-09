/**************************************
 *FILE    :D:\c\car\parking management\carbarninfo.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/5 19:48:09
 *TEXT    :车库模块:负责车库信息
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
#include "carbarninfo.h"
#include "DataStructure.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

extern MYSQL mysql;

carbarninfo::carbarninfo()
{
	this->carbarnid=0;
	this->nowstatus=-1;
	this->oldstatus=-1;
	this->sumcar=0;
	this->spendcar=0;
	this->rows=0;
	this->cols=0;
	this->speed_rows=0;
	this->speed_cols=0;
}

carbarninfo::~carbarninfo()
{
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));
}

int carbarninfo::readdate(int carbarnid)
{
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
	CString str;
	str.Format("select name,nowstatus,oldstatus,command,spendtime,rows,cols,speedrows,speedcols,map_queue from t_garageinfo where carbarnid='%d'",carbarnid);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		
		if(column)
		{
			//////////////////////////////////////////////////////////////////////////
			//忘保存编号了...
			this->carbarnid=carbarnid;
			//////////////////////////////////////////////////////////////////////////
			this->name=column[0];
			this->nowstatus=atoi(column[1]);
			this->oldstatus=atoi(column[2]);
			this->command.push(column[3]);
			this->spendtime=atoi(column[4]);
			this->sumcar=0;
			this->spendcar=0;
			this->rows=atoi(column[5]);
			this->cols=atoi(column[6]);
			this->speed_rows=atof(column[7]);
			this->speed_cols=atof(column[8]);

			if(column[9]==NULL)return -1;
			string tmpstr=column[9];

			if(rows<0)return -1;
			if(cols<0)return -1;

			stringstream stream;
			stream<<tmpstr;
			for(int i=0;i<rows*cols;i++)
			{
				speed_location tmp;
				tmp.id=i+1;
				tmp.idle=0;
				stream>>tmp.id;
				if(tmp.id)
				{
					tmp.idle=judgeposition(tmp.id);
					//////////////////////////////////////////////////////////////////////////
					//多减了个1
					tmp.id=getid(tmp.id);
					//////////////////////////////////////////////////////////////////////////
				}
				
				if(tmp.idle!=2)sumcar++;
				if(tmp.idle==1)spendcar++;
				
				//////////////////////////////////////////////////////////////////////////
				//突然发现不需要用到rows值计算时间
				//难怪一直找不到问题出在哪
				//////////////////////////////////////////////////////////////////////////
				//突然发现横纵轴速度算反了
				//////////////////////////////////////////////////////////////////////////
				//shit,横轴坐标又少加1
				//////////////////////////////////////////////////////////////////////////
				//shit,横轴移动时间又改错了
				tmp.time=(tmp.id/cols)/speed_cols+((tmp.id-1)%cols)/speed_rows;
				//////////////////////////////////////////////////////////////////////////
				map_queue.push_back(tmp);
			}

			//////////////////////////////////////////////////////////////////////////
			//排序函数忘加了
			if(rows&&cols)
			{
				countqueue();
			}
			//////////////////////////////////////////////////////////////////////////

			return 0;
		}
		else
		{
			AfxMessageBox("readdate:未找到数据");
			//////////////////////////////////////////////////////////////////////////
			//错误未返回值,造成程序崩溃
			return -1;
			//////////////////////////////////////////////////////////////////////////
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		return -1;
	}
	return -1;
}

int carbarninfo::savedatetomysql()
{
	string tmpstr;
	CString str;

	for(int i=0;i<rows*cols&&i<map_queue.size();i++)
	{
		str.Format("%d ",combine(map_queue[i].id,map_queue[i].idle));
		tmpstr=tmpstr+str.GetBuffer(0);
	}
	//AfxMessageBox(tmpstr.c_str());

	//////////////////////////////////////////////////////////////////////////
	//把速度用%d输出造成程序崩溃了
	//CString str;卧槽这样都可以
	str.Format("\
UPDATE t_garageinfo set name='%s',nowstatus=%d,oldstatus=%d,command='%s',spendtime=%d,speedrows=%f,speedcols=%f,map_queue='%s' where carbarnid='%d'",
name.c_str(),nowstatus,oldstatus,command.front().c_str(),spendtime,speed_rows,speed_cols,tmpstr.c_str(),carbarnid);
	//////////////////////////////////////////////////////////////////////////

	//AfxMessageBox(str);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		return -1;
	}

	return 0;
}

int carbarninfo::judgeposition(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//用位移将数据分为两段，前端存状态
	return (unsigned int)num>>(sizeof(int)*4);
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::getid(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//用位移将数据分为两段，后段存id
	return ((unsigned int)num<<(sizeof(int)*4)) >>(sizeof(int)*4);
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::combine(int id,int idle)
{
	/////////////////////////////////////////////////////////////////////////
	//真是个悲伤的故事,id少加了个1,然后每保存一次数值就往后移动一位,还好改过来了
	//shit,改了序号后又忘了改回来,第二次改这个函数了
	return ((unsigned int)idle<<(sizeof(int)*4))|id;
	/////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////
//求折叠~~~
int carbarninfo::getcarbarnid()
{
	return this->carbarnid;
}

void carbarninfo::setcarbarnid(int carbarnid)
{
	this->carbarnid=carbarnid;
}

string carbarninfo::getname()
{
	return this->name;
}

void carbarninfo::setname(string name)
{
	this->name=name;
}

int carbarninfo::getnowstatus()
{
	return this->nowstatus;
}

void carbarninfo::setnowstatus(int status)
{
	this->oldstatus=this->nowstatus;
	this->nowstatus=status;
	if(this->nowstatus!=this->oldstatus)
	{
		spendtime=0;
		if(!command.empty())
			command.pop();
	}
}

int carbarninfo::getoldstatus()
{
	return oldstatus;
}

void carbarninfo::setoldstatus(int status)
{
	this->oldstatus=status;
}

string carbarninfo::getcommand()
{
	if(command.empty())
		return "";
	return command.front();
}

void carbarninfo::addcommand(string command)
{
	this->command.push(command);
	//spendtime=0;
}

int carbarninfo::getspendtime()
{
	return spendtime;
}

void carbarninfo::accspendtime()
{
	spendtime++;
}

int carbarninfo::getsumcar()
{
	sumcar=0;
	for(int i=0;i<map_queue.size();i++)
	{
		if(map_queue[i].idle!=2)sumcar++;
	}
	return sumcar;
}

int carbarninfo::getspendcar()
{
	return this->spendcar;
}

int carbarninfo::getrows()
{
	return this->rows;
}

void carbarninfo::setrows(int rows)
{
	this->rows=rows;
}

int carbarninfo::getcols()
{
	return this->cols;
}

void carbarninfo::setcols(int cols)
{
	this->cols=cols;
}

double carbarninfo::getspeedrows()
{
	return this->speed_rows;
}

void carbarninfo::setspeedrows(double rows)
{
	this->speed_rows=rows;
}

double carbarninfo::getspeedcols()
{
	return this->speed_cols;
}

void carbarninfo::setspeedcols(double cols)
{
	this->speed_cols=cols;
}

int carbarninfo::getrows(int location)
{
	//////////////////////////////////////////////////////////////////////////
	//返回值有±1误差,改好了
	return ((location-1)/cols+1);
	//////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////

int carbarninfo::getcols(int location)
{
	//////////////////////////////////////////////////////////////////////////
	//忘了行列怎么算了,还好改过来了
	//shit,这边也忘了改了
	//shit,又忘了-1
	return (location-(location-1)/cols*cols);
	//////////////////////////////////////////////////////////////////////////
}

bool compare(speed_location a,speed_location b)
{
	//////////////////////////////////////////////////////////////////////////
	//升序排列，如果改为return a>b，则为降序
	return a.time<b.time;
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::countqueue()
{
	//////////////////////////////////////////////////////////////////////////
	//按花费时间从小到大排序
	sort(map_queue.begin(),map_queue.end(),compare);
	//////////////////////////////////////////////////////////////////////////
	return 0;
}

int carbarninfo::findemptycarport()
{
	//////////////////////////////////////////////////////////////////////////
	//查找空余车位
	for(int i=0;i<map_queue.size();i++)
	{
		if(map_queue[i].idle==0)
		{
			return i;
		}
	}
	return -1;
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::switchid(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//使下标与id对应
	//index--;忘了删除了
	//////////////////////////////////////////////////////////////////////////
	if(index<1)return -1;
	if(index>map_queue.size())return -1;
	
	//////////////////////////////////////////////////////////////////////////
	//转换外部坐标为内部坐标

	for(int i=0;i<map_queue.size();i++)
	{
		if(map_queue[i].id==index)
		{
			return i;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	return -1;
}

int carbarninfo::savecar()
{
	int index=findemptycarport();
	if(index==-1)return index;
	map_queue[index].idle=1;

	spendcar++;

	savedatetomysql();

	//////////////////////////////////////////////////////////////////////////
	//最开始返回了内部下标,后来改成外部下标
	return map_queue[index].id;
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::setentry(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//坐标转换
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////

	map_queue[index].idle=2;
	
	//spendcar--;
	
	savedatetomysql();
	
	return map_queue[index].id;
}

int carbarninfo::cancelentry(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//坐标转换
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////
	
	map_queue[index].idle=0;
	
	//spendcar--;
	
	savedatetomysql();
	
	return map_queue[index].id;
}

int carbarninfo::newgarage()
{
	string tmpstr;
	CString str;
	
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));

	for(int i=0;i<rows*cols;i++)
	{
		speed_location tmp;
		tmp.id=i+1;
		tmp.idle=0;
		str.Format("%d ",tmp.id);
		tmpstr=tmpstr+str.GetBuffer(0);

		map_queue.push_back(tmp);
	}

	//AfxMessageBox(tmpstr.c_str());

	str.Format("INSERT INTO t_garageinfo \
(carbarnid,name,rows,cols,speedrows,speedcols,sumcar,spendcar,map_queue,compotr) \
VALUES(%d,'%s',%d,%d,%f,%f,%d,%d,'%s')",
this->carbarnid,this->name.c_str(),this->rows,this->cols,this->speed_rows,this->speed_cols,0,0,tmpstr.c_str());

	//AfxMessageBox(str);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
	}
	else
	{
		AfxMessageBox("插入失败");
		return -1;
	}
	
	return 0;
}

int carbarninfo::deletecar(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//坐标转换
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////
	
	if(map_queue[index].idle!=1)return -1;
	map_queue[index].idle=0;

	spendcar--;

	savedatetomysql();

	return map_queue[index].id;
}

int carbarninfo::clear()
{
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));

	rows=0;
	cols=0;

	return 0;
}

void carbarninfo::deletedate()
{
	CString str;
	//////////////////////////////////////////////////////////////////////////
	str.Format("DELETE FROM t_garageinfo where carbarnid='%d'",carbarnid);
	//////////////////////////////////////////////////////////////////////////
	//AfxMessageBox(str);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		return ;
	}
	
	//////////////////////////////////////////////////////////////////////////
	str.Format("DELETE FROM t_carinfo where carbarnid='%d'",carbarnid);
	//////////////////////////////////////////////////////////////////////////
	//AfxMessageBox(str);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		return ;
	}
}
