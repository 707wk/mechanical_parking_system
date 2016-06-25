/**************************************
 *FILE    :D:\c\car\parking management\ControlCode.h
 *PROJECT :NULL
 *AUTHOR  :707wk
 *CREATED :2015/12/4 21:13:36
 *TEXT    :控制码头文件
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

/*////////////////////////////////////////////////////////////////////////
串口

标志
{
	奇偶位为1
}

00000000 地址
{
	00000000~01111111
}

标志
{
	奇偶位为0
}

00000000 控制码
{
	0x01 存车
	0x02 取车
	0x03 获取机械臂位置
	0x04 读取模块状态
	{
		控制码
		状态
	}
	0x05 紧急停止
	0x06 复位
}

00000000 数据
{
	横坐标
	纵坐标
	状态标识
	{
		控制码
		完成状态
	}
	范围 1-127
}

发送数据
{
	标志 地址 标志 控制码 数据 校验
	1字节1字节1字节1字节1字节
}

接收数据
{
	地址 状态
	状态
	{
		0:空闲
		1:存车
		2:取车
		3:停止
		4:复位
	}
	机械臂位置
	{
		横坐标
		纵坐标
	}
	校验

	地址 状态 数据 校验
	1字节1字节1字节1字节1字节
}
////////////////////////////////////////////////////////////////////////*/
//////////////////////////////////////////////////////////////////////////
//控制码
#define SAVECAR     0x01            //存车
#define DELETECAR   0x02            //取车
#define GETLOCATION 0x03            //获取机械臂位置
#define GETSTATE    0x04            //读取模块状态
#define STOP        0x05            //紧急停止
#define RESET       0x06            //复位

//状态码
#define STATEFREE   0x00            //空闲
#define STATESAVE   0x01            //存车
#define STATEDELETE 0x02            //取车
#define STATESTOP   0x03            //停止
#define STATERSET   0x04            //复位
#define ACCEPTED    0x05            //已接收
#define BUSY        0x06            //运行中
#define ONLINE      0x0f            //在线
#define OFFLINE     0xff            //离线

//校验码
#define CHECKMOD    128             //校验取余

//地址标志
#define ADDFIRST    (char)0x55      //首标志
#define ADDEND      (char)0xaa      //尾标志
//////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////////////
sock

接收数据
{
	INPUTSAVE      请求码[unsigned char] 分隔符 车牌号[char 40] 分隔符 入口id
	OUTPUTDELE     请求码[unsigned char] 分隔符 车牌号[char 40]
	OUTPUTGARAGE   请求码[unsigned char] 分隔符 车牌号[char 40]
	RESERVATION    请求码[unsigned char] 校验[unsigned char]
	UNRESERVATION  请求码[unsigned char] 校验[unsigned char]
	GETGARAGEINFO  请求码[unsigned char] 校验[unsigned char]
	PANTBAG        请求码[unsigned char] 分隔符 id
}

发送数据
{
	INPUTSAVE      返回码[unsigned char] 分隔符 最近车库编号[int]
	OUTPUTDELE     返回码[unsigned char] 分隔符 存储时间[double] 分隔符 收费[double]
	OUTPUTGARAGE   返回码[unsigned char]
	RESERVATION    返回码[unsigned char]
	UNRESERVATION  返回码[unsigned char]
	GETGARAGEINFO  返回码[unsigned char] 分隔符 剩余车位[int] 分隔符 剩余时间[int]
	PANTBAG        请求码[unsigned char] 分隔符 总车位[int]   分隔符 剩余车位[int]
}
////////////////////////////////////////////////////////////////////////*/
//////////////////////////////////////////////////////////////////////////
//请求码
#define INPUTSAVE      0x01         //入口存车
#define OUTPUTDELE     0x02         //出口出车
#define OUTPUTGARAGE   0x03         //车库模块取车
#define RESERVATION    0x04         //预约存车
#define UNRESERVATION  0x05         //取消预约
#define GETGARAGEINFO  0x06         //获取停车场信息
#define PANTBAG        0x07         //心跳包

//返回码
#define TASKSUCCEED    0x01         //请求成功
#define NOCAR          0x02         //车位已满
#define GARAGEBUSY     0x03         //无空闲模块
#define NOTFOUND       0x04         //未找到车辆
#define PLATEREPEAT    0x05         //车牌重复
#define NOTOUTPUT      0x06         //未找到出口
#define NOTDEFINE      0x07         //未定义的请求
#define TASKFAIL       0xff         //请求失败
//////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////////////
web用户
权限
{
	1:超级管理员
	2:管理员
	3:来宾
}
////////////////////////////////////////////////////////////////////////*/
