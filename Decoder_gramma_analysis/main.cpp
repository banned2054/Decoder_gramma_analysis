#include "Gramma_analysis.h"

int main()
{
	Gramma_analysis gramma_analysis;
	cout << "请输入分析式：\n";
	bool flag = gramma_analysis.Analysis_start(); //进行词法分析和预测分析表生成

	cout << endl;
	if (!flag)
	{
		cout << "词法分析出错，错误原因：" + gramma_analysis.error_log[0];
		return 0;
	}
	cout << "词法分析结果：\n";
	gramma_analysis.print_word();
	cout << endl;
	gramma_analysis.Analysis(); //进行语法分析

	if (!gramma_analysis.error_log.empty()) //语法分析出错
	{
		cout << "语法分析出错，错误原因：" + gramma_analysis.error_log[0];
		return 0;
	}
	cout << "预测分析过程如下：\n";
	gramma_analysis.print_answer(); //输出语法分析结果

	return 0;
}
