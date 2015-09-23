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
	for(int i=0;i<rows*cols;i++)
	{
		speed_location tmp;
		fscanf(fpin,"%d",&tmp.id);
		tmp.idle=judgeposition(tmp.id);
		tmp.id=getid(tmp.id)-1;
		//突然发现不需要用到rows值计算时间
		//难怪一直找不到问题出在哪
		tmp.time=(tmp.id/cols)/speed_rows+(tmp.id%cols)/speed_cols;
		map_queue.push_back(tmp);
	}
	countqueue();
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

int car_module::getmac()
{
	return this->mac;
}

void car_module::setmac(int mac)
{
	this->mac=mac;
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
	for(int i=0;i<map_queue.size();i++)
	{
		if(map_queue[i].idle==0)
		{
			return i;
		}
	}
	return -1;
}

int car_module::savecar()
{
	int index=findemptycarport();
	if(index==-1)return index;
	map_queue[index].idle=1;
	return index;
}

void car_module::savedatetomysql()
{
}

void car_module::putinfo()
{
	printf("%d\n",mac);
	printf("%d %d\n",rows,cols);
	printf("%lf %lf\n",speed_rows,speed_cols);

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
		printf("rows=%2d cols=%2d id=%2d free=%2d time=%lf\n",map_queue[i].id/cols,map_queue[i].id%cols,map_queue[i].id,map_queue[i].idle,map_queue[i].time);
	}
	printf("\n");
}