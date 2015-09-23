#include <iostream>
#include <vector>
#include <algorithm>

#include "car_module.h"

using namespace std;

int main()
{
	car_module tmp;
	
	tmp.readdate();
	tmp.putinfo();
	printf("%d\n",tmp.findemptycarport());

	return 0;
}