/**************************************
 *FILE    :D:\c\car\parking management\CCarbarnInfo.cpp
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/5 19:48:09
 *TEXT    :����ģ��:���𳵿���Ϣ
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
#include "CCarbarnInfo.h"
#include "DataStructure.h"
#include "ControlCode.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;

extern struct serverset serverinfo;

CCarbarnInfo::CCarbarnInfo()
{
	this->carbarnid=0;
	this->nowstatus=0;
	this->command[0]='\0';
	this->sqlcommand[0]='\0';
	this->spendtime=0;
	this->sumcar=0;
	this->spendcar=0;
	this->rows=0;
	this->cols=0;
	this->speed_rows=0;
	this->speed_cols=0;
}

CCarbarnInfo::~CCarbarnInfo()
{
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));
}

int CCarbarnInfo::readdate(int carbarnid)
{
	MYSQL_RES *res;                    //��ѯ�����
	MYSQL_ROW column;                  //�����е���
//	CString str;
	char str[COMLEN];
//	str.Format("select name,command,rows,cols,speedrows,speedcols,map_queue from t_garageinfo where id='%d'",carbarnid);
	sprintf_s(str, COMLEN, "select name,command,rows,cols,speedrows,speedcols,map_queue from t_garageinfo where id='%d'", carbarnid);
	mysql_query(&serverinfo.mysql,"SET NAMES 'GB2312'");

	if(mysql_query(&serverinfo.mysql,str)==NULL)
	{
		res=mysql_store_result(&serverinfo.mysql);//�����ѯ�������ݵ�result
		column=mysql_fetch_row(res);//��ȡ���������
		
		if(column)
		{
			//////////////////////////////////////////////////////////////////////////
			//����������...
			this->carbarnid=carbarnid;
			//////////////////////////////////////////////////////////////////////////
			this->name=column[0];
			//printf("%s>", this->name.c_str());
			this->sumcar=0;
			this->spendcar=0;
			this->rows=atoi(column[2]);
			this->cols=atoi(column[3]);
			this->speed_rows=atof(column[4]);
			this->speed_cols=atof(column[5]);

			if(column[6]==NULL)return -1;
			string tmpstr=column[6];

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
					//����˸�1
					tmp.id=getid(tmp.id);
					//////////////////////////////////////////////////////////////////////////
				}
				
				if(tmp.idle!=2)sumcar++;
				if(tmp.idle==1)spendcar++;
				
				//////////////////////////////////////////////////////////////////////////
				//ͻȻ���ֲ���Ҫ�õ�rowsֵ����ʱ��
				//�ѹ�һֱ�Ҳ������������
				//////////////////////////////////////////////////////////////////////////
				//ͻȻ���ֺ������ٶ��㷴��
				//////////////////////////////////////////////////////////////////////////
				//shit,�����������ټ�1
				//////////////////////////////////////////////////////////////////////////
				//shit,�����ƶ�ʱ���ָĴ���
				tmp.time=(tmp.id/cols)/speed_cols+((tmp.id-1)%cols)/speed_rows;
				//////////////////////////////////////////////////////////////////////////
				map_queue.push_back(tmp);
			}

			//////////////////////////////////////////////////////////////////////////
			//������������
			if(rows&&cols)
			{
				countqueue();
			}
			//////////////////////////////////////////////////////////////////////////

			return 0;
		}
		else
		{
			AfxMessageBox(_T("readdate:δ�ҵ�����"));
			//////////////////////////////////////////////////////////////////////////
			//����δ����ֵ,��ɳ������
			return -1;
			//////////////////////////////////////////////////////////////////////////
		}
	}
	else
	{
		AfxMessageBox(_T("carbarnid���ݿ�����ʧ��"));
		return -1;
	}
	return -1;
}

int CCarbarnInfo::savedatetomysql()
{
	string tmpstr;
//	CString str;
	char str[COMLEN];

	for(int i=0;i<(rows*cols)&&i<(int)map_queue.size();i++)
	{
//		str.Format("%d ",combine(map_queue[i].id,map_queue[i].idle));
		sprintf_s(str, COMLEN, "%d ", combine(map_queue[i].id, map_queue[i].idle));
		tmpstr=tmpstr+str;
	}
	//AfxMessageBox(tmpstr.c_str());

	//////////////////////////////////////////////////////////////////////////
	//���ٶ���%d�����ɳ��������
	//CString str;�Բ�����������
//	str.Format(
	sprintf_s(str, COMLEN, "\
UPDATE t_garageinfo set name='%s',nowstatus=%d,command='%s',speedrows=%f,speedcols=%f,map_queue='%s' where id='%d'",
name.c_str(),nowstatus,command,speed_rows,speed_cols,tmpstr.c_str(),carbarnid);
	//////////////////////////////////////////////////////////////////////////

	//AfxMessageBox(str);
	mysql_query(&serverinfo.mysql,"SET NAMES 'GB2312'");
	
	if(mysql_query(&serverinfo.mysql,str)!=NULL)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		return -1;
	}

	return 0;
}

int CCarbarnInfo::judgeposition(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//��λ�ƽ����ݷ�Ϊ���Σ�ǰ�˴�״̬
	return (unsigned int)num>>16;
	//////////////////////////////////////////////////////////////////////////
}

int CCarbarnInfo::getid(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//��λ�ƽ����ݷ�Ϊ���Σ���δ�id
	return ((unsigned int)num<<(sizeof(int)*8-16)) >>(sizeof(int)*8-16);
	//////////////////////////////////////////////////////////////////////////
}

int CCarbarnInfo::combine(int id,int idle)
{
	/////////////////////////////////////////////////////////////////////////
	//���Ǹ����˵Ĺ���,id�ټ��˸�1,Ȼ��ÿ����һ����ֵ�������ƶ�һλ,���øĹ�����
	//shit,������ź������˸Ļ���,�ڶ��θ����������
	return ((unsigned int)idle<<16)|id;
	/////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////
//���۵�~~~
int CCarbarnInfo::getcarbarnid()
{
	return this->carbarnid;
}

void CCarbarnInfo::setcarbarnid(int carbarnid)
{
	this->carbarnid=carbarnid;
}

string CCarbarnInfo::getname()
{
	return this->name;
}

void CCarbarnInfo::setname(string name)
{
	this->name=name;
}

int CCarbarnInfo::getnowstatus()
{
	return this->nowstatus;
}

void CCarbarnInfo::setnowstatus(int status)
{
	this->nowstatus=status;
	spendtime=0;
}

void CCarbarnInfo::setoffline()
{
	this->nowstatus=OFFLINE;
}

void CCarbarnInfo::getcommand(char* str)
{
	if(command[0]=='\0')str[0]='\0';
	else strcpy_s(str,COMLEN,this->command);
}

void CCarbarnInfo::setcommand(const char str[])
{
	strcpy_s(command,COMLEN,str);
	//spendtime=0;
}

void CCarbarnInfo::setsqlcommand(const char str[])
{
	strcpy_s(sqlcommand,COMLEN ,str);
}

void CCarbarnInfo::getsqlcommand(char* str)
{
	if(sqlcommand[0]=='\0')str[0]='\0';
	else strcpy_s(str, COMLEN, sqlcommand);
}

int CCarbarnInfo::getusernum()
{
	return 0;
} 

int CCarbarnInfo::getspendtime()
{
	return spendtime;
}

void CCarbarnInfo::accspendtime()
{
	spendtime++;
}

void CCarbarnInfo::setzerospendtime()
{
	spendtime=0;
}

int CCarbarnInfo::getsumcar()
{
	sumcar=0;
	for(int i=0;i<(int)map_queue.size();i++)
	{
		if(map_queue[i].idle!=2)sumcar++;
	}
	return sumcar;
}

int CCarbarnInfo::getspendcar()
{
	return this->spendcar;
}

int CCarbarnInfo::getrows()
{
	return this->rows;
}

void CCarbarnInfo::setrows(int rows)
{
	this->rows=rows;
}

int CCarbarnInfo::getcols()
{
	return this->cols;
}

void CCarbarnInfo::setcols(int cols)
{
	this->cols=cols;
}

double CCarbarnInfo::getspeedrows()
{
	return this->speed_rows;
}

void CCarbarnInfo::setspeedrows(double rows)
{
	this->speed_rows=rows;
}

double CCarbarnInfo::getspeedcols()
{
	return this->speed_cols;
}

void CCarbarnInfo::setspeedcols(double cols)
{
	this->speed_cols=cols;
}

int CCarbarnInfo::getrows(int location)
{
	//////////////////////////////////////////////////////////////////////////
	//����ֵ�С�1���,�ĺ���
	return ((location-1)/cols+1);
	//////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////

int CCarbarnInfo::getcols(int location)
{
	//////////////////////////////////////////////////////////////////////////
	//����������ô����,���øĹ�����
	//shit,���Ҳ���˸���
	//shit,������-1
	return (location-(location-1)/cols*cols);
	//////////////////////////////////////////////////////////////////////////
}

bool compare(speed_location a,speed_location b)
{
	//////////////////////////////////////////////////////////////////////////
	//�������У������Ϊreturn a>b����Ϊ����
	return a.time<b.time;
	//////////////////////////////////////////////////////////////////////////
}

int CCarbarnInfo::countqueue()
{
	//////////////////////////////////////////////////////////////////////////
	//������ʱ���С��������
	sort(map_queue.begin(),map_queue.end(),compare);
	//////////////////////////////////////////////////////////////////////////
	return 0;
}

int CCarbarnInfo::findemptycarport()
{
	//////////////////////////////////////////////////////////////////////////
	//���ҿ��೵λ
	for(int i=0;i<(int)map_queue.size();i++)
	{
		if(map_queue[i].idle==0)
		{
			return i;
		}
	}
	return -1;
	//////////////////////////////////////////////////////////////////////////
}

int CCarbarnInfo::findemptycarid()
{
	//////////////////////////////////////////////////////////////////////////
	//���ҿ��೵λ
	for(int i=0;i<(int)map_queue.size();i++)
	{
		if(map_queue[i].idle==0)
		{
			return map_queue[i].id;
		}
	}
	return -1;
	//////////////////////////////////////////////////////////////////////////
}

int CCarbarnInfo::switchid(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//ʹ�±���id��Ӧ
	//index--;����ɾ����
	//////////////////////////////////////////////////////////////////////////
	if(index<1)return -1;
	if(index>(int)map_queue.size())return -1;
	
	//////////////////////////////////////////////////////////////////////////
	//ת���ⲿ����Ϊ�ڲ�����

	for(int i=0;i<(int)map_queue.size();i++)
	{
		if(map_queue[i].id==index)
		{
			return i;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	return -1;
}

int CCarbarnInfo::savecar()
{
	int index=findemptycarport();
	if(index==-1)return index;
	map_queue[index].idle=1;

	spendcar++;

	savedatetomysql();

	//////////////////////////////////////////////////////////////////////////
	//�ʼ�������ڲ��±�,�����ĳ��ⲿ�±�
	return map_queue[index].id;
	//////////////////////////////////////////////////////////////////////////
}

int CCarbarnInfo::setentry(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//����ת��
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////

	map_queue[index].idle=2;
	
	//spendcar--;
	
	savedatetomysql();
	
	return map_queue[index].id;
}

int CCarbarnInfo::cancelentry(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//����ת��
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////
	
	map_queue[index].idle=0;
	
	//spendcar--;
	
	savedatetomysql();
	
	return map_queue[index].id;
}

int CCarbarnInfo::newgarage()
{
	string tmpstr;
//	CString str;
	char str[COMLEN];
	
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));

	for(int i=0;i<rows*cols;i++)
	{
		speed_location tmp;
		tmp.id=i+1;
		tmp.idle=0;
//		str.Format("%d ",tmp.id);
		sprintf_s(str,COMLEN, "%d ", tmp.id);
		tmpstr=tmpstr+str;

		map_queue.push_back(tmp);
	}

	//AfxMessageBox(tmpstr.c_str());
	sprintf_s(str, COMLEN, "INSERT INTO t_garageinfo \
(id,name,rows,cols,speedrows,speedcols,sumcar,spendcar,map_queue,compotr) \
VALUES(%d,'%s',%d,%d,%f,%f,%d,%d,'%s')",
this->carbarnid,this->name.c_str(),this->rows,this->cols,this->speed_rows,this->speed_cols,0,0,tmpstr.c_str());

	//AfxMessageBox(str);
	mysql_query(&serverinfo.mysql,"SET NAMES 'GB2312'");
	
	if(mysql_query(&serverinfo.mysql,str)!=NULL)
	{
		AfxMessageBox(_T("����ʧ��"));
		return -1;
	}
	
	return 0;
}

int CCarbarnInfo::deletecar(int index)
{
	//////////////////////////////////////////////////////////////////////////
	//����ת��
	index=switchid(index);
	if(index<0)return -1;
	//////////////////////////////////////////////////////////////////////////
	
	if(map_queue[index].idle!=1)return -1;
	map_queue[index].idle=0;

	spendcar--;

	savedatetomysql();

	return map_queue[index].id;
}

int CCarbarnInfo::clear()
{
	map_queue.clear();
	map_queue.swap( (std::vector <speed_location>)(map_queue));

	rows=0;
	cols=0;

	return 0;
}

void CCarbarnInfo::deletedate()
{
//	CString str;
	char str[COMLEN];
	//////////////////////////////////////////////////////////////////////////
//	str.Format("DELETE FROM t_garageinfo where id='%d'",carbarnid);
	sprintf_s(str, COMLEN, "DELETE FROM t_garageinfo where id='%d'", carbarnid);
	//////////////////////////////////////////////////////////////////////////
	//AfxMessageBox(str);
	mysql_query(&serverinfo.mysql,"SET NAMES 'GB2312'");
	
	if(mysql_query(&serverinfo.mysql,str)!=NULL)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		return ;
	}
	
	//////////////////////////////////////////////////////////////////////////
//	str.Format("DELETE FROM t_carinfo where id='%d'",carbarnid);
	sprintf_s(str, COMLEN, "DELETE FROM t_carinfo where id='%d'", carbarnid);
	//////////////////////////////////////////////////////////////////////////
	//AfxMessageBox(str);
	mysql_query(&serverinfo.mysql,"SET NAMES 'GB2312'");
	
	if(mysql_query(&serverinfo.mysql,str)!=NULL)
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
		return ;
	}
}

