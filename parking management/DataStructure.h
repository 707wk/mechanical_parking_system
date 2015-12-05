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

//用户设置
//保留
struct userdata
{
	char name[100];
	int jurisdiction;//权限
};

#endif