/**************************************
 *FILE          :C:\Users\707wk\Desktop\CWayFinding.h
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/3/26 下午 10:49:16
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


#if !defined(_CWAYFINDING_)
#define _CWAYFINDING_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

//地图数组
struct maptype
{
	int type;                          //类型
                                       //"0">墙壁
                                       //"1">入口
                                       //"2">出口
                                       //"3">车库模块
                                       //"4">道路
	int id;                            //编号
	int flage;                         //是否已经过
};

//地图路径
struct mapway
{
	int x;                             //横坐标
	int y;                             //纵坐标
};

class CWayFinding
{
private:
	int map_x;                         //地图行
	int map_y;                         //地图列
	struct maptype** maplocation;      //地图记录

public:
	CWayFinding();
	~CWayFinding();

	void initmap();                    //初始地图数组
	int nearestcarport(int id);        //查找最近车库
	int nearestexit(int id);           //查找最近出口
	void putinfo();                    //输出地图
	void clearflage();                 //清空标志位
};
#endif

