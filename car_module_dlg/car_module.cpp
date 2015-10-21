/**************************************
 *FILE    :D:\c\car\car_module\car_module.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:33
 *TEXT    :车库模块:只负责车库信息
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
#include "car_module.h"
#include "DataStructure.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

extern struct serverset serverinfo;

car_module::car_module()
{
	this->mac=-1;
	this->sumcar=0;
	this->spendcar=0;
	this->condition=0;
	this->compotr=0;
	this->rows=0;
	this->cols=0;
	this->speed_rows=0;
	this->speed_cols=0;

	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		AfxMessageBox("车库模块:数据库无法连接!");
		exit(1);
		return ;
	}
}

car_module::~car_module()
{
	mysql_close(&mysql);
}

int car_module::readdate(int mac)
{
	CString str;
	str.Format("select * from t_garageinfo where mac=%d",mac);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		if(column)
		{
			this->mac=mac;
			rows=atoi(column[3]);
			cols=atoi(column[4]);
			speed_rows=atof(column[5]);
			speed_cols=atof(column[6]);
			sumcar=0;//atoi(column[7]);
			spendcar=0;//atoi(column[8]);
			//compotr=atoi(column[11]);

			//////////////////////////////////////////////////////////////////////////
			compotr=0;
			if(column[11])
				compotr=atoi(column[11]);
			//////////////////////////////////////////////////////////////////////////
			
			//////////////////////////////////////////////////////////////////////////
			status=0;
			if(column[10])
				status=atoi(column[10]);
			//////////////////////////////////////////////////////////////////////////

			if(column[9]==NULL)return -1;
			string tmpstr=column[9];

			if(rows<0)return -1;
			if(cols<0)return -1;
/*
			CString tmp;
			tmp=column[3];
			tmp=tmp+":"+column[4];
			AfxMessageBox(tmp);
*/
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
				
				if(tmp.idle==2)sumcar--;
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
			if(rows*cols)
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

int car_module::getstatus()
{
	return this->status;
}

int car_module::savedatetomysql(int mac)
{
	this->mac=mac;

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
UPDATE t_garageinfo set rows=%d,cols=%d,\
speedrows=%f,speedcols=%f,sumcar=%d,spendcar=%d,map_queue='%s',compotr=%d where mac=%d",
rows,cols,speed_rows,speed_cols,sumcar,spendcar,tmpstr.c_str(),compotr,mac);
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

int car_module::judgeposition(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//用位移将数据分为两段，前端存状态
	return (unsigned int)num>>(sizeof(int)*4);
	//////////////////////////////////////////////////////////////////////////
}

void car_module::setcompotr(int num)
{
	this->compotr=num;
}

int car_module::getcompotr()
{
	return this->compotr;
}

int car_module::getid(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//用位移将数据分为两段，后段存id
	return ((unsigned int)num<<(sizeof(int)*4)) >>(sizeof(int)*4);
	//////////////////////////////////////////////////////////////////////////
}

int car_module::getcond(int num)
{
	int index=switchid(num);
	//AfxMessageBox("1");
	if(index<0)return -1;
	//AfxMessageBox("2");
	if(index>=map_queue.size())return -1;
	//AfxMessageBox("3");
	//for(int i=0;i<map_queue.size();i++)
	//{
		//////////////////////////////////////////////////////////////////////////
		//shict,为什么我没把序号和下标改过来,费了这么久时间
		//if(map_queue[i].id==num)
	return this->map_queue[index].idle;
		//////////////////////////////////////////////////////////////////////////
	//}
	//return -1;
}

int car_module::combine(int id,int idle)
{
	/////////////////////////////////////////////////////////////////////////
	//真是个悲伤的故事,id少加了个1,然后每保存一次数值就往后移动一位,还好改过来了
	//shit,改了序号后又忘了改回来,第二次改这个函数了
	return ((unsigned int)idle<<(sizeof(int)*4))|id;
	/////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////
//这些怪自个作死写成这样,折叠看最好
int car_module::getmac()
{
	return this->mac;
}

void car_module::setmac(int mac)
{
	this->mac=mac;
}

int car_module::getsumcar()
{
	sumcar=0;
	for(int i=0;i<map_queue.size();i++)
	{
		if(map_queue[i].idle!=2)sumcar++;
	}
	return sumcar;
}

int car_module::getspendcar()
{
	return this->spendcar;
}

int car_module::getcondition()
{
	return this->condition;
}

void car_module::setconditopn(int num)
{
	this->condition=num;
}

int car_module::getrows()
{
	return this->rows;
}

void car_module::setrows(int rows)
{
	this->rows=rows;
}

int car_module::getcols()
{
	return this->cols;
}

void car_module::setcols(int cols)
{
	this->cols=cols;
}

double car_module::getspeedrows()
{
	return this->speed_rows;
}

void car_module::setspeedrows(double rows)
{
	this->speed_rows=rows;
}

double car_module::getspeedcols()
{
	return this->speed_cols;
}

void car_module::setspeedcols(double cols)
{
	this->speed_cols=cols;
}

int car_module::getrows(int location)
{
	//////////////////////////////////////////////////////////////////////////
	//返回值有±1误差,改好了
	return ((location-1)/cols+1);
	//////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////

int car_module::getcols(int location)
{
	//////////////////////////////////////////////////////////////////////////
	//忘了行列怎么算了,还好改过来了
	//shit,这边也忘了改了
	//shit,又忘了-1
	return (location-(location-1)/cols);
	//////////////////////////////////////////////////////////////////////////
}

bool compare(speed_location a,speed_location b)
{
	//////////////////////////////////////////////////////////////////////////
	//升序排列，如果改为return a>b，则为降序
	return a.time<b.time;
	//////////////////////////////////////////////////////////////////////////
}

int car_module::countqueue()
{
	//////////////////////////////////////////////////////////////////////////
	//按花费时间从小到大排序
	sort(map_queue.begin(),map_queue.end(),compare);
	//////////////////////////////////////////////////////////////////////////
	return 0;
}

int car_module::findemptycarport()
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

int car_module::switchid(int index)
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

int car_module::savecar()
{
	int index=findemptycarport();
	if(index==-1)return index;
	map_queue[index].idle=1;

	spendcar++;

	savedatetomysql(this->mac);

	//////////////////////////////////////////////////////////////////////////
	//最开始返回了内部下标,后来改成外部下标
	return map_queue[index].id;
	//////////////////////////////////////////////////////////////////////////
}

int car_module::setentry(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//坐标转换
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////

	map_queue[index].idle=2;
	
	//spendcar--;
	
	savedatetomysql(this->mac);
	
	return map_queue[index].id;
}

int car_module::cancelentry(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//坐标转换
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////
	
	map_queue[index].idle=0;
	
	//spendcar--;
	
	savedatetomysql(this->mac);
	
	return map_queue[index].id;
}

int car_module::newgarage()
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
(mac,rows,cols,speedrows,speedcols,sumcar,spendcar,map_queue) \
VALUES(%d,%d,%d,%f,%f,%d,%d,'%s')",
this->mac,this->rows,this->cols,this->speed_rows,this->speed_cols,0,0,tmpstr.c_str());

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

int car_module::deletecar(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//坐标转换
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////
	
	if(map_queue[index].idle!=1)return -1;
	map_queue[index].idle=0;

	spendcar--;

	savedatetomysql(this->mac);

	return map_queue[index].id;
}

int car_module::clear()
{
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));

	rows=0;
	cols=0;

	//savedatetomysql(this->mac);
	//readdate();
	return 0;
}

void car_module::deletedate()
{
	CString str;
	//////////////////////////////////////////////////////////////////////////
	str.Format("DELETE FROM t_garageinfo where mac=%d",mac);
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
	str.Format("DELETE FROM t_carinfo where mac=%d",mac);
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
