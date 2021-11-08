#include "Gramma_analysis.h"

bool Gramma_analysis::Analysis_start()
{
	lexical_.Read_line();
	lexical_.analysis_word();

	if(!lexical_.error_list.empty())
	{
		error_log.push_back(LEXICAL_FAIL);
		return false;
	}
	
	words = lexical_.words;
	types = lexical_.types;
	types.push_back("$");

	first_follow_.Get_Forecast();

	stack_.push("$");
	stack_.push("E");
	return true;
}

void Gramma_analysis::Analysis()
{
	string now;
	
	while(!stack_.empty())
	{
		now = stack_.top();
		if (get_terminal(now) != -1)//终结符
		{
			if(types[0] == now)
			{
				types.erase(types.begin());
				push_out();
				stack_.pop();
				answer.push_back(MATCH_SUCCESS);
			}
			else
			{
				error(1);
				return;
			}
		}
		if (get_not_terminal(now) != -1)//非终结符
		{
			int word_number = get_terminal(types[0]);
			int now_number = get_not_terminal(now);
			string generative = first_follow_.Forecast_Analysis_Table[now_number][word_number];
			if (generative != "")
			{
				vector <string> word = first_follow_.splitx(generative, " ");

				string now_answer = now + "=>";
				for(int i =0;i<word.size();i++)
				{
					now_answer += word[i];
				}
				answer.push_back(now_answer);

				push_out();
				stack_.pop();
				
				for (int i = word.size() - 1; i >= 0; i--)
				{
					if (word[i] == "ε") continue;
					stack_.push(word[i]);
				}
			}
			else
			{
				error(0);
				return;
			}
		}
	}
}

void Gramma_analysis::print_answer()
{
	int set_w_stack = stack_out[0].size(), set_w_word = word_out[0].size(),set_w_answer = answer[0].size();
	for (int i = 1; i < answer.size(); i++)
	{
		set_w_stack = set_w_stack > stack_out[i].size() ? set_w_stack : stack_out[i].size();
		set_w_word = set_w_word > word_out[i].size() ? set_w_word : word_out[i].size();
		set_w_answer = set_w_answer > answer[i].size() ? set_w_answer : answer[i].size();
	}

	cout << left << setw(set_w_stack) << "栈";
	cout << "  ";
	cout << left << setw(set_w_word) << "输入";
	cout << "  ";
	cout << left << setw(set_w_answer) << "输出" << endl;
	
	for (int i = 0; i < answer.size(); i++)
	{
		cout << left << setw(set_w_stack) << stack_out[i];
		cout << "  ";
		cout << left << setw(set_w_word) << word_out[i];
		cout << "  ";
		cout << left << setw(set_w_answer) << answer[i] << endl;
	}
	return;
}


int Gramma_analysis::get_not_terminal(string now)
{
	for (int i = 0; i < 5; i++)
	{
		if (now == first_follow_.not_terminal[i]) return i;
	}
	return -1;
}
int Gramma_analysis::get_terminal(string now)
{
	for (int i = 0; i < 8; i++)
	{
		if (now == first_follow_.terminal[i]) return i;
	}
	return -1;
}

void Gramma_analysis::error(int mode)
{
	if (mode) error_log.push_back(MATCH_FAIL);
	else error_log.push_back(NOT_END_SYNCH);
}
void Gramma_analysis::print_word()
{
	for (int i = 0; i < words.size(); i++)
	{
		cout << types[i] << " ";
	}
	cout << endl;
}

void Gramma_analysis::push_out()
{
	string stack_string = "";

	stack <string> stack_temp;
	while(!stack_.empty())
	{
		stack_temp.push(stack_.top());
		stack_.pop();
		stack_string = stack_temp.top() + stack_string;
	}
	while(!stack_temp.empty())
	{
		stack_.push(stack_temp.top());
		stack_temp.pop();
	}
	stack_out.push_back(stack_string);

	string word_string = "";
	for (int i = 0; i < types.size(); i++)
	{
		word_string += types[i] + " ";
	}
	word_out.push_back(word_string);
}
