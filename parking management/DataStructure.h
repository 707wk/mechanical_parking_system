/**************************************
 *FILE    :D:\c\car\parking management\DataStructure.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/4 21:12:25
 *TEXT    :结构头文件
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

#ifndef _DataStructure_h_
#define _DataStructure_h_

#include "StdAfx.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//系统设置
struct serverset
{
	char   ip[20];                     //数据库ip
	char   name[100];                  //数据库用户名
	char   password[100];              //数据库密码
	char   database[100];              //数据库名
	int    port;                       //数据库端口
	double cost;                       //费用(元/小时)(保留)
	int    mscomm;                     //端口号

	MYSQL  mysql;                      //mysql数据库
};

struct speed_location
{
	double time;                       //花费时间
	int idle;                          //空闲状态
		                               //0:空闲
	                                   //1:占用
	                                   //2:入口
	int id;                            //编号
};

struct carbarninfo
{
	int    id;                         //车库编号
	string name;                       //车库名
	int    nowstatus;                  //现状态
	int    oldstatus;                  //上一状态
	int    sumtotal;                   //车库容量
	int    spendtotal;                 //已存车辆数
	int    rows;                       //行
	int    cols;                       //列
	double speedrows;                  //行速度
	double speedcols;                  //列速度
	vector <speed_location> map_queue; //位置列表
};

//用户设置
//保留
struct userdata
{
	char name[100];
	int jurisdiction;//权限
};

#endif