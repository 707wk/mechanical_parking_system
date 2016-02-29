#include <iostream>
#include <stdio.h>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//读取地图
void readmapinfo()
{
	FILE* fpin;
	fpin=fopen("map.tmx","r");
	if(fpin==NULL)
	{
		printf("mapinfo:地图文件未找到!");
		exit(1);
	}
	int width;
	int height;
	fscanf(fpin,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<map version=\"1.0\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"20\" height=\"20\" tilewidth=\"32\" tileheight=\"32\" nextobjectid=\"1\">\n\
 <tileset firstgid=\"1\" name=\"001\" tilewidth=\"32\" tileheight=\"32\" tilecount=\"100\">\n\
  <image source=\"map.bmp\" width=\"320\" height=\"320\"/>\n\
 </tileset>\n\
 <layer name=\"map\" width=\"%d\" height=\"%d\">\n\
  <data>",&width,&height);
	printf("%d %d\n",width,height);

	int* maplocation;
	maplocation=(int*)malloc(sizeof(int)*width*height);

	int entrance[3][2];
	int quit[3][2];
	int location[30][2];

	for(int i=0;i<30;i++)
		location[i][0]=location[i][1]=-1;

	for(i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			fscanf(fpin,"   <tile gid=\"%d\"/>",maplocation+i*width+j);
			int index=*(maplocation+i*width+j);
			if(index==34)
				*(maplocation+i*width+j)=-1;
			else if(index==31)
			{
				entrance[0][0]=i;
				entrance[0][1]=j;
			}
			else if(index==32)
			{
				entrance[1][0]=i;
				entrance[1][1]=j;
			}
			else if(index==33)
			{
				entrance[2][0]=i;
				entrance[2][1]=j;
			}
			else if(index==41)
			{
				quit[0][0]=i;
				quit[0][1]=j;
			}
			else if(index==42)
			{
				quit[1][0]=i;
				quit[1][1]=j;
			}
			else if(index==43)
			{
				quit[2][0]=i;
				quit[2][1]=j;
			}
			else if(index>0&&index<=30)
			{
				location[index-1][0]=i;
				location[index-1][1]=j;
			}
			else if(index==35||
					index==36||
					index==37||
					index==38||
					index==39||
					index==44||
					index==45||
					index==46||
					index==47||
					index==48||
					index==49)
					*(maplocation+i*width+j)=0;
		}
	}

	for(i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(*(maplocation+i*width+j)==31||
				*(maplocation+i*width+j)==32||
				*(maplocation+i*width+j)==33)
				printf(" in");
			else if(*(maplocation+i*width+j)==41||
					*(maplocation+i*width+j)==42||
					*(maplocation+i*width+j)==43)
				printf("out");
			else
				printf("%3d",*(maplocation+i*width+j));
		}
		printf("\n");
	}

	printf("entrance:\n");
	for(i=0;i<3;i++)printf("%d:%d %d\t",i,entrance[i][0],entrance[i][1]);
	printf("\n");

	printf("quit:\n");
	for(i=0;i<3;i++)printf("%d:%d %d\t",i,quit[i][0],quit[i][1]);
	printf("\n");
	
	int sum=0;
	printf("location:\n");
	for(i=0;i<30;i++)
	{
		if(location[i][0]!=-1)
		{
			sum++;
			printf("%d\t%d:%d %d\n",sum,i,location[i][0],location[i][1]);
		}
	}
	printf("\n");
}

int main()
{
	readmapinfo();
	return 0;
}
