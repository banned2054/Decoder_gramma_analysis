#include "Gramma_analysis.h"

int main()
{
	Gramma_analysis gramma_analysis;
	cout << "���������ʽ��\n";
	bool flag = gramma_analysis.Analysis_start(); //���дʷ�������Ԥ�����������

	cout << endl;
	if (!flag)
	{
		cout << "�ʷ�������������ԭ��" + gramma_analysis.error_log[0];
		return 0;
	}
	cout << "�ʷ����������\n";
	gramma_analysis.print_word();
	cout << endl;
	gramma_analysis.Analysis(); //�����﷨����

	if (!gramma_analysis.error_log.empty()) //�﷨��������
	{
		cout << "�﷨������������ԭ��" + gramma_analysis.error_log[0];
		return 0;
	}
	cout << "Ԥ������������£�\n";
	gramma_analysis.print_answer(); //����﷨�������

	return 0;
}
