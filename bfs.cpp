struct 队列
{
	int rows;//行
	int cols;//列
	* 前驱节点;
	来源方向;
}

struct 路径点
{
	int roes;//行
	int cols;//列
}
int way[]={0,1,2,3};上下左右

int coordinate[4];
//01
//23

bfs
{
	读取地图
	创建临时数组
	创建队列
	将起点压入顶部

	int 分支数=1;
	int head=队列顶
	for(;;)
	{
		int len=0;
		for(int i=0;i<分支数;i++)
		{
			for(int j=0;j<4;j++)
			{
				struct temp;
				if(j==来源方向)continue;
				temp.rows=j%2?head.rows+way[j]-2:head.rows;
				temp.cols=j%2?head.cols:head.cols+way[j]-1;
				if(越界)continue;
				if(走过)continue;
				if(到达)goto end;
				else
				{
					队列.push(temp);
					len++;
				}
			}
			head++;
		}
		分支数=len;
	}
	end;
	获取行列坐标;
	读取车库信息;
	vector  路径点
	for(;;)
	{
		if(节点==起点)beak;
		将位置插入第一个位置;
	}
	输出路径
}