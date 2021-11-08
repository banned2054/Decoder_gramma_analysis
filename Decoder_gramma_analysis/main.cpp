#include "Gramma_analysis.h"

int main()
{
	Gramma_analysis gramma_analysis;
	cout << "请输入分析式：\n";
	bool flag =  gramma_analysis.Analysis_start();

	cout << endl;
	if(!flag)
	{
		cout << "词法分析出错，错误原因：" + gramma_analysis.error_log[0];
		return 0;
	}
	cout << "词法分析结果：\n";
	gramma_analysis.print_word();
	cout << endl;
	gramma_analysis.Analysis();

	if(!gramma_analysis.error_log.empty())
	{
		cout << "语法分析出错，错误原因：" + gramma_analysis.error_log[0];
		return 0;
	}
	cout << "预测分析过程如下：\n";
	gramma_analysis.print_answer();
	
	
}