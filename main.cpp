#include <iostream>
#include "KMP.h"


int main()
{	
	setlocale(LC_ALL,"ru");
	std::string txt = "abcabcabcabc";
	int k = 3;

	if (IsKPeriodic(txt, k))
	{
		std::cout <<"Строка " << "\033[34m" << txt << "\033[0m" << " состоит из паттерна " << "\033[31m" << txt.substr(0, k) << "\033[0m" << "\n";
	}
	else
	{
		std::cout << "Строка " << "\033[34m" << txt << "\033[0m" << " не периодична\n";
	}

	return 0;
}