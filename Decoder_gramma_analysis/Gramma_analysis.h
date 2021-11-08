#pragma once
#include "Global.h"
#include "Lexical_analysis.h"
#include "First_Follow.h"
class Gramma_analysis
{
private:
	#define MATCH_SUCCESS "ƥ��ɹ�!"

	#define LEXICAL_FAIL "���ִ����ַ�"
	#define MATCH_FAIL "ƥ�����"
	#define NOT_END_SYNCH "Ԥ��������Ӧλ��Ϊ��"
	
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