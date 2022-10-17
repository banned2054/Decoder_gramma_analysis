#pragma once
#include "Global.h"

class First_Follow
{
public:
	First_Follow();

	string not_terminal[5]; //非终结符

	string terminal[9]; //终结符

	vector<int> first[5];  //FIRST集
	vector<int> follow[5]; //FOLLOW集

	string Forecast_Analysis_Table[5][8]; //预测分析表

	vector<string> mapping[5]; //生成式

	void Get_Forecast();
	bool Get_First(string, int);
	void Print_Forecast();

	vector<string> splitx(const string&, const string&);
};
