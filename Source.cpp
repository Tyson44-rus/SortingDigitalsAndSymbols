#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <sstream>
using namespace std;


string WhatADigit(string buffer1)
{
	string type = "";
	if (buffer1 == "")
		return "";
	long long buffer;
	istringstream(buffer1) >> buffer;
	if ((buffer >= -32767) && (buffer <= 32767)) type = " is short";
	else if (buffer >= -2147483647 && buffer <= 2147483647) type = " is long";
	else if (buffer >= -9223372036854775807 && buffer <= 9223372036854775807) type = " is long long";
	return type;
}


string WhatASymbol(string buffer1)
{
	string type = "";
	if (buffer1 == "")
		return "";
	if (buffer1.length() < 2)
		type = " is char";
	else
		type = " is string";
	return type;
}

int main()
{
	bool flag = false;
	bool flagsymbol = false;
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream File;
	bool key = 0;
	int savei;
	File.open("C:\\Symbol.txt");
	string Text, Symbol, Digit;
	while (!File.eof())
		Text += File.get();
	for (unsigned int i = 0; i < Text.length() - 1; i++)
	{
		key = 0;
		if (isdigit(Text[i]))
		{
			Digit += Text[i];
			flag = true;
			flagsymbol = true;
		}
		else if (Text[i] == '+' || Text[i] == '-')
		{
			bool flag1;
			if ((Text[i] == '+' || Text[i] == '-') && isdigit(Text[i + 1]) && !(i == 0) && isdigit(Text[i - 1]))
			{
				flag1 = false;
				Digit += "\n";
				Digit += Text[i];
				Digit += Text[i + 1];
				i++;
			}
			else if ((Text[i] == '+' || Text[i] == '-') && isdigit(Text[i + 1]))
				flag1 = true;
			else
				flag1 = false;

			if (flag1)
			{
				Digit += Text[i];
				Digit += Text[i + 1];
				i++;
				flag = true;
				flagsymbol = true;
			}
			else if (!isdigit(Text[i]))
			{
				savei = i;
				key = 1;
			}
			if (!(Symbol.length() == 0) && flagsymbol)
			{
				if (Symbol.back() != '\n')
					Symbol += "\n";
				flagsymbol = false;
			}
		}
		else
		{
			if (flag)
			{
				Digit += "\n";
				flag = false;
			}
			if (flagsymbol)
			{
				if (!(Symbol.length() == 0) && Symbol.back() != '\n')
					Symbol += "\n";
				flagsymbol = false;
			}
			if (!isdigit(Text[i]) && !(i == 0) && isdigit(Text[i - 1]) && isdigit(Text[i + 1]) && Text[i] != '\n')
			{
				Symbol += Text[i];
				Symbol += "\n";
			}
			else if (!isdigit(Text[i]) && isdigit(Text[i + 1]) && i == 0 && Text[i] != '\n')
			{
				Symbol += Text[i];
				Symbol += "\n";
			}
			else if (!isdigit(Text[i]) && !(i == 0) && isdigit(Text[i + 1]) && Text[i - 1] == '\n')
			{
				Symbol += Text[i];
				Symbol += "\n";
			}
			else if (!isdigit(Text[i]) && !(i == 0) && Text[i + 1] == '\n' && isdigit(Text[i - 1]))
			{
				Symbol += Text[i];
			}
			else
				Symbol += Text[i];
		}
		if (key)
		{
			Symbol += Text[savei];
			Symbol += Text[savei + 1];
			i++;
			if (flag)
			{
				Digit += "\n";
				flag = false;
			}
		}
	}
	string number, buffer;
	if (!Digit.length() == 0)
	{
		number += Digit[0];
		buffer += Digit[0];
	}
	for (unsigned int i = 1; i < Digit.length(); i++)
	{
		if (Digit[i] != '\n')
		{
			buffer += Digit[i];
			number += Digit[i];
		}
		else
		{
			number += WhatADigit(buffer);
			buffer.clear();
			number += "\n";
		}
	}
	number += WhatADigit(buffer);
	if (number.length() != 0)
		number.pop_back();
	buffer.clear();
	string symbol;
	if (!Symbol.length() == 0)
	{
		symbol += Symbol[0];
		buffer += Symbol[0];
	}
	for (unsigned int i = 1; i < Symbol.length(); i++)
	{
		if (Symbol[i] != '\n')
		{
			buffer += Symbol[i];
			symbol += Symbol[i];
		}
		else
		{
			symbol += WhatASymbol(buffer);
			buffer.clear();
			symbol += "\n";
		}
	}
	symbol += WhatASymbol(buffer);
	cout << "Символы:" << endl;
	cout << symbol << endl;
	cout << endl << endl;
	cout << "Числа:" << endl;
	cout << number << endl;
	system("pause");
	return 0;
}