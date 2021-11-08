#include "Gramma_analysis.h"

void Gramma_analysis::Analysis_start()
{
	lexical_.Read_line();
	lexical_.analysis_word();
	words = lexical_.words;

	first_follow_.Get_Forecast();

	stack_.push("$");
	stack_.push("E");
}

void Gramma_analysis::Analysis()
{
	string now = stack_.top();
	stack_.top();

	while(!stack_.empty())
	{
		if (get_terminal(now) != -1)
		{
			if(words[0] == now)
			{
				words.erase(words.begin());
			}
			else
			{
				error();
			}
		}
		if (get_not_terminal(now) != -1)
		{
			int word_number = get_terminal(words[0]);
			int now_number = get_not_terminal(now);
			string generative = first_follow_.Forecast_Analysis_Table[now_number][word_number];
			if (generative != "")
			{
				string now_answer = now + "=>" + generative;
				answer.push_back(now_answer);
				
				vector <string> word = first_follow_.splitx(generative, " ");

				for (int i = word.size() - 1; i >= 0; i--)
				{
					stack_.push(word[i]);
				}
			}
			else
			{
				error();
			}
		}
		now = stack_.top();
		stack_.pop();
	}
}

void Gramma_analysis::print_answer()
{
	for(int i =0;i<answer.size();i++)
	{
		cout << answer[i] << endl;
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

void Gramma_analysis::error()
{
	
}