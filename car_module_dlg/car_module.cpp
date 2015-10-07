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
		tmp.id=i+1;
		tmp.idle=0;
		fscanf(fpin,"%d",&tmp.id);
		if(!feof(fpin))
		{
		tmp.idle=judgeposition(tmp.id);
		tmp.id=getid(tmp.id)-1;
		}

		if(tmp.idle==2)sumcar--;
		if(!tmp.idle)spendcar++;

		//突然发现不需要用到rows值计算时间
		//难怪一直找不到问题出在哪
		tmp.time=(tmp.id/cols)/speed_rows+(tmp.id%cols)/speed_cols;
		map_queue.push_back(tmp);
	}
	fclose(fpin);
	countqueue();
	return 0;
}

int car_module::readdate(int mac)
{
	this->mac=mac;
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

void car_module::setspeesrows(double rows)
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

	savedatetomysql();

	return index;
}

int car_module::deletecar(int index)
{
	if(index<0)return -1;
	if(index>=map_queue.size())return -1;
	if(map_queue[index].idle==0)return -1;
	map_queue[index].idle=0;

	savedatetomysql();

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
	for(int i=0;i<rows*cols;i++)
	{
		fprintf(fpout,"%d ",combine(map_queue[i].id,map_queue[i].idle));
	}
	fclose(fpout);
	return 0;
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

