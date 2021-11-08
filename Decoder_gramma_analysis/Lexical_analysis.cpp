#include "Lexical_analysis.h"

Lexical_analysis::Lexical_analysis()
{

}

Lexical_analysis::Lexical_analysis(string file_name)
{
	input_file_name = file_name;
	input_file.open(file_name, ios::in);
}

void Lexical_analysis::Input_file_name(string file_name)
{
	input_file_name = file_name;
	input_file.open(file_name);
}

void Lexical_analysis::Read_file()
{
	string line = "";
	lines.clear();
	while (getline(input_file, line))
	{
		lines.push_back(line);
	}
}

void Lexical_analysis::Read_line()
{
	int max_lenght = 114514;
	string line;
	lines.clear();
	getline(cin, line);
	lines.push_back(line);
}

void Lexical_analysis::analysis_word()
{
	string line;
	int state = 0;
	int mark_line = 0;
	int mark_position = 0;
	for (int i = 0; i < lines.size(); i++)
	{
		line = lines[i];
		string word = "";
		for (int j = 0; j < line.size(); j++)
		{
			char now_char = line[j];
			switch(state)
			{
				case 0:
				{
					word = "";
					now_char = is_space(j, line);
					if (j >= line.size())
					{
						break;
					}
					word.push_back(now_char);
					if(is_digit(now_char))
					{
						state = 2;
						break;
					}
					switch (now_char)
					{
						case '/':
						{
							state = 0;
							words.push_back(word);
							types.push_back(IS_DIVIDER);
							break;
						}
						case '+':
						{
							state = 0;
							words.push_back(word);
							types.push_back(IS_ADDTION);
							break;
						}
						case '-':
						{
							state = 0;
							words.push_back(word);
							types.push_back(IS_SUBTRATION);
							break;
						}
						case '*':
						{
							state = 0;
							words.push_back(word);
							types.push_back(IS_MULTPLY);
							break;
						}
						case '(':
						{
							state = 0;
							words.push_back(word);
							types.push_back(IS_LEFT_BRACKET);
							break;
						}
						case ')':
						{
							state = 0;
							words.push_back(word);
							types.push_back(IS_RIGHT_BRACKET);
							break;
						}
						default:
						{
							state = 15;
							word.pop_back();
							break;
						}
					}
					break;
				}
				case 2:
				{
					if(is_digit(now_char))
					{
						word.push_back(now_char);
						state = 2;
						break;
					}
					switch (now_char)
					{
						case '.':
						{
							state = 3;
							word.push_back(now_char);
							break;
						}
						case 'E':
						{
							state = 5;
							word.push_back(now_char);
							break;
						}
						default:
						{
							j--;
							state = 0;
							words.push_back(word);
							types.push_back(IS_NUMBER);
							break;
						}
					}
					break;
				}
				case 3:
				{
					if(is_digit(now_char))
					{
						state = 4;
						word.push_back(now_char);
					}
					else
					{
						state = 0;
						words.push_back(word);
						types.push_back(IS_NUMBER);
						error(i, j, NUMBER_ERROR_P);
					}
					break;
				}
				case 4:
				{
					if(is_digit(now_char))
					{
						state = 4;
						word.push_back(now_char);
					}
					else if(now_char == 'E')
					{
						state = 5;
						word.push_back(now_char);
					}
					else
					{
						j--;
						state = 0;
						words.push_back(word);
						types.push_back(IS_NUMBER);
					}
					break;
				}
				case 5:
				{
					if(is_digit(now_char))
					{
						state = 7;
						word.push_back(now_char);
					}
					else if(now_char == '+'||now_char == '-')
					{
						state = 6;
						word.push_back(now_char);
					}
					else
					{
						j--;
						words.push_back(word);
						types.push_back(IS_NUMBER);
						error(i, j, NUMBER_ERROR_E);
					}
					break;
				}
				case 6:
				{
					if(is_digit(now_char))
					{
						state = 7;
						word.push_back(now_char);
					}
					else
					{
						j--;
						words.push_back(word);
						types.push_back(IS_NUMBER);
						error(i, j, OPERATOR_ERROR);
					}
					break;
				}
				case 7:
				{
					if(is_digit(now_char))
					{
						state = 7;
						word.push_back(now_char);
					}
					else
					{
						j--;
						words.push_back(word);
						types.push_back(IS_NUMBER);
						state = 0;
					}
					break;
				}
				case 15:
				{
					error(i, --j, CHAR_ERROR);
					state = 0;
					break;
				}
			}
			if(j >= line.size()-1)
			{
				if (state >= 2 && state <= 7)
				{
					words.push_back(word);
					types.push_back(IS_NUMBER);
				}
			}
		}
	}
}

bool Lexical_analysis::is_digit(char character)
{
	return (character >= '0') && (character <= '9');
}

bool Lexical_analysis::is_letter(char character)
{
	return ((character >= 'a') && (character <= 'z'))|| ((character >= 'A') && (character <= 'Z')) || character == '_';
}

char Lexical_analysis::is_space(int& j, string line)
{
	char now = line[j];
	while(now == ' ')
	{
		j++;
		if (j >= line.size())
		{
			return ' ';
		}
		now = line[j];
		
	}
	return now;
}

void Lexical_analysis::error(int line_number, int position,int wrong_type)
{
	string wrong_reason = "threr is an error in line "+std::to_string(line_number)+" on " + std::to_string(position)+"\n\tThe reason is:";
	switch (wrong_type)
	{
		case NUMBER_ERROR_P:
		{
			wrong_reason += WRONG_NUMBER_POINT;
			break;
		}
		case NUMBER_ERROR_E:
		{
			wrong_reason += WRONG_NUMBER_E;
			break;
		}
		case CHAR_ERROR:
		{
			wrong_reason += WRONG_CHAR;
			break;
		}
		case OPERATOR_ERROR:
		{
			wrong_reason += WRONG_OPERATOR;
			break;
		}
	}
	error_list.push_back(wrong_reason);
}
