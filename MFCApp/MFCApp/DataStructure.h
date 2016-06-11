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

#define COMLEN 1024                    //命令缓存长度

//系统设置
struct serverset
{
	char   ip[100];                    //数据库ip
	char   name[100];                  //数据库用户名
	char   password[100];              //数据库密码
	char   database[100];              //数据库名
	int    dataport;                   //数据库端口
	int    iocpport;                   //socket端口
	double cost;                       //费用(元/小时)(保留)

	char   mscomm[255];                //端口号
	char   mscommini[100];             //连接参数
	int    BaudRate;                   //波特率为9600
	int    ByteSize;                   //每个字节有8位
	int    Parity;                     //无奇偶校验位
	int    StopBits;                   //两个停止位

	int    intervaltime;               //查询间隔
	
	MYSQL  mysql;                      //mysql数据库
};

//用户设置
//保留
struct userdata
{
	char name[100];
	int jurisdiction;                  //权限
};

//车库模块id查找表
struct idLUT
{
	int id;                            //车库id
	int index;                         //在队列中的位置
};

#endif