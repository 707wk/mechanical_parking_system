#include <iostream>
#include <vector>
#include <algorithm>

#include "DataStructure.h"
#include "management.h"

using namespace std;

struct serverset serverinfo;

int readserverset()
{
	FILE* fp=fopen("serverSet.ini","r");
	if(fp==NULL)
	{
		printf("Î´ÕÒµ½ÅäÖÃÎÄ¼ş!");
		return -1;
	}

	fscanf(fp,"server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d",
		serverinfo.ip,serverinfo.name,serverinfo.password,serverinfo.database,&serverinfo.port);

	return 0;
}

int main()
{
	readserverset();

	for(;;)
	{
		printf("1:save 2:delete\n");
		getchar();
	}


	return 0;
}