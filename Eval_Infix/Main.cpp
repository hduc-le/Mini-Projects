#include "Infix.h"

int main()
{
	string Input;
	cout << "Enter an infix expression: ";
	getline(cin, Input);

	double result;
	Infix inf(Input);
	if (inf.eval(result))
		cout << "Expression value: " << result << endl;
	else
		cout << "Invalid expression!!!" << endl;

	system("pause");
	return 0;
}