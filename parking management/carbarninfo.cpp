/**************************************
 *FILE    :D:\c\car\parking management\carbarninfo.cpp
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
	MYSQL_RES *res;                    //��ѯ�����
	MYSQL_ROW column;                  //�����е���
	CString str;
	str.Format("select name,nowstatus,oldstatus,command,spendtime,rows,cols,speedrows,speedcols,map_queue from t_garageinfo where carbarnid='%d'",carbarnid);
	mysql_query(&mysql,"SET NAMES 'UTF-8'");

	if(mysql_query(&mysql,str.GetBuffer(0))==NULL)
	{
		res=mysql_store_result(&mysql);//�����ѯ�������ݵ�result
		column=mysql_fetch_row(res);//��ȡ���������
		
		if(column)
		{
			//////////////////////////////////////////////////////////////////////////
			//����������...
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
			AfxMessageBox("readdate:δ�ҵ�����");
			//////////////////////////////////////////////////////////////////////////
			//����δ����ֵ,��ɳ������
			return -1;
			//////////////////////////////////////////////////////////////////////////
		}
	}
	else
	{
		AfxMessageBox("���ݿ�����ʧ��");
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
	//���ٶ���%d�����ɳ��������
	//CString str;�Բ�����������
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
		AfxMessageBox("���ݿ�����ʧ��");
		return -1;
	}

	return 0;
}

int carbarninfo::judgeposition(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//��λ�ƽ����ݷ�Ϊ���Σ�ǰ�˴�״̬
	return (unsigned int)num>>(sizeof(int)*4);
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::getid(int num)
{
	//////////////////////////////////////////////////////////////////////////
	//��λ�ƽ����ݷ�Ϊ���Σ���δ�id
	return ((unsigned int)num<<(sizeof(int)*4)) >>(sizeof(int)*4);
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::combine(int id,int idle)
{
	/////////////////////////////////////////////////////////////////////////
	//���Ǹ����˵Ĺ���,id�ټ��˸�1,Ȼ��ÿ����һ����ֵ�������ƶ�һλ,���øĹ�����
	//shit,������ź������˸Ļ���,�ڶ��θ����������
	return ((unsigned int)idle<<(sizeof(int)*4))|id;
	/////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////
//���۵�~~~
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
	//����ֵ�С�1���,�ĺ���
	return ((location-1)/cols+1);
	//////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////

int carbarninfo::getcols(int location)
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

int carbarninfo::countqueue()
{
	//////////////////////////////////////////////////////////////////////////
	//������ʱ���С��������
	sort(map_queue.begin(),map_queue.end(),compare);
	//////////////////////////////////////////////////////////////////////////
	return 0;
}

int carbarninfo::findemptycarport()
{
	//////////////////////////////////////////////////////////////////////////
	//���ҿ��೵λ
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
	//ʹ�±���id��Ӧ
	//index--;����ɾ����
	//////////////////////////////////////////////////////////////////////////
	if(index<1)return -1;
	if(index>map_queue.size())return -1;
	
	//////////////////////////////////////////////////////////////////////////
	//ת���ⲿ����Ϊ�ڲ�����

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
	//�ʼ�������ڲ��±�,�����ĳ��ⲿ�±�
	return map_queue[index].id;
	//////////////////////////////////////////////////////////////////////////
}

int carbarninfo::setentry(int index)
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

int carbarninfo::cancelentry(int index)
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
		AfxMessageBox("����ʧ��");
		return -1;
	}
	
	return 0;
}

int carbarninfo::deletecar(int index)
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
		AfxMessageBox("���ݿ�����ʧ��");
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
		AfxMessageBox("���ݿ�����ʧ��");
		return ;
	}
}
