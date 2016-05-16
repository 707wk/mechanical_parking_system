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
#include "CCarbarnInfo.h"
#include "CWayFinding.h"
#include "DataStructure.h"
#include "ControlCode.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

extern struct serverset serverinfo;

extern CCarbarnInfo* garage;

extern int* idtoindex;

CWayFinding::CWayFinding()
{
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
//	CString str;

	//////////////////////////////////////////////////////////////////////////
//	str="select max(x) from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if (mysql_query(&serverinfo.mysql, "select max(x) from t_map") == NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		
		if(column)
		{
			map_x=atoi(column[0])+2;
		}
		else
		{
			AfxMessageBox(_T("map:未找到数据"));
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
//	str="select max(y) from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if (mysql_query(&serverinfo.mysql, "select max(y) from t_map") == NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		
		if(column)
		{
			map_y=atoi(column[0])+2;
		}
		else
		{
			AfxMessageBox(_T("map:未找到数据"));
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////

	maplocation = new struct maptype*[map_x];
	for(int i=0;i<map_x;i++)
	{
		maplocation[i] = new struct maptype[map_y];
	}

	initmap();

	//////////////////////////////////////////////////////////////////////////
//	str="select x,y,type,type_id from t_map";
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if (mysql_query(&serverinfo.mysql, "select x,y,type,type_id from t_map") == NULL)
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
		AfxMessageBox(_T("数据库连接失败"));
		exit(1) ;
	}
	//////////////////////////////////////////////////////////////////////////
}

CWayFinding::~CWayFinding()
{
	for (int i=0;i<map_x;i++)
	{
 		delete[] maplocation[i];
	}
	delete[] maplocation;
}

void CWayFinding::initmap()
{
	for(int i=0;i<map_x;i++)
	{
		for(int j=0;j<map_y;j++)
		{
			maplocation[i][j].type    =0;
			maplocation[i][j].flage   =0;
			maplocation[i][j].id      =0;
		}
	}
}

int CWayFinding::nearestcarport(int id)
{
	queue<mapway> pathanalysis;        //寻路变量
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
//	cstring str;
	char str[1024];
	struct mapway tmp;

	//////////////////////////////////////////////////////////////////////////
//	str.Format("select x,y from t_map where type_id=%d and type=1",id);
	sprintf_s(str, COMLEN, "select x,y from t_map where type_id=%d and type=1", id);
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&serverinfo.mysql,str)==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		
		if(column)
		{
			tmp.x=atoi(column[0]);
			tmp.y=atoi(column[1]);
		}
		else
		{
			AfxMessageBox(_T("map:未找到数据"));
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1) ;
	}
	
	pathanalysis.push(tmp);
	clearflage();
	
	for(;pathanalysis.size()>0;)
	{
		int tmpx=pathanalysis.front().x;
		int tmpy=pathanalysis.front().y;
		int tmpid;
		
		if(maplocation[tmpx-1][tmpy].type==3)
		{
			tmpid=maplocation[tmpx-1][tmpy].id;

			if(garage[idtoindex[tmpid]].getsumcar()==garage[idtoindex[tmpid]].getspendcar())
				return -1;
			
			if(garage[idtoindex[tmpid]].getnowstatus()==STATEFREE)
				return tmpid;
		}
		if(maplocation[tmpx][tmpy+1].type==3)
		{
			tmpid=maplocation[tmpx][tmpy+1].id;

			if(garage[idtoindex[tmpid]].getsumcar()==garage[idtoindex[tmpid]].getspendcar())
				return -1;

			if(garage[idtoindex[tmpid]].getnowstatus()==STATEFREE)
				return tmpid;
		}			
		if(maplocation[tmpx+1][tmpy].type==3)
		{
			tmpid=maplocation[tmpx+1][tmpy].id;
			
			if(garage[idtoindex[tmpid]].getsumcar()==garage[idtoindex[tmpid]].getspendcar())
				return -1;
			
			if(garage[idtoindex[tmpid]].getnowstatus()==STATEFREE)
				return tmpid;
		}
		if(maplocation[tmpx][tmpy-1].type==3)
		{
			tmpid=maplocation[tmpx][tmpy-1].id;
			
			if(garage[idtoindex[tmpid]].getsumcar()==garage[idtoindex[tmpid]].getspendcar())
				return -1;
			
			if(garage[idtoindex[tmpid]].getnowstatus()==STATEFREE)
				return tmpid;
		}

		if(maplocation[tmpx-1][tmpy].type==4&&maplocation[tmpx-1][tmpy].flage==0)
		{
			tmp.x=tmpx-1;
			tmp.y=tmpy;
			pathanalysis.push(tmp);
		}
		if(maplocation[tmpx][tmpy+1].type==4&&maplocation[tmpx][tmpy+1].flage==0)
		{
			tmp.x=tmpx;
			tmp.y=tmpy+1;
			pathanalysis.push(tmp);
		}
		if(maplocation[tmpx+1][tmpy].type==4&&maplocation[tmpx+1][tmpy].flage==0)
		{
			tmp.x=tmpx+1;
			tmp.y=tmpy;
			pathanalysis.push(tmp);
		}
		if(maplocation[tmpx][tmpy-1].type==4&&maplocation[tmpx][tmpy-1].flage==0)
		{
			tmp.x=tmpx;
			tmp.y=tmpy-1;
			pathanalysis.push(tmp);
		}

		maplocation[tmpx][tmpy].flage=1;
		pathanalysis.pop();
	}
	return -1;
}

int CWayFinding::nearestexit(int id)
{
	queue<mapway> pathanalysis;        //寻路变量
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列
//	CString str;
	char str[1024];
	struct mapway tmp;
	
	//////////////////////////////////////////////////////////////////////////
//	str.Format("select x,y from t_map where type_id=%d and type=3",id);
	sprintf_s(str, COMLEN, "select x,y from t_map where type_id=%d and type=3", id);
	
	mysql_query(&serverinfo.mysql,"SET NAMES 'UTF-8'");
	
	if(mysql_query(&serverinfo.mysql,str)==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//保存查询到的数据到result
		column=mysql_fetch_row(res);//获取具体的数据
		
		if(column)
		{
			tmp.x=atoi(column[0]);
			tmp.y=atoi(column[1]);
		}
		else
		{
			AfxMessageBox(_T("map:未找到数据"));
			exit(1) ;
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
		exit(1) ;
	}

	pathanalysis.push(tmp);
	clearflage();
	
	for(;pathanalysis.size()>0;)
	{
		int tmpx=pathanalysis.front().x;
		int tmpy=pathanalysis.front().y;
		
		if(maplocation[tmpx-1][tmpy].type==2)
		{
			return maplocation[tmpx-1][tmpy].id;
		}
		if(maplocation[tmpx][tmpy+1].type==2)
		{
			return maplocation[tmpx][tmpy+1].id;
		}			
		if(maplocation[tmpx+1][tmpy].type==2)
		{
			return maplocation[tmpx+1][tmpy].id;
		}
		if(maplocation[tmpx][tmpy-1].type==2)
		{
			return maplocation[tmpx][tmpy-1].id;
		}
		
		if(maplocation[tmpx-1][tmpy].type==4&&maplocation[tmpx-1][tmpy].flage==0)
		{
			tmp.x=tmpx-1;
			tmp.y=tmpy;
			pathanalysis.push(tmp);
		}
		if(maplocation[tmpx][tmpy+1].type==4&&maplocation[tmpx][tmpy+1].flage==0)
		{
			tmp.x=tmpx;
			tmp.y=tmpy+1;
			pathanalysis.push(tmp);
		}
		if(maplocation[tmpx+1][tmpy].type==4&&maplocation[tmpx+1][tmpy].flage==0)
		{
			tmp.x=tmpx+1;
			tmp.y=tmpy;
			pathanalysis.push(tmp);
		}
		if(maplocation[tmpx][tmpy-1].type==4&&maplocation[tmpx][tmpy-1].flage==0)
		{
			tmp.x=tmpx;
			tmp.y=tmpy-1;
			pathanalysis.push(tmp);
		}

		maplocation[tmpx][tmpy].flage=1;
		pathanalysis.pop();
	}
	return -1;
}

void CWayFinding::putinfo()
{
	FILE* fp;
	fopen_s(&fp,"map.txt", "w");

	fprintf(fp,"%d\n",nearestcarport(1));
	fprintf(fp,"%d\n",nearestexit(17));
	
	for(int i=0;i<map_x;i++)
	{
		for(int j=0;j<map_y;j++)
		{
			fprintf(fp,"%3d:%d",maplocation[i][j].type,maplocation[i][j].id);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	return ;
}

void CWayFinding::clearflage()
{
	for(int i=0;i<map_x;i++)
	{
		for(int j=0;j<map_y;j++)
		{
			maplocation[i][j].flage=0;
		}
	}
}
