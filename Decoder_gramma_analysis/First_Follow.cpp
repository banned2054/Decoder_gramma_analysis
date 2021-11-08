#include "First_Follow.h"

vector<string> First_Follow::splitx(const string& s, const string& spitter) {
	vector<string> ret; // 1
	int p1 = 0;
	int p2;
	int len = spitter.size();
	int slen = s.size();
	while (true) {
		p2 = s.find(spitter, p1);
		if (p2 == string::npos) p2 = slen;
		ret.push_back(s.substr(p1, p2 - p1));
		p1 = p2 + len;
		if (p1 > slen) break;
	}
	return ret;
}
First_Follow::First_Follow()
{
	/* 非终结符 */
	{
		not_terminal[E] = "E";
		not_terminal[EP] = "E\'";
		not_terminal[T] = "T";
		not_terminal[TP] = "T\'";
		not_terminal[F] = "F";
	}

	/* 终结符 */
	{
		terminal[0] = "+";
		terminal[1] = "-";
		terminal[2] = "*";
		terminal[3] = "/";
		terminal[4] = "(";
		terminal[5] = ")";
		terminal[6] = "num";
		terminal[7] = "$";
		terminal[8] = "null";
	}
	
	/* First集 */
	{
		{
			first[E].push_back(4);
			first[E].push_back(6);
		}
		{
			first[EP].push_back(0);
			first[EP].push_back(1);
			first[EP].push_back(8);
		}
		{
			first[T].push_back(4);
			first[T].push_back(6);
		}
		{
			first[TP].push_back(2);
			first[TP].push_back(3);
		}
		{
			first[F].push_back(4);
			first[F].push_back(6);
		}
	}
	/* Follow集 */
	{
		{
			follow[E].push_back(6);
			follow[E].push_back(7);
		}
		{
			follow[EP].push_back(5);
			follow[EP].push_back(7);
		}
		{
			follow[T].push_back(0);
			follow[T].push_back(1);
			follow[T].push_back(5);
			follow[T].push_back(7);
		}
		{
			follow[TP].push_back(0);
			follow[TP].push_back(1);
			follow[TP].push_back(5);
			follow[TP].push_back(7);
		}
		{
			follow[F].push_back(7);
			follow[F].push_back(0);
			follow[F].push_back(1);
			follow[F].push_back(2);
			follow[F].push_back(3);
		}
	}

	/* 生成式 */
	{
		mapping[E].push_back("T E\'");
		mapping[EP].push_back("- T E\'");
		mapping[EP].push_back("+ T E\'");
		mapping[EP].push_back("null");
		mapping[T].push_back("F T\'");
		mapping[TP].push_back("* F T\'");
		mapping[TP].push_back("/ F T\'");
		mapping[TP].push_back("null");
		mapping[F].push_back("( E )");
		mapping[F].push_back("num");
	}
}

void First_Follow::Get_Forecast()//生成预测分析表
{
	bool flag = false;
	for (int i = 0; i < 5; i++)
	{
		flag = false;
		for (int j = 0; j < mapping[i].size(); j++)//枚举生成式
		{
			flag = flag| Get_First(mapping[i][j],i);
		}
		if (flag)//生成式的FIRST集有ε
		{
			for (int j = 0; j < follow[i].size(); j++)
			{
				Forecast_Analysis_Table[i][follow[i][j]] = "ε";
			}
		}
		
	}
}
bool First_Follow::Get_First(string now_mapping,int now_num)//查询生成式的FIRST集
{
	bool flag = false;
	vector <string> words = splitx(now_mapping, " ");//切割单词，求每个生成式的FIRST
	if (words[0] == "null") return true;
	for (int i = 0; i < words.size(); i++)
	{
		bool flag1 = false;
		bool flag2 = false;
		for (int j = 0; j < 5; j++)//如果首部是非终结符
		{
			if(words[i] == not_terminal[j])
			{
				flag1 = true;
				for (int k = 0; k < first[j].size(); k++)
				{
					if (first[j][k] == 8)//非终结符的FIRST有空集
					{
						flag2 = true;
						continue;
					}
					Forecast_Analysis_Table[now_num][first[j][k]] = now_mapping;
				}
				break;
			}
		}
		if (flag1 && !flag2) //非终结符非空
		{
			flag = false;
			break;
		}
		if (flag1 && flag2) //非终结符含空
		{
			flag = true;
			continue;
		}
		for (int j = 0; j < 8; j++)//如果首部是终结符
		{
			if(words[i] == terminal[j])
			{
				flag = false;
				Forecast_Analysis_Table[now_num][j] = now_mapping;
				break;
			}
		}
		if (!flag) break;//首部是非终结符，且FIRST有空集
	}
	return flag;
}

void First_Follow::Print_Forecast() //打印预测分析表
{
	cout << "            ";
	string out_="| "+terminal[0];
	cout << std::left << setw(12)<<out_;
	for (int i = 1; i < 8; i++)
	{
		out_ = "| " + terminal[i];
		cout << std::left << setw(12)<<out_;
	}
	cout << endl;
	
	for (int i = 0; i < 5; i++)
	{
		out_ = "-";
		cout << setfill('-') << setw(108) << out_<<endl;
		out_ = "| " + not_terminal[i];
		cout <<setfill(' ') << std::left << setw(12) << out_;
		for (int j = 0; j < 8; j++)
		{
			setfill(' ');
			out_ = "| ";
			if (Forecast_Analysis_Table[i][j] == "") 
			{
				cout << std::left << setw(12)<<  out_;
				continue;
			}
			
			vector <string> words = splitx(Forecast_Analysis_Table[i][j], " ");
			string output = not_terminal[i]+"=>";
			for (int k = 0; k < words.size(); k++)
			{
				output += words[k];
			}
			out_ += output;
			cout << std::left << setw(12) <<out_;
		}
		cout << endl;
	}
}
