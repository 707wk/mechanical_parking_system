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

标志
{
	0x55
}

00000000 地址
{
	00000000~01111111
}

标志
{
	0xaa
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
*/////////////////////////////////////////////////////////////////////////

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
#define OFFLINE     0xff            //离线

//校验码
#define CHECKMOD    128             //校验取余
//////////////////////////////////////////////////////////////////////////
