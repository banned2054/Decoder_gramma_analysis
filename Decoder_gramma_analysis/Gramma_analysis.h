#pragma once
#include "Global.h"
#include "Lexical_analysis.h"
#include "First_Follow.h"
class Gramma_analysis
{
private:
#define MATCH_SUCCESS "∆•≈‰≥…π¶!"
	
	Lexical_analysis lexical_;
	First_Follow first_follow_;

	vector <string> words;
	vector <string> types;

	vector <string> stack_out;
	vector <string> word_out;
	vector <string> answer;

	stack <string> stack_;
public:
	void Analysis_start();
	void Analysis();

	void print_answer();
	void print_word();
	
	int get_not_terminal(string);
	int get_terminal(string);

	void push_out();

	void error();
};

