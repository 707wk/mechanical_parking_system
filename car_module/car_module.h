/**************************************
 *FILE    :D:\c\car\car_module\car_module.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/9/23 11:04:13
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

#if !defined(_CAR_MODULE_)
#define _CAR_MODULE_

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct speed_location
{
	double time;                       //花费时间
	int idle;                          //空闲状态
	int id;                            //编号
};

class car_module
{
private:
	int mac;                           //车库模块地址
	int rows;                          //行
	int cols;                          //列
	double speed_rows;                 //行速度
	double speed_cols;                 //列速度
	vector <speed_location> map_queue; //位置列表

public:
	int readdate();

	int judgeposition(int num);        //获取空闲状态
	int getid(int num);                //获取id
	int getmac();                      //获取模块地址
	void setmac(int mac);              //设置模块地址
	int getrows();                     //获取车库行
	void setrows(int rows);            //设置车库行
	int getcols();                     //获取车库列
	void setcols(int cols);            //设置车库列
	double getspeedrows();             //获取行移动速度
	void setspeesrows(double rows);    //设置行移动速度
	double getspeedcols();             //获取列移动速度
	void setspeedcols(double cols);    //设置列移动速度
	int getrows(int location);         //获取location的行
	int getcols(int location);         //获取location的列
	int countqueue();                  //按花费时间从小到大排序
	int findemptycarport();            //查找最近的车位,未找到返回-1
	int savecar();                     //存车
	void savedatetomysql();            //保存数据到mysql

	void putinfo();
};
#endif
