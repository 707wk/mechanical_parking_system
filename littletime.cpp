

struct 车位
{
	int rows;//行
	int cols;//列
	double spendtime;//花费时间
	int car;//是否停车
}

class garageinfo
{
private:
	int rows;//行
	int cols;//列
	int sumcar;//容量
	int spendcar;//已停车量
	double rowsspeed;//上下速度
	double colsspeed;//左右速度
	vector <车位> 最小时间地址;
public:
	void setspeed(double rows,double cols);
	double getrowsspeed();		
	double getcolsspeed();
	int insertcar(车位 car);
	int removecar(车位 car);
}