#pragma once
#include "Global.h"
#include "Lexical_analysis.h"
#include "First_Follow.h"
class Gramma_analysis
{
private:
	Lexical_analysis lexical_;
	First_Follow first_follow_;

	vector <string> words;
	vector <string> answer;

	stack <string> stack_;
public:
	void Analysis_start();
	void Analysis();

	void print_answer();
	
	int get_not_terminal(string);
	int get_terminal(string);

	void error();
};

