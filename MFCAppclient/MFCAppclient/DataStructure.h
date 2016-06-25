/**************************************
 *FILE          :T:\car\MFCAppclient\MFCAppclient\DataStructure.h
 *AUTHOR        :707wk
 *ORGANIZATION  :GT-Soft Studio
 *LAST-MODIFIED :2016/6/18 19:40:21
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

#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include "StdAfx.h"
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define COMLEN 1024                    //命令缓存长度

struct comNode
{
	int  IOCTL;                        //控制码
	char strplate[COMLEN];             //车牌号
	int  ioputid;                      //出入口id
};

//系统设置
struct serverset
{
	int    ioId;                       //id
	char   ip[100];                    //服务器ip
	int    iocpport;                   //socket端口
	int    intervaltime;               //查询间隔

	int    overtime;                   //超时时间
	int    maxovertime;                //最大超时时间

	queue<struct comNode> command;     //等待队列
	char   iobuf[COMLEN];              //接收发送字符串
};

//用户设置
//保留
struct userdata
{
	char name[100];
	int jurisdiction;                  //权限
};

#endif