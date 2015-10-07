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
#include "car_module.h"
#include "DataStructure.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

extern struct serverset serverinfo;

int car_module::readdate()
{
	FILE* fpin;
	fpin=fopen("date.txt","r");
	if(fpin==NULL)
	{
		printf("can not open date.txt\n");
		return 1;
	}
	fscanf(fpin,"%d\n",&mac);
	fscanf(fpin,"%d%d\n",&rows,&cols);
	fscanf(fpin,"%lf%lf\n",&speed_rows,&speed_cols);
	sumcar=rows*cols;
	spendcar=0;
	for(int i=0;i<rows*cols;i++)
	{
		speed_location tmp;
		tmp.id=i;
		tmp.idle=0;
		fscanf(fpin,"%d",&tmp.id);
		if(!feof(fpin))
		{
			tmp.idle=judgeposition(tmp.id);
			tmp.id=getid(tmp.id)-1;
		}

		if(tmp.idle==2)sumcar--;
		if(tmp.idle==1)spendcar++;

		//////////////////////////////////////////////////////////////////////////
		//突然发现不需要用到rows值计算时间
		//难怪一直找不到问题出在哪
		//////////////////////////////////////////////////////////////////////////
		//突然发现横纵轴速度算反了
		tmp.time=(tmp.id/cols)/speed_cols+(tmp.id%cols)/speed_rows;
		//////////////////////////////////////////////////////////////////////////
		map_queue.push_back(tmp);
	}
	fclose(fpin);

	if(rows*cols)
	{
		countqueue();
	}

	return 0;
}

int car_module::readdate(int mac)
{
	this->mac=mac;

	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		AfxMessageBox("数据库无法连接!");
		return -1;
	}

	CString str;
	str.Format("select * from t_garageinfo where mac=%d",mac);

	mysql_query(&mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		if(column)
		{
			rows=atoi(column[3]);
			cols=atoi(column[4]);
			speed_rows=atof(column[5]);
			speed_cols=atof(column[6]);
			sumcar=0;//atoi(column[7]);
			spendcar=0;//atoi(column[8]);
			string tmpstr=column[9];

			stringstream stream;
			stream<<tmpstr;
			for(int i=0;i<rows*cols;i++)
			{
				speed_location tmp;
				tmp.id=i;
				tmp.idle=0;
				stream>>tmp.id;
				if(tmp.id)
				{
					tmp.idle=judgeposition(tmp.id);
					tmp.id=getid(tmp.id)-1;
				}
				
				if(tmp.idle==2)sumcar--;
				if(tmp.idle==1)spendcar++;
				
				//////////////////////////////////////////////////////////////////////////
				//突然发现不需要用到rows值计算时间
				//难怪一直找不到问题出在哪
				//////////////////////////////////////////////////////////////////////////
				//突然发现横纵轴速度算反了
				tmp.time=(tmp.id/cols)/speed_cols+(tmp.id%cols)/speed_rows;
				//////////////////////////////////////////////////////////////////////////
				map_queue.push_back(tmp);
			}
		}
		else
		{
			AfxMessageBox("readdate:未找到数据");
		}
	}
	else
	{
		AfxMessageBox("数据库连接失败");
		return -1;
	}

	return 0;
}

int car_module::savedatetomysql()
{
	FILE* fpout;
	fpout=fopen("date.txt","w");
	if(fpout==NULL)
	{
		printf("can not open date.txt\n");
		return 1;
	}
	fprintf(fpout,"%d\n",mac);
	fprintf(fpout,"%d %d\n",rows,cols);
	fprintf(fpout,"%.3lf %.3lf\n",speed_rows,speed_cols);
	for(int i=0;i<rows*cols&&map_queue.size();i++)
	{
		fprintf(fpout,"%d ",combine(map_queue[i].id,map_queue[i].idle));
	}
	fclose(fpout);
	return 0;
}

int car_module::savedatetomysql(int mac)
{
	this->mac=mac;

	mysql_init(&mysql);
	if(mysql_real_connect(&mysql, serverinfo.ip , serverinfo.name, serverinfo.password, serverinfo.database, serverinfo.port, NULL, 0) == NULL)
	{
		AfxMessageBox("数据库无法连接!");
		return -1;
	}
	
	string tmpstr;
	CString str;

	for(int i=0;i<rows*cols;i++)
	{
		str.Format("%d ",combine(map_queue[i].id,map_queue[i].idle));
		tmpstr=tmpstr+str.GetBuffer(0);
	}

	//////////////////////////////////////////////////////////////////////////
	//把速度用%d输出造成程序崩溃了
	//CString str;
	str.Format("\
UPDATE t_garageinfo set rows=%d,cols=%d,\
speedrows=%f,speedcols=%f,sumcar=%d,spendcar=%d,map_queue='%s' where mac=%d",
rows,cols,speed_rows,speed_cols,sumcar,spendcar,tmpstr.c_str(),mac);
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

int car_module::getid(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//用位移将数据分为两段，后段存id
	return ((unsigned int)num<<(sizeof(int)*4)) >>(sizeof(int)*4);
	//////////////////////////////////////////////////////////////////////////
}

int car_module::getcond(int num)
{
	for(int i=0;i<map_queue.size();i++)
	{
		if(map_queue[i].id==num-1)
			return this->map_queue[i].idle;
	}
	return -1;
}

int car_module::combine(int id,int idle)
{
	/////////////////////////////////////////////////////////////////////////
	//真是个悲伤的故事,id少加了个1,然后每保存一次数值就往后移动一位,还好改过来了
	return ((unsigned int)idle<<(sizeof(int)*4))|(id+1);
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
	return (location/cols);
}
/////////////////////////////////////////////////////////////////////////

int car_module::getcols(int location)
{
	//////////////////////////////////////////////////////////////////////////
	//忘了行列怎么算了,还好改过来了
	return (location%cols);
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

int car_module::savecar()
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

int car_module::deletecar(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//使下标与id对应
	index--;
	//////////////////////////////////////////////////////////////////////////
	if(index<0)return -1;
	if(index>=map_queue.size())return -1;

	//////////////////////////////////////////////////////////////////////////
	//转换外部坐标为内部坐标
	int i;
	for(i=0;i<map_queue.size();)
	{
		if(map_queue[i].id==index)
			break;
		i++;
	}
	//////////////////////////////////////////////////////////////////////////
	
	if(map_queue[i].idle==0)return -1;
	map_queue[i].idle=0;

	spendcar--;

	savedatetomysql();

	return map_queue[i].id;
}

void car_module::putinfo()
{
	printf("mac=%d\n",mac);
	printf("sumcar=%2d spendcar=%2d\n",sumcar,spendcar);
	printf("rows=%2d cols=%2d\n",rows,cols);
	printf("speed_rows=%.3lf speed_cols=%.3lf\n",speed_rows,speed_cols);

	printf("\n");
	for(int i=rows-1;i>=0;i--)
	{
		for(int j=0;j<cols;j++)
		{
			printf("%2d ",i*cols+j);
		}
		printf("\n");
	}
	printf("\n");

	for(i=0;i<rows*cols;i++)
	{
		printf("rows=%2d cols=%2d id=%2d free=%2d time=%.3lf\n",getrows(map_queue[i].id),getcols(map_queue[i].id),map_queue[i].id,map_queue[i].idle,map_queue[i].time);
	}
	printf("\n");
}

int car_module::clear()
{
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));

	rows=0;
	cols=0;

	savedatetomysql();
	readdate();
	return 0;
}