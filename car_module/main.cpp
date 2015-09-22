#include <iostream>
#include <vector>

using namespace std;

struct speed_location
{
	double time;
	int idle;
	int id;
};

class car_module
{
private:
	int mac;
	int rows;
	int cols;
	double speed_rows;
	double speed_cols;
	vector <speed_location> map_queue;
public:
	int readdate();
	int judgeposition(int num);
	int countqueue();

	void putinfo();
};

int car_module::readdate()
{
	FILE* fpin;
	fpin=fopen("date.txt","r");
	if(fpin==NULL)
	{
		printf("can not open date.txt\n");
		return 1;
	}
	fscanf(fpin,"%d\n",&mac);
	fscanf(fpin,"%d%d\n",&rows,&cols);
	fscanf(fpin,"%lf%lf\n",&speed_rows,&speed_cols);
	for(int i=0;i<rows*cols;i++)
	{
		speed_location tmp;
		fscanf(fpin,"%d",&tmp.id);
		tmp.idle=judgeposition(tmp.id);
		tmp.time=(i/rows)/speed_rows+(i%cols)/speed_cols;
		map_queue.push_back(tmp);
	}
	return 0;
}

int car_module::judgeposition(int num)
{
	return num>>(sizeof(int)*4);
}

int car_module::countqueue()
{
	return 0;
}

void car_module::putinfo()
{
	printf("%d\n",mac);
	printf("%d %d\n",rows,cols);
	printf("%lf %lf\n",speed_rows,speed_cols);
	for(int i=0;i<rows*cols;i++)
	{
		printf("rows=%2d cols=%2d id=%2d free=%2d time=%lf\n",i/rows,i%cols,map_queue[i].id,map_queue[i].idle,map_queue[i].time);
	}
	printf("\n");
}

int main()
{
	car_module tmp;
	tmp.readdate();
	tmp.putinfo();
	return 0;
}