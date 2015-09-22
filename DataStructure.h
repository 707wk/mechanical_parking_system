
#ifndef _DataStructure_h_
#define _DataStructure_h_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//配置信息
struct serverset
{
	char ip[20];
	char name[100];
	char password[100];
	char database[100];
	int  port;
};

//登录账户
struct userdata
{
	char name[100];
	int jurisdiction;//权限
};

t_mapinfo//地图大小表
{
	int rows;//行
	int cols;//列
}

t_maplocation//地图表
{
	int rows;//行
	int cols;//列
	int object;
	/*
	0:路
	1:墙
	2:车库
	3:入口
	4:出口
	5:出口
	*/
}

t_garageinfo//车库表
{
	int MAC;//车库模块识别码
	int map_rows;//地图行坐标
	int map_cols;//地图列坐标
	int rows;//行
	int cols;//列
	TEXT location;//停放信息
}

t_carinfo//车辆表
{
	int id;//卡号  主键
	TEXT plate_number;//车牌号  索引
	double balance;//余额 小数位:2
	int MAC;//车库模块识别码
	int rows;//行
	int cols;//列
	timestamp start;//停放时间起点
	timestamp end;//停放时间终点
}

#endif