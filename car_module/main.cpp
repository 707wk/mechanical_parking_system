#include <iostream>
#include <vector>
#include <algorithm>

#include "DataStructure.h"
#include "car_module.h"

using namespace std;

struct serverset serverinfo;

int readserverset()
{
	FILE* fp=fopen("serverSet.ini","r");
	if(fp==NULL)
	{
		printf("Œ¥’“µΩ≈‰÷√Œƒº˛!");
		return -1;
	}

	fscanf(fp,"server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d",
		serverinfo.ip,serverinfo.name,serverinfo.password,serverinfo.database,&serverinfo.port);

	return 0;
}

int main()
{
	readserverset();

	car_module tmp;
	
	tmp.readdate();
	tmp.putinfo();
	printf("%d\n",tmp.findemptycarport());
	printf("%d\n",tmp.savecar());
	tmp.putinfo();

	for(;;)
	{
		int a;
		int b;
		printf("1:save 2:delete\n");
		scanf("%d %d",&a,&b);
		getchar();
		switch(a)
		{
		case 1:
			tmp.savecar();
			break;
		case 2:
			tmp.deletecar(b);
			break;
		}
		tmp.putinfo();
	}


	return 0;
}