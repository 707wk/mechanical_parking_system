/**************************************
 *FILE    :D:\c\car\parking management\carbarninfo.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/5 19:48:19
 *TEXT    :车库模块:只负责车库信息
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

#if !defined(_CARBARNINFO_)
#define _CARBARNINFO_

#include "StdAfx.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct speed_location
{
	double time;                       //花费时间
	int idle;                          //空闲状态
		                               //0:空闲
	                                   //1:占用
	                                   //2:入口
	int id;                            //编号
};

class carbarninfo
{
private:
	int    id;                         //车库编号
	string name;                       //车库名
	int    nowstatus;                  //现状态
	int    oldstatus;                  //上一状态
	string command;                    //正在执行的命令
	int    sumcar;                     //总存车量
	int    spendcar;                   //已存车量
	int    map_rows;                   //第几行
	int    map_cols;                   //第几列
	int    rows;                       //行
	int    cols;                       //列
	double speed_rows;                 //横向移动速度
	double speed_cols;                 //纵向移动速度
	vector <speed_location> map_queue; //位置列表
	//MYSQL  mysql;                      //mysql数据库
	//MYSQL_RES *res;                  //查询结果集
	//MYSQL_ROW column;                //数据行的列

public:
	carbarninfo();
	~carbarninfo();
	//////////////////////////////////////////////////////////////////////////
	//函数重载挺蛋疼的
	//int checkfist();                 //检测是否初始化
	//int readdate();                  //从文件读取数据
	//////////////////////////////////////////////////////////////////////////
	int readdate(string name);         //从mysql读取车库信息
	int judgeposition(int num);        //获取空闲状态
	                                   //0:空闲
	                                   //1:占用
	                                   //2:入口
	void setcompotr(int num);          //设置端口号
	int getcompotr();                  //获取端口号
	int getid(int num);                //获取id
	int getcond(int num);              //获取状态
	int combine(int id,int idle);      //合并id和空闲状态
	string getname();                  //获取模块名
	void setname(string name);         //设置模块名
	int getsumcar();                   //获取总量
	int getspendcar();                 //获取已存车量
	int getcondition();                //获取状态
	void setconditopn(int num);        //设置状态
	int getrows();                     //获取车库行
	void setrows(int rows);            //设置车库行
	int getcols();                     //获取车库列
	void setcols(int cols);            //设置车库列
	double getspeedrows();             //获取行移动速度
	void setspeedrows(double rows);    //设置行移动速度
	double getspeedcols();             //获取列移动速度
	void setspeedcols(double cols);    //设置列移动速度
	int getrows(int location);         //获取location的行
	int getcols(int location);         //获取location的列
	int countqueue();                  //按花费时间从小到大排序
	int findemptycarport();            //查找最近的车位,未找到返回-1
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
	int savecar();                     //存车,未找到返回-1
	int deletecar(int index);          //取车,未找到返回-1
	//int savedatetomysql();           //保存数据到文件
	int savedatetomysql(string name);  //保存数据到mysql
	int clear();                       //清空库存数据[已废弃]
	void deletedate();                 //删除模块

	/*////////////////////////////////////////////////////////////////////////
	增加 setentry(int index)［设置入口］ 
		 cancelentry(int index) ［取消入口］ 
		 newgarage() ［创建车库］
		 switchid() ［外部坐标转换为内部坐标］
	*/////////////////////////////////////////////////////////////////////////
	int setentry(int index);           //设置入口
	int cancelentry(int index);        //取消入口
	int newgarage();                   //创建队列
	int switchid(int index);           //外部坐标转换为内部坐标

	//void putinfo();                  //输出信息[终端用]
};
#endif
