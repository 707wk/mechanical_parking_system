/**************************************
 *FILE    :D:\c\car\car_module\car_module.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:13
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

#if !defined(_MANAGEMENT_)
#define _MANAGEMENT_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class management
{
private:
	int findmac;                       //临时mac
	int index;                         //临时序号
	int rows;                          //临时横坐标
	int cols;                          //临时纵坐标
	MYSQL mysql;                       //mysql数据库
	MYSQL_RES *res;                    //查询结果集
	MYSQL_ROW column;                  //数据行的列

public:
	management();
	~management();

	void setfindmac(int mac);          //设置mac
	int getmac();                      //返回mac
	int getindex();                    //返回序号
	int getrows();                     //返回rows
	int getcols();                     //返回cols

	//////////////////////////////////////////////////////////////////////////
	/*存车
	{
		读取carid
			int mac=搜索最近的停车库
			int index=搜索mac车库的最近停车点
			将index换算成行列坐标
			存储到数据库
	}
	
	取车
	{
		读取carid
			int mac=carid.mac
			int index=(carid.rows-1)*cols+carid.cols;
		删除此条记录
	}
	*/////////////////////////////////////////////////////////////////////////
	int savecar(char* str);            //存车,未找到返回-1
	int deletecar(char* str);          //取车,未找到返回-1
	double countmoney(char* str);      //统计费用

	//void AfxMessageBox(char* str);
};
#endif

/*////////////////////////////////////////////////////////////////////////
id    	int
mac	    int
index	int
rows	int
cols	int
*/////////////////////////////////////////////////////////////////////////
