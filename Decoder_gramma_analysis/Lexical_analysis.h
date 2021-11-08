#pragma once
#include "Global.h"

class Lexical_analysis
{
private:
	//#define KEYWORDS_SIZE 22

	#define NUMBER_ERROR_P 1
	#define NUMBER_ERROR_E 2
	#define CHAR_ERROR 3
	#define OPERATOR_ERROR 4
	
	#define WRONG_CHAR			"There is a wrong character."
	#define WRONG_NUMBER_E		"A number can't have char except a E."
	#define WRONG_NUMBER_POINT	"The point's behind can only be number."
	#define WRONG_OPERATOR		"The operator's behind can only be number."
	
	ifstream input_file;

	string input_file_name;
	vector <string> lines;

public:
	vector <string> words;
	vector <string> types;
	vector <string> error_list;
	
	Lexical_analysis();
	Lexical_analysis(string);
	void Input_file_name(string);
	void Read_file();
	void Read_line();
	void analysis_word();
	void error(int, int, int);

	bool is_letter(char);
	bool is_digit(char);
	char is_space(int&, string);
};

