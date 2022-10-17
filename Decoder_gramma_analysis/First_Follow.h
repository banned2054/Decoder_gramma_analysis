#pragma once
#include "Global.h"

class First_Follow
{
public:
	First_Follow();

	string not_terminal[5]; //���ս��

	string terminal[9]; //�ս��

	vector<int> first[5];  //FIRST��
	vector<int> follow[5]; //FOLLOW��

	string Forecast_Analysis_Table[5][8]; //Ԥ�������

	vector<string> mapping[5]; //����ʽ

	void Get_Forecast();
	bool Get_First(string, int);
	void Print_Forecast();

	vector<string> splitx(const string&, const string&);
};
