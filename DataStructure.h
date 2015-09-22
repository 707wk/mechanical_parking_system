
#ifndef _DataStructure_h_
#define _DataStructure_h_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//������Ϣ
struct serverset
{
	char ip[20];
	char name[100];
	char password[100];
	char database[100];
	int  port;
};

//��¼�˻�
struct userdata
{
	char name[100];
	int jurisdiction;//Ȩ��
};

t_mapinfo//��ͼ��С��
{
	int rows;//��
	int cols;//��
}

t_maplocation//��ͼ��
{
	int rows;//��
	int cols;//��
	int object;
	/*
	0:·
	1:ǽ
	2:����
	3:���
	4:����
	5:����
	*/
}

t_garageinfo//�����
{
	int MAC;//����ģ��ʶ����
	int map_rows;//��ͼ������
	int map_cols;//��ͼ������
	int rows;//��
	int cols;//��
	TEXT location;//ͣ����Ϣ
}

t_carinfo//������
{
	int id;//����  ����
	TEXT plate_number;//���ƺ�  ����
	double balance;//��� С��λ:2
	int MAC;//����ģ��ʶ����
	int rows;//��
	int cols;//��
	timestamp start;//ͣ��ʱ�����
	timestamp end;//ͣ��ʱ���յ�
}

#endif