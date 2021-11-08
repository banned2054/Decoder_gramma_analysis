#pragma once
#include "Global.h"
#include "Lexical_analysis.h"
#include "First_Follow.h"
class Gramma_analysis
{
private:
	#define MATCH_SUCCESS "匹配成功!"

	#define LEXICAL_FAIL "出现错误字符"
	#define MATCH_FAIL "匹配错误"
	#define NOT_END_SYNCH "预测分析表对应位置为空"
	
	Lexical_analysis lexical_;
	First_Follow first_follow_;

	vector <string> words;
	vector <string> types;

	vector <string> stack_out;
	vector <string> word_out;
	vector <string> answer;

	stack <string> stack_;
public:
	vector <string> error_log;
	
	bool Analysis_start();
	void Analysis();

	void print_answer();
	void print_word();
	
	int get_not_terminal(string);
	int get_terminal(string);

	void push_out();

	void error(int);
};