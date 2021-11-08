#pragma once
#include "Global.h"

class First_Follow
{
public:
	First_Follow();

	string not_terminal[5];

	string terminal[9];
	
	vector <int> first[5];
	vector <int> follow[5];
	
	string Forecast_Analysis_Table[5][8];

	vector<string> mapping[5];

	void Get_Forecast();
	bool Get_First(string,int);
	void Print_Forecast();

	vector<string> splitx(const string&, const string&);
};

